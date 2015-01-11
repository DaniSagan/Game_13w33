/*
 * BuildRoad.cpp
 *
 *  Created on: Jan 11, 2015
 *      Author: daniel
 */

#include "BuildRoad.h"

namespace dfv
{

BuildRoad::BuildRoad()
{

}

BuildRoad::~BuildRoad()
{

}

void BuildRoad::set(const sf::Vector2f& start, const sf::Vector2f& end)
{

}

const vector<sf::Vector2i>& BuildRoad::get() const
{
	return this->tileIds;
}

void BuildRoad::clear()
{
	this->tileIds.clear();
}

BuildRoad::TilePos BuildRoad::getTilePos(const sf::Vector2f& pos)
{
	float x = fmod(pos.x, 1.f);
	float y = fmod(pos.y, 1.f);
	if(y < x)
	{
		if(y < 1 - x) return Y_NEG;
		else return X_POS;
	}
	else
	{
		if(y < 1 - x) return X_NEG;
		else return Y_POS;
	}
}

bool testBuildRoad()
{
	assert(BuildRoad::getTilePos(sf::Vector2f(0.25f, 0.5f)) == BuildRoad::X_NEG);
	assert(BuildRoad::getTilePos(sf::Vector2f(0.75f, 0.5f)) == BuildRoad::X_POS);
	assert(BuildRoad::getTilePos(sf::Vector2f(0.5f, 0.25f)) == BuildRoad::Y_NEG);
	assert(BuildRoad::getTilePos(sf::Vector2f(0.5f, 0.75f)) == BuildRoad::Y_POS);
	return true;
}

} /* namespace dfv */
