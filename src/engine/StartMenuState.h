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

 * StartMenuState.h
 *
 *  Created on: Aug 30, 2014
 *      Author: daniel
 */

#ifndef STARTMENUSTATE_H_
#define STARTMENUSTATE_H_

#include "GameState.h"
#include "../gui/Text.h"
#include "../gui/Clickable.h"
#include "../gui/Picture.h"
#include "../gui/Panel.h"
#include "../gui/Editable.h"

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
		NONE = 0,
		START_NEW_BUTTON,
		LOAD_BUTTON,
		QUIT_BUTTON,
		START_NEW_MENU,
		SIZE_EDIT,
		GENERATE_NEW_BUTTON,
		LOGO_IMG
	};
};

} /* namespace dfv */

#endif /* STARTMENUSTATE_H_ */
