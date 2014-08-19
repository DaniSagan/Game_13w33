/*
 * Prop.h
 *
 *  Created on: Jun 23, 2014
 *      Author: daniel
 */

#ifndef PROP_H_
#define PROP_H_

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Resources.h"
#include "Camera.h"
#include "Utils.h"

namespace dfv {

class Prop
{
public:
	Prop();
	virtual ~Prop();
	virtual void create(const std::vector<sf::Vector3f>& tile_vertices);
	virtual void draw(const dfv::Camera& camera, const dfv::Resources& resources) const;
protected:
	OpenGLImage img;
	std::vector<Quad> quads;
};

} /* namespace dfv */
#endif /* PROP_H_ */
