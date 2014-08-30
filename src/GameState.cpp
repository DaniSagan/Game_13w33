/*
 * GameState.cpp
 *
 *  Created on: Aug 30, 2014
 *      Author: daniel
 */

#include "GameState.h"

namespace dfv
{

GameState::GameState()
{
	// TODO Auto-generated constructor stub

}

GameState::~GameState()
{
	// TODO Auto-generated destructor stub
}

void GameState::changeState(GameEngine* lp_game_engine, GameState* lp_state)
{
	lp_game_engine->changeState(lp_state);
}

} /* namespace dfv */
