/*
 * App.cpp
 *
 *  Created on: Aug 11, 2013
 *      Author: daniel
 */

#include "App.h"

namespace dfv
{

App::App():
		frame(0),
		walking(false),
		road_id(0),
		road_orientation(0),
		frame_time(0),
		moving_mode(Free)
{
	this->initialize();
	//this->Run();
}

App::~App()
{
	// TODO Auto-generated destructor stub
}

void App::initialize()
{
	srand(0);

	this->window.create(sf::VideoMode(1024, 1024 * 9 / 16), "Saganopolis", sf::Style::Default, sf::ContextSettings(32));
	this->window.setVerticalSyncEnabled(true);
	this->initOpenGL();

	//this->map.LoadFromMapFormat("res/map/world1_test.map");
	this->map.createRandom(700);
	/*Tree* lp_tree = new Tree();
	std::vector<sf::Vector3f> tile_vertices = this->map.GetTileVertices(sf::Vector2i(167, 196));
	lp_tree->Create(tile_vertices);
	this->map.addProp(167, 196, lp_tree);*/

	Tree* lp_tree = new Tree();
	for(unsigned int i = 0; i < 50000; i++)
	{
		unsigned int x = rand() % this->map.getSize();
		unsigned int y = rand() % this->map.getSize();
		if(!this->map.isWater(x, y) && !this->map.hasBuilding(x, y) && !this->map.isRoad(x, y))
		{
			lp_tree = new Tree();
			std::vector<sf::Vector3f> tile_vertices = this->map.getTileVertices(sf::Vector2i(x, y));
			lp_tree->create(tile_vertices);
			this->map.addProp(x, y, lp_tree);
		}
	}

	this->camera.setPosition(sf::Vector3f(this->map.getSize() / 2, this->map.getSize() / 2, 5.f));
	this->camera.setRpy(sf::Vector3f(-90.0, 0.0, 0.0));
	this->resources.load();

	this->map.generateTileList(this->camera, this->resources);
	this->map.generateBuildingList();
	this->map.generateRoadList(this->camera, this->resources);

}

void App::run()
{
	while(this->window.isOpen())
	{
		this->handleInput();
		this->update();
		this->draw();
	}
}

void App::update()
{
	++this->frame;
	this->frame_time = this->clock.restart().asSeconds();

	sf::Vector2f camera_pos = this->camera.getPosition2d();
	sf::Vector3f normal = this->map.getNormal(camera_pos.x, camera_pos.y);
	this->camera.update(this->frame_time,
						this->map.getHeight(sf::Vector2f(this->camera.getPosition().x, this->camera.getPosition().y)),
						normal);

	this->gui.setFps(1.0 / this->frame_time);
	this->gui.setQuadrant(this->camera.getQuadrant());
	this->gui.update(this->map, this->camera.getPosition2d());

	// window vertices of selected tile;
	sf::Vector2i tile_pos(floor(this->map_pos.x), floor(this->map_pos.y));
	if(tile_pos.x < 0) tile_pos.x = 0;
	if(tile_pos.x >= (int)this->map.getSize()) tile_pos.x = this->map.getSize() - 1;
	if(tile_pos.y < 0) tile_pos.y = 0;
	if(tile_pos.y >= (int)this->map.getSize()) tile_pos.y = this->map.getSize() - 1;

	std::vector<sf::Vector3f> tile_vertices = this->map.getTileVertices(tile_pos);
	std::vector<sf::Vector2f> sel_vertices(4);
	try
	{
		for(unsigned int k = 0; k < 4; k++)
		{
			sel_vertices.at(k) = dfv::Utils::getVector2d(this->map.getViewPos(tile_vertices.at(k), this->window));
		}
		this->gui.setSelectedTileVertices(sel_vertices);
	}
	catch(...)
	{
		std::cout << "Error getting view pos vertices" << std::endl;
	}

	/*std::vector<sf::ConvexShape> selected_shapes(this->selected_tiles.size());
	std::vector<sf::Vector2u>::iterator it;
	unsigned int i = 0;
	for(it = this->selected_tiles.begin(); it != this->selected_tiles.end(); it++)
	{
		sf::Vector2i pos(it->x, it->y);
		try
		{
			std::vector<sf::Vector3f> tile_vertices = this->map.GetTileVertices(pos);
			std::vector<sf::Vector2f> sel_vertices(4);
			for(unsigned int k = 0; k < 4; k++)
			{
				sel_vertices.at(k) = dfv::Utils::GetVector2d(this->map.GetViewPos(tile_vertices[k], window));
			}
			selected_shapes.at(i).setPointCount(4);
			for(unsigned int k = 0; k < 4; k++)
			{
				selected_shapes.at(i).setPoint(k, sel_vertices.at(k));
			}
			selected_shapes.at(i).setFillColor(sf::Color(255, 0, 0, 64));
		}
		catch(...)
		{
			std::cout << "Index out of range" << std::endl;
		}
		i++;
	}

	this->gui.setSelectedShapes(selected_shapes);*/

	//std::cout << "Map pos: " << this->map_pos.x << ", " << this->map_pos.y << std::endl;
}

void App::handleInput()
{
	this->mouse_pos = sf::Vector2i(sf::Mouse::getPosition(this->window));
	sf::Event event;
	this->command.clear();
	while(this->window.pollEvent(event))
	{
		this->gui.handleInput(event, this->command);
		if(this->executeCommand(this->command)) break;
		this->camera.handleInput(event);

		if(event.type == sf::Event::Closed)
		{
			this->window.close();
		}
		else if (event.type == sf::Event::Resized)
		{
			glViewport(0, 0, event.size.width, event.size.height);
			this->window.setView(sf::View(sf::FloatRect(0.0, 0.0, event.size.width, event.size.height)));
		}
		else if(event.type == sf::Event::KeyPressed)
		{
			/*if(event.key.code == sf::Keyboard::N)
			{
				this->walking = !this->walking;
			}*/
			if(event.key.code == sf::Keyboard::P)
			{
				this->map.saveAsMapFormat("res/map/world1.map");
			}
			else if(event.key.code == sf::Keyboard::O)
			{
				std::string cmd;
				std::cout << "cmd> ";
				std::getline(std::cin, cmd);
				//this->commands.push_back(cmd);
				this->command = cmd;
			}
		}
		else if(event.type == sf::Event::MouseWheelMoved)
		{
			float height = this->map.getHeight(sf::Vector2f(this->camera.getPosition().x, this->camera.getPosition().y));
			this->camera.move(sf::Vector3f(0.f,
										   0.f,
							               -0.02f * (float)event.mouseWheel.delta * (this->camera.getPosition().z - height)));
		}
		else if(event.type == sf::Event::MouseButtonPressed)
		{
			if(event.mouseButton.button == sf::Mouse::Left)
			{
				//sf::Vector3f v = this->map.GetMapPosFromMouse(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
				this->select_from = this->map.getTileFromMapPos(this->map_pos);//sf::Vector2i(floor(v.x), floor(v.y));
				std::cout << "select_from:" << this->select_from.x << ", " << this->select_from.y << std::endl;
				this->selected_tiles.clear();
				this->selected_tiles.push_back(this->select_from);
				//this->createSelectedShapes();
			}
			else if(event.mouseButton.button == sf::Mouse::Right)
			{
				this->select_to = this->map.getTileFromMapPos(this->map_pos);
				this->selected_tiles.clear();
				std::cout << "select_to:" << this->select_to.x << ", " << this->select_to.y << std::endl;
				for(int i = std::min(this->select_from.x, this->select_to.x); i <= std::max(this->select_from.x, this->select_to.x); i++)
				{
					for(int j = std::min(this->select_from.y, this->select_to.y); j <= std::max(this->select_from.y, this->select_to.y); j++)
					{
						this->selected_tiles.push_back(sf::Vector2i(i, j));

					}
				}
			}
		}
	}

	//this->gui.HandleInput(event, this->commands);


}

void App::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	this->window.setActive();
	this->camera.setView(this->window);

	this->map.drawSky();

	this->map.setLight(sf::Vector3f(400.f, -200.f, 400.f));

	//dfv::IntRect view_rect = this->camera.GetRectFromView(this->map.GetRect());
	dfv::RealIntRect view_rect = this->camera.getRectFromView(this->map.getTileRect());
	if(this->camera.getRpy().x > -120.f)
	{
		this->map.callTileList();
	}
	this->map_pos = this->map.getMapPosFromMouse(this->mouse_pos);
	this->createSelectedShapes();

	//sf::Vector2i position = dfv::Utils::ToVector2i(this->camera.GetPosition2d());
	//dfv::IntRect road_rect = dfv::Utils::CreateRect(position, 50);
	//dfv::Utils::TrimRect(road_rect, this->camera.GetRectFromView(this->map.GetRect()));
	dfv::RealIntRect road_rect;
	road_rect.setFromCenterRadius(dfv::Utils::toVector2i(this->camera.getPosition2d()), 50);
	//road_rect.trim(this->map.getRect());
	road_rect.trim(this->camera.getRectFromView(this->map.getTileRect()));
	//this->map.DrawRoads(road_rect, this->camera, this->resources);

	this->map.drawRoads(road_rect, this->camera, this->resources);
	//this->map.callRoadList();

	/*dfv::IntRect outlines_rect = dfv::Utils::CreateRect(
			dfv::Utils::ToVector2i(this->camera.GetPosition2d()),
			30);*/

	dfv::RealIntRect outlines_rect;
	outlines_rect.setFromCenterRadius(dfv::Utils::toVector2i(this->camera.getPosition2d()), 30);
	outlines_rect.trim(this->camera.getRectFromView(this->map.getTileRect()));

	//dfv::Utils::TrimRect(outlines_rect, view_rect);

	this->map.callBuildingList();
	glDisable(GL_CULL_FACE);
	this->map.drawBuildingOutlines(outlines_rect);

	this->gui.setMapPos(this->map_pos);
	this->map.drawBuildingFloors(outlines_rect);

	glDisable(GL_LIGHTING);
	this->map.drawProps(road_rect, this->camera, this->resources);
	glEnable(GL_LIGHTING);

	glEnable(GL_CULL_FACE);



	this->window.pushGLStates();

	this->drawSelection(this->window);
	this->gui.draw(this->window, this->camera);


	this->window.popGLStates();
	this->window.display();
}

void App::initOpenGL()
{
	glClearDepth(1.0f);
	glClearColor(0.5f, 0.6f, 0.95f, 0.f);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(55.f, (float)this->window.getSize().x / (float)this->window.getSize().y, 0.01f, 2500.f);

	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//GLfloat mat_specular[] = { 0.2, 0.2, 0.2, 0.2 };
	GLfloat mat_specular[] = { 0.0, 0.0, 0.0, 0.0 };
	GLfloat mat_shininess[] = { 128.0 };
	GLfloat light_position[] = { 400.0, 0.0, 400.0, 0.0 };
	glShadeModel (GL_SMOOTH);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
}

bool App::executeCommand(std::string cmd)
{
	std::vector<std::string> tokens = dfv::Utils::stringTokenize(cmd, " ");
	if(tokens.size() == 0) return false;

	try
	{
		if(tokens.at(0) == std::string("save"))
		{
			std::string filename;
			if(tokens.size() == 2)
			{
				filename = tokens.at(1);
			}
			else
			{
				filename = "res/map/world1_test.map";
			}
			this->map.saveAsMapFormat(filename);
			std::cout << "Map saved in file " << filename << std::endl;
			return true;
		}
		else if(tokens.at(0) == std::string("select"))
		{
			if(tokens.at(1) == std::string("from") && tokens.at(4) == std::string("to"))
			{
				unsigned int x1, y1, x2, y2;
				x1 = strtol(tokens.at(2).c_str(), NULL, 10);
				y1 = strtol(tokens.at(3).c_str(), NULL, 10);
				x2 = strtol(tokens.at(5).c_str(), NULL, 10);
				y2 = strtol(tokens.at(6).c_str(), NULL, 10);
				this->selected_tiles.clear();
				for(unsigned int y = std::min(y1, y2); y <= std::max(y1, y2); y++)
				{
					for(unsigned int x = std::min(x1, x2); x <= std::max(x1, x2); x++)
					{
						this->selected_tiles.push_back(sf::Vector2i(x, y));
					}
				}
				return true;
			}
			else
			{
				unsigned int x, y;
				x = std::stoi(tokens.at(1));
				y = std::stoi(tokens.at(2));
				this->selected_tiles.clear();
				this->selected_tiles.push_back(sf::Vector2i(x, y));
				std::cout << "Selected tile at " << x << "," << y << std::endl;
				return true;
			}
		}
		else if(tokens.at(0) == std::string("selected"))
		{
			std::vector<sf::Vector2i>::iterator it;
			std::cout << "Selected tiles:" << std::endl;
			for(it = this->selected_tiles.begin(); it != this->selected_tiles.end(); it++)
			{
				std::cout << it->x << ", " << it->y << std::endl;
			}
			return true;
		}
		else if(tokens.at(0) == std::string("clear"))
		{
			if(tokens.at(1) == std::string("road"))
			{
				std::vector<sf::Vector2i>::iterator it;
				for(it = this->selected_tiles.begin(); it != this->selected_tiles.end(); it++)
				{
					this->map.clearRoad(it->x, it->y);
				}
				this->map.generateTileList(this->camera, this->resources);
				return true;
			}
			else if(tokens.at(1) == std::string("building"))
			{
				std::vector<sf::Vector2i>::iterator it;
				for(it = this->selected_tiles.begin(); it != this->selected_tiles.end(); it++)
				{
					this->map.clearBuilding(it->x, it->y);
				}
				this->map.generateBuildingList();
				return true;
			}
			else if(tokens.at(1) == std::string("prop"))
			{
				std::vector<sf::Vector2i>::iterator it;
				for(it = this->selected_tiles.begin(); it != this->selected_tiles.end(); it++)
				{
					this->map.clearProp(it->x, it->y);
				}
				this->map.generateBuildingList();
				return true;
			}
		}
		else if(tokens.at(0) == std::string("build"))
		{
			if(tokens.at(1) == std::string("road"))
			{
				unsigned int id = std::stoi(tokens.at(2));
				unsigned int orientation = std::stoi(tokens.at(2));
				std::vector<sf::Vector2i>::iterator it;
				for(it = this->selected_tiles.begin(); it != this->selected_tiles.end(); it++)
				{
					this->map.buildRoad(it->x, it->y, id, orientation);
				}
				this->map.generateTileList(this->camera, this->resources);
				return true;
			}
		}
		std::cout << "Could not recognize command" << std::endl;
		return false;
	}
	catch(...)
	{
		std::cout << "Could not recognize command" << std::endl;
		return false;
	}
}

void App::createSelectedShapes()
{
	this->selected_shapes.clear();
	this->selected_shapes.resize(this->selected_tiles.size());
	std::vector<sf::Vector2i>::const_iterator it;
	unsigned int i = 0;
	for(it = this->selected_tiles.begin(); it != this->selected_tiles.end(); it++)
	{
		sf::Vector2i pos(it->x, it->y);
		//std::cout << pos.x << ", " << pos.y << std::endl;
		std::vector<sf::Vector3f> tile_vertices = this->map.getTileVertices(pos);
		std::vector<sf::Vector2f> sel_vertices(4);
		for(unsigned int k = 0; k < 4; k++)
		{
			sel_vertices.at(k) = dfv::Utils::getVector2d(this->map.getViewPos(tile_vertices[k], window));
		}
		this->selected_shapes.at(i).setPointCount(4);
		for(unsigned int k = 0; k < 4; k++)
		{
			this->selected_shapes.at(i).setPoint(k, sel_vertices.at(k));
		}
		this->selected_shapes.at(i).setFillColor(sf::Color(255, 0, 0, 64));
		i++;
	}
}

void App::drawSelection(sf::RenderWindow& window) const
{
	std::vector<sf::ConvexShape>::const_iterator it;
	for(it = this->selected_shapes.begin(); it != this->selected_shapes.end(); it++)
	{
		window.draw(*it);
	}
}

sf::Vector2i App::getCameraTile() const
{
	sf::Vector2f camera_pos = this->camera.getPosition2d();
	sf::Vector2i pos(floor(camera_pos.x), floor(camera_pos.y));
	return pos;
}

} /* namespace dfv */
