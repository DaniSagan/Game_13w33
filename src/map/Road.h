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

 * Road.h
 *
 *  Created on: Aug 14, 2013
 *      Author: daniel
 */

#ifndef ROAD_H_
#define ROAD_H_

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "../Resources.h"
#include "../Camera.h"
#include "../Utils.h"

namespace dfv
{

class Road
{
public:
	Road();
	virtual ~Road();

	enum Type
	{
		straight,
		cross,
		tcross,
		curve,
		av_straight,
		av_cross,
		av_tcross,
		count
	};

	void create(const std::vector<sf::Vector3f>& vertices, Type type, unsigned int orientation);
	void draw(const dfv::Camera& camera, const dfv::Resources& resources) const;
	void setId(unsigned int id);
	void setOrientation(unsigned int orientation);
	unsigned int getOrientation() const;
	unsigned int getId() const;

private:
	//Type id;
	unsigned int id;
	unsigned int orientation;
	std::vector<sf::Vector3f> vertices;
	std::vector<sf::Vector3f> normals;
	std::vector<sf::Vector2f> tex_coords;

};

} /* namespace dfv */
#endif /* ROAD_H_ */
