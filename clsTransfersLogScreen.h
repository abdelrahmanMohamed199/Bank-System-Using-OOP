#pragma once
#include "clsScreen.h"
#include "clsString.h"
#include "iomanip"

class clsTransfersLogScreen : protected clsScreen
{
	static void _PrintTransRecordData(clsBankClient::stTransferLog transferLog)
	{		
		cout << "\t| " << left << setw(25) << transferLog.dateTime;
		cout << "| " << left << setw(10) << transferLog.sourceAccNum;
		cout << "| " << left << setw(10) << transferLog.destinationAccNum;
		cout << "| " << left << setw(10) << transferLog.amount;
		cout << "| " << left << setw(10) << transferLog.sourceBalance;
		cout << "| " << left << setw(10) << transferLog.destinationBalance;
		cout << "| " << left << setw(10) << transferLog.username;
	}

public:

	static void ShowTransfersLogScreen()
	{
		vector<clsBankClient::stTransferLog> vTransferLogData = clsBankClient::LoadTransfersLogListFromFile("TransferLog.txt");
		string subtitle = "(" + to_string(vTransferLogData.size()) + ") Record(s).";
		HeaderOfScreen("Transfer Log List Screen", subtitle);
		cout << "\n\t------------------------------------------------";
		cout << "---------------------------------------------------\n";
		cout << "\t| " << left << setw(25) << "Date/Time";
		cout << "| " << left << setw(10) << "S.Acc";
		cout << "| " << left << setw(10) << "D.Acc";
		cout << "| " << left << setw(10) << "Amount";
		cout << "| " << left << setw(10) << "S.Balance";
		cout << "| " << left << setw(10) << "D.Balance";
		cout << "| " << left << setw(10) << "Username";
		cout << "\n\t------------------------------------------------";
		cout << "---------------------------------------------------\n";
		if (vTransferLogData.size() == 0)
		{
			cout << "\nNo Transfers Log Data To Show\n";
		}
		else
		{
			for (clsBankClient::stTransferLog& transferLog : vTransferLogData)
			{
				_PrintTransRecordData(transferLog);
				cout << endl;
			}
		}
		cout << "\n\t------------------------------------------------";
		cout << "---------------------------------------------------\n";

	}

};

