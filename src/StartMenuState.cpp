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
	else if(cmd == std::string("start_new_close"))
	{
		static_cast<Panel*>(this->gui.getById(START_NEW_MENU))->visible = false;
	}
	cmd.clear();
}


StartMenuState::StartMenuState():
		gui(nullptr)
{
	Picture* lp_bg_img = new Picture(&(this->gui));
	lp_bg_img->loadFromFile("res/gui/start_bg_1.png");

	Picture* lp_logo = new Picture(lp_bg_img);
	lp_logo->loadFromFile("res/gui/logo.png");
	lp_logo->setPosition(sf::Vector2f(50.f, 50.f));

	Clickable* lp_start_button = new Clickable(lp_bg_img);
	lp_start_button->text = "Start new";
	lp_start_button->txt_size = 24.f;
	lp_start_button->size = {200.f, 50.f};
	lp_start_button->setPosition({1024.f - 200.f, 1024.f * 9.f / 16.f - 50.f*3.f});
	lp_start_button->txt_color = sf::Color::White;
	lp_start_button->bg_color = sf::Color(64, 64, 64, 192);
	lp_start_button->bg_over_color = sf::Color(64, 64, 64, 255);
	lp_start_button->cmd = std::string("start");

	Clickable* lp_load_button = new Clickable(lp_bg_img);
	lp_load_button->text = "Load city";
	lp_load_button->txt_size = 24.f;
	lp_load_button->setPosition({1024.f - 200.f, 1024.f * 9.f / 16.f - 50.f*2.f});
	lp_load_button->size = {200.f, 50.f};
	lp_load_button->txt_color = sf::Color::White;
	lp_load_button->bg_color = sf::Color(64, 64, 64, 192);
	lp_load_button->bg_over_color = sf::Color(64, 64, 64, 255);
	lp_load_button->cmd = std::string("load");

	Clickable* lp_quit_button = new Clickable(lp_bg_img);
	lp_quit_button->text = "Quit game";
	lp_quit_button->txt_size = 24.f;
	lp_quit_button->setPosition({1024.f - 200.f, 1024.f * 9.f / 16.f - 50.f*1.f});
	lp_quit_button->size = {200.f, 50.f};
	lp_quit_button->txt_color = sf::Color::White;
	lp_quit_button->bg_color = sf::Color(64, 64, 64, 192);
	lp_quit_button->bg_over_color = sf::Color(64, 64, 64, 255);
	lp_quit_button->cmd = std::string("quit");

	Panel* lp_new_menu = new Panel(lp_bg_img, START_NEW_MENU);
	lp_new_menu->size = {300.f, 200.f};
	lp_new_menu->setPosition({300.f, 300.f});
	lp_new_menu->visible = true;
	lp_new_menu->color = sf::Color(64, 64, 64, 192);

	Clickable* lp_close_button = new Clickable(lp_new_menu);
	lp_close_button->bg_color = sf::Color(255, 0, 0, 128);
	lp_close_button->bg_over_color = sf::Color(255, 0, 0, 255);
	lp_close_button->size = sf::Vector2f(15.f, 15.f);
	lp_close_button->cmd = std::string("start_new_close");
	lp_close_button->setPosition({2.f, 2.f});




}

StartMenuState::~StartMenuState()
{
	// TODO Auto-generated destructor stub
}

} /* namespace dfv */
