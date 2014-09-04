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

 * Model.cpp
 *
 *  Created on: Aug 19, 2014
 *      Author: daniel
 */

#include "Model.h"

namespace dfv {

Model::Model()
{
	// TODO Auto-generated constructor stub

}

Model::~Model()
{
	// TODO Auto-generated destructor stub
}

void Model::drawBox() const
{
	for(auto q: this->facade_quads)
	{
		q.draw();
	}
}

void Model::drawOutlines() const
{
	for(auto q: this->outline_quads)
	{
		q.draw();
	}
}

void Model::create(const Quad & tile_quad,
				   const Quad & base_quad,
				   unsigned int floor_count)
{
	const float street_height = 0.1625f;
	const float floor_height = 0.125f;
	const float margin = 0.01f;
	const float line_width = 0.02f;

	std::vector<float> tile_heights = {tile_quad.getVertex(0).z,
									   tile_quad.getVertex(1).z,
									   tile_quad.getVertex(2).z,
									   tile_quad.getVertex(3).z};
	float max_height = *(std::max_element(tile_heights.begin(), tile_heights.end()));
	float min_height = *(std::min_element(tile_heights.begin(), tile_heights.end()));

	const float building_height = floor_count * floor_height + street_height;

	// Create building box
	const sf::Vector3f &origin = tile_quad.getVertex(0);
	for(unsigned int i = 0; i < 4; i++)
	{
		sf::Vector3f v0(origin.x + base_quad.getVertex(i%4).x,     origin.y + base_quad.getVertex(i%4).y,     min_height);
		sf::Vector3f v1(origin.x + base_quad.getVertex((i+1)%4).x, origin.y + base_quad.getVertex((i+1)%4).y, min_height);
		sf::Vector3f v2(origin.x + base_quad.getVertex((i+1)%4).x, origin.y + base_quad.getVertex((i+1)%4).y, max_height + building_height);
		sf::Vector3f v3(origin.x + base_quad.getVertex(i%4).x,     origin.y + base_quad.getVertex(i%4).y,     max_height + building_height);
		Quad q = Quad();
		q.create(v0, v1, v2, v3);
		this->facade_quads.push_back(q);
	}
	sf::Vector3f v0(origin.x + base_quad.getVertex(0).x, origin.y + base_quad.getVertex(0).y, max_height + building_height);
	sf::Vector3f v1(origin.x + base_quad.getVertex(1).x, origin.y + base_quad.getVertex(1).y, max_height + building_height);
	sf::Vector3f v2(origin.x + base_quad.getVertex(2).x, origin.y + base_quad.getVertex(2).y, max_height + building_height);
	sf::Vector3f v3(origin.x + base_quad.getVertex(3).x, origin.y + base_quad.getVertex(3).y, max_height + building_height);
	Quad q = Quad();
	q.create(v0, v1, v2, v3);
	this->facade_quads.push_back(q);

	// Create building outlines
	std::vector<sf::Vector3f> vh = {sf::Vector3f(v0.x, v0.y, 0.0),
								    sf::Vector3f(v1.x, v1.y, 0.0),
								    sf::Vector3f(v2.x, v2.y, 0.0),
								    sf::Vector3f(v3.x, v3.y, 0.0)};

	std::vector<sf::Vector3f> vv(4);
	for(unsigned int i = 0; i < 4; i++)
	{
		vv.at(i) = vh.at(i) +
				   margin*(vh.at(i%4)-vh.at((i+1)%4))/Utils::length(vh.at(i%4)-vh.at((i+1)%4)) +
				   margin*(vh.at(i%4)-vh.at((i-1)%4))/Utils::length(vh.at(i%4)-vh.at((i-1)%4));
	}

	assert(std::abs(floor_count) < 10000);
	this->floor_count = floor_count;
	for(unsigned int i = 0; i <= this->floor_count; i++)
	{
		for(unsigned int j = 0; j < 4; j++)
		{
			v0 = vv.at(j)       + sf::Vector3f(0.0, 0.0, max_height + street_height + floor_height*i - line_width/2.f);
			v1 = vv.at((j+1)%4) + sf::Vector3f(0.0, 0.0, max_height + street_height + floor_height*i - line_width/2.f);
			v2 = vv.at((j+1)%4) + sf::Vector3f(0.0, 0.0, max_height + street_height + floor_height*i + line_width/2.f);
			v3 = vv.at(j)       + sf::Vector3f(0.0, 0.0, max_height + street_height + floor_height*i + line_width/2.f);
			q.create(v0, v1, v2, v3);
			this->outline_quads.push_back(q);
		}
	}
}

void Model::create(const float min_terrain_height,
		const float max_terrain_height, const sf::Vector2f& position,
		const Quad& base_quad, unsigned int floor_count)
{
	const float street_height = 0.18f;
	const float floor_height = 0.125f;
	const float margin = 0.01f;
	const float line_width = 0.02f;

	const float building_height = floor_count * floor_height + street_height;
	this->height = building_height;

	// Create building box
	const sf::Vector3f origin(position.x, position.y, min_terrain_height);
	for(unsigned int i = 0; i < 4; i++)
	{
		sf::Vector3f v0(origin.x + base_quad.getVertex(i%4).x,     origin.y + base_quad.getVertex(i%4).y,     min_terrain_height);
		sf::Vector3f v1(origin.x + base_quad.getVertex((i+1)%4).x, origin.y + base_quad.getVertex((i+1)%4).y, min_terrain_height);
		sf::Vector3f v2(origin.x + base_quad.getVertex((i+1)%4).x, origin.y + base_quad.getVertex((i+1)%4).y, max_terrain_height + building_height);
		sf::Vector3f v3(origin.x + base_quad.getVertex(i%4).x,     origin.y + base_quad.getVertex(i%4).y,     max_terrain_height + building_height);
		Quad q = Quad();
		q.create(v0, v1, v2, v3);
		this->facade_quads.push_back(q);
	}
	sf::Vector3f v0(origin.x + base_quad.getVertex(0).x, origin.y + base_quad.getVertex(0).y, max_terrain_height + building_height);
	sf::Vector3f v1(origin.x + base_quad.getVertex(1).x, origin.y + base_quad.getVertex(1).y, max_terrain_height + building_height);
	sf::Vector3f v2(origin.x + base_quad.getVertex(2).x, origin.y + base_quad.getVertex(2).y, max_terrain_height + building_height);
	sf::Vector3f v3(origin.x + base_quad.getVertex(3).x, origin.y + base_quad.getVertex(3).y, max_terrain_height + building_height);
	Quad q = Quad();
	q.create(v0, v1, v2, v3);
	this->facade_quads.push_back(q);

	// Create building outlines
	std::vector<sf::Vector3f> vh = {sf::Vector3f(v0.x, v0.y, 0.0),
									sf::Vector3f(v1.x, v1.y, 0.0),
									sf::Vector3f(v2.x, v2.y, 0.0),
									sf::Vector3f(v3.x, v3.y, 0.0)};

	std::vector<sf::Vector3f> vv(4);
	for(unsigned int i = 0; i < 4; i++)
	{
		//float angle = Utils::dot(vh.at(i%4), vh.at((i+1)%4)) / Utils::length()
		sf::Vector3f& v0 = vh.at(i);
		sf::Vector3f& v1 = vh.at((i+1)%4);
		sf::Vector3f& v2 = vh.at((i-1)%4);
		float angle = Utils::angle(v1, v2);
		float margin2 = margin / sin(angle);
		/*vv.at(i) = vh.at(i) +
				   margin*(vh.at(i%4)-vh.at((i+1)%4))/Utils::length(vh.at(i%4)-vh.at((i+1)%4)) +
				   margin*(vh.at(i%4)-vh.at((i-1)%4))/Utils::length(vh.at(i%4)-vh.at((i-1)%4));*/
		vv.at(i) = v0 +
				   margin2 * (v0-v1) / Utils::length(v0-v1) +
				   margin2 * (v0-v2) / Utils::length(v0-v2);
	}

	assert(std::abs(floor_count) < 10000);
	this->floor_count = floor_count;
	for(unsigned int i = 0; i <= this->floor_count; i++)
	{
		for(unsigned int j = 0; j < 4; j++)
		{
			v0 = vv.at(j)       + sf::Vector3f(0.0, 0.0, max_terrain_height + street_height + floor_height*i - line_width/2.f);
			v1 = vv.at((j+1)%4) + sf::Vector3f(0.0, 0.0, max_terrain_height + street_height + floor_height*i - line_width/2.f);
			v2 = vv.at((j+1)%4) + sf::Vector3f(0.0, 0.0, max_terrain_height + street_height + floor_height*i + line_width/2.f);
			v3 = vv.at(j)       + sf::Vector3f(0.0, 0.0, max_terrain_height + street_height + floor_height*i + line_width/2.f);
			q.create(v0, v1, v2, v3);
			this->outline_quads.push_back(q);
		}
	}
}

unsigned int Model::getFloorCount() const
{
	return this->floor_count;
}

float Model::getHeight() const
{
	return this->height;
}

} /* namespace dfv */
