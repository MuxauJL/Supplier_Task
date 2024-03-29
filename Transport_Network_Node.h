#pragma once
#include <vector>
#include <string>
#include <set>
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
		int flow;
		Saturation(int c, int f) :
			capacity(c), flow(f) {};
	};
	std::string name;
	std::vector<Transport_Network_Node*> children;
	std::vector<Saturation> saturations;
	Transport_Network_Node* previous;
public:
	class Transport_Network_Node_Iterator
		:public IIterator
	{
	private:
		Transport_Network_Node* node;
		int currentChild;
		std::set<Transport_Network_Node*>* visitedNodes;
	public:
		Transport_Network_Node_Iterator(Transport_Network_Node* node, std::set<Transport_Network_Node*>* visitedNodes = nullptr);
		void reset() { currentChild = 0; };
		void moveNext() { ++currentChild; };
		Transport_Network_Node* getCurrent();
		bool isDone(); // false - if you can take the current
		Transport_Network_Node* getNode() { return node; }
	};
	Transport_Network_Node(std::string name) :name(name), previous(nullptr) {}
	std::string getName() { return name; };
	Transport_Network_Node_Iterator* createIterator(std::set<Transport_Network_Node*>* visited = nullptr);
	void add(Transport_Network_Node* node, int capacity, int flow = 0);
	void setSaturation(Transport_Network_Node* node, int capacity, int flow = 0);
	int getCapacity(Transport_Network_Node* child);
	int getFlow(Transport_Network_Node* child);
	Transport_Network_Node* getPrevious() { return previous; }
	void setPrevious(Transport_Network_Node* prev) { previous = prev; }
	void addFlow(Transport_Network_Node* child, int additionalFlow);
	int calculateTotalFlow();
};

