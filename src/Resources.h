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

 * Resources.h
 *
 *  Created on: Aug 12, 2013
 *      Author: daniel
 */

#ifndef RESOURCES_H_
#define RESOURCES_H_

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <sstream>
#include "Utils.h"

namespace dfv
{

class Road;

class Resources
{
public:
	Resources();
	virtual ~Resources();

	bool load();

	std::vector<sf::Image> img_roads;
	std::vector<GLuint> img_roads_handles;
	GLuint img_1_handle;

	OpenGLImage img_tree;
	OpenGLImage img_tree_2;
};

} /* namespace dfv */
#endif /* RESOURCES_H_ */
