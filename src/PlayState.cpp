/*
 * PlayState.cpp
 *
 *  Created on: Aug 30, 2014
 *      Author: daniel
 */

#include "PlayState.h"

namespace dfv
{

PlayState PlayState::play_state;

void PlayState::init(GameEngine* lp_game_engine)
{
	assert(this->test());

	srand(time(NULL));

	//this->window.create(sf::VideoMode(1024, 1024 * 9 / 16), "Saganopolis", sf::Style::Default, sf::ContextSettings(32));
	//this->window.setVerticalSyncEnabled(true);
	this->initOpenGL(lp_game_engine);

	// Initialize comand server
	if(!this->cmd_server.init())
	{
		std::cout << "ERROR: could not initialize command server." << std::endl;
	}
	else
	{
		this->cmd_server.run();
	}

	//this->map.LoadFromMapFormat("res/map/world1_test.map");
	//this->map.createRandom(700);
	//this->map.createFlat(850, 2.0);
	//this->map.createFlat(64, 2.0);
	this->map.createFlat(900, 2.f);

	// create roads
	for(unsigned int i = 0; i < this->map.getSize(); i++)
	{
		for(unsigned int j = 0; j < this->map.getSize(); j++)
		{
			if(!this->map.isWater(i, j) &&
			   !this->map.isBeach(i, j) &&
			   this->map.getMaxInclination(i, j) < 0.25f //&&
			   //this->map.getAvgHeight(i, j) < 5.f)
			   )
			{
				sf::Vector2i pos(i, j);
				if((i%4 == 0) && !((j%4==0) || (j%20==1)))
				{
					this->map.addRoad(pos, Road::straight, 0);
				}
				else if(!(i%4 == 0) && ((j%4==0) || (j%20==1)))
				{
					this->map.addRoad(pos, Road::straight, 1);
				}
				else if((i%4 == 0) && ((j%4==0) || (j%20==1)))
				{
					this->map.addRoad(pos, Road::cross, 0);
				}
			}
		}
	}

	// generate random trees
	Tree* lp_tree = new Tree();
	for(unsigned int i = 0; i < 200000; i++)
	{
		unsigned int x = rand() % this->map.getSize();
		unsigned int y = rand() % this->map.getSize();
		if(!this->map.isWater(x, y) &&
		   !this->map.isBeach(x, y) &&
		   !this->map.hasBuilding(x, y) &&
		   !this->map.isRoad(x, y))
		{
			lp_tree = new Tree();
			std::vector<sf::Vector3f> tile_vertices = this->map.getTileVertices(sf::Vector2i(x, y));
			lp_tree->create(tile_vertices);
			this->map.addProp(x, y, lp_tree);
		}
	}

	// generate lots
	unsigned int buildings = 0;
	unsigned int floors = 0;
	for(unsigned int i = 0; i < 5000000; i++)
	{
		unsigned int xmin = rand() % this->map.getSize();
		unsigned int ymin = rand() % this->map.getSize();
		//unsigned int size_x = (rand() % 3) + 1;
		//unsigned int size_y = (rand() % 3) + 1;
		unsigned int size_x = 1 + floor(2.f * Utils::rFunction(Utils::floatRandom(0.f, 1.f), 10.f) + 0.5f);
		unsigned int size_y = 1 + floor(2.f * Utils::rFunction(Utils::floatRandom(0.f, 1.f), 10.f) + 0.5f);
		//std::cout << xmin << ", " << ymin << ", " << size_x << ", " << size_y << std::endl;
		if(this->map.addLot(xmin, ymin, xmin + (size_x-1), ymin + (size_y-1)))
		{
			Model model;
			Lot* lp_lot = this->map.getLot(xmin, ymin);
			Quad base_quad;
			std::vector<sf::Vector3f> base_vertices = {sf::Vector3f(Utils::floatRandom(0.f, 0.3*size_x), Utils::floatRandom(0.f, 0.3*size_y), 0.0),
													   sf::Vector3f(Utils::floatRandom(0.7*size_x, size_x), Utils::floatRandom(0.f, 0.3*size_y), 0.0),
													   sf::Vector3f(Utils::floatRandom(0.7*size_x, size_x), Utils::floatRandom(0.7*size_y, size_y), 0.0),
													   sf::Vector3f(Utils::floatRandom(0.f, 0.3*size_x), Utils::floatRandom(0.7*size_y, size_y), 0.0)};
			base_quad.create(base_vertices);
			unsigned int floor_count = floor(20.f * float(size_x*size_y) * Utils::rFunction(Utils::floatRandom(0.f, 1.f), 1));
			model.create(lp_lot->getMinHeight(), lp_lot->getMaxHeight(), lp_lot->getOrigin2d(), base_quad, floor_count);

			Structure* lp_structure = new Structure();
			lp_structure->setModel(model);
			lp_lot->addStructure(lp_structure);

			buildings++;
			floors += floor_count;
			//std::cout << "Model created" << std::endl;
		}
	}

	std::cout << "Buildings: " << buildings << std::endl;
	std::cout << "Floors: " << floors << std::endl;

	this->camera.setPosition(sf::Vector3f(this->map.getSize() / 2, this->map.getSize() / 2, 5.f));
	this->camera.setRpy(sf::Vector3f(-90.0, 0.0, 0.0));
	this->resources.load();

	this->generateLists();
}

void PlayState::cleanup()
{
}

void PlayState::pause()
{
}

void PlayState::resume()
{
}

void PlayState::handleInput(GameEngine* lp_game_engine)
{
	this->mouse_pos = sf::Vector2i(sf::Mouse::getPosition(lp_game_engine->window));
	std::string server_cmd = this->cmd_server.getCmd();
	if(server_cmd != std::string(""))
	{
		std::cout << "Command received!: " << server_cmd << std::endl;
		this->executeCmd(server_cmd, lp_game_engine);
	}

	std::string cmd("");
	sf::Event event;
	while(lp_game_engine->window.pollEvent(event))
	{
		this->camera.handleInput(event);
		this->root_component.handleInput(cmd, event);
		this->executeCmd(cmd, lp_game_engine);
		if(event.type == sf::Event::Closed)
		{
			lp_game_engine->quit();
		}
		this->gui.handleInput(event, this->command);
		if(!this->command.empty())
		{
			std::cout << "Command: " << this->command << std::endl;
		}
		if(this->executeCmd(this->command, lp_game_engine)) break;

		if(event.type == sf::Event::Closed)
		{
			this->cmd_server.terminate();
			lp_game_engine->window.close();
		}
		else if (event.type == sf::Event::Resized)
		{
			glViewport(0, 0, event.size.width, event.size.height);
			lp_game_engine->window.setView(sf::View(sf::FloatRect(0.0, 0.0, event.size.width, event.size.height)));
		}
		else if(event.type == sf::Event::KeyPressed)
		{
			if(event.key.code == sf::Keyboard::P)
			{
				this->map.saveAsMapFormat("res/map/world1.map");
			}
			else if(event.key.code == sf::Keyboard::O)
			{
				std::string cmd;
				std::cout << "cmd> ";
				std::getline(std::cin, cmd);
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
				this->select_from = this->map.getTileFromMapPos(this->map_pos);//sf::Vector2i(floor(v.x), floor(v.y));
				std::cout << "select_from:" << this->select_from.x << ", " << this->select_from.y << std::endl;
				this->selected_tiles.clear();
				this->selected_tiles.push_back(this->select_from);
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
}

void PlayState::update(GameEngine* lp_game_engine)
{
	++this->frame;
	this->frame_time = this->clock.restart().asSeconds();

	sf::Vector2f camera_pos = this->camera.getPosition2d();
	sf::Vector3f normal = this->map.getNormal(camera_pos.x, camera_pos.y);
	this->camera.update(this->frame_time,
						this->map.getHeight(sf::Vector2f(this->camera.getPosition().x, this->camera.getPosition().y)),
						normal);

	// update gui data
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
			sel_vertices.at(k) = dfv::Utils::getVector2d(this->map.getViewPos(tile_vertices.at(k), lp_game_engine->window));
		}
		this->gui.setSelectedTileVertices(sel_vertices);
	}
	catch(...)
	{
		std::cout << "Error getting view pos vertices" << std::endl;
	}
}

void PlayState::draw(GameEngine* lp_game_engine)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	lp_game_engine->window.setActive();
	this->camera.setView(lp_game_engine->window);

	this->map.drawSky();
	this->map.setLight(sf::Vector3f(800.f, -200.f, 800.f));

	dfv::RealIntRect view_rect = this->camera.getRectFromView(this->map.getTileRect());
	this->map.callTileList();
	this->map_pos = this->map.getMapPosFromMouse(this->mouse_pos);
	this->createSelectedShapes(lp_game_engine);

	dfv::RealIntRect road_rect;
	road_rect.setFromCenterRadius(dfv::Utils::toVector2i(this->camera.getPosition2d()), 50);
	road_rect.trim(this->camera.getRectFromView(this->map.getTileRect()));

	this->map.drawRoads(road_rect, this->camera, this->resources);

	dfv::RealIntRect outlines_rect;
	outlines_rect.setFromCenterRadius(dfv::Utils::toVector2i(this->camera.getPosition2d()), 30);
	outlines_rect.trim(this->camera.getRectFromView(this->map.getTileRect()));

	this->map.callStructureBoxList();
	glDisable(GL_CULL_FACE);
	this->map.drawStructureOutlines(outlines_rect);

	this->gui.setMapPos(this->map_pos);

	glDisable(GL_LIGHTING);
	this->map.drawProps(road_rect, this->camera, this->resources);
	glEnable(GL_LIGHTING);

	glEnable(GL_CULL_FACE);

	lp_game_engine->window.pushGLStates();

	this->drawSelection(lp_game_engine->window);
	this->gui.draw(lp_game_engine->window, this->camera);

	lp_game_engine->window.popGLStates();
	lp_game_engine->window.display();
}

bool PlayState::executeCmd(const std::string& cmd, GameEngine* lp_game_engine)
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
				unsigned int orientation = std::stoi(tokens.at(3));
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

void PlayState::initOpenGL(GameEngine* lp_game_engine)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0f);
	glClearColor(0.5f, 0.6f, 0.95f, 0.f);
	//glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(55.f, (float)lp_game_engine->window.getSize().x / (float)lp_game_engine->window.getSize().y, 0.01f, 2500.f);

	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLfloat mat_specular[] = { 0.0, 0.0, 0.0, 0.0 };
	GLfloat mat_shininess[] = { 0.5 };
	GLfloat light_position_0[] = { 800.0, -200.0, 800.0, 0.0 };
	GLfloat light_position_1[] = { -800.0, -200.0, 800.0, 0.0 };
	//GLfloat ambient[] = {0.1, 0.1, 0.15, 1.0};
	GLfloat ambient[] = {0.0, 0.0, 0.0, 1.0};
	glShadeModel (GL_SMOOTH);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position_0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position_1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);

	GLfloat light1_diffuse[] = {0.2, 0.2, 0.2, 1.0};
	GLfloat light1_specular[] = {0.2, 0.2, 0.2, 1.0};
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
}

void PlayState::createSelectedShapes(GameEngine* lp_game_engine)
{
	this->selected_shapes.clear();
	this->selected_shapes.resize(this->selected_tiles.size());
	std::vector<sf::Vector2i>::const_iterator it;
	unsigned int i = 0;
	for(it = this->selected_tiles.begin(); it != this->selected_tiles.end(); it++)
	{
		sf::Vector2i pos(it->x, it->y);
		std::vector<sf::Vector3f> tile_vertices = this->map.getTileVertices(pos);
		std::vector<sf::Vector2f> sel_vertices(4);
		for(unsigned int k = 0; k < 4; k++)
		{
			sel_vertices.at(k) = dfv::Utils::getVector2d(this->map.getViewPos(tile_vertices[k], lp_game_engine->window));
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

void PlayState::drawSelection(sf::RenderWindow& window) const
{
	std::vector<sf::ConvexShape>::const_iterator it;
	for(it = this->selected_shapes.begin(); it != this->selected_shapes.end(); it++)
	{
		window.draw(*it);
	}
}

sf::Vector2i PlayState::getCameraTile() const
{
	sf::Vector2f camera_pos = this->camera.getPosition2d();
	sf::Vector2i pos(floor(camera_pos.x), floor(camera_pos.y));
	return pos;
}

void PlayState::generateLists()
{
	std::cout << "generating lists" << std::endl;
	this->map.generateTileList(this->camera, this->resources);
	this->map.generateBuildingList();
	this->map.generateRoadList(this->camera, this->resources);
	this->map.generateStructureBoxList(this->camera, this->resources);
}

bool PlayState::test()
{
	if(!Utils::test())
	{
		return false;
	}
	return true;
}

PlayState::PlayState():
		root_component(nullptr),
		frame(0),
		walking(false),
		road_id(0),
		road_orientation(0),
		frame_time(0),
		moving_mode(Free),
		cmd_server(5005)
{
	// TODO Auto-generated constructor stub

}

PlayState::~PlayState()
{
	// TODO Auto-generated destructor stub
}

} /* namespace dfv */
