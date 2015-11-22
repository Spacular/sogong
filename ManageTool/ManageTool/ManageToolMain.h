#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <atlimage.h>
#include "afxwin.h"
#include "ManageToolODBC.h"
#include "atltypes.h"

typedef struct StuInfo {
	int m_id;
	char m_name[10];
	char m_department[20];
	//string m_department;
	char m_gen[5];
	int m_attendance;
	CHAR m_qcontent[200];		// ������ �ִ� 200�ڱ���;
	DATE_STRUCT m_birthdate;
}StuInfo;

typedef struct attendance {
	int s_location;
	int m_warning;
	int m_question;
}attendance;

class CManageToolMain : public CDialogEx, public CManageToolODBC
{
	DECLARE_DYNAMIC(CManageToolMain)

public:
	CManageToolMain(CWnd* pParent = NULL)
		: CDialogEx(IDD_MAINDLG, pParent)
		, m_name(_T(""))
		, m_dept(_T(""))
		, m_gen(_T(""))
		, m_birth(_T(""))
		, m_qcontent(_T(""))
		, m_radio(0)
	{

	}   // ǥ�� �������Դϴ�.
	virtual ~CManageToolMain();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAINDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	DECLARE_MESSAGE_MAP()

public:
	CString Errmsg = _T("");

	// ���� ������ ����� �̸�
	char filename[11];
	int m_Status;

	// ���� ���콺 �������� ��ġ�� ��Ÿ��
	CPoint m_point;
	// ���콺 �ֽ� ���� ��ǥ
	CPoint m_lbdown;
	// ���� ���콺 ���� Ŭ�� ��ǥ
	CPoint m_Oldlbdown;
	// �ش� �л��� �����ϴ��� Ȯ��!
	StuInfo WhoIs(int Loc);
	// ������ �л��� �̸�
	void MakeConn();
	void Scan(attendance* result);

private:
	CString m_name;
	// ������ �л��� ID
	CString m_ID;
	bool isFirst = TRUE;
	int location[100] = {};
	int count;						// s_chech�� Ȯ���Ͽ� ������ �¼��� ������ ��Ÿ��. First()�Լ����� ���.
	attendance result[100];		// ������ ���. �ִ� 100���� ������ �� �־�� �ϹǷ�.
public:
	// ��ȯ���� �а� ����
	CString m_dept;
	// �л� ����
	CString m_gen;
	afx_msg void OnPaint();
	CString m_birth;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	CString m_qcontent;			// ���� ���� ��Ʈ�ѿ� ����� ����
	int m_radio;				// ���� ��ư�� ����� ������
	BOOL PreTranslateMessage(MSG* pMsg);
	void SetProfileImage(CString str);
		// Picture Control�� ����� ����
	CStatic m_profileImage;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	CString str_loc;			// ����� ���� ������ ���
};
