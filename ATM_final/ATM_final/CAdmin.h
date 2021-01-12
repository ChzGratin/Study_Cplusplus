/*================================
�ۼ���: 202035156 ������
�ۼ���: 2021-01-12
================================*/

#include "CAccount.h"
#include "CDBManager.h"

#include <iostream>
#include <Windows.h>
using namespace std;

#ifndef CADMIN_H
#define CADMIN_H

//ATM ���� ���α׷� Ŭ���� (������)
class CAdmin: public CDBManager<CAccount>
{
public:
	CAdmin(wstring FileName) : CDBManager<CAccount>(FileName)
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