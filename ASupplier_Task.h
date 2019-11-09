#pragma once
#include <vector>
#include <set>
#include "Ford_Fulkerson.h"

class ASupplier_Task
{
protected:
	int n, m, T;
	std::vector<int> a;
	std::vector<std::vector<int>> b;
	std::vector<std::vector<int>> C;
	std::vector<std::set<int>> D;
	Ford_Fulkerson solver;
	std::vector<Transport_Network_Node*> suppliersTotal;
	std::vector<Transport_Network_Node*> suppliersPartial;
	std::vector<Transport_Network_Node*> consumers;
	virtual void createTransportNetwork();
public:
	ASupplier_Task(int n, int m, int T,
		std::vector<int> a,	std::vector<std::vector<int>> b,
	std::vector<std::vector<int>> C, std::vector<std::set<int>> D);
	~ASupplier_Task();
	void solve();
};