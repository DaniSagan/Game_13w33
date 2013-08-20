/*
 * Camera.h
 *
 *  Created on: Aug 11, 2013
 *      Author: daniel
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include <SFML/Graphics.hpp>
#include "Utils.h"

namespace dfv
{

class Camera
{
public:
	Camera();
	virtual ~Camera();

	sf::Vector3f GetPosition() const;
	sf::Vector2f GetPosition2d() const;
	void SetPosition(const sf::Vector3f& position);
	void Move(const sf::Vector3f& v);
	const sf::Vector3f& GetRpy() const;
	void SetRpy(const sf::Vector3f& rpy);
	void Rotate(const sf::Vector3f& v);
	unsigned int GetQuadrant() const;
	void SetView(const sf::RenderWindow& window) const;
	sf::IntRect GetRectFromView(const sf::IntRect& map_rect) const;

private:
	sf::Vector3f position;
	sf::Vector3f rpy;
};

} /* namespace dfv */
#endif /* CAMERA_H_ */
