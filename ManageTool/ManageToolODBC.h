#pragma once
#include <iostream>
#include <string.h>
#include <windows.h>
#include <sql.h>
#include <sqlext.h>

class CManageToolODBC
{
public:
	SQLHENV		henv;		// 이벤트 핸들러
	SQLHDBC		hdbc1;      // 접속 핸들러
	SQLHSTMT	hstmt1;		// 접속 결과저장 변수
	SQLRETURN	retcode;	// SQL문 수행 결과.

public:
	CManageToolODBC();
	~CManageToolODBC();
	
public:
	// 가상 함수 구현부입니다.
	virtual void MakeConn() = 0;		// 하위클래스에서 연결을 정의하는 용도로 사용할 함수.
};

