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
	Text* lp_title = new Text(&(this->gui));
	lp_title->text = "HYPEROPOLIS";
	lp_title->txt_size = 50.f;
	lp_title->position = {100.f, 100.f};
	lp_title->size = {500.f, 200.f};
	lp_title->txt_color = sf::Color::White;
	lp_title->bg_color = sf::Color(0, 0, 0, 0);
	this->gui.addComponent(lp_title);

	Clickable* lp_start_button = new Clickable(&(this->gui));
	lp_start_button->text = "Start";
	lp_start_button->txt_size = 20.f;
	lp_start_button->position = {300.f, 300.f};
	lp_start_button->size = {200.f, 50.f};
	lp_start_button->txt_color = sf::Color::White;
	lp_start_button->bg_color = sf::Color(64, 64, 64, 128);
	lp_start_button->bg_over_color = sf::Color(64, 64, 64, 255);
	lp_start_button->cmd = std::string("start");
	this->gui.addComponent(lp_start_button);

	Clickable* lp_quit_button = new Clickable(&(this->gui));
	lp_quit_button->text = "Quit";
	lp_quit_button->txt_size = 20.f;
	lp_quit_button->position = {300.f, 375.f};
	lp_quit_button->size = {200.f, 50.f};
	lp_quit_button->txt_color = sf::Color::White;
	lp_quit_button->bg_color = sf::Color(64, 64, 64, 128);
	lp_quit_button->bg_over_color = sf::Color(64, 64, 64, 255);
	lp_quit_button->cmd = std::string("quit");
	this->gui.addComponent(lp_quit_button);



}

StartMenuState::~StartMenuState()
{
	// TODO Auto-generated destructor stub
}

} /* namespace dfv */
