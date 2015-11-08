
// MFCApplication1Set.cpp : CMFCApplication1Set 클래스의 구현
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Set.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication1Set 구현

// 코드 생성 위치 2015년 11월 8일 일요일, 오전 2:08

IMPLEMENT_DYNAMIC(CMFCApplication1Set, CRecordset)

CMFCApplication1Set::CMFCApplication1Set(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_m_id = 0;
	m_m_pw = "";
	m_m_name = "";
	m_m_department = "";
	m_m_gen = "";
	m_m_birthdate;
	m_m_picture;
	m_m_admin = 0;
	m_m_warning = 0;
	m_nFields = 9;
	m_nDefaultType = snapshot;
}
//#error 보안 문제: 연결 문자열에 암호가 포함되어 있을 수 있습니다.
// 아래 연결 문자열에 일반 텍스트 암호 및/또는 
// 다른 중요한 정보가 포함되어 있을 수 있습니다.
// 보안 관련 문제가 있는지 연결 문자열을 검토한 후에 #error을(를) 제거하십시오.
// 다른 형식으로 암호를 저장하거나 다른 사용자 인증을 사용하십시오.
CString CMFCApplication1Set::GetDefaultConnect()
{
	return _T("DSN=member;DESCRIPTION={\xc0ac\xc6a9\xc790 \xb370\xc774\xd130\xbca0\xc774\xc2a4};SERVER=localhost;UID=root;PWD=542133tlatms;DATABASE=member;PORT=3306");
}

CString CMFCApplication1Set::GetDefaultSQL()
{
	return _T("[member]");
}

void CMFCApplication1Set::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 및 RFX_Int() 같은 매크로는 데이터베이스의 필드
// 형식이 아니라 멤버 변수의 형식에 따라 달라집니다.
// ODBC에서는 자동으로 열 값을 요청된 형식으로 변환하려고 합니다
	RFX_Long(pFX, _T("[m_id]"), m_m_id);
	RFX_Text(pFX, _T("[m_pw]"), m_m_pw);
	RFX_Text(pFX, _T("[m_name]"), m_m_name);
	RFX_Text(pFX, _T("[m_department]"), m_m_department);
	RFX_Text(pFX, _T("[m_gen]"), m_m_gen);
	RFX_Date(pFX, _T("[m_birthdate]"), m_m_birthdate);
	RFX_LongBinary(pFX, _T("[m_picture]"), m_m_picture);
	RFX_Long(pFX, _T("[m_admin]"), m_m_admin);
	RFX_Long(pFX, _T("[m_warning]"), m_m_warning);

}
/////////////////////////////////////////////////////////////////////////////
// CMFCApplication1Set 진단

#ifdef _DEBUG
void CMFCApplication1Set::AssertValid() const
{
	CRecordset::AssertValid();
}

void CMFCApplication1Set::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

