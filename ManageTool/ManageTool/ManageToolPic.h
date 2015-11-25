#pragma once


// CManageToolPic 대화 상자입니다.

class CManageToolPic : public CDialogEx
{
	DECLARE_DYNAMIC(CManageToolPic)

public:
	CManageToolPic(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CManageToolPic();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAINDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};
