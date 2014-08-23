/*
 * Structure.cpp
 *
 *  Created on: Aug 22, 2014
 *      Author: daniel
 */

#include "Structure.h"

namespace dfv
{

Structure::Structure()
{
	// TODO Auto-generated constructor stub

}

Structure::~Structure()
{
	// TODO Auto-generated destructor stub
}

void Structure::setModel(const Model& model)
{
	this->model = model;
}

void Structure::drawBox() const
{
	this->model.drawBox();
}

void Structure::drawOutline() const
{
	this->model.drawOutlines();
}

} /* namespace dfv */
