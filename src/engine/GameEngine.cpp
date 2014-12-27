/*
 * GameEngine.cpp
 *
 *  Created on: Aug 30, 2014
 *      Author: daniel
 */

#include "GameEngine.h"
#include "GameState.h"

namespace dfv
{

GameEngine::GameEngine():
		running(true)
{
	const unsigned int WIDTH = 1024;
	const unsigned int HEIGHT = WIDTH * 9 / 16;
	const std::string GAME_NAME("Hyperopolis");
	sf::ContextSettings contextSettings(32);
	//contextSettings.antialiasingLevel = 1;
	this->window.create({WIDTH, HEIGHT}, GAME_NAME, sf::Style::Default, contextSettings);
	assert(this->assets.load());

}

GameEngine::~GameEngine()
{

}

void GameEngine::changeState(GameState* lp_state)
{
	if(!this->lp_states.empty())
	{
		this->lp_states.top()->cleanup();
		this->lp_states.pop();
	}

	this->lp_states.push(lp_state);
	this->lp_states.top()->init(this);
}

void GameEngine::pushState(GameState* lp_state)
{
	if(!this->lp_states.empty())
	{
		this->lp_states.top()->pause();
	}

	this->lp_states.push(lp_state);
	this->lp_states.top()->init(this);
}

void GameEngine::popState()
{
	if(!this->lp_states.empty())
	{
		this->lp_states.top()->cleanup();
		this->lp_states.pop();
	}

	if(!this->lp_states.empty())
	{
		this->lp_states.top()->resume();
	}
}

void GameEngine::handleInput()
{
	this->lp_states.top()->handleInput(this);
}

void GameEngine::update()
{
	this->lp_states.top()->update(this);
}

void GameEngine::draw()
{
	this->lp_states.top()->draw(this);
}

bool GameEngine::isRunning() const
{
	return this->running;
}

void GameEngine::quit()
{
	this->running = false;
}

} /* namespace dfv */
