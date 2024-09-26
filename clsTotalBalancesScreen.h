#pragma once
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsUtil.h"


class clsTotalBalancesScreen : protected clsScreen
{
    static void _PrintClientRecordBalanceLine(clsBankClient client)
    {
        cout << "\t\t\t| " << left << setw(20) << client.AccountNumber;
        cout << "| " << left << setw(25) << client.FullName();
        cout << "| " << left << setw(12) << client.AccountBalance;
    }

public:

    static void ShowTotalBalances()
    {
        vector<clsBankClient> vClients = clsBankClient::GetClientsList();
        string title = "Balances List Screen";
        string subtitle = to_string(vClients.size()) + " Client(s)";
        HeaderOfScreen(title, subtitle);
        cout << "\n\t\t\t---------------------------------------------------------------\n";
        cout << "\t\t\t| " << left << setw(20) << "Account Number";
        cout << "| " << left << setw(25) << "Client Name";
        cout << "| " << left << setw(12) << "Balance";
        cout << "\n\t\t\t---------------------------------------------------------------\n";
        if (vClients.size() == 0)
        {
            cout << "\n\t\t\t\t\tThere are no clients to show\n";
        }
        else
        {
            for (clsBankClient& c : vClients)
            {
                _PrintClientRecordBalanceLine(c);
                cout << endl;
            }
        }
        cout << "\n\t\t\t---------------------------------------------------------------\n";
        double TotalBalances = clsBankClient::GetTotalBalances();
        cout << "\t\t\t\t\t Total Balances = " << TotalBalances << endl;
        cout << "\t\t\t\t\t (" << clsUtil::convertNumToText(TotalBalances) << ")\n";
    }

};

