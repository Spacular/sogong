// ManageToolMain.cpp : ���� �����Դϴ�.

#include "stdafx.h"
#include "ManageTool.h"
#include "ManageToolMain.h"
#include "afxdialogex.h"
using namespace std;

// CManageToolMain ��ȭ �����Դϴ�.

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

// CManageToolMain �޽��� ó�����Դϴ�.

void CManageToolMain::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� CDialogEx::OnPaint()��(��) ȣ������ ���ʽÿ�.
	
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

	for (int i = 0; i < nRows; i++){
		for (int j = 0; j < nCols; j++){
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

	if (m_lbdown != m_Oldlbdown){
		BOOL result = 0;
		CString num, birth;

		num.Format(_T(""));	birth.Format(_T(""));				// �ʱ�ȭ!
		
		StuInfo info;

		info.m_birthdate.day = NULL;	info.m_birthdate.day = NULL; info.m_birthdate.day = NULL;	info.m_id = NULL;
		strcpy_s(info.m_department, "");	strcpy_s(info.m_gen, "");	strcpy_s(info.m_name, "");

		for (int i = 0; i < nRows; i++){
			for (int j = 0; j < nCols; j++){
				result = desk[i][j].PtInRect(m_lbdown);
				if (result)	{
					Selected_Seat.x = i;	Selected_Seat.y = j;
					int Loc = Selected_Seat.x * 10 + Selected_Seat.y + 1;
					// trData.Format(_T("%02d��, %02d���Դϴ�."), Selected_Seat.x + 1, Selected_Seat.y + 1);
					// trData.Format(_T("%3d�� �¼��Դϴ�."), Selected_Seat.x * 10 + Selected_Seat.y + 1);
					// dc.TextOut(10, 10, strData);

					this->MakeConn();				// �� Ŭ������ ���� ȹ��!
					info = WhoIs(Loc);

					//CString strImagePath;
					//strImagePath.Format(_T("%s"), filename);
					
					string  strImagePath;
					strImagePath = filename;

					/**********************************************************************************************************/
					/*																	��													��										 	     */														
					/* Picture Control�� �ѷ��ֱ� ���� CImage�� ����ؾ� �ϸ� �̰��� �Ű������� CString Ÿ���̴�!! �ݵ�� ����!!!   */
					/**********************************************************************************************************/
					
					m_name = info.m_name;

					num.Format(_T("%d"), info.m_id);
					m_ID = num;

					m_dept = info.m_department;

					birth.Format(_T("%d - %d - %d"), info.m_birthdate.year, info.m_birthdate.month, info.m_birthdate.day);
					m_birth = birth;

					UpdateData(false);		// �� ����!
				}
			}
		}
		m_Oldlbdown = m_lbdown;
	}
}


void CManageToolMain::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CDialogEx::OnLButtonDown(nFlags, point);
	m_lbdown = point;
	RedrawWindow();
}


void CManageToolMain::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	m_point = point;
}


void CManageToolMain::MakeConn(){

	if ((retcode = SQLAllocEnv(&henv)) != SQL_SUCCESS){
		Errmsg.Format(_T("�����߻�! �����ڵ�: %d"), retcode);		// ���� ������ �����Ѵ�.
		AfxMessageBox(Errmsg);								// �޼��� �ڽ��� ���� ������ ������ ����Ѵ�.
	}
	if ((retcode = SQLAllocConnect(henv, &hdbc1)) != SQL_SUCCESS){
		Errmsg.Format(_T("�����߻�! �����ڵ�: %d"), retcode);
		AfxMessageBox(Errmsg);
	}
		
	if ((retcode = SQLConnect(hdbc1, (SQLWCHAR *)TEXT("manage"/*DSN�̸�*/), SQL_NTS/*NULL���� ���*/, (SQLWCHAR *)TEXT("root"/*���Ӱ���*/), SQL_NTS, (SQLWCHAR *)TEXT("542133tlatms"/*��й�ȣ*/), SQL_NTS)) != SQL_SUCCESS){
		Errmsg.Format(_T("�����߻�! �����ڵ�: %d"), retcode);
		AfxMessageBox(Errmsg);
	}
		
	SQLAllocStmt(hdbc1, &hstmt1);		// ���� ���� Handle ȹ��
}


StuInfo CManageToolMain::WhoIs(int Loc){
	StuInfo stuinfo;										// ����ü �ʱ�ȭ

	stuinfo.m_birthdate.day = 0;
	stuinfo.m_birthdate.month = 0;
	stuinfo.m_birthdate.year = 0;
	stuinfo.m_id = 0;
	strcpy_s(stuinfo.m_department, sizeof("��������"), "��������");
	strcpy_s(stuinfo.m_gen, sizeof("��������"), "��������");
	strcpy_s(stuinfo.m_name, sizeof("��������"), "��������");
	/* �ʱ�ȭ�� �Լ��� ���ؼ� �������� ���� ����� �ǳ�...*/


	int save0, save1, save2, save3, save4, save5, save6, pos, Pic_size = 0;

	pos = Loc - 1;

	SQLWCHAR* pic_size_query = (SQLWCHAR*)TEXT("select octet_length(m_picture) from member as m inner join seat as s on m.m_id = s.m_id and s_location = ?;");
	SQLWCHAR* query = (SQLWCHAR*)TEXT("select m.m_id, m_name, m_department, m_gen, m_birthdate, m_picture from member as m inner join seat as s on m.m_id = s.m_id and s_location = ?;");

	/********** BLOC data ũ�� �˾Ƴ��� �κ�	********/
	if ((retcode = SQLPrepare(hstmt1, /*���� SQL ���ڿ�*/pic_size_query, SQL_NTS)) != SQL_SUCCESS){
		Errmsg.Format(_T("�����߻�! �����ڵ�: %d"), retcode);
		AfxMessageBox(Errmsg);
	}
	else{
		if ((retcode = SQLBindParameter(hstmt1, 1, SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER, 0, 0, &pos, 0, NULL)) != SQL_SUCCESS){
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

	if (Pic_size == 0)	{
		Errmsg.Format(_T("�����߻�! �����ڵ�: %d"), -999);
		AfxMessageBox(Errmsg);
		AfxMessageBox(_T("������ �������� �ʽ��ϴ�! "));
		//CManageToolMain::OnClose();
		//OnDestroy();
		//::SendMessage(this->m_hWnd, WM_CLOSE, NULL, NULL);
	}
	char *m_picture = (char*)calloc(Pic_size, sizeof(char));
	// �˾Ƴ� ũ���� ����!

	if ((retcode = SQLPrepare(hstmt1, query/*���� SQL ���ڿ�*/, SQL_NTS)) != SQL_SUCCESS){
		Errmsg.Format(_T("�����߻�! �����ڵ�: %d"), retcode);
		AfxMessageBox(Errmsg);
	}
	else{
		if ((retcode = SQLBindParameter(hstmt1, 1, SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER, 0, 0, &pos, 0, NULL)) != SQL_SUCCESS){
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
	}
	while (SQLFetch(hstmt1) == SQL_SUCCESS);

	if (Pic_size != 0){
		strcpy_s(filename, "pic_");
		ofstream output;
		char num[8];
		sprintf_s(num, sizeof(num), "%03d.jpg", pos);
		strcpy_s(filename + 3, sizeof(num), num);

		output.open(filename, ios::binary);					// 'pic_�¼���ȣ' �� �������� ����

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
BLOB ������ ũ�� �˾Ƴ���(Mysql)

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