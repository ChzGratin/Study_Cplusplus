/*================================
작성자: 202035156 박정현
작성일: 2021-01-12
================================*/

#include "CAppAdmin.h"

//템플릿 클래스의 정의 포함 (템플릿 클래스의 헤더와 소스를 분리했기 때문)
//CAppATM은 템플릿 클래스 CDBManager와 연관됨
#include "CDBManager.cpp"

//================================================================

void CAppAdmin::m_PageView() //계좌를 1페이지에 ACCOUNT_PER_PAGE(=10)개씩 끊어서 출력; 페이지 넘기기; 계좌 선택
{
	wchar_t menu; //사용자 입력 (메뉴 코드)

	size_t curPage = 0; //현재 페이지; 0페이지에서 시작
	size_t curCount; //현재 페이지에 표시되는 계좌 수

	while (true)
	{
		size_t size = GetSize(); //전체 계좌 수; 업데이트

		system("cls");
		wcout << L"<202035156 박정현의 ATM_final (관리자)>" << endl
			<< L"================================" << endl
			<< L"[인덱스]: 계좌 ID" << endl;

		//계좌를 1페이지에 ACCOUNT_PER_PAGE(=10)개씩 끊어서 출력
		curCount = 0;
		for (size_t i = 0; i < ACCOUNT_PER_PAGE; i++)
		{
			if ((curPage * ACCOUNT_PER_PAGE + i) >= size) { break; }
			wcout << L"[" << i << L"]: ";
			wcout << GetRecord(curPage * ACCOUNT_PER_PAGE + i).GetName() << endl;
			curCount++;
		}
		wcout << L"================================" << endl;

		//메뉴 선택
		wcout << L" Q : 종료" << endl
			<< L"0~9: 계좌 선택 (인덱스를 입력)" << endl
			<< L" Z : 이전 페이지" << endl
			<< L" X : 다음 페이지" << endl
			<< L"================================" << endl
			<< L"메뉴 선택: ";
		wcin >> menu;

		//종료
		if (menu == L'Q' || menu == L'q') { return; }

		//계좌 선택
		if (L'0' <= menu && menu <= L'9')
		{
			if ((size_t)(menu - L'0') < curCount) //현재 페이지에서 선택할 수 있는 계좌라면
			{
				m_ManageAccount(curPage * ACCOUNT_PER_PAGE + menu - L'0'); //계좌 관리
				curPage = 0; //계좌 관리가 끝나면 첫 페이지로 복귀
			}
			continue;
		}

		//이전 페이지
		if (menu == L'Z' || menu == L'z')
		{
			if (curPage > 0) { curPage--; } //현재 페이지가 첫 페이지가 아니라면
			continue;
		}

		//다음 페이지
		if (menu == L'X' || menu == L'x')
		{
			if (curPage * ACCOUNT_PER_PAGE + curCount < size) { curPage++; } //현재 페이지가 마지막 페이지가 아니라면
			continue;
		}

		//default:
		wcout << L"잘못된 입력입니다." << endl;
		system("pause");
		continue;
	}
}

void CAppAdmin::m_ManageAccount(size_t index) //계좌 정보 출력; 계좌 삭제
{
	int menu; //사용자 입력 (메뉴 코드)

	while (true)
	{
		system("cls");
		wcout << L"<202035156 박정현의 ATM_final (관리자)>" << endl
			<< L"이름: " << GetRecord(index).GetName() << endl
			<< L"ID: " << GetRecord(index).GetID() << endl
			<< L"PW: " << GetRecord(index).GetPW() << endl
			<< L"계좌 잔액: " << GetRecord(index).GetBalance() << "원" << endl
			<< L"================================" << endl
			<< L" 0: 뒤로가기" << endl
			<< L"-1: 계좌 삭제" << endl
			<< L"================================" << endl
			<< L"메뉴 선택: ";
		wcin >> menu;

		switch (menu)
		{
		case 0: //뒤로가기
			return; //PageView()로 복귀

		case -1: //계좌 삭제
			wcout << L"<계좌 삭제>" << endl;
			DeleteRecord(index);
			wcout << L"계좌가 삭제되었습니다." << endl;
			system("pause");
			return; //PageView()로 복귀

		default:
			wcout << L"잘못된 입력입니다." << endl;
			system("pause");
			continue;
		}
	}
}