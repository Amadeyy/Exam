#include "Header.h"


string pathQuestions = "Test\\questions.txt";
string pathAnswers = "Test\\answers.txt";
string pathTestResults = "Test\\Results\\TestResults.txt";


void Questions::ReadingPassedTests()
	{
		ifstream fin(pathTestResults);
		string buf;

		try
		{
			if (!fin)
				throw "Ошибка при чтении файла ";

			fin >> buf;
			if (IsEmptyFile(buf))
			{
				throw "Файл Пустой (Нет пройденных тестов)\n";
			}
			fin.close();
			ifstream fin(pathTestResults);

			while (getline(fin, buf))
			{
				cout << buf << endl;
			}

		}
		catch (const char* ss)
		{
			cerr << ss << endl;
		}

		fin.close();
	}


int countLinesInFile() // Test\\answers.txt возвращает всегда на +1 больше
{
	ifstream fin2(pathAnswers);
	string buf2; int count = 1;
	while (getline(fin2, buf2))
	{
		count++;
	}
	fin2.close();

	return count;
}

bool Questions::IsEmptyFile(string s)
{
	for (size_t i = 0;i < s.length();i++)
	{
		if (s[i] != ' ' && s[i] != '\t' && s[i] != '\n')
			return false;
	}
	return true;
}



void User::passTheTest2()
{
	vector<char> vecOfAnswers(999);
	ifstream fin(pathQuestions);
	ifstream fin22(pathAnswers);
	string strBuf;

	int count = 0;

	char sym;

	if (!fin22)
		cout << "Error\n";

	while (fin22.get(sym))
	{
		if (sym == '|')
			count++;

		if (sym == 'a' || sym == 'b' || sym == 'c' || sym == 'd')
		{
			vecOfAnswers[count] = sym;
		}
	}
	
	fin22.close();

	int grade = 0;

	count = 0;
	while (!fin.eof())
	{
		while (getline(fin, strBuf)) {
			if (strBuf == "|")
			{
				cout << ">>>";
				char sBuf;
				cin >> sBuf;
                
				if (vecOfAnswers[count] == sBuf) grade++;

				count++;
			}
			else
			{
				cout << strBuf << endl;
			}
		}
	}
	fin.close();

	cout << "Ваша оценка : " << grade << " из " << countLinesInFile() - 1 << endl;


	ifstream fin2(pathTestResults);

	int countLines = 1;

	while (getline(fin2, strBuf))
	{
		countLines++;
	}
	fin2.close();

	ofstream fout(pathTestResults, ios::app);

	fout << "Результаты " << countLines << " теста : " << grade << " балла(ов) из " << countLinesInFile() - 1 << endl;

	fout.close();
}


void Admin::AddQuestion()
{
	cout << "Новый вопрос :";
	string buf,a,b,c,d,rightAnswer;
	getline(cin, buf);
	cout << "Варианты ответов :\n";
	cout << "a :";
	getline(cin, a);
	cout << "b :";
	getline(cin, b);
	cout << "c :";
	getline(cin, c);
	cout << "d :";
	getline(cin, d);
	while (true)
	{
	cout << "Правильный ответ : ";
	getline(cin, rightAnswer);
	if(rightAnswer != "a" && rightAnswer != "b" && rightAnswer != "c" && rightAnswer != "d")
	{
		cout << "Только a,b,c или d\n";
		continue;
	}
	break;
	}

	ofstream fout(pathQuestions, ios::app);
	fout << countLinesInFile() << ". " << buf << endl;
	fout << "\t" << "a. " << a << endl;
	fout << "\t" << "b. " << b << endl;
	fout << "\t" << "c. " << c << endl;
	fout << "\t" << "d. " << d << endl;
	fout << "|" << endl;
	fout.close();

	ofstream fout2(pathAnswers, ios::app);

	fout2 << countLinesInFile() << "." << rightAnswer << "|" << endl;

	fout2.close();

	cout << "Вопрос успешно добавлен\n";
}