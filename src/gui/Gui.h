/*
 * Gui.h
 *
 *  Created on: Aug 20, 2013
 *      Author: daniel
 */

#ifndef GUI_H_
#define GUI_H_

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <sstream>
#include <list>
#include "Minimap.h"
#include "Button.h"
#include "TextButton.h"

namespace dfv
{

class Gui
{
public:
	Gui();
	virtual ~Gui();

	enum Tool
	{
		none = 0,
		road,
		select,
		copy
	};

	void draw(sf::RenderWindow& window, const Camera& camera) const;
	void setFps(float fps);
	void setQuadrant(unsigned int quadrant);
	void setMapPos(const sf::Vector3f& mapPos);
	void setSelectedTileVertices(const std::vector<sf::Vector2f>& selected_vertices);
	void setSelectedShapes(std::vector<sf::ConvexShape>& shapes);

	std::vector<std::string> handleInput(const sf::Event& event, std::vector<std::string>& commands);
	void handleInput(const sf::Event& event, std::string& command);
	std::vector<std::string>& handleButtonInput(const sf::Event& event, std::vector<std::string>& commands);
	void update(const Map& map, const sf::Vector2f& position);

	void drawShapes(sf::RenderWindow& window) const;

private:

	float fps;
	unsigned int quadrant;
	Minimap minimap;
	sf::Vector3f map_pos;
	std::vector<sf::Vector2f> selected_tile_vertices;
	sf::IntRect selected_tiles;

	Tool selected_tool;
	std::list<Button> button_list;
	sf::Image toolbar_img;
	sf::Font font;
	std::vector<sf::ConvexShape> selected_shapes;

	std::vector<TextButton> text_button_list;
	//TextButton text_button;
};

} /* namespace dfv */
#endif /* GUI_H_ */
