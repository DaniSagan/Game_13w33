/*
 * TextButton.cpp
 *
 *  Created on: Jun 30, 2014
 *      Author: daniel
 */

#include "TextButton.h"

namespace dfv
{

TextButton::TextButton():
		visible(true), size(sf::Vector2f(192.f, 32.f)), state(Normal)
{
	// TODO Auto-generated constructor stub

}

TextButton::~TextButton()
{
	// TODO Auto-generated destructor stub
}

/*void TextButton::onClick(std::vector<std::string>& commands)
{
	commands.push_back(this->command);
}*/

void TextButton::onClick(std::string& command)
{
	command = this->command;
}

void TextButton::onDraw(sf::RenderWindow& window, const sf::Font& font) const
{
	if(this->visible)
	{
		sf::RectangleShape rect(this->size);
		if(this->state == Normal)
		{
			rect.setFillColor(sf::Color(64, 64, 64, 128));
		}
		else
		{
			rect.setFillColor(sf::Color(64, 64, 64, 192));
		}
		rect.setPosition(this->position);
		window.draw(rect);

		sf::Text text(this->text, font, 20.f);
		text.setPosition(this->position + sf::Vector2f(5.0, 4.0));
		text.setColor(sf::Color(255, 255, 255, 255));
		window.draw(text);
	}
}

/*void TextButton::handleInput(const sf::Event& event, std::vector<std::string>& commands)
{
	if(event.type == sf::Event::MouseButtonPressed &&
			event.mouseButton.button == sf::Mouse::Left)
	{
		if(this->contains(event.mouseButton.x, event.mouseButton.y))
		{
			this->onClick(commands);
		}
	}
	else if(event.type == sf::Event::MouseMoved)
	{
		if(this->contains(event.mouseMove.x, event.mouseMove.y))
		{
			this->state = Over;
		}
		else
		{
			this->state = Normal;
		}
	}
}*/

void TextButton::handleInput(const sf::Event& event, std::string& command)
{
	if(event.type == sf::Event::MouseButtonPressed &&
				event.mouseButton.button == sf::Mouse::Left)
	{
		if(this->contains(event.mouseButton.x, event.mouseButton.y))
		{
			this->onClick(command);
		}
	}
	else if(event.type == sf::Event::MouseMoved)
	{
		if(this->contains(event.mouseMove.x, event.mouseMove.y))
		{
			this->state = Over;
		}
		else
		{
			this->state = Normal;
		}
	}
}

void TextButton::setVisible(bool visible)
{
	this->visible = visible;
}

void TextButton::setText(std::string text)
{
	this->text = text;
}

void TextButton::setCommand(std::string command)
{
	this->command = command;
}

void TextButton::setPosition(sf::Vector2f position)
{
	this->position = position;
}

bool TextButton::contains(float x, float y) const
{
	return x >= this->position.x && x < this->position.x + this->size.x &&
		   y >= this->position.y && y < this->position.y + this->size.y;
}

} /* namespace dfv */
