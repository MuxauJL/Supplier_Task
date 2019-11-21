#include "Supplier_Task.h"
#include <numeric>

Supplier_Task::Supplier_Task(short int n, short int m, short int T,
	const std::vector<short int>& a, const std::vector<std::vector<short int>>& b,
	const std::vector<std::vector<short int>>& C, const std::vector<std::set<short int>>& D) :
	n(n), m(m), T(T), a(a), b(b), C(C), D(D)
{
	U = std::accumulate(a.begin(), a.end(), 0);
}

Supplier_Task::~Supplier_Task()
{
	for (auto s : suppliersTotal)
		delete s;
	for (auto s : suppliersPartial)
		delete s;
	for (auto c : consumersPartial)
		delete c;
	delete source;
	delete stock;
}

void Supplier_Task::createTransportNetwork()
{
	source = new Transport_Network_Node("source");
	stock = new Transport_Network_Node("stock");
	suppliersTotal.reserve(n);
	for (int i = 0; i < n; ++i) {
		suppliersTotal.emplace_back(new Transport_Network_Node("supplier_" + std::to_string(i)));
		source->add(suppliersTotal.back(), a[i]);
	}
	suppliersTotal.reserve(n * T);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < T; ++j) {
			suppliersPartial.emplace_back(new Transport_Network_Node("supplier_" + std::to_string(i) + "_tact_" + std::to_string(j)));
			suppliersTotal[i]->add(suppliersPartial.back(), b[i][j]);
			suppliersPartial.back()->add(suppliersTotal[i], 0, 0);
		}
	consumersPartial.reserve(m * T);
	for (int i = 0; i < m; ++i)
		for (int j = 0; j < T; ++j) {
			consumersPartial.emplace_back(new Transport_Network_Node("consumer_" + std::to_string(i) + "_tact_" + std::to_string(j)));
			for (auto suppl : D[i]) {
				suppliersPartial[(suppl - 1) * T + j]->add(consumersPartial.back(), U);
				consumersPartial.back()->add(suppliersPartial[(suppl - 1) * T + j], 0, 0);
			}
			consumersPartial.back()->add(stock, C[i][j]);
		}
	std::unique_ptr<Transport_Network> network = 
		std::unique_ptr<Transport_Network>(new Transport_Network(source, stock));
	solver.setNetwork(std::move(network));
}

int Supplier_Task::solve()
{
	createTransportNetwork();
	return solver.findMaxFlow();
}

void Supplier_Task::refreshNetwork()
{
	for (int i = 0; i < n; ++i) {
		source->setSaturation(suppliersTotal[i], a[i]);
		for (int j = 0; j < T; ++j) {
			suppliersTotal[i]->setSaturation(suppliersPartial[i * T + j], b[i][j]);
			suppliersPartial[i * T + j]->setSaturation(suppliersTotal[i], 0);
		}
	}

	for (int i = 0; i < m; ++i)
		for (int t = 0; t < T; ++t) {
			for (auto suppl : D[i]) {
				suppliersPartial[(suppl - 1) * T + t]->setSaturation(consumersPartial[i * T + t], U);
				consumersPartial[i * T + t]->setSaturation(suppliersPartial[(suppl - 1) * T + t], 0);
			}
			consumersPartial[i * T + t]->setSaturation(stock, C[i][t]);
		}
}
