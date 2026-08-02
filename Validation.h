#pragma once
#include <iostream>

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

	bool IsEmpty(string& Line)
	{
		return Line.empty() || Line == " ";
	}
}

