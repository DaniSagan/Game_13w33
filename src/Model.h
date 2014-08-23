/*
 * Model.h
 *
 *  Created on: Aug 19, 2014
 *      Author: daniel
 */

#ifndef MODEL_H_
#define MODEL_H_

#include <vector>
#include <SFML/Graphics.hpp>
#include <cassert>
#include "Utils.h"

namespace dfv {

class Model {
public:
	Model();
	virtual ~Model();

	void drawBox() const;
	void drawOutlines() const;
	//void addBaseVertex(const sf::Vector2f & vertex);
	void create(const Quad & tile_quad,
			    const Quad & base_quad,
			    unsigned int floor_count);
	//std::vector<sf::Vector2f> base;
private:
	//std::vector<sf::Vector2f> base_vertices;
	//std::vector<sf::Vector3f> vertices;
	Quad base_quad;
	std::vector<Quad> facade_quads;
	std::vector<Quad> outline_quads;
	unsigned int floor_count;

};

} /* namespace dfv */

#endif /* MODEL_H_ */
