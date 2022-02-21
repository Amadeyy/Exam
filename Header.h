#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>
#include <conio.h>

using namespace std;


//void AddInformation(string name, string surname, string patronymic, string path);

string Decrypter(string login);
string Encrypter(string login);

class Account // базовый класс (полиморфизм)
{
protected:
	string mLogin;
	string mPassword;

public:

	Account()
	{
	}

	virtual void Registration() = 0;
	virtual bool Authorization() = 0;
	
};

class User : public Account
{
protected:
	fstream userData;
	string pathLogin;
	string pathPass;
	string pathPersonal;

	string DecryptedLogin;
	string DecryptedPassword;

	//char name[40],surname[40], address[40], phone[40];

	string name, surname, address, phone;
public:

	User()
	{
		pathLogin = "Data\\UserLogin.txt";
		pathPass = "Data\\UserPassword.txt";
		pathPersonal = "Data\\UserPersonal.txt";
	}

	void Registration() override;

	bool Authorization() override;

	int CheckEmptyLogPass();
	int CheckEmptyPersonal();

	void ChangeLogPass();

	void InitPersonalData();
	void ShowPersonalData();
	
	void passTheTest();
	void passTheTest2();

	string getDecryptedLogin();
	string getDecryptedPass();


	friend class Admin;
};


class Admin : public Account
{
private:
	fstream adminData;
	string pathLogin;
	string pathPass;
	/*string mLogin;
	string mPassword;*/
	bool adminEntrance;
	string DecryptedLogin;
	string DecryptedPassword;

public:
	Admin()
	{
		adminEntrance = false;
		pathPass = "Data\\AdminPass.txt";
		pathLogin = "Data\\AdminLogin.txt";
	}


	void Registration() override;

	bool Authorization() override;

	void ChangeLogPass();

	int CheckEmpty();

	void ChangePersonalData(); 

	void DeleteUser();

	void AddQuestion();
	void DeleteQuestion();

};

void CheckType(Account* acc);


class Questions
{
private:

public:

	Questions() = default;

	void ReadingPassedTests();

	bool IsEmptyFile(string s);

};