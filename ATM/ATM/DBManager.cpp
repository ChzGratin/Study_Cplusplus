/*================================
작성자: 202035156 박정현
작성일: 2021-01-06
================================*/

#include "DBManager.h"

DBManager::DBManager(wstring fN)
{
	m_fs.imbue(locale("kor"));

	m_FileName = fN;
	m_fs.open(m_FileName, ios::in);
	if (m_fs.is_open())
	{
		while(!m_fs.eof())
		{
			Record bufRec;
			m_fs >> bufRec;

			if (bufRec.GetID() == L"") { break; }

			m_DB.push_back(bufRec);
		}
	}
	m_fs.close();
}

DBManager::~DBManager()
{
	m_fs.open(m_FileName, ios::out | ios::trunc);
	if (m_fs.is_open())
	{
		for (size_t i = 0; i < m_DB.size(); i++) { m_fs << m_DB[i]; }
	}
}

//Query a record with id; Success: non-negative index, Fail: -1
int DBManager::QueryRecord(wstring id)
{
	for (size_t i=0; i<m_DB.size(); i++)
	{
		if (m_DB[i].GetID() == id) { return i; }
	}
	return -1;
}

Record& DBManager::GetRecord(size_t index)
{
	return m_DB[index];
}

void DBManager::AddRecord(Record rec)
{
	m_DB.push_back(rec);
}

void DBManager::DeleteRecord(size_t index)
{
	m_DB.erase(m_DB.begin() + index);
}