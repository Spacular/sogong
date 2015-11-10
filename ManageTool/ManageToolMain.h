#pragma once
#include "atltypes.h"
#include "ManageToolODBC.h"

typedef struct StuInfo {
	int m_id;
	char m_name[10];
	char m_department[20];
	char m_gen[5];
	DATE_STRUCT m_birthdate;
	char picture[2000];
}StuInfo;

// CManageToolMain ��ȭ �����Դϴ�.
class CManageToolMain : public CDialogEx, public CManageToolODBC	// DB�κ��� �����͸� �޾ƿ;� �ϹǷ�, ����ؾ� ��.
{
	DECLARE_DYNAMIC(CManageToolMain)

public:
	CManageToolMain(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CManageToolMain();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	DECLARE_MESSAGE_MAP()

public:
	CString Errmsg = _T("");

	afx_msg void OnPaint();
	// ���� ���콺 �������� ��ġ�� ��Ÿ��
	CPoint m_point;
	// ���콺 �ֽ� ���� ��ǥ
	CPoint m_lbdown;
	// ���� ���콺 ���� Ŭ�� ��ǥ
	CPoint m_Oldlbdown;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	void MakeConn();			// CManageToolODBC Ŭ������ �����Լ��� ��ӹ޾� ����.
	StuInfo WhoIs(int Loc);
	// �ش� �л��� ID
	CString m_name;
	// �ش� �л��� ID
	CString m_ID;
	// �ش� �л��� �а�
	CString m_dept;
	// �ش� �л��� ����
	CString m_birth;
};
