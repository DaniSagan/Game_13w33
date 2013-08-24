/*
 * App.h
 *
 *  Created on: Aug 11, 2013
 *      Author: daniel
 */

#ifndef APP_H_
#define APP_H_

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>
#include "Map.h"
#include "Resources.h"
//#include "Minimap.h"
#include "gui/Button.h"
#include "gui/Gui.h"

namespace dfv
{

class App : public sf::Thread
{
public:
	App();
	virtual ~App();

	void Initialize();
	void Run();
	void Update();
	void HandleInput();
	void Draw();
	void InitOpenGL();

	bool ExecuteCommand(std::string cmd);

private:
	sf::RenderWindow window;
	sf::Clock clock;
	dfv::Camera camera;
	dfv::Map map;
	unsigned int frame;
	dfv::Resources resources;
	//dfv::Minimap minimap;
	sf::Vector3f map_pos;
	sf::Vector2i mouse_pos;

	dfv::Button button;
	dfv::Gui gui;

	bool walking;
};

} /* namespace dfv */
#endif /* APP_H_ */
