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
//#include "Building.h"
#include "../Utils.h"
#include "../Resources.h"
#include "../Camera.h"
#include "Road.h"
#include "Prop.h"
#include "Structure.h"
#include "Model.h"
#include "Lot.h"

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
		grass,
		road,
		building,
		tree,
		count
	};

	void create(sf::Vector2f pos, float h0, float h1, float h2, float h3);
	void setColor(sf::Color color);
	void draw(const dfv::Camera& camera, const dfv::Resources& resources) const;
	//void addBuilding(float height);
	//bool hasBuilding() const;
	bool hasProp() const;
	//void drawBuilding(const bool draw_floors) const;
	//sf::Color getBuildingColor() const;
	void setAsRoad(const bool r);
	bool isRoad() const;
	//float getBuildingHeight() const;
	void addRoad(dfv::Road::Type type, unsigned int orientation);
	unsigned int getRoadId() const;
	unsigned int getRoadOrientation() const;
	bool setRoadId(unsigned int road_id);
	bool setRoadOrientation(unsigned int road_orientation);
	void addProp(Prop* lp_prop);
	sf::Vector3f getVertex(const unsigned int index) const;
	const std::vector<sf::Vector3f> & getVertices() const;

	//void drawBuildingBox() const;
	//void drawBuildingOutline() const;
	//void drawBuildingFloors() const;

	sf::Vector3f getColor(unsigned int index) const;
	sf::Vector3f getNormal(unsigned int index) const;
	//sf::Vector3f getBuildingColor3f() const;

	void setVertex(const unsigned int index, const sf::Vector3f& vertex);
	sf::Color getSfmlColor() const;
	//void setBuildingColor(const sf::Color& color);
	void drawRoad(const Camera& camera, const Resources& resources) const;
	void drawProp(const Camera& camera, const Resources& resources) const;

	bool isWater() const;
	bool isBeach() const;
	bool clearRoad();
	bool clearBuilding();
	bool clearProp();

	Quad getQuad() const;

	void createStructure(Quad base, unsigned int floor_count);
	void destroyStructure();
	void drawStructureBox() const;
	void drawStructureOutline() const;
	bool hasStructure() const;

	friend class Map;

private:
	std::vector<sf::Vector3f> vertices;
	std::vector<sf::Vector3f> normals;
	std::vector<sf::Vector3f> colors;
	sf::Vector3f color;
	//dfv::Building* lp_building;
	bool is_road;
	dfv::Road* lp_road;
	dfv::Prop* lp_prop;

	//bool has_structure;
	//Structure structure;
	Structure* lp_structure;
	Lot* lp_lot;
};

} /* namespace dfv */
#endif /* TILE_H_ */
