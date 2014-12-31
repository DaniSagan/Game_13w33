/*
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
