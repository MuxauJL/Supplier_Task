#include "Transport_Network_Node.h"

void Transport_Network_Node::add(Transport_Network_Node* node, int capacity, int currentFlow)
{
	children.push_back(node);
	saturations.push_back(Saturation(capacity, currentFlow));
}
