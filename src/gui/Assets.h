/*
 * Assets.h
 *
 *  Created on: Aug 28, 2014
 *      Author: daniel
 */

#ifndef ASSETS_H_
#define ASSETS_H_

#include <SFML/Graphics.hpp>

namespace dfv
{

class Assets
{
public:
	Assets();
	virtual ~Assets();

	sf::Font font;
	bool load();
};

} /* namespace dfv */

#endif /* ASSETS_H_ */
