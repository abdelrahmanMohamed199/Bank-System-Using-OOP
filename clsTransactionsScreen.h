#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransfereScreen.h"
#include "clsTransfersLogScreen.h"

class clsTransactionsScreen : protected clsScreen
{
	enum enTransactionsOptions
	{
		Deposite = 1, Withdraw = 2, TotalBalances = 3,
		Transfere = 4, TransfersLog = 5, MainMenu = 6
	};

	static void _DepositeScreen()
	{
		clsDepositScreen::ShowDepositScreen();
	}

	static void _WithdrawScreen()
	{
		clsWithdrawScreen::ShowWithdrawScreen();
	}

	static void _ShowTotalBalances()
	{
		clsTotalBalancesScreen::ShowTotalBalances();
	}

	static void _ShowTransfereScreen()
	{
		clsTransfereScreen::ShowTransfereScreen();
	}

	static void _ShowTransfersLog()
	{
		clsTransfersLogScreen::ShowTransfersLogScreen();
	}

	static void _GoBackToTransactionsMenu()
	{
		cout << "\n\nPress any key to go back to transactions menu...\n";
		system("pause>0");
		ShowTransactionsScreen();
	}

	static void _PerformTransactionsMenuOption(enTransactionsOptions option)
	{
		switch (option)
		{
		case clsTransactionsScreen::Deposite:
			system("cls");
			_DepositeScreen();
			_GoBackToTransactionsMenu();
			break;
		case clsTransactionsScreen::Withdraw:
			system("cls");
			_WithdrawScreen();
			_GoBackToTransactionsMenu();
			break;
		case clsTransactionsScreen::TotalBalances:
			system("cls");
			_ShowTotalBalances();
			_GoBackToTransactionsMenu();	
		case clsTransactionsScreen::Transfere:
			system("cls");
			_ShowTransfereScreen();
			_GoBackToTransactionsMenu();
		case clsTransactionsScreen::TransfersLog:
			system("cls");
			_ShowTransfersLog();
			_GoBackToTransactionsMenu();
		}
	}
	
public:

	static void ShowTransactionsScreen()
	{
		if (!CheckAccessRights(clsUser::enPermitions::Transactions))
		{
			return;
		}
		system("cls");
		HeaderOfScreen("Transactions Screen");
		cout << "\n\t\t\t======================================================\n";
		cout << "\t\t\t\t\tTransactions Menu";
		cout << "\n\t\t\t======================================================\n";
		cout << "\t\t\t\t\t[1] Deposite.\n";
		cout << "\t\t\t\t\t[2] Withdraw.\n";
		cout << "\t\t\t\t\t[3] Total Balances.\n";
		cout << "\t\t\t\t\t[4] Transfere.\n";
		cout << "\t\t\t\t\t[5] Transfere Log List.\n";
		cout << "\t\t\t\t\t[6] Main Menu.\n";
		cout << "\n\t\t\t======================================================\n";
		cout << "\t\t\t\tChoose what you want from [1 to 6]? ";
		_PerformTransactionsMenuOption((enTransactionsOptions)clsInputValidate::ReadNumberBetween(1, 6));
	}
};

