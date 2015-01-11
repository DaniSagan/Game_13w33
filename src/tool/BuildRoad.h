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

	void set(const sf::Vector2f& start, const sf::Vector2f& end);
	const vector<sf::Vector2i>& get() const;
	void clear();

	static TilePos getTilePos(const sf::Vector2f& pos);

	friend bool testBuildRoad();

protected:
	vector<sf::Vector2i> tileIds;
};

} /* namespace dfv */

#endif /* SRC_TOOL_BUILDROAD_H_ */
