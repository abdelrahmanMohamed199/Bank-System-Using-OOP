#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsUser.h"

class clsFindClientScreen : protected clsScreen
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

    static void ShowFindClientScreen()
    {
        if (!CheckAccessRights(clsUser::enPermitions::FindClient))
        {
            return;
        }
        HeaderOfScreen("Find Client Screen");
        cout << "\nEnter account number? ";
        string AccountNumber = "";
        AccountNumber = clsInputValidate::ReadString();
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nClient is not exist, Enter another one? ";
            AccountNumber = clsInputValidate::ReadString();
        }
        clsBankClient client = clsBankClient::Find(AccountNumber);
        if (!client.IsEmpty())
        {
            cout << "\nClient found :-)\n";
            _Print(client);
        }
        else
        {
            cout << "\nClient was not found\n";
        }
    }
};

