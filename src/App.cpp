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
		frame(0)
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

	glClearDepth(1.0f);
	glClearColor(0.5f, 0.6f, 0.95f, 0.f);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(55.f, (float)this->window.GetWidth() / (float)this->window.GetHeight(), 0.01f, 2000.f);

	glEnable( GL_LIGHTING );
	glEnable(GL_COLOR_MATERIAL);

	GLfloat mat_specular[] = { 0.2, 0.2, 0.2, 0.2 };
	GLfloat mat_shininess[] = { 128.0 };
	GLfloat light_position[] = { 100.0, 200.0, 100.0, 0.0 };
	//glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_SMOOTH);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_TEXTURE_2D);

	this->map.CreateRandom(400);
	this->map.LoadHeightMap("res/map/sinheights.hm");
	this->map.LoadBuildingMap("res/map/sinbuildings.png");
	//this->map.CreateFromFile("res/map/asturias_leon.png", 50, 5.f);
	this->camera.SetPosition(sf::Vector3f(this->map.GetSize() / 2, this->map.GetSize() / 2, 5.f));
	this->resources.Load();

	// save the map to a file
	//this->map.SaveHeightMap("res/map/sinheights.hm");
	//this->map.SaveBuildingMap("res/map/sinbuildings.png");
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
	if(frame % 60 == 0)
	{
		std::cout << 1.0 / this->window.GetFrameTime() << " FPS" << std::endl;
	}

	float height = this->map.GetHeight((int)this->camera.GetPosition().x, (int)this->camera.GetPosition().y);
	if(this->camera.GetPosition().z < height)
	{
		this->camera.Move(sf::Vector3f(0.f, 0.f, height - this->camera.GetPosition().z + 0.02f));
	}

	if(camera.GetRpy().z < 0.f)
	{
		this->camera.Rotate(sf::Vector3f(0.f, 0.f, 360.f));
	}
	if(camera.GetRpy().z >= 360.f)
	{
		this->camera.Rotate(sf::Vector3f(0.f, 0.f, -360.f));
	}
}

void App::HandleInput()
{
	sf::Event event;
	while(this->window.GetEvent(event))
	{
		if(event.Type == sf::Event::Closed)
		{
			this->window.Close();
		}
		if(event.Type == sf::Event::Resized)
		{
			glViewport(0, 0, event.Size.Width, event.Size.Height);
		}
		if(event.Type == sf::Event::MouseWheelMoved)
		{
			float height = this->map.GetHeight((int)this->camera.GetPosition().x, (int)this->camera.GetPosition().y);
			this->camera.Move(
					sf::Vector3f(
							0.f,
							0.f,
							-0.05f * (float)event.MouseWheel.Delta * (this->camera.GetPosition().z - height)));
		}
	}

	const sf::Input& input = this->window.GetInput();
	float height = this->camera.GetPosition().z - this->map.GetHeight(this->camera.GetPosition().x, this->camera.GetPosition().y);
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

}

void App::Draw()
{
	this->window.SetActive();
	this->map.Draw(this->window, this->camera, this->resources);
	this->window.Display();
}

} /* namespace dfv */
