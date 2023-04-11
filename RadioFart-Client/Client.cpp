#include "Client.h"

Client::Client()
{
	std::string line;
	for (size_t i = 0; std::getline(config, line); i++)
	{
		if (i == 0) server = line;
		else if (i == 1) port = std::stoi(line);
	}
	out = "Client connected!";
}

void Client::connect()
{
	if (socket.receive(in, sizeof(in), received, sender, senderPort) != sf::Socket::Done)
		return;
	std::cout << "Message received from " << sender << ": \"" << in << "\"" << std::endl;
}
