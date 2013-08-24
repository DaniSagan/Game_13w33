/*
 * ComandParser.h
 *
 *  Created on: Aug 23, 2013
 *      Author: daniel
 */

#ifndef COMANDPARSER_H_
#define COMANDPARSER_H_

#include <string>
#include <vector>

namespace dfv
{

class ComandParser
{
public:
	ComandParser();
	virtual ~ComandParser();

	bool Parse(
			const std::string& command,
			std::string& function_name,
			std::vector<float> params);
};

} /* namespace dfv */
#endif /* COMANDPARSER_H_ */
