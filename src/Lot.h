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

 * Lot.h
 *
 *  Created on: Jul 3, 2014
 *      Author: daniel
 */

#ifndef LOT_H_
#define LOT_H_

#include <SFML/Graphics.hpp>
#include "Tile.h"

namespace dfv
{

class Lot
{
public:
	Lot();
	virtual ~Lot();

private:
	std::vector<Tile*> lp_tiles;
};

} /* namespace dfv */
#endif /* LOT_H_ */
