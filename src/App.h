/*
 *  Hyperopolis: Megacities building game.
    Copyright (C) 2014  Daniel Fernández Villanueva

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

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
#include <thread>
#include "Map.h"
#include "Resources.h"
//#include "Minimap.h"
#include "gui/Button.h"
#include "gui/Gui.h"
#include "Utils.h"
#include "CmdServer.h"

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
	CmdServer cmd_server;
};

} /* namespace dfv */
#endif /* APP_H_ */
