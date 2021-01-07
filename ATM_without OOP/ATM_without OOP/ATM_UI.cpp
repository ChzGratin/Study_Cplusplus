#include "ATM_UI.h"

//================================================================
//함수 몸체 정의

//USER INPUT
void ATM_getUserInput_Menu(int& buf) { wcin >> buf; }
void ATM_wrongMenu() { wcout << L"잘못된 입력입니다." << endl; system("pause"); }

//FRONTPAGE-------------------------------------------------------
void ATM_frontPage_Exit(DBManager& refDBM) //종료
{
	wcout << L"<종료>" << endl;
	wcout << L"ATM을 종료합니다." << endl;
	system("pause");
	DBManager_kill(refDBM);
}

Record* ATM_frontPage_LogIn(DBManager& refDBM) //로그인
{
	//로그인 시도
	wstring bufID, bufPW;
	int bufIndex;

	wcout << L"<로그인>" << endl;
	wcout << L"ID: ";
	wcin >> bufID;
	wcout << L"PW: ";
	wcin >> bufPW;

	bufIndex = DBManager_QueryRecord(refDBM, bufID);
	if (bufIndex >= 0)
	{
		if (refDBM.m_DB[bufIndex].m_PW != bufPW)
		{
			wcout << L"잘못된 비밀번호입니다." << endl;
			system("pause");
			return nullptr;
		}
	}
	else
	{
		wcout << L"존재하지 않는 계좌 ID입니다." << endl;
		system("pause");
		return nullptr;
	}

	//로그인 성공
	wcout << refDBM.m_DB[bufIndex].m_Name << L" 고객님," << endl
		  << L"웃음 가득한 즐거운 하루" << endl
		  << L"보내시기 바랍니다." << endl;
	system("pause");
	return &(refDBM.m_DB[bufIndex]);
}

void ATM_frontPage_CreateAccount(DBManager& refDBM) //계좌 생성
{
	wstring bufID, bufPW, bufName;

	wcout << L"<계좌 생성>" << endl;

	wcout << L"ID: ";
	wcin >> bufID;

	if (DBManager_QueryRecord(refDBM, bufID) >= 0)
	{
		wcout << L"이미 등록된 계좌 ID입니다." << endl;
		system("pause");
		return;
	}

	wcout << L"PW: ";
	wcin >> bufPW;
	wcout << L"이름: ";
	wcin >> bufName;

	Record tmpRec = { bufID, bufPW, bufName, 0 };
	DBManager_AddRecord(refDBM, tmpRec);

	wcout << bufName << L"님의 계좌가 생성되었습니다." << endl;
	system("pause");
	return;
}

//SERVICE---------------------------------------------------------
void ATM_service_LogOut() //로그아웃
{
	wcout << L"<로그아웃>" << endl;
	wcout << L"정상적으로 로그아웃 되었습니다." << endl;
	system("pause");
	return;
}

void ATM_service_Deposit(Record* pRec) //입금
{
	ULL bufCash;

	wcout << L"<입금>" << endl;
	wcout << L"입금액: ";
	wcin >> bufCash;

	if (pRec->m_Balance + bufCash <= MAX_BALANCE)
	{
		pRec->m_Balance += bufCash;

		wcout << bufCash << L"원이 입금되었습니다." << endl;
		system("pause");
		return;
	}
	else
	{
		wcout << L"계좌의 최대 예금액을 초과하여," << endl;
		wcout << MAX_BALANCE - pRec->m_Balance << L"원이 입금되었습니다." << endl;
		system("pause");

		pRec->m_Balance = MAX_BALANCE;
		return;
	}
}

void ATM_service_withdraw(Record* pRec) //출금
{
	ULL bufCash;

	wcout << L"<출금>" << endl;
	wcout << L"출금액: ";
	wcin >> bufCash;

	if (pRec->m_Balance >= bufCash)
	{
		pRec->m_Balance -= bufCash;

		wcout << bufCash << L"원이 출금되었습니다." << endl;
		system("pause");
		return;
	}
	else
	{
		wcout << L"계좌의 잔액이 부족하여," << endl;
		wcout << pRec->m_Balance << L"원이 출금되었습니다." << endl;
		system("pause");

		pRec->m_Balance = 0;
		return;
	}
}

void ATM_service_Transfer(Record* pRec, DBManager& refDBM) //이체
{
	ULL bufTransfer;
	wstring bufID;
	int bufIndex;

	wcout << L"<이체>" << endl;
	wcout << L"출금할 금액: ";
	wcin >> bufTransfer;

	if (pRec->m_Balance >= bufTransfer)
	{
		wcout << bufTransfer << L"원을 이체합니다." << endl;
	}
	else
	{
		wcout << L"계좌의 잔액이 부족하여," << endl;
		wcout << pRec->m_Balance << L"원을 이체합니다." << endl;
		bufTransfer = pRec->m_Balance;
	}

	wcout << endl;

	wcout << L"입금할 계좌의 ID: ";
	wcin >> bufID;

	bufIndex = DBManager_QueryRecord(refDBM, bufID);
	if (bufIndex < 0)
	{
		wcout << L"존재하지 않는 계좌 ID입니다." << endl
			  << endl
			  << L"<이체 실패>" << endl;
		system("pause");
		return;
	}
	if (pRec->m_ID == bufID)
	{
		wcout << L"출금 계좌와 입금 계좌는 같을 수 없습니다." << endl
			<< endl
			<< L"<이체 실패>" << endl;
		system("pause");
		return;
	}

	if (refDBM.m_DB[bufIndex].m_Balance + bufTransfer > MAX_BALANCE)
	{
		bufTransfer = refDBM.m_DB[bufIndex].m_Balance + bufTransfer - MAX_BALANCE;
		wcout << L"입금 계좌의 잔액이 최대 예금액을 초과하여," << endl;
		wcout << bufTransfer << L"원을 이체합니다." << endl;
	}

	//이체 수행
	pRec->m_Balance -= bufTransfer;
	refDBM.m_DB[bufIndex].m_Balance += bufTransfer;

	wcout << L"<이체 성공>" << endl;
	system("pause");
	return;
}

void ATM_service_DeleteAccount(Record* pRec, DBManager& refDBM) //계좌 삭제
{
	int bufIndex;

	wcout << L"<계좌 삭제>" << endl;

	bufIndex = DBManager_QueryRecord(refDBM, pRec->m_ID);
	DBManager_DeleteRecord(refDBM, bufIndex);
	pRec = nullptr;

	wcout << L"계좌가 삭제되었습니다." << endl;
	system("pause");
	return;
}