/*
 * Quad.cpp
 *
 *  Created on: Jan 7, 2015
 *      Author: daniel
 */

#include "Quad.h"

namespace dfv
{

Quad::Quad()
{

}

void Quad::create(const std::vector<sf::Vector3f>& vertices)
{
	assert(vertices.size() == 4);
	this->vertices.resize(4);
	for(unsigned int i = 0; i < 4; i++)
	{
		this->vertices.at(i) = vertices.at(i);
	}
	this->normals.resize(4);
	this->normals[0] = Utils::cross(this->vertices[1] - this->vertices[0],
			                        this->vertices[3] - this->vertices[0]);
	this->normals[1] = Utils::cross(this->vertices[2] - this->vertices[1],
				                    this->vertices[0] - this->vertices[1]);
	this->normals[2] = Utils::cross(this->vertices[3] - this->vertices[2],
									this->vertices[1] - this->vertices[2]);
	this->normals[3] = Utils::cross(this->vertices[0] - this->vertices[3],
									this->vertices[2] - this->vertices[3]);
	this->normals.at(0) = this->normals.at(0) / Utils::length(this->normals.at(0));
	this->normals.at(1) = this->normals.at(1) / Utils::length(this->normals.at(1));
	this->normals.at(2) = this->normals.at(2) / Utils::length(this->normals.at(2));
	this->normals.at(3) = this->normals.at(3) / Utils::length(this->normals.at(3));
}

void Quad::create(const sf::Vector3f & v0,
				  const sf::Vector3f & v1,
				  const sf::Vector3f & v2,
				  const sf::Vector3f & v3)
{
	this->vertices.resize(4);
	this->vertices[0] = v0;
	this->vertices[1] = v1;
	this->vertices[2] = v2;
	this->vertices[3] = v3;

	this->normals.resize(4);
	this->normals[0] = Utils::cross(this->vertices[1] - this->vertices[0],
									this->vertices[3] - this->vertices[0]);
	this->normals[1] = Utils::cross(this->vertices[2] - this->vertices[1],
									this->vertices[0] - this->vertices[1]);
	this->normals[2] = Utils::cross(this->vertices[3] - this->vertices[2],
									this->vertices[1] - this->vertices[2]);
	this->normals[3] = Utils::cross(this->vertices[0] - this->vertices[3],
									this->vertices[2] - this->vertices[3]);
	this->normals.at(0) = this->normals.at(0) / Utils::length(this->normals.at(0));
	this->normals.at(1) = this->normals.at(1) / Utils::length(this->normals.at(1));
	this->normals.at(2) = this->normals.at(2) / Utils::length(this->normals.at(2));
	this->normals.at(3) = this->normals.at(3) / Utils::length(this->normals.at(3));
}

sf::Vector3f Quad::getVertex(const unsigned int index) const
{
	return this->vertices.at(index);
}

sf::Vector3f Quad::getNormal(const unsigned int vertex_index) const
{
	return this->normals.at(vertex_index);
}

sf::Vector3f Quad::getNormal() const
{
	assert(this->vertices.size() == 4);
	sf::Vector3f v =  Utils::cross(Utils::diff(this->vertices[1], this->vertices[0]),
								   Utils::diff(this->vertices[3], this->vertices[0]));
	return v / Utils::length(v);
}

void Quad::draw() const
{
	assert(this->vertices.size() == 4);
	sf::Vector3f normal = this->getNormal();
	glNormal3f(normal.x, normal.y, normal.z);
	std::vector<sf::Vector3f>::const_iterator it;
	for(it = this->vertices.begin(); it != this->vertices.end(); it++)
	{
		glVertex3f(it->x, it->y, it->z);
	}

}

float Quad::getAvgHeight() const
{
	return 0.25 * (this->vertices.at(0).z + this->vertices.at(1).z + this->vertices.at(2).z + this->vertices.at(3).z);
}

float Quad::getMaxInclination() const
{
	std::vector<float> inc(4);
	inc.at(0) = Utils::pitch(this->vertices[0]-this->vertices[1]);
	inc.at(1) = Utils::pitch(this->vertices[1]-this->vertices[2]);
	inc.at(2) = Utils::pitch(this->vertices[2]-this->vertices[3]);
	inc.at(3) = Utils::pitch(this->vertices[3]-this->vertices[0]);
	return *(std::max_element(inc.begin(), inc.end()));
}

float Quad::getMinHeight() const
{
	std::vector<float> heights;
	for(auto vertex: this->vertices)
	{
		heights.push_back(vertex.z);
	}
	return *(std::min_element(heights.begin(), heights.end()));
}

float Quad::getMaxheight() const
{
	std::vector<float> heights;
	for(auto vertex: this->vertices)
	{
		heights.push_back(vertex.z);
	}
	return *(std::max_element(heights.begin(), heights.end()));
}

string osString(size_t level, const string& name, const Quad& quad)
{
	stringstream ss;
	if(name.empty())
	{
		ss << strRepeat(level, string("\t")) << "{" << endl;
	}
	else
	{
		ss << strRepeat(level, string("\t")) << "Quad " << name << " = {" << endl;
	}
	ss << osString(level+1, "v0", quad.vertices.at(0));
	ss << osString(level+1, "v1", quad.vertices.at(1));
	ss << osString(level+1, "v2", quad.vertices.at(2));
	ss << osString(level+1, "v3", quad.vertices.at(3));
	ss << strRepeat(level, string("\t")) << "}" << endl;
	return ss.str();
}

bool isRead(Serializer& ser, Quad& quad)
{
	sf::Vector3f v0, v1, v2, v3;
	bool finished = false;
	while(!finished)
	{
		Serializer::Reading reading;
		Serializer::Reading::Position pos = ser.read(reading);
		if(pos == Serializer::Reading::OBJECT_END)
		{
			finished = true;
		}
		else if(pos == Serializer::Reading::VALUE)
		{
			if(reading.name == "v0")
			{
				isRead(reading, v0);
			}
			else if(reading.name == "v1")
			{
				isRead(reading, v1);
			}
			else if(reading.name == "v2")
			{
				isRead(reading, v2);
			}
			else if(reading.name == "v3")
			{
				isRead(reading, v3);
			}
		}
	}
	quad.create(v0, v1, v2, v3);
	return true;
}

} /* namespace dfv */
