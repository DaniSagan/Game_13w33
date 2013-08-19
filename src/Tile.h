/*
 * Tile.h
 *
 *  Created on: Aug 12, 2013
 *      Author: daniel
 */

#ifndef TILE_H_
#define TILE_H_


#include <SFML/Graphics.hpp>
#include <iostream>
#include "Building.h"
#include "Utils.h"
#include "Resources.h"
#include "Camera.h"
#include "Road.h"

namespace dfv
{

class Tile
{
public:
	Tile();
	virtual ~Tile();

	void Create(sf::Vector2f pos, float h0, float h1, float h2, float h3);
	void SetColor(sf::Color color);
	void Draw(const dfv::Camera& camera, const dfv::Resources& resources) const;
	void AddBuilding(float height);
	bool HasBuilding() const;
	void DrawBuilding(const bool draw_floors) const;
	sf::Color GetBuildingColor() const;
	void SetAsRoad(const bool r);
	bool IsRoad() const;
	float GetBuildingHeight() const;
	void AddRoad(dfv::Road::Type type, unsigned int orientation);
	Road::Type GetRoadType() const;
	unsigned int GetRoadOrientation() const;
	bool SetRoadType(Road::Type road_type);
	bool SetRoadOrientation(unsigned int road_orientation);

	sf::Vector3f GetVertex(const unsigned int index) const;
	std::vector<sf::Vector3f> GetVertices() const;

	void DrawBuildingBox() const;
	void DrawBuildingOutline() const;
	void DrawBuildingFloors() const;

	sf::Vector3f GetColor(unsigned int index) const;
	sf::Vector3f GetNormal(unsigned int index) const;
	sf::Vector3f GetBuildingColor3f() const;

	void SetVertex(const unsigned int index, const sf::Vector3f& vertex);
	sf::Color GetColor() const;
	void SetBuildingColor(const sf::Color& color);

private:
	std::vector<sf::Vector3f> vertices;
	std::vector<sf::Vector3f> normals;
	std::vector<sf::Vector3f> colors;
	sf::Vector3f color;
	dfv::Building* lp_building;
	bool is_road;
	dfv::Road* lp_road;
};

} /* namespace dfv */
#endif /* TILE_H_ */
