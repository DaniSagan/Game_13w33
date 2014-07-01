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
#include "Map.h"
#include "Resources.h"
//#include "Minimap.h"
#include "gui/Button.h"
#include "gui/Gui.h"

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

	void Initialize();
	void Run();
	void Update();
	void HandleInput();
	void Draw();
	void InitOpenGL();

	bool ExecuteCommand(std::string cmd);

	void createSelectedShapes();
	void drawSelection(sf::RenderWindow& window) const;

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

	std::vector<std::string> commands;
	std::vector<sf::Vector2u> selected_tiles;
	std::vector<sf::ConvexShape> selected_shapes;

	sf::Vector2u select_from;
	sf::Vector2u select_to;
};

} /* namespace dfv */
#endif /* APP_H_ */
