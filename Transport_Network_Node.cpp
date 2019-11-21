#include "Transport_Network_Node.h"
#include <stdexcept>


Transport_Network_Node::Transport_Network_Node_Iterator::Transport_Network_Node_Iterator(Transport_Network_Node* node, std::set<Transport_Network_Node*>* visitedNodes)
	:node(node), currentChild(0), visitedNodes(visitedNodes) {};

Transport_Network_Node::Transport_Network_Node_Iterator* Transport_Network_Node::createIterator(std::set<Transport_Network_Node*>* visited)
{
	auto it = new Transport_Network_Node_Iterator(this, visited);
	it->reset();
	while (!it->isDone()) {
		auto current = it->getCurrent();
		if (getCapacity(current) > 0) {
			if (visited != nullptr
				&& visited->find(current) != visited->end()) {
				it->moveNext();
				continue;
			}
			return it;
		}
		it->moveNext();
	}
	delete it;
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

			auto capacity = child->getCapacity(this);
			//auto flow = child->getFlow(this);
			child->setSaturation(this, capacity + additionalFlow, -saturations[i].flow/*flow - additionalFlow*/);
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
		if (node->saturations[i].capacity > 0) {
			if (visitedNodes != nullptr &&
				visitedNodes->find(node->children[i]) != visitedNodes->end())
				continue;
			currentChild = i;
			return false;
		}
	return true;
}
