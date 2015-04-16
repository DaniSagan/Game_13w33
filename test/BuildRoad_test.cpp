/*
 * BuildRoad_test.cpp
 *
 *  Created on: Jan 11, 2015
 *      Author: daniel
 */

#include <gtest/gtest.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../src/tool/BuildRoad.h"

using namespace std;

namespace dfv
{

TEST(buidRoadTest, getTilePosTest)
{
	EXPECT_TRUE(BuildRoad::getTilePos(sf::Vector2f(0.25f, 0.5f)) == BuildRoad::X_NEG);
	EXPECT_TRUE(BuildRoad::getTilePos(sf::Vector2f(0.75f, 0.5f)) == BuildRoad::X_POS);
	EXPECT_TRUE(BuildRoad::getTilePos(sf::Vector2f(0.5f, 0.25f)) == BuildRoad::Y_NEG);
	EXPECT_TRUE(BuildRoad::getTilePos(sf::Vector2f(0.5f, 0.75f)) == BuildRoad::Y_POS);
}

TEST(buidRoadTest, tilePosTest)
{
	EXPECT_EQ(BuildRoad::X_NEG, -BuildRoad::X_POS);
	EXPECT_EQ(BuildRoad::X_POS, -BuildRoad::X_NEG);
	EXPECT_EQ(BuildRoad::Y_NEG, -BuildRoad::Y_POS);
	EXPECT_EQ(BuildRoad::Y_POS, -BuildRoad::Y_NEG);
}

TEST(buildRoadTest, generateTest)
{
	vector<BuildRoad::TileRoadInfo> info;
	info = BuildRoad::generate(make_pair(sf::Vector2i(0, 0), BuildRoad::X_NEG),
			                   make_pair(sf::Vector2i(0, 0), BuildRoad::X_POS));
	ASSERT_TRUE(info.size() == 1);
	ASSERT_TRUE(info.at(0).tileId == sf::Vector2i(0, 0));
	ASSERT_TRUE(info.at(0).roadType == Road::straight);
	ASSERT_TRUE(info.at(0).orientation == 1);

	info = BuildRoad::generate(make_pair(sf::Vector2i(0, 0), BuildRoad::Y_NEG),
			                   make_pair(sf::Vector2i(0, 0), BuildRoad::Y_POS));
	ASSERT_TRUE(info.size() == 1);
	ASSERT_TRUE(info.at(0).tileId == sf::Vector2i(0, 0));
	ASSERT_TRUE(info.at(0).roadType == Road::straight);
	ASSERT_TRUE(info.at(0).orientation == 0);

	info = BuildRoad::generate(make_pair(sf::Vector2i(0, 0), BuildRoad::Y_NEG),
			                   make_pair(sf::Vector2i(0, 0), BuildRoad::X_POS));
	ASSERT_TRUE(info.size() == 1);
	ASSERT_TRUE(info.at(0).tileId == sf::Vector2i(0, 0));
	ASSERT_TRUE(info.at(0).roadType == Road::curve);
	ASSERT_TRUE(info.at(0).orientation == 0);

	info = BuildRoad::generate(make_pair(sf::Vector2i(0, 0), BuildRoad::Y_NEG),
			                   make_pair(sf::Vector2i(0, 1), BuildRoad::Y_POS));
	ASSERT_TRUE(info.size() == 2);
	ASSERT_TRUE(info.at(0).tileId == sf::Vector2i(0, 0));
	ASSERT_TRUE(info.at(0).roadType == Road::straight);
	ASSERT_TRUE(info.at(0).orientation == 0);
	ASSERT_TRUE(info.at(1).tileId == sf::Vector2i(0, 1));
	ASSERT_TRUE(info.at(1).roadType == Road::straight);
	ASSERT_TRUE(info.at(1).orientation == 0);

}

TEST(buildRoadTest, generateSimpleTest)
{
	vector<BuildRoad::TileRoadInfo> info;
	info = BuildRoad::generateSimple(
			make_pair(sf::Vector2i(0, 0), BuildRoad::X_NEG),
			make_pair(sf::Vector2i(0, 0), BuildRoad::X_POS)
	);
	ASSERT_TRUE(info.size() == 1);
	ASSERT_TRUE(info.at(0).tileId == sf::Vector2i(0, 0));
	ASSERT_TRUE(info.at(0).roadType == Road::straight);
	ASSERT_TRUE(info.at(0).orientation == 1);

	info = BuildRoad::generateSimple(
			make_pair(sf::Vector2i(0, 0), BuildRoad::Y_NEG),
			make_pair(sf::Vector2i(0, 0), BuildRoad::Y_POS)
	);
	ASSERT_TRUE(info.size() == 1);
	ASSERT_TRUE(info.at(0).tileId == sf::Vector2i(0, 0));
	ASSERT_TRUE(info.at(0).roadType == Road::straight);
	ASSERT_TRUE(info.at(0).orientation == 0);

	info = BuildRoad::generateSimple(
			make_pair(sf::Vector2i(0, 0), BuildRoad::X_NEG),
			make_pair(sf::Vector2i(0, 0), BuildRoad::Y_POS)
	);
	ASSERT_TRUE(info.size() == 1);
	ASSERT_TRUE(info.at(0).tileId == sf::Vector2i(0, 0));
	ASSERT_TRUE(info.at(0).roadType == Road::curve);
	ASSERT_TRUE(info.at(0).orientation == 2);

	info = BuildRoad::generateSimple(
			make_pair(sf::Vector2i(0, 0), BuildRoad::X_NEG),
			make_pair(sf::Vector2i(1, 0), BuildRoad::X_POS)
	);
	ASSERT_TRUE(info.size() == 2);
	ASSERT_TRUE(info.at(0).tileId == sf::Vector2i(0, 0));
	ASSERT_TRUE(info.at(1).tileId == sf::Vector2i(1, 0));
	ASSERT_TRUE(info.at(0).roadType == Road::straight);
	ASSERT_TRUE(info.at(1).roadType == Road::straight);
	ASSERT_TRUE(info.at(0).orientation == 0);
	ASSERT_TRUE(info.at(1).orientation == 0);

}

}
