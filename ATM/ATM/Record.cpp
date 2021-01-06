/*================================
작성자: 202035156 박정현
작성일: 2021-01-06
================================*/

#include "Record.h"

Record::Record()
{
	m_ID = L"";
	m_PW = L"";
	m_Name = L"";
	m_Balance = 0;
}

Record::Record(wstring id, wstring pw, wstring name, ULL balance)
{
	m_ID = id;
	m_PW = pw;
	m_Name = name;
	m_Balance = balance;
}

wstring& Record::GetID() { return m_ID; }
wstring& Record::GetPW() { return m_PW; }
wstring& Record::GetName() { return m_Name; }
ULL& Record::GetBalance() { return m_Balance; }

wfstream& operator>>(wfstream& fs, Record& Rec) //Read from File
{
	getline(fs, Rec.m_ID);
	getline(fs, Rec.m_PW);
	getline(fs, Rec.m_Name);

	//Use _wtoi() to read m_Balance correctly
	wstring buf;
	getline(fs, buf);
	Rec.GetBalance() = _wtoi(buf.c_str());

	return fs;
}

wfstream& operator<<(wfstream& fs, Record& Rec) //Write to File
{
	fs << Rec.m_ID << endl
	   << Rec.m_PW << endl
	   << Rec.m_Name << endl
	   << Rec.m_Balance << endl;

	return fs;
}