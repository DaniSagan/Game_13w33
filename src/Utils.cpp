/*
 * Utils.cpp
 *
 *  Created on: Aug 13, 2013
 *      Author: daniel
 */

#include "Utils.h"

namespace dfv
{

Utils::Utils()
{
	// TODO Auto-generated constructor stub

}

Utils::~Utils()
{
	// TODO Auto-generated destructor stub
}

sf::Vector3f Utils::Cross(const sf::Vector3f& v1, const sf::Vector3f& v2)
{
	return sf::Vector3f(v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x);
}

sf::Vector3f Utils::Diff(const sf::Vector3f& v1, const sf::Vector3f& v2)
{
	return sf::Vector3f(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

} /* namespace dfv */

void dfv::Utils::DrawRectangle(sf::Image& img, const sf::Vector2i& top_left,
		const sf::Vector2i& bottom_right, const sf::Color& color)
{
	unsigned int width = bottom_right.x - top_left.x + 1;
	unsigned int height = bottom_right.y - top_left.y + 1;
	const sf::Uint8* lp_pixels = img.GetPixelsPtr();
	for(unsigned int i = 0; i < width; i++)
	{
		for(unsigned j = 0; j < height; j++)
		{
			img.SetPixel(top_left.y + j, top_left.x + i, color);
		}
	}
}
