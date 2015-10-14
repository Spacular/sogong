<?php
    include("header.php");
?>

<body>
	<div id="wrapper">
		<div id="top">
			<p style="padding-top:20px; font-size:20px; font-weight:bold; color:#13284c;">좌석 번호 입력</p>
		</div>
		<div id="middle">
			<form action="seat_chk.php" method="post">
				<input type="text" name="s_number" class="login_box3"/>
				<br />
				<input type="submit" value="확인"  class="login_bt2" />
			</form>
		</div>
		<div id="footer">
			ddd
		</div>
	</div>
</body>
</html>