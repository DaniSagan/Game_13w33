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
		quadrant(0),
		selected_tool(none)
		//copy_road_id(0),
		//copy_road_orientation(0)
{
	this->minimap.Create(256);
	this->font.loadFromFile("res/font/Ubuntu-L.ttf");

	Button b1("res/gui/button_road.png", sf::Vector2f(0, 0));
	//b1.LoadImage("res/gui/button_road.png");
	//b1.SetSize(sf::Vector2i(32, 32));
	//b1.SetPosition(sf::Vector2i(0, 0));
	b1.SetCommand(std::string("button_road_cmd"));
	this->button_list.push_back(b1);

	Button b2("res/gui/button_select.png", sf::Vector2f(0, 32));
	//b2.LoadImage("res/gui/button_select.png");
	//b2.SetSize(sf::Vector2i(32, 32));
	//b2.SetPosition(sf::Vector2i(0, 32));
	b2.SetCommand(std::string("button_select_cmd"));
	this->button_list.push_back(b2);

	Button b3("res/gui/button_copy.png", sf::Vector2f(0, 64));
	//b3.LoadImage("res/gui/button_copy.png");
	//b3.SetSize(sf::Vector2i(32, 32));
	//b3.SetPosition(sf::Vector2i(0, 64));
	b3.SetCommand(std::string("button_copy_cmd"));
	this->button_list.push_back(b3);


	//this->toolbar_img = sf::Image()
}

Gui::~Gui()
{
	// TODO Auto-generated destructor stub
}

void Gui::Draw(sf::RenderWindow& window, const Camera& camera) const
{
	sf::Text text("", this->font);
	std::stringstream ss;

	ss << "FPS: " << floor(this->fps) << ", Quadrant: " << camera.GetQuadrant() << ", RPY: " << camera.GetRpy().x << ", " << camera.GetRpy().y << ", " << camera.GetRpy().z;
	text.setString(ss.str());
	text.setCharacterSize(14.0);
	text.setPosition(300, 5);
	window.draw(text);

	ss.str(std::string(""));
	ss << "Map pos: " << this->map_pos.x << ", " << this->map_pos.y << "," << this->map_pos.z;
	text.setString(ss.str());
	text.setPosition(300, 20);
	window.draw(text);

	ss.str(std::string(""));
	ss << floor(camera.getCarTorque()) << " Nm, " << floor(camera.getCarPower()/746.0) << " bhp";
	text.setString(ss.str());
	text.setPosition(820, 380);
	window.draw(text);

	ss.str(std::string(""));
	ss << floor(camera.getCarSpeed()*3.6) << " km/h";
	text.setCharacterSize(40);
	text.setString(ss.str());
	text.setPosition(820, 400);
	window.draw(text);

	ss.str(std::string(""));
	ss << floor(camera.getMotorRPM()) << " rpm";
	text.setString(ss.str());
	text.setPosition(820, 450);
	window.draw(text);

	ss.str(std::string(""));
	ss << "Gear " << camera.getCarGear() + 1;
	text.setString(ss.str());
	text.setPosition(820, 500);
	window.draw(text);


	sf::ConvexShape shape;
	shape.setPointCount(4);
	shape.setPoint(0, this->selected_tile_vertices[0]);
	shape.setPoint(1, this->selected_tile_vertices[1]);
	shape.setPoint(2, this->selected_tile_vertices[2]);
	shape.setPoint(3, this->selected_tile_vertices[3]);
	shape.setFillColor(sf::Color(255, 255, 255, 64));
	window.draw(shape);

	/*sf::Shape shape = sf::Shape::Line(
			this->selected_tile_vertices[0],
			this->selected_tile_vertices[1],
			2.0, sf::Color(255, 0, 0));
	window.Draw(shape);
	shape = sf::Shape::Line(
			this->selected_tile_vertices[1],
			this->selected_tile_vertices[2],
			2.0, sf::Color(255, 0, 0));
	window.Draw(shape);
	shape = sf::Shape::Line(
			this->selected_tile_vertices[2],
			this->selected_tile_vertices[3],
			2.0, sf::Color(255, 0, 0));
	window.Draw(shape);
	shape = sf::Shape::Line(
			this->selected_tile_vertices[3],
			this->selected_tile_vertices[0],
			2.0, sf::Color(255, 0, 0));
	window.Draw(shape);*/

	// toolbar

	this->minimap.Draw(window, camera);

	/*sf::Image toolbar_img(42, window.GetHeight() - this->minimap.GetSize() + 1, sf::Color(200, 200, 200, 150));
	window.Draw(sf::Sprite(toolbar_img));*/

	std::list<Button>::const_iterator it;
	for(it = this->button_list.begin(); it != this->button_list.end(); it++)
	{
		it->Draw(window);
	}


	/*sf::Shape toolbar_rect;
	toolbar_rect = sf::Shape::Line(
			200, 200,
			//window.GetWidth() - this->minimap.GetSize(), 42,
			500, 500, 1.0,
			sf::Color(0, 0, 0));
	window.Draw(toolbar_rect);*/
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

void Gui::SetSelectedTileVertices(const std::vector<sf::Vector2f>& selected_tile_vertices)
{
	this->selected_tile_vertices = selected_tile_vertices;
}

std::vector<std::string> Gui::HandleInput(const sf::Event& event, std::vector<std::string>& commands)
{
	if(event.type == sf::Event::KeyPressed)
	{
		if(event.key.code == sf::Keyboard::B)
		{

		}
	}


	std::vector<std::string> button_commands;
	std::list<Button>::iterator it;
	for(it = this->button_list.begin(); it != this->button_list.end(); it++)
	{
		it->HandleInput(button_commands, event);
	}

	//std::vector<std::string> commands;
	if(button_commands.size() == 0)
	{
		std::stringstream ss;
		if(this->selected_tool == road)
		{
			// if left click
			if(event.type == sf::Event::MouseButtonPressed &&
					event.mouseButton.button == sf::Mouse::Left)
			{
				// command : build_road <x> <y>
				ss << "build_road " << floor(this->map_pos.x) << " " << floor(this->map_pos.y);
				std::cout << "Command: " << ss.str() << std::endl;
				commands.push_back(ss.str());
			}

			// if right click
			if(event.type == sf::Event::MouseButtonPressed &&
						event.mouseButton.button == sf::Mouse::Right)
			{
				// command : rotate_road <x> <y>
				ss << "rotate_road " << floor(this->map_pos.x) << " " << floor(this->map_pos.y);
				std::cout << "Command: " << ss.str() << std::endl;
				commands.push_back(ss.str());
			}
		}
		else if(this->selected_tool == select)
		{

		}
		else if(this->selected_tool == copy)
		{
			// if left click
			if(event.type == sf::Event::MouseButtonPressed &&
					event.mouseButton.button == sf::Mouse::Left)
			{
				// command : copy_road <x> <y>

				ss << "copy_road " << floor(this->map_pos.x) << " " << floor(this->map_pos.y);
				std::cout << "Command: " << ss.str() << std::endl;
				commands.push_back(ss.str());
			}
		}
	}
	else
	{
		for(unsigned int i = 0; i < button_commands.size(); i++)
		{
			if(button_commands[i] == "button_road_cmd")
			{
				this->selected_tool = road;
				std::cout << "Selected road tool" << std::endl;
			}
			else if(button_commands[i] == "button_select_cmd")
			{
				this->selected_tool = select;
				std::cout << "Selected select tool" << std::endl;
			}
			else if(button_commands[i] == "button_copy_cmd")
			{
				this->selected_tool = copy;
				std::cout << "Selected copy tool" << std::endl;
			}
		}
	}

	return commands;
}

std::vector<std::string>& Gui::handleButtonInput(const sf::Event& event, std::vector<std::string>& commands)
{
	//std::vector<std::string> button_commands;
	std::list<Button>::iterator it;
	for(it = this->button_list.begin(); it != this->button_list.end(); it++)
	{
		it->HandleInput(commands, event);
	}
	return commands;
}

void Gui::Update(const Map& map, const sf::Vector2f& position)
{
	this->minimap.GenerateFromMap(map, position, 64);
}

} /* namespace dfv */
