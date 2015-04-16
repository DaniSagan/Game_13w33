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

BuildRoad::TileRoadInfo::TileRoadInfo():
		roadType(Road::straight), orientation(0)
{

}

BuildRoad::TileRoadInfo::TileRoadInfo(const sf::Vector2i _tileId, Road::Type _roadType, unsigned int _orientation):
		tileId(_tileId), roadType(_roadType), orientation(_orientation)
{

}

void BuildRoad::set(const sf::Vector2f& start, const sf::Vector2f& end)
{

}

const vector<BuildRoad::TileRoadInfo>& BuildRoad::get() const
{
	return this->tileInfo;
}

vector<BuildRoad::TileRoadInfo> BuildRoad::generateSimple(pair<sf::Vector2i, BuildRoad::TilePos> p1, pair<sf::Vector2i, BuildRoad::TilePos> p2)
{
	if(p1.first == p2.first)
	{
		if(p1.second == p2.second)
		{
			return vector<TileRoadInfo>(0);
		}
		else if((p1.second == BuildRoad::X_NEG && p2.second == BuildRoad::X_POS) ||
				(p1.second == BuildRoad::X_POS && p2.second == BuildRoad::X_NEG))
		{
			return vector<TileRoadInfo>(1, TileRoadInfo(p1.first, Road::straight, 1));
		}
		else if((p1.second == BuildRoad::Y_NEG && p2.second == BuildRoad::Y_POS) ||
				(p1.second == BuildRoad::Y_POS && p2.second == BuildRoad::Y_NEG))
		{
			return vector<TileRoadInfo>(1, TileRoadInfo(p1.first, Road::straight, 0));
		}
		else if((p1.second == BuildRoad::Y_NEG && p2.second == BuildRoad::X_POS) ||
				(p1.second == BuildRoad::X_POS && p2.second == BuildRoad::Y_NEG))
		{
			return vector<TileRoadInfo>(1, TileRoadInfo(p1.first, Road::curve, 0));
		}
		else if((p1.second == BuildRoad::Y_NEG && p2.second == BuildRoad::X_NEG) ||
				(p1.second == BuildRoad::X_NEG && p2.second == BuildRoad::Y_NEG))
		{
			return vector<TileRoadInfo>(1, TileRoadInfo(p1.first, Road::curve, 1));
		}
		else if((p1.second == BuildRoad::Y_POS && p2.second == BuildRoad::X_NEG) ||
				(p1.second == BuildRoad::X_NEG && p2.second == BuildRoad::Y_POS))
		{
			return vector<TileRoadInfo>(1, TileRoadInfo(p1.first, Road::curve, 2));
		}
		else if((p1.second == BuildRoad::Y_POS && p2.second == BuildRoad::X_POS) ||
				(p1.second == BuildRoad::X_POS && p2.second == BuildRoad::Y_POS))
		{
			return vector<TileRoadInfo>(1, TileRoadInfo(p1.first, Road::curve, 3));
		}
	}
	else if(p1.first.x == p2.first.x) // same x
	{
		vector<TileRoadInfo> res;
		for(int y = min(p1.first.y, p2.first.y); y <= max(p1.first.y, p2.first.y); y++)
		{
			res.push_back(TileRoadInfo(sf::Vector2i(p1.first.x, y), Road::straight, 0));
		}
		return res;
	}
	else if(p1.first.y == p2.first.y) // same y
	{
		vector<TileRoadInfo> res;
		for(int x = min(p1.first.x, p2.first.x); x <= max(p1.first.x, p2.first.x); x++)
		{
			res.push_back(TileRoadInfo(sf::Vector2i(x, p1.first.y), Road::straight, 0));
		}
		return res;
	}
	else // otherwise
	{
		sf::Vector2i size = p2.first - p1.first;
		vector<TileRoadInfo> v1 = BuildRoad::generateSimple(
				make_pair(p1.first, p1.second),
			    make_pair(p1.first+sf::Vector2i(size.x, 0), -p1.second)
	    );
		vector<TileRoadInfo> v2 = BuildRoad::generateSimple(
				make_pair(p2.first-sf::Vector2i(0, size.y), -p2.second),
			    make_pair(p1.first+sf::Vector2i(size.x, 0), p2.second)
	    );
		vector<TileRoadInfo> v3 = BuildRoad::generateSimple(
				make_pair(sf::Vector2i(p2.first.x, p1.first.y), -p1.second),
			    make_pair(sf::Vector2i(p2.first.x, p1.first.y), -p2.second)
	    );
		v1.insert(v1.end(), v3.begin(), v3.end());
		v1.insert(v1.end(), v2.begin(), v2.end());
		return v1;
	}
}

vector<BuildRoad::TileRoadInfo> BuildRoad::generate(pair<sf::Vector2i, BuildRoad::TilePos> p1, pair<sf::Vector2i, BuildRoad::TilePos> p2)
{
	// same tile
	if(p1.first == p2.first)
	{
		if(p1.second == p2.second)
		{
			return vector<TileRoadInfo>(0);
		}
		else if((p1.second == BuildRoad::X_NEG && p2.second == BuildRoad::X_POS) ||
				(p1.second == BuildRoad::X_POS && p2.second == BuildRoad::X_NEG))
		{
			return vector<TileRoadInfo>(1, TileRoadInfo(p1.first, Road::straight, 1));
		}
		else if((p1.second == BuildRoad::Y_NEG && p2.second == BuildRoad::Y_POS) ||
				(p1.second == BuildRoad::Y_POS && p2.second == BuildRoad::Y_NEG))
		{
			return vector<TileRoadInfo>(1, TileRoadInfo(p1.first, Road::straight, 0));
		}
		else if((p1.second == BuildRoad::Y_NEG && p2.second == BuildRoad::X_POS) ||
				(p1.second == BuildRoad::X_POS && p2.second == BuildRoad::Y_NEG))
		{
			return vector<TileRoadInfo>(1, TileRoadInfo(p1.first, Road::curve, 0));
		}
		else if((p1.second == BuildRoad::Y_NEG && p2.second == BuildRoad::X_NEG) ||
				(p1.second == BuildRoad::X_NEG && p2.second == BuildRoad::Y_NEG))
		{
			return vector<TileRoadInfo>(1, TileRoadInfo(p1.first, Road::curve, 1));
		}
		else if((p1.second == BuildRoad::Y_POS && p2.second == BuildRoad::X_NEG) ||
				(p1.second == BuildRoad::X_NEG && p2.second == BuildRoad::Y_POS))
		{
			return vector<TileRoadInfo>(1, TileRoadInfo(p1.first, Road::curve, 2));
		}
		else if((p1.second == BuildRoad::Y_POS && p2.second == BuildRoad::X_POS) ||
				(p1.second == BuildRoad::X_POS && p2.second == BuildRoad::Y_POS))
		{
			return vector<TileRoadInfo>(1, TileRoadInfo(p1.first, Road::curve, 3));
		}
	}
	// same x
	else if(p1.first.x == p2.first.x)
	{
		if(p1.first.y < p2.first.y)
		{
			if(p1.second == BuildRoad::Y_POS)
			{
				pair<sf::Vector2i, BuildRoad::TilePos> newP1(
						p1.first + sf::Vector2i(0, 1),
						BuildRoad::Y_NEG
				);
				return BuildRoad::generate(newP1, p2);
			}
			else if(p2.second == BuildRoad::Y_NEG)
			{
				pair<sf::Vector2i, BuildRoad::TilePos> newP2(
						p1.first + sf::Vector2i(0, -1),
						BuildRoad::Y_POS
				);
				return BuildRoad::generate(p1, newP2);
			}
			else
			{
				vector<BuildRoad::TileRoadInfo> v1, v2;
				pair<sf::Vector2i, BuildRoad::TilePos> newP2a(
						p2.first + sf::Vector2i(0, -1),
						BuildRoad::Y_POS
				);
				v1 = BuildRoad::generate(p1, newP2a);
				pair<sf::Vector2i, BuildRoad::TilePos> newP1b(
						p2.first,
						BuildRoad::Y_NEG
				);
				v2 = BuildRoad::generate(newP1b, p2);
				v1.insert(v1.end(), v2.begin(), v2.end());
				return v1;
			}
		}
	}
	// same y
	else if(p1.first.y == p2.first.y)
	{
		return vector<BuildRoad::TileRoadInfo>(0);
	}
	// otherwise
	else if((p1.first.x < p2.first.x) && (p1.first.y < p2.first.y))
	{
		// corrections
		if(p2.second == BuildRoad::X_NEG)
		{
			pair<sf::Vector2i, BuildRoad::TilePos> newP2(
					p2.first - sf::Vector2i(1, 0),
					BuildRoad::X_POS
			);
			return BuildRoad::generate(p1, newP2);
		}
		else if(p2.second == BuildRoad::Y_NEG)
		{
			pair<sf::Vector2i, BuildRoad::TilePos> newP2(
					p2.first - sf::Vector2i(0, 1),
					BuildRoad::Y_POS
			);
			return BuildRoad::generate(p1, newP2);
		}
		else if(p1.second == BuildRoad::X_POS)
		{
			pair<sf::Vector2i, BuildRoad::TilePos> newP2(
					p2.first + sf::Vector2i(1, 0),
					BuildRoad::X_NEG
			);
			return BuildRoad::generate(p1, newP2);
		}
		else if(p1.second == BuildRoad::Y_POS)
		{
			pair<sf::Vector2i, BuildRoad::TilePos> newP2(
					p2.first + sf::Vector2i(0, 1),
					BuildRoad::Y_NEG
			);
			return BuildRoad::generate(p1, newP2);
		}
		//
		else if(p2.second == BuildRoad::Y_POS)
		{
			pair<sf::Vector2i, BuildRoad::TilePos> newP1a(
					p2.first + sf::Vector2i(0, 1),
					BuildRoad::Y_NEG
			);
			//return BuildRoad::generate()
		}
	}
	return vector<BuildRoad::TileRoadInfo>(0);
}

void BuildRoad::clear()
{
	this->tileInfo.clear();
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

BuildRoad::TilePos operator-(BuildRoad::TilePos p)
{
	switch(p)
	{
	case BuildRoad::X_NEG: return BuildRoad::X_POS;
	case BuildRoad::Y_NEG: return BuildRoad::Y_POS;
	case BuildRoad::X_POS: return BuildRoad::X_NEG;
	case BuildRoad::Y_POS: return BuildRoad::Y_NEG;
	}
}

} /* namespace dfv */
