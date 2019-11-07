#pragma once
#include <stack>
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
		std::stack<IIterator*> stack;
	public:
		Transport_Network_Iterator(Transport_Network* n) :network(n) { reset(); };
		void reset() { current = network->source; };
		void moveNext();
		Transport_Network_Node* getCurrent() { return current; };
		bool isDone();
	};
	Transport_Network_Node* source;
	Transport_Network_Node* stock;
public:
	Transport_Network();
	~Transport_Network();
	Transport_Network_Iterator* createIterator() { return new Transport_Network_Iterator(this); };
	void add(Transport_Network_Node* node, int capacity, int currentFlow = 0);
	Transport_Network_Node* getStock() { return stock; }
	int calculateFlow();
};

