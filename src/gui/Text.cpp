/*
 * Text.cpp
 *
 *  Created on: Aug 28, 2014
 *      Author: daniel
 */

#include "Text.h"

namespace dfv
{

Text::Text(Component* lp_parent, int id):
	Component(lp_parent, id),
	bg_color(sf::Color(0, 0, 0, 0)),
	txt_color(sf::Color::White),
	txt_size(10.f),
	visible(true)

{

}

Text::~Text()
{
	// TODO Auto-generated destructor stub
}

void Text::draw(sf::RenderWindow& window, const Assets& assets) const
{
	if(!this->visible)
	{
		return;
	}

	sf::Text text(this->text, assets.font, this->txt_size);

	text.setColor(this->txt_color);

	sf::RectangleShape rect;
	rect.setSize(this->size);
	sf::FloatRect txt_rect = text.getLocalBounds();
	//rect.setSize(sf::Vector2f(txt_rect.width+2.f*margin, txt_rect.height+2.f*margin));
	rect.setFillColor(this->bg_color);
	rect.setPosition(this->getAbsPosition());
	sf::Vector2f text_position = this->getAbsPosition() + sf::Vector2f((this->size.x - txt_rect.width) / 2.0, (this->size.y - txt_rect.height) / 2.0 - txt_rect.top);
	text.setPosition(floor(text_position.x), floor(text_position.y));

	window.draw(rect);
	window.draw(text);

}

void Text::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if(!this->visible)
	{
		return;
	}

	sf::Text text(this->text, assetsInstance.font, this->txt_size);

	text.setColor(this->txt_color);

	sf::RectangleShape rect;
	rect.setSize(this->size);
	sf::FloatRect txt_rect = text.getLocalBounds();
	//rect.setSize(sf::Vector2f(txt_rect.width+2.f*margin, txt_rect.height+2.f*margin));
	rect.setFillColor(this->bg_color);
	rect.setPosition(this->getAbsPosition());
	sf::Vector2f text_position = this->getAbsPosition() + sf::Vector2f((this->size.x - txt_rect.width) / 2.0, (this->size.y - txt_rect.height) / 2.0 - txt_rect.top);
	text.setPosition(floor(text_position.x), floor(text_position.y));

	target.draw(rect);
	target.draw(text);
	for(Component* lp_component: this->lp_children)
	{
		target.draw(*lp_component);
	}
}

GuiRect Text::getRect() const
{
	return GuiRect(this->getAbsPosition().x,
				   this->getAbsPosition().y,
				   this->getAbsPosition().x + this->size.x,
				   this->getAbsPosition().y + this->size.y);
}

} /* namespace dfv */
