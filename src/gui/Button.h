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

 * Button.h
 *
 *  Created on: Aug 20, 2013
 *      Author: daniel
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include <SFML/Graphics.hpp>
#include "../Utils.h"

namespace dfv
{

class Button
{
public:
	Button();
	Button(const std::string& image_file, const sf::Vector2f& position);
	virtual ~Button();

	void setSize(const sf::Vector2u& size);
	void setPosition(const sf::Vector2i& position);
	void setImage(const sf::Image& image);
	void setCommand(const std::string& command);

	void draw(sf::RenderWindow& window) const;
	void handleInput(std::vector<std::string>& command_list, const sf::Event& event);
	bool contains(const sf::Vector2i& pos) const;
	bool loadImage(const std::string& filename);

private:
	sf::Vector2u size;
	sf::Vector2f position;
	std::string command;
	sf::Image image;
	sf::Texture texture;
	//sf::Sprite sprite;
};

} /* namespace dfv */
#endif /* BUTTON_H_ */
