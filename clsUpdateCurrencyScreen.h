#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

class clsUpdateCurrencyScreen : protected clsScreen
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

public:

	static void ShowCurrencyUpdateScreen()
	{
		HeaderOfScreen("Currency Update Screen");
		string code = "";
		cout << "\nPlease Enter Currency Code? ";
		code = clsInputValidate::ReadString();
		while (!clsCurrency::IsCurrencyExist(code))
		{
			cout << "\nCurrency not Exist, Enter another code? ";
			code = clsInputValidate::ReadString();
		}
		clsCurrency currency = clsCurrency::FindByCode(code);
		_PrintCurrencyInfo(currency);
		cout << "\nAre you sure you want to update rate of this currency? y/n? ";
		char ans = 'n';
		cin >> ans;
		if (tolower(ans) == 'y')
		{
			cout << "\nUpdate Currency Rate:";
			cout << "\n----------------------------\n";
			cout << "\nEnter New Rate? ";
			float rate;
			rate = clsInputValidate::ReadNumber<float>();
			currency.UpdateRate(rate);
			cout << "\nCurrency rate updated successfully :-)\n";
			_PrintCurrencyInfo(currency);
		}
	}

};

