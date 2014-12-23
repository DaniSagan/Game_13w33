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

 * Camera.h
 *
 *  Created on: Aug 11, 2013
 *      Author: daniel
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <cmath>
#include "Utils.h"
#include "map/Car.h"

namespace dfv
{

class Camera
{
public:
	Camera();
	virtual ~Camera();

	enum Mode
	{
		Free,
		Walking,
		Driving
	};

	enum Direction
	{
		NoDirection,
		Forwards,
		Backwards,
		SidewaysLeft,
		SidewaysRight,
		Up,
		Down
	};

	enum Rotation
	{
		NoRotation,
		RollCW,
		RolCCW,
		PitchUp,
		PitchDown,
		YawLeft,
		YawRight
	};

	sf::Vector3f getPosition() const;
	sf::Vector2f getPosition2d() const;
	void setPosition(const sf::Vector3f& position);
	void move(const sf::Vector3f& v);
	const sf::Vector3f& getRpy() const;
	void setRpy(const sf::Vector3f& rpy);
	void rotate(const sf::Vector3f& v);
	unsigned int getQuadrant() const;
	void setView(const sf::Window& window) const;
	//dfv::IntRect GetRectFromView(const dfv::IntRect& map_rect) const;
	void handleInput(sf::Event& event);
	void update(float dt, float map_height, sf::Vector3f& normal);
	float getCarSpeed() const;
	float getMotorRPM() const;
	unsigned int getCarGear() const;
	float getCarTorque() const;
	float getCarPower() const;
	Mode getMode() const;
	dfv::RealIntRect getRectFromView(const dfv::RealIntRect& map_rect) const;

private:
	sf::Vector3f position;
	sf::Vector3f rpy;
	sf::Vector3f map_normal;
	Mode mode;
	Car car;
	float curr_pitch;
	float curr_roll;
};

} /* namespace dfv */
#endif /* CAMERA_H_ */
