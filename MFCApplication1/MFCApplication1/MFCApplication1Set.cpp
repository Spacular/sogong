
// MFCApplication1Set.cpp : CMFCApplication1Set Ŭ������ ����
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Set.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication1Set ����

// �ڵ� ���� ��ġ 2015�� 11�� 8�� �Ͽ���, ���� 2:08

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
//#error ���� ����: ���� ���ڿ��� ��ȣ�� ���ԵǾ� ���� �� �ֽ��ϴ�.
// �Ʒ� ���� ���ڿ��� �Ϲ� �ؽ�Ʈ ��ȣ ��/�Ǵ� 
// �ٸ� �߿��� ������ ���ԵǾ� ���� �� �ֽ��ϴ�.
// ���� ���� ������ �ִ��� ���� ���ڿ��� ������ �Ŀ� #error��(��) �����Ͻʽÿ�.
// �ٸ� �������� ��ȣ�� �����ϰų� �ٸ� ����� ������ ����Ͻʽÿ�.
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
// RFX_Text() �� RFX_Int() ���� ��ũ�δ� �����ͺ��̽��� �ʵ�
// ������ �ƴ϶� ��� ������ ���Ŀ� ���� �޶����ϴ�.
// ODBC������ �ڵ����� �� ���� ��û�� �������� ��ȯ�Ϸ��� �մϴ�
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
// CMFCApplication1Set ����

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

