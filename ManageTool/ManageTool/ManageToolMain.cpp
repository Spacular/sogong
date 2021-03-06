#include "stdafx.h"
#include "ManageTool.h"
#include "ManageToolMain.h"
#include "ManageToolPic.h"
#include "afxdialogex.h"
#include <atlimage.h>
#include <afxwin.h>
#include <afxconv.h>
#include "UTF8Conv.h"

using namespace std;

// CManageToolMain 대화 상자입니다.

IMPLEMENT_DYNAMIC(CManageToolMain, CDialogEx)

CManageToolMain::CManageToolMain(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MAINDLG, pParent)
	, m_name(_T(""))
	, m_dept(_T(""))
	, m_gen(_T(""))
	, m_birth(_T(""))
	, m_qcontent(_T(""))
	, m_radio(0)
{
	strcpy_s(filename, "pic/pic_");				// filename 초기화.
	count = 0;									// count 초기화.
	for (int i = 0; i < 100; i++) {				// attendance 구조체 각 요소 초기화.
		result[i].m_question = 0;
		result[i].m_warning = 0;
		result[i].s_location = 0;
	}
	m_qcontent.Format(_T(""));

}   // 표준 생성자입니다.
CManageToolMain::~CManageToolMain()
{
}

void CManageToolMain::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_name);
	DDX_Text(pDX, IDC_EDIT2, m_ID);
	DDX_Text(pDX, IDC_EDIT3, m_dept);
	DDX_Text(pDX, IDC_EDIT4, m_gen);
	DDX_Text(pDX, IDC_EDIT5, m_birth);
	DDX_Radio(pDX, IDC_RADIO1, m_radio);
	DDX_Control(pDX, IDC_EDIT6, m_profileImage);
	DDX_Text(pDX, IDC_EDIT7, m_qcontent);
}


BEGIN_MESSAGE_MAP(CManageToolMain, CDialogEx)
	ON_WM_PAINT()//
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	ON_WM_ACTIVATE()
//	ON_EN_CHANGE(IDC_EDIT7, &CManageToolMain::OnEnChangeEdit7)
	ON_BN_CLICKED(IDC_RADIO2, &CManageToolMain::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CManageToolMain::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO1, &CManageToolMain::OnBnClickedRadio1)
END_MESSAGE_MAP()


// CManageToolMain 메시지 처리기입니다.


void CManageToolMain::MakeConn() {

	if ((retcode = SQLAllocEnv(&henv)) != SQL_SUCCESS) {
		Errmsg.Format(_T("에러발생! 에러코드: %d"), retcode);		// 에러 형식을 정의한다.
		AfxMessageBox(Errmsg);								// 메세지 박스를 띄우고 정해진 내용을 출력한다.
	}
	if ((retcode = SQLAllocConnect(henv, &hdbc1)) != SQL_SUCCESS) {
		Errmsg.Format(_T("에러발생! 에러코드: %d"), retcode);
		AfxMessageBox(Errmsg);
	}

	if ((retcode = SQLConnect(hdbc1, (SQLWCHAR *)TEXT("loginapp"/*DSN이름*/), SQL_NTS/*NULL문자 대신*/, (SQLWCHAR *)TEXT("genius"/*접속계정*/), SQL_NTS, (SQLWCHAR *)TEXT("12345678"/*비밀번호*/), SQL_NTS)) != SQL_SUCCESS) {
		Errmsg.Format(_T("에러발생! 에러코드: %d"), retcode);
		AfxMessageBox(Errmsg);
	}

	SQLAllocStmt(hdbc1, &hstmt1);		// 실제 문장 Handle 획득
}

void CManageToolMain::Scan(attendance* result) {
	int save;

	SQLWCHAR* query = (SQLWCHAR*)TEXT("select s_location, m_warning, m_question from member as m inner join seat as s on m.m_id = s.m_id where s_check = 'x';");
	/*
	select s_location, m_warning, m_question
	from member as m inner join seat as s
	on m.m_id = s.m_id
	where s_check = 'x';
	*/
	if ((retcode = SQLPrepare(hstmt1, /*보낼 SQL 문자열*/query, SQL_NTS)) != SQL_SUCCESS) {
		Errmsg.Format(_T("에러발생! 에러코드: %d"), retcode);
		AfxMessageBox(Errmsg);
	}

	retcode = SQLExecute(hstmt1);

	if (retcode == SQL_SUCCESS)
	{
		count = 0;
		retcode = SQLBindCol(hstmt1, 1, SQL_C_SLONG, &(result + (count))->s_location, sizeof(result), (SQLINTEGER *)&save);	// 결과물의 첫 번째 Column을 저장.
		retcode = SQLBindCol(hstmt1, 2, SQL_C_SLONG, &(result + (count))->m_warning, sizeof(result), (SQLINTEGER *)&save);	// 결과물의 두 번째 Column을 저장.
		retcode = SQLBindCol(hstmt1, 3, SQL_C_SLONG, &(result + (count))->m_question, sizeof(result), (SQLINTEGER *)&save);	// 결과물의 세 번째 Column을 저장.
	}
	while (SQLFetch(hstmt1) == SQL_SUCCESS) {
		count++;
		retcode = SQLBindCol(hstmt1, 1, SQL_C_SLONG, &(result + (count))->s_location, sizeof(result), (SQLINTEGER *)&save);	// 결과물의 첫 번째 Column을 저장.
		retcode = SQLBindCol(hstmt1, 2, SQL_C_SLONG, &(result + (count))->m_warning, sizeof(result), (SQLINTEGER *)&save);	// 결과물의 두 번째 Column을 저장.
		retcode = SQLBindCol(hstmt1, 3, SQL_C_SLONG, &(result + (count))->m_question, sizeof(result), (SQLINTEGER *)&save);	// 결과물의 세 번째 Column을 저장.
	}

	SQLFreeStmt(hstmt1, SQL_DROP);
	SQLDisconnect(hdbc1);
	SQLFreeConnect(hdbc1);
	SQLFreeEnv(henv);
}

StuInfo CManageToolMain::WhoIs(int Loc) {

	StuInfo stuinfo;										// 구조체 선언.

	stuinfo.m_birthdate.day = 0;
	stuinfo.m_birthdate.month = 0;
	stuinfo.m_birthdate.year = 0;
	stuinfo.m_id = 0;
	strcpy_s(stuinfo.m_department, sizeof("정보없음"), "정보없음");
	strcpy_s(stuinfo.m_gen, sizeof("정보없음"), "정보없음");
	strcpy_s(stuinfo.m_name, sizeof("정보없음"), "정보없음");
	stuinfo.m_attendance = 2;		// 기본적으로 결석으로 초기화!
////////////////////////////////////



	/* 초기화는 함수를 통해서 하지말고 직접 해줘야 되네...*/


	int save0, save1, save2, save3, save4, save5, save6, save7, save8, pos, Pic_size = 0;
	int check = 0;		// 학생이 존재하는지 체크하는 SQL문 수행 결과를 저장하는 변수.
	pos = Loc - 1;
	SQLWCHAR* check_query = (SQLWCHAR*)TEXT("select m.m_id from member as m inner join seat as s on m.m_id = s.m_id where s_location = ?;");
	SQLWCHAR* pic_size_query = (SQLWCHAR*)TEXT("select octet_length(m_picture) from member as m inner join seat as s on m.m_id = s.m_id and s_location = ?;");
	SQLWCHAR* query = (SQLWCHAR*)TEXT("select m.m_id, m_name, m_department, m_gen, m_birthdate, m_picture, m_attendance, m_qcontent from member as m inner join seat as s on m.m_id = s.m_id and s_location = ?;");
	SQLWCHAR* question_query_one = (SQLWCHAR*)TEXT("update member set m_question = 0 where m_id = ?;");
	SQLWCHAR* question_query_two = (SQLWCHAR*)TEXT("update member set m_qcontent = '' where m_id = ?;");
   
	//ㅊㄱ 학생좌석이 어디있는지 알아내는 부분 
	if ((retcode = SQLPrepare(hstmt1, /*보낼 SQL 문자열*/check_query, SQL_NTS)) != SQL_SUCCESS) {
		Errmsg.Format(_T("에러발생! 에러코드: %d"), retcode);
		AfxMessageBox(Errmsg);
	}
	else {
		if ((retcode = SQLBindParameter(hstmt1, 1, SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER, 0, 0, &pos, 0, NULL)) != SQL_SUCCESS) {
			Errmsg.Format(_T("에러발생! 에러코드: %d"), retcode);
			AfxMessageBox(Errmsg);
		}
	}

	if (retcode == SQL_SUCCESS)
		retcode = SQLExecute(hstmt1);

	if (retcode == SQL_SUCCESS)
	{
		retcode = SQLBindCol(hstmt1, 1, SQL_C_SLONG, &check, sizeof(check), (SQLINTEGER *)&save0);	// 결과물의 첫 번째 Column을 저장.
	}

	while (SQLFetch(hstmt1) == SQL_SUCCESS) { ; }

	if (check == 0)
	{
		Errmsg.Format(_T("에러발생! 에러코드: %d"), -1);
		AfxMessageBox(Errmsg);
		AfxMessageBox(_T("학생이 존재하지 않습니다!"));
		return stuinfo;
	} //ㅊㄱ
	/********** BLOC data 크기 알아내는 부분	********/
	if ((retcode = SQLPrepare(hstmt1, /*보낼 SQL 문자열*/pic_size_query, SQL_NTS)) != SQL_SUCCESS) {
		Errmsg.Format(_T("에러발생! 에러코드: %d"), retcode);
		AfxMessageBox(Errmsg);
	}
	else {
		if ((retcode = SQLBindParameter(hstmt1, 1, SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER, 0, 0, &pos, 0, NULL)) != SQL_SUCCESS) {
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

	if (Pic_size == 0) {
		Errmsg.Format(_T("에러발생! 에러코드: %d"), -999);
		//AfxMessageBox(Errmsg);
		//AfxMessageBox(_T("사진이 존재하지 않습니다! "));
		//CManageToolMain::OnClose();
		//OnDestroy();
		//::SendMessage(this->m_hWnd, WM_CLOSE, NULL, NULL);
	}
	char *m_picture = (char*)calloc(Pic_size, sizeof(char));
	// 알아낸 크기대로 설정!

	if ((retcode = SQLPrepare(hstmt1, query/*보낼 SQL 문자열*/, SQL_NTS)) != SQL_SUCCESS) {
		Errmsg.Format(_T("에러발생! 에러코드: %d"), retcode);
		AfxMessageBox(Errmsg);
	}
	else {
		if ((retcode = SQLBindParameter(hstmt1, 1, SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER, 0, 0, &pos, 0, NULL)) != SQL_SUCCESS) {
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
		retcode = SQLBindCol(hstmt1, 7, SQL_C_SLONG, &stuinfo.m_attendance, sizeof(stuinfo.m_attendance), (SQLINTEGER *)&save7);	// 결과물의 일곱번째 Column을 저장.
		retcode = SQLBindCol(hstmt1, 8, SQL_C_CHAR, &stuinfo.m_qcontent, sizeof(stuinfo.m_qcontent), (SQLINTEGER *)&save8);	// 결과물의 일곱번째 Column을 저장.
	}
	while (SQLFetch(hstmt1) == SQL_SUCCESS);

	/*********************************** 알아낸 학번으로 해당 학생의 질문의사를 초기화시키는 SQL **************************************/
	if ((retcode = SQLPrepare(hstmt1, /*보낼 SQL 문자열*/question_query_one, SQL_NTS)) != SQL_SUCCESS) {
		Errmsg.Format(_T("에러발생! 에러코드: %d"), retcode);
		AfxMessageBox(Errmsg);
	}
	else {
		if ((retcode = SQLBindParameter(hstmt1, 1, SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER, 0, 0, &stuinfo.m_id, 0, NULL)) != SQL_SUCCESS) {
			Errmsg.Format(_T("에러발생! 에러코드: %d"), retcode);
			AfxMessageBox(Errmsg);
		}
	}
	if (retcode == SQL_SUCCESS)
		retcode = SQLExecute(hstmt1);
	/*****************************************************************************************************************************/
	/******************************** 알아낸 학번으로 해당 학생의 질문내용을 초기화시키는 SQL *******************************************/
	if ((retcode = SQLPrepare(hstmt1, /*보낼 SQL 문자열*/question_query_two, SQL_NTS)) != SQL_SUCCESS) {
		Errmsg.Format(_T("에러발생! 에러코드: %d"), retcode);
		AfxMessageBox(Errmsg);
	}
	else {
		if ((retcode = SQLBindParameter(hstmt1, 1, SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER, 0, 0, &stuinfo.m_id, 0, NULL)) != SQL_SUCCESS) {
			Errmsg.Format(_T("에러발생! 에러코드: %d"), retcode);
			AfxMessageBox(Errmsg);
		}
	}
	if (retcode == SQL_SUCCESS)
		retcode = SQLExecute(hstmt1);
	/****************************************************************************************************************************/
	
	if (Pic_size != 0) {
		CreateDirectory(_T("pic/"), NULL);
		strcpy_s(filename, "pic/pic_");
		ofstream output;
		char num[8];
		sprintf_s(num, sizeof(num), "%03d.jpg", pos + 1);
		strcpy_s(filename + 8, sizeof(num), num);

		output.open(filename, ios::binary);					// 'pic_좌석번호' 의 형식으로 저장

		for (int i = 0; i < Pic_size; i++)
			output << m_picture[i];

		free(m_picture);
	}

	SQLFreeStmt(hstmt1, SQL_DROP);
	SQLDisconnect(hdbc1);
	SQLFreeConnect(hdbc1);
	SQLFreeEnv(henv);

	if (strcmp(stuinfo.m_qcontent, "") == 0) {
		strcpy_s(stuinfo.m_qcontent, sizeof("질문없음"), "질문없음");
	}

	if ((stuinfo.m_attendance < 0) || (stuinfo.m_attendance > 2))
	{
		stuinfo.m_attendance = 2;			// 이상한값이 들어있어도 결석으로 처리;
	}
	
	return stuinfo;
}

void CManageToolMain::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 __super::OnPaint()을(를) 호출하지 마십시오.

	CPen newPen(PS_SOLID, 1, RGB(0, 0, 0));
	//CPen *pOldPen = dc.SelectObject(&newPen);	//팬 객체에 대한 포인터 저장.(이전 펜으로 되돌아 갈 시 필요.)

	int Init_x = 20;
	int Init_y = 20;
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

	if (isFirst)
	{
		this->MakeConn();
		Scan(result);
		isFirst = FALSE;
		SetTimer(1, 5000, NULL);		// 5초에 한 번 꼴로 확인!
	}

	for (int i = 0; i < nRows; i++) {
		for (int j = 0; j < nCols; j++) {
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


	// 가져온 데이터 개수만큼 사각형 내부 색칠
	for (int i = 0; i < count; i++) 
	{
		int row = result[i].s_location / 10;	// 행 위치
		int column = result[i].s_location % 10;	// 열 위치
	
		if		(result[i].m_warning == 1)	dc.FillSolidRect(&desk[row][column], RGB(255, 0, 0));	// 의심학생은 빨간색으로
		else if (result[i].m_question == 1)	dc.FillSolidRect(&desk[row][column], RGB(255, 255, 0));	// 질문 있는 학생은 노란색으로
		else	dc.FillSolidRect(&desk[row][column], RGB(0, 0, 0));		// 그 외의 일반 출석은 검은색으로
	}

	if (m_lbdown != m_Oldlbdown) {
		BOOL result = 0;
		CString num, birth;

		StuInfo info;

		num.Format(_T(""));	birth.Format(_T(""));				// 초기화!
		
		info.m_birthdate.day = NULL;	info.m_birthdate.day = NULL; info.m_birthdate.day = NULL;	info.m_id = NULL;
		strcpy_s(info.m_department, "");	strcpy_s(info.m_gen, "");	strcpy_s(info.m_name, ""); // m_qcontent = "";

		for (int i = 0; i < nRows; i++) { 
			for (int j = 0; j < nCols; j++) {
				result = desk[i][j].PtInRect(m_lbdown);
				if (result) {
					Selected_Seat.x = i;	Selected_Seat.y = j;
					int Loc = Selected_Seat.x * 10 + Selected_Seat.y + 1;
					// trData.Format(_T("%02d행, %02d열입니다."), Selected_Seat.x + 1, Selected_Seat.y + 1);
					// trData.Format(_T("%3d번 좌석입니다."), Selected_Seat.x * 10 + Selected_Seat.y + 1);
					// dc.TextOut(10, 10, strData);

					this->MakeConn();				// 이 클래스의 연결 획득!
					info = WhoIs(Loc);

					CString str = _T("test");
					int strLen = str.GetLength();
					char* ch = new char[strLen + 1];
					WideCharToMultiByte(CP_ACP, 0, str, -1, ch, strLen + 1, NULL, NULL);


					CPaintDC dc(this);
					CString strImagePath = _T("");

					m_name = info.m_name;
					num.Format(_T("%d"), info.m_id);
					m_ID = num;
					m_dept = info.m_department;
					birth.Format(_T("%d - %d - %d"), info.m_birthdate.year, info.m_birthdate.month, info.m_birthdate.day);					m_birth = birth;

					if (strcmp(info.m_gen, "m") == 0)
					{
						TCHAR *man = L"남자";// 남자일 경우
						m_gen.Format(_T("%s"), man);
					}
					else if (strcmp(info.m_gen, "f") == 0)
					{
						TCHAR *woman = L"여자";// 여자일 경우
						m_gen.Format(_T("%s"), woman);
					}
					m_qcontent = info.m_qcontent;

					str_loc.Format(_T("%03d"), Loc);
					SetProfileImage(str_loc);
					CString str_id;
					str_id.Format(_T("%d"), info.m_id);
					SetProfileImage(str_id);	
					m_radio = info.m_attendance;
					
					UpdateData(FALSE);		// 값 갱신!
				}
			}
		}
		m_Oldlbdown = m_lbdown;
	}
}

void CManageToolMain::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_lbdown = point;
	Invalidate(FALSE);
}

void CManageToolMain::SetProfileImage(CString str)
{
	CDC *dc = m_profileImage.GetWindowDC();
	CImage m_jpg;	// jpg이미지
	static CString strImagePath;
	
	if (str != "")
	{
		//strImagePath = _T("res/") + str + _T(".jpg");
		strImagePath = _T("pic/pic_") + str + _T(".jpg");
	}
	dc->SetStretchBltMode(COLORONCOLOR); //이거하니깐 화면닿는부분 모양사라짐 

	HRESULT hResult = m_jpg.Load(strImagePath);

	if(!FAILED(hResult))
	{
		CRect rect;
		m_profileImage.GetClientRect(rect);
		//m_jpg.BitBlt(dc->m_hDC, 0, 0);
		m_jpg.StretchBlt(dc->m_hDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY); //이거하니깐 화면닿는부분 모양사라짐, 픽쳐컨트롤 크기에 맞게 이미지 크기 조정
	}
	m_profileImage.ReleaseDC(dc);
}

BOOL CManageToolMain::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)	// 엔터나 ESC 종료 방지
		return TRUE;

	return __super::PreTranslateMessage(pMsg);
}

void CManageToolMain::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	this->MakeConn();
	Scan(this->result);

	Invalidate(FALSE);
	//RedrawWindow();
	//__super::OnTimer(nIDEvent);

	/*
	CPaintDC dc(this);
	CDC memdc;
	memdc.CreateCompatibleDC(&dc);

	CRect ClientRect;
	GetClientRect(ClientRect);

	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(&dc, ClientRect.Width(), ClientRect.Height());
	memdc.SelectObject(bitmap);

	dc.BitBlt(0, 0, ClientRect.Width(), ClientRect.Height(), &memdc, 0, 0, SRCCOPY);
	memdc.DeleteDC();
	//membm.DeleteObject();
	*/
}

void CManageToolMain::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	//__super::OnActivate(nState, pWndOther, bMinimized);
	SetProfileImage(str_loc);
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void CManageToolMain::OnBnClickedRadio1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 학생을 출석으로 변경할 경우
	this->MakeConn();
	int m_id = _ttoi(this->m_ID);
	SQLWCHAR* query = (SQLWCHAR*)TEXT("update member set m_attendance = 0 where m_id = ?;");
	if ((retcode = SQLPrepare(hstmt1, /*보낼 SQL 문자열*/query, SQL_NTS)) != SQL_SUCCESS) {
		Errmsg.Format(_T("에러발생! 에러코드: %d"), retcode);
		AfxMessageBox(Errmsg);
	}
	else {
		if ((retcode = SQLBindParameter(hstmt1, 1, SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER, 0, 0, &m_id, 0, NULL)) != SQL_SUCCESS) {
			Errmsg.Format(_T("에러발생! 에러코드: %d"), retcode);
			AfxMessageBox(Errmsg);
		}
	}
	if (retcode == SQL_SUCCESS)
		retcode = SQLExecute(hstmt1);
}

void CManageToolMain::OnBnClickedRadio2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 학생을 지각으로 변경할 경우
	this->MakeConn();
	int m_id = _ttoi(this->m_ID);
	SQLWCHAR* query = (SQLWCHAR*)TEXT("update member set m_attendance = 1 where m_id = ?;");
	if ((retcode = SQLPrepare(hstmt1, /*보낼 SQL 문자열*/query, SQL_NTS)) != SQL_SUCCESS) {
		Errmsg.Format(_T("에러발생! 에러코드: %d"), retcode);
		AfxMessageBox(Errmsg);
	}
	else {
		if ((retcode = SQLBindParameter(hstmt1, 1, SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER, 0, 0, &m_id, 0, NULL)) != SQL_SUCCESS) {
			Errmsg.Format(_T("에러발생! 에러코드: %d"), retcode);
			AfxMessageBox(Errmsg);
		}
	}
	if (retcode == SQL_SUCCESS)
		retcode = SQLExecute(hstmt1);
}

void CManageToolMain::OnBnClickedRadio3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 학생을 결석으로 변경할 경우
	this->MakeConn();
	int m_id = _ttoi(this->m_ID);
	SQLWCHAR* query = (SQLWCHAR*)TEXT("update member set m_attendance = 2 where m_id = ?;");
	if ((retcode = SQLPrepare(hstmt1, /*보낼 SQL 문자열*/query, SQL_NTS)) != SQL_SUCCESS) {
		Errmsg.Format(_T("에러발생! 에러코드: %d"), retcode);
		AfxMessageBox(Errmsg);
	}
	else {
		if ((retcode = SQLBindParameter(hstmt1, 1, SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER, 0, 0, &m_id, 0, NULL)) != SQL_SUCCESS) {
			Errmsg.Format(_T("에러발생! 에러코드: %d"), retcode);
			AfxMessageBox(Errmsg);
		}
	}
	if (retcode == SQL_SUCCESS)
		retcode = SQLExecute(hstmt1);
}
