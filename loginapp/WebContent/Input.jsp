<!doctype html>
<html class="no-js" lang="">
    <head>
        <meta http-equiv="content-type" content="text/html; charset=utf-8">
        <title> 좌석 입력 페이지 </title>
        <meta name="description" content="좌석입력">
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
            html{
                height: 100%;
                width: 100%;	
            }
            .input{
                border: 1px solid black;
                position: absolute;
                width: 100%;
                height: 100%;
                background-color: #E1EDEB;
            }
            @media screen, handheld and (max-width:479px){
                .image {
                    background-image: url("./image/seat.jpg");
                    background-repeat: no-repeat;
                    background-size: cover;
                    -webkit-background-size: cover;
                    -moz-background-size: cover;
                    -o-background-size: cover;
                    background-attachment: fixed;
                    background-position: center;
                    position: absolute;
                    width: 100%;
                    height: 100%;
                }
            }

            tr{
                font-family: "Malgun", sans-serif;
                font-size: 30pt;
            }
            table{
                position: absolute;
                left: 25%;
                top: 50%;
            }
        </style>
    </head>
    <body onload="count();">    
        <div class="image">
            <form action ="check_desk.jsp" accept-charset="utf-8" name="check" method = "post">
                <input type="hidden" id="count" name="count" value="">
                <input type="hidden" id="id" name="id" value="">
                <table>
                    <tr>
                        <th style="color:white; text-align:right;"><label for="username">좌석번호:</label></th>
                        <td width = "10"></td>
                        <td style="text-align:right;"><input style="text-align:right; width:300px; height:50px; font-size:30pt;" type="text" name="number" id="number" tabindex="1" /></td>
                        <td width = "30"></td>
                        <td><input type="submit" value="등록" data-wait="Please wait..." class="button" onclick="document.check.onsubmit();"></td>
                    </tr>
                </table>
            </form>
        </div>
        <%
            String ID = request.getParameter("id");
        %>
        <script type="text/javascript">
            function count() {
                var count = document.getElementById("count").value;
                if (count == "") {
                    count = "0";
                    document.getElementById("count").value = count;
                }
                alert(count);
                var id = <%= ID%>;
                document.check.id.value = id;
                // 넘겨 받은 ID와 count 수치로 세팅.
            }
        </script>
    </body>
</html>
