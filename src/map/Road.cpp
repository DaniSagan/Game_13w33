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

void Road::create(const std::vector<sf::Vector3f>& vertices, Type type,
		unsigned int orientation)
{
	assert(vertices.size() == 4);
	this->vertices.resize(4);
	for(unsigned int i = 0; i < 4; i++)
	{
		this->vertices[i] = vertices[i] + sf::Vector3f(0.0, 0.0, 0.01f);
	}
	this->normals.resize(4);
	this->normals[0] = dfv::Utils::cross(
			dfv::Utils::diff(this->vertices[1], this->vertices[0]),
			dfv::Utils::diff(this->vertices[3], this->vertices[0]));
	this->normals[1] = dfv::Utils::cross(
			dfv::Utils::diff(this->vertices[2], this->vertices[1]),
			dfv::Utils::diff(this->vertices[0], this->vertices[1]));
	this->normals[2] = dfv::Utils::cross(
			dfv::Utils::diff(this->vertices[3], this->vertices[2]),
			dfv::Utils::diff(this->vertices[1], this->vertices[2]));
	this->normals[3] = dfv::Utils::cross(
			dfv::Utils::diff(this->vertices[0], this->vertices[3]),
			dfv::Utils::diff(this->vertices[2], this->vertices[3]));

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

	/*if(vertices.size() == 4)
	{
		this->vertices.resize(4);
		for(unsigned int i = 0; i < 4; i++)
		{
			this->vertices[i] = vertices[i];
		}

		this->normals.resize(4);
		this->normals[0] = dfv::Utils::cross(
				dfv::Utils::diff(this->vertices[1], this->vertices[0]),
				dfv::Utils::diff(this->vertices[3], this->vertices[0]));
		this->normals[1] = dfv::Utils::cross(
				dfv::Utils::diff(this->vertices[2], this->vertices[1]),
				dfv::Utils::diff(this->vertices[0], this->vertices[1]));
		this->normals[2] = dfv::Utils::cross(
				dfv::Utils::diff(this->vertices[3], this->vertices[2]),
				dfv::Utils::diff(this->vertices[1], this->vertices[2]));
		this->normals[3] = dfv::Utils::cross(
				dfv::Utils::diff(this->vertices[0], this->vertices[3]),
				dfv::Utils::diff(this->vertices[2], this->vertices[3]));

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
	}*/
}

void Road::draw(const dfv::Camera& camera, const dfv::Resources& resources) const
{
	glBindTexture(GL_TEXTURE_2D, resources.img_roads_handles[this->id]);
	glBegin(GL_QUADS);
		//glColor3f(1.f, 1.f, 1.f);
		for(unsigned int i = 0; i < 4; i++)
		{
			glTexCoord2d(this->tex_coords[i].x, this->tex_coords[i].y);
			glNormal3f(this->normals[i].x, this->normals[i].y, this->normals[i].z);
			//glVertex3f(this->vertices[i].x, this->vertices[i].y, this->vertices[i].z + 0.01f);
			glVertex3f(this->vertices[i].x, this->vertices[i].y, this->vertices[i].z);
		}
	glEnd();
	//glBindTexture(GL_TEXTURE_2D, 0);
}

void Road::setId(unsigned int id)
{
	this->id = id;
}

void Road::setOrientation(unsigned int orientation)
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

unsigned int Road::getOrientation() const
{
	return this->orientation;
}

unsigned int Road::getId() const
{
	return this->id;
}

char Road::asChar(int type, int orientation)
{
	if(type == Road::straight && (orientation == 0 || orientation == 2)) return '|';
	else if(type == Road::straight && (orientation == 1 || orientation == 3)) return '-';
	else if(type == Road::curve && (orientation == 0 || orientation == 2)) return '/';
	else if(type == Road::curve && (orientation == 1 || orientation == 3)) return '\\';
	else if(type == Road::cross) return '+';
	else return ' ';
}

} /* namespace dfv */


