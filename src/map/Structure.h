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
#include <utility>
#include <vector>
#include "Model.h"
#include "../Serializer.h"

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

	float getModelHeight() const;
	unsigned int getModelFloorCount() const;

	friend string osString(size_t level, const string& name, const Structure& structure);
	friend string osString(size_t level, const string& name, const vector<Structure*>& lpStructures);
	friend bool isRead(Serializer& ser, Structure& structure);
	friend bool isRead(Serializer& ser, vector<Structure*>& lpStructures);

private:
	Model model;
};

} /* namespace dfv */

#endif /* STRUCTURE_H_ */
