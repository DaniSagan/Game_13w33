/*
 * Multitext.cpp
 *
 *  Created on: Sep 4, 2014
 *      Author: daniel
 */

#include "Multitext.h"

namespace dfv
{

Multitext::Multitext(Component* lp_parent, int id):
		Component(lp_parent, id),
		bg_color(sf::Color(0, 0, 0, 0)),
		txt_color(sf::Color::White),
		visible(true),
		txt_size(12.f),
		interline_space(0.f),
		text_alignment(LEFT),
		margin(5.f)
{
}

Multitext::~Multitext()
{
}

void Multitext::draw(sf::RenderWindow& window, const Assets& assets) const
{
	if(!this->visible)
	{
		return;
	}

	std::vector<sf::Text> txts(this->lines.size());
	int txt_height = 0;
	for(std::size_t i = 0; i < this->lines.size(); i++)
	{
		txts.at(i) = sf::Text(this->lines.at(i), assets.font, this->txt_size);
		txts.at(i).setColor(this->txt_color);
		float xpos = 0.f;
		if(this->text_alignment == LEFT)
		{
			xpos = this->margin;
		}
		else if(this->text_alignment == CENTER)
		{
			xpos = (this->size.x - txts.at(i).getLocalBounds().width)/2.f;
		}
		else if(this->text_alignment == RIGHT)
		{
			xpos = this->size.x - txts.at(i).getLocalBounds().width - this->margin;
		}

		txts.at(i).setPosition(xpos, -txts.at(i).getLocalBounds().top);
		if(i >= 1)
		{
			/*txts.at(i).setPosition(txts.at(i-1).getLocalBounds().height+txts.at(i-1).getLocalBounds().top + this->interline_space,
								   (this->size.x-txts.at(i).getLocalBounds().width)/2.f - txts.at(i).getLocalBounds().top);*/
			float last_bottom = txts.at(i-1).getGlobalBounds().top + txts.at(i-1).getGlobalBounds().height;
			txts.at(i).move(0.f, last_bottom + this->interline_space);
		}
		txt_height += txts.at(i).getLocalBounds().height;
	}

	int txt_block_height = txt_height + this->interline_space * (this->lines.size() - 1);
	for(std::size_t i = 0; i < txts.size(); i++)
	{
		txts.at(i).move(this->getAbsPosition() + sf::Vector2f(0.f, (this->size.y-txt_block_height)/2.f));
		txts.at(i).setPosition(floor(txts.at(i).getPosition().x), floor(txts.at(i).getPosition().y));
	}

	sf::RectangleShape rect;
	rect.setSize(this->size);
	rect.setFillColor(this->bg_color);
	rect.setPosition(this->getAbsPosition());

	window.draw(rect);
	for(const sf::Text& text: txts)
	{
		window.draw(text);
	}
}

GuiRect Multitext::getRect() const
{
	return GuiRect(this->getAbsPosition().x,
				   this->getAbsPosition().y,
				   this->getAbsPosition().x + this->size.x,
				   this->getAbsPosition().y + this->size.y);
}

}
/* namespace dfv */
