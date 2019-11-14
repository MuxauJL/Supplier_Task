#pragma once
#include "Supplier_Task.h"

class Supplier_Task_Controlling_Storages_Amount :
	public Supplier_Task
{
public:
	enum Storages_Distributing_Strategy {
		Everybody,
		Basic,
		My
	};
	Supplier_Task_Controlling_Storages_Amount(int n, int m, int T,
		const std::vector<int>& a, const std::vector<std::vector<int>>& b,
		const std::vector<std::vector<int>>& C, const std::vector<std::set<int>>& D, Storages_Distributing_Strategy strategy = Everybody);
	~Supplier_Task_Controlling_Storages_Amount();
	virtual int solve();
	int getStorageAmount();
protected:
	virtual void createTransportNetwork();
	virtual void refreshNetwork();
private:
	std::vector<bool> whoHasStorage;
	class IMinimize_Storage_Amount_Strategy
	{
	public:
		virtual void distributeStorages(Supplier_Task_Controlling_Storages_Amount* context) = 0;
	};
	IMinimize_Storage_Amount_Strategy* strategy;

	class Storages_for_Everybody_Strategy
		:public IMinimize_Storage_Amount_Strategy
	{
	public:
		virtual void distributeStorages(Supplier_Task_Controlling_Storages_Amount* context);
	};

	class Basic_Choosing_Strategy
		:public IMinimize_Storage_Amount_Strategy
	{
	public:
		virtual void distributeStorages(Supplier_Task_Controlling_Storages_Amount* context);
	};

	class My_Choosing_Strategy
		:public IMinimize_Storage_Amount_Strategy
	{
	public:
		virtual void distributeStorages(Supplier_Task_Controlling_Storages_Amount* context);
	};
};

