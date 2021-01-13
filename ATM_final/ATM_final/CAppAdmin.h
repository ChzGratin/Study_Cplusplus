/*================================
�ۼ���: 202035156 ������
�ۼ���: 2021-01-12
================================*/

#ifndef CAPPADMIN_H
#define CAPPADMIN_H

#include "CApp.h"
#include "CAccount.h"

#include <iostream>
#include <Windows.h>
using namespace std;

//ATM ���� ���α׷� Ŭ���� (������)
class CAppAdmin: public CApp<CAccount>
{
public:
	CAppAdmin(wstring FileName) : CApp(FileName)
	{
		//������ ����
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