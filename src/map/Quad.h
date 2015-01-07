/*
 * Quad.h
 *
 *  Created on: Jan 7, 2015
 *      Author: daniel
 */

#ifndef SRC_MAP_QUAD_H_
#define SRC_MAP_QUAD_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "../Utils.h"
#include "../Serializer.h"

namespace dfv
{

class Quad
{
public:
	Quad();
	void create(const std::vector<sf::Vector3f>& vertices);
	void create(const sf::Vector3f & v0,
			    const sf::Vector3f & v1,
			    const sf::Vector3f & v2,
			    const sf::Vector3f & v3);
	sf::Vector3f getVertex(const unsigned int index) const;
	sf::Vector3f getNormal(const unsigned int vertex_index) const;
	sf::Vector3f getNormal() const;
	void draw() const;
	float getAvgHeight() const;
	float getMaxInclination() const;
	float getMinHeight() const;
	float getMaxheight() const;
	friend string osString(size_t level, const string& name, const Quad& quad);
protected:
	std::vector<sf::Vector3f> vertices;
	std::vector<sf::Vector3f> normals;
};

} /* namespace dfv */

#endif /* SRC_MAP_QUAD_H_ */
