/*
 * Text.cpp
 *
 *  Created on: Aug 28, 2014
 *      Author: daniel
 */

#include "Text.h"

namespace dfv
{

Text::Text(Component* lp_parent):
	Component(lp_parent),
	bg_color(sf::Color(0, 0, 0, 0)),
	txt_color(sf::Color::White),
	txt_size(10.f),
	visible(true)

{
	this->lp_parent = lp_parent;
}

Text::~Text()
{
	// TODO Auto-generated destructor stub
}

void Text::draw(sf::RenderWindow& window, const Assets& assets) const
{
	if(this->visible)
	{
		sf::Text text(this->text, assets.font, this->txt_size);

		text.setColor(this->txt_color);

		sf::RectangleShape rect;
		rect.setSize(this->size);
		sf::FloatRect txt_rect = text.getLocalBounds();
		//rect.setSize(sf::Vector2f(txt_rect.width+2.f*margin, txt_rect.height+2.f*margin));
		rect.setFillColor(this->bg_color);
		rect.setPosition(this->position);
		text.setPosition(this->position + sf::Vector2f((this->size.x - txt_rect.width) / 2.0, (this->size.y - txt_rect.height) / 2.0 - txt_rect.top));

		window.draw(rect);
		window.draw(text);
	}
}

std::string& Text::handleInput(std::string& cmd, sf::Event& event)
{
	return cmd;
}

GuiRect Text::getRect() const
{
	return GuiRect(this->position.x,
				   this->position.y,
				   this->position.x + this->size.x,
				   this->position.y + this->size.y);
}

} /* namespace dfv */
