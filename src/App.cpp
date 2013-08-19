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
		walking(false)
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

	this->window.Create(sf::VideoMode(1024, 1024 * 9 / 16), "Saganopolis");
	this->window.SetFramerateLimit(60);
	this->InitOpenGL();

	//this->map.CreateRandom(400);


	//this->map.LoadHeightMap("res/map/sinheights.hm");
	//this->map.LoadBuildingMap("res/map/sinbuildings.png");
	this->map.LoadFromMapFormat("res/map/world1.map");
	//this->map.CreateFromFile("res/map/asturias_leon.png", 50, 5.f);
	this->camera.SetPosition(sf::Vector3f(this->map.GetSize() / 2, this->map.GetSize() / 2, 5.f));
	this->resources.Load();

	// save the map to a file
	//this->map.SaveHeightMap("res/map/sinheights.hm");
	//this->map.SaveBuildingMap("res/map/sinbuildings.png");
	//this->map.GenerateMapImg(16);
	this->minimap.Create(256);
	this->minimap.GenerateFromMap(&(this->map), this->camera);
	//this->map.SaveAsMapFormat("res/map/world1.map");
	//this->map.LoadFromMapFormat("res/map/world1.map");
}

void App::Run()
{
	while(this->window.IsOpened())
	{
		this->Update();
		this->Draw();
		this->HandleInput();
	}
}

void App::Update()
{
	++this->frame;
	if(frame % 15 == 0)
	{
		//std::cout << 1.0 / this->window.GetFrameTime() << " FPS" << std::endl;
		this->minimap.GenerateFromMap(&(this->map), this->camera);
	}

	float height = this->map.GetHeight(sf::Vector2f(this->camera.GetPosition().x, this->camera.GetPosition().y));

	if(camera.GetRpy().z < 0.f)
	{
		this->camera.Rotate(sf::Vector3f(0.f, 0.f, 360.f));
	}
	if(camera.GetRpy().z >= 360.f)
	{
		this->camera.Rotate(sf::Vector3f(0.f, 0.f, -360.f));
	}

	//std::cout << "world pos: " << this->map_pos.x << ", " << this->map_pos.y << ", " << this->map_pos.z << std::endl;
}

void App::HandleInput()
{
	const sf::Input& input = this->window.GetInput();
	this->mouse_pos = sf::Vector2i(input.GetMouseX(), input.GetMouseY());
	sf::Event event;
	while(this->window.GetEvent(event))
	{
		if(event.Type == sf::Event::Closed)
		{
			this->window.Close();
		}
		if(event.Type == sf::Event::Resized)
		{
			this->window.Create(sf::VideoMode(event.Size.Width, event.Size.Height), "Saganopolis");
			this->InitOpenGL();
		}
		if(event.Type == sf::Event::KeyPressed)
		{
			if(event.Key.Code == sf::Key::N)
			{
				this->walking = !this->walking;
			}
		}
		if(event.Type == sf::Event::MouseWheelMoved)
		{
			//float height = this->map.GetHeight((int)this->camera.GetPosition().x, (int)this->camera.GetPosition().y);
			float height = this->map.GetHeight(sf::Vector2f(this->camera.GetPosition().x, this->camera.GetPosition().y));
			this->camera.Move(
					sf::Vector3f(
							0.f,
							0.f,
							-0.02f * (float)event.MouseWheel.Delta * (this->camera.GetPosition().z - height)));
		}

		if(this->mouse_pos.x < (int)(this->minimap.GetSize()) && this->mouse_pos.y < (int)(this->minimap.GetSize()))
		{
			this->minimap.HandleInput(this->camera, event, mouse_pos);
		}
	}

	float map_height = this->map.GetHeight(sf::Vector2f(this->camera.GetPosition().x, this->camera.GetPosition().y));
	float height = this->camera.GetPosition().z - map_height;
	float vel = this->window.GetFrameTime() * 0.1f * (8*height + 1.0);
	float ang = camera.GetRpy().z * 3.1416 / 180.0;
	float angx = camera.GetRpy().x * 3.1416 / 180.0;
	if(input.IsKeyDown(sf::Key::W))
	{
		this->camera.Move(sf::Vector3f(vel * sin(ang) * sin(-angx), vel * cos(ang) * sin(-angx), -vel * cos(angx)));
	}
	if(input.IsKeyDown(sf::Key::S))
	{
		this->camera.Move(sf::Vector3f(-vel * sin(ang) * sin(-angx), -vel * cos(ang) * sin(-angx), vel * cos(angx)));
	}
	if(input.IsKeyDown(sf::Key::D))
	{
		this->camera.Move(sf::Vector3f(vel * cos(ang), -vel * sin(ang), 0.f));
	}
	if(input.IsKeyDown(sf::Key::A))
	{
		this->camera.Move(sf::Vector3f(-vel * cos(ang), vel * sin(ang), 0.f));
	}
	if(input.IsKeyDown(sf::Key::R))
	{
		this->camera.Move(sf::Vector3f(vel * sin(ang), vel * cos(ang), 0.0));
	}
	if(input.IsKeyDown(sf::Key::F))
	{
		this->camera.Move(sf::Vector3f(-vel * sin(ang), -vel * cos(ang), 0.0));
	}

	float rot = 20.0f * this->window.GetFrameTime();
	if(input.IsKeyDown(sf::Key::Q) || input.IsKeyDown(sf::Key::Up))
	{
		this->camera.Rotate(sf::Vector3f(-rot/2.0, 0.f, 0.f));
	}
	if(input.IsKeyDown(sf::Key::Z) || input.IsKeyDown(sf::Key::Down))
	{
		this->camera.Rotate(sf::Vector3f(rot/2.0, 0.f, 0.f));
	}
	if(input.IsKeyDown(sf::Key::Num1) || input.IsKeyDown(sf::Key::Left))
	{
		this->camera.Rotate(sf::Vector3f(0.f, 0.f, -rot));
	}
	if(input.IsKeyDown(sf::Key::Num3) || input.IsKeyDown(sf::Key::Right))
	{
		this->camera.Rotate(sf::Vector3f(0.f, 0.f, rot));
	}

	map_height = this->map.GetHeight(sf::Vector2f(this->camera.GetPosition().x, this->camera.GetPosition().y));
	height = this->camera.GetPosition().z - map_height;

	std::cout << "map_height: " << map_height << std::endl;
	std::cout << "height: " << height << std::endl;
	std::cout << "---" << std::endl;

	//float height = this->map.GetHeight(sf::Vector2f(this->camera.GetPosition().x, this->camera.GetPosition().y));
	if(this->walking)
	{
		this->camera.SetPosition(sf::Vector3f(this->camera.GetPosition().x, this->camera.GetPosition().y, 0.04f + map_height));
	}
	else
	{
		if(height < 0.04f)
		{
			this->camera.Move(sf::Vector3f(0.f, 0.f, 0.04f - height));
		}
	}

}

void App::Draw()
{
	this->window.PreserveOpenGLStates(false);
	this->window.SetActive();
	//gluPerspective(55.f, (float)this->window.GetWidth() / (float)this->window.GetHeight(), 0.01f, 2000.f);
	glViewport(0, 0, this->window.GetWidth(), this->window.GetHeight());

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	this->map.Draw(this->window, this->camera, this->resources);
	this->map_pos = this->map.GetMapPosFromMouse(this->mouse_pos);

	const unsigned int quadrant = (int)this->camera.GetQuadrant();
	float pos_x = this->map_pos.x;
	if(quadrant == 0) pos_x += 0.03f;
	if(quadrant == 1) pos_x += 0.03f;
	if(quadrant == 2 && pos_x < this->window.GetWidth() / 2) pos_x -= 0.03f;
	if(quadrant == 2 && pos_x >= this->window.GetWidth() / 2) pos_x += 0.03f;
	if(quadrant == 3 && pos_x < this->window.GetWidth() / 2) pos_x -= 0.03f;
	if(quadrant == 3 && pos_x >= this->window.GetWidth() / 2) pos_x -= 0.03f;
	float pos_y = this->map_pos.y;
	if(quadrant == 0) pos_y += 0.03f;
	if(quadrant == 1) pos_y += 0.03f;
	if(quadrant == 2) pos_y -= 0.03f;
	if(quadrant == 3) pos_y -= 0.03f;
	pos_x = pos_x >= (int)this->map.GetSize()? (int)this->map.GetSize() - 1: pos_x;
	pos_x = pos_x < 0 ? 0 : pos_x;
	pos_y = pos_y >= (int)this->map.GetSize()? (int)this->map.GetSize() - 1: pos_y;
	pos_y = pos_y < 0 ? 0 : pos_y;
	std::vector<sf::Vector3f> tile_vertices = this->map.GetTileVertices(sf::Vector2i(floor(pos_x), floor(pos_y)));
	std::vector<sf::Vector3f> view_vertices;
	view_vertices.resize(4);
	view_vertices[0] = this->map.GetViewPos(tile_vertices[0], this->window);
	view_vertices[1] = this->map.GetViewPos(tile_vertices[1], this->window);
	view_vertices[2] = this->map.GetViewPos(tile_vertices[2], this->window);
	view_vertices[3] = this->map.GetViewPos(tile_vertices[3], this->window);

	this->window.PreserveOpenGLStates(true);
	this->minimap.Draw(this->window, this->camera);

	sf::String str;
	std::stringstream ss;
	ss << "FPS: " << 1.0 / this->window.GetFrameTime();
	str.SetText(ss.str());
	str.SetPosition(270, 0);
	str.SetSize(12);
	this->window.Draw(str);

	ss.str(std::string(""));
	ss << "Map pos: " << this->map_pos.x << ", " << this->map_pos.y << ", " << this->map_pos.z;
	str.SetText(ss.str());
	str.SetPosition(270, 15);
	this->window.Draw(str);

	ss.str(std::string(""));
	ss << "Window size: " << this->window.GetWidth() << " x " << this->window.GetHeight();
	str.SetText(ss.str());
	str.SetPosition(270, 30);
	this->window.Draw(str);

	ss.str(std::string(""));
	ss << "Quadrant: " << this->camera.GetQuadrant();
	str.SetText(ss.str());
	str.SetPosition(270, 45);
	this->window.Draw(str);


	if(!this->walking)
	{
		sf::Shape l = sf::Shape::Line(view_vertices[0].x, view_vertices[0].y, view_vertices[1].x, view_vertices[1].y, 2.0, sf::Color::Red);
		this->window.Draw(l);
		l = sf::Shape::Line(view_vertices[1].x, view_vertices[1].y, view_vertices[2].x, view_vertices[2].y, 2.0, sf::Color::Red);
		this->window.Draw(l);
		l = sf::Shape::Line(view_vertices[2].x, view_vertices[2].y, view_vertices[3].x, view_vertices[3].y, 2.0, sf::Color::Red);
		this->window.Draw(l);
		l = sf::Shape::Line(view_vertices[3].x, view_vertices[3].y, view_vertices[0].x, view_vertices[0].y, 2.0, sf::Color::Red);
		this->window.Draw(l);
	}



	this->window.Display();
}

void App::InitOpenGL()
{
	glClearDepth(1.0f);
	glClearColor(0.5f, 0.6f, 0.95f, 0.f);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(55.f, (float)this->window.GetWidth() / (float)this->window.GetHeight(), 0.01f, 2500.f);

	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_BLEND);

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
}

} /* namespace dfv */
