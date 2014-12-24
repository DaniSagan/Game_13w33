/*
 * HeightMap.cpp
 *
 *  Created on: Dec 24, 2014
 *      Author: daniel
 */

#include "HeightMap.h"

namespace dfv
{

HeightMap::HeightMap():
		minHeight(-1.f), maxHeight(20.f)
{
	/*this->m_data.resize(size);
	for(vector<float> v: this->m_data)
	{
		v.resize(size);
		for(float& x: v)
		{
			x = 0.f;
		}
	}*/
}

HeightMap::~HeightMap()
{
	// TODO Auto-generated destructor stub
}

float& HeightMap::at(size_t x, size_t y)
{
	return this->m_data.at(x).at(y);
}

void HeightMap::load(const string& filename)
{
	sf::Image img;
	img.loadFromFile(filename);
	size_t size = min(img.getSize().x, img.getSize().y);
	cout << "Loading heightmap file from " << filename << " of size " << size << endl;
	this->m_data.resize(size);
	for(size_t x = 0; x < size; x++)
	{
		this->m_data.at(x).resize(size);
		for(size_t y = 0; y < size; y++)
		{
			float color = static_cast<float>(img.getPixel(x, y).r);
			float height = max(-0.01f, this->minHeight + (this->maxHeight-this->minHeight)/255.f * color);
			this->m_data.at(x).at(y) = height;
		}
	}
	cout << "Finished loading heightmap" << endl;
}

size_t HeightMap::size() const
{
	return this->m_data.size();
}

} /* namespace dfv */
