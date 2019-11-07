#include <iostream>

int main() {
	/*HierarchicalStructure* hs = new HierarchicalStructure("1");
	Element* ch10 = new Element("2");
	ch10->add(new Element("3"));

	Element* ch11 = new Element("4");
	Element* ch110 = new Element("5");
	ch11->add(ch110);
	ch110->add(new Element("6")); ch110->add(new Element("7"));
	ch11->add(new Element("8"));
	Element* ch112 = new Element("9");
	ch11->add(ch112);

	Element* ch12 = new Element("10");
	ch12->add(new Element("11"));
	ch12->add(new Element("12"));

	hs->add(ch10);
	hs->add(ch11);
	hs->add(ch12);
	IIterator* it = hs->createIterator();
	it->reset();
	int k = 0;
	while (!it->isDone()) {
		if (++k == 3) ch112->add(new Element("9,5"));
		if (++k == 2) hs->add(new Element("3,5"));
		std::cout << it->getCurrent()->getStr() << "; ";
		it->moveNext();
	}
	std::cout << it->getCurrent()->getStr() << "; ";*/
	system("pause");
	return 0;
}