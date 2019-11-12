#pragma once
#include "Supplier_Task.h"
class Supplier_Task_with_Storage :
	public Supplier_Task
{
public:
	Supplier_Task_with_Storage(int n, int m, int T,
		const std::vector<int>& a, const std::vector<std::vector<int>>& b,
		const std::vector<std::vector<int>>& C, const std::vector<std::set<int>>& D);
	virtual int solve();
	int getMinStorage() { return minStorage; }
protected:
	virtual void createTransportNetwork();
private:
	int minStorage;
};

