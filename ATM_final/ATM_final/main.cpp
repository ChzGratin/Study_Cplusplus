/*================================
작성자: 202035156 박정현
작성일: 2021-01-12
================================*/

#include "CAppATM.h"
#include "CAppAdmin.h"
#include <string> //문자열 비교 함수 strcmp()

//템플릿 클래스의 정의 포함 (템플릿 클래스의 헤더와 소스를 분리했기 때문)
#include "CApp.cpp"
#include "CDBManager.cpp"

const wchar_t* const WSTR_EXENAME = L"ATM_final.exe";
const wchar_t* const WSTR_FILENAME = L"ATM_final.txt";
const wchar_t* const STR_ADMIN = L"admin";

int wmain(int argc, wchar_t* argv[]) //유니코드를 지원하는 main()
{
	wstring argv_0(argv[0]); //L"파일 경로+ATM_final.exe"와 L"ATM_final.exe"를 구분하기 위함; ATM_final.exe가 있는 곳에 ATM_final.txt가 생성되아야 함
	wstring FileLoc; //파일 위치

	if (argv_0 == WSTR_EXENAME) { FileLoc = WSTR_FILENAME; } //L"ATM_final.exe"인 경우
	else //L"파일 경로+ATM_final.exe"인 경우, ATM_final.exe 부분을 지우고 ATM_final.txt를 덧붙여야 함
	{
		size_t index_exeName = argv_0.rfind(WSTR_EXENAME); //파일 경로에 L"ATM_final.exe"가 있을 때를 대비하여 rfind 사용
		FileLoc = argv_0.erase(index_exeName) + WSTR_FILENAME; //L"파일 경로" + L"ATM_final.txt"
	}

	//명령행 인자가 ATM_final.exe admin 이면 관리자 프로그램 실행
	if (argc >= 2 && wcscmp(argv[1], STR_ADMIN) == 0)
	{
		CAppAdmin myAdmin(FileLoc);
		return myAdmin.Run();
	}
	else
	{
		CAppATM myATM(FileLoc);
		return myATM.Run();
	}
}