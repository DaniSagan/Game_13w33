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

 * PlayState.h
 *
 *  Created on: Aug 30, 2014
 *      Author: daniel
 */

#ifndef PLAYSTATE_H_
#define PLAYSTATE_H_

#include "GameState.h"
#include "../gui/Gui.h"
#include <iostream>
#include <string>
#include <cmath>
#include <random>
#include <thread>
#include "../map/Map.h"
#include "../Resources.h"
#include "../gui/Button.h"
#include "../gui/Gui.h"
#include "../gui/Component.h"
#include "../gui/Text.h"
#include "../gui/Clickable.h"
#include "../gui/Editable.h"
#include "../gui/Multitext.h"
#include "../gui/MenuButton.h"
#include "../Utils.h"
#include "../CmdServer.h"
#include "../Serializer.h"

namespace dfv
{

class PlayState: public GameState
{
public:
	virtual ~PlayState();

	enum MovingMode
	{
		Free,
		Walking,
		Driving
	};

	enum LoadMode
	{
		TERRAIN,
		CITY
	};

	void setLoadMode(LoadMode loadMode);

	void init(GameEngine* lp_game_engine);
	void cleanup();
	void pause();
	void resume();
	void handleInput(GameEngine* lp_game_engine);
	void update(GameEngine* lp_game_engine);
	void draw(GameEngine* lp_game_engine);
	bool executeCmd(const std::string& cmd, GameEngine* lp_game_engine);
	void initOpenGL(GameEngine* lp_game_engine);
	void createSelectedShapes(GameEngine* lp_game_engine);
	void drawSelection(sf::RenderWindow& window) const;
	sf::Vector2i getCameraTile() const;
	void generateLists();
	bool test();

	static PlayState* getInstance()
	{
		return &play_state;
	}

protected:
	PlayState();

private:
	static PlayState play_state;
	Component root_component;

	LoadMode loadMode;
	sf::Clock clock;
	dfv::Map map;
	unsigned int frame;
	dfv::Resources resources;
	sf::Vector3f map_pos;
	sf::Vector2i mouse_pos;

	Gui gui;

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

	Component gui_root;
	enum GuiId
	{
		STATS_TEXT_BAR = 0,
		INFO_PANEL,
		INFO_TEXT,
		BUTTON_MENU,
		BUTTON_CAMERA_FREE,
		BUTTON_CAMERA_WALKING,
		BUTTON_CAMERA_DRIVING
	};
};

} /* namespace dfv */

#endif /* PLAYSTATE_H_ */
