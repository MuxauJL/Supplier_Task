#include "Transport_Network.h"

void Transport_Network::Transport_Network_Iterator::reset()
{
	stack = std::stack<Transport_Network_Node::Transport_Network_Node_Iterator*>();
	current = network->source;
}

void Transport_Network::Transport_Network_Iterator::moveNext()
{
	Transport_Network_Node::Transport_Network_Node_Iterator* it = current->createIterator();
	if (it == nullptr) {
		it = stack.top();
		while (!it->isDone() && it->getNode()->getCapacity(it->getCurrent()) == 0) {
			it->moveNext();
		}
		current = it->getCurrent();
		it->moveNext();
	}
	else {
		it->reset();
		while (!it->isDone() && current->getCapacity(it->getCurrent()) == 0) {
			it->moveNext();
		}
		current = it->getCurrent();
		stack.push(it);
		it->moveNext();
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

Transport_Network::Transport_Network(Transport_Network_Node* source, Transport_Network_Node* stock) :
	source(source), stock(stock)
{}

int Transport_Network::calculateFlow()
{
	return source->calculateTotalFlow();
}
