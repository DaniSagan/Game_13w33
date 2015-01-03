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

 * Component.h
 *
 *  Created on: Aug 28, 2014
 *      Author: daniel
 */

#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <SFML/Graphics.hpp>
#include <map>
#include "Assets.h"
#include "../Utils.h"
#include "GuiEvent.h"

namespace dfv
{

class Component: public sf::Drawable
{
public:
	Component(Component* parent, int id=-1);
	virtual ~Component();

	virtual void draw(sf::RenderWindow& window, const Assets& assets) const;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	//virtual std::string& handleInput(std::string& cmd, sf::Event& event);
	virtual const GuiEvent handleInput(const sf::Event& event);

	void addComponent(Component* component);

	void setPosition(const sf::Vector2f& position);
	sf::Vector2f getLocalPosition() const;
	sf::Vector2f getAbsPosition() const;
	Component* getById(const int id) const;
	void clear();

protected:
	Component* lp_parent;
	int mId;
	std::vector<Component*> lp_children;
	sf::Vector2f position;
	std::map<int, Component*> lp_components;

};

} /* namespace dfv */

#endif /* COMPONENT_H_ */
