-- phpMyAdmin SQL Dump
-- version 4.2.6
-- http://www.phpmyadmin.net
--
-- Tiempo de generación: 21-01-2015 a las 12:11:21
-- Versión del servidor: 5.5.38-1~dotdeb.0-log
-- Versión de PHP: 5.3.29-1~dotdeb.0

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Base de datos: `hermetica`
--

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `herm3tica_data`
--

CREATE TABLE IF NOT EXISTS `herm3tica_data` (
`id` int(11) NOT NULL,
  `user_id` int(11) DEFAULT NULL,
  `data_name` varchar(32) DEFAULT NULL,
  `data_type` varchar(32) DEFAULT NULL,
  `data_bool` tinyint(1) DEFAULT NULL,
  `data_int` int(11) DEFAULT NULL,
  `data_float` float DEFAULT NULL,
  `data_string` varchar(255) DEFAULT NULL,
  `data_text` text DEFAULT NULL,
  `insert_datetime` datetime DEFAULT NULL
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=61 ;

--
-- Volcado de datos para la tabla `herm3tica_data`
--

INSERT INTO `herm3tica_data` (`id`, `user_id`, `data_name`, `data_type`, `data_bool`, `data_int`, `data_float`, `data_string`, `data_text`, `insert_datetime`) VALUES
(1, 1, 'test', 'bool', 0, 0, NULL, NULL, NULL, '2015-01-02 12:20:24'),
(52, 1, 'test', 'bool', 0, 0, NULL, NULL, NULL, '2015-01-20 16:55:24'),
(60, 2, 'testVLC', 'int', NULL, 12, NULL, NULL, NULL, '2015-01-21 12:10:30');
(4, 3, 'sierpinski', 'text', NULL, NULL, NULL, NULL, '6-1-0-12_12-1-0-4', '2015-02-15 12:10:41'),
(47, 3, 'sierpinski', 'text', NULL, NULL, NULL, NULL, '2-1-0-15_12-0-0-14', '2015-02-15 12:11:10'),
(63, 3, 'sierpinski', 'text', NULL, NULL, NULL, NULL, '7-0-0-17_12-0-0-17', '2015-02-15 12:11:32');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `herm3tica_stored_data`
--

CREATE TABLE IF NOT EXISTS `herm3tica_stored_data` (
`id` int(11) NOT NULL,
  `user_id` int(11) DEFAULT NULL,
  `stored_data` text
) ENGINE=MyISAM DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `herm3tica_user`
--

CREATE TABLE IF NOT EXISTS `herm3tica_user` (
`id` int(11) NOT NULL,
  `user_name` varchar(32) DEFAULT NULL
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=3 ;

--
-- Volcado de datos para la tabla `herm3tica_user`
--

INSERT INTO `herm3tica_user` (`id`, `user_name`) VALUES
(1, 'horacio'),
(2, 'n3m3da'),
(3, 'hermetica');

--
-- Índices para tablas volcadas
--

--
-- Indices de la tabla `herm3tica_data`
--
ALTER TABLE `herm3tica_data`
 ADD PRIMARY KEY (`id`);

--
-- Indices de la tabla `herm3tica_stored_data`
--
ALTER TABLE `herm3tica_stored_data`
 ADD PRIMARY KEY (`id`);

--
-- Indices de la tabla `herm3tica_user`
--
ALTER TABLE `herm3tica_user`
 ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT de las tablas volcadas
--

--
-- AUTO_INCREMENT de la tabla `herm3tica_data`
--
ALTER TABLE `herm3tica_data`
MODIFY `id` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=61;
--
-- AUTO_INCREMENT de la tabla `herm3tica_stored_data`
--
ALTER TABLE `herm3tica_stored_data`
MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT de la tabla `herm3tica_user`
--
ALTER TABLE `herm3tica_user`
MODIFY `id` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=3;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
