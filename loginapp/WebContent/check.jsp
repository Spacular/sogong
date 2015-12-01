<!doctype html>
<%@page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
 <%@page import = "java.sql.*" %>
<html class="no-js" lang="">
    <head>
        <meta charset="utf-8">
        <title></title>
        <meta name="viewport" content="width=device-width, initial-scale=1">
    </head>
    <body onload="check()">
        <%        	
	        Connection conn = null;
        
        	boolean isExist = false;
        	boolean isCorrect = false;
        	boolean isAdmin = false;
        	
        	String ID = request.getParameter("username");	
        	String Passwd = request.getParameter("password");
        	
	    	try{
	    		String url = "jdbc:mysql://localhost:3306/member";
	    		String DbId = "root";
	    		String DbPass = "542133tlatms";
	    		ResultSet rst = null;
	    		
	    		Class.forName("com.mysql.jdbc.Driver");
	    		conn = DriverManager.getConnection(url, DbId, DbPass);

	    		String sql = "select m_id, m_pw from member where m_id = ?;";
	    		
	    		PreparedStatement pstmt = conn.prepareStatement(sql);
	    		pstmt.setString(1, ID);
	    		
	    		rst = pstmt.executeQuery();		// Select문을 실행하기 위해 사용하는 구문
	    		if(rst.next()){
	    			// 반환값이 있으면 진입하게 된다.
	    			// 여기서 반환된 비밀번호를 대조해야!
	    			String result = rst.getString("m_id");
	    			if(result.equals(ID))	// 비밀번호가 일치한다면!
	    			{
	    				isExist = true;
	    			}
	    			
	    			result = rst.getString("m_pw");
	    			if(result.equals(Passwd))	// 비밀번호가 일치한다면!
	    			{
	    				isCorrect = true;
	    			}
				}
	    	}
	    	catch(SQLException e){
	    		e.printStackTrace();
	    	}
	    	%>
	    	
	    	<form action = "Input.jsp" method="post" accept-charset="utf-8" name="idform">
	    		<input type="hidden" name="id" value="">
	    	</form>
        <script type="text/javascript">
		
		function check(){
			var exist = "<%= isExist%>";
			var correct = "<%=isCorrect%>";
			
			if(exist == "true")
			{
				if(correct == "true")
				{	
					alert("환영합니다!");
					document.idform.id.value = <%= ID%>;	// 넘겨받은 학번으로 다시 재설정
					document.idform.submit();
					/*location.href = "http://sogong.iptime.org:8080/loginapp/Input.jsp";*/
					/*http://sogong.iptime.org:8080/loginapp/main.jsp*/
				}
				else
				{
					alert("비밀번호가 틀렸습니다! 다시 입력해주세요!");
					history.back();
				}
			}
			else
			{
				alert("학번이 존재하지 않습니다! 다시 입력해주세요!");
				history.back();
			}
		}
	</script>
    </body>
</html>
