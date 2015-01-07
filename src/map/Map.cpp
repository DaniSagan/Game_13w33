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
}

Map::~Map()
{
	this->clear();
}

void Map::clear()
{
	cout << "clearing lots" << endl;
	for(size_t x = 0; x < this->size; x++)
	{
		for(size_t y = 0; y < this->size; y++)
		{
			this->clearLot(sf::Vector2i(x, y));
		}
	}
	cout << "clearing tiles" << endl;
	for(size_t x = 0; x < this->size; x++)
	{
		for(size_t y = 0; y < this->size; y++)
		{
			delete this->lp_tiles.at(x).at(y);
		}
	}
	this->lp_tiles.clear();
	this->size = 0;
}

void Map::clearLot(const sf::Vector2i& tileIndex)
{
	Lot* lpLot = this->lp_tiles.at(tileIndex.x).at(tileIndex.y)->getLot();
	if(lpLot != nullptr)
	{
		lpLot->clearStructures();
		for(const sf::Vector2i& tileIndex: lpLot->getTileIndices())
		{
			Tile& tile = *(this->lp_tiles.at(tileIndex.x).at(tileIndex.y));
			tile.setColor(Tile::randomGrassColor());
			tile.forgetLot();
		}
		delete lpLot;
	}
}

void Map::create(size_t size)
{
	cout << "Creating map of size " << size << endl;
	this->size = size;

	/*
	this->heights.resize(size + 1);
	for(std::size_t i = 0; i < this->heights.size(); i++)
	{
		this->heights[i].resize(size + 1);
		for(std::size_t j = 0; j < this->heights.size(); j++)
		{
			this->heights.at(i).at(j) = 0.f;
		}
	}*/

	/*this->lp_tiles.resize(size);
	for(std::size_t i = 0; i < this->lp_tiles.size(); i++)
	{
		this->lp_tiles.at(i).resize(size);
		for(std::size_t j = 0; j < this->lp_tiles.size(); j++)
		{
			this->lp_tiles.at(i).at(j) = nullptr;
		}
	}*/
	this->lp_tiles = vector<vector<Tile*>>(size, vector<Tile*>(size, nullptr));

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
			this->lp_tiles.at(i).at(j)->setColor(Tile::randomGrassColor());
		}
	}
}

size_t Map::getSize() const
{
	return this->size;
}

void Map::generateMapImg(const size_t tile_size)
{
	this->map_img.create(this->size * tile_size, this->size * tile_size, sf::Color(200,200,200));

	for(unsigned int i = 0; i < this->size; i++)
	{
		for(unsigned int j = 0; j < this->size; j++)
		{
			if(this->lp_tiles.at(i).at(j)->hasRoad())
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
			Tile* lp_tile = new Tile;
			lp_tile->create(
					sf::Vector2f(i, j),
					this->heightMap.at(i  , j  ),
					this->heightMap.at(i+1, j  ),
					this->heightMap.at(i+1, j+1),
					this->heightMap.at(i  , j+1));
			lp_tile->setColor(Tile::randomGrassColor());
			this->lp_tiles.at(i).at(j) = lp_tile;
		}
	}
	this->sky.create(1500, sf::Vector2f(this->size/2, this->size/2), "res/bg/bg.png");
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
	if(rect.trim(this->getTileRect()))
	{
		if(rect.xmin >= 0 && rect.xmax < static_cast<int>(this->size) &&
		   rect.ymin >= 0 && rect.ymax < static_cast<int>(this->size))
		{
			glBegin(GL_QUADS);
			glColor3f(0.65, 0.65, 0.65);
			for(int i = rect.xmin; i <= rect.xmax; i++)
			{
				for(int j = rect.ymin; j <= rect.ymax; j++)
				{
					Lot* lp_lot = this->getTile(i, j).getLot();
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
	}
}

void Map::drawStructureOutlines(dfv::RealIntRect rect) const
{
	if(rect.trim(this->getTileRect()))
	{
		glBegin(GL_QUADS);
		glColor3f(0.1, 0.1, 0.1);
		for(int i = rect.xmin; i <= rect.xmax; i++)
		{
			for(int j = rect.ymin; j <= rect.ymax; j++)
			{
				Lot* lp_lot = this->getTile(i, j).getLot();
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

void Map::generateRoadList(const Camera& camera, const Resources& resources)
{
	this->road_list = glGenLists(1);
	glNewList(this->road_list, GL_COMPILE);
	glBegin(GL_QUADS);
	for(unsigned int i = 0; i < this->size; i++)
	{
		for(unsigned int j = 0; j < this->size; j++)
		{
			if(this->lp_tiles.at(i).at(j)->hasRoad())
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

void Map::deleteLists()
{
	glDeleteLists(this->road_list, 1);
	glDeleteLists(this->tile_list, 1);
	glDeleteLists(this->structure_box_list, 1);
}

void Map::drawRoads(dfv::RealIntRect rect, const Camera& camera, const Resources& resources) const
{
	if(rect.trim(this->getTileRect()))
	{
		glColor3f(1.f, 1.f, 1.f);
		for(int i = floor(rect.xmin); i <= floor(rect.xmax); i++)
		{
			for(int j = floor(rect.ymin); j <= floor(rect.ymax); j++)
			{
				Tile& tile = this->getTile(i, j);
				if(tile.hasRoad())
				{
					tile.drawRoad(camera, resources);
				}
			}
		}
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void Map::drawProps(dfv::RealIntRect rect, const Camera& camera, const Resources& resources) const
{
	if(!rect.trim(this->getTileRect())) return;
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
			if(!this->getTile(i, j).hasLot() &&
			   !this->getTile(i, j).hasRoad() &&
			   !this->getTile(i, j).isBeach() &&
			   !this->getTile(i, j).isWater() &&
			   !this->getTile(i, j).hasProp() &&
			   this->getTile(i, j).getQuad().getMaxheight() < 9.f &&
			   this->getTile(i, j).getQuad().getMaxInclination() < 0.2f)
			{
				// add tile to the list of tiles for the lot
				tile_quads.push_back(this->getTile(i, j).getQuad());
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
			this->getTile(i, j).addLot(lp_new_lot);
			if(xmin != xmax || ymin != ymax)
			{
				this->lp_tiles.at(i).at(j)->setColor(sf::Color(180+(rand()%10), 180+(rand()%10), 180+(rand()%10)));
			}
		}
	}
	this->lpLots.push_back(lp_new_lot);

	return true;
}

Lot* Map::getLot(unsigned int x, unsigned int y) const
{
	//return this->lp_tiles.at(x).at(y)->lpLot;
	return this->getTile(x, y).getLot();
}

Tile& Map::getTile(int x, int y) const
{
	return this->getTile(sf::Vector2i(x, y));
}

Tile& Map::getTile(const sf::Vector2i& pos) const
{
	assert(this->contains(pos));
	return *(this->lp_tiles.at(pos.x).at(pos.y));
}

char Map::getRoadChar(const sf::Vector2i& pos) const
{
	if(!this->getTile(pos).hasRoad())
	{
		return ' ';
	}
	else
	{
		Road* lpRoad = this->getTile(pos).getRoad();
		return Road::asChar(lpRoad->getId(), lpRoad->getOrientation());
	}
}

vector<string> Map::getRoadPattern(const sf::Vector2i& pos, size_t radius) const
{
	vector<string> result;
	for(int y = pos.y + static_cast<int>(radius); y >= pos.y - static_cast<int>(radius); y--)
	{
		string s;
		for(int x = pos.x - static_cast<int>(radius); x <= pos.x + static_cast<int>(radius); x++)
		{
			if(this->contains(sf::Vector2i(x, y)))
			{
				s += this->getRoadChar(sf::Vector2i(x, y));
			}
			else
			{
				s += ' ';
			}
		}
		result.push_back(s);
	}
	return result;
}

bool Map::matchRoadPattern(sf::Vector2i pos, const string& pattern) const
{
	bool result = true;
	return result;
}

bool Map::contains(const sf::Vector2i& pos) const
{
	return pos.x >= 0 && pos.x < static_cast<int>(this->size) &&
		   pos.y >= 0 && pos.y < static_cast<int>(this->size);
}

bool Map::contains(int x, int y) const
{
	return this->contains(sf::Vector2i(x, y));
}

string Map::getName() const
{
	return this->name;
}

void Map::setName(const string& name)
{
	this->name = name;
}

void Map::deserialize(const string& filename)
{
	Serializer ser;
	ser.openInFile(filename);
	isRead(ser, *this);
}

string osString(size_t level, const string& name, const Map& map)
{
	stringstream ss;
	ss << strRepeat(level, string("\t")) << "Map " << name << " = {\n";
	ss << osString(level+1, "name", map.getName());
	ss << osString(level+1, "size", map.getSize());
	ss << osString(level+1, "tiles", map.lp_tiles, "Tile");
	ss << strRepeat(level, string("\t")) << "}\n";
	return ss.str();
}

ostream& operator<<(ostream& os, Map& map)
{
	os << osString(0, "map", map);
	return os;
}

bool isRead(Serializer& ser, Map& map)
{
	bool finished = false;
	while(!finished)
	{
		Serializer::Reading reading;
		Serializer::Reading::Position pos;
		pos = ser.read(reading);
		if(pos == Serializer::Reading::OBJECT_END)
		{
			finished = true;
		}
		else if(pos == Serializer::Reading::VALUE)
		{
			if(reading.name == "name")
			{
				string name;
				isRead(reading, name);
				map.setName(name);
			}
			else if(reading.name == "size")
			{
				size_t size;
				isRead(reading, size);
				map.create(size);
			}
		}
		else if(pos == Serializer::Reading::ARRAY_START)
		{
			if(reading.name == "tiles")
			{
				for(size_t i = 0; i < map.size; i++)
				{
					for(size_t j = 0; j < map.size; j++)
					{
						pos = ser.read(reading);
						assert(pos == Serializer::Reading::OBJECT_START);
						//cout << "Creating tile @" << i << "," << j << endl;
						Tile* lpTile = new Tile;
						isRead(ser, *lpTile);
						map.lp_tiles.at(i).at(j) = lpTile;
					}
				}
			}
		}
	}
	return true;
}

} /* namespace dfv */


