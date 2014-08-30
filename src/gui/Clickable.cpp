/*
 * Clickable.cpp
 *
 *  Created on: Aug 30, 2014
 *      Author: daniel
 */

#include "Clickable.h"

namespace dfv
{

Clickable::Clickable(Component* parent):
		Text(parent),
		bg_over_color(sf::Color(0, 0, 0, 0)),
		cmd(std::string("")),
		mouse_over(false)
{
	// TODO Auto-generated constructor stub

}

Clickable::~Clickable()
{
	// TODO Auto-generated destructor stub
}

void Clickable::draw(sf::RenderWindow& window, const Assets& assets) const
{
	if(!this->visible)
	{
		return;
	}
	sf::Text text(this->text, assets.font, this->txt_size);

	text.setColor(this->txt_color);

	sf::RectangleShape rect;
	rect.setSize(this->size);
	sf::FloatRect txt_rect = text.getLocalBounds();

	if(this->mouse_over)
	{
		rect.setFillColor(this->bg_over_color);
	}
	else
	{
		rect.setFillColor(this->bg_color);
	}
	rect.setPosition(this->position);
	text.setPosition(this->position + sf::Vector2f((this->size.x - txt_rect.width) / 2.0,
			         (this->size.y - txt_rect.height) / 2.0 - txt_rect.top));

	window.draw(rect);
	window.draw(text);
}

std::string& Clickable::handleInput(std::string& cmd, sf::Event& event)
{
	if(event.type == sf::Event::MouseButtonPressed)
	{
		if(event.mouseButton.button == sf::Mouse::Left)
		{
			sf::Vector2f mouse_pos(event.mouseButton.x, event.mouseButton.y);
			if(this->getRect().contains(mouse_pos))
			{
				cmd = this->cmd;
			}
		}
	}
	else if(event.type == sf::Event::MouseMoved)
	{
		sf::Vector2f mouse_pos(event.mouseMove.x, event.mouseMove.y);
		if(this->getRect().contains(mouse_pos))
		{
			this->mouse_over = true;
		}
		else
		{
			this->mouse_over = false;
		}
	}
	return cmd;
}

} /* namespace dfv */
