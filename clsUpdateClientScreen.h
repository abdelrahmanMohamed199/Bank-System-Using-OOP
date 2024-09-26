#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsUser.h"

class clsUpdateClientScreen : protected clsScreen
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

    static void _ReadClientInfo(clsBankClient& client)
    {
        cout << "\nEnter First Name? ";
        client.FirstName = clsInputValidate::ReadString();

        cout << "Enter Last Name? ";
        client.LastName = clsInputValidate::ReadString();

        cout << "Enter Email? ";
        client.Email = clsInputValidate::ReadString();

        cout << "Enter Phone? ";
        client.Phone = clsInputValidate::ReadString();

        cout << "Enter Password? ";
        client.PIN = clsInputValidate::ReadString();

        cout << "Enter Account Balance? ";
        client.AccountBalance = clsInputValidate::ReadNumber<float>();
    }

public:

    static void ShowUpdateClientScreen()
    {
        if (!CheckAccessRights(clsUser::enPermitions::UpdateClient))
        {
            return;
        }
        HeaderOfScreen("Update Client Screen");
        string AccountNumber = "";
        cout << "\nEnter Account Number? ";
        AccountNumber = clsInputValidate::ReadString();
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nClient is not found, Enter another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }
        clsBankClient client = clsBankClient::Find(AccountNumber);
        _Print(client);
        char ans = 'n';
        cout << "\nAre you sure you want to update this client? y/n? ";
        cin >> ans;
        if (tolower(ans) == 'y')
        {
            cout << "\nUpdate Client Info:";
            cout << "\n-------------------------\n";
            _ReadClientInfo(client);
            clsBankClient::enSaveResult SaveResult;
            SaveResult = client.Save();
            switch (SaveResult)
            {
            case clsBankClient::enSaveResult::svFailedEmptyObject:
                cout << "\nError fail to save because object is empty\n";
                break;
            case clsBankClient::enSaveResult::svSucceeded:
                cout << "\nClient account updated successfully\n";
                _Print(client);
            }
        }
        
    }
};

