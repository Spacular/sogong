
// ManageToolDlg.h : ��� ����

#pragma once
#include "ManageToolLogin.h"


// CManageToolDlg ��ȭ ����
class CManageToolDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CManageToolDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MANAGETOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// �α׿� ���̵�
	CString m_strID;
	// ��й�ȣ
	CString m_strPwd;
	CString message = _T("");
	afx_msg void OnBnClickedButton1();
};
