/*================================
작성자: 202035156 박정현
작성일: 2021-01-12
================================*/

#include "CAppATM.h"
#include "CAdmin.h"
#include <string> //문자열 비교 함수 strcmp()

//템플릿 클래스의 정의 포함 (템플릿 클래스의 헤더와 소스를 분리했기 때문)
#include "CApp.cpp"
#include "CDBManager.cpp"

const wchar_t* const WSTR_FILENAME = L"ATM_final.txt";
const char* const STR_ADMIN = "admin";

int main(int argc, char* argv[])
{
	//명령행 인자가 ATM_final.exe admin 이면 관리자 프로그램 실행
	if (argc >= 2)
	{
		if (strcmp(argv[1], STR_ADMIN) == 0)
		{
			CAdmin myAdmin(WSTR_FILENAME);
			return myAdmin.Run();
		}
	}
	CAppATM myATM(WSTR_FILENAME);
	return myATM.Run();
}