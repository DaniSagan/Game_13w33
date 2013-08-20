/*
 * Gui.h
 *
 *  Created on: Aug 20, 2013
 *      Author: daniel
 */

#ifndef GUI_H_
#define GUI_H_

#include <SFML/Graphics.hpp>

namespace dfv
{

class Gui
{
public:
	Gui();
	virtual ~Gui();

	void Draw(sf::RenderWindow& window) const;

private:

	float fps;
	unsigned int quadrant;
};

} /* namespace dfv */
#endif /* GUI_H_ */
