/*
 * Component.cpp
 *
 *  Created on: Aug 28, 2014
 *      Author: daniel
 */

#include "Component.h"

namespace dfv
{

Component::Component(Component* lp_parent)
{
	this->lp_parent = lp_parent;
}

Component::~Component()
{
	for(Component* lp_component: this->lp_children)
	{
		delete lp_component;
	}
}

void Component::draw(sf::RenderWindow& window, const Assets& assets) const
{
	for(Component* lp_component: this->lp_children)
	{
		lp_component->draw(window, assets);
	}
}

std::string& Component::handleInput(std::string& cmd, sf::Event& event)
{
	for(Component* lp_component: this->lp_children)
	{
		cmd = lp_component->handleInput(cmd, event);
	}
	return cmd;
}

void Component::addComponent(Component* component)
{
	this->lp_children.push_back(component);
}

} /* namespace dfv */
