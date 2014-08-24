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
