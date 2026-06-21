#pragma once
#include <iostream>
using namespace std;

template<typename T>
class BankAccount
{
private:
	int accNum;
	T balance;

public:
	BankAccount(int n = 0, T bal = 0)
	{
		accNum = n;
		balance = bal;
	}

	T deposite(T amount)
	{
		balance += amount;
		return balance;
	}
	T withdraw(T amount)
	{
		balance -= amount;
		return balance;
	}

	void display()
	{
		cout << "Account Num: " << accNum << endl << "Balance: " << balance << endl << endl;
	}
};