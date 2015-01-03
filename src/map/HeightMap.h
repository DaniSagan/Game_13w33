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

 * HeightMap.h
 *
 *  Created on: Dec 24, 2014
 *      Author: daniel
 */

#ifndef HEIGHTMAP_H_
#define HEIGHTMAP_H_

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

namespace dfv
{

class HeightMap
{
public:
	HeightMap();
	virtual ~HeightMap();

	float& at(size_t x, size_t y);
	void load(const string& filename);
	void smooth();

	float minHeight;
	float maxHeight;
	size_t size() const;

protected:
	vector<vector<float>> m_data;
};

} /* namespace dfv */

#endif /* HEIGHTMAP_H_ */
