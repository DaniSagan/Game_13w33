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
#include <map>
#include "../Resources.h"
#include "../Camera.h"
#include "../Utils.h"
#include "Quad.h"

namespace dfv {

class Prop
{
public:
	Prop();
	virtual ~Prop();
	virtual void create(const std::vector<sf::Vector3f>& tile_vertices);
	virtual void draw(const dfv::Camera& camera, const dfv::Resources& resources) const;

	enum Type
	{
		NONE = 0,
		TREE,
		BOULDER
	};

	virtual Type getType() const;
	static string asString(Type type);
	static Type fromString(const string& str);

	static map<string, Type> strType;

protected:
	//OpenGLImage img;
	std::vector<Quad> quads;
};

} /* namespace dfv */
#endif /* PROP_H_ */
