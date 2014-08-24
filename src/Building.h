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
