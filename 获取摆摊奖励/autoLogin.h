
// autoLogin.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CautoLoginApp: 
// �йش����ʵ�֣������ autoLogin.cpp
//

class CautoLoginApp : public CWinApp
{
public:
	CautoLoginApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CautoLoginApp theApp;