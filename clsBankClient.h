#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
#include "clsDate.h"
#include "Global.h"

using namespace std;

class clsBankClient : public clsPerson
{
	struct stTransferLog;
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _Mode;
	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkForDelete = false;
	
	static clsBankClient _ConvertLineToUserObject(string line, string separator = "#//#")
	{
		vector<string> vClients = clsString::Split(line, separator);

		return clsBankClient(enMode::UpdateMode, vClients[0], vClients[1], vClients[2],
			vClients[3], vClients[4], vClients[5], stof(vClients[6]));
	}

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static vector<clsBankClient> _LoadClientsDataFromFile()
	{
		vector<clsBankClient> vClients;
		fstream file;
		file.open("Clients.txt", ios::in);
		if (file.is_open())
		{
			string DataLine;
			while (getline(file, DataLine))
			{
				clsBankClient client = _ConvertLineToUserObject(DataLine);
				vClients.push_back(client);
			}
			file.close();
		}
		return vClients;
	}

	string _ConvertClientObjToLine(clsBankClient client, string separator = "#//#")
	{
		string line = "";
		line += client.FirstName + separator + client.LastName + separator + client.Email + separator;
		line += client.Phone + separator + client.AccountNumber + separator;
		line += client.PIN + separator + to_string(client.AccountBalance);
		return line;
	}

	void _SaveDataInFile(vector<clsBankClient>& vClients)
	{
		fstream file;
		file.open("Clients.txt", ios::out);
		if (file.is_open())
		{
			string Line = "";
			for (clsBankClient& c : vClients)
			{
				if (c._MarkForDelete == false)
				{
					Line = _ConvertClientObjToLine(c);
					file << Line << endl;
				}
			}
			file.close();
		}
	}

	void _Update()
	{
		vector<clsBankClient> vClients = _LoadClientsDataFromFile();
		for (clsBankClient& c : vClients)
		{
			if (c.AccountNumber == AccountNumber)
			{
				c = *this;
				break;
			}
		}
		_SaveDataInFile(vClients);
	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertClientObjToLine(*this));
	}

	void _AddDataLineToFile(string line)
	{
		fstream file;
		file.open("Clients.txt", ios::out | ios::app);
		if (file.is_open())
		{
			file << line << endl;
			file.close();
		}
	}

	string _PrepareTransfereLogRecord(float amount, clsBankClient destinationClient,string username, string separator = "#//#")
	{
		return clsDate::GetSystemDateTimeString() + separator
			+ AccountNumber + separator
			+ destinationClient.AccountNumber + separator
			+ to_string(amount) + separator
			+ to_string(AccountBalance) + separator
			+ to_string(destinationClient.AccountBalance) + separator
			+ username;
	}

	void _RegisterTransferLog(string fileName, float amount, clsBankClient destinationClient, string username, string separator = "#//#")
	{
		fstream file;
		file.open(fileName, ios::out | ios::app);
		if (file.is_open())
		{
			string recordLine = _PrepareTransfereLogRecord(amount, destinationClient, username);
			file << recordLine << endl;
			file.close();
		}
	}

	static stTransferLog _ConvertRecordToTransferLog(string record)
	{
		vector<string> vTransferLog = clsString::Split(record, "#//#");
		stTransferLog tLog;
		tLog.dateTime = vTransferLog[0];
		tLog.sourceAccNum = vTransferLog[1];
		tLog.destinationAccNum = vTransferLog[2];
		tLog.amount = stof(vTransferLog[3]);
		tLog.sourceBalance = stof(vTransferLog[4]);
		tLog.destinationBalance = stof(vTransferLog[5]);
		tLog.username = vTransferLog[6];
		return tLog;
	}

public:

	clsBankClient(enMode mode, string FirstName, string LastName, string email,
		string phone, string accNum, string PIN, double accbalance) :
		clsPerson(FirstName, LastName, email, phone)
	{
		_Mode = mode;
		_AccountNumber = accNum;
		_AccountBalance = accbalance;
		_PinCode = PIN;
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	string GetAccountNumber()
	{
		return _AccountNumber;
	}
	_declspec(property(get = GetAccountNumber)) string AccountNumber;

	void SetPinCode(string PIN)
	{
		_PinCode = PIN;
	}
	string GetPinCode()
	{
		return _PinCode;
	}
	_declspec(property(get = GetPinCode, put = SetPinCode)) string PIN;

	void SetAccountBalance(double balance)
	{
		_AccountBalance = balance;
	}
	double GetAccountBalance()
	{
		return _AccountBalance;
	}
	_declspec(property(get = GetAccountBalance, put = SetAccountBalance)) double AccountBalance;

	static clsBankClient Find(string accountNum)
	{
		fstream file;
		file.open("Clients.txt", ios::in);
		if (file.is_open())
		{
			string line;
			while (getline(file, line))
			{
				clsBankClient client = _ConvertLineToUserObject(line);
				if (client.AccountNumber == accountNum)
				{
					file.close();
					return client;
				}
			}
			file.close();
		}
		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string accountNum, string PinCode)
	{
		fstream file;
		file.open("Clients.txt", ios::in);
		if (file.is_open())
		{
			string line;
			while (getline(file, line))
			{
				clsBankClient client = _ConvertLineToUserObject(line);
				if (client.AccountNumber == accountNum && client.PIN == PinCode)
				{
					file.close();
					return client;
				}
			}
			file.close();
		}
		return _GetEmptyClientObject();
	}

	enum enSaveResult{svFailedEmptyObject = 0, svSucceeded = 1, svFailedClientExisted = 2};

	enSaveResult Save()
	{
		switch (_Mode)
		{
		case clsBankClient::EmptyMode:
			return enSaveResult::svFailedEmptyObject;
		case clsBankClient::UpdateMode:
			_Update();
			return enSaveResult::svSucceeded;
		case clsBankClient::AddNewMode:
			if (IsClientExist(AccountNumber))
			{
				return enSaveResult::svFailedClientExisted;
			}
			else
			{
				_AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResult::svSucceeded;
			}
		}
	}

	static bool IsClientExist(string accountNum)
	{
		clsBankClient client = Find(accountNum);
		return !client.IsEmpty();
	}

	static clsBankClient GetAddNewClientObject(string accountNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", accountNumber, "", 0);
	}

	bool Delete()
	{
		vector<clsBankClient> vClients = _LoadClientsDataFromFile();
		for (clsBankClient& c : vClients)
		{
			if (c.AccountNumber == AccountNumber)
			{
				c._MarkForDelete = true;
				break;
			}
		}
		_SaveDataInFile(vClients);
		*this = _GetEmptyClientObject();
		return true;
	}

	static vector<clsBankClient> GetClientsList()
	{
		return _LoadClientsDataFromFile();
	}

	static double GetTotalBalances()
	{
		vector<clsBankClient> vClients = _LoadClientsDataFromFile();
		double TotalBalances = 0;
		for (clsBankClient& c : vClients)
		{
			TotalBalances += c.AccountBalance;
		}
		return TotalBalances;
	}

	void Deposite(float amount)
	{
		AccountBalance += amount;
		Save();
	}

	bool Withdraw(float amount)
	{
		if (amount > AccountBalance)
		{
			return false;
		}
		else
		{
			AccountBalance -= amount;
			Save();
		}
	}

	bool Transfere(float amount, clsBankClient& destinationClient)
	{
		if (amount > AccountBalance)
		{
			return false;
		}
		Withdraw(amount);
		destinationClient.Deposite(amount);
		_RegisterTransferLog("TransferLog.txt", amount, destinationClient, CurrentUser.username);
		return true;
	}

	struct stTransferLog
	{
		string dateTime, sourceAccNum, destinationAccNum, username;
		float amount, sourceBalance, destinationBalance;
	};

	static vector<stTransferLog> LoadTransfersLogListFromFile(string fileName)
	{
		vector<stTransferLog> vTransfersLog;
		fstream file;
		file.open(fileName, ios::in);
		if (file.is_open())
		{
			string line;
			stTransferLog tLog;
			while (getline(file, line))
			{
				tLog = _ConvertRecordToTransferLog(line);
				vTransfersLog.push_back(tLog);
			}
			file.close();
		}
		return vTransfersLog;
	}
};

