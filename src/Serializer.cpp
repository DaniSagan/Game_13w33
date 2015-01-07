/*
 * Serializer.cpp
 *
 *  Created on: Jan 6, 2015
 *      Author: daniel
 */

#include "Serializer.h"

namespace dfv
{

Serializer::Serializer()
{
	// TODO Auto-generated constructor stub

}

Serializer::~Serializer()
{
	// TODO Auto-generated destructor stub
}

Serializer::Reading::Reading()
{
}

Serializer::Reading::Reading(const string& type, const string& name,
		const string& value)
{
	this->type = type;
	this->name = name;
	this->value = value;
}

bool Serializer::openOutFile(const string& filename)
{
	this->out.open(filename.c_str(), ofstream::out);
	return this->out.is_open();
}

void Serializer::closeOutFile()
{
	this->out.close();
}

bool Serializer::openInFile(const string& filename)
{
	this->in.open(filename.c_str(), ifstream::in);
	return this->in.is_open();
}

Serializer::Reading::Position Serializer::read(Reading& reading)
{
	string line;
	if(getline(in, line))
	{
		istringstream iss(line);
		//iss.ignore(numeric_limits<streamsize>::max(), '=');
		string type, name, oper, value;
		if(line.find("=") != string::npos)
		{
			iss >> type >> name >> oper;
			value = line.substr(line.find("=")+2, line.size());
		}
		else
		{
			value = line.substr(line.find_first_not_of(" \t\r\n"), line.size());
		}
		reading = Reading(type, name, value);
		if(value == "{")
		{
			return Serializer::Reading::OBJECT_START;
		}
		else if(value == "}")
		{
			return Serializer::Reading::OBJECT_END;
		}
		if(value == "[")
		{
			return Serializer::Reading::ARRAY_START;
		}
		else if(value == "]")
		{
			return Serializer::Reading::ARRAY_END;
		}
		else
		{
			return Serializer::Reading::VALUE;
		}
	}
	else
	{
		return Serializer::Reading::FILE_END;
	}
}

void Serializer::closeInFile()
{
}

string osString(size_t level, const string& name, const int& value)
{
	stringstream ss;
	for(size_t k = 0; k < level; k++)
	{
		ss << "\t";
	}
	ss << "int " << name << " = " << to_string(value) << "\n";
	return ss.str();
}

bool isRead(const Serializer::Reading& reading, int& var)
{
	var = stoi(reading.value);
}

string osString(size_t level, const string& name, const size_t& value)
{
	stringstream ss;
	for(size_t k = 0; k < level; k++)
	{
		ss << "\t";
	}
	ss << "size_t " << name << " = " << to_string(value) << "\n";
	return ss.str();
}

bool isRead(const Serializer::Reading& reading, size_t& var)
{
	var = stoi(reading.value);
}

string osString(size_t level, const string& name, const unsigned int& value)
{
	stringstream ss;
	for(size_t k = 0; k < level; k++)
	{
		ss << "\t";
	}
	ss << "unsigned_int " << name << " = " << to_string(value) << "\n";
	return ss.str();
}

bool isRead(const Serializer::Reading& reading, unsigned int& var)
{
	var = stoi(reading.value);
}

string osString(size_t level, const string& name, const float& value)
{
	stringstream ss;
	for(size_t k = 0; k < level; k++)
	{
		ss << "\t";
	}
	ss << "float " << name << " = " << to_string(value) << "\n";
	return ss.str();
}

bool isRead(const Serializer::Reading& reading, float& var)
{
	var = stof(reading.value);
}

string osString(size_t level, const string& name, const string& value)
{
	stringstream ss;
	for(size_t k = 0; k < level; k++)
	{
		ss << "\t";
	}
	ss << "string " << name << " = \"" << value << "\"\n";
	return ss.str();
}

bool isRead(const Serializer::Reading& reading, string& var)
{
	var = reading.value.substr(1, reading.value.size()-2);
}

string osString(size_t level, const string& name, const sf::Vector3f& value)
{
	stringstream ss;
	for(size_t k = 0; k < level; k++)
	{
		ss << "\t";
	}
	ss << "sf::Vector3f " << name << " = " << to_string(value.x) << ", " << to_string(value.y) << ", " << to_string(value.z) << "\n";
	return ss.str();
}

bool isRead(const Serializer::Reading& reading, sf::Vector3f& var)
{
	float x, y, z;
	stringstream ss(reading.value);
	ss >> x;
	ss.ignore();
	ss >> y;
	ss.ignore();
	ss >> z;
	var = sf::Vector3f(x, y, z);
}

string osString(size_t level, const string& name, const sf::Color& value)
{
	stringstream ss;
	for(size_t k = 0; k < level; k++)
	{
		ss << "\t";
	}
	ss << "sf::Color " << name << " = " << to_string(value.r) << ", " << to_string(value.g) << ", " << to_string(value.b) << "\n";
	return ss.str();
}

} /* namespace dfv */
