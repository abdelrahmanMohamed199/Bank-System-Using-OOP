#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsUser.h"

class clsAddNewClientScreen : protected clsScreen
{
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

    static void ShowAddNewClientScreen()
    {
        if (!CheckAccessRights(clsUser::enPermitions::AddNewClient))
        {
            return;
        }
        HeaderOfScreen("Add New Client Screen");
        string AccountNumber = "";
        cout << "Enter Account Number? ";
        AccountNumber = clsInputValidate::ReadString();
        while (clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is already exist, Enter another one? ";
            AccountNumber = clsInputValidate::ReadString();
        }
        clsBankClient client = clsBankClient::GetAddNewClientObject(AccountNumber);
        _ReadClientInfo(client);
        clsBankClient::enSaveResult SaveResult;
        SaveResult = client.Save();
        switch (SaveResult)
        {
        case clsBankClient::enSaveResult::svSucceeded:
            cout << "\nClient Account Added Successfully\n";
            _Print(client);
            break;
        case clsBankClient::enSaveResult::svFailedEmptyObject:
            cout << "\nError fail to save because object is empty\n";
            break;
        case clsBankClient::enSaveResult::svFailedClientExisted:
            cout << "\nError fail to save because client is already exist\n";
        }
    }
};

