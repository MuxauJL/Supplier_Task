#include "ASupplier_Task.h"
#include <numeric>

ASupplier_Task::ASupplier_Task(int n, int m, int T,
	std::vector<int> a, std::vector<std::vector<int>> b,
	std::vector<std::vector<int>> C, std::vector<std::set<int>> D) :
	n(n), m(m), T(T), a(a), b(b), C(C), D(D)
{}

ASupplier_Task::~ASupplier_Task()
{
	for (auto s : suppliersTotal)
		delete s;
	for (auto s : suppliersPartial)
		delete s;
	for (auto c : consumers)
		delete c;
}

void ASupplier_Task::createTransportNetwork()
{
	Transport_Network_Node* source = new Transport_Network_Node("source");
	Transport_Network_Node* stock = new Transport_Network_Node("stock");
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
		}
	int U = std::accumulate(a.begin(), a.end(), 0);
	consumers.reserve(m * T);
	for (int i = 0; i < m; ++i)
		for (int j = 0; j < T; ++j) {
			consumers.emplace_back(new Transport_Network_Node("consumer_" + std::to_string(i) + "_tact_" + std::to_string(j)));
			for (auto suppl : D[i]) {
				suppliersPartial[suppl * T + j]->add(consumers.back(), U);
			}
			consumers.back()->add(stock, C[i][j]);
		}
	Transport_Network* network = new Transport_Network(source, stock);
	solver.setNetwork(network);
}

void ASupplier_Task::solve()
{
	createTransportNetwork();
}
