/*================================
작성자: 202035156 박정현
작성일: 2021-01-12
================================*/

#include "CAppATM.h"

//템플릿 클래스의 정의 포함 (템플릿 클래스의 헤더와 소스를 분리했기 때문)
//CAppATM은 템플릿 클래스 CDBManager와 CApp과 연관됨
#include "CApp.cpp"
#include "CDBManager.cpp"

//================================================================

void CAppATM::m_FrontPageMenu() //프론트페이지 메뉴
{
	int menu; //사용자 입력 (메뉴 코드)

	while (true)
	{
		system("cls");
		wcout << L"<202035156 박정현의 ATM_final>" << endl
			<< L"환영합니다." << endl
			<< L"================================" << endl
			<< L"0: 종료" << endl
			<< L"1: 로그인" << endl
			<< L"2: 계좌 생성" << endl
			<< L"================================" << endl
			<< L"메뉴 선택: ";
		wcin >> menu;

		switch (menu)
		{
		case 0: //종료
			m_Exit();
			return;
		case 1: //로그인
			m_LogIn();
			continue;
		case 2: //계좌 생성
			m_CreateAccount();
			continue;
		default:
			wcout << L"잘못된 입력입니다." << endl;
			system("pause");
			continue;
		}
	}
}

//----------------------------------------------------------------

void CAppATM::m_Exit()
{
	wcout << L"<종료>" << endl
		  << L"ATM을 종료합니다." << endl;
	system("pause");
}

void CAppATM::m_LogIn() //로그인; 좀 더 간단하고 현실적으로 구현
{
	wstring bufID, bufPW; //사용자 입력 (ID, PW)

	wcout << L"<로그인>" << endl;
	wcout << L"ID: ";
	wcin >> bufID;
	wcout << L"PW: ";
	wcin >> bufPW;

	int index = m_DBM.QueryRecord(bufID); //사용자가 입력한 ID에 대응하는 계좌의 인덱스 질의
	if (index < 0) //존재하지 않는 ID라면
	{
		wcout << L"존재하지 않는 계좌 ID입니다." << endl;
		system("pause");
		return;
	}
	else //ID가 존재한다면
	{
		if (m_DBM.GetRecord(index).GetPW() != bufPW) //잘못된 비밀번호라면
		{
			wcout << L"잘못된 비밀번호입니다." << endl;
			system("pause");
			return;
		}
		else //올바른 비밀번호라면; 로그인 성공
		{
			m_curRecord = &(m_DBM.GetRecord(index)); //CDBApp 클래스가 처리할 레코드를 지정

			wcout << m_curRecord->GetName() << L"님 안녕하세요." << endl;
			system("pause");

			m_ServiceMenu(); //서비스 메뉴 실행
			return;
		}
	}
}

void CAppATM::m_CreateAccount() //계좌 생성
{
	wstring bufID, bufPW, bufName; //사용자 입력 (ID, PW, 이름)

	wcout << L"<계좌 생성>" << endl;
	wcout << L"ID: ";
	wcin >> bufID;

	if (m_DBM.QueryRecord(bufID) >= 0) //이미 등록된 계좌 ID라면
	{
		wcout << L"이미 등록된 계좌 ID입니다." << endl;
		system("pause");
		return;
	}

	wcout << L"PW: ";
	wcin >> bufPW;
	wcout << L"이름: ";
	wcin >> bufName;

	CAccount tmpAcc; //생성할 계좌의 정보를 임시로 저장할 변수
	tmpAcc.GetID() = bufID;
	tmpAcc.GetPW() = bufPW;
	tmpAcc.GetName() = bufName;
	m_DBM.AddRecord(tmpAcc);

	wcout << bufName << L"님의 계좌가 생성되었습니다." << endl;
	system("pause");
	return;
}