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

 * Tree.cpp
 *
 *  Created on: Jun 23, 2014
 *      Author: daniel
 */

#include "Tree.h"

#include <stdexcept>

namespace dfv {

Tree::Tree():
	lp_img(NULL),
	id(0)
{
	// TODO Auto-generated constructor stub
}

Tree::~Tree()
{
	// TODO Auto-generated destructor stub
}

void Tree::create(const std::vector<sf::Vector3f>& tile_vertices, unsigned int id)
{
	assert(tile_vertices.size() == 4);
	assert(id >= 0 && id <= 1);
	sf::Vector3f mid_point = (tile_vertices.at(1) + tile_vertices.at(3)) * 0.5f;
	std::vector<sf::Vector3f> quad_vertices(4);
	this->quads.resize(4);
	for(std::size_t i = 0; i < this->quads.size(); i++)
	{
		quad_vertices.at(0) = tile_vertices[i];
		quad_vertices.at(1) = mid_point;
		quad_vertices.at(2) = mid_point + sf::Vector3f(0.0, 0.0, 1.0);
		quad_vertices.at(3) = tile_vertices[i] + sf::Vector3f(0.0, 0.0, 1.0);
		this->quads.at(i).create(quad_vertices);
	}
	this->id = id;
}

void Tree::draw(const dfv::Camera& camera, const dfv::Resources& resources) const
{
	/*if(this->type == 0)
	{
		glBindTexture(GL_TEXTURE_2D, resources.imgTree.getHandle());
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, resources.imgTree2.getHandle());
	}*/
	glBindTexture(GL_TEXTURE_2D, resources.images.trees[this->id]);

	float yaw = camera.getRpy().z;
	glColor4f(1.f, 1.f, 1.f, 1.0f);
	if(yaw < 90.f)
	{
		this->drawQuad(2, resources);
		this->drawQuad(1, resources);
		this->drawQuad(3, resources);
		this->drawQuad(0, resources);
	}
	else if(yaw > 90.f && yaw <= 180.0)
	{
		this->drawQuad(1, resources);
		this->drawQuad(0, resources);
		this->drawQuad(2, resources);
		this->drawQuad(3, resources);
	}
	else if(yaw > 180.f && yaw <= 270.0)
	{
		this->drawQuad(0, resources);
		this->drawQuad(1, resources);
		this->drawQuad(3, resources);
		this->drawQuad(2, resources);
	}
	else if(yaw > 270.0)
	{
		this->drawQuad(3, resources);
		this->drawQuad(0, resources);
		this->drawQuad(2, resources);
		this->drawQuad(1, resources);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Tree::drawQuad(const unsigned int index, const dfv::Resources& resources) const
{
	glBegin(GL_QUADS);
		for(unsigned int i = 0; i < 4; i++)
		{
			//glTexCoord2d(resources.imgTree.getTexCoords(i).x, resources.imgTree.getTexCoords(i).y);
			glTexCoord2d(resources.imgTree.getTexCoords(i).x, resources.imgTree.getTexCoords(i).y);
			glNormal3f(this->quads[index].getNormal(i).x, this->quads[index].getNormal(i).y, this->quads[index].getNormal(i).z);
			glVertex3f(this->quads[index].getVertex(i).x, this->quads[index].getVertex(i).y, this->quads[index].getVertex(i).z);
		}
	glEnd();
}

unsigned int Tree::getId() const
{
	return this->id;
}

Prop::Type Tree::getType() const
{
	return Prop::TREE;
}

} /* namespace dfv */
