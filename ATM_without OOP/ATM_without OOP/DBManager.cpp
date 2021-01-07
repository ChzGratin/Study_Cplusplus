#include "DBManager.h"

void DBManager_init(DBManager& DBM, wstring fileName) //기존에 존재하는 Database.txt 파일을 읽어서 계좌 리스트 로드
{
	DBM.m_fs.imbue(locale("kor"));
	DBM.m_fileName = fileName;

	DBM.m_fs.open(DBM.m_fileName, ios::in);
	if (DBM.m_fs.is_open())
	{
		while (!DBM.m_fs.eof())
		{
			Record bufRec;
			bufRec.m_Balance = 0;
			Record_ReadFromFile(DBM.m_fs, bufRec);

			if (bufRec.m_ID == L"") { break; }

			DBM.m_DB.push_back(bufRec);
		}
	}
	DBM.m_fs.close();
}

void DBManager_kill(DBManager& DBM) //수정된 계좌 리스트를 Database.txt에 덮어쓰기
{
	DBM.m_fs.open(DBM.m_fileName, ios::out | ios::trunc);
	if (DBM.m_fs.is_open())
	{
		for (size_t i = 0; i < DBM.m_DB.size(); i++) { Record_WriteToFile(DBM.m_fs, DBM.m_DB[i]); }
	}
	DBM.m_fs.close();
}

int DBManager_QueryRecord(DBManager& DBM, wstring id) //Query a record with id; Success: non-negative index, Fail: -1
{
	for (size_t i = 0; i < DBM.m_DB.size(); i++)
	{
		if (DBM.m_DB[i].m_ID == id) { return i; }
	}
	return -1;
}

Record& DBManager_GetRecord(DBManager& DBM, size_t index) //Get a record (ref) from DB
{
	return DBM.m_DB[index];
}

void DBManager_AddRecord(DBManager& DBM, Record rec) //Add a record to DB
{
	DBM.m_DB.push_back(rec);
}

void DBManager_DeleteRecord(DBManager& DBM, size_t index) //Delete a record from DB
{
	DBM.m_DB.erase(DBM.m_DB.begin() + index);
}