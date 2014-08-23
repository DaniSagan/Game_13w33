/*
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
	for(unsigned int i = 0; i < this->floor_count; i++)
	{
		for(unsigned int j = 0; j < 4; j++)
		{
			v0 = vv.at(j)       + sf::Vector3f(0.0, 0.0, max_height + street_height + floor_height*i);
			v1 = vv.at((j+1)%4) + sf::Vector3f(0.0, 0.0, max_height + street_height + floor_height*i);
			v2 = vv.at((j+1)%4) + sf::Vector3f(0.0, 0.0, max_height + street_height + floor_height*i + line_width);
			v3 = vv.at(j)       + sf::Vector3f(0.0, 0.0, max_height + street_height + floor_height*i + line_width);
			q.create(v0, v1, v2, v3);
			this->outline_quads.push_back(q);
		}
	}
}

} /* namespace dfv */
