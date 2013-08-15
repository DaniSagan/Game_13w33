/*
 * Building.cpp
 *
 *  Created on: Aug 12, 2013
 *      Author: daniel
 */

#include "Building.h"

namespace dfv
{

Building::Building():
		height(0.f)
{
	// TODO Auto-generated constructor stub

}

Building::~Building()
{
	// TODO Auto-generated destructor stub
}

void Building::Create(const std::vector<sf::Vector3f>& base_pos, float height)
{
	this->height = height;
	if(base_pos.size() != 4)
	{
		std::cout << "ERROR: Building::Create()" << std::endl;
		return;
	}
	float max_height = base_pos[0].z;
	this->base_pos.resize(4);
	for(unsigned int i = 0; i < 4; i++)
	{
		this->base_pos[i] = base_pos[i];
		if(max_height < base_pos[i].z)
		{
			max_height = base_pos[i].z;
		}
	}

	this->roof_pos.resize(4);
	for(unsigned int i = 0; i < 4; i++)
	{
		this->roof_pos[i].x = base_pos[i].x;
		this->roof_pos[i].y = base_pos[i].y;
		this->roof_pos[i].z = max_height + height;
	}

	float floor_delta = 0.02;

	this->floor_pos.resize(4);
	this->floor_pos[0] = sf::Vector2f(base_pos[0].x - floor_delta, base_pos[0].y - floor_delta);
	this->floor_pos[1] = sf::Vector2f(base_pos[1].x + floor_delta, base_pos[1].y - floor_delta);
	this->floor_pos[2] = sf::Vector2f(base_pos[2].x + floor_delta, base_pos[2].y + floor_delta);
	this->floor_pos[3] = sf::Vector2f(base_pos[3].x - floor_delta, base_pos[3].y + floor_delta);

	this->floor_heights.resize(height / 0.125f);
	for(unsigned int i = 0; i < this->floor_heights.size(); i++)
	{
		this->floor_heights[i] = max_height + 0.125*((float)i + 1) - 0.02f;
	}
}

void Building::SetColor(const sf::Color& color)
{
	sf::Vector3f col(color.r / 255.f, color.g / 255.f, color.b / 255.f);
	this->colors.resize(5);
	this->colors[0] = sf::Vector3f(col.x, col.y, col.z); // roof
	this->colors[1] = sf::Vector3f(col.x*0.4, col.y*0.4, col.z*0.4); // roof
	this->colors[2] = sf::Vector3f(col.x*0.5, col.y*0.5, col.z*0.5); // roof
	this->colors[3] = sf::Vector3f(col.x*0.6, col.y*0.6, col.z*0.6); // roof
	this->colors[4] = sf::Vector3f(col.x*0.7, col.y*0.7, col.z*0.7); // roof
}

void Building::Draw(const bool draw_floors) const
{
	glBegin(GL_QUADS);
		// roof
		glColor3f(this->colors[0].x, this->colors[0].y, this->colors[0].z);
		glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(this->roof_pos[0].x, this->roof_pos[0].y, this->roof_pos[0].z);
		glVertex3f(this->roof_pos[1].x, this->roof_pos[1].y, this->roof_pos[1].z);
		glVertex3f(this->roof_pos[2].x, this->roof_pos[2].y, this->roof_pos[2].z);
		glVertex3f(this->roof_pos[3].x, this->roof_pos[3].y, this->roof_pos[3].z);

		// side 1
		//glColor3f(this->colors[1].x, this->colors[1].y, this->colors[1].z);
		glNormal3f(0.0, -1.0, 0.0);
		glTexCoord2d(0.0,0.0);
		glVertex3f(this->base_pos[0].x, this->base_pos[0].y, this->base_pos[0].z);
		glTexCoord2d(0.0,1.0);
		glVertex3f(this->base_pos[1].x, this->base_pos[1].y, this->base_pos[1].z);
		glTexCoord2d(1.0,1.0);
		glVertex3f(this->roof_pos[1].x, this->roof_pos[1].y, this->roof_pos[1].z);
		glTexCoord2d(1.0,0.0);
		glVertex3f(this->roof_pos[0].x, this->roof_pos[0].y, this->roof_pos[0].z);

		// side 2
		//glColor3f(this->colors[2].x, this->colors[2].y, this->colors[2].z);
		glNormal3f(1.0, 0.0, 0.0);
		glVertex3f(this->base_pos[1].x, this->base_pos[1].y, this->base_pos[1].z);
		glVertex3f(this->base_pos[2].x, this->base_pos[2].y, this->base_pos[2].z);
		glVertex3f(this->roof_pos[2].x, this->roof_pos[2].y, this->roof_pos[2].z);
		glVertex3f(this->roof_pos[1].x, this->roof_pos[1].y, this->roof_pos[1].z);

		// side 3
		//glColor3f(this->colors[3].x, this->colors[3].y, this->colors[3].z);
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(this->base_pos[2].x, this->base_pos[2].y, this->base_pos[2].z);
		glVertex3f(this->base_pos[3].x, this->base_pos[3].y, this->base_pos[3].z);
		glVertex3f(this->roof_pos[3].x, this->roof_pos[3].y, this->roof_pos[3].z);
		glVertex3f(this->roof_pos[2].x, this->roof_pos[2].y, this->roof_pos[2].z);

		// side 4
		//glColor3f(this->colors[4].x, this->colors[4].y, this->colors[4].z);
		glNormal3f(-1.0, 0.0, 0.0);
		glVertex3f(this->base_pos[3].x, this->base_pos[3].y, this->base_pos[3].z);
		glVertex3f(this->base_pos[0].x, this->base_pos[0].y, this->base_pos[0].z);
		glVertex3f(this->roof_pos[0].x, this->roof_pos[0].y, this->roof_pos[0].z);
		glVertex3f(this->roof_pos[3].x, this->roof_pos[3].y, this->roof_pos[3].z);

		if(draw_floors == true)
		{
			glColor3f(0.1f, 0.1f, 0.1f);
			for(unsigned int i = 0; i < this->floor_heights.size(); i++)
			{
				glNormal3f(0.0, 0.0, -1.0);
				glVertex3f(this->floor_pos[0].x, this->floor_pos[0].y, this->floor_heights[i]);
				glVertex3f(this->floor_pos[1].x, this->floor_pos[1].y, this->floor_heights[i]);
				glVertex3f(this->floor_pos[2].x, this->floor_pos[2].y, this->floor_heights[i]);
				glVertex3f(this->floor_pos[3].x, this->floor_pos[3].y, this->floor_heights[i]);

				if(i < 20)
				{
					for(unsigned int j = 0; j < 4; j++)
					{
						glVertex3f(this->floor_pos[j % 4].x, this->floor_pos[j % 4].y, this->floor_heights[i]);
						glVertex3f(this->floor_pos[(j + 1) % 4].x, this->floor_pos[(j + 1) % 4].y, this->floor_heights[i]);
						glVertex3f(this->floor_pos[(j + 1) % 4].x, this->floor_pos[(j + 1) % 4].y, this->floor_heights[i] + 0.01f);
						glVertex3f(this->floor_pos[j % 4].x, this->floor_pos[j % 4].y, this->floor_heights[i] + 0.01f);
					}
				}
			}
		}
	glEnd();
}

float Building::GetHeight() const
{
	return this->height;
}

} /* namespace dfv */
