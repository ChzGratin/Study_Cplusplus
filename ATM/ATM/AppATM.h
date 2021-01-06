/*================================
�ۼ���: 202035156 ������
�ۼ���: 2021-01-06
================================*/

#ifndef AppATM_H
#define AppATM_H

#include "DBManager.h"
#include "Record.h"
#include <iostream>
#include <Windows.h>

using namespace std;

class AppATM : DBManager
{
public:
	AppATM(wstring fileName);
	int Run();

private:
	const ULL MAX_BALANCE = 100000000;
	Record* m_curUser;

	void Exit(); //����
	int LogIn(); //�α���; Success: 1, Fail: 0
	void CreateAccount(); //���� ����

	void Service(); //ATM ����
};

#endif