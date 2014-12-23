/*
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
