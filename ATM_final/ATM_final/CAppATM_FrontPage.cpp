/*================================
�ۼ���: 202035156 ������
�ۼ���: 2021-01-12
================================*/

#include "CAppATM.h"

//���ø� Ŭ������ ���� ���� (���ø� Ŭ������ ����� �ҽ��� �и��߱� ����)
//CAppATM�� ���ø� Ŭ���� CDBManager�� CApp�� ������
#include "CApp.cpp"
#include "CDBManager.cpp"

//================================================================

void CAppATM::m_FrontPageMenu() //����Ʈ������ �޴�
{
	int menu; //����� �Է� (�޴� �ڵ�)

	while (true)
	{
		system("cls");
		wcout << L"<202035156 �������� ATM_final>" << endl
			<< L"ȯ���մϴ�." << endl
			<< L"================================" << endl
			<< L"0: ����" << endl
			<< L"1: �α���" << endl
			<< L"2: ���� ����" << endl
			<< L"================================" << endl
			<< L"�޴� ����: ";
		wcin >> menu;

		switch (menu)
		{
		case 0: //����
			m_Exit();
			return;
		case 1: //�α���
			m_LogIn();
			continue;
		case 2: //���� ����
			m_CreateAccount();
			continue;
		default:
			wcout << L"�߸��� �Է��Դϴ�." << endl;
			system("pause");
			continue;
		}
	}
}

//----------------------------------------------------------------

void CAppATM::m_Exit()
{
	wcout << L"<����>" << endl
		  << L"ATM�� �����մϴ�." << endl;
	system("pause");
}

void CAppATM::m_LogIn() //�α���; �� �� �����ϰ� ���������� ����
{
	wstring bufID, bufPW; //����� �Է� (ID, PW)

	wcout << L"<�α���>" << endl;
	wcout << L"ID: ";
	wcin >> bufID;
	wcout << L"PW: ";
	wcin >> bufPW;

	int index = m_DBM.QueryRecord(bufID); //����ڰ� �Է��� ID�� �����ϴ� ������ �ε��� ����
	if (index < 0) //�������� �ʴ� ID���
	{
		wcout << L"�������� �ʴ� ���� ID�Դϴ�." << endl;
		system("pause");
		return;
	}
	else //ID�� �����Ѵٸ�
	{
		if (m_DBM.GetRecord(index).GetPW() != bufPW) //�߸��� ��й�ȣ���
		{
			wcout << L"�߸��� ��й�ȣ�Դϴ�." << endl;
			system("pause");
			return;
		}
		else //�ùٸ� ��й�ȣ���; �α��� ����
		{
			m_curRecord = &(m_DBM.GetRecord(index)); //CDBApp Ŭ������ ó���� ���ڵ带 ����

			wcout << m_curRecord->GetName() << L"�� �ȳ��ϼ���." << endl;
			system("pause");

			m_ServiceMenu(); //���� �޴� ����
			return;
		}
	}
}

void CAppATM::m_CreateAccount() //���� ����
{
	wstring bufID, bufPW, bufName; //����� �Է� (ID, PW, �̸�)

	wcout << L"<���� ����>" << endl;
	wcout << L"ID: ";
	wcin >> bufID;

	if (m_DBM.QueryRecord(bufID) >= 0) //�̹� ��ϵ� ���� ID���
	{
		wcout << L"�̹� ��ϵ� ���� ID�Դϴ�." << endl;
		system("pause");
		return;
	}

	wcout << L"PW: ";
	wcin >> bufPW;
	wcout << L"�̸�: ";
	wcin >> bufName;

	CAccount tmpAcc; //������ ������ ������ �ӽ÷� ������ ����
	tmpAcc.GetID() = bufID;
	tmpAcc.GetPW() = bufPW;
	tmpAcc.GetName() = bufName;
	m_DBM.AddRecord(tmpAcc);

	wcout << bufName << L"���� ���°� �����Ǿ����ϴ�." << endl;
	system("pause");
	return;
}