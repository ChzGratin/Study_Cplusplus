/*================================
�ۼ���: 202035156 ������
�ۼ���: 2021-01-12
================================*/

#ifndef CAPP_CPP
#define CAPP_CPP

#include "CApp.h"

template <typename R>
CApp<R>::CApp(wstring FileName): m_DBM(FileName), m_curRecord(nullptr)
{}

#endif