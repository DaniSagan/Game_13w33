/*
 * MenuButton.h
 *
 *  Created on: Dec 29, 2014
 *      Author: daniel
 */

#ifndef MENUBUTTON_H_
#define MENUBUTTON_H_

#include "Component.h"
#include <string>

namespace dfv
{

class MenuButton: public Component
{
public:
	MenuButton(Component* parent, int id=-1);
	virtual ~MenuButton();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual const GuiEvent handleInput(const sf::Event& event);
	bool loadTexture(const string& filename);

	enum State
	{
		NORMAL,
		OVER
	};
protected:
	sf::Texture texture;
	bool visible;
	float radius;
	sf::Vector2f position;
	State state;
};

} /* namespace dfv */

#endif /* MENUBUTTON_H_ */
