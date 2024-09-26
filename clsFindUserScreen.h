#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsFindUserScreen : protected clsScreen
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

    static void ShowFindUserScreen()
    {
        HeaderOfScreen("Find User Screen");
        cout << "\nEnter Username? ";
        string Username = "";
        Username = clsInputValidate::ReadString();
        while (!clsUser::IsUserExist(Username))
        {
            cout << "\nUsername is not exist, Enter another one? ";
            Username = clsInputValidate::ReadString();
        }
        clsUser user = clsUser::Find(Username);
        if (!user.IsEmpty())
        {
            cout << "\nUser found :-)\n";
            _PrintUserCard(user);
        }
        else
        {
            cout << "\nUser was not found\n";
        }
    }

};

