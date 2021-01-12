/*================================
작성자: 202035156 박정현
작성일: 2021-01-12
================================*/

#include "CRecord.h"

CRecord::CRecord() { m_ID = L""; }
CRecord::CRecord(const CRecord& rec) { m_ID = rec.m_ID; }

void CRecord::ReadFromFile(wfstream& fs) //Read from File
{
	getline(fs, m_ID);
}

void CRecord::WriteToFile(wfstream& fs) //Write to File
{
	fs << m_ID << endl;
}

wstring& CRecord::GetID() { return m_ID; }