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

 * Minimap.h
 *
 *  Created on: Aug 15, 2013
 *      Author: daniel
 */

#ifndef MINIMAP_H_
#define MINIMAP_H_

#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
#include "../Camera.h"
#include "../map/Map.h"

namespace dfv
{

class Minimap
{
public:
	Minimap();
	virtual ~Minimap();

	void create(const unsigned int size);
	//void GenerateFromMap(Map* lp_map, const Camera& camera);
	void generateFromMap(const Map& map, const sf::Vector2f position, unsigned int range);
	sf::Vector2i realPosFromMapPos(sf::Vector2i map_pos, int range);
	sf::Vector2f realPosFromMinimapPos(const sf::Vector2i& minimapPos, const sf::Vector2f& mapPos) const;
	void draw(sf::RenderWindow& window, const Camera& camera) const;
	std::string handleInput(const Camera& camera, const sf::Event& event, const sf::Vector2i& mouse_pos);
	unsigned int getSize() const;

	struct Colors
	{
		sf::Color none;
		sf::Color road;
		sf::Color grass;
		sf::Color structure;
		sf::Color water;
		sf::Color sand;
	} colors;

private:
	sf::Image img;
	unsigned int size;
	unsigned int range;
	sf::Uint8* lp_pixels;
	sf::Texture texture;
	//dfv::Map* lp_map;
};

} /* namespace dfv */
#endif /* MINIMAP_H_ */
