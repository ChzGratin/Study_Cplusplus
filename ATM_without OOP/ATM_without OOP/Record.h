#ifndef RECORD_H
#define RECORD_H

#include <iostream>
#include <fstream>
#include <string> //wchar_t Ÿ���� C ��Ÿ�� ��Ʈ���� ����ϱ� ����

using namespace std;

//const size_t SIZE_STR = 20;
//enum BANK_ID {KB, SHINHAN, HANA};

typedef unsigned long long ULL;
const ULL MAX_BALANCE = 100000000;
struct Record
{
	wstring m_ID;
	wstring m_PW;
	wstring m_Name;
	ULL m_Balance = 0; //�ʱ�ȭ���� ���� �ʵ�� ���� �߻��ϴ� C26495 ��� ���ϱ� ���� m_Balance�� �ʱⰪ 0 ����
};

//�Լ��� ó���ϴ� ����ü�� Ÿ���� �Լ��� ���

void Record_WriteToFile(wfstream& fs, Record& rec); //Write to File
void Record_ReadFromFile(wfstream& fs, Record& rec); //Read from File

#endif