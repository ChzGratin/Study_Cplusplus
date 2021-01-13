/*================================
�ۼ���: 202035156 ������
�ۼ���: 2021-01-12
================================*/

#include "CAccount.h"

CAccount::CAccount()
{
	m_ID = L"";
	m_PW = L"";
	m_Name = L"";
	m_balance = 0;
	m_Log = L"|[���� ����]|";
}

CAccount::CAccount(const CAccount& acc)
{
	m_ID = acc.m_ID;
	m_PW = acc.m_PW;
	m_Name = acc.m_Name;
	m_balance = acc.m_balance;
	m_Log = acc.m_Log;
}

void CAccount::ReadFromFile(wfstream& fs)
{
	wstring buf; //���ڿ��� ������ ��ȯ�ϴ� _wtoi()�� �̿��Ͽ� ������ �о�� ���������� ���ڵ带 �о �� ����

	getline(fs, m_ID);
	getline(fs, m_PW);
	getline(fs, m_Name);
	getline(fs, buf); m_balance = _wtoi(buf.c_str());
	getline(fs, m_Log);
}

void CAccount::WriteToFile(wfstream& fs)
{
	fs << m_ID << endl
	   << m_PW << endl
	   << m_Name << endl
	   << m_balance << endl
	   << m_Log << endl;
}

void CAccount::PrintLog()
{
	wstring::iterator iter;
	for (iter = m_Log.begin(); iter != m_Log.end(); iter++)
	{
		if (iter == m_Log.begin()) { continue; }
		if (*iter == CAccount::DELIMITER) { wcout << endl; continue; } //������ L'|'�� ������ �ٹٲ�
		wcout << *iter;
	}
}

//wstring& CAccount::GetID() { return m_ID; }
wstring& CAccount::GetPW() { return m_PW; }
wstring& CAccount::GetName() { return m_Name; }
ULL& CAccount::GetBalance() { return m_balance; }
wstring& CAccount::GetLog() { return m_Log; }