#ifndef ATM_UI_H
#define ATM_UI_H

#include "Record.h"
#include "DBManager.h"
#include <iostream>
#include <string>
#include <Windows.h> //������ �ܼ� ��ɾ� cls, pause ���

using namespace std;

//================================================================
//�Լ� ������Ÿ��

//USER INPUT
void ATM_getUserInput_Menu(int& buf);
void ATM_wrongMenu();

//FRONTPAGE-------------------------------------------------------
void ATM_frontPage_Exit(DBManager& refDBM); //����
Record* ATM_frontPage_LogIn(DBManager& refDBM); //�α���; Success: ptr for curUser, Fail: nullptr
void ATM_frontPage_CreateAccount(DBManager& refDBM); //���� ����

//SERVICE---------------------------------------------------------
void ATM_service_LogOut();
void ATM_service_Deposit(Record* pRec); //�Ա�
void ATM_service_withdraw(Record* pRec); //���
void ATM_service_Transfer(Record* pRec, DBManager& refDBM); //��ü
void ATM_service_DeleteAccount(Record* pRec, DBManager& refDBM); //���� ����

#endif