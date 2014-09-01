/*
 * Editable.h
 *
 *  Created on: Sep 1, 2014
 *      Author: daniel
 */

#ifndef EDITABLE_H_
#define EDITABLE_H_

#include "Text.h"

namespace dfv
{

class Editable: public Text
{
public:
	Editable(Component* parent, int id=-1);
	virtual ~Editable();

	virtual void draw(sf::RenderWindow& window, const Assets& assets) const;
	virtual std::string& handleInput(std::string& cmd, sf::Event& event);

	sf::Color active_color;
	bool visible;
	float margin;
	bool has_focus;
	int cursor_pos;
protected:

};

} /* namespace dfv */

#endif /* EDITABLE_H_ */
