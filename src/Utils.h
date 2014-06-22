/*
 * Utils.h
 *
 *  Created on: Aug 13, 2013
 *      Author: daniel
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
#include <sstream>

namespace dfv
{

struct IntRect
{
	IntRect();
	IntRect(int left, int top, int right, int bottom);
	int Left;
	int Right;
	int Top;
	int Bottom;
};

class Utils
{
public:
	Utils();
	virtual ~Utils();

	static sf::Vector3f Cross(const sf::Vector3f& v1, const sf::Vector3f& v2);
	static sf::Vector3f Diff(const sf::Vector3f& v1, const sf::Vector3f& v2);
	static sf::Vector2f Diff(const sf::Vector2f& v1, const sf::Vector2f& v2);
	static void DrawRectangle(
			sf::Image& img,
			const sf::Vector2i& top_left,
			const sf::Vector2i& bottom_right,
			const sf::Color& color);
	static float Length(const sf::Vector3f v);
	static float Length(const sf::Vector2f v);
	static void TrimRect(IntRect& rect, int left, int right, int top, int bottom);
	static void TrimRect(IntRect& rect, const dfv::IntRect& limits);
	static IntRect CreateRect(const sf::Vector2i& position, int radius);
	static sf::Vector2i ToVector2i(const sf::Vector2f& v);
	static sf::Vector2f ToVector2f(const sf::Vector2i& v);
	static sf::Vector2f GetVector2d(const sf::Vector3f& v);
	static std::vector<std::string> StringTokenize(
			const std::string& str,
			const std::string& delimiters);
	static std::string ToString(const IntRect& rect);
	static bool RectContains(const IntRect& rect, const sf::Vector2i& pos);
};

} /* namespace dfv */
#endif /* UTILS_H_ */
