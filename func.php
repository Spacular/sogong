<?php

	function alert($msg){
		echo "<script type='text/javascript'>
		alert('$msg');
		</script>";
	}


	function pagemove($url){
		echo "<script type='text/javascript'>
		top.location.replace('$url');
		</script>";
	}


	function alertback($msg){
		echo "<script type='text/javascript'>
		alert('$msg');
		history.back();
		</script>";
	}

	function window_c(){
		echo "<script type='text/javascript'>
		window.close();
		</script>";
	}
	
	function reple(){
		echo "<script type='text/javascript'>
		opener.location.reload(); 
		</script>";
	}
	
?>