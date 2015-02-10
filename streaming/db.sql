-- phpMyAdmin SQL Dump
-- version 3.3.10.4
-- http://www.phpmyadmin.net
--
-- Servidor: mysql.test.escoitar.org
-- Tiempo de generación: 20-01-2015 a las 04:38:04
-- Versión del servidor: 5.1.56
-- Versión de PHP: 5.4.20

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";

--
-- Base de datos: `test_escoitar_db`
--

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

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `herm3tica_user`
--

CREATE TABLE IF NOT EXISTS `herm3tica_user` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `user_name` varchar(32) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=2 ;
