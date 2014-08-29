/*
 * Assets.cpp
 *
 *  Created on: Aug 28, 2014
 *      Author: daniel
 */

#include "Assets.h"

namespace dfv
{

Assets::Assets()
{
	// TODO Auto-generated constructor stub

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
	return everything_ok;
}


} /* namespace dfv */
