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

	this->map.LoadFromMapFormat("res/map/world1.map");
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
	this->map.SaveAsMapFormat("res/map/world1.map");
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
	this->camera.update(this->frame_time,
						this->map.GetHeight(sf::Vector2f(this->camera.GetPosition().x, this->camera.GetPosition().y)));
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
	sel_vertices[0] = dfv::Utils::GetVector2d(this->map.GetViewPos(tile_vertices[0], this->window));
	sel_vertices[1] = dfv::Utils::GetVector2d(this->map.GetViewPos(tile_vertices[1], this->window));
	sel_vertices[2] = dfv::Utils::GetVector2d(this->map.GetViewPos(tile_vertices[2], this->window));
	sel_vertices[3] = dfv::Utils::GetVector2d(this->map.GetViewPos(tile_vertices[3], this->window));

	this->gui.SetSelectedTileVertices(sel_vertices);
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
		}
		else if(event.type == sf::Event::MouseWheelMoved)
		{
			//float height = this->map.GetHeight((int)this->camera.GetPosition().x, (int)this->camera.GetPosition().y);
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

	std::vector<std::string> command_list = this->gui.HandleInput(event);
	for(unsigned int i = 0; i < command_list.size(); i++)
	{
		this->ExecuteCommand(command_list[i]);
	}

	this->camera.handleInput(event);
	/*
	if(this->moving_mode == Free)
	{
		float map_height = this->map.GetHeight(sf::Vector2f(this->camera.GetPosition().x, this->camera.GetPosition().y));
		float height = this->camera.GetPosition().z - map_height;
		//float vel = this->window.GetFrameTime() * 0.1f * (8*height + 1.0);
		float vel = this->frame_time * 0.1f * (16*height + 16.0);
		float ang = camera.GetRpy().z * 3.1416 / 180.0;
		float angx = camera.GetRpy().x * 3.1416 / 180.0;

		//if(input.IsKeyDown(sf::Key::W))
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			this->camera.Move(sf::Vector3f(vel * sin(ang) * sin(-angx), vel * cos(ang) * sin(-angx), -vel * cos(angx)));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			this->camera.Move(sf::Vector3f(-vel * sin(ang) * sin(-angx), -vel * cos(ang) * sin(-angx), vel * cos(angx)));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			this->camera.Move(sf::Vector3f(vel * cos(ang), -vel * sin(ang), 0.f));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			this->camera.Move(sf::Vector3f(-vel * cos(ang), vel * sin(ang), 0.f));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			this->camera.Move(sf::Vector3f(vel * sin(ang), vel * cos(ang), 0.0));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
		{
			this->camera.Move(sf::Vector3f(-vel * sin(ang), -vel * cos(ang), 0.0));
		}

		float rot = 20.0f * this->frame_time;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			this->camera.Rotate(sf::Vector3f(-rot/2.0, 0.f, 0.f));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			this->camera.Rotate(sf::Vector3f(rot/2.0, 0.f, 0.f));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			this->camera.Rotate(sf::Vector3f(0.f, 0.f, -rot));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			this->camera.Rotate(sf::Vector3f(0.f, 0.f, rot));
		}
	}
	else if(this->moving_mode == Driving)
	{
		this->camera.handleInput(event);
	}

	float map_height = this->map.GetHeight(sf::Vector2f(this->camera.GetPosition().x, this->camera.GetPosition().y));
	float height = this->camera.GetPosition().z - map_height;

	//float height = this->map.GetHeight(sf::Vector2f(this->camera.GetPosition().x, this->camera.GetPosition().y));
	if(this->walking)
	{
		this->camera.SetPosition(sf::Vector3f(this->camera.GetPosition().x, this->camera.GetPosition().y, 0.05f + map_height));// + 0.001f * sin(75.f * this->camera.GetPosition().x) + 0.001f * sin(75.f * this->camera.GetPosition().y)));
	}
	else
	{
		if(height < 0.04f)
		{
			this->camera.Move(sf::Vector3f(0.f, 0.f, 0.04f - height));
		}
	}
	*/

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
	this->map_pos = this->map.GetMapPosFromMouse(this->mouse_pos);
	if(camera.GetQuadrant() == 0) map_pos.x += 0.1;
	else if(camera.GetQuadrant() == 1) map_pos.y += 0.1;
	else if(camera.GetQuadrant() == 2) map_pos.x -= 0.1;
	else if(camera.GetQuadrant() == 3) map_pos.y -= 0.1;
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

	if(tokens.size() > 0)
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
	return false;
}

} /* namespace dfv */
