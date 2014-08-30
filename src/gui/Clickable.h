/*
 * Clickable.h
 *
 *  Created on: Aug 30, 2014
 *      Author: daniel
 */

#ifndef CLICKABLE_H_
#define CLICKABLE_H_

#include "Text.h"

namespace dfv
{

class Clickable: public Text
{
public:
	Clickable(Component* parent);
	virtual ~Clickable();

	virtual void draw(sf::RenderWindow& window, const Assets& assets) const;
	virtual std::string& handleInput(std::string& cmd, sf::Event& event);

	sf::Color bg_over_color;
	std::string cmd;

protected:
	bool mouse_over;

};

} /* namespace dfv */

#endif /* CLICKABLE_H_ */
