/*
 * App.h
 *
 *  Created on: Aug 11, 2013
 *      Author: daniel
 */

#ifndef APP_H_
#define APP_H_

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>
#include <cmath>
#include <random>
#include "Map.h"
#include "Resources.h"
//#include "Minimap.h"
#include "gui/Button.h"
#include "gui/Gui.h"
#include "Utils.h"

namespace dfv
{

class App
{
public:
	App();
	virtual ~App();

	enum MovingMode
	{
		Free,
		Walking,
		Driving
	};

	void initialize();
	void run();
	void update();
	void handleInput();
	void draw();
	void initOpenGL();

	bool executeCommand(std::string cmd);

	void createSelectedShapes();
	void drawSelection(sf::RenderWindow& window) const;
	sf::Vector2i getCameraTile() const;
	void generateLists();

	bool test();

private:
	sf::RenderWindow window;
	sf::Clock clock;
	dfv::Camera camera;
	dfv::Map map;
	unsigned int frame;
	dfv::Resources resources;
	sf::Vector3f map_pos;
	sf::Vector2i mouse_pos;

	dfv::Button button;
	dfv::Gui gui;

	bool walking;
	unsigned int road_id;
	unsigned int road_orientation;

	float frame_time;
	MovingMode moving_mode;

	//std::vector<std::string> commands;
	std::string command;
	std::vector<sf::Vector2i> selected_tiles;
	std::vector<sf::ConvexShape> selected_shapes;

	sf::Vector2i select_from;
	sf::Vector2i select_to;
};

} /* namespace dfv */
#endif /* APP_H_ */
