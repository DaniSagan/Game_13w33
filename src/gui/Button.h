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

	void SetSize(const sf::Vector2u& size);
	void SetPosition(const sf::Vector2i& position);
	void SetImage(const sf::Image& image);
	void SetCommand(const std::string& command);

	void Draw(sf::RenderWindow& window) const;
	void HandleInput(std::vector<std::string>& command_list, const sf::Event& event);
	bool Contains(const sf::Vector2i& pos) const;
	bool LoadImage(const std::string& filename);

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
