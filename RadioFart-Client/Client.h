#pragma once

#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

class Client
{
public:
	Client();
	void connectClient();
	void closeSocket();
	int end();
private:
	int clientResult;
	SOCKET connectSocket;
	char recvBuffer[512];
	ADDRINFO* addrResult = NULL;
};

