#include "stdafx.h"
#include "ManageToolLogin.h"
using namespace std;


CManageToolLogin::CManageToolLogin()
{
}


CManageToolLogin::~CManageToolLogin()
{
}

void CManageToolLogin::MakeConn() {
	Errmsg.Format(_T("에러발생! 에러코드: %d"), retcode);		// 에러 형식을 정의한다.

	if ((retcode = SQLAllocEnv(&henv)) != SQL_SUCCESS)
		AfxMessageBox(Errmsg);								// 메세지 박스를 띄우고 정해진 내용을 출력한다.
	if ((retcode = SQLAllocConnect(henv, &hdbc1)) != SQL_SUCCESS)
		AfxMessageBox(Errmsg);
	if ((retcode = SQLConnect(hdbc1, (SQLWCHAR *)TEXT("member"/*DSN이름*/), SQL_NTS/*NULL문자 대신*/, (SQLWCHAR *)TEXT("root"/*접속계정*/), SQL_NTS, (SQLWCHAR *)TEXT("542133tlatms"/*비밀번호*/), SQL_NTS)) != SQL_SUCCESS)
		AfxMessageBox(Errmsg);

	SQLAllocStmt(hdbc1, &hstmt1);		// 실제 문장 Handle 획득
}

int CManageToolLogin::isExist(CString ID, CString Pwd) {
	int ID_result = 0, i = 0, user_i;
	SQLINTEGER save, save2 = 0;
	BOOL isExistID = 0, isExistPwd = 0, isAdmin = 0;

	int strLen = Pwd.GetLength();		// CString 타입 변수의 문자열 길이 알아내기

										//char pwd[20];
	char* pwd = (char*)calloc(strLen, sizeof(char));		// 동적할당 해주기 *주의* 아래에 주소 넣을떄 pwd다! &pwd 아니다!!!
															//char* pwd = new char[strLen];
	char PWD_result[20];
	int user[100];

	SQLWCHAR* admin_query = (SQLWCHAR*)TEXT("select m_id from member where m_admin = 1;");

	SQLWCHAR* id_query = (SQLWCHAR*)TEXT("select m_id from member where m_id = ?;");
	int id = _wtoi(ID);

	SQLWCHAR* pwd_query = (SQLWCHAR*)TEXT("select m_pw from member where m_pw = ?;");
	//int pwd = _wtoi(Pwd);

	//pwd = CStringA(Pwd);			// Unicode 문자셋에서 string 타입으로 변환해주는 함수.
	//int passwd = atoi(pwd.c_str());

	WideCharToMultiByte(CP_ACP, 0, Pwd, -1, pwd, strLen + 1, NULL, NULL);

	SQLINTEGER ret = SQL_NTS;


	/********* 여기서부터가 관리자 여부 조회 과정임 *********/
	if ((retcode = SQLPrepare(hstmt1, admin_query/*보낼 SQL 문자열*/, SQL_NTS)) != SQL_SUCCESS)
		AfxMessageBox(Errmsg);
	if (retcode == SQL_SUCCESS)
	{
		retcode = SQLBindCol(hstmt1, 1, SQL_C_SLONG, &user_i, sizeof(user_i), &save);	// 결과물의 첫 Column을 저장.
	}
	SQLExecute(hstmt1);
	while ((retcode = SQLFetch(hstmt1)) == SQL_SUCCESS) {
		user[i++] = user_i;
	}

	for (i = 0; i < sizeof(user)/sizeof(int); i++) {
		if (id == user[i])
			isAdmin = TRUE;
	}
	/********* 여기서까지가 관리자 여부 조회 과정임 *********/


	/********* 여기서부터가 비밀번호 조회 과정임 *********/
	if ((retcode = SQLPrepare(hstmt1, pwd_query/*보낼 SQL 문자열*/, SQL_NTS)) != SQL_SUCCESS)
		AfxMessageBox(Errmsg);
	else {
		if ((retcode = SQLBindParameter(hstmt1, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, sizeof(pwd), 0, pwd, 0, &ret)) != SQL_SUCCESS)
		{
			AfxMessageBox(Errmsg);
		}
	}
	if (retcode == SQL_SUCCESS)
	{
		retcode = SQLBindCol(hstmt1, 1, SQL_C_CHAR, PWD_result, sizeof(PWD_result), &save2);	// 결과물의 첫 Column을 저장.
	}

	SQLExecute(hstmt1);
	while ((retcode = SQLFetch(hstmt1)) == SQL_SUCCESS)
	{
		isExistPwd = TRUE;
	}
	/********* 여기서까지가 비밀번호 조회 과정임 *********/

	/********* 학번 및 교번 조회 과정!! *********/
	if ((retcode = SQLPrepare(hstmt1, id_query/*보낼 SQL 문자열*/, SQL_NTS)) != SQL_SUCCESS)
		AfxMessageBox(Errmsg);
	else {
		if ((retcode = SQLBindParameter(hstmt1, 1, SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER, 0, 0, &id, 0, NULL)) != SQL_SUCCESS)
		{
			AfxMessageBox(Errmsg);
		}
	}
	if (retcode == SQL_SUCCESS)
	{
		retcode = SQLBindCol(hstmt1, 1, SQL_C_SLONG, &ID_result, sizeof(ID_result), &save);	// 결과물의 첫 Column을 저장.
	}

	SQLExecute(hstmt1);
	while (SQLFetch(hstmt1) == SQL_SUCCESS)
	{
		isExistID = TRUE;
	}
	/********* 여기까지가 학번 및 교번 조회 과정이었음 *********/

	SQLFreeStmt(hstmt1, SQL_DROP);
	SQLDisconnect(hdbc1);
	SQLFreeConnect(hdbc1);
	SQLFreeEnv(henv);

	if ((isExistID == TRUE) && (isExistPwd == TRUE) && (isAdmin == TRUE)) {
		return TRUE;				// 일치하는 계정 찾음!
	}
	else if ((isExistID == TRUE) && (isExistPwd == TRUE) && (isAdmin != TRUE)) {
		return 0;					// 관리자 계정이 아님!
	}
	else {
		return -1;					// 계정 자체가 없음!
	}
}

/**********************
* SQLBindParameter 함수 원형 *

SQLBindParameter(	명령문 핸들(참조1),
매개변수의 순서(1부터 시작),
매개변수 타입(택1),
매개변수의 C 데이터 타입,
매개변수의 SQL 데이터 타입,
*value의 정밀도(참조2),
십진 숫자(참조3),
실제 데이터 포인터(중요!!),
*value 버퍼의 최대 크기,
SQLExecute() 또는 SQLExecDirect()가 호출되었을 때 입력/출력된 데이터 길이의 포인터 -> 반드시 SQL_NTS여야!
)
※ 참조1 명령문 핸들 : 접속 결과 저장 변수 hstmt1을 말함.
※ 택1			  :(SQL_PARAM_INPUT, SQL_PARAM_OUTPUT, SQL_PARAM_INPUT_OUTPUT)
※ 참조2			  :	columnSize를 나타내며 SQL 데이터 타입에 따라 달라짐. -> 자리수를 뜻함.
※ 참조3			  : Scale을 나타내며, SQL 데이터 타입이 SQL_NUMERIC일 경우 소수점 아래의 자리수
※ 중요!!			  : 물음표에 해당하는 데이터가 저장된 변수의 주소값을 나타냄!!!!

***********************/

