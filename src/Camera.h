/*
 * Camera.h
 *
 *  Created on: Aug 11, 2013
 *      Author: daniel
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include <SFML/Graphics.hpp>

namespace dfv
{

class Camera
{
public:
	Camera();
	virtual ~Camera();

	const sf::Vector3f& GetPosition() const;
	void SetPosition(const sf::Vector3f& position);
	void Move(const sf::Vector3f& v);
	const sf::Vector3f& GetRpy() const;
	void SetRpy(const sf::Vector3f& rpy);
	void Rotate(const sf::Vector3f& v);

private:
	sf::Vector3f position;
	sf::Vector3f rpy;
};

} /* namespace dfv */
#endif /* CAMERA_H_ */
