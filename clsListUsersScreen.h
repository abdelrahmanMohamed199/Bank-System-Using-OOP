#pragma once
#include <iomanip>
#include "clsScreen.h"
#include "clsUser.h"

class clsListUsersScreen : protected clsScreen
{
	static void _PrintUserRecordLine(clsUser user)
	{
		cout << "\t| " << setw(10) << left << user.username;
		cout << "| " << setw(25) << left << user.FullName();
		cout << "| " << setw(12) << left << user.Phone;
		cout << "| " << setw(20) << left << user.Email;
		cout << "| " << setw(10) << left << user.password;
		cout << "| " << setw(12) << left << user.permitions;
	}

public:

	static void ShowUsersList()
	{
		vector<clsUser> vUsers = clsUser::GetUsersList();
		string subtitle = to_string(vUsers.size()) + " User(s)";
		HeaderOfScreen("Users List Screen", subtitle);
		cout << "\n\t------------------------------------------------";
		cout << "---------------------------------------------------\n";
		cout << "\t| " << setw(10) << left << "Username";
		cout << "| " << setw(25) << left << "Full Name";
		cout << "| " << setw(12) << left << "Phone";
		cout << "| " << setw(20) << left << "Email";
		cout << "| " << setw(10) << left << "Password";
		cout << "| " << setw(12) << left << "Permitions";
		cout << "\n\t------------------------------------------------";
		cout << "---------------------------------------------------\n";
		if (vUsers.size() == 0)
		{
			cout << "\nThere are no users to show\n";
		}
		else
		{
			for (clsUser& user : vUsers)
			{
				_PrintUserRecordLine(user);
				cout << endl;
			}
		}
		cout << "\n\t------------------------------------------------";
		cout << "---------------------------------------------------\n";
	}
};

