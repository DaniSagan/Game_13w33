/*
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

} /* namespace dfv */
