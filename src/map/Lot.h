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

 * Lot.h
 *
 *  Created on: Jul 3, 2014
 *      Author: daniel
 */

#ifndef LOT_H_
#define LOT_H_

#include <SFML/Graphics.hpp>
#include "Structure.h"
//#include "Tile.h"

namespace dfv
{

class Tile;

class Lot
{
public:
	Lot();
	Lot(const std::vector<sf::Vector2i> & tile_indices,
	    const std::vector<Quad> & tile_quads,
	    const sf::Vector3f & origin);
	virtual ~Lot();

	void addStructure(Structure* lp_structure);
	void clearStructures();

	void drawStructureBoxes() const;
	void drawStructureOutlines() const;
	bool hasStructure() const;

	float getMinHeight() const;
	float getMaxHeight() const;
	sf::Vector3f getOrigin() const;
	sf::Vector2f getOrigin2d() const;
	sf::Vector2i getOriginTileIndices() const;
	const vector<sf::Vector2i>& getTileIndices() const;

	void setInhabitants(unsigned int value);
	unsigned int getInhabitants() const;

	void setJobs(unsigned int value);
	unsigned int getJobs() const;

	float getStructureHeight() const;
	unsigned int getStructureFloorCount() const;

	friend string osString(size_t level, const string& name, const Lot& lot);
	friend string osString(size_t level, const string& name, const Lot* lpLot);
	friend string osString(size_t level, const string& name, const vector<Lot*>& lpLots);
	friend bool isRead(Serializer& ser, Lot& lot);

private:
	sf::Vector3f origin;
	std::vector<Structure*> lpStructures;
	std::vector<sf::Vector2i> tileIndices;
	std::vector<Quad> tileQuads;
	unsigned int inhabitants;
	unsigned int jobs;
};

} /* namespace dfv */
#endif /* LOT_H_ */
