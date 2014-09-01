/*
 * StartMenuState.h
 *
 *  Created on: Aug 30, 2014
 *      Author: daniel
 */

#ifndef STARTMENUSTATE_H_
#define STARTMENUSTATE_H_

#include "GameState.h"
#include "gui/Text.h"
#include "gui/Clickable.h"
#include "gui/Picture.h"
#include "gui/Panel.h"
#include "gui/Editable.h"

namespace dfv
{

class StartMenuState: public GameState
{
public:
	virtual ~StartMenuState();

	friend class PlayState;

	void init(GameEngine* lp_game_engine);
	void cleanup();
	void pause();
	void resume();
	void handleInput(GameEngine* lp_game_engine);
	void update(GameEngine* lp_game_engine);
	void draw(GameEngine* lp_game_engine);
	void executeCmd(std::string& cmd, GameEngine* lp_game_engine);

	static StartMenuState* getInstance()
	{
		return &start_menu_state;
	}

protected:
	StartMenuState();

private:
	static StartMenuState start_menu_state;

	Component gui;
	enum GuiComponents
	{
		START_NEW_BUTTON = 0,
		START_NEW_MENU,
		SIZE_EDIT,
		GENERATE_NEW_BUTTON
	};
};

} /* namespace dfv */

#endif /* STARTMENUSTATE_H_ */
