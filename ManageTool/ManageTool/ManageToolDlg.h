
// ManageToolDlg.h : ��� ����
//

#pragma once


// CManageToolDlg ��ȭ ����
class CManageToolDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CManageToolDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MANAGETOOL_DIALOG };
#endif

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
	// ������ �Է¹޴� ��
	CString m_strID;
	// ��й�ȣ�� �Է¹޴� ��
	CString m_strPwd;

	int result;			// Login Ŭ������ isExist �Լ��� �����ϰ� ��ȯ���� ������� ������ ����.
	afx_msg void OnBnClickedLogin();
};
