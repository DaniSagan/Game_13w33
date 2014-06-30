/*
 * Road.cpp
 *
 *  Created on: Aug 14, 2013
 *      Author: daniel
 */

#include "Road.h"

namespace dfv
{

Road::Road():
		id(straight),
		orientation(0)
{
	// TODO Auto-generated constructor stub

}

Road::~Road()
{
	// TODO Auto-generated destructor stub
}

void Road::Create(const std::vector<sf::Vector3f>& vertices, Type type,
		unsigned int orientation)
{
	if(vertices.size() == 4)
	{
		this->vertices.resize(4);
		for(unsigned int i = 0; i < 4; i++)
		{
			this->vertices[i] = vertices[i];
		}

		this->normals.resize(4);
		this->normals[0] = dfv::Utils::Cross(
				dfv::Utils::Diff(this->vertices[1], this->vertices[0]),
				dfv::Utils::Diff(this->vertices[3], this->vertices[0]));
		this->normals[1] = dfv::Utils::Cross(
				dfv::Utils::Diff(this->vertices[2], this->vertices[1]),
				dfv::Utils::Diff(this->vertices[0], this->vertices[1]));
		this->normals[2] = dfv::Utils::Cross(
				dfv::Utils::Diff(this->vertices[3], this->vertices[2]),
				dfv::Utils::Diff(this->vertices[1], this->vertices[2]));
		this->normals[3] = dfv::Utils::Cross(
				dfv::Utils::Diff(this->vertices[0], this->vertices[3]),
				dfv::Utils::Diff(this->vertices[2], this->vertices[3]));

		this->id = type;
		this->orientation = orientation;

		this->tex_coords.resize(4);
		if(this->orientation == 0)
		{
			this->tex_coords[0] = sf::Vector2f(0.f, 0.f);
			this->tex_coords[1] = sf::Vector2f(1.f, 0.f);
			this->tex_coords[2] = sf::Vector2f(1.f, 1.f);
			this->tex_coords[3] = sf::Vector2f(0.f, 1.f);
		}
		if(this->orientation == 1)
		{
			this->tex_coords[0] = sf::Vector2f(1.f, 0.f);
			this->tex_coords[1] = sf::Vector2f(1.f, 1.f);
			this->tex_coords[2] = sf::Vector2f(0.f, 1.f);
			this->tex_coords[3] = sf::Vector2f(0.f, 0.f);
		}
		if(this->orientation == 2)
		{
			this->tex_coords[0] = sf::Vector2f(1.f, 1.f);
			this->tex_coords[1] = sf::Vector2f(0.f, 1.f);
			this->tex_coords[2] = sf::Vector2f(0.f, 0.f);
			this->tex_coords[3] = sf::Vector2f(1.f, 0.f);
		}
		if(this->orientation == 3)
		{
			this->tex_coords[0] = sf::Vector2f(0.f, 1.f);
			this->tex_coords[1] = sf::Vector2f(0.f, 0.f);
			this->tex_coords[2] = sf::Vector2f(1.f, 0.f);
			this->tex_coords[3] = sf::Vector2f(1.f, 1.f);
		}
	}
	else
	{
		std::cout << "ERROR: Could not create road." << std::endl;
	}
}

void Road::Draw(const dfv::Camera& camera, const dfv::Resources& resources) const
{
	glBindTexture(GL_TEXTURE_2D, resources.img_roads_handles[this->id]);
	glBegin(GL_QUADS);
		glColor3f(1.f, 1.f, 1.f);
		for(unsigned int i = 0; i < 4; i++)
		{
			glTexCoord2d(this->tex_coords[i].x, this->tex_coords[i].y);
			glNormal3f(this->normals[i].x, this->normals[i].y, this->normals[i].z);
			glVertex3f(this->vertices[i].x, this->vertices[i].y, this->vertices[i].z + 0.01f);
		}
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Road::SetId(unsigned int id)
{
	this->id = id;
}

void Road::SetOrientation(unsigned int orientation)
{
	this->orientation = orientation;
	if(this->orientation == 0)
	{
		this->tex_coords[0] = sf::Vector2f(0.f, 0.f);
		this->tex_coords[1] = sf::Vector2f(1.f, 0.f);
		this->tex_coords[2] = sf::Vector2f(1.f, 1.f);
		this->tex_coords[3] = sf::Vector2f(0.f, 1.f);
	}
	if(this->orientation == 1)
	{
		this->tex_coords[0] = sf::Vector2f(1.f, 0.f);
		this->tex_coords[1] = sf::Vector2f(1.f, 1.f);
		this->tex_coords[2] = sf::Vector2f(0.f, 1.f);
		this->tex_coords[3] = sf::Vector2f(0.f, 0.f);
	}
	if(this->orientation == 2)
	{
		this->tex_coords[0] = sf::Vector2f(1.f, 1.f);
		this->tex_coords[1] = sf::Vector2f(0.f, 1.f);
		this->tex_coords[2] = sf::Vector2f(0.f, 0.f);
		this->tex_coords[3] = sf::Vector2f(1.f, 0.f);
	}
	if(this->orientation == 3)
	{
		this->tex_coords[0] = sf::Vector2f(0.f, 1.f);
		this->tex_coords[1] = sf::Vector2f(0.f, 0.f);
		this->tex_coords[2] = sf::Vector2f(1.f, 0.f);
		this->tex_coords[3] = sf::Vector2f(1.f, 1.f);
	}
}

unsigned int Road::GetOrientation() const
{
	return this->orientation;
}

unsigned int Road::GetId() const
{
	return this->id;
}

} /* namespace dfv */


