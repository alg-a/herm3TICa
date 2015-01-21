-- phpMyAdmin SQL Dump
-- version 3.3.10.4
-- http://www.phpmyadmin.net
--
-- Versión del servidor: 5.1.56
-- Versión de PHP: 5.4.20

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `herm3tica_data`
--

CREATE TABLE IF NOT EXISTS `herm3tica_data` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `user_id` int(11) DEFAULT NULL,
  `data_name` varchar(32) DEFAULT NULL,
  `data_type` varchar(32) DEFAULT NULL,
  `data_bool` tinyint(1) DEFAULT NULL,
  `insert_datetime` datetime DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=51 ;

--
-- Volcar la base de datos para la tabla `herm3tica_data`
--

INSERT INTO `herm3tica_data` (`id`, `user_id`, `data_name`, `data_type`, `data_bool`, `insert_datetime`) VALUES
(1, 1, 'test', 'bool', 0, '2015-01-02 12:20:24');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `herm3tica_stored_data`
--

CREATE TABLE IF NOT EXISTS `herm3tica_stored_data` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `user_id` int(11) DEFAULT NULL,
  `stored_data` text,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

--
-- Volcar la base de datos para la tabla `herm3tica_stored_data`
--


-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `herm3tica_user`
--

CREATE TABLE IF NOT EXISTS `herm3tica_user` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `user_name` varchar(32) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=2 ;

--
-- Volcar la base de datos para la tabla `herm3tica_user`
--

INSERT INTO `herm3tica_user` (`id`, `user_name`) VALUES
(1, 'horacio');