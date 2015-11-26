<!doctype html>
<html lang="ko">
    <head>
        <meta charset="utf-8">
        <title></title>
        <meta name="description" content="">
        <meta name="viewport" content="width=device-width, initial-scale=1">
    </head>
    <body>
        <%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
        <%@ page import = "java.sql.*" %>
        <%@ page import = "java.lang.*" %>

        <%
            Connection conn = null;

            String number = request.getParameter("number");         // 좌석번호
            String count = request.getParameter("count");           // 실패횟수
            String ID = request.getParameter("id");                 // 넘겨받은 학번

            int count_num;                                          // 넘겨받은 학번이 String 타입이므로 Int형으로 받아줄 변수
            count_num = Integer.valueOf(count);
            String novalue = "null";

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
                if (rst.next()) {
                    // 반환값이 있으면 진입하게 된다.
                    // 여기서 중복값 증가시키고 반환!
                    count_num = Integer.valueOf(count);      // 전달받은 카운트 변수를 정수형으로 변경
                    count_num++;                             // 중복이니까 카운트 하나 증가
                    // 여기서 카운트 횟수에 따라 좌석등록에페이지로 가지만 warning이 1이 되고
                    // 경고성 메세지 출력 
                    if (count_num < 3) {
        %>
        <script>
            alert("중복입니다. 다시 입력해주세요.");
        </script>
        <%
                    } else {
        %>
        <script>
            alert("좌석 중복 3회 이상입니다. 의심학생으로 등록되었으므로 담당교수와 상의하시기 바랍니다.");
        </script>                            
        <% 
                    sql = "update member set m_warning = 1 where m_id = ?;";
                    pstmt = conn.prepareStatement(sql);
                    pstmt.setString(1, ID);
                    pstmt.executeUpdate();
                        // 해당 학생 m_warning = 1로 UpdateQuery 날리고
                        // 이전 페이지로 이동
                        // 경고성 메세지 출력
                        // 좌석 중복 3회 초과입니다. 의심학생으로 등록되었으므로 담당교수와 상의하시기 바랍니다.
                    }
                    request.setAttribute("id", ID);
                    request.setAttribute("count", count_num);
                    pageContext.forward("Input.jsp");               // setAttribute로 속성 지정하고 나서 다음 페이지로 넘어간다.
                } else {
                    // 책상이 중복이 아닌경우!
                    
                    sql = "update seat set s_check = 'x' where s_id = ?;";
                    // 해당 좌석의 상태를 앉아있는 상태로 변경.
                    pstmt = conn.prepareStatement(sql);
                    pstmt.setString(1, number);
                    pstmt.executeUpdate();

                    sql = "update seat set s.m_id = ? where s_id = ?;";
                    // 해당 좌석에 배정된 학생도 변경
                    pstmt = conn.prepareStatement(sql);
                    pstmt.setString(1, ID);
                    pstmt.setString(2, number);
                    pstmt.executeUpdate();
                }
            } catch (SQLException e) {
                e.printStackTrace();
            }
        %>
    </body>
</html>
