-- phpMyAdmin SQL Dump
-- version 3.2.3
-- http://www.phpmyadmin.net
--
-- 호스트: localhost
-- 처리한 시간: 15-11-08 20:05 
-- 서버 버전: 5.1.41
-- PHP 버전: 5.2.12

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- 데이터베이스: `좌석`
--

-- --------------------------------------------------------

--
-- 테이블 구조 `seat`
--

CREATE TABLE IF NOT EXISTS `seat` (
  `s_id` int(10) NOT NULL,
  `s_check` varchar(5) NOT NULL DEFAULT 'o',
  `s_location` int(5) NOT NULL,
  `m_id` int(10) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- 테이블의 덤프 데이터 `seat`
--

INSERT INTO `seat` (`s_id`, `s_check`, `s_location`, `m_id`) VALUES
(1, 'o', 0, 0),
(2, 'o', 1, 0),
(3, 'o', 2, 0),
(4, 'o', 3, 0),
(5, 'o', 4, 0),
(6, 'o', 5, 0),
(7, 'o', 6, 0),
(8, 'o', 7, 0),
(9, 'o', 8, 0),
(10, 'o', 9, 0),
(11, 'o', 10, 0),
(12, 'o', 11, 0),
(13, 'o', 12, 0),
(14, 'o', 13, 0),
(15, 'o', 14, 0),
(16, 'o', 15, 0),
(17, 'o', 16, 0),
(18, 'o', 17, 0),
(19, 'o', 18, 0),
(20, 'o', 19, 0),
(21, 'o', 20, 0),
(22, 'o', 21, 0),
(23, 'o', 22, 0),
(24, 'o', 23, 0),
(25, 'o', 24, 0),
(26, 'o', 25, 0),
(27, 'o', 26, 0),
(28, 'o', 27, 0),
(29, 'o', 28, 0),
(30, 'o', 29, 0),
(31, 'o', 30, 0),
(32, 'o', 31, 0),
(33, 'o', 32, 0),
(34, 'o', 33, 0),
(35, 'o', 34, 0),
(36, 'o', 35, 0),
(37, 'o', 36, 0),
(38, 'o', 37, 0),
(39, 'o', 38, 0),
(40, 'o', 39, 0),
(41, 'o', 40, 0),
(42, 'o', 41, 0),
(43, 'o', 42, 0),
(44, 'o', 43, 0),
(45, 'o', 44, 0),
(46, 'o', 45, 0),
(47, 'o', 46, 0),
(48, 'o', 47, 0),
(49, 'o', 48, 0),
(50, 'o', 49, 0);
