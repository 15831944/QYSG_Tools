
// DropItem.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

#include "Local_com.h"

#include "DropItemDlg.h"
#include "ArmyDlg.h"
#include "PlayersDlg.h"


// CDropItemApp:
// �йش����ʵ�֣������ DropItem.cpp
//

class CDropItemApp : public CWinApp
{
public:
	CDropItemApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CDropItemApp theApp;