<?php
	include("header.php");
?>
<body>
	<div id="wrapper">
		<div id="top">
			<p style="padding-top:20px; font-size:20px; font-weight:bold; color:#13284c;">자리배치 확인</p>
		</div>
		<div id="middle">
			<?php
				$query_q=mysql_query("select * from seat where s_id='$_SESSION[m_id]'",$connect);
				$query=mysql_fetch_array($query_q);
			?>
			<script type="text/javascript">
					$(document).ready(function (){ 
						$('#<?php echo $query[s_number];?>').css('color','pink');
						$('.a').css('color','blue');
					});
				</script>
				<p class="a">asdff</p>
			<table class="table1">
				
				
				<tr>
					<td id="a1">a1</td>
					<td id="a2">a2</td>
					<td id="a3">a3</td>
					<td id="a4">a4</td>
				</tr>
				<tr>
					<td id="a5">a5</td>
					<td id="a6">a6</td>
					<td id="a7">a7</td>
					<td id="a8">a8</td>
				</tr>
				<tr>
					<td id="a9">a9</td>
					<td id="a10">a10</td>
					<td id="a11">a11</td>
					<td id="a12">a12</td>
				</tr>
				<tr>
					<td id="a13">a13</td>
					<td id="a14">a14</td>
					<td id="a15">a15</td>
					<td id="a16">a16</td>
				</tr>
			</table>
		</div>
		<div id="footer">
			ccc
		</div>
	</div>
</body>
</html>