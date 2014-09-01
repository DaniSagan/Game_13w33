/*
 *  Hyperopolis: Megacities building game.
    Copyright (C) 2014  Daniel Fernández Villanueva

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

 * Camera.cpp
 *
 *  Created on: Aug 11, 2013
 *      Author: daniel
 */

#include "Camera.h"

namespace dfv
{

Camera::Camera():
		mode(Free),
		curr_pitch(0.0),
		curr_roll(0.0)
{
	// TODO Auto-generated constructor stub

}

Camera::~Camera()
{
	// TODO Auto-generated destructor stub
}

sf::Vector3f Camera::getPosition() const
{
	return this->position;
}

void Camera::setPosition(const sf::Vector3f& position)
{
	this->position = position;
}

void Camera::move(const sf::Vector3f& v)
{
	this->position.x += v.x;
	this->position.y += v.y;
	this->position.z += v.z;
}

const sf::Vector3f& Camera::getRpy() const
{
	return this->rpy;
}

void Camera::setRpy(const sf::Vector3f& rpy)
{
	this->rpy = rpy;
}

void Camera::rotate(const sf::Vector3f& v)
{
	this->rpy.x += v.x;
	this->rpy.y += v.y;
	this->rpy.z += v.z;
}

unsigned int Camera::getQuadrant() const
{
	if(this->getRpy().z >= 315.f || this->getRpy().z < 45.f) return 1;
	if(this->getRpy().z >= 45.f && this->getRpy().z < 135.f) return 0;
	if(this->getRpy().z >= 135.f && this->getRpy().z < 225.f) return 3;
	if(this->getRpy().z >= 225.f && this->getRpy().z < 315.f) return 2;
	return 0;
}

sf::Vector2f Camera::getPosition2d() const
{
	return sf::Vector2f(this->position.x, this->position.y);
}

void Camera::setView(const sf::Window& window) const
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, window.getSize().x, window.getSize().y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(55.0f, (float)window.getSize().x / (float)window.getSize().y, 0.01f, 2000.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(this->getRpy().x, 1.f, 0.f, 0.f);
	glRotatef(this->getRpy().y, 0.f, 1.f, 0.f);
	glRotatef(this->getRpy().z, 0.f, 0.f, 1.f);
	glTranslatef(-this->getPosition().x, -this->getPosition().y, -this->getPosition().z);

}

/*dfv::IntRect Camera::GetRectFromView(const dfv::IntRect& map_rect) const
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
}*/

void Camera::handleInput(sf::Event& event)
{
	if(event.type == sf::Event::KeyPressed)
	{
		if(event.key.code == sf::Keyboard::N)
		{
			this->mode = Free;
		}
		else if(event.key.code == sf::Keyboard::M)
		{
			if(this->mode != Driving)
			{
				this->mode = Driving;
				this->car.init();
			}
		}
	}
}

void Camera::update(float dt, float map_height, sf::Vector3f& normal)
{
	this->map_normal = normal;
	//std::cout << "normal: " << normal.x << ", " << normal.y << ", " << normal.z << std::endl;
	sf::Vector3f vdirx(sin(this->rpy.z*M_PI/180.0), cos(this->rpy.z*M_PI/180.0), 0.0);
	sf::Vector3f vdiry(sin((this->rpy.z-90)*M_PI/180.0), cos((this->rpy.z-90)*M_PI/180.0), 0.0);
	//std::cout << "vdirx: " << vdirx.x << ", " << vdirx.y << ", " << vdirx.z << std::endl;
	//std::cout << "vdiry: " << vdiry.x << ", " << vdiry.y << ", " << vdiry.z << std::endl;

	float pitch = acos(Utils::dot(vdirx, normal)) * 180.0/M_PI - 90.0;
	float roll = acos(Utils::dot(vdiry, normal)) * 180.0/M_PI - 90.0;

	//std::cout << "pitch:" << pitch << std::endl;
	//std::cout << "roll:" << roll << std::endl;

	float height = this->getPosition().z - map_height;
	float base_height = 0.05f / cos(pitch*M_PI/180.f);
	/*if(height < 0.04f)
	{
		this->setPosition(sf::Vector3f(this->getPosition().x, this->getPosition().y, 0.04f + map_height));
	}*/

	if(height < base_height)
	{
		this->setPosition(sf::Vector3f(this->getPosition().x, this->getPosition().y, base_height + map_height));
	}
	//float vel = dt * 0.1f * (16*height + 16.0);
	float vel = 0.1 * (16.0*height + 16.0);
	float ang = this->getRpy().z * M_PI / 180.0;
	float angx = this->getRpy().x * M_PI / 180.0;

	if(this->mode == Free)
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			this->move(sf::Vector3f(-dt * vel * sin(ang) * sin(angx), -dt * vel * cos(ang) * sin(angx), -dt * vel * cos(angx)));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			this->move(sf::Vector3f(dt * vel * sin(ang) * sin(angx), dt * vel * cos(ang) * sin(angx), dt * vel * cos(angx)));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			this->move(sf::Vector3f(dt * vel * cos(ang), -dt * vel * sin(ang), 0.f));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			this->move(sf::Vector3f(-dt * vel * cos(ang), dt * vel * sin(ang), 0.f));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			this->move(sf::Vector3f(dt * vel * sin(ang), dt * vel * cos(ang), 0.0));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
		{
			this->move(sf::Vector3f(-dt * vel * sin(ang), -dt * vel * cos(ang), 0.0));
		}

		float rot = 20.0f * dt;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			this->rotate(sf::Vector3f(-rot/2.0, 0.f, 0.f));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			this->rotate(sf::Vector3f(rot/2.0, 0.f, 0.f));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			this->rotate(sf::Vector3f(0.f, 0.f, -rot));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			this->rotate(sf::Vector3f(0.f, 0.f, rot));
		}
		//std::cout << "height:" << height << std::endl;
		if(height < 0.04f)
		{
			this->setPosition(sf::Vector3f(this->getPosition().x, this->getPosition().y, 0.04f + map_height));
		}

	}
	else if(this->mode == Driving)
	{
		this->car.update(dt, this->curr_pitch);
		vel = 1.f/32.f*this->car.getSpeed();
		float rot = 0.0;
		if(vel > 0.0)
		{
			rot = this->car.getDeltaSteeringAngle(dt);
			float fc = this->car.getCentrifugalForce();
			float fc_max = this->car.getMaxCentrifugalForce();
			if(fc > fc_max)
			{
				rot = this->car.getMaxDeltaSteeringAngle(dt);
			}
			else if(fc < -fc_max)
			{
				rot = -this->car.getMaxDeltaSteeringAngle(dt);
			}
		}
		float rot_pitch = 0.0;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			rot_pitch -= 50.f;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			rot_pitch += 50.f;
		}
		this->curr_pitch += 2.0f*(pitch - this->curr_pitch)*dt;
		this->curr_roll += 2.0f*(roll - this->curr_roll)*dt;
		this->setRpy(sf::Vector3f(-105.0 - curr_pitch,  -curr_roll, this->getRpy().z));
		this->rotate(sf::Vector3f(0.f, 0.f, rot*180.0/M_PI));
		this->move(sf::Vector3f(dt * vel * sin(ang), dt * vel * cos(ang), 0.f));
		this->setPosition(sf::Vector3f(this->getPosition().x, this->getPosition().y, base_height + map_height));
	}

	// Normalize camera angles
	if(this->getRpy().z < 0.f)
	{
		this->rotate(sf::Vector3f(0.f, 0.f, 360.f));
	}
	if(this->getRpy().z >= 360.f)
	{
		this->rotate(sf::Vector3f(0.f, 0.f, -360.f));
	}
}

float Camera::getCarSpeed() const
{
	return this->car.getSpeed();
}

unsigned int Camera::getCarGear() const
{
	return this->car.getGear();
}

float Camera::getMotorRPM() const
{
	return this->car.getMotorW() * 60 / (2*M_PI);
}

float Camera::getCarTorque() const
{
	return this->car.getCurrTorque();
}

float Camera::getCarPower() const
{
	return this->car.getCurrTorque()*this->car.getMotorW();
}

Camera::Mode Camera::getMode() const
{
	return this->mode;
}

dfv::RealIntRect Camera::getRectFromView(const dfv::RealIntRect& map_rect) const
{
	dfv::RealIntRect view_rect = map_rect;

	// If looking down return the entire map


	if(this->getRpy().x > -20.f)
	{
		return map_rect;
	}

	// If not looking down, draw only the half of the map we're facing
	else
	{
		if(this->getQuadrant() == 0)
		{

			view_rect.trim(this->getPosition2d().x - 5, map_rect.xmax, map_rect.ymin, map_rect.ymax);
			//view_rect.Left = floor(this->GetPosition2d().x) - 5;
			//view_rect.Bottom = 0;
			//view_rect.Right = map_rect.Right;
			//view_rect.Top = map_rect.Top;
		}

		else if(this->getQuadrant() == 1)
		{
			view_rect.trim(map_rect.xmin, map_rect.xmax, this->getPosition2d().y - 5, map_rect.ymax);
			/*view_rect.Left = 0;
			view_rect.Bottom = floor(this->GetPosition2d().y) - 5;
			view_rect.Right = map_rect.Right;
			view_rect.Top = map_rect.Top;*/
		}

		else if(this->getQuadrant() == 2)
		{
			view_rect.trim(map_rect.xmin, this->getPosition2d().x + 5, map_rect.ymin, map_rect.ymax);
			/*view_rect.Left = 0;
			view_rect.Bottom = 0;
			view_rect.Right = floor(this->GetPosition2d().x) + 5;
			view_rect.Top = map_rect.Top;*/
		}

		else if(this->getQuadrant() == 3)
		{
			view_rect.trim(map_rect.xmin, map_rect.xmax, map_rect.ymin, this->getPosition2d().y + 5);
			/*view_rect.Left = 0;
			view_rect.Bottom = 0;
			view_rect.Right = map_rect.Right;
			view_rect.Top = floor(this->GetPosition2d().y) + 5;*/
		}
	}

	/*

	dfv::Utils::TrimRect(
			view_rect,
			map_rect.Left, map_rect.Right,
			map_rect.Top, map_rect.Bottom);*/
	//aastd::cout << "view_rect: " << view_rect.toString() << std::endl;
	return view_rect;
}

} /* namespace dfv */


