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

 * Structure.h
 *
 *  Created on: Aug 22, 2014
 *      Author: daniel
 */

#ifndef STRUCTURE_H_
#define STRUCTURE_H_

#include <SFML/Graphics.hpp>
#include "Model.h"

namespace dfv
{

class Structure
{
public:
	Structure();
	virtual ~Structure();

	void setModel(const Model & model);
	void drawBox() const;
	void drawOutline() const;
private:
	Model model;
};

} /* namespace dfv */

#endif /* STRUCTURE_H_ */
