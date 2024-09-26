#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsUser.h"

class clsDeleteClientScreen : protected clsScreen
{
    static void _Print(clsBankClient client)
    {
        cout << "\nClient Card:";
        cout << "\n-------------------------------------\n";
        cout << "First Name      : " << client.FirstName << endl;
        cout << "Last Name       : " << client.LastName << endl;
        cout << "Full Name       : " << client.FullName() << endl;
        cout << "Email           : " << client.Email << endl;
        cout << "Phone           : " << client.Phone << endl;
        cout << "Account Number  : " << client.AccountNumber << endl;
        cout << "PIN Code        : " << client.PIN << endl;
        cout << "Account Balance : " << client.AccountBalance;
        cout << "\n-------------------------------------\n";
    }

public:

    static void ShowDeleteClientScreen()
    {
        if (!CheckAccessRights(clsUser::enPermitions::DeleteClient))
        {
            return;
        }
        HeaderOfScreen("Delete Client Screen");
        string AccountNumber = "";
        cout << "\nEnter Account Number? ";
        AccountNumber = clsInputValidate::ReadString();
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nClient is not exist, Enter another one? ";
            AccountNumber = clsInputValidate::ReadString();
        }
        clsBankClient client = clsBankClient::Find(AccountNumber);
        _Print(client);
        cout << "\nAre you sure you want to delete this client? y/n? ";
        char ans = 'n';
        cin >> ans;
        if (tolower(ans) == 'y')
        {
            if (client.Delete())
            {
                cout << "\nClient Account Deleted Successfully\n";
                _Print(client);
            }
            else
            {
                cout << "\nError Account Did Not Delete\n";
            }
        }
    }

};

