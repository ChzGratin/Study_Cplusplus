/*================================
작성자: 202035156 박정현
작성일: 2021-01-12
================================*/

#ifndef CRECORD_H
#define CRECORD_H

#include <string>
#include <fstream>
using namespace std;

//CRecord의 멤버 메소드(중요):
//파일 입출력(wfstream과의 <<, >> 연산) 역할을 하는 가상함수 ReadFromFile(), WriteToFile()
//R의 각 멤버에 대한 참조를 반환하는 메소드
//ex) GetID(), GetPW(), GetName(), etc.

//파일 입력 규칙:
// i) 한 행은 하나의 멤버에 대응된다.
//ii) 두 레코드는 '\n'으로 구분된다.

//파일 출력 규칙:
// i) 한 행에 하나의 멤버를 출력한다.
//ii) 모든 멤버를 출력했다면, 끝에 '\n'을 추가한다.

//레코드 클래스
class CRecord
{
protected:
	wstring m_ID;

public:
	CRecord();
	CRecord(const CRecord&); //복사생성자

	virtual void ReadFromFile(wfstream& fs);
	virtual void WriteToFile(wfstream& fs);
	wstring& GetID();
};

#endif