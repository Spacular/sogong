
// MFCApplication1View.cpp : CMFCApplication1View Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "MFCApplication1.h"
#endif

#include "MFCApplication1Set.h"
#include "MFCApplication1Doc.h"
#include "MFCApplication1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication1View

IMPLEMENT_DYNCREATE(CMFCApplication1View, CRecordView)

BEGIN_MESSAGE_MAP(CMFCApplication1View, CRecordView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CRecordView::OnFilePrintPreview)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CMFCApplication1View ����/�Ҹ�

CMFCApplication1View::CMFCApplication1View()
	: CRecordView(CMFCApplication1View::IDD)
{
	m_pSet = NULL;
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	m_point = CPoint(0, 0);
	m_lbdown = CPoint(0, 0);
	m_Oldlbdown = CPoint(0, 0);
}

CMFCApplication1View::~CMFCApplication1View()
{
}

void CMFCApplication1View::DoDataExchange(CDataExchange* pDX)
{
	CRecordView::DoDataExchange(pDX);
	// ��Ʈ���� �����ͺ��̽� �ʵ忡 '����'�ϱ� ���� ���⿡ DDX_Field* �Լ��� ������ �� �ֽ��ϴ�. ��:
	// DDX_FieldText(pDX, IDC_MYEDITBOX, m_pSet->m_szColumn1, m_pSet);
	// DDX_FieldCheck(pDX, IDC_MYCHECKBOX, m_pSet->m_bColumn2, m_pSet);
	// �ڼ��� ������ MSDN �� ODBC ������ �����Ͻʽÿ�.
}

BOOL CMFCApplication1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CRecordView::PreCreateWindow(cs);
}

void CMFCApplication1View::OnInitialUpdate()
{
	m_pSet = &GetDocument()->m_MFCApplication1Set;
	CRecordView::OnInitialUpdate();

}


// CMFCApplication1View �μ�

BOOL CMFCApplication1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CMFCApplication1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CMFCApplication1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CMFCApplication1View ����

#ifdef _DEBUG
void CMFCApplication1View::AssertValid() const
{
	CRecordView::AssertValid();
}

void CMFCApplication1View::Dump(CDumpContext& dc) const
{
	CRecordView::Dump(dc);
}

CMFCApplication1Doc* CMFCApplication1View::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication1Doc)));
	return (CMFCApplication1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication1View �����ͺ��̽� ����
CRecordset* CMFCApplication1View::OnGetRecordset()
{
	return m_pSet;
}



// CMFCApplication1View �޽��� ó����


void CMFCApplication1View::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� CRecordView::OnPaint()��(��) ȣ������ ���ʽÿ�.

	/*
	POINT initpoint;	initpoint.x = 0;	initpoint.y = 0;	// ����ǥ �ʱ�ȭ�� ���� POINT���� ����.
	POINT ptMoving = initpoint;		// �����̰� �ִ� ��ġ(��, Point)�� ��Ÿ��.

	int nRows = 10;	// ��(Row)�� ��(Number).
	int nCols = 10; 	// ��(Column)�� ��.
	int RowInterval = 30;	// �� ���� ����.
	int ColInterval = RowInterval*1.78;	// �� ���� ����.	16:9 == 1.78 ����.

	for (int i = 0; i < nRows; i++){
		for (int j = 0; j < nCols; j++){
			dc.MoveTo(ptMoving.x, ptMoving.y);	//dc.MoveTo(int x, int y) => ������ǥ �����ϴ� �Լ�.
			dc.LineTo(ptMoving.x + ColInterval, ptMoving.y);	// dc.Lineto(int x, int y) => �� ��ǥ���� ������ �� �׾��ִ� �Լ�.
		//	dc.MoveTo(ptMoving.x + ColInterval, ptMoving.y);
			dc.LineTo(ptMoving.x + ColInterval, ptMoving.y + RowInterval);
		//	dc.MoveTo(ptMoving.x + ColInterval, ptMoving.y + RowInterval);
			dc.LineTo(ptMoving.x, ptMoving.y + RowInterval);
		//	dc.MoveTo(ptMoving.x, ptMoving.y + RowInterval);
			dc.LineTo(ptMoving.x, ptMoving.y);
			ptMoving.x += ColInterval;
		}
		ptMoving.x = initpoint.x;
		ptMoving.y += RowInterval;
	}
	*/
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
		BOOL result;
		for (int i = 0; i < nRows; i++){
			for (int j = 0; j < nCols; j++){
				result = desk[i][j].PtInRect(m_lbdown);
				if (result)	{
					Selected_Seat.x = i;	Selected_Seat.y = j;
					//strData.Format(_T("%02d��, %02d���Դϴ�."), Selected_Seat.x + 1, Selected_Seat.y + 1);
					strData.Format(_T("%3d�� �¼��Դϴ�."), Selected_Seat.x * 10 + Selected_Seat.y + 1);
					dc.TextOut(10, 10, strData);
				}
			}
		}
		m_Oldlbdown = m_lbdown;
	}

}


void CMFCApplication1View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	m_point = point;
	//RedrawWindow();		//OnPaint()�Լ��� ����� ���� ��������!
	CRecordView::OnMouseMove(nFlags, point);
}


void CMFCApplication1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	CPaintDC dc(this);
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	m_lbdown = point;
	RedrawWindow();
	CRecordView::OnLButtonDown(nFlags, point);
}
