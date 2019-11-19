#pragma once
#include <iostream>
#include "Ford_Fulkerson.h"
#include "Transport_Network.h"
#include "Supplier_Task.h"
#include "Supplier_Task_with_Storage.h"
#include "Supplier_Task_Controlling_Storages_Amount.h"
#include <fstream>
#include <numeric>

int main() {
	//Transport_Network* hs = new Transport_Network();
	//Transport_Network_Node* ch10 = new Transport_Network_Node("2");
	//ch10->add(new Transport_Network_Node("3"),0,0);

	//Transport_Network_Node* ch11 = new Transport_Network_Node("4");
	//Transport_Network_Node* ch110 = new Transport_Network_Node("5");
	//ch11->add(ch110,0,0);
	//ch110->add(new Transport_Network_Node("6"),0,0); ch110->add(new Transport_Network_Node("7"),0,0);
	//ch11->add(new Transport_Network_Node("8"),0,0);
	//Transport_Network_Node* ch112 = new Transport_Network_Node("9");
	//ch11->add(ch112,0,0);

	//Transport_Network_Node* ch12 = new Transport_Network_Node("10");
	//ch12->add(new Transport_Network_Node("11"),0,0);
	//ch12->add(new Transport_Network_Node("12"),0,0);

	//hs->add(ch10,0,0);
	//hs->add(ch11,0,0);
	//hs->add(ch12,0,0);
	//IIterator* it = hs->createIterator();
	//it->reset();
	//int k = 0;
	//while (!it->isDone()) {
	//	if (k == 3) ch112->add(new Transport_Network_Node("9,5"),0,0);
	//	if (k == 2) hs->add(new Transport_Network_Node("3,5"),0,0);
	//	//if (k == 5) ch11->remove();
	//	++k;
	//	if (k == 1) {
	//		ch112->add(hs->getStock(),0,0);
	//		hs->add(hs->getStock(), 0, 0);
	//		ch12->add(hs->getStock(), 0, 0);
	//	}
	//	std::cout << it->getCurrent()->getName() << "; ";
	//	it->moveNext();
	//}
	//std::cout << it->getCurrent()->getName() << "; ";


	Transport_Network_Node source("source");
	Transport_Network_Node stock("stock");
	Transport_Network* network = new Transport_Network(&source, &stock);
	Transport_Network_Node n2("2");
	Transport_Network_Node n3("3");
	Transport_Network_Node n4("4");
	Transport_Network_Node n5("5");
	Transport_Network_Node n6("6");
	Transport_Network_Node n7("7");
	Transport_Network_Node n8("8");
	Transport_Network_Node n9("9");
	n2.add(&n5, 2, 0);
	n5.add(&n8, 3, 0);
	n8.add(network->getStock(), 3, 0);
	n2.add(&n7, 2, 0);
	n7.add(network->getStock(), 4, 0);
	n3.add(&n6, 2, 0);
	n6.add(&n7, 3, 0);
	n4.add(&n6, 3, 0);
	n4.add(&n7, 3, 0);
	n6.add(&n9, 2, 0);
	n9.add(network->getStock(), 2, 0);
	source.add(&n2, 4, 0);
	source.add(&n3, 1, 0);
	source.add(&n4, 3, 0);

	Ford_Fulkerson solver;
	solver.setNetwork(std::unique_ptr<Transport_Network>(network));
	//std::cout << solver.findMaxFlow();

	IIterator* it = network->createIterator();
	it->reset();
	while (!it->isDone()) {
		std::cout << it->getCurrent()->getName() << "; ";
		it->moveNext();
	}
	std::cout << it->getCurrent()->getName() << ";\n\n";
	std::cout << "Maximal flow:\n" << solver.findMaxFlow() << '\n';

	std::string dir = "Task4\\";
	std::vector<std::string> files = {
		"task_4_01_n2_m2_T2.txt",
		"task_4_02_n2_m2_T2.txt",
		"task_4_03_n3_m2_T2.txt",
		"task_4_04_n3_m2_T2.txt",
		"task_4_05_n20_m15_T6.txt",
		"task_4_06_n20_m15_T6.txt",
		"task_4_07_n30_m15_T12.txt",
		"task_4_08_n30_m15_T12.txt",
		"task_4_09_n50_m20_T24.txt",
		"task_4_10_n50_m20_T24.txt"
	};

	int n, m, T;
	std::vector<int> a;
	std::vector<std::vector<int>> b;
	std::vector<std::vector<int>> C;
	std::vector<std::set<int>> D;

	for (size_t i = 0; i < files.size(); ++i) {
		std::ifstream in(dir + files[i]);
		if (in.is_open()) {
			in >> n >> m >> T;
			std::string mark;
			in >> mark;
			if (mark == "a:") {
				a.resize(n);
				for (int j = 0; j < n; ++j)
					in >> a[j];
			}
			in >> mark;
			if (mark == "b:") {
				b.resize(n);
				for (int j = 0; j < n; ++j) {
					b[j].resize(T);
					for (int t = 0; t < T; ++t)
						in >> b[j][t];
				}
			}
			in >> mark;
			int totalC = 0;
			if (mark == "c:") {
				C.resize(m);
				for (int j = 0; j < m; ++j) {
					C[j].resize(T);
					for (int t = 0; t < T; ++t) {
						in >> C[j][t];
						totalC += C[j][t];
					}
				}
			}
			in >> mark;
			if (mark == "D:") {
				D.resize(m);
				int value;
				in >> value;
				for (int j = 0; j < m;++j) {
					D[j].insert(value);
					int prev = value;
					in >> value;
					if (value > prev)
						--j;
				}
			}
			Supplier_Task defaultTask(n, m, T, a, b, C, D);
			std::cout << i + 1 << ")\nDefault:\n" << defaultTask.solve() <<
				", " << totalC << '\n';
			Supplier_Task_Controlling_Storages_Amount taskWithAllStorages(n, m, T, a, b, C, D);
			std::cout << "Everybody has a storage:\n" << taskWithAllStorages.solve() <<
				", " << totalC << ", " << taskWithAllStorages.getStorageAmount() << '\n';
			Supplier_Task_with_Storage taskWithMinimalStorageSize(n, m, T, a, b, C, D);
			std::cout << "Minimizing storage size:\n" << taskWithMinimalStorageSize.solve() <<
				", " << totalC << ", " << taskWithMinimalStorageSize.getMinStorage() << '\n';
			Supplier_Task_Controlling_Storages_Amount taskWithLimitedStorageAmountBasic(n, m, T, a, b, C, D, Supplier_Task_Controlling_Storages_Amount::Basic);
			std::cout << "Basic distribution of storages:\n" << taskWithLimitedStorageAmountBasic.solve() <<
				", " << totalC << ", "<< taskWithLimitedStorageAmountBasic.getStorageAmount() << '\n';
			Supplier_Task_Controlling_Storages_Amount taskWithLimitedStorageAmountMy(n, m, T, a, b, C, D, Supplier_Task_Controlling_Storages_Amount::My);
			std::cout << "My distribution of storages:\n" << taskWithLimitedStorageAmountMy.solve() <<
				", " << totalC << ", " << taskWithLimitedStorageAmountMy.getStorageAmount() << '\n';
		}
		in.close();
	}
	system("pause");
	return 0;
}