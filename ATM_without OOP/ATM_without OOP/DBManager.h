#ifndef DBMANAGER_H
#define DBMANAGER_H

#include "Record.h"
#include <fstream>
#include <string>
#include <vector> //동적할당으로 m_DB를 구현할 수 있지만 시간상의 이유로 vector.h 사용

using namespace std;

struct DBManager
{
	wfstream m_fs;
	wstring m_fileName;
	vector<Record> m_DB;
};

//멤버 메소드라는 개념을 사용할 수 없으므로,
//i)  함수가 처리하는 구조체의 이름을 함수명 앞에 명시
//ii) 멤버 메소드의 호출을 레퍼런스로 구현

void DBManager_init(DBManager& DBM, wstring fileName); //기존에 존재하는 Database.txt 파일을 읽어서 계좌 리스트 로드
void DBManager_kill(DBManager& DBM); //수정된 계좌 리스트를 Database.txt에 덮어쓰기

int DBManager_QueryRecord(DBManager& DBM, wstring id); //Query a record with id; Success: non-negative index, Fail: -1

Record& DBManager_GetRecord(DBManager& DBM, size_t index); //Get a record (ref) from DB
void DBManager_AddRecord(DBManager& DBM, Record rec); //Add a record to DB
void DBManager_DeleteRecord(DBManager& DBM, size_t id); //Delete a record from DB

#endif