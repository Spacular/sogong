#pragma once
#include "ManageToolODBC.h"
class CManageToolLogin : public CManageToolODBC
{
private:
	CString Errmsg = _T("");								// ���� �޼����� ���� ���ڿ���.
	CString result = _T("");								// ��� �޼����� ���� ���ڿ���.

public:
	CManageToolLogin();
	~CManageToolLogin();

public:
	void MakeConn();
	int isExist(CString ID, CString Pwd);		// ID�� Password�� �����ϴ��� Ȯ���ϴ� �뵵. �ٸ� ���� ���������� Ȯ���� �� �ִ� ����̶�� ����Ŭ������ �����Լ���!
};

