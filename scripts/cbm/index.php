<?php

require_once("php_utils.php");
require_once("cpp.php");
require_once("thrift.php");
require_once("sql.php");

function build_cbm_tables()
{
	$tables = array();

	$mysqli = mysqli_connect("localhost", "root", "", "cbm");

	/* check connection */
	if (mysqli_connect_errno()) {
	    printf("Connect failed: %s\r\n", mysqli_connect_error());
	    exit();
	}

	//查找所有的表名
	$result = $mysqli->query("show tables");//执行查询语句
	while($arr = $result->fetch_assoc()) {
	    $tbl = $arr["Tables_in_cbm"];//遍历查询结果
	    if($tbl == 'cbm_dummy') continue;
	    $tables[$tbl]=array();
	}

	//查找表中的所有字段
	foreach(array_keys($tables) as $tbl) {
		$query = "SELECT * from $tbl";
		if ($result = mysqli_query($mysqli, $query)) {

		    /* Get field information for all columns */
		    $finfo = mysqli_fetch_fields($result);
		    $fields = array();
		    foreach ($finfo as $val) {
		        //类型编号映射成c++数据类型
		        // var_dump($tbl.'----'.h_type2txt($val->type));
		        $fields[$val->name] = MYSQL_type_to_cpp_type(h_type2txt($val->type));
		    }
		    $tables[$tbl] = $fields;
		    
		    mysqli_free_result($result);
		}
	}
	/* close connection */
	mysqli_close($mysqli);

	return $tables;
}

function build_tbl_relations(&$relations, $tbl_name, $fields)
{
	//去掉cbm前缀,作为文件名
	$fname = table_no_prefix($tbl_name);
	//得到类名
	$clsname = camel_case($fname);

	foreach ($fields as $name => $type) {
		$param_type = $type;
		$parent_tbl_name = table_no_id($name);
		$var_name = $name;
		$field_name = table_no_prefix($parent_tbl_name);
		if($name == 'id') continue;
		//该字段是外键(所有的外键ID都是以_id结尾的)
		if($field_name != $name && $name != 'id') {
			$param_type = camel_case($field_name);
			$var_name = $field_name;

			if(!isset($relations[$parent_tbl_name])) {
				$relations[$parent_tbl_name] = array();
			}
			var_dump($parent_tbl_name."-->".$tbl_name);
			$relations[$parent_tbl_name][] = $tbl_name;
		}
	}
	// var_dump($relations);
}

function build_cbm_relations($tables)
{
	$relations = array();

	//查找表中的所有字段
	foreach($tables as $tbl => $fields) {
	    //构造表关联
	    build_tbl_relations($relations, $tbl, $fields);
	}
	return $relations;
}

function copy_files()
{
	//项目路径(读取root.txt文件得到)
	$projDir = file_get_contents('root.txt');

	//将c++代码复制到cbm项目
	// copy('Entity.h', $projDir.'Dao\Entity.h');
	// copy('Entity.cpp', $projDir.'Dao\Entity.cpp');

	//将sql文件复制到cbm项目
	// copy('cbm-mysql.sql', $projDir.'scripts\sql\cbm-mysql.sql');
	// copy('cbm-data.sql', $projDir.'scripts\sql\cbm-data.sql');
	// copy('cbm.sql', $projDir.'scripts\sql\cbm.sql');

	//将php代码复制到cbm项目
	// copy('root.txt', $projDir.'php\cbm\root.txt');
	copy('index.php', $projDir.'scripts\cbm\index.php');
	copy('inflector.php', $projDir.'scripts\cbm\inflector.php');
	copy('php_utils.php', $projDir.'scripts\cbm\php_utils.php');
	copy('cpp.php', $projDir.'scripts\cbm\cpp.php');
	copy('thrift.php', $projDir.'scripts\cbm\thrift.php');
	copy('sql.php', $projDir.'scripts\cbm\sql.php');

	//将thrift接口文件复制到cbm项目
	copy('cbm.thrift', $projDir.'thrift\cbm.thrift');
	// copy('ctrl.thrift', $projDir.'thrift\ctrl.thrift');
	copy('SQLServerHelper.py', $projDir.'thrift\SQLServerHelper.py');
	copy('SQLClientHelper.py', $projDir.'thrift\SQLClientHelper.py');
	copy('CbmRtti.py', $projDir.'thrift\CbmRtti.py');
	copy('SQLClientHelper.h', $projDir.'thrift\SQLClientHelper.h');
	copy('SQLClientHelper.cpp', $projDir.'thrift\SQLClientHelper.cpp');
	copy('SQLClientHelper.php', $projDir.'thrift\SQLClientHelper.php');
}

//生成
$tables = build_cbm_tables();
//建立表关系映射
$relations = build_cbm_relations($tables);
//生成Entity.h和Entity.cpp文件
make_cpp_files($tables, $relations);
//生成cbm.thrift
make_thrift_files($tables, $relations);
merge_thrift_files();
//生成cbm_data.sql文件
// make_sql_files();
//复制文件到cbm/php目录下
copy_files();

?>
