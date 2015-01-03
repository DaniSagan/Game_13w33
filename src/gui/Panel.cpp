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

 * Panel.cpp
 *
 *  Created on: Aug 31, 2014
 *      Author: daniel
 */

#include "Panel.h"

namespace dfv
{

Panel::Panel(Component* lp_parent, int id):
		Component(lp_parent, id),
		visible(true)
{
}

Panel::~Panel()
{
	// TODO Auto-generated destructor stub
}

void Panel::draw(sf::RenderWindow& window, const Assets& assets) const
{
	if(!this->visible)
	{
		return;
	}
	sf::RectangleShape rect;
	rect.setSize(this->size);
	rect.setFillColor(this->color);
	rect.setPosition(this->getAbsPosition());
	window.draw(rect);
	for(Component* lp_component: this->lp_children)
	{
		lp_component->draw(window, assets);
	}
}

void Panel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if(!this->visible)
	{
		return;
	}
	sf::RectangleShape rect;
	rect.setSize(this->size);
	rect.setFillColor(this->color);
	rect.setPosition(this->getAbsPosition());
	target.draw(rect);
	for(Component* lp_component: this->lp_children)
	{
		target.draw(*lp_component);
	}
}

/*
std::string& Panel::handleInput(std::string& cmd, sf::Event& event)
{
	for(Component* lp_component: this->lp_children)
	{
		cmd = lp_component->handleInput(cmd, event);
	}
	return cmd;
}*/

} /* namespace dfv */
