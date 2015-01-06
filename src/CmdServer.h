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

 * CmdServer.h
 *
 *  Created on: Aug 24, 2014
 *      Author: daniel
 */

#ifndef CMDSERVER_H_
#define CMDSERVER_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>

namespace dfv
{

class CmdServer
{
public:
	CmdServer(const int portno);
	virtual ~CmdServer();

	bool init();
	void run();
	void runThread();
	std::string getCmd();
	void terminate();

private:
	int sockfd;
	int newsockfd;
	int portno;
	socklen_t clilen;
	char buffer[256];
	struct sockaddr_in serverAddr;
	struct sockaddr_in clientAddr;
	std::string cmd;
	bool cmdReceived;
	std::thread thread;
	bool running;
};

} /* namespace dfv */

#endif /* CMDSERVER_H_ */
