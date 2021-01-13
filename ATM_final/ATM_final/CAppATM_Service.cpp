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

void CAppATM::m_ServiceMenu() //서비스 메뉴
{
	int menu; //사용자 입력 (메뉴 코드)

	while (true)
	{
		system("cls");
		wcout << L"<202035156 박정현의 ATM_final>" << endl
			<< m_curRecord->GetName() << L"님의 계좌 잔액: " << m_curRecord->GetBalance() << L"원" << endl
			<< L"================================" << endl
			<< L" 0: 로그아웃" << endl
			<< L" 1: 입금" << endl
			<< L" 2: 출금" << endl
			<< L" 3: 이체" << endl
			<< L"-1: 계좌 삭제" << endl
			<< L"================================" << endl
			<< L"메뉴 선택: ";
		wcin >> menu;

		switch (menu)
		{
		case 0: //로그아웃
			m_LogOut();
			return; //프론트페이지로 복귀
		case 1: //입금
			m_Deposit();
			continue;
		case 2: //출금
			m_Withdraw();
			continue;
		case 3: //이체
			m_Transfer();
			continue;
		case -1: //계좌 삭제
			m_DeleteAccount();
			return; //프론트페이지로 복귀
		default:
			wcout << L"잘못된 입력입니다." << endl;
			system("pause");
			continue;
		}
	}
}

//----------------------------------------------------------------

void CAppATM::m_LogOut() //로그아웃
{
	m_curRecord = nullptr; //CDBApp 클래스가 처리하도록 지정했던 레코드를 해제

	wcout << L"<로그아웃>" << endl
		  << L"정상적으로 로그아웃 되었습니다." << endl;
	system("pause");
	return;
}

void CAppATM::m_Deposit() //입금
{
	ULL bufCash; //사용자 입력 (입금액)

	wcout << L"<입금>" << endl;
	wcout << L"입금액: ";
	wcin >> bufCash;

	if (m_curRecord->GetBalance() + bufCash <= CAccount::MAX_BALANCE) //최대 예금액을 초과하지 않을 때
	{
		m_curRecord->GetBalance() += bufCash;

		wcout << bufCash << L"원이 입금되었습니다." << endl;
		system("pause");
		return;
	}
	else //최대 예금액을 초과할 때
	{
		wcout << L"계좌의 최대 예금액을 초과하여," << endl
			  << CAccount::MAX_BALANCE - m_curRecord->GetBalance() << L"원이 입금되었습니다." << endl;
		system("pause");

		m_curRecord->GetBalance() = CAccount::MAX_BALANCE;
		return;
	}
}

void CAppATM::m_Withdraw() //출금
{
	ULL bufCash; //사용자 입력 (출금액)

	wcout << L"<출금>" << endl;
	wcout << L"출금액: ";
	wcin >> bufCash;

	if (m_curRecord->GetBalance() >= bufCash) //잔액이 부족하지 않을 때
	{
		m_curRecord->GetBalance() -= bufCash;

		wcout << bufCash << L"원이 출금되었습니다." << endl;
		system("pause");
		return;
	}
	else //잔액이 부족할 때
	{
		wcout << L"계좌의 잔액이 부족하여," << endl
			  << m_curRecord->GetBalance() << L"원이 출금되었습니다." << endl;
		system("pause");

		m_curRecord->GetBalance() = 0;
		return;
	}
}


void CAppATM::m_Transfer() //이체
{
	ULL bufTransfer; //사용자 입력 (이체액)
	wstring bufID_to; //사용자 입력 (입금계좌 ID); transfer "to"

	wcout << L"<이체>" << endl;
	wcout << L"출금액: ";
	wcin >> bufTransfer;
	wcout << L"입금계좌 ID: ";
	wcin >> bufID_to;

	//입금계좌 존재여부 및 잔액 확인
	int index = QueryRecord(bufID_to); //사용자가 입력한 ID에 대응하는 계좌의 인덱스 질의
	if (index < 0) //존재하지 않는 계좌라면
	{
		wcout << L"[입금계좌 검색 실패] 이체실패" << endl;
		system("pause");
		return;
	}
	else //계좌가 존재한다면
	{
		if (GetRecord(index).GetBalance() + bufTransfer > CAccount::MAX_BALANCE) //최대 예금액을 초과할 떄
		{
			bufTransfer = CAccount::MAX_BALANCE - GetRecord(index).GetBalance(); //이체액 재계산

			wcout << L"[입금계좌 잔액 초과] "
				  << bufTransfer << L"원을 이체합니다." << endl;
		}
	}

	//출금계좌 잔액 확인
	if (m_curRecord->GetBalance() < bufTransfer) //잔액이 부족할 때
	{
		bufTransfer = m_curRecord->GetBalance(); //이체액 재계산

		wcout << L"[출금계좌 잔액 부족] "
			  << m_curRecord->GetBalance() << L"원을 이체합니다." << endl;
	}

	//이체 수행
	m_curRecord->GetBalance() -= bufTransfer; //출금
	GetRecord(index).GetBalance() += bufTransfer; //입금
	wcout << L"이체성공" << endl;
	system("pause");
	return;
}

void CAppATM::m_DeleteAccount() //계좌 삭제
{
	wcout << L"<계좌 삭제>" << endl;

	int index = QueryRecord(m_curRecord->GetID()); //현재 사용자의 레코드에 대응되는 인덱스 질의
	DeleteRecord(index); //현재 사용자의 레코드 제거
	m_curRecord = nullptr; //메모리가 해제되었으므로 nullptr 처리

	wcout << L"계좌가 삭제되었습니다." << endl;
	system("pause");
	return;
}