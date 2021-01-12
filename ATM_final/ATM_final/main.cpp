/*================================
�ۼ���: 202035156 ������
�ۼ���: 2021-01-12
================================*/

#include "CAppATM.h"
#include "CAdmin.h"
#include <string> //���ڿ� �� �Լ� strcmp()

//���ø� Ŭ������ ���� ���� (���ø� Ŭ������ ����� �ҽ��� �и��߱� ����)
#include "CApp.cpp"
#include "CDBManager.cpp"

const wchar_t* const WSTR_FILENAME = L"ATM_final.txt";
const char* const STR_ADMIN = "admin";

int main(int argc, char* argv[])
{
	//����� ���ڰ� ATM_final.exe admin �̸� ������ ���α׷� ����
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