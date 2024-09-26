#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsUpdateUserScreen : protected clsScreen
{
    static void _ReadUserInfo(clsUser& user)
    {
        cout << "\nEnter First Name? ";
        user.FirstName = clsInputValidate::ReadString();

        cout << "Enter Last Name? ";
        user.LastName = clsInputValidate::ReadString();

        cout << "Enter Email? ";
        user.Email = clsInputValidate::ReadString();

        cout << "Enter Phone? ";
        user.Phone = clsInputValidate::ReadString();

        cout << "Enter Password? ";
        user.password = clsInputValidate::ReadString();

        cout << "Enter Permitions:";
        user.permitions = _ReadUserPermitions();
    }

    static int _ReadUserPermitions()
    {
        int Permitions = 0;
        char ans = 'n';
        cout << "\nDo you want to give full access? y/n? ";
        cin >> ans;
        if (tolower(ans) == 'y')
        {
            return -1;
        }
        cout << "\nDo you want to give access to:\n";
        cout << "\nShow Clients List? y/n? ";
        cin >> ans;
        if (tolower(ans) == 'y')
        {
            Permitions += clsUser::enPermitions::ShowClientsList;
        }
        cout << "Add New Client? y/n? ";
        cin >> ans;
        if (tolower(ans) == 'y')
        {
            Permitions += clsUser::enPermitions::AddNewClient;
        }
        cout << "Delete Client? y/n? ";
        cin >> ans;
        if (tolower(ans) == 'y')
        {
            Permitions += clsUser::enPermitions::DeleteClient;
        }
        cout << "Update Client? y/n? ";
        cin >> ans;
        if (tolower(ans) == 'y')
        {
            Permitions += clsUser::enPermitions::UpdateClient;
        }
        cout << "Find Client? y/n? ";
        cin >> ans;
        if (tolower(ans) == 'y')
        {
            Permitions += clsUser::enPermitions::FindClient;
        }
        cout << "Transactions? y/n? ";
        cin >> ans;
        if (tolower(ans) == 'y')
        {
            Permitions += clsUser::enPermitions::Transactions;
        }
        cout << "Manage Users? y/n? ";
        cin >> ans;
        if (tolower(ans) == 'y')
        {
            Permitions += clsUser::enPermitions::ManageUsers;
        }
        cout << "Login Register List? y/n? ";
        cin >> ans;
        if (tolower(ans) == 'y')
        {
            Permitions += clsUser::enPermitions::LoginRegisterList;
        }
        return Permitions;
    }

    static void _PrintUserCard(clsUser user)
    {
        cout << "\nUser Card:";
        cout << "\n-------------------------------------\n";
        cout << "First Name      : " << user.FirstName << endl;
        cout << "Last Name       : " << user.LastName << endl;
        cout << "Full Name       : " << user.FullName() << endl;
        cout << "Email           : " << user.Email << endl;
        cout << "Phone           : " << user.Phone << endl;
        cout << "Username        : " << user.username << endl;
        cout << "Password        : " << user.password << endl;
        cout << "Permitions      : " << user.permitions;
        cout << "\n-------------------------------------\n";
    }

public:

    static void ShowUpdateUserScreen()
    {
        HeaderOfScreen("Update User Screen");
        string username = "";
        cout << "\nEnter Username? ";
        username = clsInputValidate::ReadString();
        while (!clsUser::IsUserExist(username))
        {
            cout << "\nUsername is not exist, Enter another one? ";
            username = clsInputValidate::ReadString();
        }
        clsUser user = clsUser::Find(username);
        _PrintUserCard(user);
        cout << "\nAre you sure you want to update this user? y/n? ";
        char ans = 'n';
        cin >> ans;
        if (tolower(ans) == 'y')
        {
            cout << "\nUpdate User Info:";
            cout << "\n--------------------------------------\n";
            _ReadUserInfo(user);
            clsUser::enSaveResult SaveResult;
            SaveResult = user.Save();
            switch (SaveResult)
            {
            case clsUser::svFailedEmptyObject:
                cout << "\nUser was not saved, because it is empty\n";
                break;
            case clsUser::svSucceeded:
                cout << "\nUser Updated Successfully :-)\n";
                _PrintUserCard(user);           
            }
        }
    }
};

