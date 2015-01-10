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
		assert(line != "");
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
	ss << strRepeat(level, "\t");
	if(name != "")
	{
		ss << "int " << name << " = ";
	}
	ss << to_string(value) << "\n";
	return ss.str();
}

bool isRead(const Serializer::Reading& reading, int& var)
{
	var = stoi(reading.value);
	return true;
}

string osString(size_t level, const string& name, const size_t& value)
{
	stringstream ss;
	ss << strRepeat(level, "\t");
	if(name != "")
	{
		ss << "size_t " << name << " = ";
	}
	ss << to_string(value) << "\n";
	return ss.str();
}

bool isRead(const Serializer::Reading& reading, size_t& var)
{
	var = stoi(reading.value);
	return true;
}

string osString(size_t level, const string& name, const unsigned int& value)
{
	stringstream ss;
	ss << strRepeat(level, "\t");
	if(name != "")
	{
		ss << "unsigned_int " << name << " = ";
	}
	ss << to_string(value) << "\n";
	return ss.str();
}

bool isRead(const Serializer::Reading& reading, unsigned int& var)
{
	var = stoi(reading.value);
	return true;
}

string osString(size_t level, const string& name, const float& value)
{
	stringstream ss;
	ss << strRepeat(level, "\t");
	if(name != "")
	{
		ss << "float " << name << " = ";
	}
	ss << to_string(value) << "\n";
	return ss.str();
}

bool isRead(const Serializer::Reading& reading, float& var)
{
	var = stof(reading.value);
	return true;
}

string osString(size_t level, const string& name, const string& value)
{
	stringstream ss;
	ss << strRepeat(level, "\t");
	if(name != "")
	{
		ss << "string " << name << " = ";
	}
	ss << "\"" << value << "\"\n";
	return ss.str();
}

bool isRead(const Serializer::Reading& reading, string& var)
{
	var = reading.value.substr(1, reading.value.size()-2);
	return true;
}

string osString(size_t level, const string& name, const sf::Vector2f& value)
{
	stringstream ss;
	ss << strRepeat(level, "\t");
	if(name != "")
	{
		ss << "sf::Vector2f " << name << " = ";
	}
	ss << to_string(value.x) << ", " << to_string(value.y) << "\n";
	return ss.str();
}

bool isRead(const Serializer::Reading& reading, sf::Vector2f& var)
{
	float x, y;
	stringstream ss(reading.value);
	ss >> x;
	ss.ignore();
	ss >> y;
	var = sf::Vector2f(x, y);
	return true;
}

string osString(size_t level, const string& name, const sf::Vector3f& value)
{
	stringstream ss;
	ss << strRepeat(level, "\t");
	if(name != "")
	{
		ss << "sf::Vector3f " << name << " = ";
	}
	ss << to_string(value.x) << ", " << to_string(value.y) << ", " << to_string(value.z) << "\n";
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
	return true;
}

string osString(size_t level, const string& name, const sf::Vector2i& value)
{
	stringstream ss;
	ss << strRepeat(level, "\t");
	if(name != "")
	{
		ss << "sf::Vector2i " << name << " = ";
	}
	ss << value.x << ", " << value.y << "\n";
	return ss.str();
}

bool isRead(const Serializer::Reading& reading, sf::Vector2i& var)
{
	int x, y;
	stringstream ss(reading.value);
	ss >> x;
	ss.ignore();
	ss >> y;
	var = sf::Vector2i(x, y);
	return true;
}

string osString(size_t level, const string& name, const vector<sf::Vector2i>& value)
{
	stringstream ss;
	ss << strRepeat(level, "\t") << "sf::Vector2i" << "[" << value.size() << "] " << name << " = [" << "\n";
	for(sf::Vector2i v: value)
	{
		ss << osString(level+1, string(""), v);
	}
	ss << strRepeat(level, "\t") << "]\n";
	return ss.str();
}

bool isRead(Serializer& ser, vector<sf::Vector2i>& var)
{
	vector<sf::Vector2i> res;
	bool finished = false;
	while(!finished)
	{
		Serializer::Reading reading;
		Serializer::Reading::Position pos = ser.read(reading);
		if(pos == Serializer::Reading::VALUE)
		{
			sf::Vector2i v;
			isRead(reading, v);
			res.push_back(v);
		}
		else if(pos == Serializer::Reading::ARRAY_END)
		{
			finished = true;
		}
	}
	var = res;
	return true;
}

string osString(size_t level, const string& name, const sf::Color& value)
{
	stringstream ss;
	ss << strRepeat(level, "\t");
	if(name != "")
	{
		ss << "sf::Color " << name << " = ";
	}
	ss << to_string(value.r) << ", " << to_string(value.g) << ", " << to_string(value.b) << "\n";
	return ss.str();
}

bool testSerializer()
{
	string testStr("test");
	Serializer ser;
	ser.openOutFile("test_serialization.txt");
	ser.write("testStr", testStr);
	ser.closeOutFile();

	ser.openInFile("test_serialization.txt");
	bool finished = false;
	while(!finished)
	{
		Serializer::Reading reading;
		Serializer::Reading::Position pos = ser.read(reading);
		if(pos == Serializer::Reading::FILE_END)
		{
			finished = true;
		}
		else if(pos == Serializer::Reading::VALUE)
		{
			if(reading.name == "testStr")
			{
				string readValue;
				isRead(reading, readValue);
				assert(readValue == testStr);
			}
		}
	}
	return true;
}

} /* namespace dfv */
