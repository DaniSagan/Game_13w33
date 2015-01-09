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

 * Tile.cpp
 *
 *  Created on: Aug 12, 2013
 *      Author: daniel
 */

#include "Tile.h"

namespace dfv
{

Tile::Tile():
		lpRoad(make_pair(false, nullptr)),
		lpProp(make_pair(false, nullptr)),
		lpLot(make_pair(false, nullptr))
{
}

Tile::~Tile()
{
	if(lpRoad.first) delete this->lpRoad.second;
}

void Tile::create(sf::Vector2f pos, float h0, float h1, float h2, float h3)
{
	this->vertices.resize(4);
	this->vertices.at(0) = sf::Vector3f(pos.x, pos.y, h0);
	this->vertices.at(1) = sf::Vector3f(pos.x + 1.0, pos.y, h1);
	this->vertices.at(2) = sf::Vector3f(pos.x + 1.0, pos.y + 1.0, h2);
	this->vertices.at(3) = sf::Vector3f(pos.x , pos.y + 1.0, h3);

	this->normals.resize(4);
	this->normals.at(0) = (this->vertices.at(1)-this->vertices.at(0)) ^ (this->vertices.at(3)-this->vertices.at(0));
	this->normals.at(1) = (this->vertices.at(2)-this->vertices.at(1)) ^ (this->vertices.at(0)-this->vertices.at(1));
	this->normals.at(2) = (this->vertices.at(3)-this->vertices.at(2)) ^ (this->vertices.at(1)-this->vertices.at(2));
	this->normals.at(3) = (this->vertices.at(0)-this->vertices.at(3)) ^ (this->vertices.at(2)-this->vertices.at(3));

	this->colors.resize(4);

}

void Tile::clear()
{

}

void Tile::setColor(sf::Color color)
{
	const float water_threshold = 0.f;
	const float sand_threshold = 0.1f;
	const float snow_threshold = 40.0f;

	for(size_t i = 0; i < 4; i++)
	{
		if(this->vertices.at(i).z < water_threshold)
		{
			this->colors.at(i) = Tile::randomWaterColor();
		}
		else if(this->vertices.at(i).z < sand_threshold)
		{
			this->colors.at(i) = Tile::randomSandColor();
		}
		else if(this->vertices.at(i).z > snow_threshold + static_cast<float>(rand() % 100)/10.f && !this->hasRoad())
		{
			this->colors.at(i) = Tile::randomSnowColor();
		}
		else
		{
			this->colors.at(i) = color;
		}
	}
}

void Tile::draw(const Camera& camera, const Resources& resources) const
{
	for(size_t k = 0; k < 4; k++)
	{
		glColor3ub(this->colors.at(k).r, this->colors.at(k).g, this->colors.at(k).b);
		glNormal3f(this->normals.at(k).x, this->normals.at(k).y, this->normals.at(k).z);
		glVertex3f(this->vertices.at(k).x, this->vertices.at(k).y, this->vertices.at(k).z);
	}
}

bool Tile::hasProp() const
{
	return this->lpProp.first;
}

bool Tile::hasRoad() const
{
	return this->lpRoad.first;
}

bool Tile::hasLot() const
{
	return this->lpLot.first;
}

void Tile::addRoad(Road::Type type, unsigned int orientation)
{
	if(this->lpRoad.first == true)
	{
		delete this->lpRoad.second;
	}
	this->lpRoad.second = new Road;
	this->lpRoad.second->create(this->vertices, type, orientation);
	this->setColor(sf::Color(32, 32, 32));
	this->lpRoad.first = true;
}

void Tile::addLot(Lot* lpLot)
{
	this->lpLot.first = true;
	this->lpLot.second = lpLot;
}

void Tile::addProp(Prop* lp_prop)
{
	this->lpProp.first = true;
	this->lpProp.second = lp_prop;
}

void Tile::addProp(Prop::Type type, unsigned int id)
{
	if(type == Prop::TREE)
	{
		Tree* lp_tree = new Tree();
		vector<sf::Vector3f> tile_vertices = this->getVertices();//this->map.getTileVertices(sf::Vector2i(x, y));
		lp_tree->create(tile_vertices, id);
		this->addProp(lp_tree);
	}
}

sf::Vector3f Tile::getVertex(const unsigned int index) const
{
	if(index < 4)
	{
		return this->vertices.at(index);
	}
	return this->vertices.back();
}

const std::vector<sf::Vector3f> & Tile::getVertices() const
{
	return this->vertices;
}

sf::Color Tile::getColor(unsigned int index) const
{
	return this->colors.at(index);
}

sf::Vector3f Tile::getNormal(unsigned int index) const
{
	return this->normals.at(index);
}

void Tile::setVertex(const unsigned int index, const sf::Vector3f& vertex)
{
	this->vertices.at(index) = vertex;
}

void Tile::drawRoad(const Camera& camera, const Resources& resources) const
{
	if(this->lpRoad.first)
	{
		this->lpRoad.second->draw(camera, resources);
	}
}

void Tile::drawProp(const Camera& camera, const Resources& resources) const
{
	if(this->lpProp.first)
	{
		this->lpProp.second->draw(camera, resources);
	}
}

bool Tile::isWater() const
{
	float threshold = 0.f;
	return (this->vertices[0].z < threshold ||
			this->vertices[1].z < threshold ||
			this->vertices[2].z < threshold ||
			this->vertices[3].z < threshold);
}

bool Tile::isBeach() const
{
	float threshold = 0.1f;
	return ((this->vertices[0].z < threshold ||
			 this->vertices[1].z < threshold ||
			 this->vertices[2].z < threshold ||
			 this->vertices[3].z < threshold) &&
			 !this->isWater());
}

bool Tile::clearRoad()
{
	if(this->lpRoad.first)
	{
		delete this->lpRoad.second;
		this->lpRoad.second = nullptr;
		this->setColor(sf::Color(10 + rand() % 20, 130 + rand() % 20, 10 + rand() % 20));
		return true;
	}
	else
	{
		return false;
	}

}

bool Tile::clearProp()
{
	std::cout << "Clearing prop" << std::endl;
	if(this->lpProp.first)
	{
		delete this->lpProp.second;
		this->lpProp.second = nullptr;
		this->setColor(sf::Color(10 + rand() % 20, 130 + rand() % 20, 10 + rand() % 20));
		return true;
	}
	else
	{
		return false;
	}
}

void Tile::forgetLot()
{
	this->lpLot.first = false;
	this->lpLot.second = nullptr;
}

Quad Tile::getQuad() const
{
	Quad res;
	res.create(this->vertices);
	return res;
}

Lot* Tile::getLot() const
{
	return this->lpLot.second;
}

Prop* Tile::getProp() const
{
	return this->lpProp.second;
}

Road* Tile::getRoad() const
{
	return this->lpRoad.second;
}

bool Tile::canBuildRoad() const
{
	return
	!this->isWater() &&
	!this->isBeach() &&
	this->getQuad().getMaxInclination() < 0.25f &&
    this->getQuad().getAvgHeight() < 9.f;
}

bool Tile::canHaveLot() const
{
	return
	!this->hasLot() &&
	!this->hasRoad() &&
	!this->isBeach() &&
	!this->isWater() &&
	!this->hasProp() &&
	this->getQuad().getMaxInclination() < 0.2f;
}

sf::Color Tile::randomGrassColor()
{
	return sf::Color(5 + rand() % 10, 40 + rand() % 10, 5 + rand() % 10);
}

sf::Color Tile::randomSnowColor()
{
	int rr = rand() % 25;
	return sf::Color(230-rr, 230-rr, 242-rr);
}

sf::Color Tile::randomSandColor()
{
	int rr1 = rand() % 25;
	int rr2 = rand() % 25;
	int rr3 = rand() % 25;
	return sf::Color(230 + rr1, 230 + rr2, 102 + rr3);
}

sf::Color Tile::randomWaterColor()
{
	int rr = rand() % 3;
	return sf::Color(12-rr, 12-rr, 64-rr);
}

sf::Color Tile::randomSidewalkColor()
{
	return sf::Color(180+(rand()%10), 180+(rand()%10), 180+(rand()%10));
}

string osString(size_t level, const string& name, const Tile& tile)
{
	stringstream ss;
	if(name.empty())
	{
		ss << strRepeat(level, string("\t")) << "{" << endl;
	}
	else
	{
		ss << strRepeat(level, string("\t")) << "Tile " << name << " = {" << endl;
	}
	ss << osString(level+1, "x", static_cast<int>(tile.vertices.at(0).x));
	ss << osString(level+1, "y", static_cast<int>(tile.vertices.at(0).y));
	ss << osString(level+1, "v0", tile.vertices.at(0));
	ss << osString(level+1, "v1", tile.vertices.at(1));
	ss << osString(level+1, "v2", tile.vertices.at(2));
	ss << osString(level+1, "v3", tile.vertices.at(3));
	if(tile.hasRoad())
	{
		ss << osString(level+1, "roadType", Road::asString(tile.getRoad()->getType()));
		ss << osString(level+1, "roadOrientation", tile.getRoad()->getOrientation());
	}
	if(tile.hasProp())
	{
		if(tile.getProp()->getType() == Prop::TREE)
		{
			Tree* lpTree = static_cast<Tree*>(tile.getProp());
			ss << osString(level+1, "propType", Prop::asString(lpTree->getType()));
			ss << osString(level+1, "propId", lpTree->getId());
		}
	}
	ss << strRepeat(level, string("\t")) << "}" << endl;
	return ss.str();
}

string osString(size_t level, const string& name, const Tile* lpTile)
{
	return osString(level, name, *lpTile);
}

string osString(size_t level, const string& name, const vector<vector<Tile*>>& lpTiles, const string& type)
{
	stringstream ss;
	ss << strRepeat(level, "\t") << type << "[" << lpTiles.size() << "," << lpTiles.at(0).size() << "] " << name << " = [" << "\n";
	for(const vector<Tile*>& v: lpTiles)
	{
		for(Tile* lpTile: v)
		{
			ss << osString(level+1, string(""), *lpTile);
		}
	}
	ss << strRepeat(level, "\t") << "]\n";
	return ss.str();
}

bool isRead(Serializer& ser, Tile& tile)
{
	sf::Vector2i id;
	vector<sf::Vector3f> vs(4);
	Road::Type roadType = Road::none;
	unsigned int roadOrientation;
	Prop::Type propType = Prop::NONE;
	unsigned int propId;

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
			if(reading.name == "x")
			{
				int x;
				isRead(reading, x);
				id.x = x;
			}
			else if(reading.name == "y")
			{
				int y;
				isRead(reading, y);
				id.y = y;
			}
			else if(reading.name == "v0")
			{
				sf::Vector3f v;
				isRead(reading, v);
				vs.at(0) = v;
			}
			else if(reading.name == "v1")
			{
				sf::Vector3f v;
				isRead(reading, v);
				vs.at(1) = v;
			}
			else if(reading.name == "v2")
			{
				sf::Vector3f v;
				isRead(reading, v);
				vs.at(2) = v;
			}
			else if(reading.name == "v3")
			{
				sf::Vector3f v;
				isRead(reading, v);
				vs.at(3) = v;
			}
			else if(reading.name == "roadType")
			{
				string str;
				isRead(reading, str);
				roadType = Road::fromString(str);
			}
			else if(reading.name == "roadOrientation")
			{
				isRead(reading, roadOrientation);
			}
			else if(reading.name == "propType")
			{
				string str;
				isRead(reading, str);
				propType = Prop::fromString(str);
			}
			else if(reading.name == "propId")
			{
				isRead(reading, propId);
			}
		}
	}
	tile.create(sf::Vector2f(id.x, id.y), vs.at(0).z, vs.at(1).z, vs.at(2).z, vs.at(3).z);
	tile.setColor(Tile::randomGrassColor());
	if(roadType != Road::none)
	{
		tile.addRoad(roadType, roadOrientation);
	}
	if(propType != Prop::NONE)
	{
		tile.addProp(propType, propId);
	}
	return true;
}

} /* namespace dfv */


