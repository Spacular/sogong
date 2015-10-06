<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>::회원가입::</title>
</head>
<body>
	<% 
	String ID = null;
	String Passwd = null;
	%>
	<form method = "post" action ="DB.jsp">
	<dl>
		<dd>
			<label for = "ID">학번: </label>
			<input id = "ID" name = "ID" type = "text" placeholder = "1234" required>
		</dd>
		<dd>
			<label for = "Passwd">비밀번호: </label>
			<input id = "Passwd" name = "Passwd" type = "password" placeholder = "1234" required>
		</dd>
	</dl>
	<input type = "reset" value = "다시작성">
	<input type = "submit" value = "등록하기" >
	</form>
	<form method = "post" action = "JDBCtest.jsp">
		<input type = "submit" value = "DB 연결상태 테스트">
	</form>
</body>
</html>