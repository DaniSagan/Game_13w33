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

 * Map.h
 *
 *  Created on: Aug 11, 2013
 *      Author: daniel
 */

#ifndef MAP_H_
#define MAP_H_

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <SFML/OpenGL.hpp>
#include "Camera.h"
#include "Tile.h"
#include "Resources.h"
#include "Sky.h"
#include "Prop.h"
#include "Tree.h"
#include "Model.h"


namespace dfv
{

class Map
{
public:
	Map();
	virtual ~Map();

	void create(unsigned int size);
	void generateTiles();
	void createFromFile(std::string filename, unsigned int water_level, float max_height);
	void createRandom(const unsigned int size);
	void draw(sf::Window& window, const dfv::Camera& camera, const dfv::Resources& resources) const;
	unsigned int getSize() const;
	float getTileHeight(int x, int y);
	bool saveHeightMap(const std::string& filename);
	bool loadHeightMap(const std::string& filename);
	bool saveBuildingMap(const std::string& filename);
	bool loadBuildingMap(const std::string& filename);
	void generateMapImg(const unsigned int tile_size);

	bool isRoad(unsigned int x, unsigned int y) const;
	bool hasBuilding(unsigned int x, unsigned int y) const;
	sf::Color getBuildingColor(const sf::Vector2i& tile_pos) const;
	bool changeRoadType(const sf::Vector2i& tile_pos);
	bool changeRoadOrientation(const sf::Vector2i& tile_pos);

	sf::Vector3f getMapPosFromMouse(sf::Vector2i mouse_pos);
	sf::Vector3f getViewPos(sf::Vector3f map_pos, const sf::Window& window) const;
	const std::vector<sf::Vector3f> & getTileVertices(sf::Vector2i pos) const;

	void drawTiles(dfv::RealIntRect rect, const Camera& camera, const Resources& resources) const;
	void drawBuildingBoxes(dfv::RealIntRect rect) const;
	void drawBuildingOutlines(dfv::RealIntRect rect) const;
	void drawBuildingFloors(dfv::RealIntRect rect) const;
	void drawStructureBoxes(dfv::RealIntRect rect) const;
	void drawStructureOutlines(dfv::RealIntRect rect) const;

	bool saveAsMapFormat(std::string filename);
	bool loadFromMapFormat(std::string filename);
	float getHeight(const sf::Vector2f& pos) const;

	//dfv::IntRect GetRect() const;
	dfv::RealRect getRect() const;
	dfv::RealIntRect getTileRect() const;

	void drawSky() const;
	void setLight(const sf::Vector3f& position) const;
	bool addRoad(const sf::Vector2i& tile_pos, Road::Type type, unsigned int orientation);

	void generateBuildingList();
	void callBuildingList() const;

	void generateRoadList(const Camera& camera, const Resources& resources);
	void callRoadList() const;

	void generateTileList(const Camera& camera, const Resources& resources);
	void callTileList() const;

	void generateStructureBoxList(const Camera& camera, const Resources& resources);
	void callStructureBoxList() const;

	void drawRoads(dfv::RealIntRect rect, const Camera& camera, const Resources& resources) const;
	void drawProps(dfv::RealIntRect rect, const Camera& camera, const Resources& resources) const;
	void addProp(const unsigned int x, const unsigned int y, Prop* lp_prop);
	bool hasProp(const unsigned int x, const unsigned int y) const;
	unsigned int getRoadId(const sf::Vector2i& pos) const;
	unsigned int getRoadOrientation(const sf::Vector2i& pos) const;
	bool setRoadId(const sf::Vector2i& pos, unsigned int id);
	bool setRoadOrientation(const sf::Vector2i& pos, unsigned int orientation);

	bool saveAsSgmFormat(const std::string& filename) const;
	bool loadFromSgmFormat(const std::string& filename);

	bool isWater(unsigned int x, unsigned int y) const;
	bool isBeach(unsigned int x, unsigned int y) const;
	sf::Vector3f getNormal(unsigned int x, unsigned int y);

	bool clearRoad(unsigned int x, unsigned int y);
	bool buildRoad(unsigned int x, unsigned int y, unsigned int id, unsigned int orientation);
	bool clearBuilding(unsigned int x, unsigned int y);
	bool clearProp(unsigned int x, unsigned int y);
	sf::Vector2i getTileFromMapPos(sf::Vector3f map_pos) const;

	void addStructure(const unsigned int x, const unsigned int y,
			          Quad base, const unsigned int floor_count);
	bool hasStructure(const unsigned int x, const unsigned int y) const;

	float getAvgHeight(const unsigned int x, const unsigned int y) const;
	float getMaxInclination(const unsigned int x, const unsigned int y) const;

	Model test_model;
private:
	unsigned int size;
	std::vector<std::vector<float> > heights;
	std::vector<std::vector<dfv::Tile*> > lp_tiles;
	sf::Image map_img;
	dfv::Sky sky;
	GLuint building_list;
	GLuint tile_list;
	GLuint road_list;
	unsigned int population;
	GLuint structure_box_list;

};

} /* namespace dfv */
#endif /* MAP_H_ */
