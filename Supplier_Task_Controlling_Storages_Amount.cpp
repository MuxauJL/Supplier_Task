#include "Supplier_Task_Controlling_Storages_Amount.h"
#include <algorithm>
#include <numeric>

Supplier_Task_Controlling_Storages_Amount::Supplier_Task_Controlling_Storages_Amount(short int n, short int m, short int T,
	const std::vector<short int>& a, const std::vector<std::vector<short int>>& b,
	const std::vector<std::vector<short int>>& C, const std::vector<std::set<short int>>& D, Storages_Distributing_Strategy strategyID) :
Supplier_Task(n, m, T, a, b, C, D)
{
	switch(strategyID){
	case Everybody:
		strategy = new Storages_for_Everybody_Strategy;
		break;
	case Basic:
		strategy = new Basic_Choosing_Strategy;
		break;
	case My:	
		strategy = new My_Choosing_Strategy;
		break;
	default:
		strategy = new Storages_for_Everybody_Strategy;
		break;
	}
}

Supplier_Task_Controlling_Storages_Amount::~Supplier_Task_Controlling_Storages_Amount()
{
	delete strategy;
}

void Supplier_Task_Controlling_Storages_Amount::createTransportNetwork()
{
	Supplier_Task::createTransportNetwork();
	whoHasStorage.resize(m, true);
	for (int i = 0; i < m; ++i) 
		for (int t = 0; t < T - 1; ++t) {
			consumersPartial[i * T + t]->add(consumersPartial[i * T + t + 1], U);
			consumersPartial[i * T + t + 1]->add(consumersPartial[i * T + t], 0);
		}
}

void Supplier_Task_Controlling_Storages_Amount::refreshNetwork()
{
	Supplier_Task::refreshNetwork();
	int capacity;
	for (int i = 0; i < m; ++i) {
		if (whoHasStorage[i])
			capacity = U;
		else
			capacity = 0;
		for (int t = 0; t < T - 1; ++t) {
			consumersPartial[i * T + t]->setSaturation(consumersPartial[i * T + t + 1], capacity);
			consumersPartial[i * T + t + 1]->setSaturation(consumersPartial[i * T + t], 0);
		}
	}
}

int Supplier_Task_Controlling_Storages_Amount::solve()
{
	createTransportNetwork();
	strategy->distributeStorages(this);
	refreshNetwork();
	return solver.findMaxFlow();
}

int Supplier_Task_Controlling_Storages_Amount::getStorageAmount()
{
	return std::count(whoHasStorage.begin(), whoHasStorage.end(), true);
}

void Supplier_Task_Controlling_Storages_Amount::Storages_for_Everybody_Strategy::distributeStorages(Supplier_Task_Controlling_Storages_Amount* context)
{
	context->whoHasStorage.resize(context->m, true);
}

void Supplier_Task_Controlling_Storages_Amount::Basic_Choosing_Strategy::distributeStorages(Supplier_Task_Controlling_Storages_Amount* context)
{
	int totalC = 0;
	for (int j = 0; j < context->m; ++j)
		for (int t = 0; t < context->T; ++t)
			totalC += context->C[j][t];
	int current = 0;
	int maxFlow;
	while (current < context->m) {
		context->whoHasStorage[current] = false;
		context->refreshNetwork();
		maxFlow = context->solver.findMaxFlow();
		if (totalC != maxFlow)
			context->whoHasStorage[current] = true;
		++current;
	}
}

void Supplier_Task_Controlling_Storages_Amount::My_Choosing_Strategy::distributeStorages(Supplier_Task_Controlling_Storages_Amount* context)
{
	int m = context->m;
	std::vector<int> indexes;
	indexes.reserve(m);
	for (int i = 0; i < m; ++i)
		indexes.push_back(i);
	// sort by increasing amount of consumption
	auto comp = [&context](const int& idx1, const int& idx2) {
		auto consumption_1 = std::accumulate(context->C[idx1].begin(), context->C[idx1].end(), 0);
		auto consumption_2 = std::accumulate(context->C[idx2].begin(), context->C[idx2].end(), 0);
		return consumption_1 <= consumption_2;
	};
	std::sort(indexes.begin(), indexes.end(), comp);

	int totalC = 0;
	for (int j = 0; j < m; ++j)
		for (int t = 0; t < context->T; ++t)
			totalC += context->C[j][t];

	int current = 0;
	int maxFlow;
	while (current < m) {
		context->whoHasStorage[indexes[current]] = false;
		context->refreshNetwork();
		maxFlow = context->solver.findMaxFlow();
		if (totalC != maxFlow)
			context->whoHasStorage[indexes[current]] = true;
		++current;
	}
}
