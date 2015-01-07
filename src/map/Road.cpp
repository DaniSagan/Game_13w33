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

map<string, Road::Type> Road::strType = {
		{"none", 				Road::none},
		{"undefined", 			Road::none},
		{"straight", 			Road::straight},
		{"cross", 				Road::cross},
		{"tcross", 				Road::tcross},
		{"curve", 				Road::curve},
		{"av_straight", 		Road::av_straight},
		{"av_cross", 			Road::av_cross},
		{"av_tcross", 			Road::av_tcross},
		{"roundabout_center", 	Road::roundabout_center},
		{"roundabout_side", 	Road::roundabout_side},
		{"roundabout_corner",	Road::roundabout_corner},
		{"roundabout_exit", 	Road::roundabout_exit}
};

Road::Road():
		id(0),
		type(straight),
		orientation(0)
{
}

Road::~Road()
{
}

void Road::create(const std::vector<sf::Vector3f>& vertices, Type type,
		unsigned int orientation)
{
	assert(vertices.size() == 4);
	assert(orientation < 4);
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

	this->setType(type);
	//this->id = type;
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

void Road::draw(const dfv::Camera& camera, const dfv::Resources& resources) const
{
	glBindTexture(GL_TEXTURE_2D, resources.imgRoadsHandles.at(this->id));
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

/*void Road::setId(unsigned int id)
{
	assert(id < 11);
	this->id = id;
}*/

void Road::setType(Type type)
{
	this->type = type;
	switch(type)
	{
	case straight: 			this->id = 0; break;
	case cross: 			this->id = 1; break;
	case tcross: 			this->id = 2; break;
	case curve: 			this->id = 3; break;
	case av_straight: 		this->id = 4; break;
	case av_cross: 			this->id = 5; break;
	case av_tcross: 		this->id = 6; break;
	case roundabout_center: this->id = 7; break;
	case roundabout_side: 	this->id = 8; break;
	case roundabout_corner: this->id = 9; break;
	case roundabout_exit: 	this->id = 10; break;
	}
	assert(id < 11);
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

Road::Type Road::getType() const
{
	return this->type;
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

string Road::asString(Road::Type type)
{
	switch(type)
	{
	case Road::straight: 			return "straight"; 			break;
	case Road::cross: 				return "cross"; 			break;
	case Road::tcross: 				return "tcross"; 			break;
	case Road::curve: 				return "curve"; 			break;
	case Road::av_straight: 		return "av_straight"; 		break;
	case Road::av_cross: 			return "av_cross"; 			break;
	case Road::av_tcross: 			return "av_tcross"; 		break;
	case Road::roundabout_center: 	return "roundabout_center"; break;
	case Road::roundabout_side: 	return "roundabout_side"; 	break;
	case Road::roundabout_corner: 	return "roundabout_corner"; break;
	case Road::roundabout_exit: 	return "roundabout_exit"; 	break;
	default: 						return "undefined"; 		break;
	}
}

Road::Type Road::fromString(const string& str)
{
	if(Road::strType.find(str) != strType.end())
	{
		return Road::strType.at(str);
	}
	else
	{
		return Road::none;
	}
}

} /* namespace dfv */


