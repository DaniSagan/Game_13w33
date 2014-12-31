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

 * Car.cpp
 *
 *  Created on: Jun 26, 2014
 *      Author: daniel
 */

#include "Car.h"

namespace dfv
{

Car::Car():
		k(-141.0/(186327.1)),
		//k(-1200.0/(186327.1)),
		w0(-500.0*2.0*3.1416/60.0), w1(9100.0*2.0*3.1416/60.0),
		curr_gear(0), yaw(0), wheel_radius(0.381), speed(0),
		mass(1200),
		//mass(1800),
		state(None), steering_angle(0.0), steering_time(0.0),
		friction_coeff(1.f), wheel_base(2.54f)
{
	float diff_ratio = 4.17;
	this->gear_ratios.resize(5);
	this->gear_ratios.at(0) = diff_ratio * 3.06;
	this->gear_ratios.at(1) = diff_ratio * 1.83;
	this->gear_ratios.at(2) = diff_ratio * 1.29;
	this->gear_ratios.at(3) = diff_ratio * 0.98;
	this->gear_ratios.at(4) = diff_ratio * 0.76;
	/*float diff_ratio = 3.64;
	this->gear_ratios.resize(7);
	this->gear_ratios[0] = diff_ratio * 3.18;
	this->gear_ratios[1] = diff_ratio * 2.26;
	this->gear_ratios[2] = diff_ratio * 1.68;
	this->gear_ratios[3] = diff_ratio * 1.29;
	this->gear_ratios[4] = diff_ratio * 1.06;
	this->gear_ratios[5] = diff_ratio * 0.88;
	this->gear_ratios[6] = diff_ratio * 0.80;*/
}

Car::~Car()
{
	// TODO Auto-generated destructor stub
}

void Car::init()
{
	this->speed = 0.0;
	this->curr_gear = 0;
}

void Car::setTorqueParameters(float k, float w0, float w1)
{
	this->k = k;
	this->w0 = w0;
	this->w1 = w1;
}

float Car::getCurrTorque() const
{
	if(this->state == Accelerating)
	{
		float torque = this->k*(this->getMotorW() - this->w0) * (this->getMotorW() - this->w1);
		return torque;
	}
	else
	{
		return 0.0;
	}
}

float Car::getMaxTorque() const
{
	float w_tmax = 0.5*(this->w0 + this->w1);
	return this->k * (w_tmax - w0) * (w_tmax - w1);
}

void Car::setGearRatios(std::vector<float>& gear_ratios)
{
	this->gear_ratios.resize(gear_ratios.size());
	for(std::size_t i = 0; i < gear_ratios.size(); i++)
	{
		this->gear_ratios.at(i) = gear_ratios.at(i);
	}
}

void Car::setWheelRadius(float radius)
{
	this->wheel_radius = radius;
}

float Car::getMaxPower() const
{
	float w_pmax = 2.0/3.0*(this->w0 + this->w1);
	return w_pmax * this->k * (w_pmax - w0) * (w_pmax - w1);
}

bool Car::gearUp()
{
	if(this->curr_gear < this->gear_ratios.size() - 1u)
	{
		this->curr_gear++;
		return true;
	}
	else
	{
		return false;
	}
}

float Car::getMotorW() const
{
	float wmin = 980*2*3.1416/60;
	float w = (this->speed/this->wheel_radius)*this->gear_ratios.at(this->curr_gear);
	if(w < wmin)
	{
		return wmin;
	}
	else
	{
		return w;
	}
}

bool Car::gearDown()
{
	if(this->curr_gear > 0)
	{
		this->curr_gear--;
		return true;
	}
	else
	{
		return false;
	}
}

void Car::update(float dt, float pitch)
{
	this->state = None;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->state = Accelerating;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->state = Braking;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->steering_time += dt;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		float k = this->steering_angle > 0.01f? 60.f : (50.f*this->steering_time > 20.f? 20.f:50.f*this->steering_time);
		this->steering_angle -= k*dt*(1.0/(1.0+0.1f*this->speed));
		if(this->steering_angle < -40.f)
		{
			this->steering_angle = -40.f;
		}
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		float k = this->steering_angle < -0.01f? 60.f : (50.f*this->steering_time > 20.f? 20.f:50.f*this->steering_time);
		this->steering_angle += k*dt*(1.0/(1.0+0.1f*this->speed));
		if(this->steering_angle > 40.f)
		{
			this->steering_angle = 40.f;
		}
	}
	if(!sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->steering_time = 0.0f;
		this->steering_angle -= 5.0f*this->steering_angle*dt;
	}
	if(this->getMotorW() > 5000.0*2.0*3.1416/60.0)
	{
		this->gearUp();
	}
	if(this->curr_gear != 0 && this->getMotorW() < 3000.0*2.0*3.1416/60.0)
	{
		this->gearDown();
	}
	this->speed += dt * (this->getForce() - this->getDrag() - this->getGravityForce(pitch)) / (this->mass);
	if(this->speed < 0.0)
	{
		this->speed = 0.0;
	}
}

void Car::setState(State state)
{
	this->state = state;
}

float Car::getDrag() const
{
	const float Ad = 0.7;
	const float d = 1.2;
	return 0.5 * d * Ad * this->speed*this->speed;
}

float Car::getForce() const
{
	if(this->state == None)
	{
		return 0.0;
	}
	else if(this->state == Accelerating)
	{
		return (this->getCurrTorque()*this->gear_ratios.at(this->curr_gear)) / this->wheel_radius;
	}
	else if(this->state == Braking)
	{
		return -15000.0;
	}
	else
	{
		return 0.0;
	}
}

float Car::getSpeed() const
{
	return this->speed;
}

float Car::getSteeringAngle() const
{
	return this->steering_angle;
}

unsigned int Car::getGear() const
{
	return this->curr_gear;
}

float Car::getGravityForce(float pitch) const
{
	return this->mass*9.81*sin(pitch*3.141592/180.0);
}

float Car::getSteeringRadius() const
{
	return this->wheel_base/tan(this->steering_angle);
}

float Car::getDeltaSteeringAngle(float dt) const
{
	return this->speed*dt*tan(this->steering_angle*3.141592/180.0)/this->wheel_base;
}

float Car::getCentrifugalForce() const
{
	return this->mass*this->speed*this->speed*tan(this->steering_angle*3.1416/180.0)/this->wheel_base;
}

float Car::getMaxCentrifugalForce() const
{
	return this->mass*this->friction_coeff*9.81;
}

float Car::getMaxDeltaSteeringAngle(float dt) const
{
	return dt*this->friction_coeff*9.81/this->speed;
}

float Car::getMass() const
{
	return this->mass;
}

} /* namespace dfv */


