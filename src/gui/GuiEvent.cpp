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

 * GuiEvent.cpp
 *
 *  Created on: Dec 28, 2014
 *      Author: daniel
 */

#include "GuiEvent.h"

namespace dfv
{

GuiEvent::GuiEvent():
		type(None)
{
	// TODO Auto-generated constructor stub

}

GuiEvent::~GuiEvent()
{
	// TODO Auto-generated destructor stub
}

GuiEvent GuiEvent::noEvent = GuiEvent();

} /* namespace dfv */
