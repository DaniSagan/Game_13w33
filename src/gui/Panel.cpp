/*
 * Panel.cpp
 *
 *  Created on: Aug 31, 2014
 *      Author: daniel
 */

#include "Panel.h"

namespace dfv
{

Panel::Panel(Component* lp_parent, int id):
		Component(lp_parent, id),
		visible(true)
{
}

Panel::~Panel()
{
	// TODO Auto-generated destructor stub
}

void Panel::draw(sf::RenderWindow& window, const Assets& assets) const
{
	if(!this->visible)
	{
		return;
	}
	sf::RectangleShape rect;
	rect.setSize(this->size);
	rect.setFillColor(this->color);
	rect.setPosition(this->getAbsPosition());
	window.draw(rect);
	for(Component* lp_component: this->lp_children)
	{
		lp_component->draw(window, assets);
	}
}

std::string& Panel::handleInput(std::string& cmd, sf::Event& event)
{
	for(Component* lp_component: this->lp_children)
	{
		cmd = lp_component->handleInput(cmd, event);
	}
	return cmd;
}

} /* namespace dfv */
