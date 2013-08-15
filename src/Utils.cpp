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
