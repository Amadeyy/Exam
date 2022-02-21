#include "Header.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	//com
	Admin adminVar;
	User userVar;
	Questions q;

	while (true)
	{
	system("cls");
	cout << "----------------------------------\n";
	cout << "1 - Вход для админа\n"; //пароль и логин 123 123
	cout << "2 - Вход для тестируемого\n"; //пароль и логин 123 123
	cout << "0 - Выход из программы\n";
	cout << "----------------------------------\n";
	cout << ">>> : ";
	int globalchoice;
	cin >> globalchoice;
	cin.ignore(123, '\n');

	if (globalchoice == 1)
	{
		if (adminVar.CheckEmpty() == 0)
		{
			adminVar.Registration();
		}
		else
		{
			if (adminVar.Authorization() == true)
			{
				int choice = -1;
				while (choice != 0)
				{
					system("pause");
					system("cls");
					cout << "------------------------------------------------\n";
					cout << "\nМеню администратора \n";
					cout << "\n1 - замена пароля и/или логина\n";
					cout << "\n2 - изменить личные данные пользователя\n";
					cout << "\n3 - удалить текущего пользователя\n";
					cout << "\n4 - Управление тестированием \n";
					cout << "\n0 - выйти в меню\n";
					cout << "------------------------------------------------\n";
					cout << "\n~>>> :";
					cin >> choice;
					cin.ignore();

					switch (choice)
					{
					case 1:
					{
						cout << "---------------------------\n";
						cout << "\nChange Profile\n";
						cout << "1 - Admin\\ 2 - User\n";
						cout << "0 - назад\n";
						cout << "---------------------------\n";
						cout << "\n~>>> :";
						cin >> choice;

						if (choice == 1)
						{
							adminVar.ChangeLogPass();
						}
						else if (choice == 2)
						{
							userVar.ChangeLogPass();
						}
						else if (choice == 0) cout << "....\n";
						else
						{
							cout << "Error\n";
						}
					}
					break;
					case 2:
					{
						userVar.ShowPersonalData();
						adminVar.ChangePersonalData();
					}
					break;
					case 3:
			        	adminVar.DeleteUser();
						break;
					case 4:
						cout << "-------------------------\n";
						cout << "1 - Добавить вопрос\n";
						cout << "0 - выйти\n";
						cout << "-------------------------\n";
						cout << "~>>>";
						cin >> choice;
						cin.ignore();
						if (choice == 1)
						{
							adminVar.AddQuestion();
						}
						else if (choice == 0) "выход...\n"; break;

						break;
					case 0: break;
					default:
						cout << "Error\n";
						break;
					}
				}
			}
		}
	}
	else if (globalchoice == 2)
	{
		if (userVar.CheckEmptyLogPass() == 0)
		{
	 	    userVar.Registration();
		}
		else
		{
			if (userVar.Authorization() == true)
			{
				int choice = -1;
				while (choice != 0)
				{
					system("pause");
					system("cls");
					cout << "---------------------------------------\n";
					cout << "\nМеню пользователя \n";
					cout << "\n1 - Личный кабинет\n";
					cout << "\n2 - Пройти тест\n";
					cout << "\n3 - Результаты пройденных тестов\n";
					cout << "\n0 - выйти в меню\n";
					cout << "---------------------------------------\n";
					cout << "\n>>> :";
					cin >> choice;
					cin.ignore();

					switch (choice)
					{
					case 1:
					{
						if (userVar.CheckEmptyPersonal() == 0)
						{
							userVar.InitPersonalData();
						}
						else
						{
							userVar.ShowPersonalData();
						}
					}
					break;
					case 2:
					{
						userVar.passTheTest2();
					}
					break;
					case 3:
					{
						q.ReadingPassedTests();
					}
					break;
					case 0:cout << "___выход в меню___\n"; break;
					default:
						cout << "Error\n";
						break;
					}
				}
			}
			
		}

	}
	else if (globalchoice == 0) exit(0);
	else
	{
		cout << "Error\n";
	}	


	}//while(true)

	return 0;
}
