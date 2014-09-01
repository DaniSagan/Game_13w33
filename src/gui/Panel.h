/*
 * Panel.h
 *
 *  Created on: Aug 31, 2014
 *      Author: daniel
 */

#ifndef PANEL_H_
#define PANEL_H_

#include "Component.h"

namespace dfv
{

class Panel: public Component
{
public:
	Panel(Component* lp_parent, int id=-1);
	virtual ~Panel();

	virtual void draw(sf::RenderWindow& window, const Assets& assets) const;
	virtual std::string& handleInput(std::string& cmd, sf::Event& event);

	sf::Vector2f size;
	sf::Color color;
	bool visible;
};

} /* namespace dfv */

#endif /* PANEL_H_ */
