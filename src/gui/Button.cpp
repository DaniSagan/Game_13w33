/*
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
		command(std::string("button")),
		image(sf::Image(32, 32, 0))
{
	// TODO Auto-generated constructor stub

}

Button::~Button()
{
	// TODO Auto-generated destructor stub
}

void Button::SetSize(const sf::Vector2i& size)
{
	this->size = size;
}

void Button::SetPosition(const sf::Vector2i& position)
{
	this->position = position;
}

void Button::SetImage(const sf::Image& image)
{
	this->image = image;
}

void Button::SetCommand(const std::string& command)
{
	this->command = command;
}

void Button::Draw(sf::RenderWindow& window) const
{
	sf::Sprite sprite;
	sprite.SetImage(this->image);
	//sprite.SetSubRect(sf::IntRect(0, 0, this->size.x, this->size.y));
	sprite.Resize(this->size.x, this->size.y);
	sprite.SetPosition(this->position.x, this->position.y);

	window.Draw(sprite);
}

void Button::HandleInput(std::vector<std::string>& command_list, const sf::Event& event)
{
	if(event.Type == sf::Event::MouseButtonPressed &&
			event.MouseButton.Button == sf::Mouse::Left)
	{
		if(this->Contains(sf::Vector2i(event.MouseButton.X, event.MouseButton.Y)))
		{
			command_list.push_back(this->command);
		}
	}
}

bool Button::Contains(const sf::Vector2i& pos) const
{
	sf::IntRect rect(
			this->position.x,
			this->position.y,
			this->position.x + this->size.x,
			this->position.y + this->size.y);

	return rect.Contains(pos.x, pos.y);
}

} /* namespace dfv */
