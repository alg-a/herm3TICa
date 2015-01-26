<?php
	// incluimos el documento que contiene todas las funciones
	include ("../inc/config.php");
	include ("../inc/db.php");
	include ("../inc/base.php");
	
	// header("Content-type: text/javascript; charset=utf-8");
	header("Content-type: text/html; charset=utf-8");
	
	$store = null;
	$data_user = array();
	$fields_user = array('user_name','data_name');
	$data_text = '';
	$auth  = '';

	if((isset($_POST['auth_key']))){
		$auth = $_POST['auth_key'];
	}
	
	if ( (isset($_POST['store'])) && ($_POST['store']!="") ) {
		$store = false;
		if($_POST['store']=="true") $store = true;
	}
	
	for ($i=0; $i<count($fields_user); $i++) {
		if ( (isset($_POST[$fields_user[$i]])) && ($_POST[$fields_user[$i]]!="") ) {
			$data_user[$fields_user[$i]] = $_POST[$fields_user[$i]];
		}
		$data_text .= "\$_POST['".$fields_user[$i]."'] = '".$_POST[$fields_user[$i]]."', ";
	}
	$data_text = rtrim($data_text,", ");
	
	if ( (isset($_POST['lang'])) && ($_POST['lang']!="") ) {
		include ("../inc/lang_".$_POST['lang'].".php");
	} else {
		include ("../inc/lang_es.php");
	}
	
	// http://test.escoitar.org/exec/store_data.php?user_name=horacio&data_name=test&store=true&auth_key=****
	// echo "<pre>";
	if($auth === $auth_key) {
		if ((count($data_user)==count($fields_user))&&(isset($store))) {
			if (store) {
				// encontrar el usuario o crearlo si no existe
				$user = db_select_one($db_tables['user'], $fields_user[0], $data_user['user_name']);
				if (!$user['error']) {
					// el usuario existe
					$user_id = $user['data']['id'];
					$user_data = db_select_all($db_tables['data'], array('user_id', 'data_name'), array($user_id, $data_user['data_name']));
					if (!$user_data['error']) {
						$data = '';
						$type = $user_data['data']['herm3tica_data'][0]['data_type'];
						foreach ($user_data['data']['herm3tica_data'] as $d) {
    						$data .= $d['data_'.$d['data_type']].', '.$d['insert_datetime']."; ";
						}
						$data = trim($data);
						$insert = db_insert($db_tables['stored_data'], array('user_id'=>$user_id, 'stored_data'=>$data, 'data_name'=>$data_user['data_name'], 'data_type'=>$type));
						if (!$insert['error']) {
							// se han guardado los datos del usuario
							$delete = db_delete_all($db_tables['data'], array('user_id', 'data_name'), array($user_id, $data_user['data_name']));
							if (!$delete['error']) {
								// las entradas antiguas del usuario se han borrado correctamente
								//// print_r($delete);
							} else {
								// se ha producido un error al intentar borrar las entradas antiguas del usuario
								// print_r($delete);
								//echo json_encode($delete);
							}
						} else {
							// se ha producido un error al intentar guardar los datos del usuario
							// print_r($insert);
							echo json_encode($insert);
						}
					} else {
						$error = intval($user_data['error_type']);
						switch ($error) {
							case 3:
								// no hay datos de este usuario
								break;
							default:
								// se ha producido un error al intentar leer los datos de este usuario
								// print_r($user_data);
								echo json_encode($user_data);
								break;
						}
					}
				} else {
					$error = intval($user['error_type']);
					switch ($error) {
						case 3:
							// el usuario no existe
							break;
						default:
							// se ha producido un error al intentar comprobar si el usuario existe
							// print_r($user);
							echo json_encode($user);
							break;
					}
				}
			} else {
				// error: n(0???) - some variables have wrong values.
				$error = return_array('exec_store_data', '', $write['error_wrong_datavalue'], '', true, 0, "Wrong variables: \$_POST['user_name'] = '".$_POST['user_name']."', \$_POST['data_name'] = '".$_POST['data_name']."'.", 'exec_store_data');
				// print_r($error);
				echo json_encode($error);
			}
		} else {
			// error: 10 - POST/GET vars missing.
			$error = return_array('exec_store_data', '', $write['data_mising'], '', true, 10, "Mising variables: \$_POST['user_name'] = '".$_POST['user_name']."', \$_POST['data_name'] = '".$_POST['data_name']."'.", 'exec_store_data');
			// print_r($error);
			echo json_encode($error);
		}
	} else {
		// error: 11 - wrong auth_key
		$error = return_array('exec_store_data', '', $write['auth_missing'], '', true, 11, "Missing or wrong auth key: ".$auth.".", 'exec_update_data');
		// print_r($error);
		echo json_encode($error);
	}
	// echo "</pre>";
?>