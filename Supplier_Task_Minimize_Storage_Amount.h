#pragma once
#include "Supplier_Task.h"
class Supplier_Task_Minimize_Storage_Amount :
	public Supplier_Task
{
public:
	Supplier_Task_Minimize_Storage_Amount(int n, int m, int T,
		const std::vector<int>& a, const std::vector<std::vector<int>>& b,
		const std::vector<std::vector<int>>& C, const std::vector<std::set<int>>& D);
	virtual int solve();
	int getStorageAmount();
protected:
	virtual void createTransportNetwork();
	virtual void refreshNetwork();
private:
	std::vector<bool> whoHasStorage;
};

