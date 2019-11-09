#pragma once
#include <iostream>
#include "Ford_Fulkerson.h"
#include "Transport_Network.h"

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
	//delete hs;
	Transport_Network_Node source("source");
	Transport_Network_Node stock("stock");
	Transport_Network network(&source, &stock);
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
	n8.add(network.getStock(), 3, 0);
	n2.add(&n7, 2, 0);
	n7.add(network.getStock(), 4, 0);
	n3.add(&n6, 2, 0);
	n6.add(&n7, 3, 0);
	n4.add(&n6, 3, 0);
	n4.add(&n7, 3, 0);
	n6.add(&n9, 2, 0);
	n9.add(network.getStock(), 2, 0);
	source.add(&n2, 4, 0);
	source.add(&n3, 1, 0);
	source.add(&n4, 3, 0);

	Ford_Fulkerson solver(&network);
	//std::cout << solver.findMaxFlow();

	IIterator* it = network.createIterator();
	it->reset();
	while (!it->isDone()) {
		std::cout << it->getCurrent()->getName() << "; ";
		it->moveNext();
	}
	std::cout << it->getCurrent()->getName() << ";\n";
	std::cout << solver.findMaxFlow();

	system("pause");
	return 0;
}