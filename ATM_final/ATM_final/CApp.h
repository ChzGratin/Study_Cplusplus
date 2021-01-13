/*================================
�ۼ���: 202035156 ������
�ۼ���: 2021-01-12
================================*/

#ifndef CAPP_H
#define CAPP_H

#include "CRecord.h"
#include "CDBManager.h"

#include <string>
#include <map>
using namespace std;

//CRecord���� �Ļ��� Ŭ���� R�� �ʼ� �޼ҵ�:
//R�� �� ����� ���� ������ ��ȯ�ϴ� �޼ҵ�
//ex) GetID(), GetPW(), GetName(), etc.

//CDBManager<R>�� ����ϴ� ���� ���α׷� Ŭ����
template <typename R>
class CApp: public CDBManager<R>
{
protected:
	R* m_curRecord; //���� CDBApp Ŭ������ ó���ϰ� �ִ� ���ڵ�; ������

public:
	CApp(wstring FileName);
	virtual int Run() = 0; //���� ���α׷� ����; ���� �����Լ�; (���û���) main()�� ���ϰ��� ����
};

#endif