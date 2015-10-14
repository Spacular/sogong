<?php
	session_start();
	$connect=mysql_connect("localhost","root", "apmsetup" ) or die ("die");
	mysql_select_db("150819",$connect);
	mysql_query('set names utf8');

	

	
	
?>
