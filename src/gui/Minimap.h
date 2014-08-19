/*
 * Minimap.h
 *
 *  Created on: Aug 15, 2013
 *      Author: daniel
 */

#ifndef MINIMAP_H_
#define MINIMAP_H_

#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
#include "../Camera.h"
#include "../Map.h"

namespace dfv
{

class Minimap
{
public:
	Minimap();
	virtual ~Minimap();

	void create(const unsigned int size);
	//void GenerateFromMap(Map* lp_map, const Camera& camera);
	void generateFromMap(const Map& map, const sf::Vector2f position, unsigned int range);
	sf::Vector2i realPosFromMapPos(sf::Vector2i map_pos, int range);
	void draw(sf::RenderWindow& window, const Camera& camera) const;
	std::string handleInput(const Camera& camera, const sf::Event& event, const sf::Vector2i& mouse_pos);
	unsigned int getSize() const;

private:
	sf::Image img;
	unsigned int size;
	unsigned int range;
	sf::Uint8* lp_pixels;
	sf::Texture texture;
	//dfv::Map* lp_map;
};

} /* namespace dfv */
#endif /* MINIMAP_H_ */
