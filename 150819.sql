-- phpMyAdmin SQL Dump
-- version 3.2.3
-- http://www.phpmyadmin.net
--
-- 호스트: localhost
-- 처리한 시간: 15-09-24 22:25 
-- 서버 버전: 5.1.41
-- PHP 버전: 5.2.12

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- 데이터베이스: `150819`
--

-- --------------------------------------------------------

--
-- 테이블 구조 `member`
--

CREATE TABLE IF NOT EXISTS `member` (
  `m_no` int(20) NOT NULL AUTO_INCREMENT,
  `m_id` varchar(40) NOT NULL,
  `m_pw` varchar(40) NOT NULL,
  `m_level` int(5) NOT NULL,
  `m_name` varchar(20) NOT NULL,
  `m_warning` int(10) NOT NULL,
  PRIMARY KEY (`m_no`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=3 ;

--
-- 테이블의 덤프 데이터 `member`
--

INSERT INTO `member` (`m_no`, `m_id`, `m_pw`, `m_level`, `m_name`, `m_warning`) VALUES
(1, 'admin', 'admin', 1, '강태웅', 3),
(2, '21111738', 'admin', 0, '김동오', 0);

-- --------------------------------------------------------

--
-- 테이블 구조 `seat`
--

CREATE TABLE IF NOT EXISTS `seat` (
  `s_no` int(10) NOT NULL AUTO_INCREMENT,
  `s_number` varchar(20) NOT NULL,
  `s_check` varchar(10) NOT NULL,
  `s_id` varchar(25) NOT NULL,
  PRIMARY KEY (`s_no`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=17 ;

--
-- 테이블의 덤프 데이터 `seat`
--

INSERT INTO `seat` (`s_no`, `s_number`, `s_check`, `s_id`) VALUES
(1, 'a1', 'O', 'admin'),
(2, 'a2', 'O', 'admin'),
(3, 'a3', 'O', 'admin'),
(4, 'a4', 'O', 'admin'),
(5, 'a5', 'O', 'admin'),
(6, 'a6', 'O', 'admin'),
(7, 'a7', 'O', 'admin'),
(8, 'a8', 'O', 'admin'),
(9, 'a9', 'O', 'admin'),
(10, 'a10', 'O', 'admin'),
(11, 'a11', 'O', 'admin'),
(12, 'a12', 'O', 'admin'),
(13, 'a13', 'O', 'admin'),
(14, 'a14', 'O', 'admin'),
(15, 'a15', 'O', 'admin'),
(16, 'a16', 'O', 'admin');
