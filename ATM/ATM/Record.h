/*================================
작성자: 202035156 박정현
작성일: 2021-01-06
================================*/

#ifndef RECORD_H
#define RECORD_H

#include <fstream>
#include <string>

typedef unsigned long long ULL;

using namespace std;

class Record
{
private:
	wstring m_ID;
	wstring m_PW;
	wstring m_Name;
	ULL m_Balance;

public:
	Record();
	Record(wstring id, wstring pw, wstring name, ULL balance);

	wstring& GetID();
	wstring& GetPW();
	wstring& GetName();
	ULL& GetBalance();

	friend wfstream& operator>>(wfstream& fs, Record& Rec);
	friend wfstream& operator<<(wfstream& fs, Record& Rec);
};

#endif