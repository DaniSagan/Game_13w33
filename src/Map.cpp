/*
 * Map.cpp
 *
 *  Created on: Aug 11, 2013
 *      Author: daniel
 */

#include "Map.h"

namespace dfv
{

Map::Map():
		size(0)
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

void Map::Create(unsigned int size)
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
}

void Map::GenerateTiles()
{
	for(unsigned int i = 0; i < this->lp_tiles.size(); i++)
	{
		for(unsigned int j = 0; j < this->lp_tiles.size(); j++)
		{
			this->lp_tiles[i][j] = new Tile;
			this->lp_tiles[i][j]->Create(
					sf::Vector2f(i, j),
					this->heights[i][j],
					this->heights[i+1][j],
					this->heights[i+1][j+1],
					this->heights[i][j+1]);
			this->lp_tiles[i][j]->SetColor(sf::Color(10 + rand() % 20, 130 + rand() % 20, 10 + rand() % 20));
		}
	}
}

void Map::CreateFromFile(std::string filename, unsigned int water_level, float max_height)
{


	sf::Image heightmap;
	heightmap.LoadFromFile(filename);
	this->size = heightmap.GetHeight() - 1;
	this->heights.resize(this->size + 1);

	for(unsigned int i = 0; i < this->size + 1; i++)
	{
		this->heights[i].resize(this->size + 1);
		for(unsigned int j = 0; j < this->size + 1; j++)
		{
			// generate height map
			sf::Color col = heightmap.GetPixel(i, this->size - j);
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
			lp_tile->Create(
					sf::Vector2f(i, j),
					this->heights[i][j],
					this->heights[i+1][j],
					this->heights[i+1][j+1],
					this->heights[i][j+1]);
			lp_tile->SetColor(sf::Color(20 + rand() % 20, 180 + rand() % 20, 20 + rand() % 20));
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
					this->lp_tiles[i][j]->AddBuilding(0.5f + 0.00001f* (200.f/(float)(0.03*(x*x + y*y) + 50)) * ((float)(rand() % 100)*(float)(rand() % 100) * (float)(rand() % 100)));
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
					this->lp_tiles[i][j]->SetColor(sf::Color(50 + rr, 50 + rr, 50 + rr));
				}
			}
			if(this->heights[i][j] < 1.1f &&
			   this->heights[i+1][j] < 1.1f &&
			   this->heights[i+1][j+1] < 1.1f &&
			   this->heights[i][j+1] < 1.1f)
			{
				// beach
				this->lp_tiles[i][j]->SetColor(sf::Color(200 + rand() % 10, 200 + rand() % 10, 110 + rand() % 10));
			}
		}
	}
	//std::cout << "No. of buildings: " << building_count << std::endl;
}

void Map::CreateRandom(const unsigned int size)
{
	this->size = size;

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
			this->heights[i][j] = 5.0 * (pow(sin(0.01 * sqrt(pow(x - 50, 2.0) + pow(y - 50, 2.0))), 2.0) -
										  0.4 * pow(sin(0.02 * sqrt(pow(x1, 2.0) + pow(y1, 2.0))), 2.0) -
										  0.3 * pow(sin(0.04 * sqrt(pow(x2, 2.0) + pow(y2, 2.0))), 2.0) +
										  0.1 * pow(sin(0.1 * sqrt(pow(x2, 2.0) + pow(y2, 2.0))), 2.0) +
										  0.1 * pow((sin(0.1* x) + sin(0.1*y)), 2.0));
			this->heights[i][j] = 0.1 * this->heights[i][j] * this->heights[i][j] + 0.9f;
			if(this->heights[i][j] < 1.0)
			{
				this->heights[i][j] = 0.99;
			}
		}
	}

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
			lp_tile->Create(
					sf::Vector2f(i, j),
					this->heights[i][j],
					this->heights[i+1][j],
					this->heights[i+1][j+1],
					this->heights[i][j+1]);
			lp_tile->SetColor(sf::Color(20 + rand() % 20, 180 + rand() % 20, 20 + rand() % 20));
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
					this->lp_tiles[i][j]->AddBuilding(0.5f + 0.00001f* (200.f/(float)(0.03*(x*x + y*y) + 50)) * ((float)(rand() % 100)*(float)(rand() % 100) * (float)(rand() % 100)));
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
					this->lp_tiles[i][j]->SetColor(sf::Color(50 + rr, 50 + rr, 50 + rr));
					this->lp_tiles[i][j]->AddRoad(dfv::Road::straight, 0);
					//this->lp_tiles[i][j]->SetAsRoad(true);
				}
			}
			if(this->heights[i][j] < 1.1f &&
			   this->heights[i+1][j] < 1.1f &&
			   this->heights[i+1][j+1] < 1.1f &&
			   this->heights[i][j+1] < 1.1f)
			{
				// beach
				this->lp_tiles[i][j]->SetColor(sf::Color(200 + rand() % 10, 200 + rand() % 10, 110 + rand() % 10));
			}
		}
	}
	std::cout << "No. of buildings: " << building_count << std::endl;
}

void Map::Draw(sf::Window& window, const dfv::Camera& camera, const dfv::Resources& resources) const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(camera.GetRpy().x, 1.f, 0.f, 0.f);
	glRotatef(camera.GetRpy().y, 0.f, 1.f, 0.f);
	glRotatef(camera.GetRpy().z, 0.f, 0.f, 1.f);
	glTranslatef(-camera.GetPosition().x, -camera.GetPosition().y, -camera.GetPosition().z);

	if(camera.GetRpy().x > -20.f)
	{
		for(unsigned int i = 0; i < size; i++)
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
				this->lp_tiles[i][j]->DrawBuilding(false);
			}
		}
	}

	else
	{

		unsigned int quadrant;
		if(camera.GetRpy().z >= 315.f || camera.GetRpy().z < 45.f) quadrant = 1;
		if(camera.GetRpy().z >= 45.f && camera.GetRpy().z < 135.f) quadrant = 0;
		if(camera.GetRpy().z >= 135.f && camera.GetRpy().z < 225.f) quadrant = 3;
		if(camera.GetRpy().z >= 225.f && camera.GetRpy().z < 315.f) quadrant = 2;

		sf::Vector2i cam_pos(camera.GetPosition().x, camera.GetPosition().y);

		if(cam_pos.x < 0) cam_pos.x = 0;
		if(cam_pos.y < 0) cam_pos.y = 0;
		if(cam_pos.x > this->size) cam_pos.x = this->size;
		if(cam_pos.y > this->size) cam_pos.y = this->size;

		int draw_floor_radius = 30;

		if(quadrant == 0)
		{
			cam_pos.x -= 5;
			if(cam_pos.x < 0) cam_pos.x = 0;

			for(int i = cam_pos.x; i < this->size; i++)
			{
				for(int j = 0; j < this->size; j++)
				{
					this->lp_tiles[i][j]->Draw(camera, resources);
				}
			}

			for(int i = cam_pos.x; i < this->size; i++)
			{
				for(int j = 0; j < this->size; j++)
				{
					this->lp_tiles[i][j]->DrawBuilding(i < cam_pos.x + draw_floor_radius && j > cam_pos.y - draw_floor_radius && j < cam_pos.y + draw_floor_radius);
				}
			}
		}

		else if(quadrant == 1)
		{
			cam_pos.y -= 5;
			if(cam_pos.y < 0) cam_pos.y = 0;

			for(int i = 0; i < this->size; i++)
			{
				for(int j = cam_pos.y; j < this->size; j++)
				{
					this->lp_tiles[i][j]->Draw(camera, resources);
				}
			}

			for(int i = 0; i < this->size; i++)
			{
				for(int j = cam_pos.y; j < this->size; j++)
				{
					this->lp_tiles[i][j]->DrawBuilding(j < cam_pos.y + draw_floor_radius && i > cam_pos.x - draw_floor_radius && i < cam_pos.x + draw_floor_radius);
				}
			}
		}

		else if(quadrant == 2)
		{
			cam_pos.x += 5;
			if(cam_pos.x > this->size) cam_pos.x = this->size;

			for(int i = 0; i < cam_pos.x; i++)
			{
				for(unsigned int j = 0; j < size; j++)
				{
					this->lp_tiles[i][j]->Draw(camera, resources);
				}
			}

			for(int i = 0; i < cam_pos.x; i++)
			{
				for(unsigned int j = 0; j < size; j++)
				{
					this->lp_tiles[i][j]->DrawBuilding(i > cam_pos.x - draw_floor_radius && j > cam_pos.y - draw_floor_radius && j < cam_pos.y + draw_floor_radius);
				}
			}
		}

		else if(quadrant == 3)
		{
			cam_pos.y += 5;
			if(cam_pos.y > this->size) cam_pos.y = this->size;

			for(int i = 0; i < this->size; i++)
			{
				for(int j = 0; j < cam_pos.y; j++)
				{
					this->lp_tiles[i][j]->Draw(camera, resources);
				}
			}

			for(int i = 0; i < this->size; i++)
			{
				for(int j = 0; j < cam_pos.y; j++)
				{
					this->lp_tiles[i][j]->DrawBuilding(j > cam_pos.y - draw_floor_radius && i > cam_pos.x - draw_floor_radius && i < cam_pos.x + draw_floor_radius);
				}
			}
		}

		else
		{
			std::cout << "ERROR: quadrant" << std::endl;
		}

	}

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

unsigned int Map::GetSize() const
{
	return this->size;
}

float Map::GetHeight(int x, int y)
{
	if(x < 0) x = 0;
	if(x >= (int)this->size) x = this->size - 1;
	if(y < 0) y = 0;
	if(y >= (int)this->size) y = this->size - 1;

	return this->heights[x][y];
}

bool Map::SaveHeightMap(const std::string& filename)
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

bool Map::LoadHeightMap(const std::string& filename)
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
		this->Create(size);

		std::cout << "Reading heights..." << std::endl;
		for(unsigned int i = 0; i < this->heights.size(); i++)
		{
			for(unsigned int j = 0; j < this->heights.size(); j++)
			{
				file.read((char*)&(this->heights[i][j]), sizeof(float));
			}
		}

		std::cout << "Generating tiles..." << std::endl;
		this->GenerateTiles();

		file.close();
		std::cout << "Height Map loaded" << std::endl;
		return true;
	}
	else
	{
		return false;
	}

}

bool Map::SaveBuildingMap(const std::string& filename)
{
	sf::Image img;
	img.Create(this->size, this->size, sf::Color(0, 0, 0));

	for(unsigned int i = 0; i < this->size; i++)
	{
		for(unsigned int j = 0; j < this->size; j++)
		{
			if(this->lp_tiles[i][j]->IsRoad())
			{
				img.SetPixel(i, this->size - j - 1, sf::Color(255, 0, 0));
			}
			else if(this->lp_tiles[i][j]->HasBuilding())
			{
				float h = this->lp_tiles[i][j]->GetBuildingHeight();
				unsigned char hh = (h > 255 * 8) ? 255 : h * 8;
				img.SetPixel(i, this->size - j - 1, sf::Color(0, hh, 0));
			}
		}
	}

	return img.SaveToFile(filename);
}

bool Map::LoadBuildingMap(const std::string& filename)
{
	sf::Image img;
	img.LoadFromFile(filename);
	if(img.GetHeight() == this->size && img.GetWidth() == this->size)
	{
		for(unsigned int i = 0; i < this->size; i++)
		{
			for(unsigned int j = 0; j < this->size; j++)
			{
				sf::Color pix = img.GetPixel(i, this->size - j - 1);
				unsigned char gg = pix.g;
				unsigned char rr = pix.r;
				if(rr == 255)
				{
					this->lp_tiles[i][j]->SetAsRoad(true);
					//this->lp_tiles[i][j]->AddRoad(dfv::Road::straight, 0);
					unsigned int ra = rand() % 5;
					this->lp_tiles[i][j]->SetColor(sf::Color(50 + ra, 50 + ra, 50 + ra));
				}
				if(gg > 0)
				{
					this->lp_tiles[i][j]->AddBuilding((float)gg / 8.0);
				}
			}
		}

		// Setting road types
		for(unsigned int i = 0; i < this->size; i++)
		{
			for(unsigned int j = 0; j < this->size; j++)
			{
				if(this->lp_tiles[i][j]->IsRoad())
				{
					std::vector<bool> has_road(7, false);
					has_road[0] = (i == this->size - 1) ? false : this->lp_tiles[i+1][j]->IsRoad();
					has_road[1] = (i == this->size - 1) || (j == this->size - 1) ? false : this->lp_tiles[i+1][j+1]->IsRoad();
					has_road[2] = (j == this->size - 1) ? false : this->lp_tiles[i][j+1]->IsRoad();
					has_road[3] = (i == 0) || (j == this->size - 1) ? false : this->lp_tiles[i-1][j+1]->IsRoad();
					has_road[4] = (i == 0) ? false : this->lp_tiles[i-1][j]->IsRoad();
					has_road[5] = (i == 0) || (j == 0) ? false : this->lp_tiles[i-1][j-1]->IsRoad();
					has_road[6] = (j == 0) ? false : this->lp_tiles[i][j-1]->IsRoad();
					has_road[7] = (i == this->size - 1) || (j == 0) ? false : this->lp_tiles[i+1][j-1]->IsRoad();

					if(has_road[2] && has_road[6] && !has_road[0] && !has_road[4])
					{
						this->lp_tiles[i][j]->AddRoad(dfv::Road::straight, 0);
					}

					else if(!has_road[2] && !has_road[6] && has_road[0] && has_road[4])
					{
						this->lp_tiles[i][j]->AddRoad(dfv::Road::straight, 1);
					}

					else if(has_road[2] && has_road[6] && has_road[0] && has_road[4])
					{
						this->lp_tiles[i][j]->AddRoad(dfv::Road::cross, 1);
					}

					else if(has_road[2] && has_road[4] && !has_road[0] && !has_road[6])
					{
						this->lp_tiles[i][j]->AddRoad(dfv::Road::curve, 0);
					}

					else if(has_road[0] && has_road[2] && !has_road[4] && !has_road[6])
					{
						this->lp_tiles[i][j]->AddRoad(dfv::Road::curve, 1);
					}

					else if(has_road[0] && has_road[6] && !has_road[2] && !has_road[4])
					{
						this->lp_tiles[i][j]->AddRoad(dfv::Road::curve, 2);
					}

					else if(has_road[4] && has_road[6] && !has_road[2] && !has_road[0])
					{
						this->lp_tiles[i][j]->AddRoad(dfv::Road::curve, 3);
					}

					else if(has_road[2] && has_road[4] && has_road[6] && !has_road[0])
					{
						this->lp_tiles[i][j]->AddRoad(dfv::Road::tcross, 0);
					}

					else if(has_road[0] && has_road[4] && has_road[6] && !has_road[2])
					{
						this->lp_tiles[i][j]->AddRoad(dfv::Road::tcross, 3);
					}

					else if(has_road[0] && has_road[2] && has_road[6] && !has_road[4])
					{
						this->lp_tiles[i][j]->AddRoad(dfv::Road::tcross, 2);
					}

					else if(has_road[0] && has_road[2] && has_road[4] && !has_road[6])
					{
						this->lp_tiles[i][j]->AddRoad(dfv::Road::tcross, 1);
					}

					else if(has_road[0] && !has_road[2] && !has_road[4] && !has_road[6])
					{
						this->lp_tiles[i][j]->AddRoad(dfv::Road::straight, 1);
					}

					else if(!has_road[0] && has_road[2] && !has_road[4] && !has_road[6])
					{
						this->lp_tiles[i][j]->AddRoad(dfv::Road::straight, 2);
					}

					else if(!has_road[0] && !has_road[2] && has_road[4] && !has_road[6])
					{
						this->lp_tiles[i][j]->AddRoad(dfv::Road::straight, 3);
					}

					else if(!has_road[0] && !has_road[2] && !has_road[4] && has_road[6])
					{
						this->lp_tiles[i][j]->AddRoad(dfv::Road::straight, 0);
					}

					else
					{
						this->lp_tiles[i][j]->AddRoad(dfv::Road::straight, 0);
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

void Map::GenerateMapImg(const unsigned int tile_size)
{

	this->map_img.Create(this->size * tile_size, this->size * tile_size, sf::Color(200,200,200));

	for(unsigned int i = 0; i < this->size; i++)
	{
		for(unsigned int j = 0; j < this->size; j++)
		{
			if(this->lp_tiles[i][j]->IsRoad())
			{
				dfv::Utils::DrawRectangle(this->map_img, sf::Vector2i(i*tile_size, j*tile_size), sf::Vector2i((i+1)*tile_size- 1, (j+1)*tile_size - 1), sf::Color(50, 50, 50));
			}
			if(this->lp_tiles[i][j]->HasBuilding())
			{
				dfv::Utils::DrawRectangle(this->map_img, sf::Vector2i(i*tile_size, j*tile_size), sf::Vector2i((i+1)*tile_size - 1, (j+1)*tile_size - 1), sf::Color(0, 0, 0));
				dfv::Utils::DrawRectangle(this->map_img, sf::Vector2i(i*tile_size+1, j*tile_size+1), sf::Vector2i((i+1)*tile_size - 2, (j+1)*tile_size - 2), this->lp_tiles[i][j]->GetBuildingColor());
			}
		}
	}

	this->map_img.SaveToFile("res/map/map_img.png");
}

bool Map::IsRoad(const sf::Vector2i& tile_pos) const
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
}

bool Map::HasBuilding(const sf::Vector2i& tile_pos) const
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
}

sf::Color Map::GetBuildingColor(const sf::Vector2i& tile_pos) const
{
	if(tile_pos.x >= 0 && tile_pos.x < (int)this->size &&
	   tile_pos.y >= 0 && tile_pos.y < (int)this->size)
	{
		return this->lp_tiles[tile_pos.x][tile_pos.y]->GetBuildingColor();
	}
	else
	{
		return sf::Color(0, 0, 0);
	}
}

bool Map::ChangeRoadType(const sf::Vector2i& tile_pos)
{
	if(this->IsRoad(tile_pos))
	{
		const unsigned int road_type = this->lp_tiles[tile_pos.x][tile_pos.y]->GetRoadType();
		if(road_type >= Road::count)
		{
			this->lp_tiles[tile_pos.x][tile_pos.y]->SetRoadType(Road::straight);
		}
		else
		{
			this->lp_tiles[tile_pos.x][tile_pos.y]->SetRoadType((Road::Type)(road_type + 1));
		}
		return true;
	}
	else
	{
		return false;
	}
}

bool Map::ChangeRoadOrientation(const sf::Vector2i& tile_pos)
{
	std::cout << "Changing road orientation" << std::endl;
	if(this->IsRoad(tile_pos))
	{
		std::cout << "Is road" << std::endl;
		const unsigned int road_orientation = this->lp_tiles[tile_pos.x][tile_pos.y]->GetRoadOrientation();
		if(road_orientation >= 4)
		{
			this->lp_tiles[tile_pos.x][tile_pos.y]->SetRoadOrientation(0);
			std::cout << "Road orient set to 0" << std::endl;
		}
		else
		{
			this->lp_tiles[tile_pos.x][tile_pos.y]->SetRoadOrientation(road_orientation + 1);
			std::cout << "Road orient set to " << road_orientation + 1 << std::endl;
		}
		return true;
	}
	else
	{
		return false;
	}
}

} /* namespace dfv */
