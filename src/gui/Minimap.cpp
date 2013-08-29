/*
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

void Minimap::Create(const unsigned int size)
{
	this->size = size;
	this->img.Create(size, size, sf::Color(200, 200, 200));
	this->lp_pixels = new sf::Uint8[size * size * 4];
	for(unsigned int i = 0; i < size * size * 4; i++)
	{
		this->lp_pixels[i] = 150;
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

void Minimap::GenerateFromMap(const Map& map, const sf::Vector2f position, unsigned int range)
{
	this->range = range;
	for(unsigned int i = 0; i < this->size; i++)
	{
		for(unsigned int j = 0; j < this->size; j++)
		{
			sf::Vector2i rel_pos = this->RealPosFromMapPos(sf::Vector2i(i, j), this->range);
			sf::Vector2i abs_pos(position.x - rel_pos.x, position.y - rel_pos.y);

			if(abs_pos.x >= 0 && abs_pos.x < (int)(map.GetSize()) && abs_pos.y >= 0 && abs_pos.y < (int)(map.GetSize()))
			{
				if(map.IsRoad(abs_pos))
				{
					this->lp_pixels[(j * this->size + i) * 4] = 50;
					this->lp_pixels[(j * this->size + i) * 4 + 1] = 50;
					this->lp_pixels[(j * this->size + i) * 4 + 2] = 50;
				}
				else if(map.HasBuilding(abs_pos))
				{
					this->lp_pixels[(j * this->size + i) * 4] = map.GetBuildingColor(abs_pos).r;
					this->lp_pixels[(j * this->size + i) * 4 + 1] = map.GetBuildingColor(abs_pos).g;
					this->lp_pixels[(j * this->size + i) * 4 + 2] = map.GetBuildingColor(abs_pos).b;
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
}

sf::Vector2i Minimap::RealPosFromMapPos(sf::Vector2i map_pos, int range)
{
	return sf::Vector2i(
			(range*2*map_pos.x)/size - range,
			range - (range*2*map_pos.y)/size);
}

void Minimap::Draw(sf::RenderWindow& window, const Camera& camera) const
{
	sf::Sprite sprite;
	sprite.SetImage(this->img);
	sprite.SetPosition(
			0,
			window.GetHeight() - this->img.GetHeight());
	window.Draw(sprite);

	sf::Shape shape;
	float ang = -(camera.GetRpy().z + 90.f) * 3.1416 / 180.0;
	shape.AddPoint(this->size / 2.0 + 15.0*cos(ang), this->size / 2.0 - 15.0*sin(ang), sf::Color::Red);
	shape.AddPoint(this->size / 2.0 - 3.0*sin(ang), this->size / 2.0 - 3.0*cos(ang), sf::Color::Red);
	shape.AddPoint(this->size / 2.0 + 3.0*sin(ang), this->size / 2.0 + 3.0*cos(ang), sf::Color::Red);
	shape.SetPosition(
			this->img.GetWidth() / this->range / 2,
			window.GetHeight() - this->img.GetHeight() + (this->img.GetHeight() / this->range / 2));
	window.Draw(shape);
}

std::string Minimap::HandleInput(const Camera& camera, const sf::Event& event, const sf::Vector2i& mouse_pos)
{
	sf::Vector2i pos(camera.GetPosition().x, camera.GetPosition().y);
	sf::Vector2i rel_pos = this->RealPosFromMapPos(mouse_pos, this->range);
	sf::Vector2i abs_pos(camera.GetPosition().x - rel_pos.x, camera.GetPosition().y - rel_pos.y);

	//std::cout << "mouse_pos: " << abs_pos.x << ", " << abs_pos.y << std::endl;

	std::string res;

	if(event.Type == sf::Event::MouseButtonPressed)
	{
		std::cout << "Mouse Button Pressed" << std::endl;
		if(event.MouseButton.Button == sf::Mouse::Left)
		{
			/*if(this->lp_map->IsRoad(abs_pos))
			{
				std::cout << "Changed road type" << std::endl;
				this->lp_map->ChangeRoadType(abs_pos);
			}*/
		}
		if(event.MouseButton.Button == sf::Mouse::Right)
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

unsigned int Minimap::GetSize() const
{
	return this->size;
}

} /* namespace dfv */
