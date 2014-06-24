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
		lp_road(NULL)
{
	// TODO Auto-generated constructor stub

}

Tile::~Tile()
{
	if(lp_building != NULL) delete this->lp_building;
	if(lp_road != NULL) delete this->lp_road;
	// TODO Auto-generated destructor stub
}

void Tile::Create(sf::Vector2f pos, float h0, float h1, float h2, float h3)
{
	this->vertices.resize(4);
	this->vertices[0] = sf::Vector3f(pos.x, pos.y, h0);
	this->vertices[1] = sf::Vector3f(pos.x + 1.0, pos.y, h1);
	this->vertices[2] = sf::Vector3f(pos.x + 1.0, pos.y + 1.0, h2);
	this->vertices[3] = sf::Vector3f(pos.x , pos.y + 1.0, h3);

	this->normals.resize(4);
	this->normals[0] = dfv::Utils::Cross(
			dfv::Utils::Diff(this->vertices[1], this->vertices[0]),
			dfv::Utils::Diff(this->vertices[3], this->vertices[0]));
	this->normals[1] = dfv::Utils::Cross(
			dfv::Utils::Diff(this->vertices[2], this->vertices[1]),
			dfv::Utils::Diff(this->vertices[0], this->vertices[1]));
	this->normals[2] = dfv::Utils::Cross(
			dfv::Utils::Diff(this->vertices[3], this->vertices[2]),
			dfv::Utils::Diff(this->vertices[1], this->vertices[2]));
	this->normals[3] = dfv::Utils::Cross(
			dfv::Utils::Diff(this->vertices[0], this->vertices[3]),
			dfv::Utils::Diff(this->vertices[2], this->vertices[3]));

	this->colors.resize(4);

}

void Tile::SetColor(sf::Color color)
{
	this->color.x = (float)color.r / 255.f;
	this->color.y = (float)color.g / 255.f;
	this->color.z = (float)color.b / 255.f;

	for(unsigned int i = 0; i < 4; i++)
	{
		if(this->vertices[i].z < 1.0)
		{
			this->colors[i] = sf::Vector3f(0.1f, 0.1f, 0.5f);
		}
		else if(this->vertices[i].z < 1.1f)
		{
			float rr1 = ((float)rand() / (float)RAND_MAX) * 0.1f;
			float rr2 = ((float)rand() / (float)RAND_MAX) * 0.1f;
			float rr3 = ((float)rand() / (float)RAND_MAX) * 0.1f;
			this->colors[i] = sf::Vector3f(0.9f + rr1, 0.9f + rr2, 0.4f + rr3);
		}
		else if(this->vertices[i].z > 19.0)
		{
			this->colors[i] = sf::Vector3f(0.9f, 0.9f, 0.95f);
		}
		else
		{
			this->colors[i] = sf::Vector3f(this->color.x, this->color.y, this->color.z);
			//this->colors[i] = sf::Vector3f(0.5f, 0.5f, 0.5f);
		}
	}
}

void Tile::Draw(const dfv::Camera& camera, const dfv::Resources& resources) const
{
	if(this->HasBuilding() == false)
	{
		//sf::Vector3f position = camera.GetPosition();
		//if(this->IsRoad() && fabs(position.x - this->vertices[0].x) < 50 && fabs(position.y - this->vertices[0].y) < 50)
		//{
			/*glBindTexture(GL_TEXTURE_2D, resources.img_roads_handles[0]);
			glBegin(GL_QUADS);
				//glTexCoord2d(0.0,0.0);
				glColor3f(1.f, 1.f, 1.f);
				glTexCoord2d(0.0,0.0);
				glNormal3f(this->normals[0].x, this->normals[0].y, this->normals[0].z);
				glVertex3f(this->vertices[0].x, this->vertices[0].y, this->vertices[0].z);

				glTexCoord2d(1.0,0.0);
				glNormal3f(this->normals[1].x, this->normals[1].y, this->normals[1].z);
				glVertex3f(this->vertices[1].x, this->vertices[1].y, this->vertices[1].z);

				glTexCoord2d(1.0,1.0);
				glNormal3f(this->normals[2].x, this->normals[2].y, this->normals[2].z);
				glVertex3f(this->vertices[2].x, this->vertices[2].y, this->vertices[2].z);

				glTexCoord2d(0.0,1.0);
				glNormal3f(this->normals[3].x, this->normals[3].y, this->normals[3].z);
				glVertex3f(this->vertices[3].x, this->vertices[3].y, this->vertices[3].z);
			glEnd();
			glBindTexture(GL_TEXTURE_2D, 0);*/
			//this->lp_road->Draw(camera, resources);
		//}
		//else
		{
			glBegin(GL_QUADS);
				//glTexCoord2d(0.0,0.0);
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
			glEnd();
		}
	}

	/*if(this->lp_building != NULL)
	{
		this->lp_building->Draw();
	}*/

}

void Tile::AddBuilding(float height)
{
	this->lp_building = new Building;
	this->lp_building->Create(this->vertices, height);//1.f + 0.0001f * ((float)(rand() % 100)*(float)(rand() % 100)));
	this->lp_building->SetColor(sf::Color(160 + rand() % 70, 160 + rand() % 70, 160 + rand() % 70));
}

bool Tile::HasBuilding() const
{
	return this->lp_building != NULL;
}

void Tile::DrawBuilding(const bool draw_floors) const
{
	if(this->lp_building != NULL)
	{
		this->lp_building->Draw(draw_floors);
	}
}

sf::Color Tile::GetBuildingColor() const
{
	if(this->HasBuilding())
	{
		return this->lp_building->GetColor();
	}
	else
	{
		return sf::Color(0, 0, 0);
	}
}

void Tile::SetAsRoad(const bool r)
{
	this->is_road = r;
}

bool Tile::IsRoad() const
{
	return this->is_road;
}

float Tile::GetBuildingHeight() const
{
	if(this->HasBuilding())
	{
		return this->lp_building->GetHeight();
	}
	else
	{
		return 0.f;
	}
}

void Tile::AddRoad(dfv::Road::Type type, unsigned int orientation)
{
	this->is_road = true;
	this->lp_road = new Road;
	this->lp_road->Create(this->vertices, type, orientation);
}

unsigned int Tile::GetRoadId() const
{
	if(this->IsRoad())
	{
		return this->lp_road->GetId();
	}
	else
	{
		return Road::straight;
	}

}

unsigned int Tile::GetRoadOrientation() const
{
	if(this->IsRoad())
	{
		return this->lp_road->GetOrientation();
	}
	else
	{
		return 0;
	}
}

bool Tile::SetRoadId(unsigned int road_id)
{
	if(this->IsRoad())
	{
		this->lp_road->SetId(road_id);
		return true;
	}
	else
	{
		return false;
	}
}

bool Tile::SetRoadOrientation(unsigned int road_orientation)
{
	if(this->IsRoad())
	{
		this->lp_road->SetOrientation(road_orientation);
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

sf::Vector3f Tile::GetVertex(const unsigned int index) const
{
	if(index < 4)
	{
		return this->vertices[index];
	}
	return this->vertices.back();
}

const std::vector<sf::Vector3f> & Tile::GetVertices() const
{
	/*std::vector<sf::Vector3f> res;
	res.resize(4);
	res[0] = this->vertices[0];
	res[1] = this->vertices[1];
	res[2] = this->vertices[2];
	res[3] = this->vertices[3];
	return res;*/
	return this->vertices;
}

void Tile::DrawBuildingBox() const
{
	this->lp_building->DrawBox();
}

void Tile::DrawBuildingOutline() const
{
	this->lp_building->DrawOutline();
}

void Tile::DrawBuildingFloors() const
{
	this->lp_building->DrawFloors();
}

sf::Vector3f Tile::GetColor(unsigned int index) const
{
	return this->colors[index];
}

sf::Vector3f Tile::GetNormal(unsigned int index) const
{
	return this->normals[index];
}

sf::Vector3f Tile::GetBuildingColor3f() const
{
	return this->lp_building->GetColor3f();
}

void Tile::SetVertex(const unsigned int index, const sf::Vector3f& vertex)
{
	this->vertices[index] = vertex;
}

sf::Color Tile::GetColor() const
{
	return sf::Color(this->color.x * 255.f, this->color.y * 255.f, this->color.z * 255.f);
}

void Tile::SetBuildingColor(const sf::Color& color)
{
	this->lp_building->SetColor(color);
}

void Tile::DrawRoad(const Camera& camera, const Resources& resources) const
{
	if(this->IsRoad())
	{
		this->lp_road->Draw(camera, resources);
	}
}

void Tile::DrawProp(const Camera& camera, const Resources& resources) const
{
	if(this->lp_prop != NULL)
	{
		this->lp_prop->Draw(camera, resources);
	}
}

bool Tile::isWater() const
{
	float threshold = 1.1;
	return (this->vertices[0].z < threshold ||
			this->vertices[1].z < threshold ||
			this->vertices[2].z < threshold ||
			this->vertices[3].z < threshold);
}

} /* namespace dfv */
