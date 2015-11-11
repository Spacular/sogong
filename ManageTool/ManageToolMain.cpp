// ManageToolMain.cpp : 구현 파일입니다.

#include "stdafx.h"
#include "ManageTool.h"
#include "ManageToolMain.h"
#include "afxdialogex.h"
using namespace std;

// CManageToolMain 대화 상자입니다.

IMPLEMENT_DYNAMIC(CManageToolMain, CDialogEx)

CManageToolMain::CManageToolMain(CWnd* pParent /*=NULL*/)
: CDialogEx(CManageToolMain::IDD, pParent)
, m_point(0)
, m_lbdown(0)
, m_Oldlbdown(0)
, m_name(_T(""))
, m_ID(_T(""))
, m_dept(_T(""))
, m_birth(_T(""))
, m_Status(0)
{
	CManageToolMain::MakeConn();
}

CManageToolMain::~CManageToolMain()
{
}

void CManageToolMain::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_name);
	DDX_Text(pDX, IDC_EDIT2, m_ID);
	DDX_Text(pDX, IDC_EDIT3, m_dept);
	DDX_Text(pDX, IDC_EDIT4, m_birth);
	DDX_Radio(pDX, IDC_RADIO1, m_Status);
}

BEGIN_MESSAGE_MAP(CManageToolMain, CDialogEx)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CManageToolMain 메시지 처리기입니다.

void CManageToolMain::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	
	CPen newPen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen *pOldPen = dc.SelectObject(&newPen);	//팬 객체에 대한 포인터 저장.(이전 펜으로 되돌아 갈 시 필요.)

	int Init_x = 30;
	int Init_y = 30;
	int Pos_x = Init_x;
	int Pos_y = Init_y;
	int Interval_y = 30;
	int Interval_x = (int)(Interval_y * 1.78);
	int nRows = 10;		// 행(Row)의 수(Number).
	int nCols = 10;		// 열(Column)의 수.

	POINT Selected_Seat;		// 마우스로 선택한 좌석의 좌표
	Selected_Seat.x = 0;	Selected_Seat.y = 0;

	CRgn classroom[10][10];
	CRect desk[10][10];
	CString strData = _T("");
	//strData.Format(_T("X:%03d, Y:%03d"), m_lbdown.x, m_lbdown.y);

	for (int i = 0; i < nRows; i++){
		for (int j = 0; j < nCols; j++){
			dc.Rectangle(Pos_x, Pos_y, Pos_x + Interval_x, Pos_y + Interval_y);		//이 방법을 쓰면 표시는 된다.
			desk[i][j] = CRect(Pos_x, Pos_y, Pos_x + Interval_x, Pos_y + Interval_y);	// 이렇게 하니까 화면에 표시되지가 않는다,
			// dc.FillSolidRect(&desk, RGB(0, 0, 0));	사각형 내부 채우는 함수.
			// 그래서 위의 CRect를 제대로 표시되지 않더라도 일단 쓴다.
			classroom[i][j].CreateEllipticRgnIndirect(desk[i][j]);		// 이 함수에는 CRect 객체가 필요하다!
			Pos_x += Interval_x;
		}
		Pos_x = Init_x;
		Pos_y += Interval_y;
	}

	if (m_lbdown != m_Oldlbdown){
		BOOL result = 0;
		CString num, birth;

		num.Format(_T(""));	birth.Format(_T(""));				// 초기화!
		
		StuInfo info;

		info.m_birthdate.day = NULL;	info.m_birthdate.day = NULL; info.m_birthdate.day = NULL;	info.m_id = NULL;
		strcpy_s(info.m_department, "");	strcpy_s(info.m_gen, "");	strcpy_s(info.m_name, "");

		for (int i = 0; i < nRows; i++){
			for (int j = 0; j < nCols; j++){
				result = desk[i][j].PtInRect(m_lbdown);
				if (result)	{
					Selected_Seat.x = i;	Selected_Seat.y = j;
					int Loc = Selected_Seat.x * 10 + Selected_Seat.y + 1;
					// trData.Format(_T("%02d행, %02d열입니다."), Selected_Seat.x + 1, Selected_Seat.y + 1);
					// trData.Format(_T("%3d번 좌석입니다."), Selected_Seat.x * 10 + Selected_Seat.y + 1);
					// dc.TextOut(10, 10, strData);

					this->MakeConn();				// 이 클래스의 연결 획득!
					info = WhoIs(Loc);

					//CString strImagePath;
					//strImagePath.Format(_T("%s"), filename);
					
					string  strImagePath;
					strImagePath = filename;

					/**********************************************************************************************************/
					/*																	주													의										 	     */														
					/* Picture Control에 뿌려주기 위해 CImage를 사용해야 하며 이것의 매개변수는 CString 타입이다!! 반드시 구현!!!   */
					/**********************************************************************************************************/
					
					m_name = info.m_name;

					num.Format(_T("%d"), info.m_id);
					m_ID = num;

					m_dept = info.m_department;

					birth.Format(_T("%d - %d - %d"), info.m_birthdate.year, info.m_birthdate.month, info.m_birthdate.day);
					m_birth = birth;

					UpdateData(false);		// 값 갱신!
				}
			}
		}
		m_Oldlbdown = m_lbdown;
	}
}


void CManageToolMain::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CDialogEx::OnLButtonDown(nFlags, point);
	m_lbdown = point;
	RedrawWindow();
}


void CManageToolMain::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_point = point;
}


void CManageToolMain::MakeConn(){

	if ((retcode = SQLAllocEnv(&henv)) != SQL_SUCCESS){
		Errmsg.Format(_T("에러발생! 에러코드: %d"), retcode);		// 에러 형식을 정의한다.
		AfxMessageBox(Errmsg);								// 메세지 박스를 띄우고 정해진 내용을 출력한다.
	}
	if ((retcode = SQLAllocConnect(henv, &hdbc1)) != SQL_SUCCESS){
		Errmsg.Format(_T("에러발생! 에러코드: %d"), retcode);
		AfxMessageBox(Errmsg);
	}
		
	if ((retcode = SQLConnect(hdbc1, (SQLWCHAR *)TEXT("manage"/*DSN이름*/), SQL_NTS/*NULL문자 대신*/, (SQLWCHAR *)TEXT("root"/*접속계정*/), SQL_NTS, (SQLWCHAR *)TEXT("542133tlatms"/*비밀번호*/), SQL_NTS)) != SQL_SUCCESS){
		Errmsg.Format(_T("에러발생! 에러코드: %d"), retcode);
		AfxMessageBox(Errmsg);
	}
		
	SQLAllocStmt(hdbc1, &hstmt1);		// 실제 문장 Handle 획득
}


StuInfo CManageToolMain::WhoIs(int Loc){
	StuInfo stuinfo;										// 구조체 초기화

	stuinfo.m_birthdate.day = 0;
	stuinfo.m_birthdate.month = 0;
	stuinfo.m_birthdate.year = 0;
	stuinfo.m_id = 0;
	strcpy_s(stuinfo.m_department, sizeof("정보없음"), "정보없음");
	strcpy_s(stuinfo.m_gen, sizeof("정보없음"), "정보없음");
	strcpy_s(stuinfo.m_name, sizeof("정보없음"), "정보없음");
	/* 초기화는 함수를 통해서 하지말고 직접 해줘야 되네...*/


	int save0, save1, save2, save3, save4, save5, save6, pos, Pic_size = 0;

	pos = Loc - 1;

	SQLWCHAR* pic_size_query = (SQLWCHAR*)TEXT("select octet_length(m_picture) from member as m inner join seat as s on m.m_id = s.m_id and s_location = ?;");
	SQLWCHAR* query = (SQLWCHAR*)TEXT("select m.m_id, m_name, m_department, m_gen, m_birthdate, m_picture from member as m inner join seat as s on m.m_id = s.m_id and s_location = ?;");

	/********** BLOC data 크기 알아내는 부분	********/
	if ((retcode = SQLPrepare(hstmt1, /*보낼 SQL 문자열*/pic_size_query, SQL_NTS)) != SQL_SUCCESS){
		Errmsg.Format(_T("에러발생! 에러코드: %d"), retcode);
		AfxMessageBox(Errmsg);
	}
	else{
		if ((retcode = SQLBindParameter(hstmt1, 1, SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER, 0, 0, &pos, 0, NULL)) != SQL_SUCCESS){
			Errmsg.Format(_T("에러발생! 에러코드: %d"), retcode);
			AfxMessageBox(Errmsg);
		}
	}

	if (retcode == SQL_SUCCESS)
		retcode = SQLExecute(hstmt1);

	if (retcode == SQL_SUCCESS)
	{
		retcode = SQLBindCol(hstmt1, 1, SQL_C_SLONG, &Pic_size, sizeof(Pic_size), (SQLINTEGER *)&save0);	// 결과물의 첫 번째 Column을 저장.
	}
	while (SQLFetch(hstmt1) == SQL_SUCCESS);
	/********** BLOC data 크기 알아내는 부분	********/

	if (Pic_size == 0)	{
		Errmsg.Format(_T("에러발생! 에러코드: %d"), -999);
		AfxMessageBox(Errmsg);
		AfxMessageBox(_T("사진이 존재하지 않습니다! "));
		//CManageToolMain::OnClose();
		//OnDestroy();
		//::SendMessage(this->m_hWnd, WM_CLOSE, NULL, NULL);
	}
	char *m_picture = (char*)calloc(Pic_size, sizeof(char));
	// 알아낸 크기대로 설정!

	if ((retcode = SQLPrepare(hstmt1, query/*보낼 SQL 문자열*/, SQL_NTS)) != SQL_SUCCESS){
		Errmsg.Format(_T("에러발생! 에러코드: %d"), retcode);
		AfxMessageBox(Errmsg);
	}
	else{
		if ((retcode = SQLBindParameter(hstmt1, 1, SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER, 0, 0, &pos, 0, NULL)) != SQL_SUCCESS){
			Errmsg.Format(_T("에러발생! 에러코드: %d"), retcode);
			AfxMessageBox(Errmsg);
		}
	}
	if (retcode == SQL_SUCCESS)
		retcode = SQLExecute(hstmt1);
	if (retcode == SQL_SUCCESS)
	{
		retcode = SQLBindCol(hstmt1, 1, SQL_C_SLONG, &stuinfo.m_id, sizeof(stuinfo.m_id), (SQLINTEGER *)&save1);	// 결과물의 첫 번째 Column을 저장.
		retcode = SQLBindCol(hstmt1, 2, SQL_C_CHAR, stuinfo.m_name, sizeof(stuinfo.m_name), (SQLINTEGER *)&save2);	// 결과물의 두 번째 Column을 저장.
		retcode = SQLBindCol(hstmt1, 3, SQL_C_CHAR, stuinfo.m_department, sizeof(stuinfo.m_department), (SQLINTEGER *)&save3);	// 결과물의 세 번째 Column을 저장.
		retcode = SQLBindCol(hstmt1, 4, SQL_C_CHAR, stuinfo.m_gen, sizeof(stuinfo.m_gen), (SQLINTEGER *)&save4);	// 결과물의 네 번째 Column을 저장.
		retcode = SQLBindCol(hstmt1, 5, SQL_C_DATE, &stuinfo.m_birthdate, sizeof(stuinfo.m_birthdate) + 10, (SQLINTEGER *)&save5);	// 결과물의 다섯번째 Column을 저장.
		if (Pic_size != 0)
			retcode = SQLBindCol(hstmt1, 6, SQL_C_BINARY, m_picture, Pic_size, (SQLINTEGER *)&save6);	// 결과물의 여섯번째 Column을 저장.
	}
	while (SQLFetch(hstmt1) == SQL_SUCCESS);

	if (Pic_size != 0){
		strcpy_s(filename, "pic_");
		ofstream output;
		char num[8];
		sprintf_s(num, sizeof(num), "%03d.jpg", pos);
		strcpy_s(filename + 3, sizeof(num), num);

		output.open(filename, ios::binary);					// 'pic_좌석번호' 의 형식으로 저장

		for (int i = 0; i < Pic_size; i++)
			output << m_picture[i];
	}

	SQLFreeStmt(hstmt1, SQL_DROP);
	SQLDisconnect(hdbc1);
	SQLFreeConnect(hdbc1);
	SQLFreeEnv(henv);

	return stuinfo;
}

/***************************************************
BLOB 데이터 크기 알아내기(Mysql)

select OCTET_LENGTH(m_picture)
from (table)~~~~
where ~~~;

**************************************************/

StuInfo CManageToolMain::initValue(StuInfo info){
	info.m_birthdate.day = 0;
	info.m_birthdate.month = 0;
	info.m_birthdate.year = 0;
	info.m_id = 0;
	strcpy_s(info.m_department, "");
	strcpy_s(info.m_gen, "");
	strcpy_s(info.m_name, "");

	return info;
}