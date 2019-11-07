#include "Transport_Network.h"

void Transport_Network::Transport_Network_Iterator::moveNext()
{
	if (stack.size() == 0) {
		IIterator* it = current->createIterator();
		it->reset();
		stack.push(it);
		current = it->getCurrent();
		it->moveNext();
	}
	else {
		IIterator* it = current->createIterator();
		if (it == nullptr) {
			current = stack.top()->getCurrent();
			stack.top()->moveNext();
		}
		else {
			it->reset();
			stack.push(it);
			current = it->getCurrent();
			it->moveNext();
		}
	}
}

bool Transport_Network::Transport_Network_Iterator::isDone()
{
	while (stack.size() != 0 && stack.top()->isDone()) {
		delete stack.top();
		stack.pop();
	}
	if (stack.size() != 0)return false;
	IIterator* it = current->createIterator();
	if (it != nullptr) {
		delete it;
		return false;
	}
	else
		return true;
}

Transport_Network::Transport_Network()
{
	source = new Transport_Network_Node("source");
	stock  = new Transport_Network_Node("stock");
}

Transport_Network::~Transport_Network()
{
	delete stock;
	delete source;
}

void Transport_Network::add(Transport_Network_Node* node, int capacity, int currentFlow)
{
	source->add(node, capacity, currentFlow);
}

int Transport_Network::calculateFlow()
{
	int flow = 0;
	auto it = source->createIterator();
	it->reset();
	while (!it->isDone()) {
		auto current = it->getCurrent();
		flow+=source->getFlow(current);
		it->moveNext();
	}
	flow += source->getFlow(it->getCurrent());
	return flow;
}
