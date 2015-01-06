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

 * Lot.cpp
 *
 *  Created on: Jul 3, 2014
 *      Author: daniel
 */

#include "Lot.h"

namespace dfv
{

Lot::Lot():
		inhabitants(0), jobs(0)
{

}

Lot::Lot(const std::vector<sf::Vector2i> & tile_indices,
	     const std::vector<Quad> & tile_quads,
	     const sf::Vector3f & origin):
	    		 inhabitants(0), jobs(0)
{
	this->tileIndices = tile_indices;
	this->tileQuads = tile_quads;
	this->origin = origin;
}

Lot::~Lot()
{

}

void Lot::addStructure(Structure* lp_structure)
{
	this->lpStructures.push_back(lp_structure);
}

void Lot::clearStructures()
{
	for(Structure* lpStructure: this->lpStructures)
	{
		if(lpStructure != nullptr)
		{
			delete lpStructure;
		}
	}
	this->lpStructures.clear();
}

void Lot::drawStructureBoxes() const
{
	for(auto lp_structure: this->lpStructures)
	{
		lp_structure->drawBox();
	}
}

void Lot::drawStructureOutlines() const
{
	for(auto lp_structure: this->lpStructures)
	{
		lp_structure->drawOutline();
	}
}

bool Lot::hasStructure() const
{
	return !this->lpStructures.empty();
}

float Lot::getMinHeight() const
{
	std::vector<float> vertex_heights;
	for(Quad tile_quad: this->tileQuads)
	{
		vertex_heights.push_back(tile_quad.getMinHeight());
	}
	return *(std::min_element(vertex_heights.begin(), vertex_heights.end()));
}

float Lot::getMaxHeight() const
{
	std::vector<float> vertex_heights;
	for(Quad tile_quad: this->tileQuads)
	{
		vertex_heights.push_back(tile_quad.getMaxheight());
	}
	return *(std::max_element(vertex_heights.begin(), vertex_heights.end()));
}

sf::Vector3f Lot::getOrigin() const
{
	return this->origin;
}

sf::Vector2f Lot::getOrigin2d() const
{
	return sf::Vector2f(this->origin.x, this->origin.y);
}

sf::Vector2i Lot::getOriginTileIndices() const
{
	return this->tileIndices.at(0);
}

const vector<sf::Vector2i>& Lot::getTileIndices() const
{
	return this->tileIndices;
}

void Lot::setInhabitants(unsigned int value)
{
	this->inhabitants = value;
}

unsigned int Lot::getInhabitants() const
{
	return this->inhabitants;
}

void Lot::setJobs(unsigned int value)
{
	this->jobs = value;
}

unsigned int Lot::getJobs() const
{
	return this->jobs;
}

float Lot::getStructureHeight() const
{
	if(this->lpStructures.size() == 0)
	{
		return 0.f;
	}
	std::vector<float> heights;
	for(Structure* lp_structure: this->lpStructures)
	{
		heights.push_back(lp_structure->getModelHeight());
	}
	return *(std::max_element(heights.begin(), heights.end()));
}

unsigned int Lot::getStructureFloorCount() const
{
	if(this->lpStructures.size() == 0)
	{
		return 0;
	}
	std::vector<unsigned int> floors;
	for(Structure* lp_structure: this->lpStructures)
	{
		floors.push_back(lp_structure->getModelFloorCount());
	}
	return *(std::max_element(floors.begin(), floors.end()));
}

} /* namespace dfv */
