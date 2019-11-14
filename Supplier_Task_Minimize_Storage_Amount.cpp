#include "Supplier_Task_Minimize_Storage_Amount.h"

Supplier_Task_Minimize_Storage_Amount::Supplier_Task_Minimize_Storage_Amount(int n, int m, int T,
const std::vector<int>& a, const std::vector<std::vector<int>>& b,
const std::vector<std::vector<int>>& C, const std::vector<std::set<int>>& D) :
Supplier_Task(n, m, T, a, b, C, D)
{}

void Supplier_Task_Minimize_Storage_Amount::createTransportNetwork()
{
	Supplier_Task::createTransportNetwork();
	whoHasStorage.resize(m, true);
	for (int i = 0; i < m; ++i) 
		for (int t = 0; t < T - 1; ++t)
			consumersPartial[i * T + t]->add(consumersPartial[i * T + t + 1], U);
}

void Supplier_Task_Minimize_Storage_Amount::refreshNetwork()
{
	Supplier_Task::refreshNetwork();
	int capacity;
	for (int i = 0; i < m; ++i) {
		if (whoHasStorage[i])
			capacity = U;
		else
			capacity = 0;
		for (int t = 0; t < T - 1; ++t)
			consumersPartial[i * T + t]->setSaturation(consumersPartial[i * T + t + 1], capacity);
	}
}

int Supplier_Task_Minimize_Storage_Amount::solve()
{
	createTransportNetwork();
	int totalC = 0;
	for (int j = 0; j < m; ++j)
		for (int t = 0; t < T; ++t)
			totalC += C[j][t];

	int current = 0;
	int maxFlow;
	while (current < m) {
		whoHasStorage[current] = false;
		refreshNetwork();
		maxFlow = solver.findMaxFlow();
		if (totalC != maxFlow) 
			whoHasStorage[current] = true;
		++current;
	};
	refreshNetwork();
	return solver.findMaxFlow();
}

int Supplier_Task_Minimize_Storage_Amount::getStorageAmount()
{
	return std::count(whoHasStorage.begin(), whoHasStorage.end(), true);
}
