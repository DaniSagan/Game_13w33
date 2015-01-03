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

 * Resources.cpp
 *
 *  Created on: Aug 12, 2013
 *      Author: daniel
 */

#include "Resources.h"
#include "map/Road.h"

namespace dfv
{

Resources::Resources()
{

}

Resources::~Resources()
{
	// TODO Auto-generated destructor stub
}

bool Resources::load()
{
	this->imgRoads.resize(Road::id_count);
	this->imgRoadsHandles.resize(Road::id_count);
	this->imgRoadsHandles.at(Road::straight) = Utils::loadGLTexture("res/img/road/straight.png");
	this->imgRoadsHandles.at(Road::cross) = Utils::loadGLTexture("res/img/road/x-cross.png");
	this->imgRoadsHandles.at(Road::curve) = Utils::loadGLTexture("res/img/road/diagonal.png");
	this->imgRoadsHandles.at(Road::tcross) = Utils::loadGLTexture("res/img/road/t-cross.png");
	this->imgRoadsHandles.at(Road::roundabout_center) = Utils::loadGLTexture("res/img/road/roundabout1/center.png");
	this->imgRoadsHandles.at(Road::roundabout_side) = Utils::loadGLTexture("res/img/road/roundabout1/side.png");
	this->imgRoadsHandles.at(Road::roundabout_corner) = Utils::loadGLTexture("res/img/road/roundabout1/corner.png");
	this->imgRoadsHandles.at(Road::roundabout_exit) = Utils::loadGLTexture("res/img/road/roundabout1/exit.png");

	this->imgTree2.loadFromFile("res/prop/tree-1.png");
	this->imgTree.loadFromFile("res/prop/tree-2.png");

	return true;
}


} /* namespace dfv */
