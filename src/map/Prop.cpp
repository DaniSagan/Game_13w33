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

 * Prop.cpp
 *
 *  Created on: Jun 23, 2014
 *      Author: daniel
 */

#include "Prop.h"

namespace dfv
{

map<string, Prop::Type> Prop::strType = {
		{"none", NONE},
		{"tree", TREE},
		{"boulder", BOULDER}
};

Prop::Prop()
{
	// TODO Auto-generated constructor stub

}

Prop::~Prop()
{
	// TODO Auto-generated destructor stub
}

void Prop::create(const std::vector<sf::Vector3f>& tile_vertices)
{

}

void Prop::draw(const dfv::Camera& camera, const dfv::Resources& resources) const
{

}

Prop::Type Prop::getType() const
{
	return Prop::NONE;
}

string Prop::asString(Prop::Type type)
{
	switch(type)
	{
	case Prop::NONE: 	return "none"; 		break;
	case Prop::TREE: 	return "tree"; 		break;
	case Prop::BOULDER: return "boulder"; 	break;
	default: 			return "none"; 		break;
	}
}

Prop::Type Prop::fromString(const string& str)
{
	if(Prop::strType.find(str) != Prop::strType.end())
	{
		return Prop::strType.at(str);
	}
	else
	{
		return Prop::NONE;
	}
}

} /* namespace dfv */
