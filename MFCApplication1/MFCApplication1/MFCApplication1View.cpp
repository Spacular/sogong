
// MFCApplication1View.cpp : CMFCApplication1View 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CRecordView::OnFilePrintPreview)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CMFCApplication1View 생성/소멸

CMFCApplication1View::CMFCApplication1View()
	: CRecordView(CMFCApplication1View::IDD)
{
	m_pSet = NULL;
	// TODO: 여기에 생성 코드를 추가합니다.
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
	// 컨트롤을 데이터베이스 필드에 '연결'하기 위해 여기에 DDX_Field* 함수를 삽입할 수 있습니다. 예:
	// DDX_FieldText(pDX, IDC_MYEDITBOX, m_pSet->m_szColumn1, m_pSet);
	// DDX_FieldCheck(pDX, IDC_MYCHECKBOX, m_pSet->m_bColumn2, m_pSet);
	// 자세한 내용은 MSDN 및 ODBC 샘플을 참조하십시오.
}

BOOL CMFCApplication1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CRecordView::PreCreateWindow(cs);
}

void CMFCApplication1View::OnInitialUpdate()
{
	m_pSet = &GetDocument()->m_MFCApplication1Set;
	CRecordView::OnInitialUpdate();

}


// CMFCApplication1View 인쇄

BOOL CMFCApplication1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFCApplication1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFCApplication1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMFCApplication1View 진단

#ifdef _DEBUG
void CMFCApplication1View::AssertValid() const
{
	CRecordView::AssertValid();
}

void CMFCApplication1View::Dump(CDumpContext& dc) const
{
	CRecordView::Dump(dc);
}

CMFCApplication1Doc* CMFCApplication1View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication1Doc)));
	return (CMFCApplication1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication1View 데이터베이스 지원
CRecordset* CMFCApplication1View::OnGetRecordset()
{
	return m_pSet;
}



// CMFCApplication1View 메시지 처리기


void CMFCApplication1View::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CRecordView::OnPaint()을(를) 호출하지 마십시오.

	/*
	POINT initpoint;	initpoint.x = 0;	initpoint.y = 0;	// 점좌표 초기화를 위한 POINT변수 선언.
	POINT ptMoving = initpoint;		// 움직이고 있는 위치(점, Point)를 나타냄.

	int nRows = 10;	// 행(Row)의 수(Number).
	int nCols = 10; 	// 열(Column)의 수.
	int RowInterval = 30;	// 행 간의 간격.
	int ColInterval = RowInterval*1.78;	// 열 간의 간격.	16:9 == 1.78 비율.

	for (int i = 0; i < nRows; i++){
		for (int j = 0; j < nCols; j++){
			dc.MoveTo(ptMoving.x, ptMoving.y);	//dc.MoveTo(int x, int y) => 시작좌표 설정하는 함수.
			dc.LineTo(ptMoving.x + ColInterval, ptMoving.y);	// dc.Lineto(int x, int y) => 끝 좌표까지 직선을 쭉 그어주는 함수.
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
		BOOL result;
		for (int i = 0; i < nRows; i++){
			for (int j = 0; j < nCols; j++){
				result = desk[i][j].PtInRect(m_lbdown);
				if (result)	{
					Selected_Seat.x = i;	Selected_Seat.y = j;
					//strData.Format(_T("%02d행, %02d열입니다."), Selected_Seat.x + 1, Selected_Seat.y + 1);
					strData.Format(_T("%3d번 좌석입니다."), Selected_Seat.x * 10 + Selected_Seat.y + 1);
					dc.TextOut(10, 10, strData);
				}
			}
		}
		m_Oldlbdown = m_lbdown;
	}

}


void CMFCApplication1View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_point = point;
	//RedrawWindow();		//OnPaint()함수를 사용할 일이 있을때만!
	CRecordView::OnMouseMove(nFlags, point);
}


void CMFCApplication1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	CPaintDC dc(this);
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_lbdown = point;
	RedrawWindow();
	CRecordView::OnLButtonDown(nFlags, point);
}
