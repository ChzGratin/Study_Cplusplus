/*================================
�ۼ���: 202035156 ������
�ۼ���: 2021-01-12
================================*/

#ifndef CRECORD_H
#define CRECORD_H

#include <string>
#include <fstream>
using namespace std;

//CRecord�� ��� �޼ҵ�(�߿�):
//���� �����(wfstream���� <<, >> ����) ������ �ϴ� �����Լ� ReadFromFile(), WriteToFile()
//R�� �� ����� ���� ������ ��ȯ�ϴ� �޼ҵ�
//ex) GetID(), GetPW(), GetName(), etc.

//���� �Է� ��Ģ:
// i) �� ���� �ϳ��� ����� �����ȴ�.
//ii) �� ���ڵ�� '\n'���� ���еȴ�.

//���� ��� ��Ģ:
// i) �� �࿡ �ϳ��� ����� ����Ѵ�.
//ii) ��� ����� ����ߴٸ�, ���� '\n'�� �߰��Ѵ�.

//���ڵ� Ŭ����
class CRecord
{
protected:
	wstring m_ID;

public:
	CRecord();
	CRecord(const CRecord&); //���������

	virtual void ReadFromFile(wfstream& fs);
	virtual void WriteToFile(wfstream& fs);
	wstring& GetID();
};

#endif