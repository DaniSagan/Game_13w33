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

 * Multitext.h
 *
 *  Created on: Sep 4, 2014
 *      Author: daniel
 */

#ifndef MULTITEXT_H_
#define MULTITEXT_H_

#include "Component.h"
#include "Text.h"

namespace dfv
{

class Multitext: public Component
{
public:
	Multitext(Component* lp_parent, int id=-1);
	virtual ~Multitext();

	enum Alignment
	{
		LEFT,
		CENTER,
		RIGHT
	};

	virtual void draw(sf::RenderWindow& window, const Assets& assets) const;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual GuiRect getRect() const;

	sf::Vector2f size;
	sf::Color bg_color;
	sf::Color txt_color;
	float txt_size;
	//std::string text;
	bool visible;
	std::vector<std::string> lines;
	float interline_space;
	Alignment text_alignment;
	float margin;

protected:

};

} /* namespace dfv */

#endif /* MULTITEXT_H_ */
