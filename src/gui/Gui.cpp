/*
 * Gui.cpp
 *
 *  Created on: Aug 20, 2013
 *      Author: daniel
 */

#include "Gui.h"

namespace dfv
{

Gui::Gui():
		fps(0),
		quadrant(0)
{
	// TODO Auto-generated constructor stub

}

Gui::~Gui()
{
	// TODO Auto-generated destructor stub
}

void Gui::Draw(sf::RenderWindow& window) const
{
	sf::String string;
	string.SetSize(12.0);
	std::stringstream ss;

	ss << "FPS: " << this->fps;
	string.SetText(ss.str());
	string.SetPosition(300, 5);
	window.Draw(string);

	ss.str(std::string(""));
	ss << "Map pos: " << this->map_pos.x << ", " << this->map_pos.y << "," << this->map_pos.z;
	string.SetText(ss.str());
	string.SetPosition(300, 20);
	window.Draw(string);

	sf::Shape shape = sf::Shape::Line(
			this->selected_vertices[0],
			this->selected_vertices[1],
			2.0, sf::Color(255, 0, 0));
	window.Draw(shape);
	shape = sf::Shape::Line(
			this->selected_vertices[1],
			this->selected_vertices[2],
			2.0, sf::Color(255, 0, 0));
	window.Draw(shape);
	shape = sf::Shape::Line(
			this->selected_vertices[2],
			this->selected_vertices[3],
			2.0, sf::Color(255, 0, 0));
	window.Draw(shape);
	shape = sf::Shape::Line(
			this->selected_vertices[3],
			this->selected_vertices[0],
			2.0, sf::Color(255, 0, 0));
	window.Draw(shape);
}

void Gui::SetFps(float fps)
{
	this->fps = fps;
}

void Gui::SetQuadrant(unsigned int quadrant)
{
	this->quadrant = quadrant;
}

void Gui::SetMapPos(const sf::Vector3f& map_pos)
{
	this->map_pos = map_pos;
}

void Gui::SetSelectedVertices(const std::vector<sf::Vector2f>& selected_vertices)
{
	this->selected_vertices = selected_vertices;
}

std::vector<std::string> Gui::HandleInput(const sf::Event& event)
{
	std::vector<std::string> commands;
	std::stringstream ss;

	if(event.Type == sf::Event::MouseButtonPressed &&
			event.MouseButton.Button == sf::Mouse::Left)
	{
		ss << "build_road " << floor(this->map_pos.x) << " " << this->map_pos.y;
		commands.push_back(ss.str());
	}

	if(event.Type == sf::Event::MouseButtonPressed &&
				event.MouseButton.Button == sf::Mouse::Right)
	{
		ss << "rotate_road " << floor(this->map_pos.x) << " " << this->map_pos.y;
		commands.push_back(ss.str());
	}

	return commands;
}

} /* namespace dfv */
