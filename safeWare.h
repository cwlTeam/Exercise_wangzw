
// safeWare.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CsafeWareApp:
// �йش����ʵ�֣������ safeWare.cpp
//

class CsafeWareApp : public CWinApp
{
public:
	CsafeWareApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CsafeWareApp theApp;