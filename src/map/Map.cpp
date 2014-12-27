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

 * Map.cpp
 *
 *  Created on: Aug 11, 2013
 *      Author: daniel
 */

#include "Map.h"

namespace dfv
{

Map::Map():
		size(0),
		tile_list(0),
		population(0)
{
	// TODO Auto-generated constructor stub

}

Map::~Map()
{
	for(std::size_t i = 0; i < this->lp_tiles.size(); i++)
	{
		for(std::size_t j = 0; j < this->lp_tiles.size(); j++)
		{
			delete this->lp_tiles.at(i).at(j);
		}
	}
}

void Map::create(unsigned int size)
{
	this->size = size;

	this->heights.resize(size + 1);
	for(std::size_t i = 0; i < this->heights.size(); i++)
	{
		this->heights[i].resize(size + 1);
		for(std::size_t j = 0; j < this->heights.size(); j++)
		{
			this->heights.at(i).at(j) = 0.f;
		}
	}

	this->lp_tiles.resize(size);
	for(std::size_t i = 0; i < this->lp_tiles.size(); i++)
	{
		this->lp_tiles.at(i).resize(size + 1);
		for(std::size_t j = 0; j < this->lp_tiles.size(); j++)
		{
			this->lp_tiles.at(i).at(j) = NULL;
		}
	}

	this->sky.create(2000, sf::Vector2f(this->size/2, this->size/2), "res/bg/bg.png");
}

void Map::generateTiles()
{
	for(unsigned int i = 0; i < this->lp_tiles.size(); i++)
	{
		for(unsigned int j = 0; j < this->lp_tiles.size(); j++)
		{
			this->lp_tiles.at(i).at(j) = new Tile;
			this->lp_tiles.at(i).at(j)->create(
					sf::Vector2f(i, j),
					this->heights.at(i).at(j),
					this->heights.at(i+1).at(j),
					this->heights.at(i+1).at(j+1),
					this->heights.at(i).at(j+1));
			this->lp_tiles.at(i).at(j)->setColor(sf::Color(10 + rand() % 20, 130 + rand() % 20, 10 + rand() % 20));
		}
	}
}

void Map::createRandom(const unsigned int size)
{
	this->size = size;

	// Create height data
	this->heights.resize(size + 1);
	for(unsigned int i = 0; i < size + 1; i++)
	{
		this->heights[i].resize(size + 1);
		for(unsigned int j = 0; j < size + 1; j++)
		{
			float x = (float)i - (float)(size + 1)/2.0;
			float y = (float)j - (float)(size + 1)/2.0;
			float x1 = x + 300;
			float y1 = y + 300;
			float x2 = x - 200;
			float y2 = y - 400;
			this->heights[i][j] = 5.0 * (2.0 * pow(sin(0.01 * sqrt(pow(x - 50, 2.0) + pow(y - 50, 2.0))), 4.0) -
										  0.9 * pow(sin(0.02 * sqrt(pow(x1, 2.0) + pow(y1, 2.0))), 2.0) -
										  0.3 * pow(sin(0.04 * sqrt(pow(x2, 2.0) + pow(y2, 2.0))), 2.0) +
										  0.1 * pow(sin(0.1 * sqrt(pow(x2, 2.0) + pow(y2, 2.0))), 2.0) +
										  0.1 * pow((sin(0.1* x) + sin(0.1*y)), 2.0) +
										  0.05 * pow((sin(0.23* x + 89.0) + sin(0.345*y - 123.0)), 2.0) +
										  0.03 * pow((sin(0.32* x - 121.3) + sin(0.4*y + 57.56)), 2.0) +
										  0.01 * pow((sin(0.41* x - 11.0) + sin(0.52*y + 570.0)), 2.0));
			this->heights[i][j] = 0.1 * pow(this->heights[i][j], 2) + 0.80f;
			if(this->heights[i][j] < 1.0)
			{
				this->heights[i][j] = 0.99;
			}
		}
	}

	// Create tile data
	this->lp_tiles.resize(size);
	int building_count = 0;
	for(unsigned int i = 0; i < size; i++)
	{
		this->lp_tiles[i].resize(size);
		for(unsigned int j = 0; j < size; j++)
		{
			float x = (float)i - (float)(size + 1)/2.0;
			float y = (float)j - (float)(size + 1)/2.0;

			dfv::Tile* lp_tile = new Tile;
			lp_tile->create(
					sf::Vector2f(i, j),
					this->heights[i][j],
					this->heights[i+1][j],
					this->heights[i+1][j+1],
					this->heights[i][j+1]);
			lp_tile->setColor(sf::Color(10 + rand() % 20, 80 + rand() % 20, 10 + rand() % 20));
			this->lp_tiles[i][j] = lp_tile;

			// If it's a beach
			if(this->heights[i][j] < 1.1f &&
			   this->heights[i+1][j] < 1.1f &&
			   this->heights[i+1][j+1] < 1.1f &&
			   this->heights[i][j+1] < 1.1f)
			{
				// beach
				this->lp_tiles[i][j]->setColor(sf::Color(220 + rand() % 10, 220 + rand() % 10, 120 + rand() % 10));
			}
		}
	}
	this->sky.create(1500, sf::Vector2f(this->size/2, this->size/2), "res/bg/bg.png");
}

void Map::createFlat(const unsigned int size, float height)
{
	this->size = size;

	// Create height data
	this->heights.resize(size + 1);
	for(unsigned int i = 0; i < size + 1; i++)
	{
		this->heights.at(i).resize(size + 1);
		for(unsigned int j = 0; j < size + 1; j++)
		{
			this->heights.at(i).at(j) = height;
		}
	}

	// Create tile data
	this->lp_tiles.resize(size);
	int building_count = 0;
	for(unsigned int i = 0; i < size; i++)
	{
		this->lp_tiles[i].resize(size);
		for(unsigned int j = 0; j < size; j++)
		{
			float x = (float)i - (float)(size + 1)/2.0;
			float y = (float)j - (float)(size + 1)/2.0;

			dfv::Tile* lp_tile = new Tile;
			lp_tile->create(
					sf::Vector2f(i, j),
					this->heights[i][j],
					this->heights[i+1][j],
					this->heights[i+1][j+1],
					this->heights[i][j+1]);
			lp_tile->setColor(sf::Color(13 + rand() % 20, 115 + rand() % 20, 13 + rand() % 20));
			this->lp_tiles[i][j] = lp_tile;

			// If it's a beach
			if(this->heights[i][j] < 1.1f &&
			   this->heights[i+1][j] < 1.1f &&
			   this->heights[i+1][j+1] < 1.1f &&
			   this->heights[i][j+1] < 1.1f)
			{
				// beach
				this->lp_tiles[i][j]->setColor(sf::Color(220 + rand() % 10, 220 + rand() % 10, 120 + rand() % 10));
			}
		}
	}
	this->sky.create(1500, sf::Vector2f(this->size/2, this->size/2), "res/bg/bg.png");
}

void Map::createValley(const unsigned int size, const float a, const float b)
{
	this->size = size;

	// Create height data
	this->heights.resize(size + 1);
	for(unsigned int i = 0; i < size + 1; i++)
	{
		this->heights.at(i).resize(size + 1);
		for(unsigned int j = 0; j < size + 1; j++)
		{
			float x = float(i)-float(size/2);
			this->heights.at(i).at(j) = a*sqrt(1.f + (x*x)/(b*b));
		}
	}

	// Create tile data
	this->lp_tiles.resize(size);
	int building_count = 0;
	for(unsigned int i = 0; i < size; i++)
	{
		this->lp_tiles[i].resize(size);
		for(unsigned int j = 0; j < size; j++)
		{
			float x = (float)i - (float)(size + 1)/2.0;
			float y = (float)j - (float)(size + 1)/2.0;

			dfv::Tile* lp_tile = new Tile;
			lp_tile->create(
					sf::Vector2f(i, j),
					this->heights[i][j],
					this->heights[i+1][j],
					this->heights[i+1][j+1],
					this->heights[i][j+1]);
			lp_tile->setColor(sf::Color(13 + rand() % 20, 115 + rand() % 20, 13 + rand() % 20));
			this->lp_tiles[i][j] = lp_tile;

			// If it's a beach
			if(this->heights[i][j] < 1.1f &&
			   this->heights[i+1][j] < 1.1f &&
			   this->heights[i+1][j+1] < 1.1f &&
			   this->heights[i][j+1] < 1.1f)
			{
				// beach
				this->lp_tiles[i][j]->setColor(sf::Color(220 + rand() % 10, 220 + rand() % 10, 120 + rand() % 10));
			}
		}
	}
	this->sky.create(1500, sf::Vector2f(this->size/2, this->size/2), "res/bg/bg.png");
}

unsigned int Map::getSize() const
{
	return this->size;
}

float Map::getTileHeight(int x, int y)
{
	if(x < 0) x = 0;
	if(x >= (int)this->size) x = this->size - 1;
	if(y < 0) y = 0;
	if(y >= (int)this->size) y = this->size - 1;

	return this->heights[x][y];
}

void Map::generateMapImg(const unsigned int tile_size)
{

	this->map_img.create(this->size * tile_size, this->size * tile_size, sf::Color(200,200,200));

	for(unsigned int i = 0; i < this->size; i++)
	{
		for(unsigned int j = 0; j < this->size; j++)
		{
			if(this->lp_tiles[i][j]->isRoad())
			{
				dfv::Utils::drawRectangle(this->map_img, sf::Vector2i(i*tile_size, j*tile_size), sf::Vector2i((i+1)*tile_size- 1, (j+1)*tile_size - 1), sf::Color(50, 50, 50));
			}
		}
	}

	this->map_img.saveToFile("res/map/map_img.png");
}

void Map::loadHeightMap(const string& filename, size_t smoothingCount)
{
	this->heightMap.load(filename);
	for(size_t k = 0; k < smoothingCount; k++)
	{
		this->heightMap.smooth();
	}
	this->size = this->heightMap.size() - 1;
	// Create tile data
	this->lp_tiles.resize(this->size);
	for(size_t i = 0; i < this->size; i++)
	{
		this->lp_tiles.at(i).resize(this->size);
		for(size_t j = 0; j < this->size; j++)
		{
			float x = (float)i - (float)(this->size + 1)/2.0;
			float y = (float)j - (float)(this->size + 1)/2.0;

			dfv::Tile* lp_tile = new Tile;
			lp_tile->create(
					sf::Vector2f(i, j),
					this->heightMap.at(i  , j  ),
					this->heightMap.at(i+1, j  ),
					this->heightMap.at(i+1, j+1),
					this->heightMap.at(i  , j+1));
			lp_tile->setColor(sf::Color(5 + rand() % 10, 40 + rand() % 10, 5 + rand() % 10));
			this->lp_tiles.at(i).at(j) = lp_tile;

			// If it's a beach
			if(this->heightMap.at(i  , j  ) < 0.1f &&
			   this->heightMap.at(i+1, j  ) < 0.1f &&
			   this->heightMap.at(i+1, j+1) < 0.1f &&
			   this->heightMap.at(i  , j+1) < 0.1f)
			{
				// beach
				this->lp_tiles.at(i).at(j)->setColor(sf::Color(220 + rand() % 10, 220 + rand() % 10, 120 + rand() % 10));
			}
		}
	}
	this->sky.create(1500, sf::Vector2f(this->size/2, this->size/2), "res/bg/bg.png");
}

bool Map::isRoad(unsigned int x, unsigned int y) const
{
	if(x >= 0 && x < this->size &&
	   y >= 0 && y < this->size)
	{
		return this->lp_tiles.at(x).at(y)->isRoad();
	}
	else
	{
		return false;
	}
}

bool Map::changeRoadType(const sf::Vector2i& tile_pos)
{
	if(this->isRoad(tile_pos.x, tile_pos.y))
	{
		const unsigned int road_type = this->lp_tiles[tile_pos.x][tile_pos.y]->getRoadId();
		if(road_type >= Road::count - 1)
		{
			this->lp_tiles[tile_pos.x][tile_pos.y]->setRoadId(Road::straight);
		}
		else
		{
			this->lp_tiles[tile_pos.x][tile_pos.y]->setRoadId((Road::Type)(road_type + 1));
		}
		return true;
	}
	else
	{
		return false;
	}
}

bool Map::changeRoadOrientation(const sf::Vector2i& tile_pos)
{
	std::cout << "Changing road orientation" << std::endl;
	if(this->isRoad(tile_pos.x, tile_pos.y))
	{
		std::cout << "Is road" << std::endl;
		const unsigned int road_orientation = this->lp_tiles[tile_pos.x][tile_pos.y]->getRoadOrientation();
		if(road_orientation >= 4)
		{
			this->lp_tiles[tile_pos.x][tile_pos.y]->setRoadOrientation(0);
			std::cout << "Road orient set to 0" << std::endl;
		}
		else
		{
			this->lp_tiles[tile_pos.x][tile_pos.y]->setRoadOrientation(road_orientation + 1);
			std::cout << "Road orient set to " << road_orientation + 1 << std::endl;
		}
		return true;
	}
	else
	{
		return false;
	}
}

sf::Vector3f Map::getMapPosFromMouse(sf::Vector2i mouse_pos)
{
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat win_x, win_y, win_z;
	GLdouble pos_x, pos_y, pos_z;

	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);

	win_x = (float)mouse_pos.x;
	win_y = (float)viewport[3] - (float)mouse_pos.y;
	glReadPixels(mouse_pos.x, int(win_y), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &win_z);
	gluUnProject(win_x, win_y, win_z, modelview, projection, viewport, &pos_x, &pos_y, &pos_z);

	return sf::Vector3f(pos_x, pos_y, pos_z);
}

sf::Vector3f Map::getViewPos(sf::Vector3f map_pos, const sf::Window& window) const
{
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLdouble win_x, win_y, win_z;
	GLdouble pos_x, pos_y, pos_z;

	pos_x = (double)map_pos.x;
	pos_y = (double)map_pos.y;
	pos_z = (double)map_pos.z;

	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);
	gluProject(pos_x, pos_y, pos_z, modelview, projection, viewport, &win_x, &win_y, &win_z);

	return sf::Vector3f((float)win_x, viewport[3] - (float)win_y, (float)win_z);
}

const std::vector<sf::Vector3f> & Map::getTileVertices(sf::Vector2i pos) const
{
	return this->lp_tiles.at(pos.x).at(pos.y)->getVertices();
}

void Map::drawTiles(dfv::RealIntRect rect, const Camera& camera, const Resources& resources) const
{
	rect.trim(this->getTileRect());
	glBegin(GL_QUADS);
	for(int i = rect.xmin; i <= rect.xmax; i++)
	{
		for(int j = rect.ymin; j <= rect.ymax; j++)
		{
			this->lp_tiles.at(i).at(j)->draw(camera, resources);
		}
	}
	glEnd();
}

void Map::drawStructureBoxes(dfv::RealIntRect rect) const
{
	rect.trim(this->getTileRect());
	glBegin(GL_QUADS);
	glColor3f(0.65, 0.65, 0.65);
	for(int i = rect.xmin; i <= rect.xmax; i++)
	{
		for(int j = rect.ymin; j <= rect.ymax; j++)
		{
			Lot* lp_lot = this->lp_tiles.at(i).at(j)->lp_lot;
			if(lp_lot != NULL)
			{
				if(lp_lot->getOriginTileIndices() == sf::Vector2i(i, j))
				{
					lp_lot->drawStructureBoxes();
				}
			}
		}
	}
	glEnd();
}

void Map::drawStructureOutlines(dfv::RealIntRect rect) const
{
	rect.trim(this->getTileRect());
	glBegin(GL_QUADS);
	glColor3f(0.1, 0.1, 0.1);
	for(int i = rect.xmin; i <= rect.xmax; i++)
	{
		for(int j = rect.ymin; j <= rect.ymax; j++)
		{
			Lot* lp_lot = this->lp_tiles.at(i).at(j)->lp_lot;
			if(lp_lot != NULL)
			{
				if(lp_lot->getOriginTileIndices() == sf::Vector2i(i, j))
				{
					lp_lot->drawStructureOutlines();
				}
			}
		}
	}
	glEnd();
}

float Map::getHeight(const sf::Vector2f& pos) const
{
	if(pos.x >= 0 && pos.x < this->size && pos.y >= 0 && pos.y < this->size)
	{
		float x0 = floor(pos.x);
		float x1 = floor(pos.x) + 1;
		float y0 = floor(pos.y);
		float y1 = floor(pos.y) + 1;

		Tile* lp_tile = this->lp_tiles.at(floor(pos.x)).at(floor(pos.y));
		float h00 = lp_tile->getVertex(0).z;
		float h10 = lp_tile->getVertex(1).z;
		float h11 = lp_tile->getVertex(2).z;
		float h01 = lp_tile->getVertex(3).z;

		return Utils::interpolate2d(x0, x1, y0, y1, h00, h01, h10, h11, pos.x, pos.y);
	}
	return 0;
}

dfv::RealRect Map::getRect() const
{
	return dfv::RealRect(0, this->size, 0, this->size);
}

dfv::RealIntRect Map::getTileRect() const
{
	return dfv::RealIntRect(0, (int)this->size - 1, 0, (int)this->size - 1);
}

void Map::drawSky() const
{
	this->sky.draw();
}

void Map::setLight(const sf::Vector3f& position) const
{
	GLfloat light_position[] = { position.x, position.y, position.z, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	GLfloat light_position_1[] = { -position.x, position.y, position.z, 0.0 };
	glLightfv(GL_LIGHT1, GL_POSITION, light_position_1);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
}

bool Map::addRoad(const sf::Vector2i& tile_pos, Road::Type type, unsigned int orientation)
{
	if(tile_pos.x >= 0 && tile_pos.x < (int)this->size &&
			tile_pos.y >= 0 && tile_pos.y < (int)this->size)
	{
		this->lp_tiles.at(tile_pos.x).at(tile_pos.y)->addRoad(type, orientation);
		return true;
	}
	else
	{
		return false;
	}
}

void Map::generateRoadList(const Camera& camera, const Resources& resources)
{
	this->road_list = glGenLists(1);
	glNewList(this->road_list, GL_COMPILE);
	glBegin(GL_QUADS);
	for(unsigned int i = 0; i < this->size; i++)
	{
		for(unsigned int j = 0; j < this->size; j++)
		{
			if(this->lp_tiles.at(i).at(j)->isRoad())
			{
				this->lp_tiles.at(i).at(j)->drawRoad(camera, resources);
			}
		}
	}
	glEnd();
	glEndList();
}

void Map::callRoadList() const
{
	glCallList(this->road_list);
}

void Map::generateTileList(const Camera& camera, const Resources& resources)
{
	this->tile_list = glGenLists(1);
	glNewList(this->tile_list, GL_COMPILE);
	this->drawTiles(this->getTileRect(), camera, resources);
	glEndList();
}

void Map::callTileList() const
{
	glCallList(this->tile_list);
}

void Map::generateStructureBoxList(const Camera& camera, const Resources& resources)
{
	this->structure_box_list = glGenLists(1);
	glNewList(this->structure_box_list, GL_COMPILE);
	this->drawStructureBoxes(this->getTileRect());
	glEndList();
}

void Map::callStructureBoxList() const
{
	glCallList(this->structure_box_list);
}

void Map::drawRoads(dfv::RealIntRect rect, const Camera& camera, const Resources& resources) const
{
	rect.trim(this->getTileRect());
	glColor3f(1.f, 1.f, 1.f);
	for(int i = floor(rect.xmin); i <= floor(rect.xmax); i++)
	{
		for(int j = floor(rect.ymin); j <= floor(rect.ymax); j++)
		{
			this->lp_tiles.at(i).at(j)->drawRoad(camera, resources);
		}
	}
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Map::drawProps(dfv::RealIntRect rect, const Camera& camera, const Resources& resources) const
{
	rect.trim(this->getTileRect());
	unsigned int quadrant = camera.getQuadrant();

	if(quadrant == 0)
	{
		int midpoint = camera.getPosition().y;
		if(midpoint < 0) midpoint = 0;
		if(midpoint >= int(this->size)) midpoint = this->size - 1;
		for(int i = floor(rect.xmax); i > floor(rect.xmin); i--)
		{
			for(int j = floor(rect.ymin); j < midpoint; j++)
			{
				this->lp_tiles.at(i).at(j)->drawProp(camera, resources);
			}
			for(int j = floor(rect.ymax); j >= midpoint; j--)
			{
				this->lp_tiles.at(i).at(j)->drawProp(camera, resources);
			}
		}
	}
	else if(quadrant == 1)
	{
		// TODO fix props not rendering when x > 650
		int midpoint = camera.getPosition().x;
		if(midpoint < 0) midpoint = 0;
		if(midpoint >= int(this->size)) midpoint = this->size - 1;
		for(int j = floor(rect.ymax); j > floor(rect.ymin); j--)
		{
			for(int i = floor(rect.xmin); i < midpoint; i++)
			{
				this->lp_tiles.at(i).at(j)->drawProp(camera, resources);
			}
			for(int i = floor(rect.xmax); i >= midpoint; i--)
			{
				this->lp_tiles.at(i).at(j)->drawProp(camera, resources);
			}
		}
	}
	else if(quadrant == 2)
	{
		int midpoint = camera.getPosition().y;
		if(midpoint < 0) midpoint = 0;
		if(midpoint >= int(this->size)) midpoint = this->size - 1;
		for(int i = floor(rect.xmin); i <= floor(rect.xmax); i++)
		{
			for(int j = floor(rect.ymin); j < midpoint; j++)
			{
				this->lp_tiles.at(i).at(j)->drawProp(camera, resources);
			}
			for(int j = floor(rect.ymax); j >= midpoint; j--)
			{
				this->lp_tiles.at(i).at(j)->drawProp(camera, resources);
			}
		}
	}
	else if(quadrant == 3)
	{
		int midpoint = camera.getPosition().x;
		if(midpoint < 0) midpoint = 0;
		if(midpoint >= int(this->size)) midpoint = this->size - 1;
		for(unsigned int j = floor(rect.ymin); j <= floor(rect.ymax); j++)
		{
			for(int i = floor(rect.xmin); i < midpoint; i++)
			{
				this->lp_tiles.at(i).at(j)->drawProp(camera, resources);
			}
			for(int i = floor(rect.xmax); i >= midpoint; i--)
			{
				this->lp_tiles.at(i).at(j)->drawProp(camera, resources);
			}
		}
	}
}

void Map::addProp(const unsigned int x, const unsigned int y, Prop* lp_prop)
{
	this->lp_tiles.at(x).at(y)->addProp(lp_prop);
}

bool Map::hasProp(const unsigned int x, const unsigned int y) const
{
	return this->lp_tiles.at(x).at(y)->hasProp();
}

unsigned int Map::getRoadId(const sf::Vector2i& pos) const
{
	return this->lp_tiles[pos.x][pos.y]->getRoadId();
}

unsigned int Map::getRoadOrientation(const sf::Vector2i& pos) const
{
	return this->lp_tiles[pos.x][pos.y]->getRoadOrientation();
}

bool Map::setRoadId(const sf::Vector2i& pos, unsigned int id)
{
	if(pos.x >= 0 && pos.x < int(this->size) &&
	   pos.y >= 0 && pos.y < int(this->size))
	{
		return this->lp_tiles[pos.x][pos.y]->setRoadId(id);
	}
	else
	{
		return false;
	}
}

bool Map::setRoadOrientation(const sf::Vector2i& pos, unsigned int orientation)
{
	if(this->getTileRect().contains(pos))
	{
		return this->lp_tiles[pos.x][pos.y]->setRoadOrientation(orientation);
	}
	else
	{
		return false;
	}
}

bool Map::isWater(unsigned int x, unsigned int y) const
{
	return this->lp_tiles.at(x).at(y)->isWater();
}

bool Map::isBeach(unsigned int x, unsigned int y) const
{
	return this->lp_tiles.at(x).at(y)->isBeach();
}

sf::Vector3f Map::getNormal(unsigned int x, unsigned int y)
{
	if(x >= 0 && x < this->size &&
	   y >= 0 && y < this->size)
	{
		std::vector<sf::Vector3f> vertices;
		vertices = this->getTileVertices(sf::Vector2i(x, y));
		sf::Vector3f v = Utils::cross(vertices[1]-vertices[0], vertices[3]-vertices[0]);
		float len = sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
		return sf::Vector3f(v.x/len, v.y/len, v.z/len);
	}
	else
	{
		return sf::Vector3f(0.0, 0.0, 1.0);
	}
}

bool Map::clearRoad(unsigned int x, unsigned int y)
{
	try
	{
		return this->lp_tiles.at(x).at(y)->clearRoad();
	}
	catch(...)
	{
		return false;
	}
}

bool Map::buildRoad(unsigned int x, unsigned int y, unsigned int id, unsigned int orientation)
{
	if(!this->lp_tiles[x][y]->isRoad())
	{
		unsigned int rr = rand() % 5;
		this->lp_tiles[x][y]->setColor(sf::Color(50 + rr, 50 + rr, 50 + rr));
		Road::Type road_type;
		switch(id)
		{
		case 0: road_type = Road::straight; 	break;
		case 1: road_type = Road::cross; 		break;
		case 2: road_type = Road::tcross; 		break;
		case 3:	road_type = Road::curve; 		break;
		case 4:	road_type = Road::av_straight; 	break;
		case 5:	road_type = Road::av_cross; 	break;
		case 6:	road_type = Road::av_tcross; 	break;
		}
		this->lp_tiles[x][y]->addRoad(road_type, orientation);
		return true;
	}
	return false;
}

bool Map::clearProp(unsigned int x, unsigned int y)
{
	try
	{
		return this->lp_tiles.at(x).at(y)->clearProp();
	}
	catch(...)
	{
		return false;
	}
}

sf::Vector2i Map::getTileFromMapPos(sf::Vector3f map_pos) const
{
	return sf::Vector2i(floor(map_pos.x), floor(map_pos.y));
}

void Map::addStructure(const unsigned int x, const unsigned int y,
			           Quad base, const unsigned int floor_count)
{
	this->lp_tiles.at(x).at(y)->createStructure(base, floor_count);
}

bool Map::hasStructure(const unsigned int x, const unsigned int y) const
{
	if(x >= 0 && x < this->size &&
	   y >= 0 && y < this->size)
	{
		return this->lp_tiles.at(x).at(y)->hasStructure();
	}
	else
	{
		return false;
	}
}

float Map::getAvgHeight(const unsigned int x, const unsigned int y) const
{
	return this->lp_tiles.at(x).at(y)->getQuad().getAvgHeight();
}

float Map::getMaxInclination(const unsigned int x, const unsigned int y) const
{
	return this->lp_tiles.at(x).at(y)->getQuad().getMaxInclination();
}

bool Map::addLot(unsigned int xmin, unsigned int ymin, unsigned int xmax,
		unsigned int ymax)
{
	// check map boundaries
	if(xmin < 0 || xmax >= this->getSize() ||
	   ymin < 0 || ymax >= this->getSize())
	{
		return false;
	}

	// Check if any tile in the region is assigned already to a lot or a road
	std::vector<Quad> tile_quads;
	std::vector<sf::Vector2i> tile_indices;
	for(unsigned int j = ymin; j <= ymax; j++)
	{
		for(unsigned int i = xmin; i <= xmax; i++)
		{
			if(this->lp_tiles.at(i).at(j)->lp_lot == NULL &&
			   this->lp_tiles.at(i).at(j)->lp_road == NULL &&
			   !this->lp_tiles.at(i).at(j)->isBeach() &&
			   !this->lp_tiles.at(i).at(j)->isWater() &&
			   this->lp_tiles.at(i).at(j)->lp_prop == NULL &&
			   this->lp_tiles.at(i).at(j)->getQuad().getMaxheight() < 9.f &&
			   this->lp_tiles.at(i).at(j)->getQuad().getMaxInclination() < 0.2f)
			{
				// add tile to the list of tiles for the lot
				tile_quads.push_back(this->lp_tiles.at(i).at(j)->getQuad());
				tile_indices.push_back(sf::Vector2i(i, j));
			}
			else
			{
				// if a tile is assigned to a lot then return
				// without creating the lot
				return false;
			}
		}
	}

	// everything is fine, we can create the lot
	Lot* lp_new_lot = new Lot(tile_indices, tile_quads, tile_quads.at(0).getVertex(0));
	for(unsigned int j = ymin; j <= ymax; j++)
	{
		for(unsigned int i = xmin; i <= xmax; i++)
		{
			// each tile has a pointer to the lot
			this->lp_tiles.at(i).at(j)->lp_lot = lp_new_lot;
			this->lp_tiles.at(i).at(j)->setColor(sf::Color(180+(rand()%10), 180+(rand()%10), 180+(rand()%10)));
		}
	}

	return true;
}

Lot* Map::getLot(unsigned int x, unsigned int y) const
{
	return this->lp_tiles.at(x).at(y)->lp_lot;
}

const Tile& Map::getTile(size_t x, size_t y) const
{
	return *(this->lp_tiles.at(x).at(y));
}

} /* namespace dfv */


