#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsClientsListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersScreen.h"
#include "clsLoginRegisterScreen.h"
#include "Global.h"
#include "clsCurrencyExchangeScreen.h"

using namespace std;

class clsMainScreen : protected clsScreen
{
    enum _enMainMenuChoice
    {
        ShowClientsList = 1, AddNewClient = 2, DeleteClient = 3,
        UpdateClient = 4, FindClient = 5, TransactionMenu = 6,
        ManageUsers = 7, LoginRegisterList = 8, CurrencyExchange = 9, Logout = 10
    };

    static void _ShowClientsList()
    {
        clsClientsListScreen::ShowClientsList();
    }

    static void _AddNewClient()
    {
        clsAddNewClientScreen::ShowAddNewClientScreen();
    }

    static void _DeleteClient()
    {
        clsDeleteClientScreen::ShowDeleteClientScreen();
    }

    static void _UpdateClient()
    {
        clsUpdateClientScreen::ShowUpdateClientScreen();
    }

    static void _FindClient()
    {
        clsFindClientScreen::ShowFindClientScreen();
    }

    static void _ShowTransactionsMenu()
    {
        clsTransactionsScreen::ShowTransactionsScreen();
    }

    static void _ShowManageUsersMenu()
    {
        clsManageUsersScreen::ShowManageUsersMenu();
    }

    static void _ShowLoginRegisterList()
    {
        clsLoginRegisterScreen::ShowLoginRegisterScreen();
    }

    static void _ShowCurrencyExchangeScreen()
    {
        clsCurrencyExchangeScreen::ShowCurrencyExchangeScreen();
    }

    static void _Logout()
    {
        CurrentUser = clsUser::Find("", "");      
    }

    static void _GoBackToMainMenu()
    {
        cout << "\n\nPress any key to go back to main menu...\n";
        system("pause>0");
        ShowMainMenu();
    }

    static void _PerformMainMenuChoise(_enMainMenuChoice choice)
    {
        switch (choice)
        {
        case clsMainScreen::ShowClientsList:
            system("cls");
            _ShowClientsList();
            _GoBackToMainMenu();
            break;
        case clsMainScreen::AddNewClient:
            system("cls");
            _AddNewClient();
            _GoBackToMainMenu();
            break;
        case clsMainScreen::DeleteClient:
            system("cls");
            _DeleteClient();
            _GoBackToMainMenu();
            break;
        case clsMainScreen::UpdateClient:
            system("cls");
            _UpdateClient();
            _GoBackToMainMenu();
            break;
        case clsMainScreen::FindClient:
            system("cls");
            _FindClient();
            _GoBackToMainMenu();
            break;
        case clsMainScreen::TransactionMenu:
            system("cls");
            _ShowTransactionsMenu();
            _GoBackToMainMenu();
            break;
        case clsMainScreen::ManageUsers:
            system("cls");
            _ShowManageUsersMenu();
            _GoBackToMainMenu();
            break;
        case clsMainScreen::LoginRegisterList:
            system("cls");
            _ShowLoginRegisterList();
            _GoBackToMainMenu();
            break;
        case clsMainScreen::CurrencyExchange:
            system("cls");
            _ShowCurrencyExchangeScreen();
            _GoBackToMainMenu();
            break;
        case clsMainScreen::Logout:
            system("cls");
            _Logout();          
        }
    }



public:

	static void ShowMainMenu()
	{
		system("cls");
		HeaderOfScreen("Main Screen");
        cout << "\n\t\t\t======================================================\n";
        cout << "\t\t\t\t\tMain Menu Screen";
        cout << "\n\t\t\t======================================================\n";
        cout << "\t\t\t\t\t[1] Show clients list.\n";
        cout << "\t\t\t\t\t[2] Add new client.\n";
        cout << "\t\t\t\t\t[3] Delete client.\n";
        cout << "\t\t\t\t\t[4] Update client info.\n";
        cout << "\t\t\t\t\t[5] Find client.\n";
        cout << "\t\t\t\t\t[6] Transactions Menue.\n";
        cout << "\t\t\t\t\t[7] Manage Users.\n";
        cout << "\t\t\t\t\t[8] Login Register.\n";
        cout << "\t\t\t\t\t[9] Currency Exchange.\n";
        cout << "\t\t\t\t\t[10] Logout";
        cout << "\n\t\t\t======================================================\n";
        cout << "\t\t\t\tChoose what do you want to do? [1 to 10]? ";
        _PerformMainMenuChoise((_enMainMenuChoice)clsInputValidate::ReadNumberBetween(1, 10, "Enter Number Between 1 and 10"));
	}
};

