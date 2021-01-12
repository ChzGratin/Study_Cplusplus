/*================================
�ۼ���: 202035156 ������
�ۼ���: 2021-01-12
================================*/

#include "CAccount.h"

CAccount::CAccount()
{
	m_ID_Bank = IDB_NULL;
	m_ID = L"";
	m_PW = L"";
	m_Name = L"";
	m_balance = 0;
}

CAccount::CAccount(const CAccount& acc)
{
	m_ID_Bank = acc.m_ID_Bank;
	m_ID = acc.m_ID;
	m_PW = acc.m_PW;
	m_Name = acc.m_Name;
	m_balance = acc.m_balance;
}

void CAccount::ReadFromFile(wfstream& fs)
{
	wstring buf; //���ڿ��� ������ ��ȯ�ϴ� _wtoi()�� �̿��Ͽ� ������ �о�� ���������� ���ڵ带 �о �� ����

	getline(fs, buf); m_ID_Bank = _wtoi(buf.c_str());
	getline(fs, m_ID);
	getline(fs, m_PW);
	getline(fs, m_Name);
	getline(fs, buf); m_balance = _wtoi(buf.c_str());
}

void CAccount::WriteToFile(wfstream& fs)
{
	fs << m_ID_Bank << endl
	   << m_ID << endl
	   << m_PW << endl
	   << m_Name << endl
	   << m_balance << endl;
}

int& CAccount::GetID_Bank() { return m_ID_Bank; }
//wstring& CAccount::GetID() { return m_ID; }
wstring& CAccount::GetPW() { return m_PW; }
wstring& CAccount::GetName() { return m_Name; }
ULL& CAccount::GetBalance() { return m_balance; }