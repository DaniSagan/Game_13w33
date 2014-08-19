/*
 * Cube.h
 *
 *  Created on: Aug 11, 2013
 *      Author: daniel
 */

#ifndef CUBE_H_
#define CUBE_H_

#include <SFML/Graphics.hpp>
#include "Camera.h"

namespace dfv
{

class Cube
{
public:
	Cube();
	virtual ~Cube();

	sf::Color getColor() const;
	void setColor(sf::Color color);
	const sf::Vector3f& getPosition() const;
	void setPosition(const sf::Vector3f& position);

	void draw(sf::Window& window, const dfv::Camera& camera, bool top_only = false);

private:
	sf::Vector3f position;
	sf::Color color;
	sf::Vector3f gl_color_top;
	sf::Vector3f gl_color_side_b;
	sf::Vector3f gl_color_side_d;
	sf::Vector3f gl_color_bottom;
};

} /* namespace dfv */
#endif /* CUBE_H_ */
