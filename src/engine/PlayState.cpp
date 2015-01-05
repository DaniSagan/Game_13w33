/*
 * PlayState.cpp
 *
 *  Created on: Aug 30, 2014
 *      Author: daniel
 */

#include "PlayState.h"
#include "StartMenuState.h"

namespace dfv
{

PlayState PlayState::play_state;

void PlayState::init(GameEngine* lp_game_engine)
{
	assert(this->test());
	srand(time(NULL));
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

	// Size of the map obtained from the start screen
	//unsigned int çmapSize = std::stoi(static_cast<Text*>(StartMenuState::getInstance()->gui.getById(StartMenuState::SIZE_EDIT))->text);

	// Execute folder select dialog
	string filePath = Utils::exec("python script/filemanager.py f");
	string cityName = filePath.substr(filePath.find_last_of("/"), filePath.size());
	cout << cityName << endl;

	// Path to the .cfg file
	string fileName = filePath + "/" + cityName + ".cfg";
	cout << "File name: " << fileName << endl;
	SimpleParser parser;
	parser.parse(fileName);

	this->map.heightMap.minHeight = stof(parser.get("minheight"));
	this->map.heightMap.maxHeight = stof(parser.get("maxheight"));
	this->map.loadHeightMap(filePath + "/" + parser.get("heightmap"), 2);

	// create roads
	cout << "Creating roads" << endl;
	for(unsigned int i = 0; i < this->map.getSize(); i++)
	{
		for(unsigned int j = 0; j < this->map.getSize(); j++)
		{
			Tile& tile = this->map.getTile(i, j);
			if(tile.canBuildRoad())
			{
				if(((i%6 == 0) || (i%30 == 1)) && !((j%6==0) || (j%30==1)))
				{
					tile.addRoad(Road::straight, 0);
				}
				else if(!((i%6 == 0) || (i%30 == 1)) && ((j%6==0) || (j%30==1)))
				{
					tile.addRoad(Road::straight, 1);
				}
				else if(((i%6 == 0) || (i%30 == 1)) && ((j%6==0) || (j%30==1)))
				{
					tile.addRoad(Road::cross, 0);
				}
			}
		}
	}

	default_random_engine generator;

	// Add random rondabouts
	cout << "Adding roundabouts" << endl;
	for(size_t k = 0; k < 100000; k++)
	{
		uniform_int_distribution<int> distribution(1, this->map.getSize()-2);
		size_t x = distribution(generator);
		size_t y = distribution(generator);
		cout << "Trying to add roundabout @" << x << "," << y << endl;
		//size_t x = rand() % this->map.getSize();
		//size_t y = rand() % this->map.getSize();
		Tile& tile = this->map.getTile(x, y);
		// make sure it's a cross
		if(tile.hasRoad())
		{
			if(this->map.getTile(x, y).getRoad()->getId() == Road::cross)
			{
				if(this->map.getTile(x, y).canBuildRoad() &&
				   this->map.getTile(x+1, y).canBuildRoad() &&
				   this->map.getTile(x+1, y+1).canBuildRoad() &&
				   this->map.getTile(x, y+1).canBuildRoad() &&
				   this->map.getTile(x-1, y+1).canBuildRoad() &&
				   this->map.getTile(x-1, y).canBuildRoad() &&
				   this->map.getTile(x-1, y-1).canBuildRoad() &&
				   this->map.getTile(x, y-1).canBuildRoad() &&
				   this->map.getTile(x+1, y-1).canBuildRoad() &&
				   !this->map.getTile(x+1, y+1).hasRoad() &&
				   !this->map.getTile(x-1, y+1).hasRoad() &&
				   !this->map.getTile(x-1, y-1).hasRoad() &&
				   !this->map.getTile(x+1, y-1).hasRoad())
				{
					cout << "Added roundabout @" << x << "," << y << endl;
					this->map.getTile(x, y).addRoad(Road::roundabout_center, 0);
					this->map.getTile(x+1, y).addRoad(Road::roundabout_exit, 1);
					this->map.getTile(x+1, y+1).addRoad(Road::roundabout_corner, 3);
					this->map.getTile(x, y+1).addRoad(Road::roundabout_exit, 0);
					this->map.getTile(x-1, y+1).addRoad(Road::roundabout_corner, 2);
					this->map.getTile(x-1, y).addRoad(Road::roundabout_exit, 3);
					this->map.getTile(x-1, y-1).addRoad(Road::roundabout_corner, 1);
					this->map.getTile(x, y-1).addRoad(Road::roundabout_exit, 2);
					this->map.getTile(x+1, y-1).addRoad(Road::roundabout_corner, 0);
				}
			}
		}
	}

	// Fix road connections
	cout << "Fixing road connections" << endl;
	for(size_t x = 1; x < this->map.getSize()-1; x++)
	{
		for(size_t y = 1; y < this->map.getSize()-1; y++)
		{
			// x-crosses to t-crosses
			sf::Vector2i pos(x, y);
			if(this->map.getTile(pos).hasRoad())
			{
				if(this->map.getTile(pos).getRoad()->getId() == Road::cross)
				{
					vector<string> pattern = this->map.getRoadPattern(sf::Vector2i(x, y), 1);
					vector<string> matchPattern;
					matchPattern = {" | ",
							        "-+-",
							        "   "};
					if(matchPattern == pattern)
					{
						cout << "Fixing cross" << endl;
						//this->map.setRoadId(pos, Road::tcross);
						//this->map.setRoadOrientation(pos, 0);
						this->map.getTile(pos).getRoad()->setType(Road::tcross);
						this->map.getTile(pos).getRoad()->setOrientation(0);
						continue;
					}
					matchPattern = {" | ",
							        " +-",
							        " | "};
					if(matchPattern == pattern)
					{
						cout << "Fixing cross" << endl;
						//this->map.setRoadId(pos, Road::tcross);
						//this->map.setRoadOrientation(pos, 1);
						this->map.getTile(pos).getRoad()->setType(Road::tcross);
						this->map.getTile(pos).getRoad()->setOrientation(1);
						continue;
					}
					matchPattern = {"   ",
							        "-+-",
							        " | "};
					if(matchPattern == pattern)
					{
						cout << "Fixing cross" << endl;
						//this->map.setRoadId(pos, Road::tcross);
						//this->map.setRoadOrientation(pos, 2);
						this->map.getTile(pos).getRoad()->setType(Road::tcross);
						this->map.getTile(pos).getRoad()->setOrientation(2);
						continue;
					}
					matchPattern = {" | ",
							        "-+ ",
							        " | "};
					if(matchPattern == pattern)
					{
						cout << "Fixing cross" << endl;
						//this->map.setRoadId(pos, Road::tcross);
						//this->map.setRoadOrientation(pos, 3);
						this->map.getTile(pos).getRoad()->setType(Road::tcross);
						this->map.getTile(pos).getRoad()->setOrientation(3);
						continue;
					}
					matchPattern = {" | ",
							        " +-",
							        "   "};
					if(matchPattern == pattern)
					{
						cout << "Fixing cross" << endl;
						//this->map.setRoadId(pos, Road::curve);
						//this->map.setRoadOrientation(pos, 0);
						this->map.getTile(pos).getRoad()->setType(Road::curve);
						this->map.getTile(pos).getRoad()->setOrientation(0);
						continue;
					}
					matchPattern = {"   ",
							        " +-",
							        " | "};
					if(matchPattern == pattern)
					{
						cout << "Fixing cross" << endl;
						//this->map.setRoadId(pos, Road::curve);
						//this->map.setRoadOrientation(pos, 1);
						this->map.getTile(pos).getRoad()->setType(Road::curve);
						this->map.getTile(pos).getRoad()->setOrientation(1);
						continue;
					}
					matchPattern = {"   ",
							        "-+ ",
							        " | "};
					if(matchPattern == pattern)
					{
						cout << "Fixing cross" << endl;
						//this->map.setRoadId(pos, Road::curve);
						//this->map.setRoadOrientation(pos, 2);
						this->map.getTile(pos).getRoad()->setType(Road::curve);
						this->map.getTile(pos).getRoad()->setOrientation(2);
						continue;
					}
					matchPattern = {" | ",
							        "-+ ",
							        "   "};
					if(matchPattern == pattern)
					{
						cout << "Fixing cross" << endl;
						//this->map.setRoadId(pos, Road::curve);
						//this->map.setRoadOrientation(pos, 3);
						this->map.getTile(pos).getRoad()->setType(Road::curve);
						this->map.getTile(pos).getRoad()->setOrientation(3);
						continue;
					}

				}
			}
		}
	}

	// generate random trees
	cout << "Creating trees" << endl;
	Tree* lp_tree = new Tree();
	for(unsigned int i = 0; i < pow(this->map.getSize(), 2)/5; i++)
	{
		uniform_int_distribution<int> distribution(0, this->map.getSize()-1);
		size_t x = distribution(generator);
		size_t y = distribution(generator);
		//unsigned int x = rand() % this->map.getSize();
		//unsigned int y = rand() % this->map.getSize();
		Tile& tile = this->map.getTile(x, y);
		if(!tile.isWater() &&
		   !tile.isBeach() &&
		   //!this->map.hasBuilding(x, y) &&
		   this->map.getAvgHeight(x, y) < 18.f &&
		   !tile.hasRoad())
		{
			lp_tree = new Tree();
			//std::vector<sf::Vector3f> tile_vertices = this->map.getTileVertices(sf::Vector2i(x, y));
			vector<sf::Vector3f> tile_vertices = this->map.getTile(x, y).getVertices();//this->map.getTileVertices(sf::Vector2i(x, y));
			lp_tree->create(tile_vertices);
			//this->map.addProp(x, y, lp_tree);
			tile.addProp(lp_tree);
		}
	}

	// generate lots
	cout << "Creating structures" << endl;
	unsigned int buildings = 0;
	unsigned int floors = 0;
	unsigned int homes = 0;
	unsigned int population = 0;

	// Position of the city center (CBD)
	sf::Vector2i center(stof(parser.get("centerx")), stof(parser.get("centery")));
	for(unsigned int i = 0; i < 5000000; i++)
	{
		unsigned int xmin = rand() % this->map.getSize();
		unsigned int ymin = rand() % this->map.getSize();
		float distToCenter = sqrt(static_cast<float>(pow(static_cast<int>(xmin)-center.x, 2) + pow(static_cast<int>(ymin)-center.y, 2)));
		size_t size_x, size_y;
		if(distToCenter < 2.f * stof(parser.get("distrib")))
		{
			size_x = 1 + floor(5.f * Utils::rFunction(Utils::floatRandom(0.f, 1.f), 2.f) + 0.5f);
			size_y = 1 + floor(5.f * Utils::rFunction(Utils::floatRandom(0.f, 1.f), 2.f) + 0.5f);
		}
		else if(distToCenter < 3.f * stof(parser.get("distrib")))
		{
			size_x = 1 + floor(3.f * Utils::rFunction(Utils::floatRandom(0.f, 1.f), 2.f) + 0.5f);
			size_y = 1 + floor(3.f * Utils::rFunction(Utils::floatRandom(0.f, 1.f), 2.f) + 0.5f);
		}
		else
		{
			size_x = 1 + floor(1.f * Utils::rFunction(Utils::floatRandom(0.f, 1.f), 2.f) + 0.5f);
			size_y = 1 + floor(1.f * Utils::rFunction(Utils::floatRandom(0.f, 1.f), 2.f) + 0.5f);
		}


		// If a lot could be added to the map
		if(this->map.addLot(xmin, ymin, xmin + (size_x-1), ymin + (size_y-1)))
		{
			Model model;
			Lot* lp_lot = this->map.getLot(xmin, ymin);
			Quad base_quad;
			std::vector<sf::Vector3f> base_vertices;
			if(distToCenter > 2.f*stof(parser.get("distrib")))
			{
				base_vertices = {sf::Vector3f(Utils::floatRandom(0.f, 0.4*size_x), Utils::floatRandom(0.f, 0.4*size_y), 0.0),
								 sf::Vector3f(Utils::floatRandom(0.6*size_x, size_x), Utils::floatRandom(0.f, 0.4*size_y), 0.0),
								 sf::Vector3f(Utils::floatRandom(0.6*size_x, size_x), Utils::floatRandom(0.6*size_y, size_y), 0.0),
								 sf::Vector3f(Utils::floatRandom(0.f, 0.4*size_x), Utils::floatRandom(0.6*size_y, size_y), 0.0)};
			}
			else
			{
				if(rand() % 2 == 0)
				{
						base_vertices = {sf::Vector3f(0.f, 0.f, 0.0),
									     sf::Vector3f(size_x, 0.f, 0.0),
									     sf::Vector3f(size_x, size_y, 0.0),
									     sf::Vector3f(0.f, size_y, 0.0)};
				}
				else
				{
					base_vertices = {sf::Vector3f(Utils::floatRandom(0.f, 0.4*size_x), Utils::floatRandom(0.f, 0.4*size_y), 0.0),
									 sf::Vector3f(Utils::floatRandom(0.6*size_x, size_x), Utils::floatRandom(0.f, 0.4*size_y), 0.0),
									 sf::Vector3f(Utils::floatRandom(0.6*size_x, size_x), Utils::floatRandom(0.6*size_y, size_y), 0.0),
									 sf::Vector3f(Utils::floatRandom(0.f, 0.4*size_x), Utils::floatRandom(0.6*size_y, size_y), 0.0)};
				}
			}
			base_quad.create(base_vertices);

			float kCenter = exp(-pow(distToCenter/stof(parser.get("distrib")), 2.f));
			unsigned int floor_count = floor(25.f* kCenter * float(size_x*size_y) * Utils::rFunction(Utils::floatRandom(0.f, 1.f), 1));
			if(rand() % 10 == 0)
			{
				floor_count++;
			}
			model.create(lp_lot->getMinHeight(), lp_lot->getMaxHeight(), lp_lot->getOrigin2d(), base_quad, floor_count);

			Structure* lp_structure = new Structure();
			lp_structure->setModel(model);
			lp_lot->addStructure(lp_structure);

			buildings++;
			floors += floor_count;
			unsigned int home_count = (floor_count+1) * size_x * size_y;
			homes += home_count;
			unsigned int inhabitant_count = static_cast<int>(float(home_count) * 2.61 * Utils::floatRandom(0.4, 1.6));
			population += inhabitant_count;
			lp_lot->setInhabitants(inhabitant_count);
		}
	}

	std::cout << "Buildings: " << buildings << std::endl;
	std::cout << "Floors: " << floors << std::endl;
	std::cout << "Homes: " << homes << std::endl;
	std::cout << "Population: " << population << std::endl;

	cameraInstance.setPosition(sf::Vector3f(this->map.getSize() / 2, this->map.getSize() / 2, 5.f));
	cameraInstance.setRpy(sf::Vector3f(-90.0, 0.0, 0.0));
	this->resources.load();

	this->generateLists();

	// GUI elements
	Text* lp_stats_text = new Text(&this->gui_root, STATS_TEXT_BAR);
	std::stringstream ss;
	ss.imbue(std::locale(""));
	ss << parser.get("name") + " ---- Population: " << population << " ---- Buildings: " << buildings;
	lp_stats_text->text = ss.str();
	lp_stats_text->setPosition(sf::Vector2f(0.f, 0.f));
	lp_stats_text->txt_color = sf::Color::White;
	lp_stats_text->txt_size = 18.f;
	lp_stats_text->bg_color = sf::Color(0, 0, 0, 128);
	lp_stats_text->size = sf::Vector2f(lp_game_engine->window.getSize().x, 25.f);

	Panel* lp_info_panel = new Panel(&this->gui_root, INFO_PANEL);
	lp_info_panel->size = {125.f, 75.f};
	lp_info_panel->color = sf::Color(32, 32, 32, 192);

	Multitext* lp_info_text = new Multitext(lp_info_panel, INFO_TEXT);
	lp_info_text->setPosition(sf::Vector2f(0.f, 0.f));
	lp_info_text->lines = std::vector<std::string>{"Building", "height: XXX m", "#floors: XX", "#inhabitants: XXX"};
	lp_info_text->txt_color = sf::Color::White;
	lp_info_text->txt_size = 10.f;
	lp_info_text->bg_color = sf::Color(0, 0, 0, 0);
	lp_info_text->size = lp_info_panel->size;
	lp_info_text->interline_space = 5.f;

	MenuButton* lpButtonMenu = new MenuButton(&this->gui_root, BUTTON_MENU);
	lpButtonMenu->loadTexture("res/gui/button_menu.png");
	lpButtonMenu->setPosition(sf::Vector2f(lp_game_engine->window.getSize().x - 32, 32+16));

	MenuButton* lpButtonCameraFree = new MenuButton(&this->gui_root, BUTTON_CAMERA_FREE);
	lpButtonCameraFree->loadTexture("res/gui/button_camera_free.png");
	lpButtonCameraFree->setPosition(sf::Vector2f(lp_game_engine->window.getSize().x - 32, 32+16+36*1));

	MenuButton* lpButtonCameraWalking = new MenuButton(&this->gui_root, BUTTON_CAMERA_WALKING);
	lpButtonCameraWalking->loadTexture("res/gui/button_camera_walking.png");
	lpButtonCameraWalking->setPosition(sf::Vector2f(lp_game_engine->window.getSize().x - 32, 32+16+36*2));

	MenuButton* lpButtonCameraDriving = new MenuButton(&this->gui_root, BUTTON_CAMERA_DRIVING);
	lpButtonCameraDriving->loadTexture("res/gui/button_camera_driving.png");
	lpButtonCameraDriving->setPosition(sf::Vector2f(lp_game_engine->window.getSize().x - 32, 32+16+36*3));
}

void PlayState::cleanup()
{
	this->map.clear();
	this->map.deleteLists();
	this->gui_root.clear();
	this->cmd_server.terminate();
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
	sf::Vector2f mouse_pos(this->mouse_pos.x, this->mouse_pos.y);
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
		cameraInstance.handleInput(event);
		const GuiEvent guiEvent = this->gui_root.handleInput(event);
		if(guiEvent.type != GuiEvent::None)
		{
			if(guiEvent.type == GuiEvent::ButtonEvent)
			{
				if(guiEvent.click.id == BUTTON_MENU)
				{
					lp_game_engine->changeState(StartMenuState::getInstance());
					return;
				}
				else if(guiEvent.click.id == BUTTON_CAMERA_FREE)
				{
					cameraInstance.setMode(Camera::Free);
					return;
				}
				else if(guiEvent.click.id == BUTTON_CAMERA_WALKING)
				{
					cameraInstance.setMode(Camera::Walking);
					return;
				}
				else if(guiEvent.click.id == BUTTON_CAMERA_DRIVING)
				{
					cameraInstance.setMode(Camera::Driving);
					return;
				}
			}
			return;
		}
		//this->executeCmd(cmd, lp_game_engine);
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
				//this->map.saveAsMapFormat("res/map/world1.map");
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
			float height = this->map.getHeight(sf::Vector2f(cameraInstance.getPosition().x, cameraInstance.getPosition().y));
			cameraInstance.move(sf::Vector3f(0.f,
										   0.f,
										   -0.02f * (float)event.mouseWheel.delta * (cameraInstance.getPosition().z - height)));
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
		else if(event.type == sf::Event::MouseMoved)
		{
			sf::Vector2f panel_size = static_cast<Panel*>(this->gui_root.getById(INFO_PANEL))->size;
			sf::Vector2i map_pos(this->map_pos.x, this->map_pos.y);
		}
	}
}

void PlayState::update(GameEngine* lp_game_engine)
{
	++this->frame;
	this->frame_time = this->clock.restart().asSeconds();

	sf::Vector2f camera_pos = cameraInstance.getPosition2d();
	sf::Vector3f normal = this->map.getNormal(camera_pos.x, camera_pos.y);
	cameraInstance.update(this->frame_time,
						this->map.getHeight(sf::Vector2f(cameraInstance.getPosition().x, cameraInstance.getPosition().y)),
						normal);

	// update gui data
	this->gui.setFps(1.0 / this->frame_time);
	this->gui.setQuadrant(cameraInstance.getQuadrant());
	this->gui.update(this->map, cameraInstance.getPosition2d());

	// window vertices of selected tile;
	sf::Vector2i tile_pos(floor(this->map_pos.x), floor(this->map_pos.y));
	if(tile_pos.x < 0) tile_pos.x = 0;
	if(tile_pos.x >= (int)this->map.getSize()) tile_pos.x = this->map.getSize() - 1;
	if(tile_pos.y < 0) tile_pos.y = 0;
	if(tile_pos.y >= (int)this->map.getSize()) tile_pos.y = this->map.getSize() - 1;

	vector<sf::Vector3f> tile_vertices = this->map.getTile(tile_pos).getVertices();//this->map.getTileVertices(tile_pos);
	vector<sf::Vector2f> sel_vertices(4);
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


	//if(this->map.hasStructure(map_pos.x, map_pos.y))

	if(this->map.contains(this->map_pos.x, this->map_pos.y))
	{
		Tile& tile = this->map.getTile(this->map_pos.x, this->map_pos.y);
		if(tile.hasLot() && tile.getLot()->hasStructure())
		//if(this->map.getTile(this->map_pos.x, this->map_pos.y).hasStructure())
		{
			Panel* info_panel = static_cast<Panel*>(this->gui_root.getById(INFO_PANEL));
			info_panel->visible = true;
			const float structure_height = this->map.getLot(map_pos.x, map_pos.y)->getStructureHeight();
			const unsigned int structure_floors = this->map.getLot(map_pos.x, map_pos.y)->getStructureFloorCount();
			const unsigned int inhabitants = this->map.getLot(map_pos.x, map_pos.y)->getInhabitants();
			std::stringstream ss;
			ss << "Height: " << static_cast<int>(structure_height * 16.f) << " m";
			static_cast<Multitext*>(this->gui_root.getById(INFO_TEXT))->lines.at(1) = ss.str();
			ss.str("");
			ss << "#floors: " << structure_floors;
			static_cast<Multitext*>(this->gui_root.getById(INFO_TEXT))->lines.at(2) = ss.str();
			ss.str("");
			ss << "#inhabitants: " << inhabitants;
			static_cast<Multitext*>(this->gui_root.getById(INFO_TEXT))->lines.at(3) = ss.str();
			sf::Vector2f info_panel_pos(sf::Mouse::getPosition(lp_game_engine->window).x + 20.f,
					sf::Mouse::getPosition(lp_game_engine->window).y - 20.f - info_panel->size.y);
			info_panel->setPosition(info_panel_pos);
		}
		else
		{
			static_cast<Panel*>(this->gui_root.getById(INFO_PANEL))->visible = false;
		}
	}

}

void PlayState::draw(GameEngine* lp_game_engine)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	lp_game_engine->window.setActive();
	cameraInstance.setView(lp_game_engine->window);

	glDisable(GL_FOG);
	this->map.drawSky();
	glEnable(GL_FOG);
	this->map.setLight(sf::Vector3f(800.f, -200.f, 800.f));

	dfv::RealIntRect view_rect = cameraInstance.getRectFromView(this->map.getTileRect());
	this->map.callTileList();
	this->map_pos = this->map.getMapPosFromMouse(this->mouse_pos);
	this->createSelectedShapes(lp_game_engine);

	this->gui.setMapPos(this->map_pos);
	this->map.callStructureBoxList();

	// TODO set this to camera height meassured from ground
	if(cameraInstance.getPosition().z < 50.f)
	{
		dfv::RealIntRect road_rect;
		road_rect.setFromCenterRadius(dfv::Utils::toVector2i(cameraInstance.getPosition2d()), 50);
		road_rect.trim(cameraInstance.getRectFromView(this->map.getTileRect()));

		this->map.drawRoads(road_rect, cameraInstance, this->resources);

		dfv::RealIntRect outlines_rect;
		outlines_rect.setFromCenterRadius(dfv::Utils::toVector2i(cameraInstance.getPosition2d()), 30);
		outlines_rect.trim(cameraInstance.getRectFromView(this->map.getTileRect()));

		glDisable(GL_CULL_FACE);
		this->map.drawStructureOutlines(outlines_rect);

		glDisable(GL_LIGHTING);
		this->map.drawProps(road_rect, cameraInstance, this->resources);
		glEnable(GL_LIGHTING);
	}

	glEnable(GL_CULL_FACE);

	lp_game_engine->window.pushGLStates();

	this->drawSelection(lp_game_engine->window);
	this->gui.draw(lp_game_engine->window, cameraInstance);
	//this->gui_root.draw(lp_game_engine->window, lp_game_engine->assets);
	lp_game_engine->window.draw(this->gui_root);

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
			//this->map.saveAsMapFormat(filename);
			std::cout << "Map saving not implemented " << std::endl;
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
					//this->map.clearRoad(it->x, it->y);
					this->map.getTile(*it).clearRoad();
				}
				this->map.generateTileList(cameraInstance, this->resources);
				return true;
			}
			/*else if(tokens.at(1) == std::string("building"))
			{
				std::vector<sf::Vector2i>::iterator it;
				for(it = this->selected_tiles.begin(); it != this->selected_tiles.end(); it++)
				{
					this->map.clearBuilding(it->x, it->y);
				}
				this->map.generateBuildingList();
				return true;
			}*/
			else if(tokens.at(1) == std::string("prop"))
			{
				std::vector<sf::Vector2i>::iterator it;
				for(it = this->selected_tiles.begin(); it != this->selected_tiles.end(); it++)
				{
					//this->map.clearProp(it->x, it->y);
					this->map.getTile(*it).clearProp();
				}
				//this->map.generateBuildingList();
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
					//this->map.buildRoad(it->x, it->y, id, orientation);
					Road::Type type;
					switch(id)
					{
					case 0: 	type = Road::straight; 			break;
					case 1: 	type = Road::cross; 			break;
					case 2: 	type = Road::tcross; 			break;
					case 3: 	type = Road::curve; 			break;
					case 4: 	type = Road::av_straight; 		break;
					case 5: 	type = Road::av_cross; 			break;
					case 6: 	type = Road::av_tcross; 		break;
					case 7: 	type = Road::roundabout_center; break;
					case 8: 	type = Road::roundabout_side; 	break;
					case 9: 	type = Road::roundabout_corner; break;
					case 10:	type = Road::roundabout_exit; 	break;
					}
					this->map.getTile(*it).addRoad(type, orientation);
				}
				this->map.generateTileList(cameraInstance, this->resources);
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
	//glClearColor(47.f/255.f, 77.f/255.f, 127.f/255.f, 0.f);
	//glClearColor(0.35f, 0.45f, 0.725f, 0.f);
	//glClearColor(0.f, 0.f, 0.f, 0.f);
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

	// fog
	GLfloat fog_start = 20.f;
	GLfloat fog_density = 0.002f;
	GLfloat fog_color[] = {0.6f, 0.6f, 0.6f, 1.f};
	glFogfv(GL_FOG_START, &fog_start);
	glFogfv(GL_FOG_DENSITY, &fog_density);
	glFogfv(GL_FOG_COLOR, fog_color);
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
		if(!this->map.contains(pos)) continue;
		//std::vector<sf::Vector3f> tile_vertices = this->map.getTileVertices(pos);
		std::vector<sf::Vector3f> tile_vertices = this->map.getTile(pos).getVertices();
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
	//sf::Vector2f camera_pos = this->camera.getPosition2d();
	sf::Vector2f camera_pos = cameraInstance.getPosition2d();
	sf::Vector2i pos(floor(camera_pos.x), floor(camera_pos.y));
	return pos;
}

void PlayState::generateLists()
{
	std::cout << "generating tile list" << std::endl;
	this->map.generateTileList(cameraInstance, this->resources);
	std::cout << "generating road list" << std::endl;
	this->map.generateRoadList(cameraInstance, this->resources);
	std::cout << "generating structure's boxes list" << std::endl;
	this->map.generateStructureBoxList(cameraInstance, this->resources);
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
		cmd_server(5005),
		gui_root(nullptr)
{
	// TODO Auto-generated constructor stub

}

PlayState::~PlayState()
{
	// TODO Auto-generated destructor stub
}

} /* namespace dfv */
