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

 * MenuButton.cpp
 *
 *  Created on: Dec 29, 2014
 *      Author: daniel
 */

#include "MenuButton.h"

namespace dfv
{

MenuButton::MenuButton(Component* parent, int id):
		Component(parent, id), visible(true), radius(16.f), state(NORMAL)
{
	// TODO Auto-generated constructor stub

}

MenuButton::~MenuButton()
{
	// TODO Auto-generated destructor stub
}

void MenuButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if(!this->visible)
	{
		return;
	}
	sf::Sprite sprite(this->texture);
	sprite.setPosition(this->getAbsPosition() - sf::Vector2f(this->radius, this->radius));
	if(this->state == OVER)
	{
		sprite.setColor(sf::Color(255, 255, 255, 196));
	}
	else
	{
		sprite.setColor(sf::Color(255, 255, 255, 64));
	}
	target.draw(sprite);
}

const GuiEvent MenuButton::handleInput(const sf::Event& event)
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
		sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
		if(Utils::length(mousePos - this->getAbsPosition()) <= this->radius)
		{
			//sf::Sound sound;
			//sound.setBuffer(assetsInstance.sounds.select);
			//sound.play();
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
		sf::Vector2f mousePos(event.mouseMove.x, event.mouseMove.y);
		if(Utils::length(mousePos - this->getAbsPosition()) <= this->radius)
		{
			if(this->state != OVER) assetsInstance.sounds.over.play();
			this->state = OVER;
		}
		else
		{
			this->state = NORMAL;
		}
		return GuiEvent::noEvent;
	}
	return GuiEvent::noEvent;
}

bool MenuButton::loadTexture(const string& filename)
{
	return this->texture.loadFromFile(filename);
}

} /* namespace dfv */
