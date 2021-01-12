/*================================
작성자: 202035156 박정현
작성일: 2021-01-12
================================*/

#ifndef CDBMANAGER_CPP
#define CDBMANAGER_CPP

#include "CDBManager.h"

template <typename R>
CDBManager<R>::CDBManager(wstring FileName): m_FileName(FileName)
{
	//정수 1000을 1,000으로 파일에 출력하는 것을 방지하기 위해 로케일 범주를 LC_CTYPE으로 제한
	m_fs.imbue(locale("kor", LC_CTYPE));
	m_fs.open(m_FileName, ios::in);

	if (m_fs.is_open())
	{
		while (!m_fs.eof())
		{
			R tmpRecord;
			tmpRecord.ReadFromFile(m_fs);

			if (tmpRecord.GetID() == L"") { break; } //EOF 주변에서 ID가 L""인 레코드를 인식하는 버그 방지
			m_DB.push_back(tmpRecord);
		}
	}
	m_fs.close();
}

template <typename R>
CDBManager<R>::~CDBManager()
{
	m_fs.open(m_FileName, ios::out | ios::trunc);
	if (m_fs.is_open())
	{
		for (size_t i = 0; i < m_DB.size(); i++)
		{
			m_DB[i].WriteToFile(m_fs);
		}
	}
	m_fs.close();
}

template <typename R>
int CDBManager<R>::QueryRecord(wstring ID) //Query a record with id; Success: non-negative index, Fail: -1
{
	for (size_t i = 0; i < m_DB.size(); i++)
	{
		if (m_DB[i].GetID() == ID) { return i; }
	}
	return -1;
}

template <typename R>
R& CDBManager<R>::GetRecord(size_t index) //Get a record (ref.) from DB
{
	return m_DB[index];
}

template <typename R>
void CDBManager<R>::AddRecord(R record) //Add a record to DB
{
	m_DB.push_back(record);
}

template <typename R>
void CDBManager<R>::DeleteRecord(size_t index) //Delete a record from DB
{
	m_DB.erase(m_DB.begin() + index);
}

#endif