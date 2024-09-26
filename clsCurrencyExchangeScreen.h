#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyScreen.h"
#include "clsCurrencyCalculatorScreen.h"

class clsCurrencyExchangeScreen : protected clsScreen
{
	enum enCurrencyMenuOption
	{
		CurrenciesList = 1, FindCurrency = 2,
		UpdateRate = 3, CurrencyCalculator = 4, MainMenu = 5
	};

	static void _ShowListCurrencies()
	{
		clsCurrenciesListScreen::ShowCurrenciesList();
	}

	static void _FindCurrency()
	{
		clsFindCurrencyScreen::ShowFindCurrencyScreen();
	}

	static void _UpdateRate()
	{
		clsUpdateCurrencyScreen::ShowCurrencyUpdateScreen();
	}

	static void _CurrencyCalculator()
	{
		clsCurrencyCalculatorScreen::ShowCurrencyCalcScreen();
	}

	static void _GoBackToCurrencyExchangeMenu()
	{
		cout << "\n\nPress any key to go back to currency exchange menu...\n";
		system("pause>0");
		ShowCurrencyExchangeScreen();
	}

	static void _PerformCurrencyExchangeOption(enCurrencyMenuOption option)
	{
		switch (option)
		{
		case clsCurrencyExchangeScreen::CurrenciesList:
			system("cls");
			_ShowListCurrencies();
			_GoBackToCurrencyExchangeMenu();
			break;
		case clsCurrencyExchangeScreen::FindCurrency:
			system("cls");
			_FindCurrency();
			_GoBackToCurrencyExchangeMenu();
			break;
		case clsCurrencyExchangeScreen::UpdateRate:
			system("cls");
			_UpdateRate();
			_GoBackToCurrencyExchangeMenu();
			break;
		case clsCurrencyExchangeScreen::CurrencyCalculator:
			system("cls");
			_CurrencyCalculator();
			_GoBackToCurrencyExchangeMenu();
		}
	}

public:

	static void ShowCurrencyExchangeScreen()
	{
		system("cls");
		HeaderOfScreen("Currency Exchange Main Screen");
		cout << "\n\t\t\t=======================================================\n";
		cout << "\t\t\t\tCurrency Exchange Menu";
		cout << "\n\t\t\t=======================================================\n";
		cout << "\t\t\t\t[1] List Currencies.\n";
		cout << "\t\t\t\t[2] Find Currency.\n";
		cout << "\t\t\t\t[3] Update Rate.\n";
		cout << "\t\t\t\t[4] Currency Calculator.\n";
		cout << "\t\t\t\t[5] Main Menu.";
		cout << "\n\t\t\t=======================================================\n";
		cout << "\t\t\tChoose what do you want to do? [1 to 5]? ";
		_PerformCurrencyExchangeOption((enCurrencyMenuOption)clsInputValidate::ReadNumberBetween(1, 5));
	}
};

