<?php
    include("header.php");
?>

<body>
	<div id="wrapper">
		<div id="top">
			<p style="padding-top:20px; font-size:20px; font-weight:bold; color:#13284c;">자리배치 프로그램 로그인</p>
		</div>
		<div id="middle">
			<form action="login_chk.php" method="post">
				<input type="text" name="m_id" class="login_box"/>
				<br />
				<input type="password" name="m_pw" class="login_box2"/>
				<br />
				<input type="submit" value="로그인"  class="login_bt" />
			</form>
		</div>
		<div id="footer">
			ccc
		</div>
	</div>
</body>
</html>