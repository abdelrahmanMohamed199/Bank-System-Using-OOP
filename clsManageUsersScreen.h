#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsListUsersScreen.h"
#include "clsAddUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

class clsManageUsersScreen : protected clsScreen
{
	enum enManageUsersOption
	{
		UsersList = 1, AddUser = 2, DeleteUser = 3,
		UpdateUser = 4, FindUser = 5, MainMenu = 6
	};

	static void _ShowUsersList()
	{
		clsListUsersScreen::ShowUsersList();
	}

	static void _ShowAddUserScreen()
	{
		clsAddUserScreen::ShowAddUserScreen();
	}

	static void _ShowDeleteUserScreen()
	{
		clsDeleteUserScreen::ShowDeleteUserScreen();
	}

	static void _ShowUpdateUserScreen()
	{
		clsUpdateUserScreen::ShowUpdateUserScreen();
	}

	static void _ShowFindUserScreen()
	{
		clsFindUserScreen::ShowFindUserScreen();
	}

	static void _GoBackToManageUsersMenu()
	{
		cout << "\n\nPress any key to go back to transactions menu...\n";
		system("pause>0");
		ShowManageUsersMenu();
	}

	static void _PerformManageUsersOption(enManageUsersOption option)
	{
		switch (option)
		{
		case clsManageUsersScreen::UsersList:
			system("cls");
			_ShowUsersList();
			_GoBackToManageUsersMenu();
			break;
		case clsManageUsersScreen::AddUser:
			system("cls");
			_ShowAddUserScreen();
			_GoBackToManageUsersMenu();
			break;
		case clsManageUsersScreen::DeleteUser:
			system("cls");
			_ShowDeleteUserScreen();
			_GoBackToManageUsersMenu();
			break;
		case clsManageUsersScreen::UpdateUser:
			system("cls");
			_ShowUpdateUserScreen();
			_GoBackToManageUsersMenu();
			break;
		case clsManageUsersScreen::FindUser:
			system("cls");
			_ShowFindUserScreen();
			_GoBackToManageUsersMenu();
			break;
		case clsManageUsersScreen::MainMenu:
		{

		}
		}
	}

public:

	static void ShowManageUsersMenu()
	{
		if (!CheckAccessRights(clsUser::enPermitions::ManageUsers))
		{
			return;
		}
		system("cls");
		HeaderOfScreen("Manage Users Screen");
		cout << "\n\t\t\t======================================================\n";
		cout << "\t\t\t\t\tManage Users Menu";
		cout << "\n\t\t\t======================================================\n";
		cout << "\t\t\t\t\t[1] Users List.\n";
		cout << "\t\t\t\t\t[2] Add User.\n";
		cout << "\t\t\t\t\t[3] Delete User.\n";
		cout << "\t\t\t\t\t[4] Update User.\n";
		cout << "\t\t\t\t\t[5] Find User.\n";
		cout << "\t\t\t\t\t[6] Main Menu.";
		cout << "\n\t\t\t======================================================\n";
		cout << "\t\t\t\tChoose an option from [1 to 6]? ";
		_PerformManageUsersOption((enManageUsersOption)clsInputValidate::ReadNumberBetween(1, 6));
	}
};

