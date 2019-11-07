#include "Ford_Fulkerson.h"

int Ford_Fulkerson::findMaxFlow()
{
	std::vector<Transport_Network_Node*> nodes;
	IIterator* it = network->createIterator();
	it->reset();
	while (!it->isDone()) {
		auto current = it->getCurrent();
		nodes.push_back(current);
		if (current == network->getStock()) {
			stockWasReached(nodes);
			nodes.clear();
			it->reset();
			continue;
		}
		it->moveNext();
	}
	nodes.push_back(it->getCurrent());
	if(nodes.back()== network->getStock())
		stockWasReached(nodes);

	return network->calculateFlow();
}

void Ford_Fulkerson::stockWasReached(std::vector<Transport_Network_Node*>& nodes)
{
	int min = INT_MAX;
	for (int i = nodes.size() - 2; i > 0; --i) {
		auto itr = nodes[i]->createIterator();
		itr->reset();
		bool isReachable = false;
		while (!itr->isDone()) {
			if (itr->getCurrent() == nodes[i + 1]) {
				isReachable = true;
				break;
			}
			itr->moveNext();
		}
		if (itr->getCurrent() == nodes[i + 1]) {
			isReachable = true;
		}
		if (!isReachable)
			nodes[i] = nullptr;
		else {
			int capacity = nodes[i]->getCapacity(nodes[i + 1]);
			if (min > capacity)
				min = capacity;
		}
	}
	for (int i = 0; i < nodes.size() - 1; ++i)
		if (nodes[i] != nullptr) {
			int j;
			for (j = i + 1; nodes[j] == nullptr; ++j);
			nodes[i]->addFlow(nodes[j], min);
			i = j - 1;
		}
}
