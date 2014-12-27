/*
 *  Hyperopolis: Megacities building game.
    Copyright (C) 2014  Daniel Fernández Villanueva

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

 * Tile.cpp
 *
 *  Created on: Aug 12, 2013
 *      Author: daniel
 */

#include "Tile.h"

namespace dfv
{

Tile::Tile():
		is_road(false),
		lp_road(NULL),
		lp_prop(NULL),
		lp_structure(NULL),
		lp_lot(NULL)
{
	// TODO Auto-generated constructor stub
}

Tile::~Tile()
{
	if(lp_road != NULL) delete this->lp_road;
	if(lp_structure != NULL) delete this->lp_structure;
}

void Tile::create(sf::Vector2f pos, float h0, float h1, float h2, float h3)
{
	this->vertices.resize(4);
	this->vertices.at(0) = sf::Vector3f(pos.x, pos.y, h0);
	this->vertices.at(1) = sf::Vector3f(pos.x + 1.0, pos.y, h1);
	this->vertices.at(2) = sf::Vector3f(pos.x + 1.0, pos.y + 1.0, h2);
	this->vertices.at(3) = sf::Vector3f(pos.x , pos.y + 1.0, h3);

	this->normals.resize(4);
	this->normals.at(0) = Utils::cross(this->vertices.at(1)-this->vertices.at(0),
									   this->vertices.at(3)-this->vertices.at(0));
	this->normals.at(1) = Utils::cross(this->vertices.at(2)-this->vertices.at(1),
									   this->vertices.at(0)-this->vertices.at(1));
	this->normals.at(2) = Utils::cross(this->vertices.at(3)-this->vertices.at(2),
									   this->vertices.at(1)-this->vertices.at(2));
	this->normals.at(3) = Utils::cross(this->vertices.at(0)-this->vertices.at(3),
									   this->vertices.at(2)-this->vertices.at(3));

	this->colors.resize(4);

}

void Tile::setColor(sf::Color color)
{
	this->color.x = (float)color.r / 255.f;
	this->color.y = (float)color.g / 255.f;
	this->color.z = (float)color.b / 255.f;

	const float water_threshold = 0.f;
	const float sand_threshold = 0.1f;
	const float snow_threshold = 40.0f;

	for(unsigned int i = 0; i < 4; i++)
	{
		if(this->vertices[i].z < water_threshold)
		{
			this->colors[i] = sf::Vector3f(0.05f, 0.05f, 0.25f);
		}
		else if(this->vertices[i].z < sand_threshold)
		{
			float rr1 = ((float)rand() / (float)RAND_MAX) * 0.1f;
			float rr2 = ((float)rand() / (float)RAND_MAX) * 0.1f;
			float rr3 = ((float)rand() / (float)RAND_MAX) * 0.1f;
			this->colors[i] = sf::Vector3f(0.9f + rr1, 0.9f + rr2, 0.4f + rr3);
		}
		else if(this->vertices[i].z > snow_threshold + static_cast<float>(rand() % 100)/10.f && this->lp_road == NULL)
		{
			float rr = ((float)rand() / (float)RAND_MAX) * 0.1f;
			this->colors[i] = sf::Vector3f(0.9f-rr, 0.9f-rr, 0.95f-rr);
		}
		else
		{
			this->colors[i] = sf::Vector3f(this->color.x, this->color.y, this->color.z);
		}
	}
}

void Tile::draw(const dfv::Camera& camera, const dfv::Resources& resources) const
{
	glColor3f(this->colors[0].x, this->colors[0].y, this->colors[0].z);
	glNormal3f(this->normals[0].x, this->normals[0].y, this->normals[0].z);
	glVertex3f(this->vertices[0].x, this->vertices[0].y, this->vertices[0].z);

	glColor3f(this->colors[1].x, this->colors[1].y, this->colors[1].z);
	glNormal3f(this->normals[1].x, this->normals[1].y, this->normals[1].z);
	glVertex3f(this->vertices[1].x, this->vertices[1].y, this->vertices[1].z);

	glColor3f(this->colors[2].x, this->colors[2].y, this->colors[2].z);
	glNormal3f(this->normals[2].x, this->normals[2].y, this->normals[2].z);
	glVertex3f(this->vertices[2].x, this->vertices[2].y, this->vertices[2].z);

	glColor3f(this->colors[3].x, this->colors[3].y, this->colors[3].z);
	glNormal3f(this->normals[3].x, this->normals[3].y, this->normals[3].z);
	glVertex3f(this->vertices[3].x, this->vertices[3].y, this->vertices[3].z);
}

bool Tile::hasProp() const
{
	return this->lp_prop != NULL;
}

void Tile::setAsRoad(const bool r)
{
	this->is_road = r;
}

bool Tile::isRoad() const
{
	return this->lp_road != NULL;
}

void Tile::addRoad(dfv::Road::Type type, unsigned int orientation)
{
	this->is_road = true;
	this->lp_road = new Road;
	this->lp_road->create(this->vertices, type, orientation);
	this->setColor(sf::Color(32, 32, 32));
}

unsigned int Tile::getRoadId() const
{
	if(this->isRoad())
	{
		return this->lp_road->getId();
	}
	else
	{
		return Road::straight;
	}

}

unsigned int Tile::getRoadOrientation() const
{
	if(this->isRoad())
	{
		return this->lp_road->getOrientation();
	}
	else
	{
		return 0;
	}
}

bool Tile::setRoadId(unsigned int road_id)
{
	if(this->isRoad())
	{
		this->lp_road->setId(road_id);
		return true;
	}
	else
	{
		return false;
	}
}

bool Tile::setRoadOrientation(unsigned int road_orientation)
{
	if(this->isRoad())
	{
		this->lp_road->setOrientation(road_orientation);
		return true;
	}
	else
	{
		return false;
	}
}

void Tile::addProp(Prop* lp_prop)
{
	this->lp_prop = lp_prop;
}

sf::Vector3f Tile::getVertex(const unsigned int index) const
{
	if(index < 4)
	{
		return this->vertices.at(index);
	}
	return this->vertices.back();
}

const std::vector<sf::Vector3f> & Tile::getVertices() const
{
	return this->vertices;
}

sf::Vector3f Tile::getColor(unsigned int index) const
{
	return this->colors[index];
}

sf::Vector3f Tile::getNormal(unsigned int index) const
{
	return this->normals[index];
}

void Tile::setVertex(const unsigned int index, const sf::Vector3f& vertex)
{
	this->vertices[index] = vertex;
}

sf::Color Tile::getSfmlColor() const
{
	return sf::Color(this->color.x * 255.f, this->color.y * 255.f, this->color.z * 255.f);
}

void Tile::drawRoad(const Camera& camera, const Resources& resources) const
{
	if(this->isRoad())
	{
		this->lp_road->draw(camera, resources);
	}
}

void Tile::drawProp(const Camera& camera, const Resources& resources) const
{
	if(this->lp_prop != NULL)
	{
		this->lp_prop->draw(camera, resources);
	}
}

bool Tile::isWater() const
{
	float threshold = 0.f;
	return (this->vertices[0].z < threshold ||
			this->vertices[1].z < threshold ||
			this->vertices[2].z < threshold ||
			this->vertices[3].z < threshold);
}

bool Tile::isBeach() const
{
	float threshold = 0.1f;
	return ((this->vertices[0].z < threshold ||
			 this->vertices[1].z < threshold ||
			 this->vertices[2].z < threshold ||
			 this->vertices[3].z < threshold) &&
			 !this->isWater());
}

bool Tile::clearRoad()
{
	if(this->lp_road != NULL)
	{
		delete this->lp_road;
		this->lp_road = NULL;
		this->setColor(sf::Color(10 + rand() % 20, 130 + rand() % 20, 10 + rand() % 20));
		return true;
	}
	else
	{
		return false;
	}

}

bool Tile::clearProp()
{
	std::cout << "Clearing prop" << std::endl;
	if(this->lp_prop != NULL)
	{
		delete this->lp_prop;
		this->lp_prop = NULL;
		this->setColor(sf::Color(10 + rand() % 20, 130 + rand() % 20, 10 + rand() % 20));
		return true;
	}
	else
	{
		return false;
	}
}

Quad Tile::getQuad() const
{
	Quad res;
	res.create(this->vertices);
	return res;
}

void Tile::createStructure(Quad base, unsigned int floor_count)
{
	Model model;
	model.create(this->getQuad(), base, floor_count);
	this->lp_structure = new Structure;
	this->lp_structure->setModel(model);
	this->setColor({220, 220, 220});
}

void Tile::destroyStructure()
{
	delete this->lp_structure;
	this->lp_structure = NULL;
}

void Tile::drawStructureBox() const
{
	if(this->lp_structure != NULL)
	{
		this->lp_structure->drawBox();
	}
}

void Tile::drawStructureOutline() const
{
	if(this->lp_structure != NULL)
	{
		this->lp_structure->drawOutline();
	}
}

bool Tile::hasStructure() const
{
	if(this->lp_lot != NULL)
	{
		return this->lp_lot->hasStructure();
	}
	else
	{
		return false;
	}
}

} /* namespace dfv */


