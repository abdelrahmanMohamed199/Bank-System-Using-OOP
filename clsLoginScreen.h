#pragma once
#include "clsScreen.h"
#include "Global.h"
#include "clsInputValidate.h"
#include "clsMainScreen.h"

class clsLoginScreen : protected clsScreen
{
	
	static bool _Login()
	{
		bool loginFailed = false;
		string username, password;	
		short LoginTrials = 3;
		do
		{
			system("cls");
			HeaderOfScreen("Login Screen");
			if (loginFailed)
			{
				LoginTrials--;
				cout << "\nInvalid Username/Password.\n";
				cout << "\nYou have " << LoginTrials
					 << " trials to login.\n";
			}
			if (LoginTrials == 0)
			{
				cout << "\nYou locked after 3 failed trials.\n";
				return false;
			}
			cout << "\nEnter Username? ";
			username = clsInputValidate::ReadString();
			cout << "Enter Password? ";
			password = clsInputValidate::ReadString();
			CurrentUser = clsUser::Find(username, password);
			loginFailed = CurrentUser.IsEmpty();
		} while (loginFailed);
		CurrentUser.RegisterLogin();
		clsMainScreen::ShowMainMenu();
	}

public:

	static bool ShowLoginScreen()
	{
		return _Login();
	}

};

