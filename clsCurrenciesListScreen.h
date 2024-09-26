#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"
#include <iomanip>

class clsCurrenciesListScreen : protected clsScreen
{
	static void _PrintCurrencyRecordLine(clsCurrency currency)
	{
		cout << "\t| " << setw(40) << left << currency.Country();
		cout << "| " << setw(6) << left << currency.CurrencyCode();
		cout << "| " << setw(40) << left << currency.CurrencyName();
		cout << "| " << setw(10) << left << currency.Rate();
	}
	
public:

	static void ShowCurrenciesList()
	{
		vector<clsCurrency> vCurrencies = clsCurrency::GetCurrenciesList();
		string subtitle = "(" + to_string(vCurrencies.size()) + ") Currency.";
		HeaderOfScreen("Currencies List Screen", subtitle);
		cout << "\n\t-----------------------------------------------------";
		cout << "---------------------------------------------------\n";
		cout << "\t| " << setw(40) << left << "Country";
		cout << "| " << setw(6) << left << "Code";
		cout << "| " << setw(40) << left << "Currency Name";
		cout << "| " << setw(10) << left << "Rate/(1$)";
		cout << "\n\t-----------------------------------------------------";
		cout << "---------------------------------------------------\n";
		if (vCurrencies.size() == 0)
		{
			cout << "\nNo Currencies Available To Show\n";
		}
		else
		{
			for (clsCurrency& c : vCurrencies)
			{
				_PrintCurrencyRecordLine(c);
				cout << endl;
			}
		}
		cout << "\n\t-----------------------------------------------------";
		cout << "---------------------------------------------------\n";
	}

};

