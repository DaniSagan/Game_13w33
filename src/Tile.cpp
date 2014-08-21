/*
 * Tile.cpp
 *
 *  Created on: Aug 12, 2013
 *      Author: daniel
 */

#include "Tile.h"

namespace dfv
{

Tile::Tile():
		lp_building(NULL),
		is_road(false),
		lp_road(NULL),
		lp_prop(NULL)
{
	// TODO Auto-generated constructor stub

}

Tile::~Tile()
{
	if(lp_building != NULL) delete this->lp_building;
	if(lp_road != NULL) delete this->lp_road;
}

void Tile::create(sf::Vector2f pos, float h0, float h1, float h2, float h3)
{
	this->vertices.resize(4);
	this->vertices[0] = sf::Vector3f(pos.x, pos.y, h0);
	this->vertices[1] = sf::Vector3f(pos.x + 1.0, pos.y, h1);
	this->vertices[2] = sf::Vector3f(pos.x + 1.0, pos.y + 1.0, h2);
	this->vertices[3] = sf::Vector3f(pos.x , pos.y + 1.0, h3);

	this->normals.resize(4);
	this->normals[0] = dfv::Utils::cross(
			dfv::Utils::diff(this->vertices[1], this->vertices[0]),
			dfv::Utils::diff(this->vertices[3], this->vertices[0]));
	this->normals[1] = dfv::Utils::cross(
			dfv::Utils::diff(this->vertices[2], this->vertices[1]),
			dfv::Utils::diff(this->vertices[0], this->vertices[1]));
	this->normals[2] = dfv::Utils::cross(
			dfv::Utils::diff(this->vertices[3], this->vertices[2]),
			dfv::Utils::diff(this->vertices[1], this->vertices[2]));
	this->normals[3] = dfv::Utils::cross(
			dfv::Utils::diff(this->vertices[0], this->vertices[3]),
			dfv::Utils::diff(this->vertices[2], this->vertices[3]));

	this->colors.resize(4);

}

void Tile::setColor(sf::Color color)
{
	this->color.x = (float)color.r / 255.f;
	this->color.y = (float)color.g / 255.f;
	this->color.z = (float)color.b / 255.f;

	const float water_threshold = 1.0f;
	const float sand_threshold = 1.1f;
	const float snow_threshold = 15.0f;

	for(unsigned int i = 0; i < 4; i++)
	{
		if(this->vertices[i].z < water_threshold)
		{
			this->colors[i] = sf::Vector3f(0.1f, 0.1f, 0.5f);
		}
		else if(this->vertices[i].z < sand_threshold)
		{
			float rr1 = ((float)rand() / (float)RAND_MAX) * 0.1f;
			float rr2 = ((float)rand() / (float)RAND_MAX) * 0.1f;
			float rr3 = ((float)rand() / (float)RAND_MAX) * 0.1f;
			this->colors[i] = sf::Vector3f(0.9f + rr1, 0.9f + rr2, 0.4f + rr3);
		}
		else if(this->vertices[i].z > snow_threshold)
		{
			this->colors[i] = sf::Vector3f(0.9f, 0.9f, 0.95f);
		}
		else
		{
			this->colors[i] = sf::Vector3f(this->color.x, this->color.y, this->color.z);
		}
	}
}

void Tile::draw(const dfv::Camera& camera, const dfv::Resources& resources) const
{
	glColor3f(this->colors[0].x, this->colors[0].y, this->colors[0].z);
	glNormal3f(this->normals[0].x, this->normals[0].y, this->normals[0].z);
	glVertex3f(this->vertices[0].x, this->vertices[0].y, this->vertices[0].z);

	glColor3f(this->colors[1].x, this->colors[1].y, this->colors[1].z);
	glNormal3f(this->normals[1].x, this->normals[1].y, this->normals[1].z);
	glVertex3f(this->vertices[1].x, this->vertices[1].y, this->vertices[1].z);

	glColor3f(this->colors[2].x, this->colors[2].y, this->colors[2].z);
	glNormal3f(this->normals[2].x, this->normals[2].y, this->normals[2].z);
	glVertex3f(this->vertices[2].x, this->vertices[2].y, this->vertices[2].z);

	glColor3f(this->colors[3].x, this->colors[3].y, this->colors[3].z);
	glNormal3f(this->normals[3].x, this->normals[3].y, this->normals[3].z);
	glVertex3f(this->vertices[3].x, this->vertices[3].y, this->vertices[3].z);
}

void Tile::addBuilding(float height)
{
	this->lp_building = new Building;
	this->lp_building->create(this->vertices, height);//1.f + 0.0001f * ((float)(rand() % 100)*(float)(rand() % 100)));
	this->lp_building->setColor(sf::Color(160 + rand() % 70, 160 + rand() % 70, 160 + rand() % 70));
}

bool Tile::hasBuilding() const
{
	return this->lp_building != NULL;
}

void Tile::drawBuilding(const bool draw_floors) const
{
	if(this->lp_building != NULL)
	{
		this->lp_building->draw(draw_floors);
	}
}

sf::Color Tile::getBuildingColor() const
{
	if(this->hasBuilding())
	{
		return this->lp_building->getColor();
	}
	else
	{
		return sf::Color(0, 0, 0);
	}
}

void Tile::setAsRoad(const bool r)
{
	this->is_road = r;
}

bool Tile::isRoad() const
{
	return this->lp_road != NULL;
}

float Tile::getBuildingHeight() const
{
	if(this->hasBuilding())
	{
		return this->lp_building->getHeight();
	}
	else
	{
		return 0.f;
	}
}

void Tile::addRoad(dfv::Road::Type type, unsigned int orientation)
{
	this->is_road = true;
	this->lp_road = new Road;
	this->lp_road->create(this->vertices, type, orientation);
}

unsigned int Tile::getRoadId() const
{
	if(this->isRoad())
	{
		return this->lp_road->getId();
	}
	else
	{
		return Road::straight;
	}

}

unsigned int Tile::getRoadOrientation() const
{
	if(this->isRoad())
	{
		return this->lp_road->getOrientation();
	}
	else
	{
		return 0;
	}
}

bool Tile::setRoadId(unsigned int road_id)
{
	if(this->isRoad())
	{
		this->lp_road->setId(road_id);
		return true;
	}
	else
	{
		return false;
	}
}

bool Tile::setRoadOrientation(unsigned int road_orientation)
{
	if(this->isRoad())
	{
		this->lp_road->setOrientation(road_orientation);
		return true;
	}
	else
	{
		return false;
	}
}

void Tile::addProp(Prop* lp_prop)
{
	this->lp_prop = lp_prop;
}

sf::Vector3f Tile::getVertex(const unsigned int index) const
{
	if(index < 4)
	{
		return this->vertices[index];
	}
	return this->vertices.back();
}

const std::vector<sf::Vector3f> & Tile::getVertices() const
{
	return this->vertices;
}

void Tile::drawBuildingBox() const
{
	this->lp_building->drawBox();
}

void Tile::drawBuildingOutline() const
{
	this->lp_building->drawOutline();
}

void Tile::drawBuildingFloors() const
{
	this->lp_building->drawFloors();
}

sf::Vector3f Tile::getColor(unsigned int index) const
{
	return this->colors[index];
}

sf::Vector3f Tile::getNormal(unsigned int index) const
{
	return this->normals[index];
}

sf::Vector3f Tile::getBuildingColor3f() const
{
	return this->lp_building->getColor3f();
}

void Tile::setVertex(const unsigned int index, const sf::Vector3f& vertex)
{
	this->vertices[index] = vertex;
}

sf::Color Tile::getSfmlColor() const
{
	return sf::Color(this->color.x * 255.f, this->color.y * 255.f, this->color.z * 255.f);
}

void Tile::setBuildingColor(const sf::Color& color)
{
	this->lp_building->setColor(color);
}

void Tile::drawRoad(const Camera& camera, const Resources& resources) const
{
	if(this->isRoad())
	{
		this->lp_road->draw(camera, resources);
	}
}

void Tile::drawProp(const Camera& camera, const Resources& resources) const
{
	if(this->lp_prop != NULL)
	{
		this->lp_prop->draw(camera, resources);
	}
}

bool Tile::isWater() const
{
	float threshold = 1.0;
	return (this->vertices[0].z < threshold ||
			this->vertices[1].z < threshold ||
			this->vertices[2].z < threshold ||
			this->vertices[3].z < threshold);
}

bool Tile::isBeach() const
{
	float threshold = 1.1;
	return ((this->vertices[0].z < threshold ||
			 this->vertices[1].z < threshold ||
			 this->vertices[2].z < threshold ||
			 this->vertices[3].z < threshold) &&
			 !this->isWater());
}

bool Tile::clearRoad()
{
	if(this->lp_road != NULL)
	{
		delete this->lp_road;
		this->lp_road = NULL;
		this->setColor(sf::Color(10 + rand() % 20, 130 + rand() % 20, 10 + rand() % 20));
		return true;
	}
	else
	{
		return false;
	}

}

bool Tile::clearBuilding()
{
	if(this->lp_building != NULL)
	{
		delete this->lp_building;
		this->lp_building = NULL;
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
	if(this->lp_prop != NULL)
	{
		delete this->lp_prop;
		this->lp_prop = NULL;
		this->setColor(sf::Color(10 + rand() % 20, 130 + rand() % 20, 10 + rand() % 20));
		return true;
	}
	else
	{
		return false;
	}
}

Quad Tile::getQuad() const
{
	Quad res;
	res.create(this->vertices);
	return res;
}

} /* namespace dfv */


