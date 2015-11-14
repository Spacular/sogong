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
	Errmsg.Format(_T("�����߻�! �����ڵ�: %d"), retcode);		// ���� ������ �����Ѵ�.

	if ((retcode = SQLAllocEnv(&henv)) != SQL_SUCCESS)
		AfxMessageBox(Errmsg);								// �޼��� �ڽ��� ���� ������ ������ ����Ѵ�.
	if ((retcode = SQLAllocConnect(henv, &hdbc1)) != SQL_SUCCESS)
		AfxMessageBox(Errmsg);
	if ((retcode = SQLConnect(hdbc1, (SQLWCHAR *)TEXT("member"/*DSN�̸�*/), SQL_NTS/*NULL���� ���*/, (SQLWCHAR *)TEXT("root"/*���Ӱ���*/), SQL_NTS, (SQLWCHAR *)TEXT("542133tlatms"/*��й�ȣ*/), SQL_NTS)) != SQL_SUCCESS)
		AfxMessageBox(Errmsg);

	SQLAllocStmt(hdbc1, &hstmt1);		// ���� ���� Handle ȹ��
}

int CManageToolLogin::isExist(CString ID, CString Pwd) {
	int ID_result = 0, i = 0, user_i;
	SQLINTEGER save, save2 = 0;
	BOOL isExistID = 0, isExistPwd = 0, isAdmin = 0;

	int strLen = Pwd.GetLength();		// CString Ÿ�� ������ ���ڿ� ���� �˾Ƴ���

										//char pwd[20];
	char* pwd = (char*)calloc(strLen, sizeof(char));		// �����Ҵ� ���ֱ� *����* �Ʒ��� �ּ� ������ pwd��! &pwd �ƴϴ�!!!
															//char* pwd = new char[strLen];
	char PWD_result[20];
	int user[100];

	SQLWCHAR* admin_query = (SQLWCHAR*)TEXT("select m_id from member where m_admin = 1;");

	SQLWCHAR* id_query = (SQLWCHAR*)TEXT("select m_id from member where m_id = ?;");
	int id = _wtoi(ID);

	SQLWCHAR* pwd_query = (SQLWCHAR*)TEXT("select m_pw from member where m_pw = ?;");
	//int pwd = _wtoi(Pwd);

	//pwd = CStringA(Pwd);			// Unicode ���ڼ¿��� string Ÿ������ ��ȯ���ִ� �Լ�.
	//int passwd = atoi(pwd.c_str());

	WideCharToMultiByte(CP_ACP, 0, Pwd, -1, pwd, strLen + 1, NULL, NULL);

	SQLINTEGER ret = SQL_NTS;


	/********* ���⼭���Ͱ� ������ ���� ��ȸ ������ *********/
	if ((retcode = SQLPrepare(hstmt1, admin_query/*���� SQL ���ڿ�*/, SQL_NTS)) != SQL_SUCCESS)
		AfxMessageBox(Errmsg);
	if (retcode == SQL_SUCCESS)
	{
		retcode = SQLBindCol(hstmt1, 1, SQL_C_SLONG, &user_i, sizeof(user_i), &save);	// ������� ù Column�� ����.
	}
	SQLExecute(hstmt1);
	while ((retcode = SQLFetch(hstmt1)) == SQL_SUCCESS) {
		user[i++] = user_i;
	}

	for (i = 0; i < sizeof(user)/sizeof(int); i++) {
		if (id == user[i])
			isAdmin = TRUE;
	}
	/********* ���⼭������ ������ ���� ��ȸ ������ *********/


	/********* ���⼭���Ͱ� ��й�ȣ ��ȸ ������ *********/
	if ((retcode = SQLPrepare(hstmt1, pwd_query/*���� SQL ���ڿ�*/, SQL_NTS)) != SQL_SUCCESS)
		AfxMessageBox(Errmsg);
	else {
		if ((retcode = SQLBindParameter(hstmt1, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, sizeof(pwd), 0, pwd, 0, &ret)) != SQL_SUCCESS)
		{
			AfxMessageBox(Errmsg);
		}
	}
	if (retcode == SQL_SUCCESS)
	{
		retcode = SQLBindCol(hstmt1, 1, SQL_C_CHAR, PWD_result, sizeof(PWD_result), &save2);	// ������� ù Column�� ����.
	}

	SQLExecute(hstmt1);
	while ((retcode = SQLFetch(hstmt1)) == SQL_SUCCESS)
	{
		isExistPwd = TRUE;
	}
	/********* ���⼭������ ��й�ȣ ��ȸ ������ *********/

	/********* �й� �� ���� ��ȸ ����!! *********/
	if ((retcode = SQLPrepare(hstmt1, id_query/*���� SQL ���ڿ�*/, SQL_NTS)) != SQL_SUCCESS)
		AfxMessageBox(Errmsg);
	else {
		if ((retcode = SQLBindParameter(hstmt1, 1, SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER, 0, 0, &id, 0, NULL)) != SQL_SUCCESS)
		{
			AfxMessageBox(Errmsg);
		}
	}
	if (retcode == SQL_SUCCESS)
	{
		retcode = SQLBindCol(hstmt1, 1, SQL_C_SLONG, &ID_result, sizeof(ID_result), &save);	// ������� ù Column�� ����.
	}

	SQLExecute(hstmt1);
	while (SQLFetch(hstmt1) == SQL_SUCCESS)
	{
		isExistID = TRUE;
	}
	/********* ��������� �й� �� ���� ��ȸ �����̾��� *********/

	SQLFreeStmt(hstmt1, SQL_DROP);
	SQLDisconnect(hdbc1);
	SQLFreeConnect(hdbc1);
	SQLFreeEnv(henv);

	if ((isExistID == TRUE) && (isExistPwd == TRUE) && (isAdmin == TRUE)) {
		return TRUE;				// ��ġ�ϴ� ���� ã��!
	}
	else if ((isExistID == TRUE) && (isExistPwd == TRUE) && (isAdmin != TRUE)) {
		return 0;					// ������ ������ �ƴ�!
	}
	else {
		return -1;					// ���� ��ü�� ����!
	}
}

/**********************
* SQLBindParameter �Լ� ���� *

SQLBindParameter(	��ɹ� �ڵ�(����1),
�Ű������� ����(1���� ����),
�Ű����� Ÿ��(��1),
�Ű������� C ������ Ÿ��,
�Ű������� SQL ������ Ÿ��,
*value�� ���е�(����2),
���� ����(����3),
���� ������ ������(�߿�!!),
*value ������ �ִ� ũ��,
SQLExecute() �Ǵ� SQLExecDirect()�� ȣ��Ǿ��� �� �Է�/��µ� ������ ������ ������ -> �ݵ�� SQL_NTS����!
)
�� ����1 ��ɹ� �ڵ� : ���� ��� ���� ���� hstmt1�� ����.
�� ��1			  :(SQL_PARAM_INPUT, SQL_PARAM_OUTPUT, SQL_PARAM_INPUT_OUTPUT)
�� ����2			  :	columnSize�� ��Ÿ���� SQL ������ Ÿ�Կ� ���� �޶���. -> �ڸ����� ����.
�� ����3			  : Scale�� ��Ÿ����, SQL ������ Ÿ���� SQL_NUMERIC�� ��� �Ҽ��� �Ʒ��� �ڸ���
�� �߿�!!			  : ����ǥ�� �ش��ϴ� �����Ͱ� ����� ������ �ּҰ��� ��Ÿ��!!!!

***********************/

