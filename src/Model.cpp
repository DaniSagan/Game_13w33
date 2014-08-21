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

void Model::draw() const
{
	glBegin(GL_QUADS);
	glColor3f(0.5, 0.5, 0.5);
	for(auto q: this->facade_quads)
	{
		q.draw();
	}
	glEnd();
}

/*void Model::addBaseVertex(const sf::Vector2f& vertex)
{
	this->base_vertices.push_back(vertex);
}*/

void Model::create(const Quad & tile_quad,
				   const Quad & base_quad,
				   unsigned int floor_count)
{
	std::vector<float> tile_heights = {tile_quad.getVertex(0).z,
									   tile_quad.getVertex(1).z,
									   tile_quad.getVertex(2).z,
									   tile_quad.getVertex(3).z};
	float max_height = *(std::max_element(tile_heights.begin(), tile_heights.end()));
	float min_height = *(std::min_element(tile_heights.begin(), tile_heights.end()));

	const sf::Vector3f &origin = tile_quad.getVertex(0);
	for(unsigned int i = 0; i < 4; i++)
	{
		sf::Vector3f v0(origin.x + base_quad.getVertex(i%4).x,     origin.y + base_quad.getVertex(i%4).y,     min_height);
		sf::Vector3f v1(origin.x + base_quad.getVertex((i+1)%4).x, origin.y + base_quad.getVertex((i+1)%4).y, min_height);
		sf::Vector3f v2(origin.x + base_quad.getVertex((i+1)%4).x, origin.y + base_quad.getVertex((i+1)%4).y, max_height + 2.0);
		sf::Vector3f v3(origin.x + base_quad.getVertex(i%4).x,     origin.y + base_quad.getVertex(i%4).y,     max_height + 2.0);
		Quad q = Quad();
		q.create(v0, v1, v2, v3);
		this->facade_quads.push_back(q);
	}
	sf::Vector3f v0(origin.x + base_quad.getVertex(0).x, origin.y + base_quad.getVertex(0).y, max_height + 2.0);
	sf::Vector3f v1(origin.x + base_quad.getVertex(1).x, origin.y + base_quad.getVertex(1).y, max_height + 2.0);
	sf::Vector3f v2(origin.x + base_quad.getVertex(2).x, origin.y + base_quad.getVertex(2).y, max_height + 2.0);
	sf::Vector3f v3(origin.x + base_quad.getVertex(3).x, origin.y + base_quad.getVertex(3).y, max_height + 2.0);
	Quad q = Quad();
	q.create(v0, v1, v2, v3);
	this->facade_quads.push_back(q);

}

} /* namespace dfv */
