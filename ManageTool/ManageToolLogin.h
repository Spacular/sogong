#pragma once
#include "ManageToolODBC.h"
#include <iostream>
#include <string.h>
#include <windows.h>
#include <sql.h>
#include <sqlext.h>

class CManageToolLogin : public CManageToolODBC
{
public:
	CString Errmsg = _T("");								// ���� �޼����� ���� ���ڿ���.
	CString result = _T("");								// ��� �޼����� ���� ���ڿ���.

public:
	CManageToolLogin();
	~CManageToolLogin();

public:
	void CManageToolLogin::MakeConn();
	int isExist(CString ID, CString Pwd);		// ID�� Password�� �����ϴ��� Ȯ���ϴ� �뵵. �ٸ� ���� ������������ Ȯ���� �� �ִ� ����̶�� ����Ŭ������ �����Լ���!
};

