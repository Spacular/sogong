<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>확인중...</title>
</head>
<body>
	<%
		String ID = request.getParameter("name");
		String Passwd = request.getParameter("passwd");
	%>
	학번: <%=ID %><br>
	비밀번호: <%= Passwd %><br>
	입력하신 정보가 맞습니까?
	<form method = "post" action = "check2.jsp">
		<dd>
			<input type = "submit" value="예">
		</dd>
	</form>
	<form method = "post" action = "index.jsp">
		<dd>
			<input type = "submit" value="아니오">
		</dd>
	</form>
</body>
</html>