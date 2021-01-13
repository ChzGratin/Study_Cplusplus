/*================================
작성자: 202035156 박정현
작성일: 2021-01-12
================================*/

#ifndef CAPP_CPP
#define CAPP_CPP

#include "CApp.h"

template <typename R>
CApp<R>::CApp(wstring FileName): CDBManager<R>(FileName), m_curRecord(nullptr)
{}

#endif