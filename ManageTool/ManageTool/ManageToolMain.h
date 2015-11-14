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
	DATE_STRUCT m_birthdate;
}StuInfo;

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

private:
	CString m_name;
	// ������ �л��� ID
	CString m_ID;
public:
	// ��ȯ���� �а� ����
	CString m_dept;
	// �л� ����
	CString m_gen;
	afx_msg void OnPaint();
	CString m_birth;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
