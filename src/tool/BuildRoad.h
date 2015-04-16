/*
 * BuildRoad.h
 *
 *  Created on: Jan 11, 2015
 *      Author: daniel
 */

#ifndef SRC_TOOL_BUILDROAD_H_
#define SRC_TOOL_BUILDROAD_H_

#include <SFML/Graphics.hpp>
#include <vector>
#include <cassert>
#include <tuple>
#include "../map/Road.h"

using namespace std;

namespace dfv
{

class BuildRoad
{
public:
	BuildRoad();
	virtual ~BuildRoad();

	enum TilePos
	{
		X_NEG,
		X_POS,
		Y_NEG,
		Y_POS
	};

	struct TileRoadInfo
	{
		sf::Vector2i tileId;
		Road::Type roadType;
		unsigned int orientation;
		TileRoadInfo();
		TileRoadInfo(const sf::Vector2i _tileId, Road::Type _roadType, unsigned int _orientation);
	};

	void set(const sf::Vector2f& start, const sf::Vector2f& end);
	const vector<TileRoadInfo>& get() const;
	static vector<TileRoadInfo> generateSimple(pair<sf::Vector2i, TilePos> p1, pair<sf::Vector2i, TilePos> p2);
	static vector<TileRoadInfo> generate(pair<sf::Vector2i, TilePos> p1, pair<sf::Vector2i, TilePos> p2);
	void clear();

	static TilePos getTilePos(const sf::Vector2f& pos);

protected:
	vector<TileRoadInfo> tileInfo;
};

BuildRoad::TilePos operator-(BuildRoad::TilePos p);

} /* namespace dfv */

#endif /* SRC_TOOL_BUILDROAD_H_ */
