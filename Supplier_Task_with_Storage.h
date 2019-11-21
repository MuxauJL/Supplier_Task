#pragma once
#include "Supplier_Task.h"
class Supplier_Task_with_Storage :
	public Supplier_Task
{
public:
	Supplier_Task_with_Storage(short int n, short int m, short int T,
		const std::vector<short int>& a, const std::vector<std::vector<short int>>& b,
		const std::vector<std::vector<short int>>& C, const std::vector<std::set<short int>>& D);
	virtual int solve();
	int getMinStorage() { return minStorage; }
protected:
	virtual void createTransportNetwork();
private:
	int minStorage;
};

