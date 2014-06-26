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

void Button::SetSize(const sf::Vector2u& size)
{
	this->size = size;
}

void Button::SetPosition(const sf::Vector2i& position)
{
	//this->position = position;
}

void Button::SetImage(const sf::Image& image)
{
	//this->image = image;
	this->texture.loadFromImage(this->image);
	//this->sprite.setTexture(texture, true);
	//this->sprite.setPosition(this->position.x, this->position.y);
}

void Button::SetCommand(const std::string& command)
{
	this->command = command;
}

void Button::Draw(sf::RenderWindow& window) const
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

void Button::HandleInput(std::vector<std::string>& command_list, const sf::Event& event)
{
	if(event.type == sf::Event::MouseButtonPressed &&
			event.mouseButton.button == sf::Mouse::Left)
	{
		if(this->Contains(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)))
		{
			command_list.push_back(this->command);
		}
	}
}

bool Button::Contains(const sf::Vector2i& pos) const
{
	dfv::IntRect rect(
			this->position.x,
			this->position.y,
			this->position.x + this->size.x,
			this->position.y + this->size.y);

	return dfv::Utils::RectContains(rect, sf::Vector2i(pos.x, pos.y));
}

bool Button::LoadImage(const std::string& filename)
{
	if(this->image.loadFromFile(filename) == false) return false;
	else
	{
		this->SetImage(this->image);
		return true;
	}
}

} /* namespace dfv */
