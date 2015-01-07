/*
 * Serializer.h
 *
 *  Created on: Jan 6, 2015
 *      Author: daniel
 */

#ifndef SRC_SERIALIZER_H_
#define SRC_SERIALIZER_H_

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <limits>
#include <vector>
#include "Utils.h"

using namespace std;

namespace dfv
{

class Serializer
{
public:
	Serializer();
	virtual ~Serializer();

	struct Reading
	{
		string type;
		string name;
		string value;
		Reading();
		Reading(const string& type, const string& name, const string& value);
		enum Position
		{
			VALUE,
			OBJECT_START,
			OBJECT_END,
			ARRAY_START,
			ARRAY_END,
			FILE_END
		};
	};

	bool openOutFile(const string& filename);
	template <typename T>
	void write(const string& name, const T& obj)
	{
		this->out << osString(0, name, obj);
	}
	void closeOutFile();

	bool openInFile(const string& filename);
	Reading::Position read(Reading& reading);
	void closeInFile();

protected:
	ofstream out;
	ifstream in;
};

string osString(size_t level, const string& name, const int& value);
bool isRead(const Serializer::Reading& reading, int& var);
string osString(size_t level, const string& name, const size_t& value);
bool isRead(const Serializer::Reading& reading, size_t& var);
string osString(size_t level, const string& name, const float& value);
bool isRead(const Serializer::Reading& reading, float& var);
string osString(size_t level, const string& name, const string& value);
bool isRead(const Serializer::Reading& reading, string& var);
string osString(size_t level, const string& name, const sf::Vector3f& value);
bool isRead(const Serializer::Reading& reading, sf::Vector3f& var);
string osString(size_t level, const string& name, const sf::Color& value);

} /* namespace dfv */

#endif /* SRC_SERIALIZER_H_ */
