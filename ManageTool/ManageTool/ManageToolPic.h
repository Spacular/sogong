#pragma once


// CManageToolPic ��ȭ �����Դϴ�.

class CManageToolPic : public CDialogEx
{
	DECLARE_DYNAMIC(CManageToolPic)

public:
	CManageToolPic(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CManageToolPic();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAINDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};
