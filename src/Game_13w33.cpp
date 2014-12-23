/* Hyperopolis: Megacities building game.
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
*/

//#include "App.h"
#include "engine/GameEngine.h"
#include "engine/StartMenuState.h"
#include <SFML/Graphics.hpp>

int main()
{
	dfv::GameEngine game_engine;
	game_engine.changeState(dfv::StartMenuState::getInstance());
	while(game_engine.isRunning())
	{
		game_engine.handleInput();
		game_engine.update();
		game_engine.draw();
	}
	return 0;
}
