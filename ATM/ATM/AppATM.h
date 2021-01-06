/*================================
작성자: 202035156 박정현
작성일: 2021-01-06
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

	void Exit(); //종료
	int LogIn(); //로그인; Success: 1, Fail: 0
	void CreateAccount(); //계좌 생성

	void Service(); //ATM 서비스
};

#endif