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

//굳이 stack을 사용할 필요가 있나? Nope!
//wstring m_Log; 사용 규칙:
/* ex)
파일의 내용이 L"[입금] +10000원|[출금] -5000원|[이체] -3000원 ->Alice|[이체] +2000 <-Bob|" 이라면
순서대로 10000원 입금, 5000원 출금, 3000원을 내가 Alice에게 이체, 2000원을 Bob이 나에게 이체하였음을 의미
로그는 시간 순서대로 기록되며, 각 로그의 끝에는 구분자 L'|'를 삽입
기록된 로그가 없다면, 로그는 L"|[계좌 생성]|"이 됨 (L""로 하면 파일 입출력을 할 때 문제 발생)
*/

//은행 계좌 클래스
class CAccount : public CRecord
{
private:
	//wstring m_ID;
	wstring m_PW;
	wstring m_Name;
	ULL m_balance;
	wstring m_Log; //로그; 거래내역

public:
	static const ULL MAX_BALANCE = 100000000; //최대 예금액; static이므로 CAccount::MAX_BALANCE의 형태로 사용
	static const wchar_t DELIMITER = L'|'; //로그 구분자 (delimiter)

public:
	CAccount();
	CAccount(const CAccount&); //복사생성자

	void ReadFromFile(wfstream& fs);
	void WriteToFile(wfstream& fs);
	void PrintLog(); //로그 출력; wcout

	//wstring& GetID();
	wstring& GetPW();
	wstring& GetName();
	ULL& GetBalance();
	wstring& GetLog();
};

#endif