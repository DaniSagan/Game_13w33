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

 * Resources.cpp
 *
 *  Created on: Aug 12, 2013
 *      Author: daniel
 */

#include "Resources.h"

namespace dfv
{



Resources::Resources():
		img_1_handle(0)
{
	// TODO Auto-generated constructor stub

}

Resources::~Resources()
{
	// TODO Auto-generated destructor stub
}

bool Resources::load()
{
	/*if(!this->img_1.LoadFromFile("res/road/r0.png"))
	{
		std::cout << "ERROR: Texture not found" << std::endl;
		return false;
	}
	glGenTextures(1, &this->img_1_handle);
	glBindTexture(GL_TEXTURE_2D, img_1_handle);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	glTexImage2D(
	    GL_TEXTURE_2D, 0, GL_RGBA,
	    img_1.GetWidth(), img_1.GetHeight(),
	    0,
	    GL_RGBA, GL_UNSIGNED_BYTE, img_1.GetPixelsPtr()
	);*/

	const unsigned int img_road_count = 7;
	this->img_roads.resize(img_road_count);
	this->img_roads_handles.resize(img_road_count);
	for(unsigned int i = 0; i < img_road_count; i++)
	{
		std::stringstream ss;
		ss << "res/road/r" << i << ".png";
		if(!this->img_roads[i].loadFromFile(ss.str()))
		{
			std::cout << "ERROR: Texture not found" << std::endl;
			return false;
		}
		glGenTextures(1, &this->img_roads_handles[i]);
		glBindTexture(GL_TEXTURE_2D, this->img_roads_handles[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_LOD, 0.05);
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(
			GL_TEXTURE_2D, 0, GL_RGBA,
			this->img_roads[i].getSize().x, this->img_roads[i].getSize().y,
			0,
			GL_RGBA, GL_UNSIGNED_BYTE, this->img_roads[i].getPixelsPtr()
		);
	}

	this->img_tree_2.loadFromFile("res/prop/tree-1.png");
	this->img_tree.loadFromFile("res/prop/tree-2.png");
	/*glGenTextures(1, &this->img_1_handle);
	glBindTexture(GL_TEXTURE_2D, img_1_handle);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	glTexImage2D(
		GL_TEXTURE_2D, 0, GL_RGBA,
		img_1.GetWidth(), img_1.GetHeight(),
		0,
		GL_RGBA, GL_UNSIGNED_BYTE, img_1.GetPixelsPtr()
	);*/

	return true;
}


} /* namespace dfv */
