/*================================
작성자: 202035156 박정현
작성일: 2021-01-12
================================*/

#ifndef CACCOUNT_H
#define CACCOUNT_H

#include "CRecord.h"

#include <iostream>
using namespace std;

typedef unsigned long long ULL;
enum ID_BANK { IDB_NULL, IDB_KB, IDB_SHINHAN, IDB_WOORI, IDB_HANA, IDB_CITY }; //IDB = ID + Bank

//은행 계좌 클래스
class CAccount : public CRecord
{
private:
	int m_ID_Bank; //unused
	//wstring m_ID;
	wstring m_PW;
	wstring m_Name;
	ULL m_balance;

public:
	static const ULL MAX_BALANCE = 100000000; //최대 예금액; static이므로 CAccount::MAX_BALANCE의 형태로 사용

public:
	CAccount();
	CAccount(const CAccount&); //복사생성자

	void ReadFromFile(wfstream& fs);
	void WriteToFile(wfstream& fs);

	int& GetID_Bank();
	//wstring& GetID();
	wstring& GetPW();
	wstring& GetName();
	ULL& GetBalance();
};

#endif