/*
 * Tree.h
 *
 *  Created on: Jun 23, 2014
 *      Author: daniel
 */

#ifndef TREE_H_
#define TREE_H_

#include "Prop.h"

#include <SFML/OpenGL.hpp>

namespace dfv {

class Tree: public Prop
{
public:
	Tree();
	virtual ~Tree();
	void Create(const std::vector<sf::Vector3f>& tile_vertices);
	void Draw(const dfv::Camera& camera, const dfv::Resources& resources) const;
	void drawQuad(const unsigned int index, const dfv::Resources& resources) const;
protected:
	//std::vector<sf::Vector3f> vertices;
	//std::vector<sf::Vector3f> normals;
	std::vector<Quad> quads;
	OpenGLImage *lp_img;
	unsigned int type;
};

} /* namespace dfv */
#endif /* TREE_H_ */
