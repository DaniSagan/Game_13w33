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

 * Tree.h
 *
 *  Created on: Jun 23, 2014
 *      Author: daniel
 */

#ifndef TREE_H_
#define TREE_H_

#include "Prop.h"

#include <SFML/OpenGL.hpp>

namespace dfv {

class Tree: public Prop
{
public:
	Tree();
	virtual ~Tree();
	void create(const std::vector<sf::Vector3f>& tile_vertices);
	void draw(const Camera& camera, const Resources& resources) const;
	void drawQuad(const unsigned int index, const dfv::Resources& resources) const;
protected:
	std::vector<Quad> quads;
	OpenGLImage *lp_img;
	unsigned int type;
};

} /* namespace dfv */
#endif /* TREE_H_ */
