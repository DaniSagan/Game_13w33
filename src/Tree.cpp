/*
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
	type(0)
{
	// TODO Auto-generated constructor stub
}

Tree::~Tree()
{
	// TODO Auto-generated destructor stub
}

void Tree::Create(const std::vector<sf::Vector3f>& tile_vertices)
{
	if(tile_vertices.size() != 4)
	{
		throw std::invalid_argument("tile_vertices must have 4 elements");
	}

	sf::Vector3f mid_point((tile_vertices[0].x + tile_vertices[2].x) / 2.0,
			               (tile_vertices[0].y + tile_vertices[2].y) / 2.0,
			               (tile_vertices[0].z + tile_vertices[2].z) / 2.0);
	std::vector<sf::Vector3f> quad_vertices(4);
	this->quads.resize(4);
	quad_vertices[0] = tile_vertices[0];
	quad_vertices[1] = mid_point;
	quad_vertices[2] = mid_point + sf::Vector3f(0.0, 0.0, 1.0);
	quad_vertices[3] = tile_vertices[0] + sf::Vector3f(0.0, 0.0, 1.0);
	this->quads[0].create(quad_vertices);
	quad_vertices[0] = tile_vertices[1];
	quad_vertices[1] = mid_point;
	quad_vertices[2] = mid_point + sf::Vector3f(0.0, 0.0, 1.0);
	quad_vertices[3] = tile_vertices[1] + sf::Vector3f(0.0, 0.0, 1.0);
	this->quads[1].create(quad_vertices);
	quad_vertices[0] = tile_vertices[2];
	quad_vertices[1] = mid_point;
	quad_vertices[2] = mid_point + sf::Vector3f(0.0, 0.0, 1.0);
	quad_vertices[3] = tile_vertices[2] + sf::Vector3f(0.0, 0.0, 1.0);
	this->quads[2].create(quad_vertices);
	quad_vertices[0] = tile_vertices[3];
	quad_vertices[1] = mid_point;
	quad_vertices[2] = mid_point + sf::Vector3f(0.0, 0.0, 1.0);
	quad_vertices[3] = tile_vertices[3] + sf::Vector3f(0.0, 0.0, 1.0);
	this->quads[3].create(quad_vertices);
	this->type = rand() % 2;
}

void Tree::Draw(const dfv::Camera& camera, const dfv::Resources& resources) const
{
	if(this->type == 0)
	{
		glBindTexture(GL_TEXTURE_2D, resources.img_tree.getHandle());
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, resources.img_tree_2.getHandle());
	}

	float yaw = camera.GetRpy().z;
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
			glTexCoord2d(resources.img_tree.getTexCoords(i).x, resources.img_tree.getTexCoords(i).y);
			glNormal3f(this->quads[index].getNormal(i).x, this->quads[index].getNormal(i).y, this->quads[index].getNormal(i).z);
			glVertex3f(this->quads[index].getVertex(i).x, this->quads[index].getVertex(i).y, this->quads[index].getVertex(i).z);
		}
	glEnd();
}

} /* namespace dfv */
