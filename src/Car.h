/*
 * Car.h
 *
 *  Created on: Jun 26, 2014
 *      Author: daniel
 */

#ifndef CAR_H_
#define CAR_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

namespace dfv
{

class Car
{
public:
	Car();
	virtual ~Car();

	enum State
	{
		None,
		Accelerating,
		Braking
	};

	void init();
	void setTorqueParameters(float k, float w0, float w1);
	void setGearRatios(std::vector<float>& gear_ratios);
	void setWheelRadius(float radius);
	float getCurrTorque() const;
	float getMaxTorque() const;
	float getMaxPower() const;
	float getMotorW() const;
	bool gearUp();
	bool gearDown();
	void update(float dt, float pitch);
	void setState(State state);
	float getDrag() const;
	float getForce() const;
	float getSpeed() const;
	float getSteeringAngle() const;
	unsigned int getGear() const;
	float getGravityForce(float pitch) const;
	float getSteeringRadius() const;
	float getDeltaSteeringAngle(float dt) const;
	float getCentrifugalForce() const;
	float getMaxCentrifugalForce() const;
	float getMaxDeltaSteeringAngle(float dt) const;
private:
	float k, w0, w1;
	sf::Vector3f position;
	sf::Vector3f rpy;
	float speed;
	float mass;
	float wheel_radius;
	std::vector<float> gear_ratios;
	float yaw;
	unsigned int curr_gear;
	State state;
	float steering_angle;
	float steering_time;
	float friction_coeff;
	float wheel_base;
};

} /* namespace dfv */
#endif /* CAR_H_ */
