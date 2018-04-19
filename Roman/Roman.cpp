// Roman.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <regex>
#include <map>

using namespace std;

class Roman {
	const int minRoman = 1;
	const int maxRoman = 3999;
  public:	
	int decimal = 0;
	
	string longForm() {
		string M[] = { "", "M̅", "M̅M̅", "M̅M̅M̅" };
		string C[] = { "", "C", "CC", "CCC", "CCCC", "D", "DC", "DCC", "DCCC", "DCCCC" };
		string X[] = { "", "X", "XX", "XXX", "XXXX", "L", "LX", "LXX", "LXXX", "LXXXX" };
		string I[] = { "", "I", "II", "III", "IIII", "V", "VI", "VII", "VIII", "VIIII" };
		return M[decimal / 1000] + C[(decimal % 1000) / 100] + X[(decimal % 100) / 10] + I[decimal % 10];
	}

	string shortForm() {
		string M[] = { "", "M", "MM", "MMM" };
		string C[] = { "", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM" };
		string X[] = { "", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC" };
		string I[] = { "", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX" };
		return M[decimal / 1000] + C[(decimal % 1000) / 100] + X[(decimal % 100) / 10] + I[decimal % 10];
	}
	
	string lowerLongForm() {
		string str = longForm();

		transform(str.begin(),
			str.end(),
			str.begin(),
			[](unsigned char const &c) {
			return ::tolower(c);
		});

		return str;
	}

	string lowerShortForm() {
		string str = shortForm();

		transform(str.begin(),
			str.end(),
			str.begin(),
			[](unsigned char const &c) {
			return ::tolower(c);
		});

		return str;
	}

	Roman(int x) {
		if (x >= minRoman && x <= maxRoman) decimal = x;
	}

	Roman(const string x) {
		string str = x;

		enum digits { I = 1, V = 5, X = 10, L = 50, C = 100, D = 500, M = 1000 };
		
		map<char, int> charValue = { { 'M', M },{ 'D', D },{ 'C', C },{ 'L', L },{ 'X', X}, { 'V', V },{ 'I', I } };
		
		struct TFormat {
			string Short;
			string Long;
		}aFormat[] = { {"IV","IIII"},{"IIX","VIII"}, {"IX","VIIII"},{"XL","XXXX"},{"XC","LXXXX"},{"CD","CM"},{"CM","DCCCC"} };

		transform(str.begin(),
			str.end(),
			str.begin(),
			[](unsigned char const &c) {
			return ::toupper(c);
		});

		// convert shortForm to longForm by replacing Short format with Long format.
		for (TFormat thisFormat : aFormat) {
			str = regex_replace(str, regex(thisFormat.Short), thisFormat.Long);
		}

		decimal = 0;

        //  sum all values in long format
		try {
			for (char thisChar : str) {
				decimal += charValue.find(thisChar)->second;
			}
		} catch (...) {
			decimal = 0;
		}

		if (decimal > maxRoman) decimal = 0;
	}
};


int main()
{
	Roman r1(14);
	Roman r2("MDCCXLIII");

	cout << r1.longForm() << endl;
	cout << r1.shortForm() << endl;
	cout << r1.lowerShortForm() << endl;
	cout << r2.decimal << endl;

	system("PAUSE");

	return 0;
}

