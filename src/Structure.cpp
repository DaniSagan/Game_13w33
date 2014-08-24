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

 * Structure.cpp
 *
 *  Created on: Aug 22, 2014
 *      Author: daniel
 */

#include "Structure.h"

namespace dfv
{

Structure::Structure()
{
	// TODO Auto-generated constructor stub

}

Structure::~Structure()
{
	// TODO Auto-generated destructor stub
}

void Structure::setModel(const Model& model)
{
	this->model = model;
}

void Structure::drawBox() const
{
	this->model.drawBox();
}

void Structure::drawOutline() const
{
	this->model.drawOutlines();
}

} /* namespace dfv */
