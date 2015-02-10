<?php
/*!
 * Base Framework 1.02
 * 
 * Attribution-NonCommercial-ShareAlike 3.0
 * http://creativecommons.org/licenses/by-nc-sa/3.0/
 * 
 * Base Framework by Horacio González Diéguez
 * is licensed under a Creative Commons based on a work at
 * https://github.com/horaciogd/Base-Framework
 *
 * Date: Fri Jan 02 2015
 * 
 * enjoy the code and drop me a line for comments and questions!
 * horaciogd at vhplab dot net
 *
 */
 
/* DATABASE INFORMATION */

$auth_key = 'your_auth_key_here';

$db = array(
	"type" => "mysql",
	"host" => "localhost",
	"data" => "your_DB",
	"user" => "your_user",
	"pass" => "your_password"
);

$table_prefix  = 'tp_';

$db_tables = array(
	"user" => $table_prefix."user",
	"data" => $table_prefix."data",
	"stored_data" => $table_prefix."stored_data"
);

/* Global variables */
$root = "your web root";


?>