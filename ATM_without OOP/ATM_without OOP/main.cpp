#include "Record.h"
#include "DBManager.h"
#include "ATM_UI.h" //ATM�� ��ɰ� UI�� �����ϴ� ���� ����� �Լ���
#include <Windows.h> //������ �ܼ� ��ɾ� cls, pause ���
#include <iostream>

using namespace std;

//================================================================
//Ŭ������ �̿����� �ʰ� ATM ���α׷��� �ۼ��Ѵ�.
//main()�� AppATM�� �����ڿ� ��� �޼ҵ� run()�� �ش��Ѵ�.
//��ü, ���� ���� ��� �߰�
int main()
{
	//�ѱ�(�����ڵ�) ������� �����ϱ� ����, ������ ����
	wcout.imbue(locale("kor"));
	wcin.imbue(locale("kor"));

	int bufMenu;
	Record* curUser = nullptr; //���� �α����� ������� Record�� ����Ű�� ������
	DBManager DBM;
	DBManager_init(DBM, L"ATM_Data.txt"); //������ �����ϴ� Database.txt ������ �о ���� ����Ʈ �ε�

	while (true) //FRONTPAGE ����
	{
		system("cls");
		wcout << L"<202035156 �������� ATM_without OOP>" << endl
			  << L"ȯ���մϴ�! (����: 0, �α���: 1, ���� ����: 2): ";
		ATM_getUserInput_Menu(bufMenu);

		switch (bufMenu)
		{
		case 0: //����
			ATM_frontPage_Exit(DBM);
			break;

		case 2: //���� ����
			ATM_frontPage_CreateAccount(DBM);
			continue;

		default: //�߸��� �޴� ����
			ATM_wrongMenu();
			continue;

		case 1: //�α���
			if (curUser = ATM_frontPage_LogIn(DBM))
			{
				while (true) //SERVICE ����
				{
					system("cls");
					wcout << L"<202035156 �������� ATM_without OOP>" << endl
						  << curUser->m_Name << L"���� ���� �ܾ� : " << curUser->m_Balance << L"��" << endl
						  << L"(�α׾ƿ�: 0, �Ա�: 1, ���: 2, ��ü: 3, ���� ����: -1): ";
					ATM_getUserInput_Menu(bufMenu);

					switch (bufMenu)
					{
					case 0: //�α׾ƿ�
						ATM_service_LogOut();
						curUser = nullptr;
						break;

					case 1: //�Ա�
						ATM_service_Deposit(curUser);
						continue;

					case 2: //���
						ATM_service_withdraw(curUser);
						continue;

					case 3: //��ü
						ATM_service_Transfer(curUser, DBM);
						continue;

					case -1: //���� ����
						ATM_service_DeleteAccount(curUser, DBM);
						curUser = nullptr;
						break;

					default: //�߸��� �޴� ����
						ATM_wrongMenu();
						continue;
					}
					break; //�α׾ƿ�, ���� ����; SERVICE ���� Ż��
				}
			}
			continue; //�α׾ƿ�, ���� ����; FRONTPAGE�� ���� �ݺ� ����
		}
		break; //����; FRONTPAGE ���� Ż��
	}

	return 0;
}