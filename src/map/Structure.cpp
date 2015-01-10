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
	this->model = move(model);
}

void Structure::drawBox() const
{
	this->model.drawBox();
}

void Structure::drawOutline() const
{
	this->model.drawOutlines();
}

float Structure::getModelHeight() const
{
	return this->model.getHeight();
}

unsigned int Structure::getModelFloorCount() const
{
	return this->model.getFloorCount();
}

string osString(size_t level, const string& name, const Structure& structure)
{
	stringstream ss;
	if(name.empty())
	{
		ss << strRepeat(level, string("\t")) << "{" << endl;
	}
	else
	{
		ss << strRepeat(level, string("\t")) << "Structure " << name << " = {" << endl;
	}
	ss << osString(level+1, "model", structure.model);
	ss << strRepeat(level, string("\t")) << "}" << endl;
	return ss.str();
}

string osString(size_t level, const string& name, const vector<Structure*>& lpStructures)
{
	stringstream ss;
	ss << strRepeat(level, "\t") << "Structure" << "[" << lpStructures.size() << "] " << name << " = [" << "\n";
	for(const Structure* lpStructure: lpStructures)
	{
		ss << osString(level+1, string(""), *lpStructure);
	}
	ss << strRepeat(level, "\t") << "]\n";
	return ss.str();
}

bool isRead(Serializer& ser, Structure& structure)
{
	bool finished = false;
	while(!finished)
	{
		Serializer::Reading reading;
		Serializer::Reading::Position pos = ser.read(reading);
		if(pos == Serializer::Reading::OBJECT_END)
		{
			finished = true;
		}
		else if(pos == Serializer::Reading::OBJECT_START)
		{
			if(reading.name == "model")
			{
				Model model;
				isRead(ser, model);
				structure.setModel(model);
			}
		}
	}
	return true;
}

bool isRead(Serializer& ser, vector<Structure*>& lpStructures)
{
	bool finished = false;
	while(!finished)
	{
		Serializer::Reading reading;
		Serializer::Reading::Position pos = ser.read(reading);
		if(pos == Serializer::Reading::ARRAY_END)
		{
			finished = true;
		}
		else if(pos == Serializer::Reading::OBJECT_START)
		{
			Structure* lpStructure = new Structure();
			isRead(ser, *lpStructure);
			lpStructures.push_back(lpStructure);
		}
	}
	return true;
}

} /* namespace dfv */
