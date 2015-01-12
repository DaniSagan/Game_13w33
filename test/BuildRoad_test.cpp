/*
 * BuildRoad_test.cpp
 *
 *  Created on: Jan 11, 2015
 *      Author: daniel
 */

#include <gtest/gtest.h>
#include "../src/tool/BuildRoad.h"

TEST(buidRoadTest, getTilePosTest)
{
	EXPECT_TRUE(dfv::BuildRoad::getTilePos(sf::Vector2f(0.25f, 0.5f)) == dfv::BuildRoad::X_NEG);
	EXPECT_TRUE(dfv::BuildRoad::getTilePos(sf::Vector2f(0.75f, 0.5f)) == dfv::BuildRoad::X_POS);
	EXPECT_TRUE(dfv::BuildRoad::getTilePos(sf::Vector2f(0.5f, 0.25f)) == dfv::BuildRoad::Y_NEG);
	EXPECT_TRUE(dfv::BuildRoad::getTilePos(sf::Vector2f(0.5f, 0.75f)) == dfv::BuildRoad::Y_POS);
}
