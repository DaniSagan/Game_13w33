/*
 * Component.cpp
 *
 *  Created on: Aug 28, 2014
 *      Author: daniel
 */

#include "Component.h"

namespace dfv
{

Component::Component(Component* lp_parent, int id):
		position({0.f, 0.f})
{
	this->lp_parent = lp_parent;
	if(lp_parent != nullptr)
	{
		this->lp_parent->addComponent(this);
	}
	if(id >= 0)
	{
		if(lp_parent == nullptr)
		{
			this->lp_components[id] = this;
		}
		else
		{
			Component* lp_temp_comp = lp_parent;
			while(lp_temp_comp ->lp_parent != nullptr)
			{
				lp_temp_comp = lp_parent->lp_parent;
			}
			lp_temp_comp->lp_components[id] = this;
		}
	}
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

void Component::addComponent(Component* lp_component)
{
	this->lp_children.push_back(lp_component);
}

void Component::setPosition(const sf::Vector2f& position)
{
	this->position = position;
}

sf::Vector2f Component::getLocalPosition() const
{
	return this->position;
}

sf::Vector2f Component::getAbsPosition() const
{
	if(this->lp_parent == nullptr)
	{
		return this->position;
	}
	else
	{
		return this->position + this->lp_parent->getAbsPosition();
	}
}

Component* Component::getById(const int id) const
{
	if(this->lp_parent == nullptr)
	{
		return this->lp_components.at(id);
	}
	else
	{
		Component* lp_temp = this->lp_parent;
		while(lp_temp->lp_parent != nullptr)
		{
			lp_temp = lp_temp->lp_parent;
		}
		return lp_temp->lp_components.at(id);
	}
}

} /* namespace dfv */


