<%-- 
    Document   : checkdesk
    Created on : Nov 27, 2015, 4:33:09 PM
    Author     : simpsons
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@ page import = "java.sql.*" %>
<%@ page import = "java.io.*" %>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title></title>
    </head>
    <body>
        <%
            Connection conn = null;

            String number = request.getParameter("number");         // 좌석번호
            String count = request.getParameter("count");           // 실패횟수
            String ID = request.getParameter("id");                 // 넘겨받은 학번

            boolean isDuplicated = false;

            int count_num;                                          // 넘겨받은 실패횟수가 String 타입이므로 Int형으로 받아줄 변수
            count_num = Integer.valueOf(count);
            String novalue = "null";

            PrintWriter test = response.getWriter();

            try {

                String url = "jdbc:mysql://localhost:3306/member";
                String DbId = "root";
                String DbPass = "542133tlatms";
                ResultSet rst = null;

                Class.forName("com.mysql.jdbc.Driver");
                conn = DriverManager.getConnection(url, DbId, DbPass);

                String sql = "select m_id from seat where s_id = ?;";

                PreparedStatement pstmt = conn.prepareStatement(sql);
                pstmt.setString(1, number);
                rst = pstmt.executeQuery();		// Select문을 실행하기 위해 사용하는 구문
                rst.next();
                String result = rst.getString(1);
                if (result != null) {
                    // 반환값이 있으면 진입하게 된다.
                    // 여기서 중복값 증가시키고 반환!
                    count_num = Integer.valueOf(count);      // 전달받은 카운트 변수를 정수형으로 변경
                    count_num++;                             // 중복이니까 카운트 하나 증가
                    // 여기서 카운트 횟수에 따라 좌석등록에페이지로 가지만 warning이 1이 되고
                    // 경고성 메세지 출력 
                    if (count_num < 3) {
                        test.println("<script type='text/javascript'> alert('중복 좌석입니다 다시 입력해주세요.') </script>");
                    } else {
                        test.println("<script type='text/javascript'> alert('좌석 중복 3회 이상입니다. 의심학생으로 등록되었으므로 담당교수와 상의하시기 바랍니다.') </script>");
                        sql = "update member set m_warning = 1 where m_id = ?;";
                        pstmt = conn.prepareStatement(sql);
                        pstmt.setString(1, ID);
                        pstmt.executeUpdate();
                        // 해당 학생 m_warning = 1로 UpdateQuery 날리고
                        // 이전 페이지로 이동
                        // 경고성 메세지 출력
                        // 좌석 중복 3회 초과입니다. 의심학생으로 등록되었으므로 담당교수와 상의하시기 바랍니다.
                    }
                    isDuplicated = true;
                    /*
                    request.setAttribute("id", ID);
                    request.setAttribute("count", count_num);
                    pageContext.forward("Input.jsp");               // setAttribute로 속성 지정하고 나서 다음 페이지로 넘어간다.
                     */
                } 
                else {
                    // 책상이 중복이 아닌경우!

                    sql = "update seat set s_check = 'x' where s_id = ?;";
                    // 해당 좌석의 상태를 앉아있는 상태로 변경.
                    pstmt = conn.prepareStatement(sql);
                    pstmt.setString(1, number);
                    pstmt.executeUpdate();

                    sql = "update seat set m_id = ? where s_id = ?;";
                    // 해당 좌석에 배정된 학생도 변경
                    pstmt = conn.prepareStatement(sql);
                    pstmt.setString(1, ID);
                    pstmt.setString(2, number);
                    pstmt.executeUpdate();

                    // request.setAttribute("id", ID);
                    // request.setAttribute("count", count_num);
                    // pageContext.forward("view.jsp");               // setAttribute로 속성 지정하고 나서 다음 페이지로 넘어간다.
                }
            } catch (SQLException e) {
                e.printStackTrace();
            }
        %>
        <script type ="text/javascript">
            window.onload = function () {
                var isDuplicated = <%= isDuplicated%>;
                if (isDuplicated === true) {
                    location.href = "http://sogong.iptime.org:8084/loginapp/Input.jsp";
                } else {
                    location.href = "http://sogong.iptime.org:8084/loginapp/view.jsp";
                }
            };
        </script>
    </body>
</html>
