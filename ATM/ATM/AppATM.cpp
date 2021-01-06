/*================================
작성자: 202035156 박정현
작성일: 2021-01-06
================================*/

#include "AppATM.h"

AppATM::AppATM(wstring fN): DBManager(fN)
{
	wcout.imbue(locale("kor"));
	wcin.imbue(locale("kor"));
	m_curUser = nullptr;
}

int AppATM::Run()
{
	int menu;

	while (true)
	{
		system("cls");
		wcout << L"<202035156 박정현의 ATM>" << endl;
		wcout << L"환영합니다! (0: 종료, 1: 로그인, 2: 계좌 생성): ";
		wcin >> menu;

		switch (menu)
		{
		case 0: //종료
			Exit();
			return 0;

		case 1: //로그인
			if (!LogIn()) { break; };
			Service();
			break;

		case 2: //계좌 생성
			CreateAccount();
			break;

		default:
			wcout << L"잘못된 입력입니다." << endl;
			system("pause");
			break;
		}
	}
	

	return 0;
}

void AppATM::Exit() //종료
{
	wcout << L"<종료>" << endl;
	wcout << L"ATM을 종료합니다." << endl;
	system("pause");
}

int AppATM::LogIn() //로그인; Success: 1, Fail: 0
{
	//로그인 시도
	wstring bufID, bufPW;
	int bufIndex;

	wcout << L"<로그인>" << endl;
	wcout << L"ID: ";
	wcin >> bufID;
	wcout << L"PW: ";
	wcin >> bufPW;

	bufIndex = QueryRecord(bufID);
	if (bufIndex >= 0)
	{
		if (m_DB[bufIndex].GetPW() != bufPW)
		{
			wcout << L"잘못된 비밀번호입니다." << endl;
			system("pause");
			return 0;
		}
	}
	else
	{
		wcout << L"존재하지 않는 계좌 ID입니다." << endl;
		system("pause");
		return 0;
	}
	
	//로그인 성공
	m_curUser = &m_DB[bufIndex];
	return 1;
}

void AppATM::CreateAccount() //계좌 생성
{
	wstring bufID, bufPW, bufName;

	wcout << L"<계좌 생성>" << endl;

	wcout << L"ID: ";
	wcin >> bufID;

	if (QueryRecord(bufID) >= 0)
	{
		wcout << L"이미 등록된 계좌 ID입니다." << endl;
		system("pause");
		return;
	}

	wcout << L"PW: ";
	wcin >> bufPW;
	wcout << L"이름: ";
	wcin >> bufName;

	Record tmpRec(bufID, bufPW, bufName, 0);
	AddRecord(tmpRec);

	wcout << bufName << L"님의 계좌가 생성되었습니다." << endl;
	system("pause");
	return;
}

void AppATM::Service() //ATM 서비스
{
	int menu;
	ULL bufCash;

	while (true)
	{
		system("cls");
		wcout << L"<202035156 박정현의 ATM>" << endl;
		wcout << m_curUser->GetName() << L"님의 계좌 잔액: " << m_curUser->GetBalance() << L"원" << endl;
		wcout << L"(0: 로그아웃, 1: 입금, 2: 출금): ";
		wcin >> menu;

		switch (menu)
		{
		case 0: //로그아웃
			wcout << L"<로그아웃>" << endl;
			wcout << L"정상적으로 로그아웃 되었습니다." << endl;
			system("pause");

			m_curUser = nullptr;
			return;

		case 1: //입금
			wcout << L"<입금>" << endl;
			wcout << L"입금액: ";
			wcin >> bufCash;

			if (m_curUser->GetBalance() + bufCash <= MAX_BALANCE)
			{
				wcout << bufCash << L"원이 입금되었습니다." << endl;
				system("pause");

				m_curUser->GetBalance() += bufCash;
				break;
			}
			else
			{
				wcout << L"계좌의 최대 예금액을 초과하여," << endl;
				wcout << MAX_BALANCE - m_curUser->GetBalance() << L"원이 입금되었습니다." << endl;
				system("pause");

				m_curUser->GetBalance() = MAX_BALANCE;
				break;
			}

		case 2: //출금
			wcout << L"<출금>" << endl;
			wcout << L"출금액: ";
			wcin >> bufCash;

			if (m_curUser->GetBalance() >= bufCash)
			{
				wcout << bufCash << L"원이 출금되었습니다." << endl;
				system("pause");

				m_curUser->GetBalance() -= bufCash;
				break;
			}
			else
			{
				wcout << L"계좌의 잔액이 부족하여," << endl;
				wcout << m_curUser->GetBalance() << L"원이 출금되었습니다." << endl;
				system("pause");

				m_curUser->GetBalance() = 0;
				break;
			}

		default:
			wcout << L"잘못된 입력입니다." << endl;
			system("pause");
			break;
		}
	}
}