/*
 * StartMenuState.cpp
 *
 *  Created on: Aug 30, 2014
 *      Author: daniel
 */

#include "StartMenuState.h"
#include "PlayState.h"

namespace dfv
{

StartMenuState StartMenuState::start_menu_state;

void StartMenuState::init(GameEngine* lp_game_engine)
{
}

void StartMenuState::cleanup()
{
}

void StartMenuState::pause()
{
}

void StartMenuState::resume()
{
}

void StartMenuState::handleInput(GameEngine* lp_game_engine)
{
	std::string cmd("");
	sf::Event event;
	while(lp_game_engine->window.pollEvent(event))
	{
		this->gui.handleInput(cmd, event);
		this->executeCmd(cmd, lp_game_engine);
		if(event.type == sf::Event::Closed)
		{
			lp_game_engine->quit();
		}
	}
}

void StartMenuState::update(GameEngine* lp_game_engine)
{
}

void StartMenuState::draw(GameEngine* lp_game_engine)
{
	lp_game_engine->window.pushGLStates();
	lp_game_engine->window.clear(sf::Color(200, 200, 200));
	this->gui.draw(lp_game_engine->window, lp_game_engine->assets);
	lp_game_engine->window.popGLStates();
	lp_game_engine->window.display();
}

void StartMenuState::executeCmd(std::string& cmd, GameEngine* lp_game_engine)
{
	if(cmd == std::string("quit"))
	{
		lp_game_engine->quit();
	}
	else if(cmd == std::string("start"))
	{
		lp_game_engine->changeState(PlayState::getInstance());
	}
	cmd.clear();
}


StartMenuState::StartMenuState():
		gui(nullptr)
{
	Picture* lp_bg_img = new Picture(&(this->gui));
	lp_bg_img->loadFromFile("res/gui/start_bg_1.png");
	this->gui.addComponent(lp_bg_img);

	Picture* lp_logo = new Picture(lp_bg_img);
	lp_logo->loadFromFile("res/gui/logo.png");
	lp_logo->position = sf::Vector2f(50.f, 50.f);
	this->gui.addComponent(lp_logo);

	/*Text* lp_title = new Text(lp_bg_img);
	lp_title->text = "HYPEROPOLIS";
	lp_title->txt_size = 50.f;
	lp_title->position = {100.f, 100.f};
	lp_title->size = {500.f, 200.f};
	lp_title->txt_color = sf::Color::White;
	lp_title->bg_color = sf::Color(0, 0, 0, 0);
	this->gui.addComponent(lp_title);*/

	Clickable* lp_start_button = new Clickable(lp_bg_img);
	lp_start_button->text = "Start new";
	lp_start_button->txt_size = 24.f;
	lp_start_button->size = {200.f, 50.f};
	lp_start_button->position = {1024.f - 200.f, 1024.f * 9.f / 16.f - 50.f*3.f};
	lp_start_button->txt_color = sf::Color::White;
	lp_start_button->bg_color = sf::Color(64, 64, 64, 192);
	lp_start_button->bg_over_color = sf::Color(64, 64, 64, 255);
	lp_start_button->cmd = std::string("start");
	this->gui.addComponent(lp_start_button);

	Clickable* lp_load_button = new Clickable(lp_bg_img);
	lp_load_button->text = "Load city";
	lp_load_button->txt_size = 24.f;
	lp_load_button->position = {1024.f - 200.f, 1024.f * 9.f / 16.f - 50.f*2.f};
	lp_load_button->size = {200.f, 50.f};
	lp_load_button->txt_color = sf::Color::White;
	lp_load_button->bg_color = sf::Color(64, 64, 64, 192);
	lp_load_button->bg_over_color = sf::Color(64, 64, 64, 255);
	lp_load_button->cmd = std::string("load");
	this->gui.addComponent(lp_load_button);

	Clickable* lp_quit_button = new Clickable(lp_bg_img);
	lp_quit_button->text = "Quit game";
	lp_quit_button->txt_size = 24.f;
	lp_quit_button->position = {1024.f - 200.f, 1024.f * 9.f / 16.f - 50.f*1.f};
	lp_quit_button->size = {200.f, 50.f};
	lp_quit_button->txt_color = sf::Color::White;
	lp_quit_button->bg_color = sf::Color(64, 64, 64, 192);
	lp_quit_button->bg_over_color = sf::Color(64, 64, 64, 255);
	lp_quit_button->cmd = std::string("quit");
	this->gui.addComponent(lp_quit_button);



}

StartMenuState::~StartMenuState()
{
	// TODO Auto-generated destructor stub
}

} /* namespace dfv */
