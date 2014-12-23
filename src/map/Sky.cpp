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

 * Sky.cpp
 *
 *  Created on: Aug 19, 2013
 *      Author: daniel
 */

#include "Sky.h"

namespace dfv
{

Sky::Sky():
		size(0)
{
	// TODO Auto-generated constructor stub

}

Sky::~Sky()
{
	// TODO Auto-generated destructor stub
}

void Sky::create(float size, sf::Vector2f center, std::string filename)
{
	this->size = size;
	if(!this->sky_img.loadFromFile(filename))
	{
		std::cout << "Could not load sky image" << std::endl;
	}
	unsigned int img_size = this->sky_img.getSize().y / 3;

	this->images.resize(6);
	for(unsigned int i = 0; i < 6; i++)
	{
		this->images[i].create(img_size, img_size, sf::Color(0,0,0));
	}

	this->images[0].copy(this->sky_img, 0, 0, sf::IntRect(img_size, 0, img_size, img_size), false);
	this->images[1].copy(this->sky_img, 0, 0, sf::IntRect(0, img_size, img_size, img_size), false);
	this->images[2].copy(this->sky_img, 0, 0, sf::IntRect(img_size, img_size, img_size, img_size), false);
	this->images[3].copy(this->sky_img, 0, 0, sf::IntRect(2*img_size, img_size, img_size, img_size), false);
	this->images[4].copy(this->sky_img, 0, 0, sf::IntRect(3*img_size, img_size, img_size, img_size), false);
	this->images[5].copy(this->sky_img, 0, 0, sf::IntRect(img_size, 2 * img_size, img_size, img_size), false);

	this->image_handles.resize(6);
	for(unsigned int i = 0; i < 6; i++)
	{
		glGenTextures(1, &this->image_handles[i]);

		glBindTexture(GL_TEXTURE_2D, this->image_handles[i]);
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(
			GL_TEXTURE_2D, 0, GL_RGBA,
			this->images[i].getSize().x, this->images[i].getSize().y,
			0,
			GL_RGBA, GL_UNSIGNED_BYTE, this->images[i].getPixelsPtr()
		);
	}

	this->vertices.resize(8);
	//this->normals.resize(8);

	this->vertices[0] = sf::Vector3f(center.x -size /2, center.y-size/2, -size/2);
	this->vertices[4] = sf::Vector3f(center.x -size /2, center.y-size/2, size/2);

	this->vertices[1] = sf::Vector3f(center.x + size /2, center.y-size/2, -size/2);
	this->vertices[5] = sf::Vector3f(center.x + size /2, center.y-size/2, size/2);

	this->vertices[2] = sf::Vector3f(center.x + size /2, center.y+size/2, -size/2);
	this->vertices[6] = sf::Vector3f(center.x + size /2, center.y+size/2, size/2);

	this->vertices[3] = sf::Vector3f(center.x -size /2, center.y+size/2, -size/2);
	this->vertices[7] = sf::Vector3f(center.x -size /2, center.y+size/2, size/2);
}

void Sky::draw() const
{
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, this->image_handles.at(0));
	glBegin(GL_QUADS);
		//top

		glColor3f(1.f, 1.f, 1.f);
		glTexCoord2d(0.0,0.0);
		glNormal3f(0.f, 0.f, -1.f);
		glVertex3f(this->vertices[7].x, this->vertices[7].y, this->vertices[7].z);

		glColor3f(1.f, 1.f, 1.f);
		glTexCoord2d(1.0,0.0);
		glNormal3f(0.f, 0.f, -1.f);
		glVertex3f(this->vertices[6].x, this->vertices[6].y, this->vertices[6].z);

		glColor3f(1.f, 1.f, 1.f);
		glTexCoord2d(1.0,1.0);
		glNormal3f(0.f, 0.f, -1.f);
		glVertex3f(this->vertices[5].x, this->vertices[5].y, this->vertices[5].z);

		glColor3f(1.f, 1.f, 1.f);
		glTexCoord2d(0.0,1.0);
		glNormal3f(0.f, 0.f, -1.f);
		glVertex3f(this->vertices[4].x, this->vertices[4].y, this->vertices[4].z);


	glEnd();

	glBindTexture(GL_TEXTURE_2D, this->image_handles[1]); ///
	glBegin(GL_QUADS);
		//side 1

		glColor3f(1.f, 1.f, 1.f);
		glTexCoord2d(1.0,1.0);
		glNormal3f(1.f, 0.f, 0.f);
		glVertex3f(this->vertices[0].x, this->vertices[0].y, this->vertices[0].z);

		glColor3f(1.f, 1.f, 1.f);
		glTexCoord2d(0.0,1.0);
		glNormal3f(1.f, 0.f, 0.f);
		glVertex3f(this->vertices[3].x, this->vertices[3].y, this->vertices[3].z);

		glColor3f(1.f, 1.f, 1.f);
		glTexCoord2d(0.0,0.0);
		glNormal3f(1.f, 0.f, 0.f);
		glVertex3f(this->vertices[7].x, this->vertices[7].y, this->vertices[7].z);

		glColor3f(1.f, 1.f, 1.f);
		glTexCoord2d(1.0,0.0);
		glNormal3f(1.f, 0.f, 0.f);
		glVertex3f(this->vertices[4].x, this->vertices[4].y, this->vertices[4].z);


	glEnd();

	glBindTexture(GL_TEXTURE_2D, this->image_handles[4]); ///
	glBegin(GL_QUADS);
		// side 2

		glColor3f(1.f, 1.f, 1.f);
		glTexCoord2d(1.0,1.0);
		glNormal3f(0.f, -1.f, 0.f);
		glVertex3f(this->vertices[3].x, this->vertices[3].y, this->vertices[3].z);

		glColor3f(1.f, 1.f, 1.f);
		glTexCoord2d(0.0,1.0);
		glNormal3f(0.f, -1.f, 0.f);
		glVertex3f(this->vertices[2].x, this->vertices[2].y, this->vertices[2].z);

		glColor3f(1.f, 1.f, 1.f);
		glTexCoord2d(0.0,0.0);
		glNormal3f(0.f, -1.f, 0.f);
		glVertex3f(this->vertices[6].x, this->vertices[6].y, this->vertices[6].z);

		glColor3f(1.f, 1.f, 1.f);
		glTexCoord2d(1.0,0.0);
		glNormal3f(0.f, -1.f, 0.f);
		glVertex3f(this->vertices[7].x, this->vertices[7].y, this->vertices[7].z);

	glEnd();

	glBindTexture(GL_TEXTURE_2D, this->image_handles[2]); ///
	glBegin(GL_QUADS);
		// side 3

		glColor3f(1.f, 1.f, 1.f);
		glTexCoord2d(1.0,1.0);
		glNormal3f(0.f, 1.f, 0.f);
		glVertex3f(this->vertices[1].x, this->vertices[1].y, this->vertices[1].z);

		glColor3f(1.f, 1.f, 1.f);
		glTexCoord2d(0.0,1.0);
		glNormal3f(0.f, 1.f, 0.f);
		glVertex3f(this->vertices[0].x, this->vertices[0].y, this->vertices[0].z);

		glColor3f(1.f, 1.f, 1.f);
		glTexCoord2d(0.0,0.0);
		glNormal3f(0.f, 1.f, 0.f);
		glVertex3f(this->vertices[4].x, this->vertices[4].y, this->vertices[4].z);

		glColor3f(1.f, 1.f, 1.f);
		glTexCoord2d(1.0,0.0);
		glNormal3f(0.f, 1.f, 0.f);
		glVertex3f(this->vertices[5].x, this->vertices[5].y, this->vertices[5].z);

	glEnd();

	glBindTexture(GL_TEXTURE_2D, this->image_handles[3]);
	glBegin(GL_QUADS);
		// side 3

		glColor3f(1.f, 1.f, 1.f);
		glTexCoord2d(1.0,1.0);
		glNormal3f(-1.f, 0.f, 0.f);
		glVertex3f(this->vertices[2].x, this->vertices[2].y, this->vertices[2].z);

		glColor3f(1.f, 1.f, 1.f);
		glTexCoord2d(0.0,1.0);
		glNormal3f(-1.f, 0.f, 0.f);
		glVertex3f(this->vertices[1].x, this->vertices[1].y, this->vertices[1].z);

		glColor3f(1.f, 1.f, 1.f);
		glTexCoord2d(0.0,0.0);
		glNormal3f(-1.f, 0.f, 0.f);
		glVertex3f(this->vertices[5].x, this->vertices[5].y, this->vertices[5].z);

		glColor3f(1.f, 1.f, 1.f);
		glTexCoord2d(1.0,0.0);
		glNormal3f(-1.f, 0.f, 0.f);
		glVertex3f(this->vertices[6].x, this->vertices[6].y, this->vertices[6].z);

	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);

	glEnable(GL_LIGHTING);
}

} /* namespace dfv */
