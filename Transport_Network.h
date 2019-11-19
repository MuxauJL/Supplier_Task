#pragma once
#include <stack>
#include <set>
#include "Transport_Network_Node.h"

class Transport_Network
{
private:
	class Transport_Network_Iterator
		:public IIterator
	{
	private:
		Transport_Network* network;
		Transport_Network_Node* current;
		std::stack<Transport_Network_Node::Transport_Network_Node_Iterator*> stack;
		std::set< Transport_Network_Node*> visitedNodes;
	public:
		Transport_Network_Iterator(Transport_Network* n) :network(n) { reset(); };
		void reset();
		void moveNext();
		Transport_Network_Node* getCurrent() { return current; };
		bool isDone(); // false - if there is next
	};
	Transport_Network_Node* source;
	Transport_Network_Node* stock;
public:
	Transport_Network(Transport_Network_Node* source = nullptr, Transport_Network_Node* stock = nullptr);
	Transport_Network_Iterator* createIterator() { return new Transport_Network_Iterator(this); };
	void setSource(Transport_Network_Node* s) { source = s; }
	void setStock(Transport_Network_Node* st) { stock = st; }
	Transport_Network_Node* getSource() { return source; }
	Transport_Network_Node* getStock() { return stock; }
	int calculateFlow();
};

