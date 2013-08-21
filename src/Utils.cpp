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

sf::Vector2f Utils::Diff(const sf::Vector2f& v1, const sf::Vector2f& v2)
{
	return sf::Vector2f(v1.x - v2.x, v1.y - v2.y);
}

void Utils::DrawRectangle(sf::Image& img, const sf::Vector2i& top_left,
		const sf::Vector2i& bottom_right, const sf::Color& color)
{
	unsigned int width = bottom_right.x - top_left.x + 1;
	unsigned int height = bottom_right.y - top_left.y + 1;
	//const sf::Uint8* lp_pixels = img.GetPixelsPtr();
	for(unsigned int i = 0; i < width; i++)
	{
		for(unsigned j = 0; j < height; j++)
		{
			img.SetPixel(top_left.y + j, top_left.x + i, color);
		}
	}
}

float Utils::Length(const sf::Vector3f v)
{
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

float Utils::Length(const sf::Vector2f v)
{
	return sqrt(v.x*v.x + v.y*v.y);
}

void Utils::TrimRect(sf::IntRect& rect, const sf::IntRect& limits)
{
	if(rect.Left < limits.Left) rect.Left = limits.Left;
	if(rect.Right > limits.Right) rect.Right = limits.Right;
	if(rect.Top > limits.Top) rect.Top = limits.Top;
	if(rect.Bottom < limits.Bottom) rect.Bottom = limits.Bottom;
}

void Utils::TrimRect(sf::IntRect& rect, int left, int right, int top,
		int bottom)
{
	if(rect.Left < left) rect.Left = left;
	if(rect.Right > right) rect.Right = right;
	if(rect.Top > top) rect.Top = top;
	if(rect.Bottom < bottom) rect.Bottom = bottom;
}

sf::IntRect Utils::CreateRect(const sf::Vector2i& position, int radius)
{
	sf::IntRect rect;
	rect.Left = position.x - radius;
	rect.Right = position.x + radius;
	rect.Bottom = position.y - radius;
	rect.Top = position.y + radius;

	return rect;
}

sf::Vector2i Utils::ToVector2i(const sf::Vector2f& v)
{
	return sf::Vector2i(floor(v.x), floor(v.y));
}

sf::Vector2f Utils::ToVector2f(const sf::Vector2i& v)
{
	return sf::Vector2f(v.x, v.y);
}

sf::Vector2f Utils::GetVector2d(const sf::Vector3f& v)
{
	return sf::Vector2f(v.x, v.y);
}

std::vector<std::string> Utils::StringTokenize(const std::string& str,
		const std::string& delimiters)
{
	std::vector<std::string> tokens;

	// skip delimiters at beginning.
	std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);

	// find first "non-delimiter".
	std::string::size_type pos = str.find_first_of(delimiters, lastPos);

	while (std::string::npos != pos || std::string::npos != lastPos)
	{
		// found a token, add it to the vector.
		tokens.push_back(str.substr(lastPos, pos - lastPos));

		// skip delimiters.  Note the "not_of"
		lastPos = str.find_first_not_of(delimiters, pos);

		// find next "non-delimiter"
		pos = str.find_first_of(delimiters, lastPos);
	}

	return tokens;
}

} /* namespace dfv */
