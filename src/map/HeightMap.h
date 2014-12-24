/*
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

	float minHeight;
	float maxHeight;
	size_t size() const;

protected:
	vector<vector<float>> m_data;
};

} /* namespace dfv */

#endif /* HEIGHTMAP_H_ */
