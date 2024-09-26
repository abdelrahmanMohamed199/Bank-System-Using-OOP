#pragma once
#include "clsPerson.h"
#include <vector>
#include "clsString.h"
#include <fstream>
#include "clsUtil.h"

class clsUser : public clsPerson
{
	struct stRegisterLogin;
	enum enMode {EmptyMode = 1, UpdateMode = 2, AddNewMode = 3};
	enMode _Mode;
	string _Username;
	string _Password;
	int _Permitions;
	bool _MarkForDelete = false;

	static clsUser _ConvertLineToUserObject(string line, string separator = "#//#")
	{
		vector<string> vUsers = clsString::Split(line, separator);

		return clsUser(enMode::UpdateMode, vUsers[0], vUsers[1], vUsers[2],
			vUsers[3], vUsers[4], vUsers[5], stoi(vUsers[6]));
	}

	static clsUser _GetEmptyUserObject()
	{
		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static vector<clsUser> _LoadUsersDataFromFile()
	{
		vector<clsUser> vUsers;
		fstream file;
		file.open("Users.txt", ios::in);
		if (file.is_open())
		{
			string DataLine;
			while (getline(file, DataLine))
			{
				clsUser user = _ConvertLineToUserObject(DataLine);
				vUsers.push_back(user);
			}
			file.close();
		}
		return vUsers;
	}

	string _ConvertUserObjToLine(clsUser user, string separator = "#//#")
	{
		string line = "";
		line += user.FirstName + separator + user.LastName + separator + user.Email + separator;
		line += user.Phone + separator + user.username + separator;
		line += user.password + separator + to_string(user._Permitions);
		return line;
	}

	string _PrepareLoginRecord(string separator = "#//#")
	{
		string RecordLine = "";
		RecordLine += clsDate::GetSystemDateTimeString() + separator + username
			+ separator + password + separator
			+ to_string(permitions);
		return RecordLine;
	}

	void _SaveDataInFile(vector<clsUser>& vUsers)
	{
		fstream file;
		file.open("Users.txt", ios::out);
		if (file.is_open())
		{
			string Line = "";
			for (clsUser& u : vUsers)
			{
				if (u._MarkForDelete == false)
				{
					u.password = clsUtil::EncryptText(u.password, 3);
					Line = _ConvertUserObjToLine(u);
					file << Line << endl;
				}
			}
			file.close();
		}
	}

	void _Update()
	{
		vector<clsUser> vUsers = _LoadUsersDataFromFile();
		for (clsUser& u : vUsers)
		{
			if (u.username == username)
			{
				u = *this;
				break;
			}
		}
		_SaveDataInFile(vUsers);
	}

	void _AddNew()
	{
		this->password = clsUtil::EncryptText(this->password, 3);
		_AddDataLineToFile(_ConvertUserObjToLine(*this));
	}

	void _AddDataLineToFile(string line)
	{
		fstream file;
		file.open("Users.txt", ios::out | ios::app);
		if (file.is_open())
		{
			file << line << endl;
			file.close();
		}
	}

	static stRegisterLogin _ConvertLoginRecordToLogin(string record)
	{
		vector<string> vLogins = clsString::Split(record, "#//#");
		stRegisterLogin login;
		login.dateTime = vLogins[0];
		login.username = vLogins[1];
		login.password = vLogins[2];
		login.permitions = stoi(vLogins[3]);
		return login;
	}

public:

	clsUser(enMode mode, string fName, string lName, string email, string phone,
		string username, string password, int permitions)
		: clsPerson(fName, lName, email, phone)
	{
		_Mode = mode;
		_Username = username;
		_Password = password;
		_Permitions = permitions;
	}

	enum enPermitions
	{
		All = -1, ShowClientsList = 1, AddNewClient = 2, DeleteClient = 4,
		UpdateClient = 8, FindClient = 16, Transactions = 32, ManageUsers = 64,
		LoginRegisterList = 128
	};

	void SetUsername(string username)
	{
		_Username = username;
	}
	string GetUsername()
	{
		return _Username;
	}
	_declspec(property(get = GetUsername, put = SetUsername)) string username;

	void SetPassword(string password)
	{
		_Password = password;
	}
	string GetPassword()
	{
		return _Password;
	}
	_declspec(property(get = GetPassword, put = SetPassword)) string password;

	void SetPermitions(int permitions)
	{
		_Permitions = permitions;
	}
	int GetPermitions()
	{
		return _Permitions;
	}
	_declspec(property(get = GetPermitions, put = SetPermitions)) int permitions;
	
	bool IsEmpty()
	{
		return _Mode == enMode::EmptyMode;
	}

	static clsUser Find(string username)
	{
		fstream file;
		file.open("Users.txt", ios::in);
		if (file.is_open())
		{
			string line;
			while (getline(file, line))
			{
				clsUser user = _ConvertLineToUserObject(line);
				if (user.username == username)
				{
					file.close();
					return user;
				}
			}
			file.close();
		}
		return _GetEmptyUserObject();
	}

	static clsUser Find(string username, string password)
	{
		fstream file;
		file.open("Users.txt", ios::in);
		if (file.is_open())
		{
			string line;
			while (getline(file, line))
			{
				clsUser user = _ConvertLineToUserObject(line);
				if (user.username == username && clsUtil::DecryptText(user.password, 3) == password)
				{
					file.close();
					return user;
				}
			}
			file.close();
		}
		return _GetEmptyUserObject();
	}

	enum enSaveResult { svFailedEmptyObject = 0, svSucceeded = 1, svFailedUserExisted = 2 };

	enSaveResult Save()
	{
		switch (_Mode)
		{
		case clsUser::EmptyMode:
			return enSaveResult::svFailedEmptyObject;
		case clsUser::UpdateMode:
			_Update();
			return enSaveResult::svSucceeded;
		case clsUser::AddNewMode:
			if (IsUserExist(username))
			{
				return enSaveResult::svFailedUserExisted;
			}
			else
			{
				_AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResult::svSucceeded;
			}
		}
	}

	void RegisterLogin()
	{
		fstream file;
		file.open("LoginRegister.txt", ios::out | ios::app);
		if (file.is_open())
		{
			string RecordLine = "";
			RecordLine += _PrepareLoginRecord();
			file << RecordLine << endl;
			file.close();
		}
	}

	static bool IsUserExist(string username)
	{
		clsUser user = Find(username);
		return !user.IsEmpty();
	}

	static clsUser GetAddNewUserObject(string username)
	{
		return clsUser(enMode::AddNewMode, "", "", "", "", username, "", 0);
	}

	bool Delete()
	{
		vector<clsUser> vUsers = _LoadUsersDataFromFile();
		for (clsUser& u : vUsers)
		{
			if (u.username == username)
			{
				u._MarkForDelete = true;
				break;
			}
		}
		_SaveDataInFile(vUsers);
		*this = _GetEmptyUserObject();
		return true;
	}

	static vector<clsUser> GetUsersList()
	{
		return _LoadUsersDataFromFile();
	}

	bool HasPermition(enPermitions permitions)
	{
		if (permitions == enPermitions::All)
			return true;
		if ((this->permitions & permitions) == permitions)
			return true;
		else
			return false;
	}

	struct stRegisterLogin
	{
		string dateTime, username, password;
		int permitions;
	};

	static vector<stRegisterLogin> LoadLoginDataFromFile(string fileName)
	{
		vector<stRegisterLogin> vLogins;
		fstream file;
		file.open(fileName, ios::in);
		if (file.is_open())
		{
			string recordLine = "";
			stRegisterLogin login;
			while (getline(file, recordLine))
			{
				login = _ConvertLoginRecordToLogin(recordLine);
				vLogins.push_back(login);
			}
			file.close();
		}
		return vLogins;
	}

	
};

