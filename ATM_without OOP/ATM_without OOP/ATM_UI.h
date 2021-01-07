#ifndef ATM_UI_H
#define ATM_UI_H

#include "Record.h"
#include "DBManager.h"
#include <iostream>
#include <string>
#include <Windows.h> //윈도우 콘솔 명령어 cls, pause 사용

using namespace std;

//================================================================
//함수 프로토타입

//USER INPUT
void ATM_getUserInput_Menu(int& buf);
void ATM_wrongMenu();

//FRONTPAGE-------------------------------------------------------
void ATM_frontPage_Exit(DBManager& refDBM); //종료
Record* ATM_frontPage_LogIn(DBManager& refDBM); //로그인; Success: ptr for curUser, Fail: nullptr
void ATM_frontPage_CreateAccount(DBManager& refDBM); //계좌 생성

//SERVICE---------------------------------------------------------
void ATM_service_LogOut();
void ATM_service_Deposit(Record* pRec); //입금
void ATM_service_withdraw(Record* pRec); //출금
void ATM_service_Transfer(Record* pRec, DBManager& refDBM); //이체
void ATM_service_DeleteAccount(Record* pRec, DBManager& refDBM); //계좌 삭제

#endif