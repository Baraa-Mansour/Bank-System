#pragma once
#include <iostream>
#include <string>


using namespace std;

namespace Validation
{
	int ReadNumber(string Message)
	{
		int number = 0;

		cout << Message << endl;
		cin >> number;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << "Invalid Numebr, Try Again" << endl;
			cin >> number;
		}

		return number;
	}

	double ReadDoubleNumber(string Message)
	{
		double number = 0;

		cout << Message << endl;
		cin >> number;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << "Invalid Numebr, Try Again" << endl;
			cin >> number;
		}

		return number;
	}

	int ReadNumberInRange(string Message, int From, int To)
	{
		int Number = ReadNumber(Message);

		while (Number < From || Number > To)
		{
			cout << "Number Out Of Range!, Try Again" << endl;
			Number = ReadNumber(Message);
		}

		return Number;
	}

	double ReadPositiveDoubleNumber(string Message)
	{
		double Number = ReadDoubleNumber(Message);

		while (Number < 0)
		{
			cout << "Number Should Be Positive!, Try Again" << endl;
			Number = ReadNumber(Message);
		}

		return Number;
	}

	bool IsEmpty(string& Line)
	{
		return Line.empty() || Line == " ";
	}

	bool ReadYorN(string Message)
	{
		char Choice = 'y';
		do
		{
			cout << Message << endl;
			cin >> Choice;
		} while (tolower(Choice) != 'y' && tolower(Choice) != 'n');

		return tolower(Choice) == 'y';
	}

	string ReadString(string Param)
	{
		string Value = "";

		cout << "Enter " << Param << " : ";
		getline(cin >> ws, Value);

		return Value;
	}
}

