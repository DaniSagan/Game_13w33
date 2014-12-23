/*
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
