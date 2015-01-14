<?php
	// incluimos el documento que contiene todas las funciones
	include ("../inc/config.php");
	include ("../inc/db.php");
	include ("../inc/base.php");
	
	//include ("../inc/noTours-db.php");
	
	header("Content-type: text/javascript; charset=utf-8");
	// header("Content-type: text/html; charset=utf-8");
	
	$data_user = array();
	$data = array();
	$project_id = null;
	$fields_user = array('user_name');
	$fields_data = array('data_name','data_type','data');
	$data_text = '';
	
	
	for ($i=0; $i<count($fields_user); $i++) {
		if ( (isset($_POST[$fields_user[$i]])) && ($_POST[$fields_user[$i]]!="") ) {
			$data_user[$fields_user[$i]] = $_POST[$fields_user[$i]];
		}
		$data_text .= "\$_POST['".$fields_user[$i]."'] = '".$_POST[$fields_user[$i]]."', ";
	}
	for ($i=0; $i<count($fields_data); $i++) {
		if ( (isset($_POST[$fields_data[$i]])) && ($_POST[$fields_data[$i]]!="") ) {
			$data[$fields_data[$i]] = $_POST[$fields_data[$i]];
		}
		$data_text .= "\$_POST['".$fields_data[$i]."'] = '".$_POST[$fields_data[$i]]."', ";
	}
	$data_text = rtrim($data_text,", ");
	
	if ( (isset($_POST['lang'])) && ($_POST['lang']!="") ) {
		include ("../inc/lang_".$_POST['lang'].".php");
	} else {
		include ("../inc/lang_es.php");
	}
	
	// echo "<pre>";
	if ((count($data)==count($fields_data))&&(count($data_user)==count($fields_user))) {
	
		// encontrar el usuario o crearlo si no existe
		$user = db_select_one($db_tables['user'], $fields_user, $data_user['name']);
		if (!$user['error']) {
			// el usuario existe
			$user_id = $user['data']['id'];
		} else {
			$error = intval($user['error_type']);
			switch ($error) {
				case 3:
					// el usuario no existe
					$insert = db_insert($db_tables['user'], $data_user);
					if (!$insert['error']) {
						// se ha creado un nuevo usuario
						$user_id = $insert['data'];
					} else {
						// se ha producido un error al crear un nuevo usuario
						$user_id = false;
						// print_r($insert);
						echo json_encode($insert);
					}
					break;
				default:
					// se ha producido un error al intentar comprobar si el usuario existe
					$user_id = false;
					// print_r($user);
					echo json_encode($user);
					break;
			}
		}
		
		if ($user_id) {
			$data['user_id'] = $user_id;
			$data['insert_datetime'] = date("o-m-d G:i:s");
			$data_value = $data['data'];
			unset($data['data']);
			switch ($data['data_type']) {
				case 'bool':
					$data['data_'.$data['data_type']] = getBoolValue($data_value);
        			break;
        		default:
        			$data['data_'.$data['data_type']] = $data_value;
			}
			$insert = db_insert($db_tables['data'], $data);
			$new_data = array_merge(array('id'=>$insert['data']), $data);
			$insert['data'] = $new_data;
			if (!$insert['error']) {
				// success
				$return = return_array('exec_update_data', $insert['data'], $write['success_updating_data'], $insert['dosql'], false, '', '', '');
			} else {
				// error 2: Invalid query
				$return = return_array('exec_update_data', $data, $write['error_inserting_data'].', '.$write['subprocess_error'], '', true, 7, '', 'db_insert');
				$return[ 'db_insert'] = $insert;
			}
			// print_r($return);
			echo json_encode($return);
		}
		
	} else {
		// error: 10 - POST/GET vars missing.
		$error = return_array('exec_update_data', '', $write['data_mising'], '', true, 10, "Mising variables: ".$data_text.".", 'exec_update_data');
		// print_r($error);
		echo json_encode($error);
	}
	// echo "</pre>";
?>