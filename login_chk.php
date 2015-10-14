<?php
	include("header.php");

	$query=mysql_query("select * from member where m_id='$_POST[m_id]' and m_pw='$_POST[m_pw]'",$connect);
	$data=mysql_fetch_array($query);

	if(!$data){
		alertback("아이디나 비밀번호가 틀렸습니다.");
	
	} else if($data){
		$_SESSION[m_id]=$data[m_id];
		
		alert("로그인 되었습니다.");
		pagemove("seat.php");
	} 
?>