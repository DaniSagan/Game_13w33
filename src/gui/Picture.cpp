/*
 * Picture.cpp
 *
 *  Created on: Aug 31, 2014
 *      Author: daniel
 */

#include "Picture.h"

namespace dfv
{

Picture::Picture(Component* parent, int id):
		Component(parent, id),
		visible(true)
{
}

Picture::~Picture()
{
	// TODO Auto-generated destructor stub
}

void Picture::draw(sf::RenderWindow& window, const Assets& assets) const
{
	if(!this->visible)
	{
		return;
	}
	sf::Sprite sprite;
	sprite.setTexture(this->texture);
	sprite.setPosition(this->getAbsPosition());
	window.draw(sprite);
	for(Component* lp_component: this->lp_children)
	{
		lp_component->draw(window, assets);
	}
}

void Picture::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if(!this->visible)
	{
		return;
	}
	sf::Sprite sprite;
	sprite.setTexture(this->texture);
	sprite.setPosition(this->getAbsPosition());
	target.draw(sprite);
	for(Component* lp_component: this->lp_children)
	{
		target.draw(*lp_component);
	}
}

bool Picture::loadFromFile(std::string filename)
{
	return this->texture.loadFromFile(filename);
}

} /* namespace dfv */
