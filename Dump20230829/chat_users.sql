-- MySQL dump 10.13  Distrib 8.0.33, for Win64 (x86_64)
--
-- Host: localhost    Database: chat
-- ------------------------------------------------------
-- Server version	8.0.33

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `users` (
  `id` int NOT NULL AUTO_INCREMENT,
  `login` varchar(150) NOT NULL,
  `n_name` varchar(150) NOT NULL,
  `name` text NOT NULL,
  `family` text NOT NULL,
  `email` text NOT NULL,
  `status` int NOT NULL DEFAULT '1',
  PRIMARY KEY (`id`),
  UNIQUE KEY `login` (`login`),
  UNIQUE KEY `n_name` (`n_name`)
) ENGINE=InnoDB AUTO_INCREMENT=27 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
INSERT INTO `users` VALUES (1,'1','1','1','1','1',1),(8,'slawa','slawa','slawa','ivanov','ivanov@mail.ru',1),(9,'semen','semen','semen','semenov','semenov@mail.ru',1),(11,'2','2','2','2','2@mail.ru',1),(12,'admin','admin','admin','admin','admin@mail.ru',1),(13,'AndL','AndNN','AndN','AndF','And@mail.ru',1),(14,'SemL','SemNN','SemN','SemF','Sem@mail.ru',1),(15,'ffgdf','dfg','dfg','dfg','dfg',1),(16,'df','fd','fd','fd','fd',1),(17,'f','hf','hgf','hf','hf',1),(18,'fg','gd','dfg','fd','fd',1),(19,'AntonL','AntonNN','AntonN','AntonF','anto',1),(20,'Tester','Tester','Tester','Testerov','tes',1),(21,'Eric','Eric','Eric','Viking','Eric@north.se',1),(22,'Viking','Viking','Viking','Olaf','olaf@no',1),(23,'Viking1','Viking1','Viking','Baleog','Ba',1),(24,'boss','boss','boss','boss','boss@mail.ru',1),(25,'ttt','ttt','ttt','ttt','ttt',1),(26,'jjj','jjj','jjj','jjj','jjj',1);
/*!40000 ALTER TABLE `users` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2023-08-29  2:21:49
