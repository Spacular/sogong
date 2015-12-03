<!doctype html>
<html>
	<%@page import="java.sql.*" %>
    <head>
        <meta charset="utf-8">
        <meta http-equiv="x-ua-compatible" content="ie=edge">
        <title>로그아웃</title>
    </head>
    <body>
     <script>
     	alert("로그아웃되었습니다!");
     	//window.location.href = "http://sogong.iptime.org:8080/loginapp/Input.jsp";
     </script>
     <%
     Connection conn = null;

     String ID = request.getParameter("id");                 // 넘겨받은 학번  
     
     String url = "jdbc:mysql://localhost:3306/member?useUnicode=true&characterEncoding=EUC-KR";
     String DbId = "root";
     String DbPass = "542133tlatms";
     ResultSet rst = null;

     Class.forName("com.mysql.jdbc.Driver");
     conn = DriverManager.getConnection(url, DbId, DbPass);

     String sql = "update seat set s_check = 'o' where m_id = ?;";
     PreparedStatement pstmt = conn.prepareStatement(sql);
     pstmt.setString(1, ID);
     pstmt.executeUpdate();		// Select문을 실행하기 위해 사용하는 구문
     
     sql = "update seat set m_id = NULL where m_id = ?;";
     pstmt = conn.prepareStatement(sql);
     pstmt.setString(1, ID);
     pstmt.executeUpdate();
     
  	request.setAttribute("id", ID);
  	pageContext.forward("Input.jsp");
     %>  
    </body>
</html>
