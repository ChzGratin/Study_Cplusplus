/*================================
�ۼ���: 202035156 ������
�ۼ���: 2021-01-12
================================*/

#include "CAppATM.h"
#include "CAppAdmin.h"
#include <string> //���ڿ� �� �Լ� strcmp()

//���ø� Ŭ������ ���� ���� (���ø� Ŭ������ ����� �ҽ��� �и��߱� ����)
#include "CApp.cpp"
#include "CDBManager.cpp"

const wchar_t* const WSTR_EXENAME = L"ATM_final.exe";
const wchar_t* const WSTR_FILENAME = L"ATM_final.txt";
const wchar_t* const STR_ADMIN = L"admin";

int wmain(int argc, wchar_t* argv[]) //�����ڵ带 �����ϴ� main()
{
	wstring argv_0(argv[0]); //L"���� ���+ATM_final.exe"�� L"ATM_final.exe"�� �����ϱ� ����; ATM_final.exe�� �ִ� ���� ATM_final.txt�� �����Ǿƾ� ��
	wstring FileLoc; //���� ��ġ

	if (argv_0 == WSTR_EXENAME) { FileLoc = WSTR_FILENAME; } //L"ATM_final.exe"�� ���
	else //L"���� ���+ATM_final.exe"�� ���, ATM_final.exe �κ��� ����� ATM_final.txt�� ���ٿ��� ��
	{
		size_t index_exeName = argv_0.rfind(WSTR_EXENAME); //���� ��ο� L"ATM_final.exe"�� ���� ���� ����Ͽ� rfind ���
		FileLoc = argv_0.erase(index_exeName) + WSTR_FILENAME; //L"���� ���" + L"ATM_final.txt"
	}

	//����� ���ڰ� ATM_final.exe admin �̸� ������ ���α׷� ����
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