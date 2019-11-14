#pragma once
#include "Transport_Network.h"
#include <memory>

class Ford_Fulkerson
{
private:
	std::unique_ptr<Transport_Network> network;
public:
	Ford_Fulkerson(std::unique_ptr<Transport_Network> network = nullptr) :network(std::move(network)) {}
	void setNetwork(std::unique_ptr<Transport_Network> network) { this->network = std::move(network); }
	int findMaxFlow();
private:
	void stockWasReached(std::vector<Transport_Network_Node*>& nodes);
};

