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
};

} /* namespace dfv */
#endif /* UTILS_H_ */
