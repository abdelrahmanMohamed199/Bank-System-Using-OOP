#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include<iomanip>
#include "clsUser.h"

using namespace std;

class clsClientsListScreen : protected clsScreen
{
    static void PrintClientRecordLine(clsBankClient client)
    {
        cout << setw(8) << "" << "| " << left << setw(15) << client.AccountNumber;
        cout << "| " << left << setw(20) << client.FullName();
        cout << "| " << left << setw(12) << client.Phone;
        cout << "| " << left << setw(20) << client.Email;
        cout << "| " << left << setw(10) << client.PIN;
        cout << "| " << left << setw(12) << client.AccountBalance;
    }

public:

    static void ShowClientsList()
    {
        if (!CheckAccessRights(clsUser::enPermitions::ShowClientsList))
        {
            return;
        }
        vector<clsBankClient> vClients = clsBankClient::GetClientsList();
        string title = "Clients List Screen";
        string subtitle = "(" + to_string(vClients.size()) + ") Client(s).";
        HeaderOfScreen(title, subtitle);
        cout << endl << setw(8) << "" << "--------------------------------------------------------";
        cout << "-----------------------------------------\n";
        cout << setw(8) << "" << "| " << left << setw(15) << "Account Number";
        cout << "| " << left << setw(20) << "Client Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "PIN Code";
        cout << "| " << left << setw(12) << "Balance";
        cout << endl << setw(8) << "" << "--------------------------------------------------------";
        cout << "-----------------------------------------\n";
        if (vClients.size() == 0)
        {
            cout << "\n\t\t\t\t\tThere are no clients to show\n";
        }
        else
        {
            for (clsBankClient& c : vClients)
            {
                PrintClientRecordLine(c);
                cout << endl;
            }
        }
        cout << endl << setw(8) << "" << "--------------------------------------------------------";
        cout << "-----------------------------------------\n";
    }

};

