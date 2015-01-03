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

 * GameState.h
 *
 *  Created on: Aug 30, 2014
 *      Author: daniel
 */

#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include "GameEngine.h"

namespace dfv
{

class GameState
{
public:
	GameState();
	virtual ~GameState();

	virtual void init(GameEngine* lp_game_engine) = 0;
	virtual void cleanup() = 0;
	virtual void pause() = 0;
	virtual void resume() = 0;
	virtual void handleInput(GameEngine* lp_game_engine) = 0;
	virtual void update(GameEngine* lp_game_engine) = 0;
	virtual void draw(GameEngine* lp_game_engine) = 0;

	void changeState(GameEngine* lp_game_engine, GameState* lp_state);
};

} /* namespace dfv */

#endif /* GAMESTATE_H_ */
