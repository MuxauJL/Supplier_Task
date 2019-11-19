#include "Ford_Fulkerson.h"
//#include <iostream>

int Ford_Fulkerson::findMaxFlow()
{
	std::vector<Transport_Network_Node*> nodes;
	IIterator* it = network->createIterator();
	it->reset();
	while (!it->isDone()) {
		auto current = it->getCurrent();
		//std::cout << current->getName() << ";\n";
		nodes.push_back(current);
		if (current == network->getStock()) {
			stockWasReached(nodes);
			//std::cout << '\n';
			nodes.clear();
			it->reset();
			continue;
		}
		it->moveNext();
	}
	nodes.push_back(it->getCurrent());
	if (nodes.back() == network->getStock())
		stockWasReached(nodes);
	
	return network->calculateFlow();
}

void Ford_Fulkerson::stockWasReached(std::vector<Transport_Network_Node*>& nodes)
{
	int min = INT_MAX;
	for (int i = nodes.size() - 2; i >= 0; --i) {
		auto it = nodes[i]->createIterator();
		if (it == nullptr) {
			nodes[i] = nullptr;
			continue;
		}
		it->reset();
		bool isReachable = false;
		int j;
		for (j = i + 1; nodes[j] == nullptr; ++j);
		while (!it->isDone()) {
			if (it->getCurrent() == nodes[j]) {
				isReachable = true;
				break;
			}
			it->moveNext();
		}
		/*if (it->getCurrent() == nodes[i + 1]) {
			isReachable = true;
		}*/
		if (!isReachable)
			nodes[i] = nullptr;
		else {
			int capacity = nodes[i]->getCapacity(nodes[j]);
			if (min > capacity)
				min = capacity;
		}
		delete it;
	}
	for (int i = 0; i < nodes.size() - 1; ++i)
		if (nodes[i] != nullptr) {
			int j;
			for (j = i + 1; nodes[j] == nullptr; ++j);
			nodes[i]->addFlow(nodes[j], min);
			i = j - 1;
		}
}
