#include "Transport_Network.h"

void Transport_Network::Transport_Network_Iterator::reset()
{
	stack = std::stack<Transport_Network_Node::Transport_Network_Node_Iterator*>();
	current = network->source;
	visitedNodes.clear();
}

void Transport_Network::Transport_Network_Iterator::moveNext()
{
	Transport_Network_Node::Transport_Network_Node_Iterator* it = current->createIterator(&visitedNodes);
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
		if (visitedNodes.find(it->getCurrent()) == visitedNodes.end()) {
			stack.push(it);
			visitedNodes.insert(current);
			it->moveNext();
		}
		else
			delete it;
	}
}

bool Transport_Network::Transport_Network_Iterator::isDone()
{
	while (stack.size() != 0 && stack.top()->isDone()) {
		delete stack.top();
		stack.pop();
	}
	if (stack.size() != 0)return false;
	IIterator* it = current->createIterator(&visitedNodes);
	if (it == nullptr)
		return true;	
	else {
		delete it;
		return false;
	}
}

Transport_Network::Transport_Network(Transport_Network_Node* source, Transport_Network_Node* stock) :
	source(source), stock(stock)
{}

int Transport_Network::calculateFlow()
{
	return source->calculateTotalFlow();
}
