/*================================
작성자: 202035156 박정현
작성일: 2021-01-06
================================*/

#ifndef DBMANAGER_H
#define DBMANAGER_H

#include "Record.h"
#include <fstream>
#include <vector>

using namespace std;

class DBManager
{
protected:
	wstring m_FileName;
	wfstream m_fs;
	vector<Record> m_DB; //wstring: ID of a Record, R: Record

	DBManager(wstring fN); //Open or create fileName.txt; fN = fileName
	~DBManager(); //Update and close fileName.txt

	int QueryRecord(wstring id); //Query a record with id; Success: 1, Fail: 0

	Record& GetRecord(size_t index); //Get a record (ref) from DB
	void AddRecord(Record rec); //Add a record to DB
	void DeleteRecord(size_t index); //Delete a record from DB
};

#endif