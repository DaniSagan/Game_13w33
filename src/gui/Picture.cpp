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

 * Picture.cpp
 *
 *  Created on: Aug 31, 2014
 *      Author: daniel
 */

#include "Picture.h"

namespace dfv
{

Picture::Picture(Component* parent, int id):
		Component(parent, id),
		visible(true)
{
}

Picture::~Picture()
{
	// TODO Auto-generated destructor stub
}

void Picture::draw(sf::RenderWindow& window, const Assets& assets) const
{
	if(!this->visible)
	{
		return;
	}
	sf::Sprite sprite;
	sprite.setTexture(this->texture);
	sprite.setPosition(this->getAbsPosition());
	window.draw(sprite);
	for(Component* lp_component: this->lp_children)
	{
		lp_component->draw(window, assets);
	}
}

void Picture::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if(!this->visible)
	{
		return;
	}
	sf::Sprite sprite;
	sprite.setTexture(this->texture);
	sprite.setPosition(this->getAbsPosition());
	target.draw(sprite);
	for(Component* lp_component: this->lp_children)
	{
		target.draw(*lp_component);
	}
}

bool Picture::loadFromFile(std::string filename)
{
	return this->texture.loadFromFile(filename);
}

} /* namespace dfv */
