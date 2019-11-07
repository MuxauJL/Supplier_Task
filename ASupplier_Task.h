#pragma once
#include <vector>
#include <set>
class ASupplier_Task
{
protected:
	int n, m, T;
	std::vector<int> a;
	std::vector<std::vector<int>> b;
	std::vector<std::vector<int>> C;
	std::set<int> D;
public:
	ASupplier_Task(int n, int m, int T,
		std::vector<int> a,	std::vector<std::vector<int>> b,
	std::vector<std::vector<int>> C, std::set<int> D);
};

