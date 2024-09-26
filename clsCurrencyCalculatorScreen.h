#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

class clsCurrencyCalculatorScreen : protected clsScreen
{
	static void _PrintCurrencyInfo(clsCurrency currency)
	{
		cout << "\n------------------------------------------\n";
		cout << "Country       : " << currency.Country() << endl;
		cout << "Code          : " << currency.CurrencyCode() << endl;
		cout << "Currency Name : " << currency.CurrencyName() << endl;
		cout << "Rate/(1$)     : " << currency.Rate();
		cout << "\n------------------------------------------\n";
	}

	static clsCurrency _ReadCurrencyCode()
	{
		string currencyCode = "";
		currencyCode = clsInputValidate::ReadString();
		while (!clsCurrency::IsCurrencyExist(currencyCode))
		{
			cout << "\nCurrency code dose not exist, Enter another one? ";
			currencyCode = clsInputValidate::ReadString();
		}
		return clsCurrency::FindByCode(currencyCode);
	}

	static void _ExchangeProcess()
	{
		cout << "\nEnter Currency1 Code to convert from? ";		
		clsCurrency currencyFrom = _ReadCurrencyCode();
		cout << "\nEnter Currency2 Code to convert to? ";
		clsCurrency currencyTo = _ReadCurrencyCode();
		cout << "\nEnter Amount To Exchange? ";
		float amount = clsInputValidate::ReadNumber<float>();
		cout << "\nConvert From:";
		_PrintCurrencyInfo(currencyFrom);
		float result = 0;
		if (currencyFrom.CurrencyCode() == currencyTo.CurrencyCode())
		{
			cout << endl << amount << " " << currencyTo.CurrencyCode()
				<< " = " << amount << " "
				<< currencyTo.CurrencyCode() << endl;
		}
		else if (currencyFrom.CurrencyCode() == "USD")
		{
			result = currencyFrom.ConvertToOtherCurrency(currencyTo, amount);
			cout << endl << amount << " USD = " << result << " "
				<< currencyTo.CurrencyCode() << endl;
		}
		else if (currencyTo.CurrencyCode() == "USD")
		{
			result = currencyFrom.ConvertToUSD(amount);
			cout << endl << amount << " " << currencyFrom.CurrencyCode()
				<< " = " << result << " USD\n";
		}
		else
		{
			result = currencyFrom.ConvertToUSD(amount);
			cout << endl << amount << " " << currencyFrom.CurrencyCode()
				<< " = " << result << " USD\n";
			cout << "\nConvert from USD to " << currencyTo.CurrencyCode() << endl;
			_PrintCurrencyInfo(currencyTo);
			result = currencyFrom.ConvertToOtherCurrency(currencyTo, amount);
			cout << endl << amount << " " << currencyFrom.CurrencyCode()
				<< " = " << result << " "
				<< currencyTo.CurrencyCode() << endl;
		}
	}
	
public:

	static void ShowCurrencyCalcScreen()
	{
		char ans = 'n';
		do
		{
			system("cls");
			HeaderOfScreen("Currency Calculator Screen");
			_ExchangeProcess();		
			cout << "\nDo you want to perform another calculation? y/n? ";
			cin >> ans;
		} while (tolower(ans) == 'y');
	}

};

