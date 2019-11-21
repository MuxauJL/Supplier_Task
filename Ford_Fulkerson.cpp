#include "Ford_Fulkerson.h"
//#include <iostream>

int Ford_Fulkerson::findMaxFlow()
{
	IIterator* it = network->createIterator();
	it->reset();
	while (!it->isDone()) {
		auto current = it->getCurrent();
		//std::cout << current->getName() << ";\n";
		if (current == network->getStock()) {
			stockWasReached();
			//std::cout << '\n';
			it->reset();
			continue;
		}
		it->moveNext();
	}
	if (it->getCurrent() == network->getStock())
		stockWasReached();
	
	delete it;
	return network->calculateFlow();
}

void Ford_Fulkerson::stockWasReached()
{
	auto cur = network->getStock();
	int min = INT_MAX;
	while (cur != network->getSource()) {
		if (min > cur->getPrevious()->getCapacity(cur))
			min = cur->getPrevious()->getCapacity(cur);
		cur = cur->getPrevious();
	}

	cur = network->getStock();	
	while (cur != network->getSource()) {
		cur->getPrevious()->addFlow(cur, min);
		cur = cur->getPrevious();
	}
}
