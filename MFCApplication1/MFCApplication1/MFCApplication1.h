
// MFCApplication1.h : MFCApplication1 ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CMFCApplication1App:
// �� Ŭ������ ������ ���ؼ��� MFCApplication1.cpp�� �����Ͻʽÿ�.
//

class CMFCApplication1App : public CWinApp
{
public:
	CMFCApplication1App();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCApplication1App theApp;
