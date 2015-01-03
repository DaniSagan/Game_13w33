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

 * CmdServer.cpp
 *
 *  Created on: Aug 24, 2014
 *      Author: daniel
 */

#include "CmdServer.h"

namespace dfv
{

CmdServer::CmdServer(const int portno):
		cmdReceived(false), running(true)
{
	bzero((char*) &(this->serverAddr), sizeof serverAddr);
	this->serverAddr.sin_family = AF_INET;
	this->serverAddr.sin_addr.s_addr = INADDR_ANY;
	this->serverAddr.sin_port = htons(portno);
	this->clilen = sizeof clientAddr;
}

CmdServer::~CmdServer()
{
	close(this->newsockfd);
	close(this->sockfd);
}

bool CmdServer::init()
{
	this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(bind(this->sockfd,
			(struct sockaddr*) &(this->serverAddr),
			sizeof this->serverAddr) < 0)
	{
		std::cout << "ERROR on binding" << std::endl;
		return false;
	}
	std::cout << "listening" << std::endl;
	listen(this->sockfd, 5);
	return true;
}

void CmdServer::run()
{
	this->thread = std::thread(&CmdServer::runThread, this);
}

void CmdServer::runThread()
{
	while(this->running)
	{
		this->newsockfd = accept(this->sockfd, (struct sockaddr*) &(this->clientAddr), &(this->clilen));
		//std::cout << "accepted" << std::endl;
		if(this->newsockfd < 0)
		{
			std::cout << "ERROR on accept" << std::endl;
			continue;
		}
		while(this->running)
		{
			std::cout << "waiting for message" << std::endl;

			bzero(this->buffer, 256);
			n = read(this->newsockfd, this->buffer, 255);
			if(n <= 0)
			{
				std::cout << "ERROR reading from socket" << std::endl;
				break;
			}
			std::cout << "Message: " << this->buffer << std::endl;
			this->cmd = std::string(this->buffer);
			this->cmdReceived = true;
		}
	}
}

std::string CmdServer::getCmd()
{
	if(this->cmdReceived)
	{
		this->cmdReceived = false;
		return this->cmd;
	}
	else
	{
		return std::string("");
	}

}

void CmdServer::terminate()
{
	close(this->newsockfd);
	close(this->sockfd);
	this->running = false;
	//this->run_thread.join();
}

} /* namespace dfv */
