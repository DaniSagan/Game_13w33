/*
 * Gui.h
 *
 *  Created on: Aug 20, 2013
 *      Author: daniel
 */

#ifndef GUI_H_
#define GUI_H_

#include <SFML/Graphics.hpp>
#include <sstream>
#include "Minimap.h"

namespace dfv
{

class Gui
{
public:
	Gui();
	virtual ~Gui();

	void Draw(sf::RenderWindow& window, const Camera& camera) const;
	void SetFps(float fps);
	void SetQuadrant(unsigned int quadrant);
	void SetMapPos(const sf::Vector3f& mapPos);
	void SetSelectedTileVertices(const std::vector<sf::Vector2f>& selected_vertices);

	std::vector<std::string> HandleInput(const sf::Event& event);
	void Update(const Map& map, const sf::Vector2f& position);

private:

	float fps;
	unsigned int quadrant;
	Minimap minimap;
	sf::Vector3f map_pos;
	std::vector<sf::Vector2f> selected_tile_vertices;
	sf::IntRect selected_tiles;
};

} /* namespace dfv */
#endif /* GUI_H_ */
