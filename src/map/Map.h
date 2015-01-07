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
#include "../Camera.h"
#include "Tile.h"
#include "../Resources.h"
#include "Sky.h"
#include "Prop.h"
#include "Tree.h"
#include "Model.h"
#include "HeightMap.h"
#include "../Serializer.h"


namespace dfv
{

//class Tile;

class Map
{
public:
	Map();
	virtual ~Map();

	void create(size_t size);
	void clear();
	void clearLot(const sf::Vector2i& tileIndex);
	void generateTiles();
	size_t getSize() const;
	void generateMapImg(const size_t tile_size);
	void loadHeightMap(const string& filename, size_t smoothingCount = 0);

	sf::Vector3f getMapPosFromMouse(sf::Vector2i mouse_pos);
	sf::Vector3f getViewPos(sf::Vector3f map_pos, const sf::Window& window) const;

	void drawTiles(dfv::RealIntRect rect, const Camera& camera, const Resources& resources) const;
	void drawStructureBoxes(dfv::RealIntRect rect) const;
	void drawStructureOutlines(dfv::RealIntRect rect) const;

	float getHeight(const sf::Vector2f& pos) const;

	dfv::RealRect getRect() const;
	dfv::RealIntRect getTileRect() const;

	void drawSky() const;
	void setLight(const sf::Vector3f& position) const;

	void generateRoadList(const Camera& camera, const Resources& resources);
	void callRoadList() const;

	void generateTileList(const Camera& camera, const Resources& resources);
	void callTileList() const;

	void generateStructureBoxList(const Camera& camera, const Resources& resources);
	void callStructureBoxList() const;

	void deleteLists();

	void drawRoads(dfv::RealIntRect rect, const Camera& camera, const Resources& resources) const;
	void drawProps(dfv::RealIntRect rect, const Camera& camera, const Resources& resources) const;

	bool addLot(unsigned int xmin, unsigned int ymin, unsigned int xmax, unsigned int ymax);
	Lot* getLot(unsigned int x, unsigned int y) const;

	Tile& getTile(int x, int y) const;
	Tile& getTile(const sf::Vector2i& pos) const;
	char getRoadChar(const sf::Vector2i& pos) const;
	vector<string> getRoadPattern(const sf::Vector2i& pos, size_t radius) const;
	bool matchRoadPattern(sf::Vector2i pos, const string& pattern) const;
	bool contains(const sf::Vector2i& pos) const;
	bool contains(int x, int y) const;
	string getName() const;
	void setName(const string& name);
	void deserialize(const string& filename);

	HeightMap heightMap;

	friend string osString(size_t level, const string& name, const Map& map);
	friend ostream& operator<<(ostream& os, Map& map);
	friend bool isRead(Serializer& ser, Map& map);

private:
	size_t size;
	string name;
	std::vector<std::vector<float> > heights;
	std::vector<std::vector<dfv::Tile*> > lp_tiles;
	std::vector<Lot*> lpLots;
	sf::Image map_img;
	dfv::Sky sky;
	GLuint tile_list;
	GLuint road_list;
	unsigned int population;
	GLuint structure_box_list;
};



} /* namespace dfv */
#endif /* MAP_H_ */
