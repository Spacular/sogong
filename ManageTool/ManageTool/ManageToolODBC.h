#pragma once
#include <iostream>
#include <string.h>
#include <windows.h>
#include <sql.h>
#include <sqlext.h>

class CManageToolODBC
{
protected:
	SQLHENV		henv;		// �̺�Ʈ �ڵ鷯
	SQLHDBC		hdbc1;      // ���� �ڵ鷯
	SQLHSTMT	hstmt1;		// ���� ������� ����
	SQLRETURN	retcode;	// SQL�� ���� ���.

public:
	CManageToolODBC();
	~CManageToolODBC();

protected:
	// ���� �Լ� �������Դϴ�.
	virtual void MakeConn() = 0;		// ����Ŭ�������� ������ �����ϴ� �뵵�� ����� �Լ�.
};
