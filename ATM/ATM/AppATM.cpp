/*================================
�ۼ���: 202035156 ������
�ۼ���: 2021-01-06
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
		wcout << L"<202035156 �������� ATM>" << endl;
		wcout << L"ȯ���մϴ�! (0: ����, 1: �α���, 2: ���� ����): ";
		wcin >> menu;

		switch (menu)
		{
		case 0: //����
			Exit();
			return 0;

		case 1: //�α���
			if (!LogIn()) { break; };
			Service();
			break;

		case 2: //���� ����
			CreateAccount();
			break;

		default:
			wcout << L"�߸��� �Է��Դϴ�." << endl;
			system("pause");
			break;
		}
	}
	

	return 0;
}

void AppATM::Exit() //����
{
	wcout << L"<����>" << endl;
	wcout << L"ATM�� �����մϴ�." << endl;
	system("pause");
}

int AppATM::LogIn() //�α���; Success: 1, Fail: 0
{
	//�α��� �õ�
	wstring bufID, bufPW;
	int bufIndex;

	wcout << L"<�α���>" << endl;
	wcout << L"ID: ";
	wcin >> bufID;
	wcout << L"PW: ";
	wcin >> bufPW;

	bufIndex = QueryRecord(bufID);
	if (bufIndex >= 0)
	{
		if (m_DB[bufIndex].GetPW() != bufPW)
		{
			wcout << L"�߸��� ��й�ȣ�Դϴ�." << endl;
			system("pause");
			return 0;
		}
	}
	else
	{
		wcout << L"�������� �ʴ� ���� ID�Դϴ�." << endl;
		system("pause");
		return 0;
	}
	
	//�α��� ����
	m_curUser = &m_DB[bufIndex];
	return 1;
}

void AppATM::CreateAccount() //���� ����
{
	wstring bufID, bufPW, bufName;

	wcout << L"<���� ����>" << endl;

	wcout << L"ID: ";
	wcin >> bufID;

	if (QueryRecord(bufID) >= 0)
	{
		wcout << L"�̹� ��ϵ� ���� ID�Դϴ�." << endl;
		system("pause");
		return;
	}

	wcout << L"PW: ";
	wcin >> bufPW;
	wcout << L"�̸�: ";
	wcin >> bufName;

	Record tmpRec(bufID, bufPW, bufName, 0);
	AddRecord(tmpRec);

	wcout << bufName << L"���� ���°� �����Ǿ����ϴ�." << endl;
	system("pause");
	return;
}

void AppATM::Service() //ATM ����
{
	int menu;
	ULL bufCash;

	while (true)
	{
		system("cls");
		wcout << L"<202035156 �������� ATM>" << endl;
		wcout << m_curUser->GetName() << L"���� ���� �ܾ�: " << m_curUser->GetBalance() << L"��" << endl;
		wcout << L"(0: �α׾ƿ�, 1: �Ա�, 2: ���): ";
		wcin >> menu;

		switch (menu)
		{
		case 0: //�α׾ƿ�
			wcout << L"<�α׾ƿ�>" << endl;
			wcout << L"���������� �α׾ƿ� �Ǿ����ϴ�." << endl;
			system("pause");

			m_curUser = nullptr;
			return;

		case 1: //�Ա�
			wcout << L"<�Ա�>" << endl;
			wcout << L"�Աݾ�: ";
			wcin >> bufCash;

			if (m_curUser->GetBalance() + bufCash <= MAX_BALANCE)
			{
				wcout << bufCash << L"���� �ԱݵǾ����ϴ�." << endl;
				system("pause");

				m_curUser->GetBalance() += bufCash;
				break;
			}
			else
			{
				wcout << L"������ �ִ� ���ݾ��� �ʰ��Ͽ�," << endl;
				wcout << MAX_BALANCE - m_curUser->GetBalance() << L"���� �ԱݵǾ����ϴ�." << endl;
				system("pause");

				m_curUser->GetBalance() = MAX_BALANCE;
				break;
			}

		case 2: //���
			wcout << L"<���>" << endl;
			wcout << L"��ݾ�: ";
			wcin >> bufCash;

			if (m_curUser->GetBalance() >= bufCash)
			{
				wcout << bufCash << L"���� ��ݵǾ����ϴ�." << endl;
				system("pause");

				m_curUser->GetBalance() -= bufCash;
				break;
			}
			else
			{
				wcout << L"������ �ܾ��� �����Ͽ�," << endl;
				wcout << m_curUser->GetBalance() << L"���� ��ݵǾ����ϴ�." << endl;
				system("pause");

				m_curUser->GetBalance() = 0;
				break;
			}

		default:
			wcout << L"�߸��� �Է��Դϴ�." << endl;
			system("pause");
			break;
		}
	}
}