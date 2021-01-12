/*================================
작성자: 202035156 박정현
작성일: 2021-01-12
================================*/

#ifndef CAPPATM_H
#define CAPPATM_H

#include "CApp.h"
#include "CAccount.h"

#include <iostream>
#include <Windows.h>
using namespace std;

//ATM 응용 프로그램 클래스
class CAppATM: public CApp<CAccount>
{
public:
	CAppATM(wstring FileName) : CApp<CAccount>(FileName)
	{
		//로케일 설정
		wcout.imbue(locale("kor"));
		wcin.imbue(locale("kor"));
	}

//protected:
	//CDBManager<CAccount> m_DBM; //DB 클래스
	//CAccount* m_curRecord; //현재 CDBApp 클래스가 처리하고 있는 레코드; 포인터

private: //메소드의 정의부가 너무 길어져서 2개 파일에 나누어 정의함
	//CAppATM_FrontPage.cpp
	void m_FrontPageMenu(); //프론트페이지 메뉴
	void m_Exit();
	void m_LogIn(); //로그인
	void m_CreateAccount(); //계좌 생성

	//CAppATM_Service.cpp
	void m_ServiceMenu(); //서비스 메뉴
	void m_LogOut(); //로그아웃
	void m_Deposit(); //입금
	void m_Withdraw(); //출금
	void m_Transfer(); //이체
	void m_DeleteAccount(); //계좌 삭제

	//CAppATM_Admin.cpp
	void m_PageView(); //계좌를 1페이지에 10개씩 끊어서 출력; 페이지 넘기기; 계좌 선택
	void m_ManageAccount(); //계좌 정보 출력; 계좌 삭제

public:
	int Run()
	{
		m_FrontPageMenu(); //프론트페이지 메뉴에서 시작
		return 0; //(선택사항) main()의 리턴값
	}
};

#endif