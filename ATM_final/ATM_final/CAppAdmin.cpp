/*================================
�ۼ���: 202035156 ������
�ۼ���: 2021-01-12
================================*/

#include "CAppAdmin.h"

//���ø� Ŭ������ ���� ���� (���ø� Ŭ������ ����� �ҽ��� �и��߱� ����)
//CAppATM�� ���ø� Ŭ���� CDBManager�� ������
#include "CDBManager.cpp"

//================================================================

void CAppAdmin::m_PageView() //���¸� 1�������� ACCOUNT_PER_PAGE(=10)���� ��� ���; ������ �ѱ��; ���� ����
{
	wchar_t menu; //����� �Է� (�޴� �ڵ�)

	size_t curPage = 0; //���� ������; 0���������� ����
	size_t curCount; //���� �������� ǥ�õǴ� ���� ��

	while (true)
	{
		size_t size = GetSize(); //��ü ���� ��; ������Ʈ

		system("cls");
		wcout << L"<202035156 �������� ATM_final (������)>" << endl
			<< L"================================" << endl
			<< L"[�ε���]: ���� ID" << endl;

		//���¸� 1�������� ACCOUNT_PER_PAGE(=10)���� ��� ���
		curCount = 0;
		for (size_t i = 0; i < ACCOUNT_PER_PAGE; i++)
		{
			if ((curPage * ACCOUNT_PER_PAGE + i) >= size) { break; }
			wcout << L"[" << i << L"]: ";
			wcout << GetRecord(curPage * ACCOUNT_PER_PAGE + i).GetName() << endl;
			curCount++;
		}
		wcout << L"================================" << endl;

		//�޴� ����
		wcout << L" Q : ����" << endl
			<< L"0~9: ���� ���� (�ε����� �Է�)" << endl
			<< L" Z : ���� ������" << endl
			<< L" X : ���� ������" << endl
			<< L"================================" << endl
			<< L"�޴� ����: ";
		wcin >> menu;

		//����
		if (menu == L'Q' || menu == L'q') { return; }

		//���� ����
		if (L'0' <= menu && menu <= L'9')
		{
			if ((size_t)(menu - L'0') < curCount) //���� ���������� ������ �� �ִ� ���¶��
			{
				m_ManageAccount(curPage * ACCOUNT_PER_PAGE + menu - L'0'); //���� ����
				curPage = 0; //���� ������ ������ ù �������� ����
			}
			continue;
		}

		//���� ������
		if (menu == L'Z' || menu == L'z')
		{
			if (curPage > 0) { curPage--; } //���� �������� ù �������� �ƴ϶��
			continue;
		}

		//���� ������
		if (menu == L'X' || menu == L'x')
		{
			if (curPage * ACCOUNT_PER_PAGE + curCount < size) { curPage++; } //���� �������� ������ �������� �ƴ϶��
			continue;
		}

		//default:
		wcout << L"�߸��� �Է��Դϴ�." << endl;
		system("pause");
		continue;
	}
}

void CAppAdmin::m_ManageAccount(size_t index) //���� ���� ���; ���� ����
{
	int menu; //����� �Է� (�޴� �ڵ�)

	while (true)
	{
		system("cls");
		wcout << L"<202035156 �������� ATM_final (������)>" << endl
			<< L"�̸�: " << GetRecord(index).GetName() << endl
			<< L"ID: " << GetRecord(index).GetID() << endl
			<< L"PW: " << GetRecord(index).GetPW() << endl
			<< L"���� �ܾ�: " << GetRecord(index).GetBalance() << "��" << endl
			<< L"================================" << endl
			<< L" 0: �ڷΰ���" << endl
			<< L"-1: ���� ����" << endl
			<< L"================================" << endl
			<< L"�޴� ����: ";
		wcin >> menu;

		switch (menu)
		{
		case 0: //�ڷΰ���
			return; //PageView()�� ����

		case -1: //���� ����
			wcout << L"<���� ����>" << endl;
			DeleteRecord(index);
			wcout << L"���°� �����Ǿ����ϴ�." << endl;
			system("pause");
			return; //PageView()�� ����

		default:
			wcout << L"�߸��� �Է��Դϴ�." << endl;
			system("pause");
			continue;
		}
	}
}