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

 * Picture.h
 *
 *  Created on: Aug 31, 2014
 *      Author: daniel
 */

#ifndef PICTURE_H_
#define PICTURE_H_

#include "Component.h"

namespace dfv
{

class Picture: public Component
{
public:
	Picture(Component* parent, int id=-1);
	virtual ~Picture();

	virtual void draw(sf::RenderWindow& window, const Assets& assets) const;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	bool loadFromFile(std::string filename);

	bool visible;
protected:
	sf::Texture texture;
};

} /* namespace dfv */

#endif /* PICTURE_H_ */
