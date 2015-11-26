<!doctype html>
<html>
    <head>
    	<link href="my.css" rel="stylesheet" type="text/css">
        <meta charset="UTF-8">
        <!--<meta http-equiv="x-ua-compatible" content="ie=edge">-->
        <!-- 호환성 보기모드에서의 에러 방지  -->
        <title>학생 로그인</title>
        <!-- <meta name="viewport" content="width=device-width, initial-scale=1.0"/> -->
        
    </head>
    <body>
        <!--[if lt IE 8]>
            <p class="browserupgrade">You are using an <strong>outdated</strong> browser. Please <a href="http://browsehappy.com/">upgrade your browser</a> to improve your experience.</p>
        <![endif]-->
        <div class = "background">
        	<!-- <img src = "./image/Index.jpg"/> -->
           <div class = "box">
	        	<form action = "check.jsp" accept-charset="utf-8" method ="post">
				      <table>
				           <tr>
				                <th style="color:white; text-align:right;"><label for="username">로그인:</label></th>
				                <td width = "50"></td>
				                <td style="text-align:right;"><input style="text-align:right; width:300px; height:50px; font-size:30pt;" type="text" name="username" id="username" tabindex="1" /></td>
				           </tr>
				           <tr>
				                <th style="color:white; text-align:right;"><label for="password">비밀번호:</label></th>
				                <td width = "50"></td>
				                <td style="text-align:right;"><input style="text-align:right; width:300px; height:50px; font-size:30pt;" type="password" name="password" id="password" tabindex="2" /></td>
				           </tr>
				           <tr>
				                <td></td>
				                <td style="text-align:left;"></td>
				           </tr>
				           <tr>
				                <td></td>
				                <td></td>
				                <td style="text-align:right;">
				                <input type="submit" name = "login" value="로그인" data-wait="Please wait..." class="w-button">
				                </td>
				           </tr>
				  	  </table>
				</form>
			</div>
		</div>
    </body>
</html>
