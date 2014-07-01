/*
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

void Camera::update(float dt, float map_height, sf::Vector3f& normal)
{
	this->map_normal = normal;
	//std::cout << "normal: " << normal.x << ", " << normal.y << ", " << normal.z << std::endl;
	sf::Vector3f vdirx(sin(this->rpy.z*3.1416/180.0), cos(this->rpy.z*3.1416/180.0), 0.0);
	sf::Vector3f vdiry(sin((this->rpy.z-90)*3.141592/180.0), cos((this->rpy.z-90)*3.141592/180.0), 0.0);
	//std::cout << "vdirx: " << vdirx.x << ", " << vdirx.y << ", " << vdirx.z << std::endl;
	//std::cout << "vdiry: " << vdiry.x << ", " << vdiry.y << ", " << vdiry.z << std::endl;

	float pitch = acos(Utils::Dot(vdirx, normal)) * 180.0/3.141592 - 90.0;
	float roll = acos(Utils::Dot(vdiry, normal)) * 180.0/3.141592 - 90.0;

	//std::cout << "pitch:" << pitch << std::endl;
	//std::cout << "roll:" << roll << std::endl;

	float height = this->GetPosition().z - map_height;
	if(height < 0.04f)
	{
		this->SetPosition(sf::Vector3f(this->GetPosition().x, this->GetPosition().y, 0.04f + map_height));
	}
	//float vel = dt * 0.1f * (16*height + 16.0);
	float vel = 0.1 * (16.0*height + 16.0);
	float ang = this->GetRpy().z * 3.1416 / 180.0;
	float angx = this->GetRpy().x * 3.1416 / 180.0;

	if(this->mode == Free)
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			this->Move(sf::Vector3f(dt * vel * sin(ang), dt * vel * cos(ang), 0.0));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			this->Move(sf::Vector3f(-dt * vel * sin(ang), -dt * vel * cos(ang), 0.0));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			this->Move(sf::Vector3f(dt * vel * cos(ang), -dt * vel * sin(ang), 0.f));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			this->Move(sf::Vector3f(-dt * vel * cos(ang), dt * vel * sin(ang), 0.f));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			this->Move(sf::Vector3f(dt * vel * sin(ang), dt * vel * cos(ang), 0.0));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
		{
			this->Move(sf::Vector3f(-dt * vel * sin(ang), -dt * vel * cos(ang), 0.0));
		}

		float rot = 20.0f * dt;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			this->Rotate(sf::Vector3f(-rot/2.0, 0.f, 0.f));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			this->Rotate(sf::Vector3f(rot/2.0, 0.f, 0.f));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			this->Rotate(sf::Vector3f(0.f, 0.f, -rot));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			this->Rotate(sf::Vector3f(0.f, 0.f, rot));
		}
		//std::cout << "height:" << height << std::endl;
		if(height < 0.04f)
		{
			this->SetPosition(sf::Vector3f(this->GetPosition().x, this->GetPosition().y, 0.04f + map_height));
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
		this->SetRpy(sf::Vector3f(-105.0 - curr_pitch,  -curr_roll, this->GetRpy().z));
		this->Rotate(sf::Vector3f(0.f, 0.f, rot*180.0/3.1416));
		this->Move(sf::Vector3f(dt * vel * sin(ang), dt * vel * cos(ang), 0.f));
		this->SetPosition(sf::Vector3f(this->GetPosition().x, this->GetPosition().y, 0.04f + map_height));
	}

	// Normalize camera angles
	if(this->GetRpy().z < 0.f)
	{
		this->Rotate(sf::Vector3f(0.f, 0.f, 360.f));
	}
	if(this->GetRpy().z >= 360.f)
	{
		this->Rotate(sf::Vector3f(0.f, 0.f, -360.f));
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
	return this->car.getMotorW() * 60 / (2*3.1416);
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


	if(this->GetRpy().x > -20.f)
	{
		return map_rect;
	}

	// If not looking down, draw only the half of the map we're facing
	else
	{
		if(this->GetQuadrant() == 0)
		{

			view_rect.trim(this->GetPosition2d().x - 5, map_rect.xmax, map_rect.ymin, map_rect.ymax);
			//view_rect.Left = floor(this->GetPosition2d().x) - 5;
			//view_rect.Bottom = 0;
			//view_rect.Right = map_rect.Right;
			//view_rect.Top = map_rect.Top;
		}

		else if(this->GetQuadrant() == 1)
		{
			view_rect.trim(map_rect.xmin, map_rect.xmax, this->GetPosition2d().y - 5, map_rect.ymax);
			/*view_rect.Left = 0;
			view_rect.Bottom = floor(this->GetPosition2d().y) - 5;
			view_rect.Right = map_rect.Right;
			view_rect.Top = map_rect.Top;*/
		}

		else if(this->GetQuadrant() == 2)
		{
			view_rect.trim(map_rect.xmin, this->GetPosition2d().x + 5, map_rect.ymin, map_rect.ymax);
			/*view_rect.Left = 0;
			view_rect.Bottom = 0;
			view_rect.Right = floor(this->GetPosition2d().x) + 5;
			view_rect.Top = map_rect.Top;*/
		}

		else if(this->GetQuadrant() == 3)
		{
			view_rect.trim(map_rect.xmin, map_rect.xmax, map_rect.ymin, this->GetPosition2d().y + 5);
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


