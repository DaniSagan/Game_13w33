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

 * Tile.h
 *
 *  Created on: Aug 12, 2013
 *      Author: daniel
 */

#ifndef TILE_H_
#define TILE_H_


#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Utils.h"
#include "../Resources.h"
#include "../Camera.h"
#include "Road.h"
#include "Prop.h"
#include "Structure.h"
#include "Model.h"
#include "Lot.h"
#include "../Serializer.h"
#include "Quad.h"

namespace dfv
{

class Map;

class Tile
{
public:
	Tile();
	virtual ~Tile();

	enum Type
	{
		GRASS,
		ROAD,
		BUILDING,
		TREE,
		COUNT
	};

	void create(sf::Vector2f pos, float h0, float h1, float h2, float h3);
	void clear();
	void setColor(sf::Color color);
	void draw(const Camera& camera, const Resources& resources) const;

	bool hasProp() const;
	bool hasRoad() const;
	bool hasLot() const;

	void addRoad(Road::Type type, unsigned int orientation);
	void addLot(Lot* lpLot);

	void addProp(Prop* lp_prop);
	sf::Vector3f getVertex(const unsigned int index) const;
	const std::vector<sf::Vector3f> & getVertices() const;
	sf::Color getColor(unsigned int index) const;
	sf::Vector3f getNormal(unsigned int index) const;
	void setVertex(const unsigned int index, const sf::Vector3f& vertex);
	void drawRoad(const Camera& camera, const Resources& resources) const;
	void drawProp(const Camera& camera, const Resources& resources) const;

	bool isWater() const;
	bool isBeach() const;
	bool clearRoad();
	bool clearBuilding();
	bool clearProp();
	void forgetLot();

	Quad getQuad() const;

	Lot* getLot() const;
	Prop* getProp() const;
	Road* getRoad() const;

	bool canBuildRoad() const;

	static sf::Color randomGrassColor();
	static sf::Color randomSnowColor();
	static sf::Color randomSandColor();
	static sf::Color randomWaterColor();

	friend class Map;
	friend string osString(size_t level, const string& name, const Tile& tile);
	friend string osString(size_t level, const string& name, const Tile* lpTile);
	friend string osString(size_t level, const string& name, const vector<vector<Tile*>>& lpTiles, const string& type);

private:
	std::vector<sf::Vector3f> vertices;
	std::vector<sf::Vector3f> normals;
	std::vector<sf::Color> colors;
	//sf::Vector3f color;
	sf::Color color;
	pair<bool, Road*> lpRoad;
	pair<bool, Prop*> lpProp;
	pair<bool, Lot*> lpLot;
};

} /* namespace dfv */
#endif /* TILE_H_ */
