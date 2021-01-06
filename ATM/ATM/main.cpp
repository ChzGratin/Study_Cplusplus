/*================================
작성자: 202035156 박정현
작성일: 2021-01-06
================================*/

#include "AppATM.h"

int main()
{
	AppATM myATM(L"ATM_DataBase.txt");
	return myATM.Run();
}