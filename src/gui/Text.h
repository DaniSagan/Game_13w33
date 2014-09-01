/*
 * Text.h
 *
 *  Created on: Aug 28, 2014
 *      Author: daniel
 */

#ifndef TEXT_H_
#define TEXT_H_

#include "Component.h"

namespace dfv
{

class Text: public Component
{
public:
	Text(Component* lp_parent, int id=-1);
	virtual ~Text();

	virtual void draw(sf::RenderWindow& window, const Assets& assets) const;
	//virtual std::string& handleInput(std::string& cmd, sf::Event& event);
	virtual GuiRect getRect() const;

	sf::Vector2f size;
	sf::Color bg_color;
	sf::Color txt_color;
	float txt_size;
	std::string text;
	bool visible;
	//float margin;
protected:
	//sf::Text _text;

};

} /* namespace dfv */

#endif /* TEXT_H_ */
