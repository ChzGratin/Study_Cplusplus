#include "Record.h"
#include "DBManager.h"
#include "ATM_UI.h" //ATM의 기능과 UI를 구현하는 데에 사용할 함수들
#include <Windows.h> //윈도우 콘솔 명령어 cls, pause 사용
#include <iostream>

using namespace std;

//================================================================
//클래스를 이용하지 않고 ATM 프로그램을 작성한다.
//main()은 AppATM의 생성자와 멤버 메소드 run()에 해당한다.
//이체, 계좌 삭제 기능 추가
int main()
{
	//한글(유니코드) 입출력을 지원하기 위해, 로케일 설정
	wcout.imbue(locale("kor"));
	wcin.imbue(locale("kor"));

	int bufMenu;
	Record* curUser = nullptr; //현재 로그인한 사용자의 Record를 가리키는 포인터
	DBManager DBM;
	DBManager_init(DBM, L"ATM_Data.txt"); //기존에 존재하는 Database.txt 파일을 읽어서 계좌 리스트 로드

	while (true) //FRONTPAGE 루프
	{
		system("cls");
		wcout << L"<202035156 박정현의 ATM_without OOP>" << endl
			  << L"환영합니다! (종료: 0, 로그인: 1, 계좌 생성: 2): ";
		ATM_getUserInput_Menu(bufMenu);

		switch (bufMenu)
		{
		case 0: //종료
			ATM_frontPage_Exit(DBM);
			break;

		case 2: //계좌 생성
			ATM_frontPage_CreateAccount(DBM);
			continue;

		default: //잘못된 메뉴 선택
			ATM_wrongMenu();
			continue;

		case 1: //로그인
			if (curUser = ATM_frontPage_LogIn(DBM))
			{
				while (true) //SERVICE 루프
				{
					system("cls");
					wcout << L"<202035156 박정현의 ATM_without OOP>" << endl
						  << curUser->m_Name << L"님의 계좌 잔액 : " << curUser->m_Balance << L"원" << endl
						  << L"(로그아웃: 0, 입금: 1, 출금: 2, 이체: 3, 계좌 삭제: -1): ";
					ATM_getUserInput_Menu(bufMenu);

					switch (bufMenu)
					{
					case 0: //로그아웃
						ATM_service_LogOut();
						curUser = nullptr;
						break;

					case 1: //입금
						ATM_service_Deposit(curUser);
						continue;

					case 2: //출금
						ATM_service_withdraw(curUser);
						continue;

					case 3: //이체
						ATM_service_Transfer(curUser, DBM);
						continue;

					case -1: //계좌 삭제
						ATM_service_DeleteAccount(curUser, DBM);
						curUser = nullptr;
						break;

					default: //잘못된 메뉴 선택
						ATM_wrongMenu();
						continue;
					}
					break; //로그아웃, 계좌 삭제; SERVICE 루프 탈출
				}
			}
			continue; //로그아웃, 계좌 삭제; FRONTPAGE의 다음 반복 실행
		}
		break; //종료; FRONTPAGE 루프 탈출
	}

	return 0;
}