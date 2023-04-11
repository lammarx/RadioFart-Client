#pragma once

#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <string>

class Client
{
public:
	Client();
	void connect();
private:
	std::ifstream config;
	sf::IpAddress server;
	sf::UdpSocket socket;
	unsigned short port;
	char in[128];
	size_t received;
	sf::IpAddress sender;
	unsigned short senderPort;
	const char* out;
};

