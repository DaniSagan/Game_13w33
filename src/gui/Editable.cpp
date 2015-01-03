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

 * Editable.cpp
 *
 *  Created on: Sep 1, 2014
 *      Author: daniel
 */

#include "Editable.h"

namespace dfv
{

Editable::Editable(Component* parent, int id):
		Text(parent, id),
		active_color(sf::Color(0, 0, 0, 0)),
		visible(true),
		margin(5.f),
		has_focus(false),
		cursor_pos(0)
{
}

Editable::~Editable()
{
	// TODO Auto-generated destructor stub
}

void Editable::draw(sf::RenderWindow& window, const Assets& assets) const
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
	//rect.setSize(sf::Vector2f(txt_rect.width+2.f*margin, txt_rect.height+2.f*margin));
	if(this->has_focus)
	{
		rect.setFillColor(this->active_color);
	}
	else
	{
		rect.setFillColor(this->bg_color);
	}
	rect.setPosition(this->getAbsPosition());
	text.setPosition(this->getAbsPosition() + sf::Vector2f(this->margin, (this->size.y - txt_rect.height) / 2.0 - txt_rect.top));

	window.draw(rect);
	window.draw(text);
}

void Editable::draw(sf::RenderTarget& target, sf::RenderStates states) const
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
	//rect.setSize(sf::Vector2f(txt_rect.width+2.f*margin, txt_rect.height+2.f*margin));
	if(this->has_focus)
	{
		rect.setFillColor(this->active_color);
	}
	else
	{
		rect.setFillColor(this->bg_color);
	}
	rect.setPosition(this->getAbsPosition());
	text.setPosition(this->getAbsPosition() + sf::Vector2f(this->margin, (this->size.y - txt_rect.height) / 2.0 - txt_rect.top));

	target.draw(rect);
	target.draw(text);

	for(Component* lp_component: this->lp_children)
	{
		target.draw(*lp_component);
	}
}

/*
std::string& Editable::handleInput(std::string& cmd, sf::Event& event)
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
				this->has_focus = true;
			}
			else
			{
				this->has_focus = false;
			}
		}
	}
	else if(event.type == sf::Event::KeyPressed)
	{
		if(event.key.code == sf::Keyboard::BackSpace)
		{
			//this->text.pop_back();
			//this->text = this->text.substr(0, this->text.size()-1);
			if(this->text.size() > 0)
			{
				this->text.erase(this->text.end()-1);
			}
		}
		else if(event.key.code == sf::Keyboard::Return)
		{
			this->has_focus = false;
		}
	}
	else if(event.type == sf::Event::TextEntered)
	{
		// no backspaces
		if(event.text.unicode != 8)
		{
			this->text.push_back(event.text.unicode);
		}
	}
	for(Component* lp_component: this->lp_children)
	{
		lp_component->handleInput(cmd, event);
	}
	return cmd;
}*/

const GuiEvent Editable::handleInput(const sf::Event& event)
{
	if(!this->visible)
	{
		return GuiEvent::noEvent;
	}
	if(event.type == sf::Event::MouseButtonPressed)
	{
		if(event.mouseButton.button == sf::Mouse::Left)
		{
			sf::Vector2f mouse_pos(event.mouseButton.x, event.mouseButton.y);
			if(this->getRect().contains(mouse_pos))
			{
				this->has_focus = true;
			}
			else
			{
				this->has_focus = false;
			}
		}
	}
	else if(event.type == sf::Event::KeyPressed)
	{
		if(event.key.code == sf::Keyboard::BackSpace)
		{
			//this->text.pop_back();
			//this->text = this->text.substr(0, this->text.size()-1);
			if(this->text.size() > 0)
			{
				this->text.erase(this->text.end()-1);
			}
		}
		else if(event.key.code == sf::Keyboard::Return)
		{
			this->has_focus = false;
		}
	}
	else if(event.type == sf::Event::TextEntered)
	{
		// no backspaces
		if(event.text.unicode != 8)
		{
			this->text.push_back(event.text.unicode);
		}
	}
	for(Component* lp_component: this->lp_children)
	{
		lp_component->handleInput(event);
	}
	return GuiEvent::noEvent;
}

} /* namespace dfv */
