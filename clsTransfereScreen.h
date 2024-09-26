#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsTransfereScreen : protected clsScreen
{
	static void _PrintClientCard(clsBankClient client)
	{
		cout << "\nClient Card:";
		cout << "\n-------------------------------------------\n";
		cout << "Full Name      : " << client.FullName() << endl;
		cout << "Account Number : " << client.AccountNumber << endl;
		cout << "Balance        : " << client.AccountBalance;
		cout << "\n-------------------------------------------\n";
	}

	static void _TransfereOperation(float amount, clsBankClient& source, clsBankClient& destination)
	{
		while (amount > source.AccountBalance)
		{
			cout << "\nAmount exceeds the available balance, Enter another amount? ";
			cin >> amount;
		}
		cout << "\nAre you sure you want to perform this operation? y/n? ";
		char ans = 'n';
		cin >> ans;
		if (tolower(ans) == 'y')
		{
			if (source.Transfere(amount, destination))
			{
				cout << "\nTransfere Done Successfully.\n";
			}
			else
			{
				cout << "\nTransfere Failed\n";
			}
			_PrintClientCard(source);
			_PrintClientCard(destination);
		}
		else
		{
			cout << "\nOperation was canceled.\n";
		}
	}

public:

	static void ShowTransfereScreen()
	{
		HeaderOfScreen("Transfere Screen");
		string AccountNumber = "";
		cout << "\nEnter Account Number to transfere from? ";
		AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount number is not exist, enter another one? ";
			AccountNumber = clsInputValidate::ReadString();
		}
		clsBankClient sourcClient = clsBankClient::Find(AccountNumber);
		_PrintClientCard(sourcClient);
		cout << "\nEnter Account Number to transfere to? ";
		AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount number is not exist, enter another one? ";
			AccountNumber = clsInputValidate::ReadString();
		}
		clsBankClient destinationClient = clsBankClient::Find(AccountNumber);
		_PrintClientCard(destinationClient);
		cout << "\nEnter transfere amount? ";
		float amount;
		cin >> amount;
		_TransfereOperation(amount, sourcClient, destinationClient);
	}
};

