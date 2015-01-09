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

 * Utils.h
 *
 *  Created on: Aug 13, 2013
 *      Author: daniel
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <stdexcept>
#include <cassert>
#include <iomanip>
#include <map>
#include <fstream>
#include <random>

using namespace std;

namespace dfv
{

////////////////////////////////////////////////////////////////////////////////////
/// \brief Rectangle defined by its left, right, top and bottom coordinates. (DEPRECATED)
///
////////////////////////////////////////////////////////////////////////////////////
struct IntRect
{
	IntRect();
	IntRect(int left, int top, int right, int bottom);
	int Left;
	int Right;
	int Top;
	int Bottom;
};

////////////////////////////////////////////////////////////////////////////////////
/// \brief Rectangle defined by its min and max x and y coordinates.
///
////////////////////////////////////////////////////////////////////////////////////
struct RealRect
{
	RealRect();
	RealRect(float xmin_, float xmax_, float ymin_, float ymax_);
	float xmin, xmax, ymin, ymax;
	bool contains(sf::Vector2f pos);
	void trim(float xmin, float xmax, float ymin, float ymax);
	void trim(RealRect rect);
	void setFromCenterRadius(sf::Vector2f center_pos, float radius);
	std::string toString() const;
};

////////////////////////////////////////////////////////////////////////////////////
/// \brief Rectangle defined by its min and max x and y coordinates.
///
////////////////////////////////////////////////////////////////////////////////////
struct RealIntRect
{
	RealIntRect();
	RealIntRect(int xmin_, int xmax_, int ymin_, int ymax_);
	int xmin, xmax, ymin, ymax;
	bool contains(sf::Vector2i pos);
	bool trim(int xmin, int xmax, int ymin, int ymax);
	bool trim(RealIntRect rect);
	void setFromCenterRadius(sf::Vector2i center_pos, int radius);
	std::string toString() const;
};

////////////////////////////////////////////////////////////////////////////////////
/// \brief Rectangle defined by its left, top, right and bottom coordinates.
///
////////////////////////////////////////////////////////////////////////////////////
struct GuiRect
{
	GuiRect();
	GuiRect(float left_, float top_, float right_, float bottom_);
	float left, top, right, bottom;
	bool contains(sf::Vector2f pos);
};

////////////////////////////////////////////////////////////////////////////////////
/// \brief Class for loading and storing an image for using with OpenGL
///
////////////////////////////////////////////////////////////////////////////////////
class OpenGLImage
{
public:
	OpenGLImage();
	void loadFromFile(std::string filename);
	GLuint getHandle() const;
	sf::Vector2f getTexCoords(const unsigned int index) const;
protected:
	sf::Image image;
	GLuint handle;
	std::vector<sf::Vector2f> tex_coords;
};

////////////////////////////////////////////////////////////////////////////////////
/// \brief Class for creating an OpenGL quad which calculates its normal vectors.
///
////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////
/// \brief Storage class for utility functions.
///
////////////////////////////////////////////////////////////////////////////////////
class Utils
{
public:
	Utils();
	virtual ~Utils();

	static float dot(const sf::Vector3f& v1, const sf::Vector3f& v2);
	static sf::Vector3f cross(const sf::Vector3f& v1, const sf::Vector3f& v2);
	static sf::Vector3f diff(const sf::Vector3f& v1, const sf::Vector3f& v2);
	static sf::Vector2f diff(const sf::Vector2f& v1, const sf::Vector2f& v2);
	static void drawRectangle(
			sf::Image& img,
			const sf::Vector2i& top_left,
			const sf::Vector2i& bottom_right,
			const sf::Color& color);
	static float length(const sf::Vector3f v);
	static float length(const sf::Vector2f v);
	static void trimRect(IntRect& rect, int left, int right, int top, int bottom);
	static void trimRect(IntRect& rect, const dfv::IntRect& limits);
	static IntRect createRect(const sf::Vector2i& position, int radius);
	static sf::Vector2i toVector2i(const sf::Vector2f& v);
	static sf::Vector2f toVector2f(const sf::Vector2i& v);
	static sf::Vector2f getVector2d(const sf::Vector3f& v);
	static std::vector<std::string> stringTokenize(
			const std::string& str,
			const std::string& delimiters);
	static std::string toString(const IntRect& rect);
	static bool rectContains(const IntRect& rect, const sf::Vector2i& pos);
	static float interpolate2d(float x1, float x2, float y1, float y2,
			                   float z11, float z12, float z21, float z22,
			                   float x, float y);
	static float pitch(sf::Vector3f v);
	static float floatRandom(const float min, const float max);
	static float rFunction(const float x, const float n);
	static float angle(const sf::Vector3f& v1, const sf::Vector3f& v2);
	static string exec(char* cmd);
	static GLuint loadGLTexture(const string& filename);

	static bool test();
};

class SimpleParser
{
public:
	SimpleParser();
	void parse(const string& filename);
	string get(const string& field);
protected:
	map<string, string> m_data;
};

const sf::Vector3f operator^(const sf::Vector3f& v1, const sf::Vector3f& v2);
const float operator*(const sf::Vector3f& v1, const sf::Vector3f& v2);

string strRepeat(size_t count, const string& str);

template<typename T>
T getxmax(const vector<sf::Vector2<T>>& v)
{
	T xmax = v.at(0).x;
	for(sf::Vector2<T> vk: v)
	{
		if(vk.x > xmax) xmax = vk.x;
	}
	return xmax;
}

template<typename T>
T getxmin(const vector<sf::Vector2<T>>& v)
{
	T xmin = v.at(0).x;
	for(sf::Vector2<T> vk: v)
	{
		if(vk.x < xmin) xmin = vk.x;
	}
	return xmin;
}

template<typename T>
T getymax(const vector<sf::Vector2<T>>& v)
{
	T ymax = v.at(0).y;
	for(sf::Vector2<T> vk: v)
	{
		if(vk.y > ymax) ymax = vk.y;
	}
	return ymax;
}

template<typename T>
T getymin(const vector<sf::Vector2<T>>& v)
{
	T ymin = v.at(0).y;
	for(sf::Vector2<T> vk: v)
	{
		if(vk.y < ymin) ymin = vk.y;
	}
	return ymin;
}

} /* namespace dfv */
#endif /* UTILS_H_ */
