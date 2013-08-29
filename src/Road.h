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

	void Create(const std::vector<sf::Vector3f>& vertices, Type type, unsigned int orientation);
	void Draw(const dfv::Camera& camera, const dfv::Resources& resources) const;
	void SetId(unsigned int id);
	void SetOrientation(unsigned int orientation);
	unsigned int GetOrientation() const;
	unsigned int GetId() const;

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
