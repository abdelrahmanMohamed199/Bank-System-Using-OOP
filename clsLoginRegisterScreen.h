#pragma once
#include "clsScreen.h"
#include "iomanip"
#include "clsString.h"


class clsLoginRegisterScreen : protected clsScreen
{
	static void _PrintLoginRecord(clsUser::stRegisterLogin login, string separator)
	{
		cout << "\t| " << setw(25) << left << login.dateTime;
		cout << "| " << setw(10) << left << login.username;
		cout << "| " << setw(15) << left << login.password;
		cout << "| " << setw(12) << left << login.permitions;
	}

public:

	static void ShowLoginRegisterScreen()
	{
		if (!CheckAccessRights(clsUser::LoginRegisterList))
		{
			return;
		}
		vector<clsUser::stRegisterLogin> vLogins = clsUser::LoadLoginDataFromFile("LoginRegister.txt");
		system("cls");
		string subtitle = "(" + to_string(vLogins.size()) + ") Record(s).";
		HeaderOfScreen("Login Register List Screen", subtitle);
		cout << "\n\t-----------------------------------------";
		cout << "--------------------------------------\n";
		cout << "\t| " << setw(25) << left << "Date/Time";
		cout << "| " << setw(10) << left << "Username";
		cout << "| " << setw(15) << left << "Password";
		cout << "| " << setw(12) << left << "Permitions";
		cout << "\n\t-----------------------------------------";
		cout << "--------------------------------------\n";
		if (vLogins.size() == 0)
		{
			cout << "\nNo Registers Yet.\n";
		}
		else
		{
			for (clsUser::stRegisterLogin& login : vLogins)
			{
				_PrintLoginRecord(login, "#//#");
				cout << endl;
			}
		}
		cout << "\n\t-----------------------------------------";
		cout << "--------------------------------------\n";
	}

};

