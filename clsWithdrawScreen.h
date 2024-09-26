#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsWithdrawScreen : protected clsScreen
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

    static void ShowWithdrawScreen()
    {
        HeaderOfScreen("Withdraw Screen");
        string AccountNumber = "";
        cout << "\nEnter an account number? ";
        AccountNumber = clsInputValidate::ReadString();
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not exist, Enter another one? ";
            AccountNumber = clsInputValidate::ReadString();
        }
        clsBankClient client = clsBankClient::Find(AccountNumber);
        _Print(client);
        cout << "\nEnter withdraw amount? ";
        float amount = clsInputValidate::ReadNumber<float>();
        cout << "\nAre you sure you want to perform this transaction? y/n? ";
        char ans = 'n';
        cin >> ans;
        if (tolower(ans) == 'y')
        {
            if (client.Withdraw(amount))
            {
                cout << "\nOperation Done :-)\n";
                cout << "\nThe nwe balance is: " << client.AccountBalance << endl;
            }
            else
            {
                cout << "\nCan not withdraw, Insuffecient balance\n";
                cout << "\nWithdraw amount is: " << amount << endl;
                cout << "\nYour Balance is: " << client.AccountBalance << endl;
            }
        }
        else
        {
            cout << "\nOperation was canceled\n";
        }
    }
};

