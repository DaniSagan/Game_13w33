/*
 * Square.h
 *
 *  Created on: Aug 19, 2013
 *      Author: daniel
 */

#ifndef SQUARE_H_
#define SQUARE_H_

#include <SFML/Graphics.hpp>
#include <vector>

namespace dfv
{

class Square
{
public:
	Square();
	virtual ~Square();

	void create();

private:
	std::vector<sf::Vector3f> vertices;
	std::vector<sf::Vector3f> normals;
};

} /* namespace dfv */
#endif /* SQUARE_H_ */
