/*
 * Multitext.h
 *
 *  Created on: Sep 4, 2014
 *      Author: daniel
 */

#ifndef MULTITEXT_H_
#define MULTITEXT_H_

#include "Component.h"
#include "Text.h"

namespace dfv
{

class Multitext: public Component
{
public:
	Multitext(Component* lp_parent, int id=-1);
	virtual ~Multitext();

	enum Alignment
	{
		LEFT,
		CENTER,
		RIGHT
	};

	virtual void draw(sf::RenderWindow& window, const Assets& assets) const;
	virtual GuiRect getRect() const;

	sf::Vector2f size;
	sf::Color bg_color;
	sf::Color txt_color;
	float txt_size;
	//std::string text;
	bool visible;
	std::vector<std::string> lines;
	float interline_space;
	Alignment text_alignment;
	float margin;

protected:

};

} /* namespace dfv */

#endif /* MULTITEXT_H_ */
