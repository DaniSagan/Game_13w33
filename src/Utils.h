/*
 * Utils.h
 *
 *  Created on: Aug 13, 2013
 *      Author: daniel
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <SFML/Graphics.hpp>

namespace dfv
{

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
	static void TrimRect(sf::IntRect& rect, int left, int right, int top, int bottom);
	static void TrimRect(sf::IntRect& rect, const sf::IntRect& limits);
	static sf::IntRect CreateRect(const sf::Vector2i& position, int radius);
	static sf::Vector2i ToVector2i(const sf::Vector2f& v);
};

} /* namespace dfv */
#endif /* UTILS_H_ */
