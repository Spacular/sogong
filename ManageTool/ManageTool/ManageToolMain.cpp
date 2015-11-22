#include "stdafx.h"
#include "ManageTool.h"
#include "ManageToolMain.h"
#include "afxdialogex.h"
#include "afxconv.h"
#include "UTF8Conv.h"
using namespace std;


// CManageToolMain ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CManageToolMain, CDialogEx)

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
	DDX_Text(pDX, IDC_EDIT6, m_qcontent);
	DDX_Control(pDX, IDC_PICTURE, m_profileImage);
}


BEGIN_MESSAGE_MAP(CManageToolMain, CDialogEx)
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
//	ON_WM_ERASEBKGND()
ON_WM_ACTIVATE()
END_MESSAGE_MAP()


// CManageToolMain �޽��� ó�����Դϴ�.


void CManageToolMain::MakeConn() {

	if ((retcode = SQLAllocEnv(&henv)) != SQL_SUCCESS) {
		Errmsg.Format(_T("�����߻�! �����ڵ�: %d"), retcode);		// ���� ������ �����Ѵ�.
		AfxMessageBox(Errmsg);								// �޼��� �ڽ��� ���� ������ ������ ����Ѵ�.
	}
	if ((retcode = SQLAllocConnect(henv, &hdbc1)) != SQL_SUCCESS) {
		Errmsg.Format(_T("�����߻�! �����ڵ�: %d"), retcode);
		AfxMessageBox(Errmsg);
	}

	if ((retcode = SQLConnect(hdbc1, (SQLWCHAR *)TEXT("member"/*DSN�̸�*/), SQL_NTS/*NULL���� ���*/, (SQLWCHAR *)TEXT("root"/*���Ӱ���*/), SQL_NTS, (SQLWCHAR *)TEXT("542133tlatms"/*��й�ȣ*/), SQL_NTS)) != SQL_SUCCESS) {
		Errmsg.Format(_T("�����߻�! �����ڵ�: %d"), retcode);
		AfxMessageBox(Errmsg);
	}

	SQLAllocStmt(hdbc1, &hstmt1);		// ���� ���� Handle ȹ��
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
	if ((retcode = SQLPrepare(hstmt1, /*���� SQL ���ڿ�*/query, SQL_NTS)) != SQL_SUCCESS) {
		Errmsg.Format(_T("�����߻�! �����ڵ�: %d"), retcode);
		AfxMessageBox(Errmsg);
	}

	retcode = SQLExecute(hstmt1);

	if (retcode == SQL_SUCCESS)
	{
		count = 0;
		retcode = SQLBindCol(hstmt1, 1, SQL_C_SLONG, &(result + (count))->s_location, sizeof(result), (SQLINTEGER *)&save);	// ������� ù ��° Column�� ����.
		retcode = SQLBindCol(hstmt1, 2, SQL_C_SLONG, &(result + (count))->m_warning, sizeof(result), (SQLINTEGER *)&save);	// ������� �� ��° Column�� ����.
		retcode = SQLBindCol(hstmt1, 3, SQL_C_SLONG, &(result + (count))->m_question, sizeof(result), (SQLINTEGER *)&save);	// ������� �� ��° Column�� ����.
	}
	while (SQLFetch(hstmt1) == SQL_SUCCESS) {
		count++;
		retcode = SQLBindCol(hstmt1, 1, SQL_C_SLONG, &(result + (count))->s_location, sizeof(result), (SQLINTEGER *)&save);	// ������� ù ��° Column�� ����.
		retcode = SQLBindCol(hstmt1, 2, SQL_C_SLONG, &(result + (count))->m_warning, sizeof(result), (SQLINTEGER *)&save);	// ������� �� ��° Column�� ����.
		retcode = SQLBindCol(hstmt1, 3, SQL_C_SLONG, &(result + (count))->m_question, sizeof(result), (SQLINTEGER *)&save);	// ������� �� ��° Column�� ����.
	}

	SQLFreeStmt(hstmt1, SQL_DROP);
	SQLDisconnect(hdbc1);
	SQLFreeConnect(hdbc1);
	SQLFreeEnv(henv);
}

StuInfo CManageToolMain::WhoIs(int Loc) {
	StuInfo stuinfo;										// ����ü �ʱ�ȭ

	stuinfo.m_birthdate.day = 0;
	stuinfo.m_birthdate.month = 0;
	stuinfo.m_birthdate.year = 0;
	stuinfo.m_id = 0;
	strcpy_s(stuinfo.m_department, sizeof("��������"), "��������");
	strcpy_s(stuinfo.m_gen, sizeof("��������"), "��������");
	strcpy_s(stuinfo.m_name, sizeof("��������"), "��������");
	//_tcscpy_s(stuinfo.m_qcontent, _countof(stuinfo.m_qcontent), _T(""));	// TCHAR Ÿ�Կ� ���ڿ� �����ϴ� ��� 
	//_stprintf_s(szNewName, _countof(szNewName), _T("���� %s �Դϴ�."), szName);	 // TCHAR Ÿ�Կ� ���ڿ� ������ ����ϴ� ���.

	int save0, save1, save2, save3, save4, save5, save6, save7, pos, Pic_size = 0;

	pos = Loc - 1;

	SQLWCHAR* pic_size_query = (SQLWCHAR*)TEXT("select octet_length(m_picture) from member as m inner join seat as s on m.m_id = s.m_id and s_location = ?;");
	SQLWCHAR* query = (SQLWCHAR*)TEXT("select m.m_id, m_name, m_department, m_gen, m_birthdate, m_picture, m_qcontent from member as m inner join seat as s on m.m_id = s.m_id and s_location = ?;");

	/********** BLOC data ũ�� �˾Ƴ��� �κ�	********/
	if ((retcode = SQLPrepare(hstmt1, /*���� SQL ���ڿ�*/pic_size_query, SQL_NTS)) != SQL_SUCCESS) {
		Errmsg.Format(_T("�����߻�! �����ڵ�: %d"), retcode);
		AfxMessageBox(Errmsg);
	}
	else {
		if ((retcode = SQLBindParameter(hstmt1, 1, SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER, 0, 0, &pos, 0, NULL)) != SQL_SUCCESS) {
			Errmsg.Format(_T("�����߻�! �����ڵ�: %d"), retcode);
			AfxMessageBox(Errmsg);
		}
	}

	if (retcode == SQL_SUCCESS)
		retcode = SQLExecute(hstmt1);

	if (retcode == SQL_SUCCESS)
	{
		retcode = SQLBindCol(hstmt1, 1, SQL_C_SLONG, &Pic_size, sizeof(Pic_size), (SQLINTEGER *)&save0);	// ������� ù ��° Column�� ����.
	}
	while (SQLFetch(hstmt1) == SQL_SUCCESS);
	/********** BLOC data ũ�� �˾Ƴ��� �κ�	********/

	if (Pic_size == 0) {
		Errmsg.Format(_T("�����߻�! �����ڵ�: %d"), -999);
		AfxMessageBox(Errmsg);
		AfxMessageBox(_T("������ �������� �ʽ��ϴ�! "));
		//CManageToolMain::OnClose();
		//OnDestroy();
		//::SendMessage(this->m_hWnd, WM_CLOSE, NULL, NULL);
	}
	char *m_picture = (char*)calloc(Pic_size, sizeof(char));
	// �˾Ƴ� ũ���� ����!

	if ((retcode = SQLPrepare(hstmt1, query/*���� SQL ���ڿ�*/, SQL_NTS)) != SQL_SUCCESS) {
		Errmsg.Format(_T("�����߻�! �����ڵ�: %d"), retcode);
		AfxMessageBox(Errmsg);
	}
	else {
		if ((retcode = SQLBindParameter(hstmt1, 1, SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER, 0, 0, &pos, 0, NULL)) != SQL_SUCCESS) {
			Errmsg.Format(_T("�����߻�! �����ڵ�: %d"), retcode);
			AfxMessageBox(Errmsg);
		}
	}
	if (retcode == SQL_SUCCESS)
		retcode = SQLExecute(hstmt1);
	if (retcode == SQL_SUCCESS)
	{
		retcode = SQLBindCol(hstmt1, 1, SQL_C_SLONG, &stuinfo.m_id, sizeof(stuinfo.m_id), (SQLINTEGER *)&save1);	// ������� ù ��° Column�� ����.
		retcode = SQLBindCol(hstmt1, 2, SQL_C_CHAR, stuinfo.m_name, sizeof(stuinfo.m_name), (SQLINTEGER *)&save2);	// ������� �� ��° Column�� ����.
		retcode = SQLBindCol(hstmt1, 3, SQL_C_CHAR, stuinfo.m_department, sizeof(stuinfo.m_department), (SQLINTEGER *)&save3);	// ������� �� ��° Column�� ����.
		retcode = SQLBindCol(hstmt1, 4, SQL_C_CHAR, stuinfo.m_gen, sizeof(stuinfo.m_gen), (SQLINTEGER *)&save4);	// ������� �� ��° Column�� ����.
		retcode = SQLBindCol(hstmt1, 5, SQL_C_DATE, &stuinfo.m_birthdate, sizeof(stuinfo.m_birthdate) + 10, (SQLINTEGER *)&save5);	// ������� �ټ���° Column�� ����.
		if (Pic_size != 0)
			retcode = SQLBindCol(hstmt1, 6, SQL_C_BINARY, m_picture, Pic_size, (SQLINTEGER *)&save6);	// ������� ������° Column�� ����.
		retcode = SQLBindCol(hstmt1, 7, SQL_CHAR, stuinfo.m_qcontent, sizeof(stuinfo.m_qcontent), (SQLINTEGER *)&save7);	// ������� �ϰ���° Column�� ����.
	}
	while (SQLFetch(hstmt1) == SQL_SUCCESS);

	if (Pic_size != 0) {
		CreateDirectory(_T("pic"), NULL);					// ������ ���� �����.
		strcpy_s(filename, "pic/pic_");
		ofstream output;
		char num[8];
		sprintf_s(num, sizeof(num), "%03d.jpg", pos + 1);
		strcpy_s(filename + 8, sizeof(num), num);

		output.open(filename, ios::binary);					// 'pic_�¼���ȣ' �� �������� ����

		for (int i = 0; i < Pic_size; i++)
			output << m_picture[i];

		free(m_picture);                         // ��� �̹��� �����͸� ���ſϷ� �����Ƿ�, �����Ҵ� ����.
	}
	
	if (strcmp(stuinfo.m_qcontent, "") == 0)
	{
		strcpy_s(stuinfo.m_qcontent, sizeof("��������"), "��������");
	}		

	SQLFreeStmt(hstmt1, SQL_DROP);
	SQLDisconnect(hdbc1);
	SQLFreeConnect(hdbc1);
	SQLFreeEnv(henv);

	return stuinfo;
}

void CManageToolMain::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
					   // �׸��� �޽����� ���ؼ��� __super::OnPaint()��(��) ȣ������ ���ʽÿ�.

	CPen newPen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen *pOldPen = dc.SelectObject(&newPen);	//�� ��ü�� ���� ������ ����.(���� ������ �ǵ��� �� �� �ʿ�.)

	int Init_x = 30;
	int Init_y = 30;
	int Pos_x = Init_x;
	int Pos_y = Init_y;
	int Interval_y = 30;
	int Interval_x = (int)(Interval_y * 1.78);
	int nRows = 10;		// ��(Row)�� ��(Number).
	int nCols = 10;		// ��(Column)�� ��.
	

	POINT Selected_Seat;		// ���콺�� ������ �¼��� ��ǥ

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
		SetTimer(1, 3000, NULL);		// 10�ʿ� �� �� �÷� Ȯ��!
	}

	for (int i = 0; i < nRows; i++) {
		for (int j = 0; j < nCols; j++) {
			dc.Rectangle(Pos_x, Pos_y, Pos_x + Interval_x, Pos_y + Interval_y);		//�� ����� ���� ǥ�ô� �ȴ�.
			desk[i][j] = CRect(Pos_x, Pos_y, Pos_x + Interval_x, Pos_y + Interval_y);	// �̷��� �ϴϱ� ȭ�鿡 ǥ�õ����� �ʴ´�,
																						// dc.FillSolidRect(&desk, RGB(0, 0, 0));	�簢�� ���� ä��� �Լ�.
																						// �׷��� ���� CRect�� ����� ǥ�õ��� �ʴ��� �ϴ� ����.
			classroom[i][j].CreateEllipticRgnIndirect(desk[i][j]);		// �� �Լ����� CRect ��ü�� �ʿ��ϴ�!
			Pos_x += Interval_x;
		}
		Pos_x = Init_x;
		Pos_y += Interval_y;
	}
	
	for (int i = 0; i < count; i++) {
		int row = result[i].s_location / 10;
		int column = result[i].s_location % 10;
		if(result[i].m_warning == 1)
		{
			// �ǽ��л��� ����������
			dc.FillSolidRect(&desk[row][column], RGB(255, 0, 0));
		}
		else if (result[i].m_question == 1)
		{
			// ���� �ִ� �л��� ���������
			dc.FillSolidRect(&desk[row][column], RGB(255, 255, 0));
		}
		else
		{
			// �� ���� �Ϲ� �⼮�� ����������
			dc.FillSolidRect(&desk[row][column], RGB(0, 0, 0));
		}
	}
	
	if (m_lbdown != m_Oldlbdown) {
		BOOL result = 0;
		CString num, birth;

		num.Format(_T(""));	birth.Format(_T(""));				// �ʱ�ȭ!

		StuInfo info;
		

		info.m_birthdate.day = NULL;	info.m_birthdate.day = NULL; info.m_birthdate.day = NULL;	info.m_id = NULL;
		strcpy_s(info.m_department, "");	strcpy_s(info.m_gen, "");	strcpy_s(info.m_name, "");	m_qcontent = "";
		for (int i = 0; i < nRows; i++) {
			for (int j = 0; j < nCols; j++) {
				result = desk[i][j].PtInRect(m_lbdown);
				if (result) {
					Selected_Seat.x = i;	Selected_Seat.y = j;
					int Loc = Selected_Seat.x * 10 + Selected_Seat.y + 1;
					// trData.Format(_T("%02d��, %02d���Դϴ�."), Selected_Seat.x + 1, Selected_Seat.y + 1);
					// trData.Format(_T("%3d�� �¼��Դϴ�."), Selected_Seat.x * 10 + Selected_Seat.y + 1);
					// dc.TextOut(10, 10, strData);

					this->MakeConn();				// �� Ŭ������ ���� ȹ��!
					info = WhoIs(Loc);
					isFirst = FALSE;				// �ٽ� �ѹ� �¼� ��Ȳ ��ĵ�ϵ���

					m_name = info.m_name;

					num.Format(_T("%d"), info.m_id);
					m_ID = num;

					m_dept = info.m_department;

					birth.Format(_T("%d - %d - %d"), info.m_birthdate.year, info.m_birthdate.month, info.m_birthdate.day);
					m_birth = birth;
					
					if (strcmp(info.m_gen, "m") == 0)
					{
						TCHAR *man = L"����";
						// ������ ���
						m_gen.Format(_T("%s"), man);
					}
					else if (strcmp(info.m_gen, "f") == 0)
					{
						TCHAR *woman = L"����";
						// ������ ���
						m_gen.Format(_T("%s"), woman);
					}

					m_qcontent = info.m_qcontent;

					str_loc.Format(_T("%03d"), Loc);
					SetProfileImage(str_loc);

					m_radio = info.m_attendance;
					
					UpdateData(false);		// �� ����!
				}
			}
		}
		m_Oldlbdown = m_lbdown;
	}
}


void CManageToolMain::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	m_point = point;
}


void CManageToolMain::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	m_lbdown = point;
	RedrawWindow();
}

BOOL CManageToolMain::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)   // ���ͳ� ESC ���� ����
		return TRUE;

	return __super::PreTranslateMessage(pMsg);
}


void CManageToolMain::SetProfileImage(CString str)
{
	CDC *dc = m_profileImage.GetWindowDC();
	CImage m_jpg;   // jpg�̹���
	CString strImagePath = _T("pic/pic_") + str + _T(".jpg");
	dc->SetStretchBltMode(COLORONCOLOR);

	HRESULT hResult = m_jpg.Load(strImagePath);

	if (!FAILED(hResult))
	{
		CRect rect;
		m_profileImage.GetClientRect(rect);	
		// m_jpg.BitBlt(dc->m_hDC, 0, 0);
		m_jpg.StretchBlt(dc->m_hDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY); // ������Ʈ�� ũ�⿡ �°� �̹��� ũ�� ����
	}
	m_profileImage.ReleaseDC(dc);
}

void CManageToolMain::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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


//BOOL CManageToolMain::OnEraseBkgnd(CDC* pDC)
//{
//	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
//	return __super::OnEraseBkgnd(NULL);
//	/*
//	CRect rect;
//	GetClientRect(&rect);
//	COLORREF color = GetSysColor(COLOR_3DFACE);
//	pDC->FillSolidRect(&rect, color);
//	*/
//}


void CManageToolMain::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	//__super::OnActivate(nState, pWndOther, bMinimized);
	SetProfileImage(str_loc);
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}
