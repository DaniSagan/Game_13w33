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

 * Clickable.h
 *
 *  Created on: Aug 30, 2014
 *      Author: daniel
 */

#ifndef CLICKABLE_H_
#define CLICKABLE_H_

#include "Text.h"

namespace dfv
{

class Clickable: public Text
{
public:
	Clickable(Component* parent, int id=-1);
	virtual ~Clickable();

	virtual void draw(sf::RenderWindow& window, const Assets& assets) const;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	//virtual std::string& handleInput(std::string& cmd, sf::Event& event);
	virtual const GuiEvent handleInput(const sf::Event& event);

	sf::Color bg_over_color;
	std::string cmd;
	void (*onClick)();

	enum State
	{
		NORMAL,
		OVER
	};

protected:
	bool mouse_over;
	State state;

};

} /* namespace dfv */

#endif /* CLICKABLE_H_ */
