#include "Header.h"

//Another functions - Another functions - Another functions - Another functions

void CheckType(Account* acc)
{
	if (typeid(*acc) == typeid(Admin))
	{
		cout << "This is an admin type\n";
	}
	else if(typeid(*acc) == typeid(User)){
		cout << "This is a user type\n";
	}
}

string Encrypter(string login)
{
	string elogin;
	for (int i = 0; i < login.size(); i++)
	{
		elogin += login[i] + 3;
	}
	return elogin;
}


string Decrypter(string login)
{
	string elogin;
	for (int i = 0; i < login.size(); i++)
	{
		elogin += login[i] - 3;
	}
	return elogin;
}

void AddInformation(string name, string surname, string patronymic, string path)
{
	ofstream out(path, ios::app | ios::out);
	out << name << " " << surname << " " << patronymic << "|" << "0" << "|" << "0" << endl;
	out.close();
}

void User::Registration() 
{
	cout << "----- Регистрация пользователя -----\n";

	string log, pass;
	cout << "Login :";
	getline(cin, log);
	userData.open(pathLogin, ios::out);
	string elogin = Encrypter(log);
	userData << elogin << "\n";
	userData.close();

	userData.open(pathPass,  ios::out);
	cout << "Pass :";
	getline(cin, pass);
	string epass = Encrypter(pass);
	userData << epass << "\n";
	userData.close();


	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, 10);
	cout << "Данные успешно записаны\n";
	SetConsoleTextAttribute(console, 7);
}


bool User::Authorization()
{

	cout << "\nПользователь уже зарегистрирован\n";
	cout << "Log :";
	getline(cin, mLogin);
	cout << "Pass :";
	getline(cin, mPassword);

	bool logIsTrue = false;
	bool passIsTrue = false;

	userData.open(pathLogin, ios::in);
	string l;
	while (getline(userData, l))
	{
		string buf = Decrypter(l);
		if (buf == mLogin)
		{
			logIsTrue = true;
			break;
		}
	}
	userData.close();

	userData.open(pathPass, ios::in);
	string p;
	while (getline(userData, p))
	{
		string buf = Decrypter(p);
		if (buf == mPassword)
		{
			passIsTrue = true;
			break;
		}
	}
	userData.close();

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


	if (passIsTrue && logIsTrue)
	{
		SetConsoleTextAttribute(hConsole, 10);

		cout << "\nВы успешно вошли в систему \n";
		SetConsoleTextAttribute(hConsole, 7);
		return true;
	}
	else
	{	
		SetConsoleTextAttribute(hConsole, 12);
		if (!logIsTrue) cout << "\nНекорректный логин\n";
		if (!passIsTrue) cout << "\nНекорректный пароль\n";
		SetConsoleTextAttribute(hConsole, 7);
		system("pause");
		return false;
	}
}


int User::CheckEmptyLogPass()
{
	userData.open(pathLogin, ios::in | ios::app);

	char s;
	int count = 0;
	while (userData.get(s))
	{
		count++;
		cout << s;
	}
	//cout << "count : " << count << endl;
	userData.close();

	cout << endl;

	userData.open(pathPass, ios::in);

	count = 0;
	while (userData.get(s))
	{
		count++;
		cout << s;
	}
	//cout << "count : " << count << endl;

	userData.close();
	return count;
}

int User::CheckEmptyPersonal()
{
	userData.open(pathPersonal, ios::in);
	char s;
	int count = 0;
	while (userData.get(s))
	{
		count++;
		break;
	}
	userData.close();

	return count;
}

void User::ChangeLogPass()
{
	userData.open(pathLogin, ios::app | ios::in);
	cout << "Текущий Логин пользователя : \n";
	string strL, strP;
	while (getline(userData, strL))
	{
		strL = Decrypter(strL);
		cout << strL << endl;
	}
	userData.close();
	userData.open(pathPass, ios::app | ios::in);
	cout << "Пароль пользователя : \n";
	while (getline(userData, strP))
	{
		strP = Decrypter(strP);
		cout << strP << endl;
	}


	cout << "\nЗаменить\n";
	cout << "1 - логин\n";
	cout << "2 - пароль\n";
	cout << "~>>>";
	int inp;
	cin >> inp;
	cin.ignore();
	if (inp == 1)
	{
		cout << "Новый логин пользователя :";
		string newLogin;
		getline(cin, newLogin);
		newLogin = Encrypter(newLogin);
		ofstream fout(pathLogin, ios::trunc);
		fout << newLogin;
		fout.close();

		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 10);
		cout << "\nЛогин успешно заменён \n";
		SetConsoleTextAttribute(hConsole, 7);
	}
	else if (inp == 2)
	{
		cout << "Новый пароль пользователя :";
		string newPass;
		getline(cin, newPass);

		newPass = Encrypter(newPass);

		ofstream fout(pathPass, ios::trunc);
		fout << newPass;
		fout.close();

		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 10);
		cout << "\nПароль успешно заменён \n";
		SetConsoleTextAttribute(hConsole, 7);

	}
	else cout << "Error\n";

}


void User::InitPersonalData()
{
	
	string buf;
	int count, indexOfStr;
	cout << "Персональные данные (Регистрация) :\n";
	cout << "Name :";
	getline(cin, name);
	cout << "Surname :";
	getline(cin,surname);
	cout << "Address :";
	getline(cin,address);
	cout << "Phone :";
	getline(cin,phone);

	ofstream fout(pathPersonal);

	fout << "Name :" << name << endl;
	fout << "Surame :" << surname << endl;
	fout << "Address :" << address << endl;
	fout << "Phone :" << phone << endl;

	fout.close();
}

void User::ShowPersonalData()
{
	ifstream fin(pathPersonal);
	string buf;
	while (getline(fin, buf))
	{
		cout << buf << endl;
	}
}

//Admin functions - Admin functions - Admin functions - Admin functions - Admin functions - Admin functions

void Admin::Registration()
{
	adminData.open(pathLogin, ios::out);

	cout << "\n----- Регистрация админа -----\n";
	cout << "Log :";
	getline(cin, mLogin);
	string elog = Encrypter(mLogin);
	
	adminData << elog << '\n';

	adminData.close();


	adminData.open(pathPass, ios::out);
	cout << "Pass :";
	getline(cin, mPassword);
	string epass = Encrypter(mPassword);
	adminData << epass << '\n';
	adminData.close();


	cout << "----- Admin has registered -----\n";
}

bool Admin::Authorization()
{

	cout << "\nАдмин уже зарегистрирован\n";
	cout << "Log :";
	getline(cin, mLogin);
	cout << "Pass :";
	getline(cin, mPassword);

	bool logIsTrue = false;
	bool passIsTrue = false;

	adminData.open(pathLogin, ios::in);
	string l;
	while (getline(adminData, l))
	{
		string buf = Decrypter(l);
		if (buf == mLogin)
		{
			logIsTrue = true;
		    break;
		}
	}
	adminData.close();

	adminData.open(pathPass, ios::in);
	string p;
	while (getline(adminData, p))
	{
		string buf = Decrypter(p);
		if (buf == mPassword)
		{
			passIsTrue = true;
			break;
		}
	}
	adminData.close();

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


	if (passIsTrue && logIsTrue)
	{
		SetConsoleTextAttribute(hConsole, 10);

		cout << "\nВы успешно вошли в систему \n";
		SetConsoleTextAttribute(hConsole, 7);
		return true;
	}
	else
	{
		SetConsoleTextAttribute(hConsole, 12);
		if (!logIsTrue) cout << "\nНекорректный логин\n";
		if (!passIsTrue) cout << "\nНекорректный пароль\n";
		SetConsoleTextAttribute(hConsole, 7);
		system("pause");
		return false;
	}
}

int Admin::CheckEmpty()
{
	adminData.open(pathLogin, ios::in);

	char s;
	int count = 0;
	cout << "Зашифрованный логин : ";
	while (adminData.get(s))
	{
		count++;
		cout << s;
	}
	//cout << "count : " << count << endl;

	adminData.close();

	cout << endl;

	adminData.open(pathPass, ios::in);

	cout << endl;
	cout << "Зашифрованный пароль : ";
	count = 0;
	while (adminData.get(s))
	{
		count++;
		cout << s;
	}
	//cout << "count : " << count << endl;

	adminData.close();


	return count;
}

void Admin::ChangeLogPass()
{
	    adminData.open(pathLogin, ios::in);

		string str,currentLog,currentPass;
		while (getline(adminData, str))
		{
			currentLog = str;
			break;
		}

		currentLog = Decrypter(currentLog);

		cout << "Текущий логин админа - " << currentLog << endl;

		adminData.close();

		adminData.open(pathPass, ios::in);

		while (getline(adminData, str))
		{
			currentPass = str;
			break;
		}

		currentPass = Decrypter(currentPass);

		cout << "Текущий пароль админа - " << currentPass << endl;

		adminData.close();

		cout << "1 - Замена логина\n2 - Замена пароля\n";
		cout << "~>>>";
		int choice;
		cin >> choice;
		cin.ignore();

		if (choice == 1)
		{
			cout << "Новый логин :";
			string newLogin;
			getline(cin, newLogin);

			newLogin = Encrypter(newLogin);

			adminData.open(pathLogin, ios::out);

			adminData << newLogin;

			adminData.close();
			
		}
		else if (choice == 2)
		{
			cout << "Новый пароль :";
			string newPass;
			getline(cin, newPass);

			newPass = Encrypter(newPass);

			adminData.open(pathPass, ios::out);
            
			adminData << newPass;

			adminData.close();
		}
		else
			cout << "Error\n";

}

void Admin::ChangePersonalData()
{

	string buf;
	ifstream fin("Data\\UserPersonal.txt");
	vector<string> strMass(4);

	int count = 0;
	while (getline(fin, buf))
	{
		strMass[count++] = buf;
	}
	fin.close();


	cout << " 0 - Name\n";
	cout << " 1 - Surname\n";
	cout << " 2 - Address\n";
	cout << " 3 - Phone\n";
	cout << ">>>";
	int indexOfStr;
	cin >> indexOfStr;
	cin.ignore();
	string str;
	if (indexOfStr == 0) //Name
	{
		cout << "New name : ";
		getline(cin, str);
		strMass[0] = "Name : " + str;
	}
	else if (indexOfStr == 1) // Surname
	{
		cout << "New surname : ";
		getline(cin, str);
		strMass[1] = "Surname : " + str;

	}
	else if (indexOfStr == 2) // Address
	{
		cout << "New address : ";
		getline(cin, str);
		strMass[2] = "Address : " + str;

	}
	else if (indexOfStr == 3) //Phone
	{
		cout << "New phone : ";
		getline(cin, str);
		strMass[3] = "Phone : " + str;
	}
	else
		cout << "Error\n";

	ofstream out("Data\\UserPersonal.txt");

	for (size_t i = 0; i < strMass.size(); i++)
	{
		out << strMass[i] << endl;
	}

	out.close();

}


void Admin::DeleteUser()
{
	User path;

	ofstream fout(path.pathPersonal, ios::trunc);
	fout.close();
	ofstream fout2(path.pathLogin, ios::trunc);
	fout2.close();
	ofstream fout3(path.pathPass, ios::trunc);
	fout3.close();
	ofstream fout4("Test\\Results\\TestResults.txt", ios::trunc);
	fout4.close();


	cout << "Пользователь удалён\n\n";
	cout << "Удалено : пароль,логин,личные данные, прохождение тестов\n";
}


