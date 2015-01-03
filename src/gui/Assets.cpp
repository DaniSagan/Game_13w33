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

 * Assets.cpp
 *
 *  Created on: Aug 28, 2014
 *      Author: daniel
 */

#include "Assets.h"

namespace dfv
{

Assets assetsInstance;

Assets::Assets()
{
	this->load();
}

Assets::~Assets()
{
	// TODO Auto-generated destructor stub
}

bool Assets::load()
{
	bool everything_ok = true;
	if(!this->font.loadFromFile("res/font/Ubuntu-L.ttf"))
	{
		everything_ok = false;
	}
	if(!this->buttonMenuImg.loadFromFile("res/gui/button_menu.png"))
	{
		everything_ok = false;
	}
	if(!this->sounds.selectBuffer.loadFromFile("res/sound/select.wav"))
	{
		everything_ok = false;
	}
	else
	{
		this->sounds.select.setBuffer(this->sounds.selectBuffer);
	}
	if(!this->sounds.overBuffer.loadFromFile("res/sound/over.wav"))
	{
		everything_ok = false;
	}
	else
	{
		this->sounds.over.setBuffer(this->sounds.overBuffer);
	}
	return everything_ok;
}


} /* namespace dfv */
