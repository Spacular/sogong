<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"
    info = "Student Login Page By simpsons"
    session = "true"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<meta name = "viewport" content = "width=device-width, initial-scale=1.0"/>
<% request.setCharacterEncoding("utf-8"); %>
<%--
---------------- 메타태그 정리 ----------------

<META name="generator" content="저작 프로그램">
 홈페이지를 만드는데 사용한 프로그램 프로그램 이름을 넣으려면 content="EditPluse 3.0.2" 과 같은 식으로 적으시면 됩니다.

<META name="author" contents="제작자 이름">
홈페이지를 만든 제작자를 넣으려면 content="놀라운넘" 와 같이 적으시면 됩니다.

<META name="keywords" content="Key or Tag">
 홈페이지가 담고 있는 내용을 content="[Tip] META태그의 모든것" 와 같이 ',' 를 단어 사이에 넣어 나열하시면 됩니다.
검색엔진에서 검색어를 입력하고 찾기를 할 때 불러들이는 부분들입니다. 메타태그의 핵심기능이라고 할 수 있습니다.

<META name="description" content="간략한 설명">
홈페이지에 대한 간단한 소개글을 적습니다.

<META http-equiv="refresh" content="3; url=http://tuning.egloos.com">
 3초 후에 http://tuning.egloos.com 로 자동으로 이동하게 하는 옵션입니다.

<META http-equiv="Pragma" content="no-cache">
 캐쉬에서 해당 페이지를 읽어들이는 걸 방지합니다. 들어올 때마다 새로고침을 한 것과 같은 효과입니다

정리내용 출처 : http://tuning.egloos.com/3614011
----------------------------------------------------------------
그 외 참고 : http://nlife4u.tistory.com/301
--%>
<title> 로그인 페이지</title>
</head>
<body>
</body>
<form method = "post" action = "check.jsp">
	<dl>
		<dd>
			<lable for = "id">학번: </lable>
			<input id = "id" type = "number" name = "name" placeholder="example@abc.com" required>
		</dd>
		<dd>
			<lable for = "passwd"> 비밀번호: </lable>
			<input passwd = "passwd" type = "password" name = "passwd" placeholder = "12345678" required>
		</dd>
	</dl>
	<dd>
		<input type = "submit" value = "로그인">
	</dd>
</form>
<form method = "post" action = "register.jsp">
	<dd>
		<input type = "submit" value = "회원가입">
	</dd>
</form>
</html>