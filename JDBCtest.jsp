<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
 <%@ page import = "java.sql.*" %>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>DB연동 테스트 페이지</title>
</head>
<body>
<% 
	Connection conn = null;
	
	try{
		String url = "jdbc:mysql://localhost:3307/attendance";
		String DbId = "root";
		String DbPass = "542133tlatms";
		
		Class.forName("com.mysql.jdbc.Driver");
		conn =DriverManager.getConnection(url, DbId, DbPass);
		out.println("제대로 연결되었습니다!\n\n");
	}
	catch(SQLException e){
		e.printStackTrace();
	}
%>
<form method = "post" action="register.jsp">
	<input type = "submit" value="되돌아가기">
</form>

</body>
</html>