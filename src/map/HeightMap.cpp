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
		minHeight(-4.f), maxHeight(30.f)
{
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
			float color = static_cast<float>(img.getPixel(x, img.getSize().y - y - 1).r);
			float height = max(-0.01f, this->minHeight + (this->maxHeight-this->minHeight)/255.f * color);
			this->m_data.at(x).at(y) = height;
		}
	}
	cout << "Finished loading heightmap" << endl;
}

void HeightMap::smooth()
{
	vector<vector<float>> newData = this->m_data;
	for(size_t x = 1; x < newData.size()-1; x++)
	{
		for(size_t y = 1; y < newData.size()-1; y++)
		{
			newData.at(x).at(y) = (this->m_data.at(x-1).at(y) +
								   this->m_data.at(x-1).at(y-1) +
								   this->m_data.at(x).at(y-1) +
								   this->m_data.at(x+1).at(y-1) +
								   this->m_data.at(x+1).at(y) +
								   this->m_data.at(x+1).at(y+1) +
								   this->m_data.at(x).at(y+1) +
								   this->m_data.at(x-1).at(y+1) +
								   2.f*this->m_data.at(x).at(y))/10.f;
		}
	}
	this->m_data = newData;
}

size_t HeightMap::size() const
{
	return this->m_data.size();
}

} /* namespace dfv */
