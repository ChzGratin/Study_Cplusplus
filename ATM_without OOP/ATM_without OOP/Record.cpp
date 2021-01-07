#include "Record.h"

void Record_WriteToFile(wfstream& fs, Record& rec) //Write to File
{
	fs << rec.m_ID << endl
		<< rec.m_PW << endl
		<< rec.m_Name << endl
		<< rec.m_Balance << endl;
}

void Record_ReadFromFile(wfstream& fs, Record& rec) //Read from File
{
	getline(fs, rec.m_ID);
	getline(fs, rec.m_PW);
	getline(fs, rec.m_Name);

	//Use _wtoi() to read m_Balance correctly
	wstring buf;
	getline(fs, buf);
	rec.m_Balance = _wtoi(buf.c_str());
}