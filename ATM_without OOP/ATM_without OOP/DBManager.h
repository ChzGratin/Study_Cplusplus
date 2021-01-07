#ifndef DBMANAGER_H
#define DBMANAGER_H

#include "Record.h"
#include <fstream>
#include <string>
#include <vector> //�����Ҵ����� m_DB�� ������ �� ������ �ð����� ������ vector.h ���

using namespace std;

struct DBManager
{
	wfstream m_fs;
	wstring m_fileName;
	vector<Record> m_DB;
};

//��� �޼ҵ��� ������ ����� �� �����Ƿ�,
//i)  �Լ��� ó���ϴ� ����ü�� �̸��� �Լ��� �տ� ���
//ii) ��� �޼ҵ��� ȣ���� ���۷����� ����

void DBManager_init(DBManager& DBM, wstring fileName); //������ �����ϴ� Database.txt ������ �о ���� ����Ʈ �ε�
void DBManager_kill(DBManager& DBM); //������ ���� ����Ʈ�� Database.txt�� �����

int DBManager_QueryRecord(DBManager& DBM, wstring id); //Query a record with id; Success: non-negative index, Fail: -1

Record& DBManager_GetRecord(DBManager& DBM, size_t index); //Get a record (ref) from DB
void DBManager_AddRecord(DBManager& DBM, Record rec); //Add a record to DB
void DBManager_DeleteRecord(DBManager& DBM, size_t id); //Delete a record from DB

#endif