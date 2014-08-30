/*
 * Screen.h
 *
 *  Created on: Aug 29, 2014
 *      Author: daniel
 */

#ifndef SCREEN_H_
#define SCREEN_H_

#include <SFML/Graphics.hpp>
#include <map>

namespace dfv
{

class Screen
{
public:
	Screen();
	virtual ~Screen();

	enum Type
	{
		None,
		Main,
		Game
	};

	virtual void initialize();
	virtual void run();
	virtual void update();
	virtual void handleInput(sf::RenderWindow& window);
	virtual void draw(sf::RenderWindow& window);

	Screen* root;
	std::vector<Screen*> lp_screens;
};

} /* namespace dfv */

#endif /* SCREEN_H_ */
