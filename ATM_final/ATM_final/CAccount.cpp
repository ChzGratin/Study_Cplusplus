/*================================
작성자: 202035156 박정현
작성일: 2021-01-12
================================*/

#include "CAccount.h"

CAccount::CAccount()
{
	m_ID = L"";
	m_PW = L"";
	m_Name = L"";
	m_balance = 0;
	m_Log = L"|[계좌 생성]|";
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
	wstring buf; //문자열을 정수로 변환하는 _wtoi()를 이용하여 파일을 읽어야 정상적으로 레코드를 읽어낼 수 있음

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
		if (*iter == CAccount::DELIMITER) { wcout << endl; continue; } //구분자 L'|'가 나오면 줄바꿈
		wcout << *iter;
	}
}

//wstring& CAccount::GetID() { return m_ID; }
wstring& CAccount::GetPW() { return m_PW; }
wstring& CAccount::GetName() { return m_Name; }
ULL& CAccount::GetBalance() { return m_balance; }
wstring& CAccount::GetLog() { return m_Log; }