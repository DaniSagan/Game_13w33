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
		cmd_received(false)
{
	//this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero((char*) &(this->serv_addr), sizeof serv_addr);
	this->serv_addr.sin_family = AF_INET;
	this->serv_addr.sin_addr.s_addr = INADDR_ANY;
	this->serv_addr.sin_port = htons(portno);
	//if(bind(this->sockfd,
	//		(struct sockaddr*) &(this->serv_addr),
	//		sizeof this->serv_addr) < 0)
	//{
	//	std::cout << "ERROR on binding" << std::endl;
	//}
	//listen(this->sockfd, 5);
	this->clilen = sizeof cli_addr;
	//this->newsockfd = accept(this->sockfd, (struct sockaddr*) &(this->cli_addr), &(this->clilen));
	//if(this->newsockfd < 0)
	//{
	//	std::cout << "ERROR on accept" << std::endl;
	//}
	//bzero(this->buffer, 256);
	//n = read(this->newsockfd, this->buffer, 255);
	//if(n < 0)
	//{
	//	std::cout << "ERROR reading from socket" << std::endl;
	//}
	//std::cout << "Message: " << this->buffer << std::endl;
	//this->init();
	//this->run();
}

CmdServer::~CmdServer()
{
	close(this->newsockfd);
	close(this->sockfd);
}

bool CmdServer::init()
{
	this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
	//bzero((char*) &(this->serv_addr), sizeof serv_addr);
	if(bind(this->sockfd,
			(struct sockaddr*) &(this->serv_addr),
			sizeof this->serv_addr) < 0)
	{
		std::cout << "ERROR on binding" << std::endl;
		return false;
	}
	std::cout << "listening" << std::endl;
	listen(this->sockfd, 5);
	//this->clilen = sizeof cli_addr;
	return true;
}

void CmdServer::run()
{
	this->run_thread = std::thread(&CmdServer::runThread, this);
}

void CmdServer::runThread()
{
	while(true)
	{
		this->newsockfd = accept(this->sockfd, (struct sockaddr*) &(this->cli_addr), &(this->clilen));
		//std::cout << "accepted" << std::endl;
		if(this->newsockfd < 0)
		{
			std::cout << "ERROR on accept" << std::endl;
			continue;
		}
		while(true)
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
			this->cmd_received = true;
		}
	}
}

std::string CmdServer::getCmd()
{
	if(this->cmd_received)
	{
		this->cmd_received = false;
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
}

} /* namespace dfv */
