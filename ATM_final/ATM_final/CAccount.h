/*================================
작성자: 202035156 박정현
작성일: 2021-01-12
================================*/

#ifndef CACCOUNT_H
#define CACCOUNT_H

#include "CRecord.h"

#include <iostream>
#include <stack>
using namespace std;

typedef unsigned long long ULL;
enum ID_BANK { IDB_NULL, IDB_KB, IDB_SHINHAN, IDB_WOORI, IDB_HANA, IDB_CITY }; //IDB = ID + Bank

//stack<wstring> m_Log; 사용 규칙:
/*
ex) 파일의 내용이 L"입금10000|출금5000|이체3000->Alice|이체2000<-Bob" 이라면
    순서대로 10000원 입금, 5000원 출금, 3000원을 내가 Alice에게 이체, 2000원을 Bob이 나에게 이체하였음을 의미
*/

//은행 계좌 클래스
class CAccount : public CRecord
{
private:
	int m_ID_Bank; //unused
	//wstring m_ID;
	wstring m_PW;
	wstring m_Name;
	ULL m_balance;
	//stack<wstring> m_Log; //입금, 출금, 계좌이체에 대한 로그; 가장 최근의 로그가 스택의 맨 위에 위치함

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