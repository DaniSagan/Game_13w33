/*
 * Button.h
 *
 *  Created on: Aug 20, 2013
 *      Author: daniel
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include <SFML/Graphics.hpp>
#include "../Utils.h"

namespace dfv
{

class Button
{
public:
	Button();
	Button(const std::string& image_file, const sf::Vector2f& position);
	virtual ~Button();

	void setSize(const sf::Vector2u& size);
	void setPosition(const sf::Vector2i& position);
	void setImage(const sf::Image& image);
	void setCommand(const std::string& command);

	void draw(sf::RenderWindow& window) const;
	void handleInput(std::vector<std::string>& command_list, const sf::Event& event);
	bool contains(const sf::Vector2i& pos) const;
	bool loadImage(const std::string& filename);

private:
	sf::Vector2u size;
	sf::Vector2f position;
	std::string command;
	sf::Image image;
	sf::Texture texture;
	//sf::Sprite sprite;
};

} /* namespace dfv */
#endif /* BUTTON_H_ */
