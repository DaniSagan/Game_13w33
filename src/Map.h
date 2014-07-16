/*
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
#include <SFML/OpenGL.hpp>
#include "Camera.h"
#include "Tile.h"
#include "Resources.h"
#include "Sky.h"
#include "Prop.h"
#include "Tree.h"


namespace dfv
{

class Map
{
public:
	Map();
	virtual ~Map();

	void Create(unsigned int size);
	void GenerateTiles();
	void CreateFromFile(std::string filename, unsigned int water_level, float max_height);
	void CreateRandom(const unsigned int size);
	void Draw(sf::Window& window, const dfv::Camera& camera, const dfv::Resources& resources) const;
	unsigned int GetSize() const;
	float GetHeight(int x, int y);
	bool SaveHeightMap(const std::string& filename);
	bool LoadHeightMap(const std::string& filename);
	bool SaveBuildingMap(const std::string& filename);
	bool LoadBuildingMap(const std::string& filename);
	void GenerateMapImg(const unsigned int tile_size);

	bool IsRoad(const sf::Vector2i& tile_pos) const;
	bool isRoad(unsigned int x, unsigned int y) const;
	bool HasBuilding(const sf::Vector2i& tile_pos) const;
	bool hasBuilding(unsigned int x, unsigned int y) const;
	sf::Color GetBuildingColor(const sf::Vector2i& tile_pos) const;
	bool ChangeRoadType(const sf::Vector2i& tile_pos);
	bool ChangeRoadOrientation(const sf::Vector2i& tile_pos);

	sf::Vector3f GetMapPosFromMouse(sf::Vector2i mouse_pos);
	sf::Vector3f GetViewPos(sf::Vector3f map_pos, const sf::Window& window) const;
	const std::vector<sf::Vector3f> & GetTileVertices(sf::Vector2i pos) const;

	/*void DrawTiles(dfv::IntRect rect, const Camera& camera, const Resources& resources) const;
	void DrawBuildingBoxes(dfv::IntRect rect) const;
	void DrawBuildingOutlines(dfv::IntRect rect) const;
	void DrawBuildingFloors(dfv::IntRect rect) const;*/

	void drawTiles(dfv::RealIntRect rect, const Camera& camera, const Resources& resources) const;
	void drawBuildingBoxes(dfv::RealIntRect rect) const;
	void drawBuildingOutlines(dfv::RealIntRect rect) const;
	void drawBuildingFloors(dfv::RealIntRect rect) const;

	bool SaveAsMapFormat(std::string filename);
	bool LoadFromMapFormat(std::string filename);
	float GetHeight(const sf::Vector2f& pos) const;

	//dfv::IntRect GetRect() const;
	dfv::RealRect getRect() const;
	dfv::RealIntRect getTileRect() const;

	void DrawSky() const;
	void SetLight(const sf::Vector3f& position) const;
	bool AddRoad(const sf::Vector2i& tile_pos, Road::Type type, unsigned int orientation);

	void GenerateBuildingList();
	void CallBuildingList() const;

	void generateRoadList(const Camera& camera, const Resources& resources);
	void callRoadList() const;

	void GenerateTileList(const Camera& camera, const Resources& resources);
	void CallTileList() const;

	/*void DrawRoads(dfv::IntRect rect, const Camera& camera, const Resources& resources) const;*/
	void drawRoads(dfv::RealIntRect rect, const Camera& camera, const Resources& resources) const;
	//void DrawProps(dfv::IntRect rect, const Camera& camera, const Resources& resources) const;
	void drawProps(dfv::RealIntRect rect, const Camera& camera, const Resources& resources) const;
	void addProp(const unsigned int x, const unsigned int y, Prop* lp_prop);
	unsigned int GetRoadId(const sf::Vector2i& pos) const;
	unsigned int GetRoadOrientation(const sf::Vector2i& pos) const;
	bool SetRoadId(const sf::Vector2i& pos, unsigned int id);
	bool SetRoadOrientation(const sf::Vector2i& pos, unsigned int orientation);

	bool SaveAsSgmFormat(const std::string& filename) const;
	bool LoadFromSgmFormat(const std::string& filename);

	bool isWater(unsigned int x, unsigned int y) const;
	sf::Vector3f getNormal(unsigned int x, unsigned int y);

	bool clearRoad(unsigned int x, unsigned int y);
	bool buildRoad(unsigned int x, unsigned int y, unsigned int id, unsigned int orientation);
	bool clearBuilding(unsigned int x, unsigned int y);
	bool clearProp(unsigned int x, unsigned int y);
	sf::Vector2i getTileFromMapPos(sf::Vector3f map_pos) const;
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
};

} /* namespace dfv */
#endif /* MAP_H_ */
