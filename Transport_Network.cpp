#include "Transport_Network.h"

void Transport_Network::Transport_Network_Iterator::reset()
{
	stack = std::stack<Transport_Network_Node::Transport_Network_Node_Iterator*>();
	current = network->source;
	visitedNodes.clear();
}

void Transport_Network::Transport_Network_Iterator::moveNext()
{
	visitedNodes.insert(current);
	Transport_Network_Node::Transport_Network_Node_Iterator* it = current->createIterator(&visitedNodes);
	if (it == nullptr) {
		it = stack.top();
		current = it->getCurrent();
		it->moveNext();
	}
	else {
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
