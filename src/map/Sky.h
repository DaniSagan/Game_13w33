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

 * Sky.h
 *
 *  Created on: Aug 19, 2013
 *      Author: daniel
 */

#ifndef SKY_H_
#define SKY_H_

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <vector>

namespace dfv
{

class Sky
{
public:
	Sky();
	virtual ~Sky();

	void create(float size, sf::Vector2f center, std::string filename);
	void draw() const;

private:
	float size;
	std::vector<sf::Vector3f> vertices;
	std::vector<sf::Image> images;
	std::vector<GLuint> image_handles;
	sf::Image sky_img;
};

} /* namespace dfv */
#endif /* SKY_H_ */
