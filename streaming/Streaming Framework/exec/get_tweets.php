<?php
require "twitteroauth/autoloader.php";

use Abraham\TwitterOAuth\TwitterOAuth;

include ("../inc/base.php");

header("Content-type: text/javascript; charset=utf-8");
 
define('CONSUMER_KEY', 'S5CRkdg9ZrflXYH7vsw6Q');
define('CONSUMER_SECRET', 'np1KIdHQANRd5SwcTNgGjEP1IicXujfy4Uai0EecwnI');
define('ACCESS_TOKEN', '83389543-HYJ46ilEY84XyW7yIPRdr3VBMbrfEqMv5n2QjZ92q');
define('ACCESS_TOKEN_SECRET', 'kAACnBWVkv5SBeytsLWwpHbN8WN6mEYhGiUKYwZVt1AfF');
 
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

