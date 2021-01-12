/*================================
�ۼ���: 202035156 ������
�ۼ���: 2021-01-12
================================*/

#ifndef CDBMANAGER_H
#define CDBMANAGER_H

#include <vector>
#include <string>
#include <fstream>
using namespace std;

//CRecord���� �Ļ��� Ŭ���� R�� �ʼ� �޼ҵ�:
//���� �����(wfstream���� <<, >> ����) ������ �ϴ� �����Լ� ReadFromFile(), WriteToFile()
//R.m_ID�� ���� ������ ��ȯ�ϴ� GetID()

//DB Ŭ���� (.txt ���� Ŭ����)
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