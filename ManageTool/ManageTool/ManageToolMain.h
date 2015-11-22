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
	CHAR m_qcontent[200];		// 질문은 최대 200자까지;
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
	void Scan(attendance* result);

private:
	CString m_name;
	// 선택한 학생의 ID
	CString m_ID;
	bool isFirst = TRUE;
	int location[100] = {};
	int count;						// s_chech를 확인하여 착석한 좌석의 갯수를 나타냄. First()함수에서 사용.
	attendance result[100];		// 착석한 결과. 최대 100명을 수용할 수 있어야 하므로.
public:
	// 반환받은 학과 정보
	CString m_dept;
	// 학생 성별
	CString m_gen;
	afx_msg void OnPaint();
	CString m_birth;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	CString m_qcontent;			// 질문 에딧 컨트롤에 연결된 변수
	int m_radio;				// 라디오 버튼과 연결된 변수임
	BOOL PreTranslateMessage(MSG* pMsg);
	void SetProfileImage(CString str);
		// Picture Control과 연결된 변수
	CStatic m_profileImage;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	CString str_loc;			// 저장된 사진 파일의 경로
};
