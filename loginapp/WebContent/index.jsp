<!doctype html>
<html>
    <head>
    	<link href="my.css" rel="stylesheet">
        <meta charset="UTF-8">
        <meta http-equiv="x-ua-compatible" content="ie=edge">
        <!-- 호환성 보기모드에서의 에러 방지  -->
        <title>학생 로그인</title>
        <meta name="viewport" content="width=device-width, initial-scale=1">
    </head>
    <body>
        <!--[if lt IE 8]>
            <p class="browserupgrade">You are using an <strong>outdated</strong> browser. Please <a href="http://browsehappy.com/">upgrade your browser</a> to improve your experience.</p>
        <![endif]-->
    <div class = "frame">
    <div class = "background">
    <address class = "copyright" >
    <strong>Copyright Team 3. All right reserved.</strong>
    </address>
    </div>
    <div class = "box">
        <form action = "check.jsp" accept-charset="utf-8" method ="post">
           <table>
                <tr>
                    <th style="text-align:right;"><label for="username">로그인:</label></td>
                    <td style="text-align:left;"><input type="text" name="username" id="username" tabindex="1" /></td>
                </tr>
                <tr>
                    <th style="text-align:right;"><label for="password">비밀번호:</label></td>
                    <td style="text-align:right;"><input type="password" name="password" id="password" tabindex="2" /></td>
                </tr>
                <tr>
                    <td></td>
                    <td style="text-align:left;">
                    </td>
                </tr>
                <tr>
                    <td style="text-align:right;">
                        <input type="submit" name="login" value="로그인 &#187;" tabindex="5"/>
                    </td>
                </tr>
            </table>
        </form>
    </div>
	</div>
	<div class = "logo"> </div>
    </body>
</html>
