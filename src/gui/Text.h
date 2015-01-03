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

 * Text.h
 *
 *  Created on: Aug 28, 2014
 *      Author: daniel
 */

#ifndef TEXT_H_
#define TEXT_H_

#include "Component.h"

namespace dfv
{

class Text: public Component
{
public:
	Text(Component* lp_parent, int id=-1);
	virtual ~Text();

	virtual void draw(sf::RenderWindow& window, const Assets& assets) const;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	//virtual std::string& handleInput(std::string& cmd, sf::Event& event);
	virtual GuiRect getRect() const;

	sf::Vector2f size;
	sf::Color bg_color;
	sf::Color txt_color;
	float txt_size;
	std::string text;
	bool visible;
	//float margin;
protected:
	//sf::Text _text;

};

} /* namespace dfv */

#endif /* TEXT_H_ */
