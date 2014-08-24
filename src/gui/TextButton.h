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

 * TextButton.h
 *
 *  Created on: Jun 30, 2014
 *      Author: daniel
 */

#ifndef TEXTBUTTON_H_
#define TEXTBUTTON_H_

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>

namespace dfv
{

class TextButton
{
public:
	enum State
	{
		Normal,
		Over
	};

	TextButton();
	virtual ~TextButton();

	//void onClick(std::vector<std::string>& commands);
	void onClick(std::string& command);
	void onDraw(sf::RenderWindow& window, const sf::Font& font) const;
	//void handleInput(const sf::Event& event, std::vector<std::string>& commands);
	void handleInput(const sf::Event& event, std::string& command);

	void setVisible(bool value);
	void setText(std::string text);
	void setCommand(std::string command);
	void setPosition(sf::Vector2f position);

	bool contains(float x, float y) const;

protected:
	bool visible;
	std::string text;
	std::string command;
	sf::Vector2f position;
	sf::Vector2f size;
	State state;
};

} /* namespace dfv */
#endif /* TEXTBUTTON_H_ */
