<?php
	// incluimos el documento que contiene todas las funciones
	include ("../inc/config.php");
	include ("../inc/db.php");
	include ("../inc/base.php");
	
	header("Content-type: text/javascript; charset=utf-8");
	
	if ( (isset($_POST['user_name'])) && ($_POST['user_name']!="") ) {
		$user_name = $_POST["user_name"];
	}
	if ( (isset($_GET['data_name'])) && ($_GET['data_name']!="") ) {
		$data_name = $_GET["data_name"];
	}
	if ( (isset($_GET['last'])) && ($_GET['last']=="true") ) {
		$last = true;
	}
	if ( (isset($_GET['stored'])) && ($_GET['stored']=="true") ) {
		$stored = true;
	}
	if ( (isset($_GET['all'])) && ($_GET['all']=="true") ) {
		$all = true;
	} else {
		$all = false;
	}
	((isset($_GET['timeoffset']))&&($_GET['timeoffset']!=""))  ? $timeoffset = intval($_GET["timeoffset"]) : $timeoffset = 20;
	if ( (isset($_GET['lang'])) && ($_GET['lang']!="") ) {
		include ("../inc/lang_".$_GET['lang'].".php");
	} else {
		include ("../inc/lang_es.php");
	}
	
	// echo "<pre>";
	if (isset($last)) {
		$now = time();
		$now -= $timeoffset;
		$date = date("o-m-d G:i:s", $now);
		// encontrar el usuario o crearlo si no existe
		$user = db_select_one($db_tables['user'], 'user_name', $user_name);
		if (!$user['error']) {
			// el usuario existe
			$user_id = $user['data']['id'];
			$read = db_select_all($db_tables['data'], 'insert_datetime', '>'.$date, '*insert_datetime');
			if (!$read['error']) {
				$elements = Array();
				$return_elements = Array();
				foreach ($read['data']['herm3tica_data'] as $element) {
					if (!in_array($element['id'], $elements)) {
    					array_push($elements, $element['id']);
    					array_push($return_elements, $element);
					}	
				}
				$return['data'] = $return_elements;
			} else {
				// error: 3 - no_db_entries_found.
				// $process_id, $data, $ui_msg, $dosql='', $error=FALSE, $type='', $tec_msg='', $error_process=''
				$return = return_array('exec_get_data', '', $read['msg'], $read['dosql'], true, 3, "There is no recent data being streamed", 'db_select_all');
			}
		} else {
			/// no error handling jet!!!
			$return = $user;
		}
		//print_r($return);
		echo json_encode($return);
	} else if (isset($stored)) {
		/*
		$project_id = 31;
		$reference_project = call_user_func('db_read_projects', $project_id, false);
		if (!$reference_project['error']) {
			$centro = LatLonToMeters(latLong($reference_project['data']['latitude'], $reference_project['data']['longitude']));
			$return = Array(
				'format' => 'stored',
				'id' => $reference_project['data']['id'],
				'title' => $reference_project['data']['title'],
				'latitude' => $reference_project['data']['latitude'],
				'longitude' => $reference_project['data']['longitude'],
				'x' => $centro['x'],
				'y' => $centro['y'],
				'zoom' => $reference_project['data']['zoom'],
				'levels' => $reference_project['data']['levels'],
				'data' => Array()
			);
			$read = db_select_all($db_tables['walkers_stored'],'','');
			if (!$read['error']) {
				$walkers_array = $read['data']['notours_walker_stored'];
				$n = 0;
				foreach ($walkers_array as $single_walker) {
					$single_walker_data = explode(";", $single_walker['data']);
					$new_single_walker_data = "";
					foreach ($single_walker_data as $position) {
						$position_data = explode(",", $position); 
						$meters = LatLonToMeters(latLong($position_data[0], $position_data[1]));
						$dif = dif($centro, $meters);
						$new_single_walker_data .= $position_data[0].",".$position_data[1].",".$position_data[2].";";
					}
					$walkers_array[$n]['data'] = $new_single_walker_data;
					$n++;
				}
				$return['data'] = $walkers_array;
			} else if ($read['error_type']==3) {
				$return = 'No walkers';
			} else {
				$return = $read;
			}
		} else {
			$return = $reference_project;
		}
		*/
		//print_r($return);
		echo json_encode($return);
	} else {
		// error: 10 - POST/GET vars missing.
		$error = return_array('exec_get_data', '', $write['data_missing'], '', true, 10, "Missing variables: \$_POST['user_name'] = '".$_POST['user_name']."', \$_POST['data_name'] = '".$_POST['data_name']."', \$_POST['last'] = '".$_POST['last']."', \$_POST['stored'] = '".$_POST['stored']."'.", 'exec_get_data');
		//print_r($error);
		echo json_encode($error);
	}
	// echo "</pre>";
?>