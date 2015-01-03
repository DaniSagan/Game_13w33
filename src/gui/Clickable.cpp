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

 * Clickable.cpp
 *
 *  Created on: Aug 30, 2014
 *      Author: daniel
 */

#include "Clickable.h"

namespace dfv
{

Clickable::Clickable(Component* parent, int id):
		Text(parent, id),
		bg_over_color(sf::Color(0, 0, 0, 0)),
		cmd(std::string("")),
		mouse_over(false),
		state(NORMAL)
{

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
	rect.setPosition(this->getAbsPosition());
	sf::Vector2f text_position = this->getAbsPosition() +
			sf::Vector2f((this->size.x - txt_rect.width) / 2.0,
	         	 	 	 (this->size.y - txt_rect.height) / 2.0 - txt_rect.top);
	text.setPosition(floor(text_position.x), floor(text_position.y));

	window.draw(rect);
	window.draw(text);
}

void Clickable::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if(!this->visible)
	{
		return;
	}
	sf::Text text(this->text, assetsInstance.font, this->txt_size);

	text.setColor(this->txt_color);

	sf::RectangleShape rect;
	rect.setSize(this->size);
	sf::FloatRect txt_rect = text.getLocalBounds();

	//if(this->mouse_over)
	if(this->state == OVER)
	{
		rect.setFillColor(this->bg_over_color);
	}
	else
	{
		rect.setFillColor(this->bg_color);
	}
	rect.setPosition(this->getAbsPosition());
	sf::Vector2f text_position = this->getAbsPosition() +
			sf::Vector2f((this->size.x - txt_rect.width) / 2.0,
	         	 	 	 (this->size.y - txt_rect.height) / 2.0 - txt_rect.top);
	text.setPosition(floor(text_position.x), floor(text_position.y));

	target.draw(rect);
	target.draw(text);

	for(Component* lpComponent: this->lp_children)
	{
		target.draw(*lpComponent);
	}
}

/*
std::string& Clickable::handleInput(std::string& cmd, sf::Event& event)
{
	if(!this->visible)
	{
		return cmd;
	}
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
	for(Component* lp_component: this->lp_children)
	{
		lp_component->handleInput(cmd, event);
	}
	return cmd;
}*/

const GuiEvent Clickable::handleInput(const sf::Event& event)
{
	if(!this->visible)
	{
		return GuiEvent::noEvent;
	}

	for(Component* lpComponent: this->lp_children)
	{
		GuiEvent guiEvent = lpComponent->handleInput(event);
		if(guiEvent.type != GuiEvent::None)
		{
			return guiEvent;
		}
	}

	if(event.type == sf::Event::MouseButtonPressed)
	{
		sf::Vector2f mouse_pos(event.mouseButton.x, event.mouseButton.y);
		if(this->getRect().contains(mouse_pos))
		{
			assetsInstance.sounds.select.play();
			GuiEvent guiEvent;
			guiEvent.type = GuiEvent::ButtonEvent;
			guiEvent.click.id = this->mId;
			guiEvent.click.mouseButton = event.mouseButton.button;
			return guiEvent;
		}
		else
		{
			return GuiEvent::noEvent;
		}
	}
	else if(event.type == sf::Event::MouseMoved)
	{
		sf::Vector2f mouse_pos(event.mouseMove.x, event.mouseMove.y);
		if(this->getRect().contains(mouse_pos))
		{
			this->mouse_over = true;
			if(this->state != OVER) assetsInstance.sounds.over.play();
			this->state = OVER;
		}
		else
		{
			this->mouse_over = false;
			this->state = NORMAL;
		}
		return GuiEvent::noEvent;
	}
}

} /* namespace dfv */
