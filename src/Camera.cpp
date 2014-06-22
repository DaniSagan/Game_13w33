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

sf::Vector3f Camera::GetPosition() const
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

unsigned int Camera::GetQuadrant() const
{
	if(this->GetRpy().z >= 315.f || this->GetRpy().z < 45.f) return 1;
	if(this->GetRpy().z >= 45.f && this->GetRpy().z < 135.f) return 0;
	if(this->GetRpy().z >= 135.f && this->GetRpy().z < 225.f) return 3;
	if(this->GetRpy().z >= 225.f && this->GetRpy().z < 315.f) return 2;
	return 0;
}

sf::Vector2f Camera::GetPosition2d() const
{
	return sf::Vector2f(this->position.x, this->position.y);
}

void Camera::SetView(const sf::Window& window) const
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, window.getSize().x, window.getSize().y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(55.0f, (float)window.getSize().x / (float)window.getSize().y, 0.01f, 2000.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(this->GetRpy().x, 1.f, 0.f, 0.f);
	glRotatef(this->GetRpy().y, 0.f, 1.f, 0.f);
	glRotatef(this->GetRpy().z, 0.f, 0.f, 1.f);
	glTranslatef(-this->GetPosition().x, -this->GetPosition().y, -this->GetPosition().z);

}

dfv::IntRect Camera::GetRectFromView(const dfv::IntRect& map_rect) const
{
	dfv::IntRect view_rect(0, 0, 0, 0);

	// If looking down return the entire map


	if(this->GetRpy().x > -20.f)
	{
		view_rect = map_rect;
	}

	// If not looking down, draw only the half of the map we're facing
	else
	{
		if(this->GetQuadrant() == 0)
		{
			view_rect.Left = floor(this->GetPosition2d().x) - 5;
			view_rect.Bottom = 0;
			view_rect.Right = map_rect.Right;
			view_rect.Top = map_rect.Top;
		}

		else if(this->GetQuadrant() == 1)
		{
			view_rect.Left = 0;
			view_rect.Bottom = floor(this->GetPosition2d().y) - 5;
			view_rect.Right = map_rect.Right;
			view_rect.Top = map_rect.Top;
		}

		else if(this->GetQuadrant() == 2)
		{
			view_rect.Left = 0;
			view_rect.Bottom = 0;
			view_rect.Right = floor(this->GetPosition2d().x) + 5;
			view_rect.Top = map_rect.Top;
		}

		else if(this->GetQuadrant() == 3)
		{
			view_rect.Left = 0;
			view_rect.Bottom = 0;
			view_rect.Right = map_rect.Right;
			view_rect.Top = floor(this->GetPosition2d().y) + 5;
		}
	}

	dfv::Utils::TrimRect(
			view_rect,
			map_rect.Left, map_rect.Right,
			map_rect.Top, map_rect.Bottom);

	return view_rect;
}

} /* namespace dfv */
