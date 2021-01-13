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

void CAppATM::m_ServiceMenu() //���� �޴�
{
	int menu; //����� �Է� (�޴� �ڵ�)

	while (true)
	{
		system("cls");
		wcout << L"<202035156 �������� ATM_final>" << endl
			<< m_curRecord->GetName() << L"���� ���� �ܾ�: " << m_curRecord->GetBalance() << L"��" << endl
			<< L"================================" << endl
			<< L" 0: �α׾ƿ�" << endl
			<< L" 1: �Ա�" << endl
			<< L" 2: ���" << endl
			<< L" 3: ��ü" << endl
			<< L"-1: ���� ����" << endl
			<< L"================================" << endl
			<< L"�޴� ����: ";
		wcin >> menu;

		switch (menu)
		{
		case 0: //�α׾ƿ�
			m_LogOut();
			return; //����Ʈ�������� ����
		case 1: //�Ա�
			m_Deposit();
			continue;
		case 2: //���
			m_Withdraw();
			continue;
		case 3: //��ü
			m_Transfer();
			continue;
		case -1: //���� ����
			m_DeleteAccount();
			return; //����Ʈ�������� ����
		default:
			wcout << L"�߸��� �Է��Դϴ�." << endl;
			system("pause");
			continue;
		}
	}
}

//----------------------------------------------------------------

void CAppATM::m_LogOut() //�α׾ƿ�
{
	m_curRecord = nullptr; //CDBApp Ŭ������ ó���ϵ��� �����ߴ� ���ڵ带 ����

	wcout << L"<�α׾ƿ�>" << endl
		  << L"���������� �α׾ƿ� �Ǿ����ϴ�." << endl;
	system("pause");
	return;
}

void CAppATM::m_Deposit() //�Ա�
{
	ULL bufCash; //����� �Է� (�Աݾ�)

	wcout << L"<�Ա�>" << endl;
	wcout << L"�Աݾ�: ";
	wcin >> bufCash;

	if (m_curRecord->GetBalance() + bufCash <= CAccount::MAX_BALANCE) //�ִ� ���ݾ��� �ʰ����� ���� ��
	{
		m_curRecord->GetBalance() += bufCash;

		wcout << bufCash << L"���� �ԱݵǾ����ϴ�." << endl;
		system("pause");
		return;
	}
	else //�ִ� ���ݾ��� �ʰ��� ��
	{
		wcout << L"������ �ִ� ���ݾ��� �ʰ��Ͽ�," << endl
			  << CAccount::MAX_BALANCE - m_curRecord->GetBalance() << L"���� �ԱݵǾ����ϴ�." << endl;
		system("pause");

		m_curRecord->GetBalance() = CAccount::MAX_BALANCE;
		return;
	}
}

void CAppATM::m_Withdraw() //���
{
	ULL bufCash; //����� �Է� (��ݾ�)

	wcout << L"<���>" << endl;
	wcout << L"��ݾ�: ";
	wcin >> bufCash;

	if (m_curRecord->GetBalance() >= bufCash) //�ܾ��� �������� ���� ��
	{
		m_curRecord->GetBalance() -= bufCash;

		wcout << bufCash << L"���� ��ݵǾ����ϴ�." << endl;
		system("pause");
		return;
	}
	else //�ܾ��� ������ ��
	{
		wcout << L"������ �ܾ��� �����Ͽ�," << endl
			  << m_curRecord->GetBalance() << L"���� ��ݵǾ����ϴ�." << endl;
		system("pause");

		m_curRecord->GetBalance() = 0;
		return;
	}
}


void CAppATM::m_Transfer() //��ü
{
	ULL bufTransfer; //����� �Է� (��ü��)
	wstring bufID_to; //����� �Է� (�Աݰ��� ID); transfer "to"

	wcout << L"<��ü>" << endl;
	wcout << L"��ݾ�: ";
	wcin >> bufTransfer;
	wcout << L"�Աݰ��� ID: ";
	wcin >> bufID_to;

	//�Աݰ��� ���翩�� �� �ܾ� Ȯ��
	int index = QueryRecord(bufID_to); //����ڰ� �Է��� ID�� �����ϴ� ������ �ε��� ����
	if (index < 0) //�������� �ʴ� ���¶��
	{
		wcout << L"[�Աݰ��� �˻� ����] ��ü����" << endl;
		system("pause");
		return;
	}
	else //���°� �����Ѵٸ�
	{
		if (GetRecord(index).GetBalance() + bufTransfer > CAccount::MAX_BALANCE) //�ִ� ���ݾ��� �ʰ��� ��
		{
			bufTransfer = CAccount::MAX_BALANCE - GetRecord(index).GetBalance(); //��ü�� ����

			wcout << L"[�Աݰ��� �ܾ� �ʰ�] "
				  << bufTransfer << L"���� ��ü�մϴ�." << endl;
		}
	}

	//��ݰ��� �ܾ� Ȯ��
	if (m_curRecord->GetBalance() < bufTransfer) //�ܾ��� ������ ��
	{
		bufTransfer = m_curRecord->GetBalance(); //��ü�� ����

		wcout << L"[��ݰ��� �ܾ� ����] "
			  << m_curRecord->GetBalance() << L"���� ��ü�մϴ�." << endl;
	}

	//��ü ����
	m_curRecord->GetBalance() -= bufTransfer; //���
	GetRecord(index).GetBalance() += bufTransfer; //�Ա�
	wcout << L"��ü����" << endl;
	system("pause");
	return;
}

void CAppATM::m_DeleteAccount() //���� ����
{
	wcout << L"<���� ����>" << endl;

	int index = QueryRecord(m_curRecord->GetID()); //���� ������� ���ڵ忡 �����Ǵ� �ε��� ����
	DeleteRecord(index); //���� ������� ���ڵ� ����
	m_curRecord = nullptr; //�޸𸮰� �����Ǿ����Ƿ� nullptr ó��

	wcout << L"���°� �����Ǿ����ϴ�." << endl;
	system("pause");
	return;
}