#include "Client.h"

Client::Client()
{
	WSADATA wsaData;
	ADDRINFO hints;
	connectSocket = INVALID_SOCKET;
	const char* sendBuffer = "Hello from Client";

	clientResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (clientResult != 0)
	{
		std::cout << "WSAStartup failed, result = " << clientResult << std::endl;
		exit(1);
	}
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	clientResult = getaddrinfo("localhost", "666", &hints, &addrResult);
	if (clientResult != 0)
	{
		std::cout << "getaddrinfo failed, result = " << clientResult << std::endl;
		WSACleanup();
		exit(1);
	}
	connectSocket = socket(addrResult->ai_family, addrResult->ai_socktype, addrResult->ai_protocol);
	if (connectSocket == INVALID_SOCKET)
	{
		std::cout << "Socket creation failed" << std::endl;
		freeaddrinfo(addrResult);
		WSACleanup();
		exit(1);
	}
	clientResult = connect(connectSocket, addrResult->ai_addr, (int)addrResult->ai_addrlen);
	if (clientResult == SOCKET_ERROR)
	{
		std::cout << "Unable connect to server" << std::endl;
		closesocket(connectSocket);
		connectSocket = INVALID_SOCKET;
		freeaddrinfo(addrResult);
		WSACleanup();
		exit(1);
	}
	clientResult = send(connectSocket, sendBuffer, (int)strlen(sendBuffer), 0);
	if (clientResult == SOCKET_ERROR)
	{
		std::cout << "send failed, result = " << clientResult << std::endl;
		closesocket(connectSocket);
		freeaddrinfo(addrResult);
		WSACleanup();
		exit(1);
	}
	std::cout << "bytes sent: " << clientResult << std::endl;

	clientResult = shutdown(connectSocket, SD_SEND);
	if (clientResult == SOCKET_ERROR)
	{
		std::cout << "shutdown result = " << clientResult << std::endl;
		closesocket(connectSocket);
		freeaddrinfo(addrResult);
		WSACleanup();
		exit(1);
	}
}

void Client::connectClient()
{
	do
	{
		ZeroMemory(recvBuffer, 512);
		clientResult = recv(connectSocket, recvBuffer, 512, 0);
		if (clientResult > 0)
		{
			std::cout << "Recieved " << clientResult << "bytes" << std::endl;
			std::cout << "Recieved data: " << recvBuffer << std::endl;
		}
		else if (clientResult == 0)
		{
			std::cout << "Connection closed" << std::endl;
		}
		else 
		{
			std::cout << "recv failed with error" << std::endl;
		}
	} while (clientResult > 0);
	closesocket(connectSocket);
	freeaddrinfo(addrResult);
	WSACleanup();
	clientResult = 0;
	exit(0);
}

int Client::end()
{
	return clientResult;
}