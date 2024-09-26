#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsDeleteUserScreen : protected clsScreen
{
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

    static void ShowDeleteUserScreen()
    {
        HeaderOfScreen("Delete User Screen");
        string Username = "";
        cout << "\nEnter Username? ";
        Username = clsInputValidate::ReadString();
        while (!clsUser::IsUserExist(Username))
        {
            cout << "\nUser is not exist, Enter another one? ";
            Username = clsInputValidate::ReadString();
        }
        clsUser user = clsUser::Find(Username);
        _PrintUserCard(user);
        cout << "\nAre you sure you want to delete this user? y/n? ";
        char ans = 'n';
        cin >> ans;
        if (tolower(ans) == 'y')
        {
            if (user.Delete())
            {
                cout << "\nUser Deleted Successfully\n";
                _PrintUserCard(user);
            }
            else
            {
                cout << "\nError Account Did Not Delete\n";
            }
        }
    }
};

