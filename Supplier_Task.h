#pragma once
#include <vector>
#include <set>
#include "Ford_Fulkerson.h"

class Supplier_Task
{
protected:
	int n, m, T, U;
	std::vector<int> a;
	std::vector<std::vector<int>> b;
	std::vector<std::vector<int>> C;
	std::vector<std::set<int>> D;
	Ford_Fulkerson solver;
	std::vector<Transport_Network_Node*> suppliersTotal;
	std::vector<Transport_Network_Node*> suppliersPartial;
	std::vector<Transport_Network_Node*> consumersPartial;
	Transport_Network_Node* source;
	Transport_Network_Node* stock;
	virtual void createTransportNetwork();
	virtual void refreshNetwork();
public:
	Supplier_Task(int n, int m, int T,
		const std::vector<int>& a,	const std::vector<std::vector<int>>& b,
	const std::vector<std::vector<int>>& C, const std::vector<std::set<int>>& D);
	~Supplier_Task();
	virtual int solve();
};