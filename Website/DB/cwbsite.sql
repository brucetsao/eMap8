-- phpMyAdmin SQL Dump
-- version 4.8.2
-- https://www.phpmyadmin.net/
--
-- 主機: localhost
-- 產生時間： 2021 年 05 月 28 日 12:27
-- 伺服器版本: 5.5.57-MariaDB
-- PHP 版本： 5.6.31

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- 資料庫： `ncnuiot`
--

-- --------------------------------------------------------

--
-- 資料表結構 `cwbsite`
--

CREATE TABLE `cwbsite` (
  `id` int(11) NOT NULL DEFAULT '0' COMMENT '主鍵',
  `dataorder` varchar(14) NOT NULL COMMENT '時間維度',
  `sysdatetime` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00' COMMENT '資料更新時間',
  `sid` varchar(20) NOT NULL COMMENT '站台ID',
  `sname` varchar(60) DEFAULT NULL COMMENT '站台名稱',
  `sdatetime` datetime NOT NULL COMMENT '資料時間',
  `lat` double NOT NULL COMMENT '緯度',
  `lon` double NOT NULL COMMENT '經度',
  `hight` int(11) NOT NULL COMMENT '海拔',
  `wdir` int(11) NOT NULL COMMENT '風向',
  `wspeed` int(11) NOT NULL COMMENT '風速',
  `temp` double NOT NULL COMMENT '溫度',
  `humid` double NOT NULL COMMENT '濕度',
  `bar` double NOT NULL COMMENT '氣壓',
  `rain` double NOT NULL COMMENT '雨量',
  `cid` varchar(14) NOT NULL COMMENT '縣市ID',
  `cname` varchar(40) DEFAULT NULL COMMENT '縣市名稱',
  `tid` varchar(14) NOT NULL COMMENT '鄉鎮ID',
  `tname` varchar(60) DEFAULT NULL COMMENT '鄉鎮名稱'
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- 資料表的匯出資料 `cwbsite`
--

INSERT INTO `cwbsite` (`id`, `dataorder`, `sysdatetime`, `sid`, `sname`, `sdatetime`, `lat`, `lon`, `hight`, `wdir`, `wspeed`, `temp`, `humid`, `bar`, `rain`, `cid`, `cname`, `tid`, `tname`) VALUES
(42, '20210528121002', '2020-03-03 14:41:05', 'C0A520', '山佳', '2021-05-28 12:00:00', 24.976719, 121.393789, 48, 249, 4, 36.6, 4.7, 1001.4, 0, '06', '新北市', '046', '樹林區'),
(130, '20210528121002', '2020-03-03 14:41:07', 'C0A530', '坪林', '2021-05-28 12:00:00', 24.939975, 121.701531, 300, -99, -99, -99, -990, -99, -99, '06', '新北市', '053', '坪林區');

--
-- 已匯出資料表的索引
--

--
-- 資料表索引 `cwbsite`
--
ALTER TABLE `cwbsite`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `sid` (`sid`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
