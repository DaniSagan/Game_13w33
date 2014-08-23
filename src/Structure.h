/*
 * Structure.h
 *
 *  Created on: Aug 22, 2014
 *      Author: daniel
 */

#ifndef STRUCTURE_H_
#define STRUCTURE_H_

#include <SFML/Graphics.hpp>
#include "Model.h"

namespace dfv
{

class Structure
{
public:
	Structure();
	virtual ~Structure();

	void setModel(const Model & model);
	void drawBox() const;
	void drawOutline() const;
private:
	Model model;
};

} /* namespace dfv */

#endif /* STRUCTURE_H_ */
