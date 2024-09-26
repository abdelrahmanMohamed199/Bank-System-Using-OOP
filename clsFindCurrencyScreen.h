#pragma once
#include "clsScreen.h";
#include "clsCurrency.h"
#include "clsInputValidate.h"

class clsFindCurrencyScreen : protected clsScreen
{
	static void _PrintCurrencyInfo(clsCurrency currency)
	{
		cout << "\nCurrency Info:";
		cout << "\n------------------------------------------\n";
		cout << "Country       : " << currency.Country() << endl;
		cout << "Code          : " << currency.CurrencyCode() << endl;
		cout << "Currency Name : " << currency.CurrencyName() << endl;
		cout << "Rate/(1$)     : " << currency.Rate();
		cout << "\n------------------------------------------\n";
	}

	static void _PerformFindChoise(short choise)
	{
		if (choise == 1)
		{
			string code = "";
			cout << "\nPlease enter the code? ";
			code = clsInputValidate::ReadString();
			while (!clsCurrency::IsCurrencyExist(code))
			{
				cout << "\nCurrency code is not exist, Enter another one? ";
				code = clsInputValidate::ReadString();
			}
			clsCurrency currency = clsCurrency::FindByCode(code);
			if (!currency.IsEmpty())
			{
				cout << "\nCurrency Found :-)\n";
				_PrintCurrencyInfo(currency);
			}
			else
			{
				cout << "\nCurrency not found\n";
			}
		}
		else
		{
			string country = "";
			cout << "\nPlease enter country? ";
			country = clsInputValidate::ReadString();
			clsCurrency currency = clsCurrency::FindByCountry(country);
			while (currency.IsEmpty())
			{
				cout << "\nCountry is not exist, Enter another one? ";
				country = clsInputValidate::ReadString();
				currency = clsCurrency::FindByCountry(country);
			}
			cout << "\nCurrency Found :-)\n";
			_PrintCurrencyInfo(currency);
		}
	}

public:

	static void ShowFindCurrencyScreen()
	{
		HeaderOfScreen("Find Currency Screen");
		short choise = 1;
		cout << "\nFind by: [1] code or [2] country? ";
		choise = clsInputValidate::ReadNumberBetween(1, 2);
		_PerformFindChoise(choise);
	}

};

