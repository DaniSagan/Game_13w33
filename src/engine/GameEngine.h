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

 * GameEngine.h
 *
 *  Created on: Aug 30, 2014
 *      Author: daniel
 */

#ifndef GAMEENGINE_H_
#define GAMEENGINE_H_

#include <SFML/Graphics.hpp>
#include <stack>
#include <cassert>
#include "../gui/Assets.h"

namespace dfv
{

class GameState;

class GameEngine
{
public:
	GameEngine();
	virtual ~GameEngine();

	void changeState(GameState* state);
	void pushState(GameState* state);
	void popState();

	void handleInput();
	void update();
	void draw();

	bool isRunning() const;
	void quit();

	sf::RenderWindow window;
	Assets assets;

private:
	std::stack<GameState*> lp_states;

	bool running;
};

} /* namespace dfv */

#endif /* GAMEENGINE_H_ */
