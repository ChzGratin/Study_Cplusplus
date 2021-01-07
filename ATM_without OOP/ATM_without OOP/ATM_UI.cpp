#include "ATM_UI.h"

//================================================================
//�Լ� ��ü ����

//USER INPUT
void ATM_getUserInput_Menu(int& buf) { wcin >> buf; }
void ATM_wrongMenu() { wcout << L"�߸��� �Է��Դϴ�." << endl; system("pause"); }

//FRONTPAGE-------------------------------------------------------
void ATM_frontPage_Exit(DBManager& refDBM) //����
{
	wcout << L"<����>" << endl;
	wcout << L"ATM�� �����մϴ�." << endl;
	system("pause");
	DBManager_kill(refDBM);
}

Record* ATM_frontPage_LogIn(DBManager& refDBM) //�α���
{
	//�α��� �õ�
	wstring bufID, bufPW;
	int bufIndex;

	wcout << L"<�α���>" << endl;
	wcout << L"ID: ";
	wcin >> bufID;
	wcout << L"PW: ";
	wcin >> bufPW;

	bufIndex = DBManager_QueryRecord(refDBM, bufID);
	if (bufIndex >= 0)
	{
		if (refDBM.m_DB[bufIndex].m_PW != bufPW)
		{
			wcout << L"�߸��� ��й�ȣ�Դϴ�." << endl;
			system("pause");
			return nullptr;
		}
	}
	else
	{
		wcout << L"�������� �ʴ� ���� ID�Դϴ�." << endl;
		system("pause");
		return nullptr;
	}

	//�α��� ����
	wcout << refDBM.m_DB[bufIndex].m_Name << L" ����," << endl
		  << L"���� ������ ��ſ� �Ϸ�" << endl
		  << L"�����ñ� �ٶ��ϴ�." << endl;
	system("pause");
	return &(refDBM.m_DB[bufIndex]);
}

void ATM_frontPage_CreateAccount(DBManager& refDBM) //���� ����
{
	wstring bufID, bufPW, bufName;

	wcout << L"<���� ����>" << endl;

	wcout << L"ID: ";
	wcin >> bufID;

	if (DBManager_QueryRecord(refDBM, bufID) >= 0)
	{
		wcout << L"�̹� ��ϵ� ���� ID�Դϴ�." << endl;
		system("pause");
		return;
	}

	wcout << L"PW: ";
	wcin >> bufPW;
	wcout << L"�̸�: ";
	wcin >> bufName;

	Record tmpRec = { bufID, bufPW, bufName, 0 };
	DBManager_AddRecord(refDBM, tmpRec);

	wcout << bufName << L"���� ���°� �����Ǿ����ϴ�." << endl;
	system("pause");
	return;
}

//SERVICE---------------------------------------------------------
void ATM_service_LogOut() //�α׾ƿ�
{
	wcout << L"<�α׾ƿ�>" << endl;
	wcout << L"���������� �α׾ƿ� �Ǿ����ϴ�." << endl;
	system("pause");
	return;
}

void ATM_service_Deposit(Record* pRec) //�Ա�
{
	ULL bufCash;

	wcout << L"<�Ա�>" << endl;
	wcout << L"�Աݾ�: ";
	wcin >> bufCash;

	if (pRec->m_Balance + bufCash <= MAX_BALANCE)
	{
		pRec->m_Balance += bufCash;

		wcout << bufCash << L"���� �ԱݵǾ����ϴ�." << endl;
		system("pause");
		return;
	}
	else
	{
		wcout << L"������ �ִ� ���ݾ��� �ʰ��Ͽ�," << endl;
		wcout << MAX_BALANCE - pRec->m_Balance << L"���� �ԱݵǾ����ϴ�." << endl;
		system("pause");

		pRec->m_Balance = MAX_BALANCE;
		return;
	}
}

void ATM_service_withdraw(Record* pRec) //���
{
	ULL bufCash;

	wcout << L"<���>" << endl;
	wcout << L"��ݾ�: ";
	wcin >> bufCash;

	if (pRec->m_Balance >= bufCash)
	{
		pRec->m_Balance -= bufCash;

		wcout << bufCash << L"���� ��ݵǾ����ϴ�." << endl;
		system("pause");
		return;
	}
	else
	{
		wcout << L"������ �ܾ��� �����Ͽ�," << endl;
		wcout << pRec->m_Balance << L"���� ��ݵǾ����ϴ�." << endl;
		system("pause");

		pRec->m_Balance = 0;
		return;
	}
}

void ATM_service_Transfer(Record* pRec, DBManager& refDBM) //��ü
{
	ULL bufTransfer;
	wstring bufID;
	int bufIndex;

	wcout << L"<��ü>" << endl;
	wcout << L"����� �ݾ�: ";
	wcin >> bufTransfer;

	if (pRec->m_Balance >= bufTransfer)
	{
		wcout << bufTransfer << L"���� ��ü�մϴ�." << endl;
	}
	else
	{
		wcout << L"������ �ܾ��� �����Ͽ�," << endl;
		wcout << pRec->m_Balance << L"���� ��ü�մϴ�." << endl;
		bufTransfer = pRec->m_Balance;
	}

	wcout << endl;

	wcout << L"�Ա��� ������ ID: ";
	wcin >> bufID;

	bufIndex = DBManager_QueryRecord(refDBM, bufID);
	if (bufIndex < 0)
	{
		wcout << L"�������� �ʴ� ���� ID�Դϴ�." << endl
			  << endl
			  << L"<��ü ����>" << endl;
		system("pause");
		return;
	}
	if (pRec->m_ID == bufID)
	{
		wcout << L"��� ���¿� �Ա� ���´� ���� �� �����ϴ�." << endl
			<< endl
			<< L"<��ü ����>" << endl;
		system("pause");
		return;
	}

	if (refDBM.m_DB[bufIndex].m_Balance + bufTransfer > MAX_BALANCE)
	{
		bufTransfer = refDBM.m_DB[bufIndex].m_Balance + bufTransfer - MAX_BALANCE;
		wcout << L"�Ա� ������ �ܾ��� �ִ� ���ݾ��� �ʰ��Ͽ�," << endl;
		wcout << bufTransfer << L"���� ��ü�մϴ�." << endl;
	}

	//��ü ����
	pRec->m_Balance -= bufTransfer;
	refDBM.m_DB[bufIndex].m_Balance += bufTransfer;

	wcout << L"<��ü ����>" << endl;
	system("pause");
	return;
}

void ATM_service_DeleteAccount(Record* pRec, DBManager& refDBM) //���� ����
{
	int bufIndex;

	wcout << L"<���� ����>" << endl;

	bufIndex = DBManager_QueryRecord(refDBM, pRec->m_ID);
	DBManager_DeleteRecord(refDBM, bufIndex);
	pRec = nullptr;

	wcout << L"���°� �����Ǿ����ϴ�." << endl;
	system("pause");
	return;
}