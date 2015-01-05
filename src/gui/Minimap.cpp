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

void Minimap::generateFromMap(const Map& map, const sf::Vector2f position, unsigned int range)
{
	this->range = range;
	for(size_t i = 0; i < this->size; i++)
	{
		for(size_t j = 0; j < this->size; j++)
		{
			sf::Vector2i absPos = this->realPosFromMinimapPos(sf::Vector2i(i, j), position);
			size_t pixelIndex = (j * this->size + i) * 4;
			if(absPos.x >= 0 && absPos.x < (int)(map.getSize()) && absPos.y >= 0 && absPos.y < (int)(map.getSize()))
			{
				if(map.getTile(absPos).hasRoad())
				{
					this->lp_pixels[pixelIndex] = 50;
					this->lp_pixels[pixelIndex + 1] = 50;
					this->lp_pixels[pixelIndex + 2] = 50;
				}
				else if(map.getTile(absPos).isWater())
				{
					this->lp_pixels[pixelIndex] = 0;
					this->lp_pixels[pixelIndex + 1] = 0;
					this->lp_pixels[pixelIndex + 2] = 200;
				}
				else if(map.getTile(absPos).isBeach())
				{
					this->lp_pixels[pixelIndex] = 200;
					this->lp_pixels[pixelIndex + 1] = 200;
					this->lp_pixels[pixelIndex + 2] = 100;
				}
				/*
				else if(map.getTile(absPos).hasStructure())
				{
					this->lp_pixels[pixelIndex] = 200;
					this->lp_pixels[pixelIndex + 1] = 100;
					this->lp_pixels[pixelIndex + 2] = 50;
				}*/
				else
				{
					this->lp_pixels[pixelIndex] = 50;
					this->lp_pixels[pixelIndex + 1] = 100;
					this->lp_pixels[pixelIndex + 2] = 50;
				}
			}
			else
			{
				this->lp_pixels[pixelIndex] = 0;
				this->lp_pixels[pixelIndex + 1] = 0;
				this->lp_pixels[pixelIndex + 2] = 0;
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

sf::Vector2i Minimap::realPosFromMinimapPos(const sf::Vector2i& minimapPos, const sf::Vector2f& mapPos) const
{
	return sf::Vector2i(mapPos.x + 2*this->range/this->size*minimapPos.x,
			            mapPos.y - 2*this->range/this->size*minimapPos.y);
}

void Minimap::draw(sf::RenderWindow& window, const Camera& camera) const
{
	sf::Sprite sprite;
	sprite.setTexture(this->texture);
	sprite.setPosition(
			0.0,
			window.getSize().y - this->img.getSize().y);
	window.draw(sprite);

	sf::ConvexShape shape;
	float ang = -(camera.getRpy().z - 90.f) * M_PI / 180.0;
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
