/*
 * Serilizer_test.cpp
 *
 *  Created on: Jan 12, 2015
 *      Author: daniel
 */

#include <gtest/gtest.h>
#include "../src/Serializer.h"

namespace dfv
{

// Serializer test
// write some variables to a file and read the same file back
// check if corresponding values (written and read) are the same.
TEST(serializerTest, serializationTest)
{
	Serializer ser;
	ser.openOutFile("test_serialization.txt");

	string testStr("test");
	ser.write("testStr", testStr);

	int testInt = 1234;
	ser.write("testInt", testInt);

	size_t testSizeT = 1234;
	ser.write("testSizeT", testSizeT);

	unsigned int testUnsignedInt = 1234;
	ser.write("testUnsignedInt", testUnsignedInt);

	float testFloat = 1234.f;
	ser.write("testFloat", testFloat);

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
				ASSERT_EQ(readValue, testStr);
			}
			else if(reading.name == "testInt")
			{
				int readValue;
				isRead(reading, readValue);
				ASSERT_EQ(readValue, testInt);
			}
			else if(reading.name == "testSizeT")
			{
				size_t readValue;
				isRead(reading, readValue);
				ASSERT_EQ(readValue, testSizeT);
			}
			else if(reading.name == "testFloat")
			{
				float readValue;
				isRead(reading, readValue);
				ASSERT_FLOAT_EQ(readValue, testFloat);
			}
			else if(reading.name == "testUnsignedInt")
			{
				float readValue;
				isRead(reading, readValue);
				ASSERT_FLOAT_EQ(readValue, testUnsignedInt);
			}
		}
	}
}

};
