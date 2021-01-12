/*================================
작성자: 202035156 박정현
작성일: 2021-01-12
================================*/

#ifndef CAPP_H
#define CAPP_H

#include "CRecord.h"
#include "CDBManager.h"

#include <string>
#include <map>
using namespace std;

//CRecord에서 파생된 클래스 R의 필수 메소드:
//R의 각 멤버에 대한 참조를 반환하는 메소드
//ex) GetID(), GetPW(), GetName(), etc.

//CDBManager<R>를 사용하는 응용 프로그램 클래스
template <typename R>
class CApp
{
protected:
	CDBManager<R> m_DBM; //DBManager 클래스
	R* m_curRecord; //현재 CDBApp 클래스가 처리하고 있는 레코드; 포인터

public:
	CApp(wstring FileName);
	virtual int Run() = 0; //응용 프로그램 실행; 순수 가상함수; (선택사항) main()의 리턴값을 리턴
};

#endif