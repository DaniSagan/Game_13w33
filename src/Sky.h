/*
 * Sky.h
 *
 *  Created on: Aug 19, 2013
 *      Author: daniel
 */

#ifndef SKY_H_
#define SKY_H_

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <vector>

namespace dfv
{

class Sky
{
public:
	Sky();
	virtual ~Sky();

	void Create(float size, std::string filename);
	void Draw() const;

private:
	float size;
	std::vector<sf::Vector3f> vertices;
	//std::vector<sf::Vector3f> normals;
	std::vector<sf::Image> images;
	std::vector<GLuint> image_handles;
	sf::Image sky_img;
};

} /* namespace dfv */
#endif /* SKY_H_ */
