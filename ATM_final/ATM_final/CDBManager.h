/*================================
작성자: 202035156 박정현
작성일: 2021-01-12
================================*/

#ifndef CDBMANAGER_H
#define CDBMANAGER_H

#include <vector>
#include <string>
#include <fstream>
using namespace std;

//CRecord에서 파생된 클래스 R의 필수 메소드:
//파일 입출력(wfstream과의 <<, >> 연산) 역할을 하는 가상함수 ReadFromFile(), WriteToFile()
//R.m_ID에 대한 참조를 반환하는 GetID()

//DB 클래스 (.txt 관리 클래스)
template <typename R>
class CDBManager
{
private:
	wstring m_FileName;
	wfstream m_fs;

protected:
	vector<R> m_DB;

public:
	CDBManager(wstring FileName); //Open or create fileName.txt
	~CDBManager(); //Update and close fileName.txt

	int QueryRecord(wstring ID); //Query a record with id; Success: non-negative index, Fail: -1

	R& GetRecord(size_t index); //Get a record (ref.) from DB
	void AddRecord(R record); //Add a record to DB
	void DeleteRecord(size_t index); //Delete a record from DB
};

#endif