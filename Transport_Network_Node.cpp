#include "Transport_Network_Node.h"
#include <stdexcept>

void Transport_Network_Node::add(Transport_Network_Node* node, int capacity, int flow)
{
	children.push_back(node);
	saturations.push_back(Saturation(capacity, flow));
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

bool Transport_Network_Node::Transport_Network_Node_Iterator::isDone()
{
	bool answer = true;
	for (int i = 0; i < node->children.size(); ++i)
		if (node->saturations[i].capacity > 0)
			answer = false;
	return answer;
}
