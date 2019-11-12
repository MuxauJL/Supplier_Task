#include "Transport_Network_Node.h"
#include <stdexcept>

Transport_Network_Node::Transport_Network_Node_Iterator* Transport_Network_Node::createIterator()
{
	for (int i = 0; i < children.size(); ++i)
		if (saturations[i].capacity > 0)
			return new Transport_Network_Node_Iterator(this);
	return nullptr;
}

void Transport_Network_Node::add(Transport_Network_Node* node, int capacity, int flow)
{
	children.push_back(node);
	saturations.push_back(Saturation(capacity, flow));
}

void Transport_Network_Node::setSaturation(Transport_Network_Node* child, int capacity, int flow)
{
	for (int i = 0; i < children.size(); ++i)
		if (children[i] == child) {
			saturations[i].capacity = capacity;
			saturations[i].flow = flow;
			return;
		}
}

int Transport_Network_Node::getCapacity(Transport_Network_Node* child)
{
	for (int i = 0; i < children.size(); ++i)
		if (children[i] == child)
			return saturations[i].capacity;
	return -1;
}

int Transport_Network_Node::getFlow(Transport_Network_Node* child)
{
	for (int i = 0; i < children.size(); ++i)
		if (children[i] == child)
			return saturations[i].flow;
	return -1;
}

void Transport_Network_Node::addFlow(Transport_Network_Node* child, int additionalFlow)
{
	for (int i = 0; i < children.size(); ++i)
		if (children[i] == child) {
			saturations[i].capacity -= additionalFlow;
			if (saturations[i].capacity < 0)
				throw std::invalid_argument("Too much additionalFlow: capacity < 0");
			saturations[i].flow += additionalFlow;
		}
}

int Transport_Network_Node::calculateTotalFlow()
{
	int totalFlow = 0;
	for (auto s : saturations)
		totalFlow += s.flow;
	return totalFlow;
}

Transport_Network_Node* Transport_Network_Node::Transport_Network_Node_Iterator::getCurrent()
{
	return node->children[currentChild];
}

bool Transport_Network_Node::Transport_Network_Node_Iterator::isDone()
{
	bool answer = currentChild >= node->children.size() ? true : false;
	if (answer)
		return true;
	for (int i = currentChild; i < node->children.size(); ++i)
		if (node->saturations[i].capacity > 0)
			return false;
	return true;
}
