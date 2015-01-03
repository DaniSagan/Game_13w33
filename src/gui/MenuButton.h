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

 * MenuButton.h
 *
 *  Created on: Dec 29, 2014
 *      Author: daniel
 */

#ifndef MENUBUTTON_H_
#define MENUBUTTON_H_

#include "Component.h"
#include <string>

namespace dfv
{

class MenuButton: public Component
{
public:
	MenuButton(Component* parent, int id=-1);
	virtual ~MenuButton();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual const GuiEvent handleInput(const sf::Event& event);
	bool loadTexture(const string& filename);

	enum State
	{
		NORMAL,
		OVER
	};
protected:
	sf::Texture texture;
	bool visible;
	float radius;
	sf::Vector2f position;
	State state;
};

} /* namespace dfv */

#endif /* MENUBUTTON_H_ */
