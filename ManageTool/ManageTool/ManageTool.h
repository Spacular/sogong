
// ManageTool.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CManageToolApp:
// �� Ŭ������ ������ ���ؼ��� ManageTool.cpp�� �����Ͻʽÿ�.
//

class CManageToolApp : public CWinApp
{
public:
	CManageToolApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CManageToolApp theApp;