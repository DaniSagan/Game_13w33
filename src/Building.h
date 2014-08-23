/*
 * Building.h
 *
 *  Created on: Aug 12, 2013
 *      Author: daniel
 */

#ifndef BUILDING_H_
#define BUILDING_H_

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <vector>
#include "Model.h"

namespace dfv
{

class Building
{
public:
	Building();
	virtual ~Building();

	void create(const std::vector<sf::Vector3f>& base_pos, float height);
	void setColor(const sf::Color& color);
	sf::Color getColor() const;
	void draw(const bool draw_floors) const;
	float getHeight() const;

	void drawBox() const;
	void drawOutline() const;
	void drawFloors() const;

	sf::Vector3f getColor3f() const;

private:
	std::vector<sf::Vector3f> base_pos;
	std::vector<sf::Vector3f> roof_pos;
	std::vector<sf::Vector3f> colors;
	std::vector<sf::Vector2f> floor_pos;
	std::vector<float> floor_heights;
	float height;
	Model model;
};

} /* namespace dfv */
#endif /* BUILDING_H_ */
