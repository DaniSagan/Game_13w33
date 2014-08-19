/*
 * Road.h
 *
 *  Created on: Aug 14, 2013
 *      Author: daniel
 */

#ifndef ROAD_H_
#define ROAD_H_

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Resources.h"
#include "Camera.h"
#include "Utils.h"

namespace dfv
{

class Road
{
public:
	Road();
	virtual ~Road();

	enum Type
	{
		straight,
		cross,
		tcross,
		curve,
		av_straight,
		av_cross,
		av_tcross,
		count
	};

	void create(const std::vector<sf::Vector3f>& vertices, Type type, unsigned int orientation);
	void draw(const dfv::Camera& camera, const dfv::Resources& resources) const;
	void setId(unsigned int id);
	void setOrientation(unsigned int orientation);
	unsigned int getOrientation() const;
	unsigned int getId() const;

private:
	//Type id;
	unsigned int id;
	unsigned int orientation;
	std::vector<sf::Vector3f> vertices;
	std::vector<sf::Vector3f> normals;
	std::vector<sf::Vector2f> tex_coords;

};

} /* namespace dfv */
#endif /* ROAD_H_ */
