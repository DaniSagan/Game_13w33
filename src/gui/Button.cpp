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

 * Button.cpp
 *
 *  Created on: Aug 20, 2013
 *      Author: daniel
 */

#include "Button.h"

namespace dfv
{

Button::Button():
		size(sf::Vector2i(32, 32)),
		position(sf::Vector2i(0, 0)),
		command(std::string("button"))
{
	// TODO Auto-generated constructor stub

}

Button::Button(const std::string& image_file, const sf::Vector2f& position)
{
	this->image.loadFromFile(image_file);
	this->texture.loadFromFile(image_file);
	this->position = position;
	this->size = this->image.getSize();
	//this->sprite.setTexture(this->texture, true);
	//this->sprite.setPosition(position);
}


Button::~Button()
{
	// TODO Auto-generated destructor stub
}

void Button::setSize(const sf::Vector2u& size)
{
	this->size = size;
}

void Button::setPosition(const sf::Vector2i& position)
{
	//this->position = position;
}

void Button::setImage(const sf::Image& image)
{
	//this->image = image;
	this->texture.loadFromImage(this->image);
	//this->sprite.setTexture(texture, true);
	//this->sprite.setPosition(this->position.x, this->position.y);
}

void Button::setCommand(const std::string& command)
{
	this->command = command;
}

void Button::draw(sf::RenderWindow& window) const
{
	sf::Sprite sprite;
	sprite.setTexture(this->texture);
	sprite.setPosition(this->position);
	//sf::Texture texture;
	//texture.update(this->image);
	//sprite.setTexture(texture);
	//sprite.SetSubRect(sf::IntRect(0, 0, this->size.x, this->size.y));
	//sprite.resize(this->size.x, this->size.y);
	//sprite.setPosition(this->position.x, this->position.y);

	window.draw(sprite);
}

void Button::handleInput(std::vector<std::string>& command_list, const sf::Event& event)
{
	if(event.type == sf::Event::MouseButtonPressed &&
			event.mouseButton.button == sf::Mouse::Left)
	{
		if(this->contains(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)))
		{
			command_list.push_back(this->command);
		}
	}
}

bool Button::contains(const sf::Vector2i& pos) const
{
	dfv::IntRect rect(
			this->position.x,
			this->position.y,
			this->position.x + this->size.x,
			this->position.y + this->size.y);

	return dfv::Utils::rectContains(rect, sf::Vector2i(pos.x, pos.y));
}

bool Button::loadImage(const std::string& filename)
{
	if(this->image.loadFromFile(filename) == false) return false;
	else
	{
		this->setImage(this->image);
		return true;
	}
}

} /* namespace dfv */
