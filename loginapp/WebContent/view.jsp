<%-- 
    Document   : view.jsp
    Created on : Nov 30, 2015, 10:55:40 AM
    Author     : simpsons
--%>

<%@page contentType="text/html; charset = euc-kr" pageEncoding="euc-kr"%>
<%@ page import = "java.io.*" %>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>질문 페이지</title>
        <style>
            .button {
                display: inline-block;
                padding: 9px 15px;
                background-color: #3898ec;
                color: white;
                border: 0;
                line-height: inherit;
                text-decoration: none;
                cursor: pointer;
                border-radius: 0;
            }

            .text{
                width: 500px;
                height: 100px;
                text-align: right;
                font-size: 15pt;
            }
        </style>
    </head>
    <body>
        <%
            String desknumber = request.getParameter("desknumber");
            String ID = request.getParameter("identification");
        %>
        <h1 id = 'announce'> </h1>
        <form action ='upload.jsp' method ="post" accept-charset ="euckr" name ="viewpage">
            <input type="text" class = 'text' name ="question" placeholder="질문을 입력하세요" id = 'idtext'/>
            <input type ="hidden" value ="" name = "id"/>
            <input type="submit" value="질문하기" data-wait="Please wait..." name ="버튼" class="button"/>
        </form>
        <form action = 'logout.jsp'	method = "post" accept-charset="euckr" name= "logout">
        	<input type ="hidden" value ="" name = "id"/>
        	<input type="submit" value="좌석변경 하기" data-wait="Please wait..." name ="버튼" class="button"/>
        </form>
        <script>
            var id = <%= ID %>;
			var number = <%=desknumber%>;
			if(number === null){
				alert("잘못된 접근입니다!");
				window.location.href = "index.jsp";
			}
            document.getElementById('announce').innerHTML = "<%=desknumber%>번 좌석에 앉으셨습니다";
            document.getElementById('idtext').value = "";
            document.viewpage.id.value = id;
            document.logout.id.value = id;
        </script>
    </body>
</html>
