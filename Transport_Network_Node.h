#pragma once
#include <vector>
#include <string>
class Transport_Network_Node;

class IIterator {
public:
	virtual void reset() = 0;
	virtual void moveNext() = 0;
	virtual Transport_Network_Node* getCurrent() = 0;
	virtual bool isDone() = 0;
};

class Transport_Network_Node
{
private:
	struct Saturation {
		int capacity;
		int currentFlow;
		Saturation(int c, int f) :
			capacity(c), currentFlow(f) {};
	};
	std::string name;
	std::vector<Transport_Network_Node*> children;
	std::vector<Saturation> saturations;
	class Node_Iterator
		:public IIterator
	{
	private:
		Transport_Network_Node* node;
		int currentChild;
	public:
		Node_Iterator(Transport_Network_Node* node) :node(node) {};
		void reset() { currentChild = 0; };
		void moveNext() { ++currentChild; };
		Transport_Network_Node* getCurrent() { return node->children[currentChild]; };
		bool isDone() { return currentChild == node->children.size() ? true : false; };
	};
public:
	Transport_Network_Node(std::string name) :name(name) {};
	std::string getName() { return name; };
	Node_Iterator* createIterator() { if (children.size() == 0)return nullptr; else return new Node_Iterator(this); };
	void add(Transport_Network_Node* node, int capacity, int currentFlow);
	//void remove(Node* e){}
};

