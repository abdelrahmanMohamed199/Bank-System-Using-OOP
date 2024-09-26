#pragma once
#include "clsString.h"
#include <string>
#include <fstream>

class clsCurrency
{
	enum enMode {EmptyMode = 0, UpdateMode = 1};
	enMode _Mode;
	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;

	static clsCurrency _ConvertLineToCurrencyObj(string recordLine, string separator = "#//#")
	{
		vector<string> vCurrencyData = clsString::Split(recordLine, separator);
		return clsCurrency(enMode::UpdateMode, vCurrencyData[0],
			vCurrencyData[1], vCurrencyData[2], stof(vCurrencyData[3]));
	}

	string _ConvertCurrencyObjToLine(clsCurrency currency, string separator = "#//#")
	{
		return currency.Country() + separator
			+ currency.CurrencyCode() + separator
			+ currency.CurrencyName() + separator
			+ to_string(currency.Rate());
	}

	static vector<clsCurrency> _LoadCurrenciesDataFromFile(string fileName)
	{
		vector<clsCurrency> vCurrencies;
		fstream file;
		file.open(fileName, ios::in);
		if (file.is_open())
		{
			string line;
			while (getline(file, line))
			{
				clsCurrency currency = _ConvertLineToCurrencyObj(line);
				vCurrencies.push_back(currency);
			}
			file.close();
		}
		return vCurrencies;
	}

	void _SaveCurreniesDataToFile(vector<clsCurrency> vCurrencies, string fileName)
	{
		fstream file;
		file.open(fileName, ios::out);
		if (file.is_open())
		{
			string line;
			for (clsCurrency& currency : vCurrencies)
			{
				line = _ConvertCurrencyObjToLine(currency);
				file << line << endl;
			}
			file.close();
		}
	}

	void _Update()
	{
		vector<clsCurrency> vCurrencies = _LoadCurrenciesDataFromFile("Currencies.txt");
		for (clsCurrency& currency : vCurrencies)
		{
			if (currency.Country() == Country())
			{
				currency = *this;
				break;
			}
		}
		_SaveCurreniesDataToFile(vCurrencies, "Currencies.txt");
	}

	static clsCurrency _GetEmptyObject()
	{
		return clsCurrency(enMode::EmptyMode, "", "", "", 0);
	}

public:

	clsCurrency(enMode mode, string country, string currencyCode, string currencyName, float rate)
	{
		_Mode = mode;
		_Country = country;
		_CurrencyCode = currencyCode;
		_CurrencyName = currencyName;
		_Rate = rate;
	}

	string Country()
	{
		return _Country;
	}

	string CurrencyCode()
	{
		return _CurrencyCode;
	}

	string CurrencyName()
	{
		return _CurrencyName;
	}

	float Rate()
	{
		return _Rate;
	}

	void UpdateRate(float rate)
	{
		_Rate = rate;
		_Update();
	}

	bool IsEmpty()
	{
		return _Mode == enMode::EmptyMode;
	}

	static clsCurrency FindByCode(string currencyCode)
	{
		vector<clsCurrency> vCurrencies = _LoadCurrenciesDataFromFile("Currencies.txt");
		for (clsCurrency& c : vCurrencies)
		{
			if (clsString::UpperAllString(c.CurrencyCode()) == clsString::UpperAllString(currencyCode))
			{
				return c;
			}
		}
		return _GetEmptyObject();
	}

	static clsCurrency FindByCountry(string country)
	{
		vector<clsCurrency> vCurrencies = _LoadCurrenciesDataFromFile("Currencies.txt");
		for (clsCurrency& c : vCurrencies)
		{
			if (clsString::UpperAllString(c.Country()) == clsString::UpperAllString(country))
			{
				return c;
			}
		}
		return _GetEmptyObject();
	}

	static vector<clsCurrency> GetCurrenciesList()
	{
		return _LoadCurrenciesDataFromFile("Currencies.txt");
	}

	static bool IsCurrencyExist(string currencyCode)
	{
		clsCurrency currency = FindByCode(currencyCode);
		return !currency.IsEmpty();
	}

	float ConvertToUSD(float amount)
	{
		return amount / Rate();
	}

	float ConvertToOtherCurrency(clsCurrency currencyTo, float amount)
	{
		float amountInUSD = ConvertToUSD(amount);
		if (currencyTo.CurrencyCode() == "USD")
		{
			return amountInUSD;
		}
		return amountInUSD * currencyTo.Rate();
	}
};

