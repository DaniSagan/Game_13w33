/*
 * Building.h
 *
 *  Created on: Aug 12, 2013
 *      Author: daniel
 */

#ifndef BUILDING_H_
#define BUILDING_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

namespace dfv
{

class Building
{
public:
	Building();
	virtual ~Building();

	void Create(const std::vector<sf::Vector3f>& base_pos, float height);
	void SetColor(const sf::Color& color);
	sf::Color GetColor() const;
	void Draw(const bool draw_floors) const;
	float GetHeight() const;

	void DrawBox() const;
	void DrawOutline() const;
	void DrawFloors() const;

	sf::Vector3f GetColor3f() const;

private:
	std::vector<sf::Vector3f> base_pos;
	std::vector<sf::Vector3f> roof_pos;
	std::vector<sf::Vector3f> colors;
	std::vector<sf::Vector2f> floor_pos;
	std::vector<float> floor_heights;
	float height;
};

} /* namespace dfv */
#endif /* BUILDING_H_ */
