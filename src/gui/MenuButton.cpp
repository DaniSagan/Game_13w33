/*
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
