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
        <title>���� ������</title>
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
            <input type="text" class = 'text' name ="question" placeholder="������ �Է��ϼ���" id = 'idtext'/>
            <input type ="hidden" value ="" name = "id"/>
            <input type="submit" value="�����ϱ�" data-wait="Please wait..." name ="��ư" class="button"/>
        </form>
        <form action = 'logout.jsp'	method = "post" accept-charset="euckr" name= "logout">
        	<input type ="hidden" value ="" name = "id"/>
        	<input type="submit" value="�¼����� �ϱ�" data-wait="Please wait..." name ="��ư" class="button"/>
        </form>
        <script>
            var id = <%= ID %>;
			var number = <%=desknumber%>;
			if(number === null){
				alert("�߸��� �����Դϴ�!");
				window.location.href = "index.jsp";
			}
            document.getElementById('announce').innerHTML = "<%=desknumber%>�� �¼��� �����̽��ϴ�";
            document.getElementById('idtext').value = "";
            document.viewpage.id.value = id;
            document.logout.id.value = id;
        </script>
    </body>
</html>
