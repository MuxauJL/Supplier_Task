#pragma once
#include "Transport_Network.h"

class Ford_Fulkerson
{
private:
	Transport_Network* network;
public:
	Ford_Fulkerson(Transport_Network* network = nullptr) :network(network) {}
	void setNetwork(Transport_Network* network) { this->network = network; }
	int findMaxFlow();
private:
	void stockWasReached(std::vector<Transport_Network_Node*>& nodes);
};

