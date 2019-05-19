-- MySQL dump 10.13  Distrib 5.7.25, for Linux (x86_64)
--
-- Host: localhost    Database: SRS
-- ------------------------------------------------------
-- Server version	5.7.25-0ubuntu0.18.04.2

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `TbCourse`
--

DROP TABLE IF EXISTS `TbCourse`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `TbCourse` (
  `cosid` int(11) NOT NULL,
  `cosname` varchar(50) NOT NULL,
  `coscredit` tinyint(4) NOT NULL,
  `cosintro` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`cosid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `TbCourse`
--

LOCK TABLES `TbCourse` WRITE;
/*!40000 ALTER TABLE `TbCourse` DISABLE KEYS */;
INSERT INTO `TbCourse` VALUES (1111,'C语言程序设计',3,'大神级讲师授课需要抢座'),(2222,'Java程序设计',3,NULL),(3333,'数据库概论',2,NULL),(4444,'操作系统原理',4,NULL);
/*!40000 ALTER TABLE `TbCourse` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `TbSC`
--

DROP TABLE IF EXISTS `TbSC`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `TbSC` (
  `scid` int(11) NOT NULL AUTO_INCREMENT,
  `sid` int(11) NOT NULL,
  `cid` int(11) DEFAULT NULL,
  `scdate` datetime NOT NULL,
  `score` float DEFAULT NULL,
  PRIMARY KEY (`scid`),
  KEY `fk_sid` (`sid`),
  KEY `fk_cid` (`cid`),
  CONSTRAINT `fk_cid` FOREIGN KEY (`cid`) REFERENCES `TbCourse` (`cosid`) ON DELETE SET NULL ON UPDATE CASCADE,
  CONSTRAINT `fk_sid` FOREIGN KEY (`sid`) REFERENCES `TbStudent` (`stuid`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=19 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `TbSC`
--

LOCK TABLES `TbSC` WRITE;
/*!40000 ALTER TABLE `TbSC` DISABLE KEYS */;
INSERT INTO `TbSC` VALUES (1,1001,1111,'2016-09-01 00:00:00',95),(2,1002,1111,'2016-09-01 00:00:00',94),(3,1001,2222,'2019-04-30 21:16:22',NULL),(4,1001,3333,'2017-03-01 00:00:00',85),(5,1001,4444,'2019-04-30 21:16:22',NULL),(6,1002,4444,'2019-04-30 21:16:22',NULL),(7,1003,2222,'2019-04-30 21:16:22',NULL),(8,1003,3333,'2019-04-30 21:16:22',NULL),(9,1005,2222,'2019-04-30 21:16:22',NULL),(10,1006,1111,'2019-04-30 21:16:22',NULL),(11,1006,2222,'2017-03-01 00:00:00',80),(12,1006,3333,'2019-04-30 21:16:22',NULL),(13,1006,4444,'2019-04-30 21:16:22',NULL),(14,1007,1111,'2016-09-01 00:00:00',NULL),(15,1007,3333,'2019-04-30 21:16:22',NULL),(16,1007,4444,'2019-04-30 21:16:22',NULL),(17,1008,2222,'2019-04-30 21:16:22',NULL),(18,1010,1111,'2019-04-30 21:16:22',NULL);
/*!40000 ALTER TABLE `TbSC` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `TbStudent`
--

DROP TABLE IF EXISTS `TbStudent`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `TbStudent` (
  `stuid` int(11) NOT NULL,
  `stuname` varchar(20) NOT NULL,
  `stusex` bit(1) DEFAULT b'1',
  `stubirth` datetime NOT NULL,
  `stuaddr` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`stuid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `TbStudent`
--

LOCK TABLES `TbStudent` WRITE;
/*!40000 ALTER TABLE `TbStudent` DISABLE KEYS */;
INSERT INTO `TbStudent` VALUES (1001,'张三丰',_binary '','1978-01-01 00:00:00','成都市一环路西二段17号'),(1002,'郭靖',_binary '','1980-12-12 00:00:00','上海市宝山区同济支路199号'),(1003,'黄蓉',_binary '\0','1982-03-03 00:00:00','成都市二环路南四段123号'),(1004,'张无忌',_binary '','1990-04-04 00:00:00',NULL),(1005,'丘处机',_binary '','1983-05-05 00:00:00','北京市海淀区宝盛北里西区28号'),(1006,'王处一',_binary '','1985-06-06 00:00:00','深圳市宝安区宝安大道5010号'),(1007,'刘处玄',_binary '','1987-07-07 00:00:00','郑州市金水区纬五路21号'),(1008,'孙不二',_binary '\0','1989-08-08 00:00:00','武汉市光谷大道61号'),(1009,'平一指',_binary '','1992-09-09 00:00:00','西安市雁塔区高新六路52号'),(1010,'老不死',_binary '','1993-10-10 00:00:00','广州市天河区元岗路310号'),(1011,'王大锤',_binary '\0','1994-11-11 00:00:00',NULL),(1012,'隔壁老王',_binary '','1995-12-12 00:00:00',NULL),(1013,'郭啸天',_binary '','1977-10-25 00:00:00',NULL);
/*!40000 ALTER TABLE `TbStudent` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2019-04-30 21:39:06
