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
	void update(float dt);
	void setState(State state);
	float getDrag() const;
	float getForce() const;
	float getSpeed() const;
	float getSteeringAngle() const;
	unsigned int getGear() const;
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
};

} /* namespace dfv */
#endif /* CAR_H_ */
