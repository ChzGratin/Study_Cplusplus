/*================================
�ۼ���: 202035156 ������
�ۼ���: 2021-01-12
================================*/

#ifndef CACCOUNT_H
#define CACCOUNT_H

#include "CRecord.h"

#include <iostream>
using namespace std;

typedef unsigned long long ULL;
enum ID_BANK { IDB_NULL, IDB_KB, IDB_SHINHAN, IDB_WOORI, IDB_HANA, IDB_CITY }; //IDB = ID + Bank

//���� stack�� ����� �ʿ䰡 �ֳ�? Nope!
//wstring m_Log; ��� ��Ģ:
/* ex)
������ ������ L"[�Ա�] +10000��|[���] -5000��|[��ü] -3000�� ->Alice|[��ü] +2000 <-Bob|" �̶��
������� 10000�� �Ա�, 5000�� ���, 3000���� ���� Alice���� ��ü, 2000���� Bob�� ������ ��ü�Ͽ����� �ǹ�
�α״� �ð� ������� ��ϵǸ�, �� �α��� ������ ������ L'|'�� ����
��ϵ� �αװ� ���ٸ�, �α״� L"|[���� ����]|"�� �� (L""�� �ϸ� ���� ������� �� �� ���� �߻�)
*/

//���� ���� Ŭ����
class CAccount : public CRecord
{
private:
	//wstring m_ID;
	wstring m_PW;
	wstring m_Name;
	ULL m_balance;
	wstring m_Log; //�α�; �ŷ�����

public:
	static const ULL MAX_BALANCE = 100000000; //�ִ� ���ݾ�; static�̹Ƿ� CAccount::MAX_BALANCE�� ���·� ���
	static const wchar_t DELIMITER = L'|'; //�α� ������ (delimiter)

public:
	CAccount();
	CAccount(const CAccount&); //���������

	void ReadFromFile(wfstream& fs);
	void WriteToFile(wfstream& fs);
	void PrintLog(); //�α� ���; wcout

	//wstring& GetID();
	wstring& GetPW();
	wstring& GetName();
	ULL& GetBalance();
	wstring& GetLog();
};

#endif