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

 * Editable.h
 *
 *  Created on: Sep 1, 2014
 *      Author: daniel
 */

#ifndef EDITABLE_H_
#define EDITABLE_H_

#include "Text.h"

namespace dfv
{

class Editable: public Text
{
public:
	Editable(Component* parent, int id=-1);
	virtual ~Editable();

	virtual void draw(sf::RenderWindow& window, const Assets& assets) const;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	//virtual std::string& handleInput(std::string& cmd, sf::Event& event);
	virtual const GuiEvent handleInput(const sf::Event& event);

	sf::Color active_color;
	bool visible;
	float margin;
	bool has_focus;
	int cursor_pos;
protected:

};

} /* namespace dfv */

#endif /* EDITABLE_H_ */
