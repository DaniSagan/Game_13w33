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
		building_list(0),
		tile_list(0),
		population(0)
{
	// TODO Auto-generated constructor stub

}

Map::~Map()
{
	for(unsigned int i = 0; i < this->lp_tiles.size(); i++)
	{
		for(unsigned int j = 0; j < this->lp_tiles.size(); j++)
		{
			delete this->lp_tiles[i][j];
		}
	}
}

void Map::create(unsigned int size)
{
	this->size = size;

	this->heights.resize(size + 1);
	for(unsigned int i = 0; i < this->heights.size(); i++)
	{
		this->heights[i].resize(size + 1);
		for(unsigned int j = 0; j < this->heights.size(); j++)
		{
			this->heights[i][j] = 0.f;
		}
	}

	this->lp_tiles.resize(size);
	for(unsigned int i = 0; i < this->lp_tiles.size(); i++)
	{
		this->lp_tiles[i].resize(size + 1);
		for(unsigned int j = 0; j < this->lp_tiles.size(); j++)
		{
			this->lp_tiles[i][j] = NULL;
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
			this->lp_tiles[i][j] = new Tile;
			this->lp_tiles[i][j]->create(
					sf::Vector2f(i, j),
					this->heights[i][j],
					this->heights[i+1][j],
					this->heights[i+1][j+1],
					this->heights[i][j+1]);
			this->lp_tiles[i][j]->setColor(sf::Color(10 + rand() % 20, 130 + rand() % 20, 10 + rand() % 20));
		}
	}
}

void Map::createFromFile(std::string filename, unsigned int water_level, float max_height)
{


	sf::Image heightmap;
	heightmap.loadFromFile(filename);
	this->size = heightmap.getSize().y - 1;
	this->heights.resize(this->size + 1);

	for(unsigned int i = 0; i < this->size + 1; i++)
	{
		this->heights[i].resize(this->size + 1);
		for(unsigned int j = 0; j < this->size + 1; j++)
		{
			// generate height map
			sf::Color col = heightmap.getPixel(i, this->size - j);
			if(col.r <= water_level)
			{
				this->heights[i][j] = 0.99;
			}
			else
			{
				this->heights[i][j] = 1.f + (float)(col.r - water_level)*(float)(max_height - 1.0)/(float)(255 - water_level);
			}
		}
	}

	this->lp_tiles.resize(this->size);
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
			lp_tile->setColor(sf::Color(20 + rand() % 20, 180 + rand() % 20, 20 + rand() % 20));
			this->lp_tiles[i][j] = lp_tile;
			if(rand() % 5 < 4)
			{
				if(this->heights[i][j] > 1.2f &&
				   this->heights[i+1][j] > 1.2f &&
				   this->heights[i+1][j+1] > 1.2f &&
				   this->heights[i][j+1] > 1.2f &&
				   i%3 != 0 &&
				   j%5 != 0)
				{
					this->lp_tiles[i][j]->addBuilding(0.5f + 0.00001f* (200.f/(float)(0.03*(x*x + y*y) + 50)) * ((float)(rand() % 100)*(float)(rand() % 100) * (float)(rand() % 100)));
					building_count++;
					//float rr = (float)rand() / (float)RAND_MAX;
					//this->lp_tiles[i][j]->AddBuilding(2.f + 5.f * pow(rr, 4.0));
				}
			}
			if(i%3 == 0 || j %5 == 0)
			{
				if(this->heights[i][j] > 1.2f &&
				   this->heights[i+1][j] > 1.2f &&
				   this->heights[i+1][j+1] > 1.2f &&
				   this->heights[i][j+1] > 1.2f)
				{
					unsigned int rr = rand() % 5;
					// road
					this->lp_tiles[i][j]->setColor(sf::Color(50 + rr, 50 + rr, 50 + rr));
				}
			}
			if(this->heights[i][j] < 1.1f &&
			   this->heights[i+1][j] < 1.1f &&
			   this->heights[i+1][j+1] < 1.1f &&
			   this->heights[i][j+1] < 1.1f)
			{
				// beach
				this->lp_tiles[i][j]->setColor(sf::Color(200 + rand() % 10, 200 + rand() % 10, 110 + rand() % 10));
			}
		}
	}
	//std::cout << "No. of buildings: " << building_count << std::endl;
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
			//float x3 = x + 500;
			//float y3 = y - 400;
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
			//lp_tile->SetColor(sf::Color(20 + rand() % 20, 180 + rand() % 20, 20 + rand() % 20));
			lp_tile->setColor(sf::Color(13 + rand() % 20, 115 + rand() % 20, 13 + rand() % 20));
			this->lp_tiles[i][j] = lp_tile;
			/*if(rand() % 5 < 4)
			{
				if(this->heights[i][j] > 1.2f &&
				   this->heights[i+1][j] > 1.2f &&
				   this->heights[i+1][j+1] > 1.2f &&
				   this->heights[i][j+1] > 1.2f &&
				   i%3 != 0 &&
				   j%5 != 0)
				{
					this->lp_tiles[i][j]->AddBuilding(0.5f + 0.00001f* (200.f/(float)(0.03*(x*x + y*y) + 50)) * ((float)(rand() % 100)*(float)(rand() % 100) * (float)(rand() % 100)));
					building_count++;
					//float rr = (float)rand() / (float)RAND_MAX;
					//this->lp_tiles[i][j]->AddBuilding(2.f + 5.f * pow(rr, 4.0));
				}
			}*/
			/*if(i%3 == 0 || j %5 == 0)
			{
				if(this->heights[i][j] > 1.2f &&
				   this->heights[i+1][j] > 1.2f &&
				   this->heights[i+1][j+1] > 1.2f &&
				   this->heights[i][j+1] > 1.2f)
				{
					unsigned int rr = rand() % 5;
					// road
					this->lp_tiles[i][j]->SetColor(sf::Color(50 + rr, 50 + rr, 50 + rr));
					this->lp_tiles[i][j]->AddRoad(dfv::Road::straight, 0);
					//this->lp_tiles[i][j]->SetAsRoad(true);
				}
			}*/

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
	std::cout << "No. of buildings: " << building_count << std::endl;

	Quad base;
	base.create(sf::Vector3f(0.1, 0.1, 0.0),
			    sf::Vector3f(0.7, 0.1, 0.0),
			    sf::Vector3f(0.9, 0.8, 0.0),
			    sf::Vector3f(0.1, 0.5, 0.0));
	this->test_model.create(this->lp_tiles.at(100).at(100)->getQuad(), base, 10);
}

void Map::draw(sf::Window& window, const dfv::Camera& camera, const dfv::Resources& resources) const
{
	glViewport(0, 0, window.getSize().x, window.getSize().y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(55.0f, (float)window.getSize().x / (float)window.getSize().y, 0.01f, 2000.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(camera.getRpy().x, 1.f, 0.f, 0.f);
	glRotatef(camera.getRpy().y, 0.f, 1.f, 0.f);
	glRotatef(camera.getRpy().z, 0.f, 0.f, 1.f);
	glTranslatef(-camera.getPosition().x, -camera.getPosition().y, -camera.getPosition().z);

	this->sky.draw();

	GLfloat light_position[] = { 400.0, -200.0, 400.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);


	// If facing down, draw the entire map
	if(camera.getRpy().x > -20.f)
	{
		for(unsigned int i = 0; i < size; i++)
		{
			for(unsigned int j = 0; j < size; j++)
			{
				this->lp_tiles[i][j]->draw(camera, resources);
			}
		}

		//glBindTexture(GL_TEXTURE_2D, resources.img_1_handle);
		for(unsigned int i = 0; i < size; i++)
		{
			for(unsigned int j = 0; j < size; j++)
			{
				this->lp_tiles[i][j]->drawBuilding(false);
			}
		}
	}

	// If not looking down, draw only the half of the map we're facing
	else
	{
		// get the quadrant from the angle of view
		unsigned int quadrant;
		if(camera.getRpy().z >= 315.f || camera.getRpy().z < 45.f) quadrant = 1;
		if(camera.getRpy().z >= 45.f && camera.getRpy().z < 135.f) quadrant = 0;
		if(camera.getRpy().z >= 135.f && camera.getRpy().z < 225.f) quadrant = 3;
		if(camera.getRpy().z >= 225.f && camera.getRpy().z < 315.f) quadrant = 2;

		// get camera position
		sf::Vector2i cam_pos(camera.getPosition().x, camera.getPosition().y);

		if(cam_pos.x < 0) cam_pos.x = 0;
		if(cam_pos.y < 0) cam_pos.y = 0;
		if(cam_pos.x > (int)this->size) cam_pos.x = this->size;
		if(cam_pos.y > (int)this->size) cam_pos.y = this->size;

		int draw_floor_radius = 30;

		if(quadrant == 0)
		{
			cam_pos.x -= 5;
			if(cam_pos.x < 0) cam_pos.x = 0;

			if(camera.getRpy().x > -120.f)
			{
				for(int i = cam_pos.x; i < (int)this->size; i++)
				{
					for(int j = 0; j < (int)this->size; j++)
					{
						this->lp_tiles[i][j]->draw(camera, resources);
					}
				}
			}

			for(int i = cam_pos.x; i < (int)this->size; i++)
			{
				for(int j = 0; j < (int)this->size; j++)
				{
					this->lp_tiles[i][j]->drawBuilding(i < cam_pos.x + draw_floor_radius && j > cam_pos.y - draw_floor_radius && j < cam_pos.y + draw_floor_radius);
				}
			}
		}

		else if(quadrant == 1)
		{
			cam_pos.y -= 5;
			if(cam_pos.y < 0) cam_pos.y = 0;

			if(camera.getRpy().x > -120.f)
			{
				for(int i = 0; i < (int)this->size; i++)
				{
					for(int j = cam_pos.y; j < (int)this->size; j++)
					{
						this->lp_tiles[i][j]->draw(camera, resources);
					}
				}
			}

			for(int i = 0; i < (int)this->size; i++)
			{
				for(int j = cam_pos.y; j < (int)this->size; j++)
				{
					this->lp_tiles[i][j]->drawBuilding(j < cam_pos.y + draw_floor_radius && i > cam_pos.x - draw_floor_radius && i < cam_pos.x + draw_floor_radius);
				}
			}
		}

		else if(quadrant == 2)
		{
			cam_pos.x += 5;
			if(cam_pos.x > (int)this->size) cam_pos.x = this->size;

			if(camera.getRpy().x > -120.f)
			{
				for(int i = 0; i < cam_pos.x; i++)
				{
					for(unsigned int j = 0; j < size; j++)
					{
						this->lp_tiles[i][j]->draw(camera, resources);
					}
				}
			}

			for(int i = 0; i < cam_pos.x; i++)
			{
				for(unsigned int j = 0; j < size; j++)
				{
					this->lp_tiles[i][j]->drawBuilding((int)i > cam_pos.x - draw_floor_radius && (int)j > cam_pos.y - draw_floor_radius && (int)j < cam_pos.y + draw_floor_radius);
				}
			}
		}

		else if(quadrant == 3)
		{
			cam_pos.y += 5;
			if(cam_pos.y > (int)this->size) cam_pos.y = this->size;

			if(camera.getRpy().x > -120.f)
			{
				for(int i = 0; i < (int)this->size; i++)
				{
					for(int j = 0; j < cam_pos.y; j++)
					{
						this->lp_tiles[i][j]->draw(camera, resources);
					}
				}
			}

			for(int i = 0; i < (int)this->size; i++)
			{
				for(int j = 0; j < cam_pos.y; j++)
				{
					this->lp_tiles[i][j]->drawBuilding(j > cam_pos.y - draw_floor_radius && i > cam_pos.x - draw_floor_radius && i < cam_pos.x + draw_floor_radius);
				}
			}
		}

		else
		{
			std::cout << "ERROR: quadrant" << std::endl;
		}

	}


	//this->test_model.draw();


	//this->sky.Draw();

	//glBindTexture(GL_TEXTURE_2D, resources.img_1_handle);
	/*for(unsigned int i = 0; i < size; i++)
	{
		for(unsigned int j = 0; j < size; j++)
		{
			this->lp_tiles[i][j]->Draw(camera, resources);
		}
	}

	//glBindTexture(GL_TEXTURE_2D, resources.img_1_handle);
	for(unsigned int i = 0; i < size; i++)
	{
		for(unsigned int j = 0; j < size; j++)
		{
			this->lp_tiles[i][j]->DrawBuilding();
		}
	}*/
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

bool Map::saveHeightMap(const std::string& filename)
{
	std::ofstream file;
	file.open(filename.c_str(), std::ios::out | std::ios::binary);

	file.write((char*)&(this->size), sizeof(unsigned int));

	for(unsigned int i = 0; i < this->heights.size(); i++)
	{
		for(unsigned int j = 0; j < this->heights[i].size(); j++)
		{
			file.write((char*)&(this->heights[i][j]), sizeof(float));
		}
	}

	file.close();
	return true;

}

bool Map::loadHeightMap(const std::string& filename)
{
	std::ifstream file;
	file.open(filename.c_str(), std::ios::in | std::ios::binary);

	if(file.is_open())
	{
		std::cout << "Loading height map..." << std::endl;
		unsigned int size;

		std::cout << "Reading size..." << std::endl;
		file.read((char*)&(size), sizeof(unsigned int));

		std::cout << "Map size: " << size << std::endl;
		std::cout << "Creating map..." << std::endl;
		this->create(size);

		std::cout << "Reading heights..." << std::endl;
		for(unsigned int i = 0; i < this->heights.size(); i++)
		{
			for(unsigned int j = 0; j < this->heights.size(); j++)
			{
				file.read((char*)&(this->heights[i][j]), sizeof(float));
			}
		}

		std::cout << "Generating tiles..." << std::endl;
		this->generateTiles();

		file.close();
		std::cout << "Height Map loaded" << std::endl;
		return true;
	}
	else
	{
		return false;
	}

}

bool Map::saveBuildingMap(const std::string& filename)
{
	sf::Image img;
	img.create(this->size, this->size, sf::Color(0, 0, 0));

	for(unsigned int i = 0; i < this->size; i++)
	{
		for(unsigned int j = 0; j < this->size; j++)
		{
			if(this->lp_tiles[i][j]->isRoad())
			{
				img.setPixel(i, this->size - j - 1, sf::Color(255, 0, 0));
			}
			else if(this->lp_tiles[i][j]->hasBuilding())
			{
				float h = this->lp_tiles[i][j]->getBuildingHeight();
				unsigned char hh = (h > 255 * 8) ? 255 : h * 8;
				img.setPixel(i, this->size - j - 1, sf::Color(0, hh, 0));
			}
		}
	}

	return img.saveToFile(filename);
}

bool Map::loadBuildingMap(const std::string& filename)
{
	sf::Image img;
	img.loadFromFile(filename);
	if(img.getSize().y == this->size && img.getSize().x == this->size)
	{
		for(unsigned int i = 0; i < this->size; i++)
		{
			for(unsigned int j = 0; j < this->size; j++)
			{
				sf::Color pix = img.getPixel(i, this->size - j - 1);
				unsigned char gg = pix.g;
				unsigned char rr = pix.r;
				if(rr == 255)
				{
					this->lp_tiles[i][j]->setAsRoad(true);
					//this->lp_tiles[i][j]->AddRoad(dfv::Road::straight, 0);
					unsigned int ra = rand() % 5;
					this->lp_tiles[i][j]->setColor(sf::Color(50 + ra, 50 + ra, 50 + ra));
				}
				if(gg > 0)
				{
					this->lp_tiles[i][j]->addBuilding((float)gg / 8.0);
				}
			}
		}

		// Setting road types
		for(unsigned int i = 0; i < this->size; i++)
		{
			for(unsigned int j = 0; j < this->size; j++)
			{
				if(this->lp_tiles[i][j]->isRoad())
				{
					std::vector<bool> has_road(7, false);
					has_road[0] = (i == this->size - 1) ? false : this->lp_tiles[i+1][j]->isRoad();
					has_road[1] = (i == this->size - 1) || (j == this->size - 1) ? false : this->lp_tiles[i+1][j+1]->isRoad();
					has_road[2] = (j == this->size - 1) ? false : this->lp_tiles[i][j+1]->isRoad();
					has_road[3] = (i == 0) || (j == this->size - 1) ? false : this->lp_tiles[i-1][j+1]->isRoad();
					has_road[4] = (i == 0) ? false : this->lp_tiles[i-1][j]->isRoad();
					has_road[5] = (i == 0) || (j == 0) ? false : this->lp_tiles[i-1][j-1]->isRoad();
					has_road[6] = (j == 0) ? false : this->lp_tiles[i][j-1]->isRoad();
					has_road[7] = (i == this->size - 1) || (j == 0) ? false : this->lp_tiles[i+1][j-1]->isRoad();

					if(has_road[2] && has_road[6] && !has_road[0] && !has_road[4])
					{
						this->lp_tiles[i][j]->addRoad(dfv::Road::straight, 0);
					}

					else if(!has_road[2] && !has_road[6] && has_road[0] && has_road[4])
					{
						this->lp_tiles[i][j]->addRoad(dfv::Road::straight, 1);
					}

					else if(has_road[2] && has_road[6] && has_road[0] && has_road[4])
					{
						this->lp_tiles[i][j]->addRoad(dfv::Road::cross, 1);
					}

					else if(has_road[2] && has_road[4] && !has_road[0] && !has_road[6])
					{
						this->lp_tiles[i][j]->addRoad(dfv::Road::curve, 0);
					}

					else if(has_road[0] && has_road[2] && !has_road[4] && !has_road[6])
					{
						this->lp_tiles[i][j]->addRoad(dfv::Road::curve, 1);
					}

					else if(has_road[0] && has_road[6] && !has_road[2] && !has_road[4])
					{
						this->lp_tiles[i][j]->addRoad(dfv::Road::curve, 2);
					}

					else if(has_road[4] && has_road[6] && !has_road[2] && !has_road[0])
					{
						this->lp_tiles[i][j]->addRoad(dfv::Road::curve, 3);
					}

					else if(has_road[2] && has_road[4] && has_road[6] && !has_road[0])
					{
						this->lp_tiles[i][j]->addRoad(dfv::Road::tcross, 0);
					}

					else if(has_road[0] && has_road[4] && has_road[6] && !has_road[2])
					{
						this->lp_tiles[i][j]->addRoad(dfv::Road::tcross, 3);
					}

					else if(has_road[0] && has_road[2] && has_road[6] && !has_road[4])
					{
						this->lp_tiles[i][j]->addRoad(dfv::Road::tcross, 2);
					}

					else if(has_road[0] && has_road[2] && has_road[4] && !has_road[6])
					{
						this->lp_tiles[i][j]->addRoad(dfv::Road::tcross, 1);
					}

					else if(has_road[0] && !has_road[2] && !has_road[4] && !has_road[6])
					{
						this->lp_tiles[i][j]->addRoad(dfv::Road::straight, 1);
					}

					else if(!has_road[0] && has_road[2] && !has_road[4] && !has_road[6])
					{
						this->lp_tiles[i][j]->addRoad(dfv::Road::straight, 2);
					}

					else if(!has_road[0] && !has_road[2] && has_road[4] && !has_road[6])
					{
						this->lp_tiles[i][j]->addRoad(dfv::Road::straight, 3);
					}

					else if(!has_road[0] && !has_road[2] && !has_road[4] && has_road[6])
					{
						this->lp_tiles[i][j]->addRoad(dfv::Road::straight, 0);
					}

					else
					{
						this->lp_tiles[i][j]->addRoad(dfv::Road::straight, 0);
					}
				}
			}
		}
		return true;
	}
	else
	{
		std::cout << "ERROR: Building map does not match height map." << std::endl;
		return false;
	}
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
			if(this->lp_tiles[i][j]->hasBuilding())
			{
				dfv::Utils::drawRectangle(this->map_img, sf::Vector2i(i*tile_size, j*tile_size), sf::Vector2i((i+1)*tile_size - 1, (j+1)*tile_size - 1), sf::Color(0, 0, 0));
				dfv::Utils::drawRectangle(this->map_img, sf::Vector2i(i*tile_size+1, j*tile_size+1), sf::Vector2i((i+1)*tile_size - 2, (j+1)*tile_size - 2), this->lp_tiles[i][j]->getBuildingColor());
			}
		}
	}

	this->map_img.saveToFile("res/map/map_img.png");
}

/*bool Map::IsRoad(const sf::Vector2i& tile_pos) const
{
	if(tile_pos.x >= 0 && tile_pos.x < (int)this->size &&
	   tile_pos.y >= 0 && tile_pos.y < (int)this->size)
	{
		return this->lp_tiles[tile_pos.x][tile_pos.y]->IsRoad();
	}
	else
	{
		return false;
	}
}*/

bool Map::isRoad(unsigned int x, unsigned int y) const
{
	if(x >= 0 && x < this->size &&
	   y >= 0 && y < this->size)
	{
		return this->lp_tiles[x][y]->isRoad();
	}
	else
	{
		return false;
	}
}

/*bool Map::HasBuilding(const sf::Vector2i& tile_pos) const
{
	if(tile_pos.x >= 0 && tile_pos.x < (int)this->size &&
	   tile_pos.y >= 0 && tile_pos.y < (int)this->size)
	{
		return this->lp_tiles[tile_pos.x][tile_pos.y]->HasBuilding();
	}
	else
	{
		return false;
	}
}*/

bool Map::hasBuilding(unsigned int x, unsigned int y) const
{
	if(x >= 0 && x < this->size &&
	   y >= 0 && y < this->size)
	{
		return this->lp_tiles[x][y]->hasBuilding();
	}
	else
	{
		return false;
	}
}

sf::Color Map::getBuildingColor(const sf::Vector2i& tile_pos) const
{
	if(tile_pos.x >= 0 && tile_pos.x < (int)this->size &&
	   tile_pos.y >= 0 && tile_pos.y < (int)this->size)
	{
		return this->lp_tiles[tile_pos.x][tile_pos.y]->getBuildingColor();
	}
	else
	{
		return sf::Color(0, 0, 0);
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

	//std::cout << window.GetWidth() << std::endl;

	return sf::Vector3f((float)win_x, viewport[3] - (float)win_y, (float)win_z);
}

const std::vector<sf::Vector3f> & Map::getTileVertices(sf::Vector2i pos) const
{
	//return this->lp_tiles[pos.x][pos.y]->GetVertices();
	//if(pos.x >= 0 && pos.x < this->size &&
	//   pos.y >= 0 && pos.y < this->size)

	return this->lp_tiles.at(pos.x).at(pos.y)->getVertices();
}

/*void Map::DrawTiles(dfv::IntRect rect, const Camera& camera, const Resources& resources) const
{
	if(rect.Left < 0) rect.Left = 0;
	if(rect.Right >= (int)this->GetSize()) rect.Right = this->GetSize() - 1;
	if(rect.Bottom < 0) rect.Bottom = 0;
	if(rect.Top >= (int)this->GetSize()) rect.Top = this->GetSize() - 1;

	glBegin(GL_QUADS);
	for(unsigned int i = rect.Left; (int)i <= rect.Right; i++)
	{
		for(unsigned int j = rect.Bottom; (int)j <= rect.Top; j++)
		{
			this->lp_tiles[i][j]->Draw(camera, resources);
		}
	}
	glEnd();
}

void Map::DrawBuildingBoxes(dfv::IntRect rect) const
{
	if(rect.Left < 0) rect.Left = 0;
	if(rect.Right >= (int)this->GetSize()) rect.Right = this->GetSize() - 1;
	if(rect.Bottom < 0) rect.Bottom = 0;
	if(rect.Top >= (int)this->GetSize()) rect.Top = this->GetSize() - 1;

	glBegin(GL_QUADS);

	for(unsigned int i = rect.Left; (int)i <= rect.Right; i++)
	{
		for(unsigned int j = rect.Bottom; (int)j <= rect.Top; j++)
		{
			if(this->lp_tiles[i][j]->HasBuilding())
			{
				this->lp_tiles[i][j]->DrawBuildingBox();
			}
		}
	}

	glEnd();
}

void Map::DrawBuildingOutlines(dfv::IntRect rect) const
{
	if(rect.Left < 0) rect.Left = 0;
	if(rect.Right >= (int)this->GetSize()) rect.Right = this->GetSize() - 1;
	if(rect.Bottom < 0) rect.Bottom = 0;
	if(rect.Top >= (int)this->GetSize()) rect.Top = this->GetSize() - 1;

	glColor3f(0.1, 0.1, 0.1);

	glBegin(GL_QUADS);
	for(unsigned int i = rect.Left; (int)i <= rect.Right; i++)
	{
		for(unsigned int j = rect.Bottom; (int)j <= rect.Top; j++)
		{
			if(this->lp_tiles[i][j]->HasBuilding())
			{
				this->lp_tiles[i][j]->DrawBuildingOutline();
			}
		}
	}
	glEnd();
}

void Map::DrawBuildingFloors(dfv::IntRect rect) const
{
	if(rect.Left < 0) rect.Left = 0;
	if(rect.Right >= (int)this->GetSize()) rect.Right = this->GetSize() - 1;
	if(rect.Bottom < 0) rect.Bottom = 0;
	if(rect.Top >= (int)this->GetSize()) rect.Top = this->GetSize() - 1;

	glColor3f(0.1, 0.1, 0.1);

	glBegin(GL_QUADS);
	for(unsigned int i = rect.Left; (int)i <= rect.Right; i++)
	{
		for(unsigned int j = rect.Bottom; (int)j <= rect.Top; j++)
		{

			if(this->lp_tiles[i][j]->HasBuilding())
			{
				this->lp_tiles[i][j]->DrawBuildingFloors();
			}
		}
	}
	glEnd();
}*/

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

void Map::drawBuildingBoxes(dfv::RealIntRect rect) const
{
	rect.trim(this->getTileRect());
	glBegin(GL_QUADS);
	for(int i = rect.xmin; i < rect.xmax; i++)
	{
		for(int j = rect.ymin; j < rect.ymax; j++)
		{
			if(this->lp_tiles.at(i).at(j)->hasBuilding())
			{
				this->lp_tiles.at(i).at(j)->drawBuildingBox();
			}
		}
	}
	glEnd();
}

void Map::drawBuildingOutlines(dfv::RealIntRect rect) const
{
	rect.trim(this->getTileRect());
	glColor3f(0.1, 0.1, 0.1);
	glBegin(GL_QUADS);
	for(int i = rect.xmin; i < rect.xmax; i++)
	{
		for(int j = rect.ymin; j < rect.ymax; j++)
		{
			if(this->lp_tiles.at(i).at(j)->hasBuilding())
			{
				this->lp_tiles.at(i).at(j)->drawBuildingOutline();
			}
		}
	}
	glEnd();
}

void Map::drawBuildingFloors(dfv::RealIntRect rect) const
{
	rect.trim(this->getTileRect());
	glColor3f(0.1, 0.1, 0.1);
	glBegin(GL_QUADS);
	for(int i = rect.xmin; i < rect.xmax; i++)
	{
		for(int j = rect.ymin; j < rect.ymax; j++)
		{
			if(this->lp_tiles.at(i).at(j)->hasBuilding())
			{
				this->lp_tiles.at(i).at(j)->drawBuildingFloors();
			}
		}
	}
	glEnd();
}

void Map::drawStructureBoxes(dfv::RealIntRect rect) const
{
	rect.trim(this->getTileRect());
	glBegin(GL_QUADS);
	glColor3f(0.9, 0.9, 0.9);
	for(int i = rect.xmin; i <= rect.xmax; i++)
	{
		for(int j = rect.ymin; j <= rect.ymax; j++)
		{
			//this->lp_tiles.at(i).at(j)->drawStructureBox();
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
			//this->lp_tiles.at(i).at(j)->drawStructureOutline();
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

bool Map::saveAsMapFormat(std::string filename)
{
	std::ofstream file;
	file.open(filename.c_str(), std::ios::out | std::ios::binary);

	unsigned int count = 0;

	if(file.is_open())
	{
		file.write((char*)&(this->size), sizeof(unsigned int));

		for(unsigned int i = 0; i < this->size; i++)
		{
			for(unsigned int j = 0; j < this->size; j++)
			{
				// heights
				for(unsigned int k = 0; k < 4; k++)
				{
					sf::Vector3f vertex = this->lp_tiles[i][j]->getVertex(k);
					file.write((char*)&(vertex.z), sizeof(float));
				}

				// color
				sf::Color color = this->lp_tiles[i][j]->getSfmlColor();
				file.write((char*)&(color.r), sizeof(unsigned char));
				file.write((char*)&(color.g), sizeof(unsigned char));
				file.write((char*)&(color.b), sizeof(unsigned char));

				// is road
				unsigned int temp;
				if(this->lp_tiles[i][j]->isRoad())
				{
					temp = 2;
					file.write((char*)&(temp), sizeof(unsigned int));
					unsigned int road_type = this->lp_tiles[i][j]->getRoadId();
					unsigned int road_orientation = this->lp_tiles[i][j]->getRoadOrientation();

					// road type
					file.write((char*)&(road_type), sizeof(unsigned int));

					// road orientation
					file.write((char*)&(road_orientation), sizeof(unsigned int));
				}
				else
				{
					temp = 1;
					file.write((char*)&(temp), sizeof(unsigned int));
				}

				// has building
				if(this->lp_tiles[i][j]->hasBuilding())
				{
					temp = 2;
					file.write((char*)&(temp), sizeof(unsigned int));

					// building height
					float building_height = this->lp_tiles[i][j]->getBuildingHeight();
					file.write((char*)&(building_height), sizeof(float));

					// building color
					sf::Color building_color = this->lp_tiles[i][j]->getBuildingColor();
					file.write((char*)&(building_color.r), sizeof(unsigned char));
					file.write((char*)&(building_color.g), sizeof(unsigned char));
					file.write((char*)&(building_color.b), sizeof(unsigned char));
				}
				else
				{
					temp = 1;
					file.write((char*)&(temp), sizeof(unsigned int));
				}

				count++;
			}
		}
		std::cout << "Saved " << count << " tiles." << std::endl;

		file.close();
		return true;
	}
	else
	{
		return false;
	}
}

bool Map::loadFromMapFormat(std::string filename)
{
	std::ifstream file;
	file.open(filename.c_str(), std::ios::in | std::ios::binary);

	if(file.is_open())
	{
		std::cout << "Map file open. Reading data..." << std::endl;

		//float read_value_f;
		//unsigned char read_value_uc;
		unsigned int read_value_ui;

		file.read((char*)&read_value_ui, sizeof(unsigned int));
		this->create(read_value_ui);

		std::cout << "Loading map of size " << this->size << std::endl;

		for(unsigned int i = 0; i < this->size; i++)
		{
			for(unsigned int j = 0; j < this->size; j++)
			{
				float h0, h1, h2, h3;
				file.read((char*)&h0, sizeof(float));
				file.read((char*)&h1, sizeof(float));
				file.read((char*)&h2, sizeof(float));
				file.read((char*)&h3, sizeof(float));

				sf::Color t_color;
				file.read((char*)&t_color.r, sizeof(unsigned char));
				file.read((char*)&t_color.g, sizeof(unsigned char));
				file.read((char*)&t_color.b, sizeof(unsigned char));

				this->lp_tiles[i][j] = new Tile;
				this->lp_tiles[i][j]->create(sf::Vector2f(i, j), h0, h1, h2, h3);
				this->lp_tiles[i][j]->setColor(t_color);

				// is road
				unsigned int is_road_t;
				file.read((char*)&is_road_t, sizeof(unsigned int));
				if(is_road_t == 2)
				{
					unsigned int road_type_t;
					file.read((char*)&road_type_t, sizeof(unsigned int));
					unsigned int road_orientation_t;
					file.read((char*)&road_orientation_t, sizeof(unsigned int));

					this->lp_tiles[i][j]->setAsRoad(true);
					this->lp_tiles[i][j]->addRoad((Road::Type)road_type_t, road_orientation_t);
				}

				unsigned int has_building_t;
				file.read((char*)(&has_building_t), sizeof(unsigned int));
				if(has_building_t == 2)
				{
					float building_height_t;
					file.read((char*)&building_height_t, sizeof(float));

					this->population += building_height_t * 12 * 8;

					sf::Color t_color;
					file.read((char*)&t_color.r, sizeof(unsigned char));
					file.read((char*)&t_color.g, sizeof(unsigned char));
					file.read((char*)&t_color.b, sizeof(unsigned char));

					this->lp_tiles[i][j]->addBuilding(building_height_t);
					this->lp_tiles[i][j]->setBuildingColor(t_color);
				}
			}
		}

		std::cout << "Map loaded. Population: " << this->population << std::endl;

		return true;
	}
	else
	{
		std::cout << "ERROR: could not open map." << std::endl;
		return false;
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

		/*float h0 = this->lp_tiles[floor(pos.x)][floor(pos.y)]->getVertex(0).z;
		float h1 = this->lp_tiles[floor(pos.x)][floor(pos.y)]->getVertex(1).z;
		float h2 = this->lp_tiles[floor(pos.x)][floor(pos.y)]->getVertex(2).z;
		float h3 = this->lp_tiles[floor(pos.x)][floor(pos.y)]->getVertex(3).z;*/

		Tile* lp_tile = this->lp_tiles.at(floor(pos.x)).at(floor(pos.y));
		float h00 = lp_tile->getVertex(0).z;
		float h10 = lp_tile->getVertex(1).z;
		float h11 = lp_tile->getVertex(2).z;
		float h01 = lp_tile->getVertex(3).z;

		//return (1.0/((x1-x0)*(y1-y0)))*(h0*(x1-pos.x)*(y1-pos.y)+h1*(pos.x-x0)*(y1-pos.y)+h2*(pos.x-x0)*(pos.y-y0)+h3*(x1-pos.x)*(pos.y-y0));

		return Utils::interpolate2d(x0, x1, y0, y1, h00, h01, h10, h11, pos.x, pos.y);
	}
	return 0;
	/*else
	{
		std::cout << "test" << std::endl;
		return 0.f;
	}*/
}

dfv::RealRect Map::getRect() const
{
	/*dfv::IntRect rect;
	rect.Left = 0;
	rect.Right = this->size - 1;
	rect.Top = this->size - 1;
	rect.Bottom = 0;
	return rect;*/
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

void Map::generateBuildingList()
{
	this->building_list = glGenLists(1);
	glNewList(this->building_list, GL_COMPILE);
	this->drawBuildingBoxes(this->getTileRect());
	glEndList();
}

void Map::callBuildingList() const
{
	glCallList(this->building_list);
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
	//std::cout << "Calling tile list" << std::endl;
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



/*void Map::DrawRoads(dfv::IntRect rect, const Camera& camera, const Resources& resources) const
{
	dfv::Utils::TrimRect(rect, this->GetRect());
	for(int i = rect.Left; i < rect.Right; i++)
	{
		for(int j = rect.Bottom; j < rect.Top; j++)
		{
			if(this->lp_tiles[i][j]->IsRoad())
			{
				this->lp_tiles[i][j]->DrawRoad(camera, resources);
			}
		}
	}
}*/

void Map::drawRoads(dfv::RealIntRect rect, const Camera& camera, const Resources& resources) const
{
	rect.trim(this->getTileRect());
	glColor3f(1.f, 1.f, 1.f);
	for(int i = floor(rect.xmin); i <= floor(rect.xmax); i++)
	{
		for(int j = floor(rect.ymin); j <= floor(rect.ymax); j++)
		{
			if(this->lp_tiles.at(i).at(j)->isRoad())
			{
				this->lp_tiles.at(i).at(j)->drawRoad(camera, resources);
			}
		}
	}
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
		for(int i = floor(rect.xmin); i < floor(rect.xmax); i++)
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
		for(unsigned int j = floor(rect.ymin); j < floor(rect.ymax); j++)
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

/*void Map::DrawProps(dfv::IntRect rect, const Camera& camera, const Resources& resources) const
{
	if(rect.Left >= this->size) rect.Left = this->size - 1;
	if(rect.Left < 0) rect.Left = 0;
	if(rect.Right >= this->size) rect.Right = this->size - 1;
	if(rect.Right < 0) rect.Right = 0;
	if(rect.Top >= this->size) rect.Top = this->size - 1;
	if(rect.Top < 0) rect.Top = 0;
	if(rect.Bottom >= this->size) rect.Bottom = this->size - 1;
	if(rect.Bottom < 0) rect.Bottom = 0;

	unsigned int quadrant = camera.GetQuadrant();
	if(quadrant == 0)
	{
		unsigned int midpoint = camera.GetPosition().y;
		if(midpoint < 0) midpoint = 0;
		if(midpoint >= this->size) midpoint = this->size - 1;
		for(unsigned int i = rect.Right; i > rect.Left; i--)
		{
			for(unsigned int j = rect.Bottom; j < midpoint; j++)
			{
				this->lp_tiles.at(i).at(j)->DrawProp(camera, resources);
			}
			for(unsigned int j = rect.Top; j >= midpoint; j--)
			{
				this->lp_tiles.at(i).at(j)->DrawProp(camera, resources);
			}
		}
	}
	else if(quadrant == 1)
	{
		unsigned int midpoint = camera.GetPosition().x;
		if(midpoint < 0) midpoint = 0;
		if(midpoint >= this->size) midpoint = this->size - 1;
		for(int j = rect.Top; j > rect.Bottom; j--)
		{
			for(unsigned int i = rect.Left; i < midpoint; i++)
			{
				this->lp_tiles.at(i).at(j)->DrawProp(camera, resources);
			}
			for(unsigned int i = rect.Right; i >= midpoint; i--)
			{
				this->lp_tiles.at(i).at(j)->DrawProp(camera, resources);
			}
		}
	}
	else if(quadrant == 2)
	{
		unsigned int midpoint = camera.GetPosition().y;
		if(midpoint < 0) midpoint = 0;
		if(midpoint >= this->size) midpoint = this->size - 1;
		for(unsigned int i = rect.Left; i < rect.Right; i++)
		{
			for(unsigned int j = rect.Bottom; j < midpoint; j++)
			{
				this->lp_tiles[i][j]->DrawProp(camera, resources);
			}
			for(unsigned int j = rect.Top; j >= midpoint; j--)
			{
				this->lp_tiles[i][j]->DrawProp(camera, resources);
			}
		}
	}
	else if(quadrant == 3)
	{
		unsigned int midpoint = camera.GetPosition().x;
		if(midpoint < 0) midpoint = 0;
		if(midpoint >= this->size) midpoint = this->size - 1;
		for(unsigned int j = rect.Bottom; j < rect.Top; j++)
		{
			for(unsigned int i = rect.Left; i < midpoint; i++)
			{
				this->lp_tiles[i][j]->DrawProp(camera, resources);
			}
			for(unsigned int i = rect.Right; i >= midpoint; i--)
			{
				this->lp_tiles[i][j]->DrawProp(camera, resources);
			}
		}
	}
}*/

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
	//dfv::IntRect rect = this->GetRect();
	if(this->getTileRect().contains(pos))
	{
		return this->lp_tiles[pos.x][pos.y]->setRoadOrientation(orientation);
	}
	else
	{
		return false;
	}
	/*
	if(dfv::Utils::RectContains(rect, pos))
	{
		return this->lp_tiles[pos.x][pos.y]->SetRoadOrientation(orientation);
	}
	else
	{
		return false;
	}*/
}

bool Map::saveAsSgmFormat(const std::string& filename) const
{
	std::ofstream file;
	file.open(filename.c_str(), std::ios::out | std::ios::binary);
	if(file.is_open())
	{
		// map dimensions
		unsigned int width = this->size;
		unsigned int height = this->size;
		file.write((char*)&(width), sizeof(unsigned int));
		file.write((char*)&(height), sizeof(unsigned int));

		// tiles
		for(unsigned int i = 0; i < width; i++)
		{
			for(unsigned int j = 0; j < height; j++)
			{
				// tile heights
				std::vector<sf::Vector3f> tile_vertices = this->lp_tiles[i][j]->getVertices();
				std::vector<float> tile_heights(4);
				for(unsigned int k = 0; k < 4; k++)
				{
					tile_heights[k] = tile_vertices[k].z;
					file.write((char*)&(tile_heights[k]), sizeof(float));
				}

				// tile color
				sf::Color tile_color = this->lp_tiles[i][j]->getSfmlColor();
				unsigned char color_r = tile_color.r;
				unsigned char color_g = tile_color.g;
				unsigned char color_b = tile_color.b;
				file.write((char*)&(color_r), sizeof(unsigned char));
				file.write((char*)&(color_g), sizeof(unsigned char));
				file.write((char*)&(color_b), sizeof(unsigned char));
			}
		}

		return true;
	}
	return false;
}

bool Map::loadFromSgmFormat(const std::string& filename)
{
	return false;
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
		return this->lp_tiles[x][y]->clearRoad();
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

bool Map::clearBuilding(unsigned int x, unsigned int y)
{
	try
	{
		return this->lp_tiles[x][y]->clearBuilding();
	}
	catch(...)
	{
		return false;
	}
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
	return this->lp_tiles.at(x).at(y)->hasStructure();
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
			   this->lp_tiles.at(i).at(j)->getQuad().getMaxheight() < 5.f &&
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
		}
	}

	return true;
}

Lot* Map::getLot(unsigned int x, unsigned int y) const
{
	return this->lp_tiles.at(x).at(y)->lp_lot;
}

} /* namespace dfv */


