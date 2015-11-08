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
	CString Errmsg = _T("");								// 에러 메세지를 담을 문자열임.
	CString result = _T("");								// 결과 메세지를 담을 문자열임.

public:
	CManageToolLogin();
	~CManageToolLogin();

public:
	void CManageToolLogin::MakeConn();
	BOOL isExist(CString ID, CString Pwd);		// ID와 Password가 존재하는지 확인하는 용도. 다른 곳에 공통적으로 확인할 수 있는 기능이라면 상위클래스의 가상함수로!
};

