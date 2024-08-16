-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Aug 04, 2024 at 02:22 PM
-- Server version: 10.4.32-MariaDB
-- PHP Version: 8.0.30

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `capstone`
--

-- --------------------------------------------------------

--
-- Table structure for table `location`
--

CREATE TABLE `location` (
  `userID` int(3) NOT NULL,
  `address` varchar(255) NOT NULL,
  `city` varchar(255) NOT NULL,
  `state` varchar(255) NOT NULL,
  `zipCode` mediumtext NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `location`
--

INSERT INTO `location` (`userID`, `address`, `city`, `state`, `zipCode`) VALUES
(5, '1 Apple Park Way', 'Cupertino', 'California', '95014'),
(6, '1 Apple Park Way', 'Cupertino', 'California', '95014'),
(7, '1038 East 480th Rd', 'Bolivar', 'Missouri', '65613');

-- --------------------------------------------------------

--
-- Table structure for table `randsalt`
--

CREATE TABLE `randsalt` (
  `randSalt` varchar(255) NOT NULL DEFAULT '$2y$10$iusesomecrazystrings12$'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `randsalt`
--

INSERT INTO `randsalt` (`randSalt`) VALUES
('$2y$10$iusesomecrazystrings12$');

-- --------------------------------------------------------

--
-- Table structure for table `userlegalname`
--

CREATE TABLE `userlegalname` (
  `userID` int(3) NOT NULL,
  `firstName` varchar(255) NOT NULL,
  `lastName` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `userlegalname`
--

INSERT INTO `userlegalname` (`userID`, `firstName`, `lastName`) VALUES
(5, 'Admin', 'Test'),
(6, 'Tim', 'Cook'),
(7, 'Treyton', 'Davis');

-- --------------------------------------------------------

--
-- Table structure for table `users`
--

CREATE TABLE `users` (
  `userID` int(3) NOT NULL,
  `username` varchar(255) NOT NULL,
  `password` varchar(255) NOT NULL,
  `email` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `users`
--

INSERT INTO `users` (`userID`, `username`, `password`, `email`) VALUES
(5, 'admin', '$2y$10$iusesomecrazystrings1uXO7iRYYmhDKgQnAVJ9NNgfHkP4irBv.', 'admin@admin.com'),
(6, 'tcook', '$2y$10$iusesomecrazystrings1u4acSIAjcAYsRdmTdWto5Ythd/VtgaBO', 'tcook@apple.com'),
(7, 'tdavis422', '$2y$10$iusesomecrazystrings1umA6V3uIbG84dCmthOYQenT5AlRZuYU.', 'treyton.davis@snhu.edu');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `location`
--
ALTER TABLE `location`
  ADD PRIMARY KEY (`userID`);

--
-- Indexes for table `userlegalname`
--
ALTER TABLE `userlegalname`
  ADD PRIMARY KEY (`userID`);

--
-- Indexes for table `users`
--
ALTER TABLE `users`
  ADD PRIMARY KEY (`userID`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `location`
--
ALTER TABLE `location`
  MODIFY `userID` int(3) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=8;

--
-- AUTO_INCREMENT for table `userlegalname`
--
ALTER TABLE `userlegalname`
  MODIFY `userID` int(3) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=8;

--
-- AUTO_INCREMENT for table `users`
--
ALTER TABLE `users`
  MODIFY `userID` int(3) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=8;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `location`
--
ALTER TABLE `location`
  ADD CONSTRAINT `location_ibfk_1` FOREIGN KEY (`userID`) REFERENCES `users` (`userID`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `userlegalname`
--
ALTER TABLE `userlegalname`
  ADD CONSTRAINT `userlegalname_ibfk_1` FOREIGN KEY (`userID`) REFERENCES `users` (`userID`) ON DELETE CASCADE ON UPDATE NO ACTION;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
