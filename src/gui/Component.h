/*
 * Component.h
 *
 *  Created on: Aug 28, 2014
 *      Author: daniel
 */

#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <SFML/Graphics.hpp>
#include "Assets.h"
#include "../Utils.h"

namespace dfv
{

class Component
{
public:
	Component(Component* parent);
	virtual ~Component();

	virtual void draw(sf::RenderWindow& window, const Assets& assets) const;
	virtual std::string& handleInput(std::string& cmd, sf::Event& event);

	void addComponent(Component* component);

protected:
	Component* lp_parent;
	std::vector<Component*> lp_children;

};

} /* namespace dfv */

#endif /* COMPONENT_H_ */
