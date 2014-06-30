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
	this->Initialize();
	this->Run();
}

App::~App()
{
	// TODO Auto-generated destructor stub
}

void App::Initialize()
{
	srand(0);

	this->window.create(sf::VideoMode(1024, 1024 * 9 / 16), "Saganopolis", sf::Style::Default, sf::ContextSettings(32));
	//this->window.create(sf::VideoMode(1024, 1024 * 9 / 16), "Saganopolis");
	//this->window.setFramerateLimit(60);
	this->window.setVerticalSyncEnabled(true);
	//this->window.useVerticalSync(true);
	this->InitOpenGL();

	this->map.LoadFromMapFormat("res/map/world1_test.map");
	Tree* lp_tree = new Tree();
	std::vector<sf::Vector3f> tile_vertices = this->map.GetTileVertices(sf::Vector2i(167, 196));
	lp_tree->Create(tile_vertices);
	this->map.addProp(167, 196, lp_tree);

	for(unsigned int i = 0; i < 50000; i++)
	{
		unsigned int x = rand() % this->map.GetSize();
		unsigned int y = rand() % this->map.GetSize();
		if(!this->map.isWater(x, y) && !this->map.hasBuilding(x, y) && !this->map.isRoad(x, y))
		{
			lp_tree = new Tree();
			std::vector<sf::Vector3f> tile_vertices = this->map.GetTileVertices(sf::Vector2i(x, y));
			lp_tree->Create(tile_vertices);
			this->map.addProp(x, y, lp_tree);
		}
	}

	this->camera.SetPosition(sf::Vector3f(this->map.GetSize() / 2, this->map.GetSize() / 2, 5.f));
	this->camera.SetRpy(sf::Vector3f(-90.0, 0.0, 0.0));
	this->resources.Load();

	//this->minimap.Create(256);
	//this->minimap.GenerateFromMap(&(this->map), this->camera);
	//this->map.SaveAsMapFormat("res/map/world1.map");

	//this->button.SetSize(sf::Vector2i(32, 32));
	//this->button.SetPosition(sf::Vector2i(10, 300));
	//this->button.SetImage(this->resources.img_roads[0]);
	//this->button.SetCommand(std::string("road"));

	this->map.GenerateTileList(this->camera, this->resources);
	this->map.GenerateBuildingList();

}

void App::Run()
{
	while(this->window.isOpen())
	{
		this->HandleInput();
		this->Update();
		this->Draw();
	}
	//this->map.SaveAsMapFormat("res/map/world1.map");
}

void App::Update()
{
	++this->frame;
	/*if(frame % 15 == 0)
	{
		//std::cout << 1.0 / this->window.GetFrameTime() << " FPS" << std::endl;
		//this->minimap.GenerateFromMap(&(this->map), this->camera);
	}*/

	//float height = this->map.GetHeight(sf::Vector2f(this->camera.GetPosition().x, this->camera.GetPosition().y));

	if(camera.GetRpy().z < 0.f)
	{
		this->camera.Rotate(sf::Vector3f(0.f, 0.f, 360.f));
	}
	if(camera.GetRpy().z >= 360.f)
	{
		this->camera.Rotate(sf::Vector3f(0.f, 0.f, -360.f));
	}
	//this->camera.update(this->frame_time, this->map.GetHeight(this->camera.GetPosition2d()));
	sf::Vector2f camera_pos = this->camera.GetPosition2d();
	sf::Vector3f normal = this->map.getNormal(camera_pos.x, camera_pos.y);

	this->camera.update(this->frame_time,
						this->map.GetHeight(sf::Vector2f(this->camera.GetPosition().x, this->camera.GetPosition().y)),
						normal);
	//this->gui.SetFps(1.0 / this->window.getFrameTime());

	this->frame_time = this->clock.restart().asSeconds();
	this->gui.SetFps(1.0 / this->frame_time);
	this->gui.SetQuadrant(this->camera.GetQuadrant());
	this->gui.Update(this->map, this->camera.GetPosition2d());

	// window vertices of selected tile;
	sf::Vector2i tile_pos(floor(this->map_pos.x), floor(this->map_pos.y));

	if(tile_pos.x < 0) tile_pos.x = 0;
	if(tile_pos.x >= (int)this->map.GetSize()) tile_pos.x = this->map.GetSize() - 1;
	if(tile_pos.y < 0) tile_pos.y = 0;
	if(tile_pos.y >= (int)this->map.GetSize()) tile_pos.y = this->map.GetSize() - 1;

	std::vector<sf::Vector3f> tile_vertices = this->map.GetTileVertices(tile_pos);
	std::vector<sf::Vector2f> sel_vertices(4);
	try
	{
		for(unsigned int k = 0; k < 4; k++)
		{
			sel_vertices.at(k) = dfv::Utils::GetVector2d(this->map.GetViewPos(tile_vertices.at(k), this->window));
		}
		/*sel_vertices[1] = dfv::Utils::GetVector2d(this->map.GetViewPos(tile_vertices[1], this->window));
		sel_vertices[2] = dfv::Utils::GetVector2d(this->map.GetViewPos(tile_vertices[2], this->window));
		sel_vertices[3] = dfv::Utils::GetVector2d(this->map.GetViewPos(tile_vertices[3], this->window));
		*/
		this->gui.SetSelectedTileVertices(sel_vertices);
	}
	catch(...)
	{
		std::cout << "Error getting view pos vertices" << std::endl;
	}


	std::vector<sf::ConvexShape> selected_shapes(this->selected_tiles.size());
	std::vector<sf::Vector2u>::iterator it;
	unsigned int i = 0;
	for(it = this->selected_tiles.begin(); it != this->selected_tiles.end(); it++)
	{
		sf::Vector2i pos(it->x, it->y);
		std::vector<sf::Vector3f> tile_vertices = this->map.GetTileVertices(pos);
		std::vector<sf::Vector2f> sel_vertices(4);
		for(unsigned int k = 0; k < 4; k++)
		{
			sel_vertices.at(k) = dfv::Utils::GetVector2d(this->map.GetViewPos(tile_vertices[k], window));
		}
		//sf::ConvexShape shape;
		selected_shapes.at(i).setPointCount(4);
		for(unsigned int k = 0; k < 4; k++)
		{
			selected_shapes.at(i).setPoint(k, sel_vertices.at(k));
		}
		selected_shapes.at(i).setFillColor(sf::Color(255, 0, 0, 64));
		i++;
		//window.draw(shape);
	}

	this->gui.setSelectedShapes(selected_shapes);
	//std::cout << "world pos: " << this->map_pos.x << ", " << this->map_pos.y << ", " << this->map_pos.z << std::endl;
}

void App::HandleInput()
{
	//const sf::Input& input = this->window.GetInput();
	//this->mouse_pos = sf::Vector2i(input.GetMouseX(), input.GetMouseY());
	this->mouse_pos = sf::Vector2i(sf::Mouse::getPosition(this->window));
	sf::Event event;
	while(this->window.pollEvent(event))
	{
		if(event.type == sf::Event::Closed)
		{
			this->window.close();
		}
		/*if(event.type == sf::Event::Resized)
		{
			this->window.create(sf::VideoMode(event.size.width, event.size.height), "Saganopolis");
			//this->window.UseVerticalSync(true);
			this->InitOpenGL();
			this->map.GenerateTileList(this->camera, this->resources);
			this->map.GenerateBuildingList();
		}*/
		else if (event.type == sf::Event::Resized)
		{
			// adjust the viewport when the window is resized
			glViewport(0, 0, event.size.width, event.size.height);
		}
		else if(event.type == sf::Event::KeyPressed)
		{
			if(event.key.code == sf::Keyboard::N)
			{
				this->walking = !this->walking;
			}
			else if(event.key.code == sf::Keyboard::P)
			{
				this->map.SaveAsMapFormat("res/map/world1.map");
			}
			else if(event.key.code == sf::Keyboard::O)
			{
				std::string cmd;
				std::cout << "cmd> ";
				std::getline(std::cin, cmd);
				this->commands.push_back(cmd);
			}
		}
		else if(event.type == sf::Event::MouseWheelMoved)
		{
			float height = this->map.GetHeight(sf::Vector2f(this->camera.GetPosition().x, this->camera.GetPosition().y));
			this->camera.Move(
					sf::Vector3f(
							0.f,
							0.f,
							-0.02f * (float)event.mouseWheel.delta * (this->camera.GetPosition().z - height)));
		}

		/*if(this->mouse_pos.x < (int)(this->minimap.GetSize()) && this->mouse_pos.y < (int)(this->minimap.GetSize()))
		{
			this->minimap.HandleInput(this->camera, event, mouse_pos);
		}*/
	}

	//std::vector<std::string> command_list = this->gui.HandleInput(event, this->commands);
	this->gui.HandleInput(event, this->commands);
	for(unsigned int i = 0; i < this->commands.size(); i++)
	{
		this->ExecuteCommand(this->commands[i]);
	}
	this->commands.clear();

	this->camera.handleInput(event);

}

void App::Draw()
{

	//this->window.PreserveOpenGLStates(false);


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	this->window.setActive();
	this->camera.SetView(this->window);

	this->map.DrawSky();

	//sf::Vector2i position = dfv::Utils::ToVector2i(this->camera.GetPosition2d());
	//dfv::IntRect road_rect = dfv::Utils::CreateRect(position, 50);
	//dfv::Utils::TrimRect(road_rect, this->camera.GetRectFromView(this->map.GetRect()));
	//glDisable(GL_CULL_FACE);

	//glDisable(GL_CULL_FACE);

	this->map.SetLight(sf::Vector3f(400.f, -200.f, 400.f));

	dfv::IntRect view_rect = this->camera.GetRectFromView(this->map.GetRect());
	if(this->camera.GetRpy().x > -120.f)
	{
		//this->map.DrawTiles(view_rect, this->camera, this->resources);
		this->map.CallTileList();
	}
	this->map_pos = this->map.GetMapPosFromMouse(this->mouse_pos);
	//this->map_pos = this->map.GetMapPosFromMouse(this->mouse_pos);

	/*sf::Vector2i tile_pos(floor(this->map_pos.x), floor(this->map_pos.y));
	if(tile_pos.x < 0) tile_pos.x = 0;
	if(tile_pos.x >= (int)this->map.GetSize()) tile_pos.x = this->map.GetSize() - 1;
	if(tile_pos.y < 0) tile_pos.y = 0;
	if(tile_pos.y >= (int)this->map.GetSize()) tile_pos.y = this->map.GetSize() - 1;
	std::vector<sf::Vector3f> tile_vertices = this->map.GetTileVertices(tile_pos);
	std::vector<sf::Vector2f> sel_vertices(4);
	sel_vertices[0] = dfv::Utils::GetVector2d(this->map.GetViewPos(tile_vertices[0], this->window));
	sel_vertices[1] = dfv::Utils::GetVector2d(this->map.GetViewPos(tile_vertices[1], this->window));
	sel_vertices[2] = dfv::Utils::GetVector2d(this->map.GetViewPos(tile_vertices[2], this->window));
	sel_vertices[3] = dfv::Utils::GetVector2d(this->map.GetViewPos(tile_vertices[3], this->window));
	this->gui.SetSelectedTileVertices(sel_vertices);*/

	sf::Vector2i position = dfv::Utils::ToVector2i(this->camera.GetPosition2d());
	dfv::IntRect road_rect = dfv::Utils::CreateRect(position, 50);
	dfv::Utils::TrimRect(road_rect, this->camera.GetRectFromView(this->map.GetRect()));
	this->map.DrawRoads(road_rect, this->camera, this->resources);
	//glDisable(GL_CULL_FACE);
	//this->map.DrawProps(road_rect, this->camera, this->resources);
	//glEnable(GL_CULL_FACE);

	dfv::IntRect outlines_rect = dfv::Utils::CreateRect(
			dfv::Utils::ToVector2i(this->camera.GetPosition2d()),
			30);

	dfv::Utils::TrimRect(outlines_rect, view_rect);


	this->map.CallBuildingList();
	glDisable(GL_CULL_FACE);
	this->map.DrawBuildingOutlines(outlines_rect);

	this->gui.SetMapPos(this->map_pos);
	this->map.DrawBuildingFloors(outlines_rect);


	//glDisable(GL_LIGHTING);
	//glShadeModel (GL_FLAT);
	glDisable(GL_LIGHTING);
	this->map.DrawProps(road_rect, this->camera, this->resources);
	glEnable(GL_LIGHTING);
	//glShadeModel (GL_SMOOTH);
	//glEnable(GL_LIGHTING);

	glEnable(GL_CULL_FACE);
	//this->map.DrawBuildingBoxes(view_rect);



	//std::cout << "road_rect: " << dfv::Utils::ToString(road_rect) << std::endl;


	this->window.pushGLStates();
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//this->drawSelection(this->window);
	this->gui.Draw(this->window, this->camera);

	this->window.popGLStates();
	this->window.display();


}

void App::InitOpenGL()
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
	//glEnable(GL_ALPHA);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLfloat mat_specular[] = { 0.2, 0.2, 0.2, 0.2 };
	GLfloat mat_shininess[] = { 128.0 };
	//GLfloat light_position[] = { 100.0, 200.0, 100.0, 0.0 };
	GLfloat light_position[] = { 400.0, 0.0, 400.0, 0.0 };
	//glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_SMOOTH);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
}

bool App::ExecuteCommand(std::string cmd)
{
	std::vector<std::string> tokens = dfv::Utils::StringTokenize(cmd, " ");

	try
	{
		if(tokens[0] == std::string("save"))
		{
			std::string filename;
			if(tokens.size() == 2)
			{
				filename = tokens[1];
			}
			else
			{
				filename = "res/map/world1_test.map";
			}
			this->map.SaveAsMapFormat(filename);
			std::cout << "Map saved in file " << filename << std::endl;
			return true;
		}
		if(tokens.at(0) == std::string("select"))
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
						this->selected_tiles.push_back(sf::Vector2u(x, y));
					}
				}
				return true;
			}
			else
			{
				unsigned int x, y;
				//x = strtol(tokens.at(1).c_str(), NULL, 10);
				//y = strtol(tokens.at(2).c_str(), NULL, 10);
				x = std::stoi(tokens.at(1));
				y = std::stoi(tokens.at(2));
				this->selected_tiles.clear();
				this->selected_tiles.push_back(sf::Vector2u(x, y));
				std::cout << "Selected tile at " << x << "," << y << std::endl;
				return true;
			}
		}
		else if(tokens.at(0) == std::string("selected"))
		{
			std::vector<sf::Vector2u>::iterator it;
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
				std::vector<sf::Vector2u>::iterator it;
				for(it = this->selected_tiles.begin(); it != this->selected_tiles.end(); it++)
				{
					this->map.clearRoad(it->x, it->y);
				}
				this->map.GenerateTileList(this->camera, this->resources);
				return true;
			}
			if(tokens.at(1) == std::string("building"))
			{
				std::vector<sf::Vector2u>::iterator it;
				for(it = this->selected_tiles.begin(); it != this->selected_tiles.end(); it++)
				{
					this->map.clearBuilding(it->x, it->y);
				}
				this->map.GenerateBuildingList();
				return true;
			}
		}
		else if(tokens.at(0) == std::string("build"))
		{
			if(tokens.at(1) == std::string("road"))
			{
				unsigned int id = std::stoi(tokens.at(2));
				unsigned int orientation = std::stoi(tokens.at(2));
				std::vector<sf::Vector2u>::iterator it;
				for(it = this->selected_tiles.begin(); it != this->selected_tiles.end(); it++)
				{
					this->map.buildRoad(it->x, it->y, id, orientation);
				}
				this->map.GenerateTileList(this->camera, this->resources);
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

	/*if(tokens.size() > 0)
	{
		if(tokens[0] == std::string("build_road"))
		{
			if(tokens.size() >= 3)
			{
				unsigned int posx = strtol(tokens[1].c_str(), NULL, 10);
				unsigned int posy = strtol(tokens[2].c_str(), NULL, 10);
				sf::Vector2i tile_pos(posx, posy);

				if(this->map.IsRoad(tile_pos))
				{
					//return this->map.ChangeRoadType(tile_pos);
					std::cout << "Setting road to id " << this->road_id << " orientation: "
							<< this->road_orientation << std::endl;
					return this->map.SetRoadId(tile_pos, this->road_id) &&
						this->map.SetRoadOrientation(tile_pos, this->road_orientation);
				}
				else if(!this->map.HasBuilding(tile_pos))
				{
					std::cout << "Tile has a building. Cannot build road here." << std::endl;
					return this->map.AddRoad(tile_pos, Road::straight, 0);
				}
			}
		}

		else if(tokens[0] == std::string("rotate_road"))
		{
			if(tokens.size() >= 3)
			{
				unsigned int posx = strtol(tokens[1].c_str(), NULL, 10);
				unsigned int posy = strtol(tokens[2].c_str(), NULL, 10);
				sf::Vector2i tile_pos(posx, posy);

				if(this->map.IsRoad(tile_pos))
				{
					return this->map.ChangeRoadOrientation(tile_pos);
				}
			}
		}

		else if(tokens[0] == std::string("copy_road"))
		{
			if(tokens.size() >= 3)
			{
				unsigned int posx = strtol(tokens[1].c_str(), NULL, 10);
				unsigned int posy = strtol(tokens[2].c_str(), NULL, 10);
				sf::Vector2i tile_pos(posx, posy);

				if(this->map.IsRoad(tile_pos))
				{
					this->road_id = this->map.GetRoadId(tile_pos);
					this->road_orientation = this->map.GetRoadOrientation(tile_pos);
					std::cout << "Copied road at pos " << posx << "," << posy << std::endl;
					return true;
				}
			}
		}
	}
	return false;*/
}

void App::drawSelection(sf::RenderWindow& window) const
{
	std::vector<sf::Vector2u>::const_iterator it;
	for(it = this->selected_tiles.begin(); it != this->selected_tiles.end(); it++)
	{
		sf::Vector2i pos(it->x, it->y);
		std::vector<sf::Vector3f> tile_vertices = this->map.GetTileVertices(pos);
		std::vector<sf::Vector2f> sel_vertices(4);
		for(unsigned int i = 0; i < 4; i++)
		{
			sel_vertices[i] = dfv::Utils::GetVector2d(this->map.GetViewPos(tile_vertices[i], window));
		}
		sf::ConvexShape shape;
		shape.setPointCount(4);
		for(unsigned int i = 0; i < 4; i++)
		{
			shape.setPoint(i, sel_vertices[i]);
		}
		shape.setFillColor(sf::Color(255, 0, 0, 64));
		window.draw(shape);
	}
}

} /* namespace dfv */
