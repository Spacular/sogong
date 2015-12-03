<%-- 
    Document   : newjsp
    Created on : Dec 3, 2015, 8:14:31 PM
    Author     : simpsons
--%>


<html>
    <%@page contentType="text/html; charset = euc-kr" pageEncoding="UTF-8" %>
<%@ page import = "java.sql.*" %>
<!DOCTYPE html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=euc-kr">
        <title>질문처리</title>
    </head>
    <body>
        <h3>질문처리중</h3>
        <%
            Connection conn = null;

            String ID = request.getParameter("id");                 // 넘겨받은 학번
            String question = new String(request.getParameter("question").getBytes("8859_1"), "KSC5601");  // 넘겨받은 질문
            try{
                String url = "jdbc:mysql://localhost:3306/member?useUnicode=true&characterEncoding=EUC-KR";
                String DbId = "root";
                String DbPass = "542133tlatms";
                ResultSet rst = null;

                Class.forName("com.mysql.jdbc.Driver");
                conn = DriverManager.getConnection(url, DbId, DbPass);

                String sql = "update member set m_qcontent = ? where m_id = ?;";
                PreparedStatement pstmt = conn.prepareStatement(sql);
                pstmt.setString(1, question);
                pstmt.setString(2, ID);
                pstmt.executeUpdate();		// Select문을 실행하기 위해 사용하는 구문
                
                sql = "update member set m_question = ? where m_id = ?;";
                pstmt = conn.prepareStatement(sql);
                pstmt.setString(1, "1");
                pstmt.setString(2, ID);
                pstmt.executeUpdate();
                }
             catch (SQLException e) {
                e.printStackTrace();
            }
        %>
        <script>
            window.history.go(-1);
        </script>
    </body>
</html>
