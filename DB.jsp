<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page import = "java.sql.*" %>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>DB Update 페이지</title>
</head>
<body>
<%
Connection conn = null;
PreparedStatement pstmt = null;
	
	try{
		String url = "jdbc:mysql://localhost:3307/attendance";
		String DbId = "root";
		String DbPass = "542133tlatms";
		String ID = request.getParameter("ID");
		String Passwd = request.getParameter("Passwd");
		
		Class.forName("com.mysql.jdbc.Driver");
		conn =DriverManager.getConnection(url, DbId, DbPass);
		// 여기까지 db접속 및 체크에 필요한 모든 과정임.
		
		String chk = "select ID from stuinfo where ID=" + ID;	// 학생테이블에서 주키는 ID이므로 ID로 검색한다.
		String sql = "insert into stuinfo values(?,?)";				// 일단 빈 레코드를 만든 다음
		ResultSet result = null;
		
		pstmt = conn.prepareStatement(chk);
		result = pstmt.executeQuery(chk);
		
		// 다음으로 넘어갈 값이 있으면 true를 반환하니까, 있는 값이라는 뜻.
		if(result.next())	{	// 입력값이 중복인지 체크한 다음
			throw new Exception("중복값입니다!!");
		}
		pstmt = conn.prepareStatement(sql);
		pstmt.setString(1, ID);
		pstmt.setString(2, Passwd);		// 중복이 아니면 레코드를 설정해준다.
		pstmt.executeUpdate();			// select 문에서 쓰이는 commit 구문.
		out.println("attendance 테이블에 새로운 레코드를 추가했습니다!\n");
	}
	catch(Exception e){
		out.println("attendance 테이블에 새로운 레코드 추가에 실패했습니다!\n");
		out.println(e.getMessage());
		e.printStackTrace();
	}
	finally{
		if(pstmt != null)	
			try{pstmt.close();}catch(SQLException sqle){}
		if(conn != null)
			try{conn.close();}catch(SQLException sqle){}
	}
	%>
	<form method = "post" action ="index.jsp">
		<input type = "submit" value = "되돌아가기">
	</form>
</body>
</html>