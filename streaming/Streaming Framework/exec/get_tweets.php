<?php
require "twitteroauth/autoloader.php";

use Abraham\TwitterOAuth\TwitterOAuth;

include ("../inc/base.php");

header("Content-type: text/javascript; charset=utf-8");
 
define('CONSUMER_KEY', 'xxxxxxxxxxxxxxxxxx');
define('CONSUMER_SECRET', 'xxxxxxxxxxxxxxxxxx');
define('ACCESS_TOKEN', 'xxxxxxxxxxxxxxxxxx-xxxxxxxxxxxxxxxxxx');
define('ACCESS_TOKEN_SECRET', 'xxxxxxxxxxxxxxxxxx');
 
function search(array $query){
  $toa = new TwitterOAuth(CONSUMER_KEY, CONSUMER_SECRET, ACCESS_TOKEN, ACCESS_TOKEN_SECRET);
  return $toa->get('search/tweets', $query);
}


// -------------------------------------------------

if ( (isset($_POST['tag'])) && ($_POST['tag']!="") ) {
	$search_tag = $_POST["tag"];

	$query = array(
	  "q" => $search_tag,
	  "count" => 10,
	  "result_type" => "recent",
	  "lang" => "es",
	);
	  
	$results = search($query);

	$return_elements = array();
	  
	foreach ($results->statuses as $result) {
	  array_push($return_elements,$result->text);
	}

	$return = return_array('exec_get_tweets', $return_elements, '', '', false, '', '', '');

	echo json_encode($return);

}

