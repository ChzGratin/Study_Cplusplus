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

private:
	const size_t ACCOUNT_PER_PAGE = 10;
	void m_PageView();
	void m_ManageAccount(size_t index);

public:
	int Run()
	{
		m_PageView();
		return 0;
	}
};

#endif