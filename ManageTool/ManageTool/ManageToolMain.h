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

	}   // 표준 생성자입니다.
	virtual ~CManageToolMain();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAINDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()

public:
	CString Errmsg = _T("");

	// 사진 파일의 저장용 이름
	char filename[11];
	int m_Status;

	// 현재 마우스 포인터의 위치를 나타냄
	CPoint m_point;
	// 마우스 최신 왼쪽 좌표
	CPoint m_lbdown;
	// 이전 마우스 왼쪽 클릭 좌표
	CPoint m_Oldlbdown;
	// 해당 학생이 존재하는지 확인!
	StuInfo WhoIs(int Loc);
	// 선택한 학생의 이름
	void MakeConn();
	void Scan(int* result);

private:
	CString m_name;
	// 선택한 학생의 ID
	CString m_ID;
	bool isFirst = TRUE;
	int location[100] = {};
	int count;						// s_chech를 확인하여 착석한 좌석의 갯수를 나타냄. First()함수에서 사용.
	int result[100];		// 착석한 결과. 최대 100명을 수용할 수 있어야 하므로.
public:
	// 반환받은 학과 정보
	CString m_dept;
	// 학생 성별
	CString m_gen;
	afx_msg void OnPaint();
	CString m_birth;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
