/*
 * Resources.h
 *
 *  Created on: Aug 12, 2013
 *      Author: daniel
 */

#ifndef RESOURCES_H_
#define RESOURCES_H_

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <sstream>

namespace dfv
{

class Resources
{
public:
	Resources();
	virtual ~Resources();

	bool Load();

	std::vector<sf::Image> img_roads;
	std::vector<GLuint> img_roads_handles;
	GLuint img_1_handle;
};

} /* namespace dfv */
#endif /* RESOURCES_H_ */
