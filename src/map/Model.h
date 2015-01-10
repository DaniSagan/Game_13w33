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

 * Model.h
 *
 *
 *  Created on: Aug 19, 2014
 *      Author: daniel
 */

#ifndef MODEL_H_
#define MODEL_H_

#include <vector>
#include <SFML/Graphics.hpp>
#include <cassert>
#include "../Utils.h"
#include "Quad.h"
#include "../Serializer.h"

namespace dfv {

class Model {
public:
	Model();
	virtual ~Model();

	void drawBox() const;
	void drawOutlines() const;
	void create(const Quad & tile_quad,
			    const Quad & base_quad,
			    unsigned int floor_count);

	void create(const float min_terrain_height,
				const float max_terrain_height,
				const sf::Vector2f & position,
				const Quad & base_quad,
				unsigned int floor_count);

	unsigned int getFloorCount() const;
	float getHeight() const;

	friend string osString(size_t level, const string& name, const Model& model);
	friend bool isRead(Serializer& ser, Model& model);

private:
	Quad base_quad;
	std::vector<Quad> facade_quads;
	std::vector<Quad> outline_quads;
	unsigned int floor_count;
	float height;
	float minTerrainHeight;
	float maxTerrainHeight;
	sf::Vector2f position;
};

} /* namespace dfv */

#endif /* MODEL_H_ */
