#pragma once
#include <vector>
#include <set>
#include "Ford_Fulkerson.h"

class Supplier_Task
{
protected:
	short int n, m, T;
	int U;
	std::vector<short int> a;
	std::vector<std::vector<short int>> b;
	std::vector<std::vector<short int>> C;
	std::vector<std::set<short int>> D;
	Ford_Fulkerson solver;
	std::vector<Transport_Network_Node*> suppliersTotal;
	std::vector<Transport_Network_Node*> suppliersPartial;
	std::vector<Transport_Network_Node*> consumersPartial;
	Transport_Network_Node* source;
	Transport_Network_Node* stock;
	virtual void createTransportNetwork();
	virtual void refreshNetwork();
public:
	Supplier_Task(short int n, short int m, short int T,
		const std::vector<short int>& a, const std::vector<std::vector<short int>>& b,
		const std::vector<std::vector<short int>>& C, const std::vector<std::set<short int>>& D);
	~Supplier_Task();
	virtual int solve();
};