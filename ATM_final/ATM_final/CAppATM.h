/*================================
�ۼ���: 202035156 ������
�ۼ���: 2021-01-12
================================*/

#ifndef CAPPATM_H
#define CAPPATM_H

#include "CApp.h"
#include "CAccount.h"

#include <iostream>
#include <Windows.h>
using namespace std;

//ATM ���� ���α׷� Ŭ����
class CAppATM: public CApp<CAccount>
{
public:
	CAppATM(wstring FileName) : CApp<CAccount>(FileName)
	{
		//������ ����
		wcout.imbue(locale("kor"));
		wcin.imbue(locale("kor"));
	}

//protected:
	//CDBManager<CAccount> m_DBM; //DB Ŭ����
	//CAccount* m_curRecord; //���� CDBApp Ŭ������ ó���ϰ� �ִ� ���ڵ�; ������

private: //�޼ҵ��� ���Ǻΰ� �ʹ� ������� 2�� ���Ͽ� ������ ������
	//CAppATM_FrontPage.cpp
	void m_FrontPageMenu(); //����Ʈ������ �޴�
	void m_Exit();
	void m_LogIn(); //�α���
	void m_CreateAccount(); //���� ����

	//CAppATM_Service.cpp
	void m_ServiceMenu(); //���� �޴�
	void m_LogOut(); //�α׾ƿ�
	void m_Deposit(); //�Ա�
	void m_Withdraw(); //���
	void m_Transfer(); //��ü
	void m_DeleteAccount(); //���� ����

	//CAppATM_Admin.cpp
	void m_PageView(); //���¸� 1�������� 10���� ��� ���; ������ �ѱ��; ���� ����
	void m_ManageAccount(); //���� ���� ���; ���� ����

public:
	int Run()
	{
		m_FrontPageMenu(); //����Ʈ������ �޴����� ����
		return 0; //(���û���) main()�� ���ϰ�
	}
};

#endif