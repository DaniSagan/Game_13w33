/*
 *  Hyperopolis: Megacities building game.
    Copyright (C) 2014  Daniel Fernández Villanueva

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

 * Assets.h
 *
 *  Created on: Aug 28, 2014
 *      Author: daniel
 */

#ifndef ASSETS_H_
#define ASSETS_H_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace dfv
{

class Assets
{
public:
	Assets();
	virtual ~Assets();

	sf::Font font;
	sf::Texture buttonMenuImg;
	bool load();

	struct Sounds
	{
		sf::SoundBuffer selectBuffer;
		sf::Sound select;
		sf::SoundBuffer overBuffer;
		sf::Sound over;
	} sounds;
};

extern Assets assetsInstance;

} /* namespace dfv */

#endif /* ASSETS_H_ */
