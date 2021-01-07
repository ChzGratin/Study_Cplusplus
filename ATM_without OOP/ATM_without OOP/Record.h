#ifndef RECORD_H
#define RECORD_H

#include <iostream>
#include <fstream>
#include <string> //wchar_t 타입의 C 스타일 스트링은 사용하기 불편

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
	ULL m_Balance = 0; //초기화되지 않은 필드로 인해 발생하는 C26495 경고를 피하기 위해 m_Balance에 초기값 0 지정
};

//함수가 처리하는 구조체의 타입을 함수명에 명시

void Record_WriteToFile(wfstream& fs, Record& rec); //Write to File
void Record_ReadFromFile(wfstream& fs, Record& rec); //Read from File

#endif