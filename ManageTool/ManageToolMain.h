#pragma once
#include "atltypes.h"
#include "ManageToolODBC.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "afxwin.h"
#include <atlimage.h>

typedef struct StuInfo {
	int m_id;
	char m_name[10];
	char m_department[20];
	//string m_department;
	char m_gen[5];
	DATE_STRUCT m_birthdate;
}StuInfo;

// CManageToolMain 대화 상자입니다.
class CManageToolMain : public CDialogEx, public CManageToolODBC	// DB로부터 데이터를 받아와야 하므로, 상속해야 함.
{
	DECLARE_DYNAMIC(CManageToolMain)

public:
	CManageToolMain(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CManageToolMain();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()

public:
	CString Errmsg = _T("");

	afx_msg void OnPaint();
	// 현재 마우스 포인터의 위치를 나타냄
	CPoint m_point;
	// 마우스 최신 왼쪽 좌표
	CPoint m_lbdown;
	// 이전 마우스 왼쪽 클릭 좌표
	CPoint m_Oldlbdown;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	void MakeConn();			// CManageToolODBC 클래스의 가상함수를 상속받아 정의.
	StuInfo initValue(StuInfo info);

public:
	StuInfo WhoIs(int Loc);
	// 해당 학생의 ID
	CString m_name;
	// 해당 학생의 ID
	CString m_ID;
	// 해당 학생의 학과
	CString m_dept;
	// 해당 학생의 생일
	CString m_birth;

	// 사진 파일의 저장용 이름
	char filename[11];
	int m_Status;
};
