#include "Supplier_Task_with_Storage.h"
#include <numeric>

Supplier_Task_with_Storage::Supplier_Task_with_Storage(short int n, short int m, short int T,
	const std::vector<short int>& a, const std::vector<std::vector<short int>>& b,
	const std::vector<std::vector<short int>>& C, const std::vector<std::set<short int>>& D) :
	Supplier_Task(n, m, T, a, b, C, D), minStorage(U)
{}

void Supplier_Task_with_Storage::createTransportNetwork()
{
	Supplier_Task::createTransportNetwork();
	for (int i = 0; i < m; ++i)
		for (int t = 0; t < T - 1; ++t) {
			consumersPartial[i * T + t]->add(consumersPartial[i * T + t + 1], U / 2);
			consumersPartial[i * T + t + 1]->add(consumersPartial[i * T + t], 0);
		}
}

int Supplier_Task_with_Storage::solve()
{
	createTransportNetwork();
	int totalC = 0;
	for (int j = 0; j < m; ++j) 
		for (int t = 0; t < T; ++t) 
			totalC += C[j][t];
	
	int minW = 0;
	int maxW = U;
	int maxFlow;
	do{
		maxFlow = solver.findMaxFlow();
		if (totalC == maxFlow) {
			maxW -= (maxW - minW) / 2;
		}
		else {
			minW += (maxW - minW) / 2;
		}
		refreshNetwork();
		for (int i = 0; i < m; ++i)
			for (int t = 0; t < T - 1; ++t) {
				consumersPartial[i * T + t]->setSaturation(consumersPartial[i * T + t + 1], (maxW + minW) / 2);
				consumersPartial[i * T + t + 1]->setSaturation(consumersPartial[i * T + t], 0);
			}
	} while (maxW - minW != 1);
	for (int i = 0; i < m; ++i)
		for (int t = 0; t < T - 1; ++t) {
			consumersPartial[i * T + t]->setSaturation(consumersPartial[i * T + t + 1], maxW);
			consumersPartial[i * T + t + 1]->setSaturation(consumersPartial[i * T + t], 0);
		}
	minStorage = maxW;
	return solver.findMaxFlow();
}