/*
 * Component.h
 *
 *  Created on: Aug 28, 2014
 *      Author: daniel
 */

#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <SFML/Graphics.hpp>
#include <map>
#include "Assets.h"
#include "../Utils.h"

namespace dfv
{

class Component
{
public:
	Component(Component* parent, int id=-1);
	virtual ~Component();

	virtual void draw(sf::RenderWindow& window, const Assets& assets) const;
	virtual std::string& handleInput(std::string& cmd, sf::Event& event);

	void addComponent(Component* component);

	void setPosition(const sf::Vector2f& position);
	sf::Vector2f getLocalPosition() const;
	sf::Vector2f getAbsPosition() const;
	Component* getById(const int id) const;

protected:
	Component* lp_parent;
	std::vector<Component*> lp_children;
	sf::Vector2f position;
	std::map<int, Component*> lp_components;

};

} /* namespace dfv */

#endif /* COMPONENT_H_ */
