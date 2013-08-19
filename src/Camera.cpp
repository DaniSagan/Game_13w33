/*
 * Camera.cpp
 *
 *  Created on: Aug 11, 2013
 *      Author: daniel
 */

#include "Camera.h"

namespace dfv
{

Camera::Camera()
{
	// TODO Auto-generated constructor stub

}

Camera::~Camera()
{
	// TODO Auto-generated destructor stub
}

const sf::Vector3f& Camera::GetPosition() const
{
	return this->position;
}

void Camera::SetPosition(const sf::Vector3f& position)
{
	this->position = position;
}

void Camera::Move(const sf::Vector3f& v)
{
	this->position.x += v.x;
	this->position.y += v.y;
	this->position.z += v.z;
}

const sf::Vector3f& Camera::GetRpy() const
{
	return this->rpy;
}

void Camera::SetRpy(const sf::Vector3f& rpy)
{
	this->rpy = rpy;
}

void Camera::Rotate(const sf::Vector3f& v)
{
	this->rpy.x += v.x;
	this->rpy.y += v.y;
	this->rpy.z += v.z;
}

unsigned int Camera::GetQuadrant()
{
	if(this->GetRpy().z >= 315.f || this->GetRpy().z < 45.f) return 1;
	if(this->GetRpy().z >= 45.f && this->GetRpy().z < 135.f) return 0;
	if(this->GetRpy().z >= 135.f && this->GetRpy().z < 225.f) return 3;
	if(this->GetRpy().z >= 225.f && this->GetRpy().z < 315.f) return 2;
	return 0;
}

} /* namespace dfv */
