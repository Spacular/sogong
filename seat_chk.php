<?php
	include("header.php");
	
	
	$query=mysql_query("select * from seat where s_number='$_POST[s_number]'",$connect);
	$data=mysql_fetch_array($query);
	$member_q=mysql_query("select * from member where m_id='$_SESSION[m_id]'",$connect);
	$member=mysql_fetch_array($member_q);
	
	if($data[s_check]=="O" || !$data){
		
		$query3="update member set m_warning='$member[m_warning]'+1 where m_id='$_SESSION[m_id]'";
		mysql_query($query3,$connect);
		
		alertback("잘못 된 좌석 입니다.");
		
	} else if($data[s_check]=="X"){
		//$_SESSION[m_id]=$data[m_id];
		$query2="update seat set s_check='O',s_id='$_SESSION[m_id]'";
		mysql_query($query2,$connect);
		alert("좌석이 배정 되었습니다.");
		pagemove("main.php");
	} 
?>