/*
 * TextButton.h
 *
 *  Created on: Jun 30, 2014
 *      Author: daniel
 */

#ifndef TEXTBUTTON_H_
#define TEXTBUTTON_H_

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>

namespace dfv
{

class TextButton
{
public:
	enum State
	{
		Normal,
		Over
	};

	TextButton();
	virtual ~TextButton();

	void onClick(std::vector<std::string>& commands);
	void onDraw(sf::RenderWindow& window, const sf::Font& font) const;
	void handleInput(const sf::Event& event, std::vector<std::string>& commands);

	void setVisible(bool value);
	void setText(std::string text);
	void setCommand(std::string command);
	void setPosition(sf::Vector2f position);

	bool contains(float x, float y) const;

protected:
	bool visible;
	std::string text;
	std::string command;
	sf::Vector2f position;
	sf::Vector2f size;
	State state;
};

} /* namespace dfv */
#endif /* TEXTBUTTON_H_ */
