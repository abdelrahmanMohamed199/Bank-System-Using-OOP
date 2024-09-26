#pragma once
#include <iostream>
#include "Global.h"
#include "clsDate.h"

using namespace std;

class clsScreen
{
protected:

	static void HeaderOfScreen(string title, string subtitle = "")
	{
		cout << "\n\t\t\t------------------------------------------------------\n";
		cout << "\t\t\t\t\t" << title;
		if (subtitle != "")
			cout << "\n\t\t\t\t\t" << subtitle;
		cout << "\n\t\t\t------------------------------------------------------\n";
		cout << "\n\t\t\tUser: " << CurrentUser.username;
		cout << "\n\t\t\tDate: " << clsDate::DateToString(clsDate()) << endl;			 			
	}

	static bool CheckAccessRights(clsUser::enPermitions permitions)
	{
		if (CurrentUser.HasPermition(permitions))
			return true;
		else
		{
			HeaderOfScreen("Access Denied! Contact Your Admin");
			return false;
		}

	}
};

