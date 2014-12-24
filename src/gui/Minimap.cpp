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

 * Minimap.cpp
 *
 *  Created on: Aug 15, 2013
 *      Author: daniel
 */

#include "Minimap.h"

namespace dfv
{

Minimap::Minimap():
		size(0),
		range(16),
		lp_pixels(NULL)
{
	// TODO Auto-generated constructor stub

}

Minimap::~Minimap()
{
	delete this->lp_pixels;
}

void Minimap::create(const unsigned int size)
{
	this->size = size;
	this->img.create(size, size, sf::Color(200, 200, 200));
	this->texture.create(size, size);
	this->lp_pixels = new sf::Uint8[size * size * 4];
	for(unsigned int i = 0; i < size * size * 4; i++)
	{
		this->lp_pixels[i] = 220;
	}
}

/*void Minimap::GenerateFromMap(Map* lp_map, const Camera& camera)
{
	this->lp_map = lp_map;
	sf::Vector2f pos(camera.GetPosition().x, camera.GetPosition().y);
	float map_height = lp_map->GetHeight(pos);
	float height = camera.GetPosition().z - map_height;
	this->range = 16 + 2* height;
	for(unsigned int i = 0; i < this->size; i++)
	{
		for(unsigned int j = 0; j < this->size; j++)
		{
			sf::Vector2i rel_pos = this->RealPosFromMapPos(sf::Vector2i(i, j), this->range);
			sf::Vector2i abs_pos(camera.GetPosition().x - rel_pos.x, camera.GetPosition().y - rel_pos.y);

			if(abs_pos.x >= 0 && abs_pos.x < (int)(lp_map->GetSize()) && abs_pos.y >= 0 && abs_pos.y < (int)(lp_map->GetSize()))
			{
				if(lp_map->IsRoad(abs_pos))
				{
					this->lp_pixels[(j * this->size + i) * 4] = 50;
					this->lp_pixels[(j * this->size + i) * 4 + 1] = 50;
					this->lp_pixels[(j * this->size + i) * 4 + 2] = 50;
				}
				else if(lp_map->HasBuilding(abs_pos))
				{
					this->lp_pixels[(j * this->size + i) * 4] = lp_map->GetBuildingColor(abs_pos).r;
					this->lp_pixels[(j * this->size + i) * 4 + 1] = lp_map->GetBuildingColor(abs_pos).g;
					this->lp_pixels[(j * this->size + i) * 4 + 2] = lp_map->GetBuildingColor(abs_pos).b;
				}
				else
				{
					this->lp_pixels[(j * this->size + i) * 4] = 200;
					this->lp_pixels[(j * this->size + i) * 4 + 1] = 200;
					this->lp_pixels[(j * this->size + i) * 4 + 2] = 200;
				}
			}
			else
			{
				this->lp_pixels[(j * this->size + i) * 4] = 0;
				this->lp_pixels[(j * this->size + i) * 4 + 1] = 0;
				this->lp_pixels[(j * this->size + i) * 4 + 2] = 0;
			}


		}
	}



	this->img.LoadFromPixels(this->size, this->size, this->lp_pixels);
}*/

void Minimap::generateFromMap(const Map& map, const sf::Vector2f position, unsigned int range)
{
	this->range = range;
	for(unsigned int i = 0; i < this->size; i++)
	{
		for(unsigned int j = 0; j < this->size; j++)
		{
			sf::Vector2i rel_pos = this->realPosFromMapPos(sf::Vector2i(i, j), this->range);
			sf::Vector2i abs_pos(position.x - rel_pos.x, position.y - rel_pos.y);

			if(abs_pos.x >= 0 && abs_pos.x < (int)(map.getSize()) && abs_pos.y >= 0 && abs_pos.y < (int)(map.getSize()))
			{
				//if(map.IsRoad(abs_pos))
				if(map.isRoad(abs_pos.x, abs_pos.y))
				{
					this->lp_pixels[(j * this->size + i) * 4] = 50;
					this->lp_pixels[(j * this->size + i) * 4 + 1] = 50;
					this->lp_pixels[(j * this->size + i) * 4 + 2] = 50;
				}
				//else if(map.HasBuilding(abs_pos))
				/*
				else if(map.hasBuilding(abs_pos.x, abs_pos.y))
				{
					this->lp_pixels[(j * this->size + i) * 4] = map.getBuildingColor(abs_pos).r;
					this->lp_pixels[(j * this->size + i) * 4 + 1] = map.getBuildingColor(abs_pos).g;
					this->lp_pixels[(j * this->size + i) * 4 + 2] = map.getBuildingColor(abs_pos).b;
				}
				*/
				else if(map.isWater(abs_pos.x, abs_pos.y))
				{
					this->lp_pixels[(j * this->size + i) * 4] = 0;
					this->lp_pixels[(j * this->size + i) * 4 + 1] = 0;
					this->lp_pixels[(j * this->size + i) * 4 + 2] = 200;
				}
				else if(map.isBeach(abs_pos.x, abs_pos.y))
				{
					this->lp_pixels[(j * this->size + i) * 4] = 200;
					this->lp_pixels[(j * this->size + i) * 4 + 1] = 200;
					this->lp_pixels[(j * this->size + i) * 4 + 2] = 100;
				}
				else if(map.hasStructure(abs_pos.x, abs_pos.y))
				{
					this->lp_pixels[(j * this->size + i) * 4] = 200;
					this->lp_pixels[(j * this->size + i) * 4 + 1] = 100;
					this->lp_pixels[(j * this->size + i) * 4 + 2] = 50;
				}
				else
				{
					this->lp_pixels[(j * this->size + i) * 4] = 50;
					this->lp_pixels[(j * this->size + i) * 4 + 1] = 100;
					this->lp_pixels[(j * this->size + i) * 4 + 2] = 50;
				}
			}
			else
			{
				this->lp_pixels[(j * this->size + i) * 4] = 0;
				this->lp_pixels[(j * this->size + i) * 4 + 1] = 0;
				this->lp_pixels[(j * this->size + i) * 4 + 2] = 0;
			}


		}
	}

	this->img.create(this->size, this->size, this->lp_pixels);
	this->texture.update(this->img);
}

sf::Vector2i Minimap::realPosFromMapPos(sf::Vector2i map_pos, int range)
{
	return sf::Vector2i(
			(range*2*map_pos.x)/size - range,
			range - (range*2*map_pos.y)/size);
}

void Minimap::draw(sf::RenderWindow& window, const Camera& camera) const
{
	sf::Sprite sprite;
	//sf::Texture texture;
	//this->texture.update(this->lp_pixels);
	sprite.setTexture(this->texture);
	sprite.setPosition(
			0.0,
			window.getSize().y - this->img.getSize().y);
	window.draw(sprite);

	sf::ConvexShape shape;
	float ang = -(camera.getRpy().z + 90.f) * 3.1416 / 180.0;
	shape.setPointCount(3);
	shape.setFillColor(sf::Color::Red);
	shape.setPoint(0, sf::Vector2f(this->size / 2.0 + 15.0*cos(ang), this->size / 2.0 - 15.0*sin(ang)));
	shape.setPoint(1, sf::Vector2f(this->size / 2.0 - 3.0*sin(ang), this->size / 2.0 - 3.0*cos(ang)));
	shape.setPoint(2, sf::Vector2f(this->size / 2.0 + 3.0*sin(ang), this->size / 2.0 + 3.0*cos(ang)));
	shape.setPosition(
			this->img.getSize().x / this->range / 2,
			window.getSize().y - this->img.getSize().y + (this->img.getSize().y / this->range / 2));
	window.draw(shape);
}

std::string Minimap::handleInput(const Camera& camera, const sf::Event& event, const sf::Vector2i& mouse_pos)
{
	sf::Vector2i pos(camera.getPosition().x, camera.getPosition().y);
	sf::Vector2i rel_pos = this->realPosFromMapPos(mouse_pos, this->range);
	sf::Vector2i abs_pos(camera.getPosition().x - rel_pos.x, camera.getPosition().y - rel_pos.y);

	//std::cout << "mouse_pos: " << abs_pos.x << ", " << abs_pos.y << std::endl;

	std::string res;

	if(event.type == sf::Event::MouseButtonPressed)
	{
		std::cout << "Mouse Button Pressed" << std::endl;
		if(event.mouseButton.button == sf::Mouse::Left)
		{
			/*if(this->lp_map->IsRoad(abs_pos))
			{
				std::cout << "Changed road type" << std::endl;
				this->lp_map->ChangeRoadType(abs_pos);
			}*/
		}
		if(event.mouseButton.button == sf::Mouse::Right)
		{
			/*if(this->lp_map->IsRoad(abs_pos))
			{
				std::cout << "Changed road orientation" << std::endl;
				this->lp_map->ChangeRoadOrientation(abs_pos);
			}*/
		}
	}

	return res;
}

unsigned int Minimap::getSize() const
{
	return this->size;
}

} /* namespace dfv */
