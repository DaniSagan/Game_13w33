/*
 * GuiEvent.h
 *
 *  Created on: Dec 28, 2014
 *      Author: daniel
 */

#ifndef GUIEVENT_H_
#define GUIEVENT_H_

#include <SFML/Graphics.hpp>

namespace dfv
{

class GuiEvent
{
public:
	GuiEvent();
	virtual ~GuiEvent();

	struct ClickEvent
	{
		int id;
		sf::Mouse::Button mouseButton;
	};

	enum Type
	{
		None,
		ButtonEvent,
		Count
	};

	Type type;

	union
	{
		ClickEvent click;
	};

	static GuiEvent noEvent;
};

} /* namespace dfv */

#endif /* GUIEVENT_H_ */
