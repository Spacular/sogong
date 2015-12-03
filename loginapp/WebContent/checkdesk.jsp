<%-- 
    Document   : checkdesk
    Created on : Nov 27, 2015, 4:33:09 PM
    Author     : simpsons
--%>

<%@page contentType="text/html" pageEncoding="euc-kr"%>
<%@ page import = "java.sql.*" %>
<%@ page import = "java.io.*" %>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title></title>
    </head>
    <body>
        <form action ="Input.jsp" method = "post" accept-charset="utf-8" name="back">
            <input type="hidden" name = "count" value=""/>
            <input type ="hidden" name ="id" value =""/>
        </form>
        <form action ="view.jsp" method ="post" accept-charset ="utf-8" name ="viewpage">
            <input type ="hidden" name ="desknumber" value = ""/>
            <input type ="hidden" name ="identification" value = ""/>
        </form>
        <%
            Connection conn = null;

            String number = request.getParameter("number");         // �¼���ȣ
            String count = request.getParameter("count");           // ����Ƚ��
            String ID = request.getParameter("id");                 // �Ѱܹ��� �й�

            boolean isDuplicated = false;
            boolean isError = false;

            int count_num;                                          // �Ѱܹ��� ����Ƚ���� String Ÿ���̹Ƿ� Int������ �޾��� ����
            count_num = Integer.valueOf(count);
            String novalue = "null";

            PrintWriter test = response.getWriter();

            try {

                String url = "jdbc:mysql://localhost:3306/member?useUnicode=true&characterEncoding=EUC-KR";
                String DbId = "root";
                String DbPass = "542133tlatms";
                ResultSet rst = null;

                Class.forName("com.mysql.jdbc.Driver");
                conn = DriverManager.getConnection(url, DbId, DbPass);

                String sql = "select m_id from seat where s_id = ?;";
                PreparedStatement pstmt = conn.prepareStatement(sql);
                pstmt.setString(1, number);
                rst = pstmt.executeQuery();		// Select���� �����ϱ� ���� ����ϴ� ����
                if(!rst.next()){
                    test.println("<script type='text/javascript'> alert('���� �¼��Դϴ�. ����� �Է����ּ���!') </script>");
                    isError = true;
                    throw new SQLException("error");
                }
                String result = rst.getString(1);
                if (result != null) {
                    // ��ȯ���� ������ �����ϰ� �ȴ�.
                    // ���⼭ �ߺ��� ������Ű�� ��ȯ!
                    count_num = Integer.valueOf(count);      // ���޹��� ī��Ʈ ������ ���������� ����
                    count_num++;                             // �ߺ��̴ϱ� ī��Ʈ �ϳ� ����
                    // ���⼭ ī��Ʈ Ƚ���� ���� �¼���Ͽ��������� ������ warning�� 1�� �ǰ�
                    // ��� �޼��� ��� 
                    if (count_num < 3) {
                        test.println("<script type='text/javascript'> alert('�ߺ� �¼��Դϴ� �ٽ� �Է����ּ���.') </script>");
                    } else {
                        test.println("<script type='text/javascript'> alert('�¼� �ߺ� 3ȸ �̻��Դϴ�. �ǽ��л����� ��ϵǾ����Ƿ� ��米���� �����Ͻñ� �ٶ��ϴ�.') </script>");
                        sql = "update member set m_warning = 1 where m_id = ?;";
                        pstmt = conn.prepareStatement(sql);
                        pstmt.setString(1, ID);
                        pstmt.executeUpdate();
                        // �ش� �л� m_warning = 1�� UpdateQuery ������
                        // ���� �������� �̵�
                        // ��� �޼��� ���
                        // �¼� �ߺ� 3ȸ �ʰ��Դϴ�. �ǽ��л����� ��ϵǾ����Ƿ� ��米���� �����Ͻñ� �ٶ��ϴ�.
                    }
                    isDuplicated = true;
                    
                    //request.setAttribute("id", ID);
                    //request.setAttribute("count", count_num);
                    //pageContext.forward("Input.jsp");               // setAttribute�� �Ӽ� �����ϰ� ���� ���� �������� �Ѿ��.
                }
                else {
                    // å���� �ߺ��� �ƴѰ��!

                    sql = "update seat set s_check = 'x' where s_id = ?;";
                    // �ش� �¼��� ���¸� �ɾ��ִ� ���·� ����.
                    pstmt = conn.prepareStatement(sql);
                    pstmt.setString(1, number);
                    pstmt.executeUpdate();

                    sql = "update seat set m_id = ? where s_id = ?;";
                    // �ش� �¼��� ������ �л��� ����
                    pstmt = conn.prepareStatement(sql);
                    pstmt.setString(1, ID);
                    pstmt.setString(2, number);
                    pstmt.executeUpdate();

                   //request.setAttribute("id", ID);
                   //request.setAttribute("count", count_num);
                   //pageContext.forward("view.jsp");               // setAttribute�� �Ӽ� �����ϰ� ���� ���� �������� �Ѿ��.
                }
            } catch (SQLException e) {
                e.printStackTrace();
            }
        %>
        <script type ="text/javascript">
            window.onload = function () {
                var isDuplicated = <%= isDuplicated%>;
                var count = <%= count_num %>;
                var isError = <%= isError %>;
                var number = <%= number %>;
                var id = <%= ID %>;
                if(isError === true){
                    window.history.go(-1);
                }
                else if (isDuplicated === true) {
                    //document.location.href = "http://sogong.iptime.org:8084/loginapp/Input.jsp?count=";
                    document.back.count.value = count;
                    document.back.id.value = id;
                    document.back.submit();
                } else {
                    document.viewpage.desknumber.value = number;
                    document.viewpage.identification.value = id;
                    //document.location.href = "http://sogong.iptime.org:8084/loginapp/view.jsp";                   
                    document.viewpage.submit();
                }
            };
        </script>
    </body>
</html>
