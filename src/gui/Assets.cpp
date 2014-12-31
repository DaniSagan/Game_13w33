/*
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
