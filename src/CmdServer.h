/*
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

private:
	int sockfd;
	int newsockfd;
	int portno;
	socklen_t clilen;
	char buffer[256];
	struct sockaddr_in serv_addr;
	struct sockaddr_in cli_addr;
	int n;
	std::string cmd;
	bool cmd_received;
	std::thread run_thread;
};

} /* namespace dfv */

#endif /* CMDSERVER_H_ */
