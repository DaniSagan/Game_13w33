/*
 * Picture.h
 *
 *  Created on: Aug 31, 2014
 *      Author: daniel
 */

#ifndef PICTURE_H_
#define PICTURE_H_

#include "Component.h"

namespace dfv
{

class Picture: public Component
{
public:
	Picture(Component* parent, int id=-1);
	virtual ~Picture();

	virtual void draw(sf::RenderWindow& window, const Assets& assets) const;

	bool loadFromFile(std::string filename);

	bool visible;
protected:
	sf::Texture texture;
};

} /* namespace dfv */

#endif /* PICTURE_H_ */
