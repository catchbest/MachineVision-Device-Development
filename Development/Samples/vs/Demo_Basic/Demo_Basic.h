
// Demo_Basic.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDemo_BasicApp: 
// �йش����ʵ�֣������ Demo_Basic.cpp
//

class CDemo_BasicApp : public CWinApp
{
public:
	CDemo_BasicApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CDemo_BasicApp theApp;