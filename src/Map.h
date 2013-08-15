/*
 * Map.h
 *
 *  Created on: Aug 11, 2013
 *      Author: daniel
 */

#ifndef MAP_H_
#define MAP_H_

#include <string>
#include <iostream>
#include <string>
#include <fstream>
#include "Camera.h"
#include "Tile.h"
#include "Resources.h"


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

private:
	unsigned int size;
	std::vector<std::vector<float> > heights;
	std::vector<std::vector<dfv::Tile*> > lp_tiles;
	//std::vector<std::vector<dfv::Cube*> > lp_cubes;
};

} /* namespace dfv */
#endif /* MAP_H_ */
