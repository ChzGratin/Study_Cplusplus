#include <iostream>
#include "BitString.h"

using namespace std;

struct testStruct
{
	char tS_c;
	int tS_i;
};

class testClass
{
private:
	char tC_c;
	int tC_i;

public:
	testClass()
	{
		tC_c = 0;
		tC_i = 0;
	}

	testClass(char arg_c, int arg_i)
	{
		tC_c = arg_c;
		tC_i = arg_i;
	}

	testClass(testClass& arg_tC)
	{
		tC_c = arg_tC.tC_c;
		tC_i = arg_tC.tC_i;
	}
};

int main()
{
	cout << "<ASCII>" << endl;
	BitString<char> BS_c('C');
	BS_c.printBitString();

	cout << endl;

	cout << "<Signed Integer (2's Complement)>" << endl;
	BitString<int> BS_i;

	BS_i.refData() = 2020;
	BS_i.printBitString();

	BS_i.refData() = -2020;
	BS_i.printBitString();

	BS_i.refData() = 0;
	BS_i.printBitString();

	cout << endl;

	cout << "<Floating Point (IEEE 754)>" << endl;
	BitString<float> BS_pi(3.141593f);
	BS_pi.printBitString();

	cout << "<Floating Point (IEEE 754 Double)>" << endl;
	BitString<double> BS_e(2.718282);
	BS_e.printBitString();

	cout << endl;

	cout << "<struct (Alignment Restriction)>" << endl;
	testStruct tS = { 0b01010101, 0b00001111000011110000111100001111 };
	BitString<testStruct> BS_tS(tS);
	BS_tS.printBitString();

	cout << endl;

	cout << "<class (Alignment Restriction)>" << endl;
	testClass tC(0b01010101, 0b00001111000011110000111100001111);
	BitString<testClass> BS_tC(tC);
	BS_tC.printBitString();
}