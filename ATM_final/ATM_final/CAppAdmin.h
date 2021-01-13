/*================================
작성자: 202035156 박정현
작성일: 2021-01-12
================================*/

#ifndef CAPPADMIN_H
#define CAPPADMIN_H

#include "CApp.h"
#include "CAccount.h"

#include <iostream>
#include <Windows.h>
using namespace std;

//ATM 응용 프로그램 클래스 (관리자)
class CAppAdmin: public CApp<CAccount>
{
public:
	CAppAdmin(wstring FileName) : CApp(FileName)
	{
		//로케일 설정
		wcout.imbue(locale("kor"));
		wcin.imbue(locale("kor"));
	}

//protected:
	//CAccount* m_curRecord; //현재 CDBApp 클래스가 처리하고 있는 레코드; 포인터

private:
	const size_t ACCOUNT_PER_PAGE = 10;
	void m_PageView();
	void m_ManageAccount();
	void m_ViewLog(); //거래내역 조회

public:
	int Run()
	{
		m_PageView();
		return 0;
	}
};

#endif