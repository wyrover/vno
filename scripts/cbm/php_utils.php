<?php

require("inflector.php");

//带双引号的逗号
define ('COMMA', "\",\"");
define ('SEMICOLON', "\";\"");
define ('STREAM', "<<");
define ('DBL_QUOT', "\"");
define ('SINGLE_QUOT', "\"'\"");
define ('ENTER', "\r\n");
define ('TWO_ENTER', "\r\n\r\n");
define ('THREE_ENTER', "\r\n\r\n\r\n");
define ('TAB', "\t");
define ('TWO_TAB', "\t\t");
define ('THREE_TAB', "\t\t\t");
define ('FOUR_TAB', "\t\t\t\t");
define ("ID_SUBFIX", "_id");
define ('VC_PRECOM', TRUE);
define ('DLL_EXPORT', " DAO_DLLIMPEXP ");
//define ('DLL_EXPORT', " ");

function tchar($str)
{
    return '_T('.DBL_QUOT.$str.DBL_QUOT.')';
}

//创建多级目录(递归)
function mkdirs($dir)
{
    if(!is_dir($dir)) {
        if(!mkdirs(dirname($dir))) {
            return false;
        }
        if(!mkdir($dir, 0777)) {
            return false;
        }
    }
    return true;  
}

//mkdirs('div/css/layout');

//用rmdir和unlink递归删除多级目录
function rmdirs($dir)  
{
    if(!is_dir($dir)) return;

    $d = dir($dir);  
    while (false !== ($child = $d->read())) {
        if($child != '.' && $child != '..') {
            if(is_dir($dir.'/'.$child)) {
                rmdirs($dir.'/'.$child);
            }
            else {
                unlink($dir.'/'.$child);
            }
        }
    }
    $d->close();
    rmdir($dir);
}

function camel_case($name)
{
	return str_replace(" ", "", ucwords(str_replace("_", " ", $name)));
}

//echo camel_case("cbm_adj_layer");

function cpp_type_to_thrift_type($type)
{
	//static $fields_dict = array("NEWDECIMAL" => "double", "LONG"=>"long", "VAR_STRING"=>"std::string", "LONGLONG"=>"long", "INT"=>"int");
    static $cpp_fields_dict = array("double" => "double", "int"=>"i32", "CString"=>"string", "string"=>"string", "long"=>"i64");
	return $cpp_fields_dict[$type];
}

function MYSQL_type_to_cpp_type($type)
{
    //static $fields_dict = array("NEWDECIMAL" => "double", "LONG"=>"long", "VAR_STRING"=>"std::string", "LONGLONG"=>"long", "INT"=>"int");
    static $mysql_fields_dict = array("NEWDECIMAL" => "double", "LONG"=>"int", "VAR_STRING"=>"CString", "LONGLONG"=>"long", "INT"=>"int");
    return $mysql_fields_dict[$type];
}

function type_default($type)
{
    //static $default_value_dict = array("int"=>"0", "double"=>"0.0", "long"=>"0", "std::string"=>"\"NULL\"", "string"=>"\"NULL\"", "float"=>"0.0f");
    static $default_value_dict = array("int"=>"0", "double"=>"0.0", "long"=>"0", "CString"=>"_T(\"\")", "float"=>"0.0f");
    return $default_value_dict[$type];
}

function cpp_type_to_py_type_func_dict($type)
{
    static $cpp_type_to_py_type_func_dict = array("int"=>"int", "double"=>"float", "long"=>"int", "CString"=>"str", "float"=>"float", "string"=>"str");
    return $cpp_type_to_py_type_func_dict[$type];
}

function h_type2txt($type_id)
{
    static $types;

    if (!isset($types)) {
        $types = array();
        $constants = get_defined_constants(true);
        foreach ($constants["mysqli"] as $c => $n) {
        	if (preg_match("/^MYSQLI_TYPE_(.*)/", $c, $m)) $types[$n] = $m[1];
        }
    }

    // var_dump($types);
    return array_key_exists($type_id, $types)? $types[$type_id] : NULL;
}

function h_flags2txt($flags_num)
{
    static $flags;

    if (!isset($flags)) {
        $flags = array();
        $constants = get_defined_constants(true);
        foreach ($constants["mysqli"] as $c => $n) {
        	if (preg_match("/MYSQLI_(.*)_FLAG$/", $c, $m)) if (!array_key_exists($n, $flags)) $flags[$n] = $m[1];
        }
    }

    $result = array();
    foreach ($flags as $n => $t) if ($flags_num & $n) $result[] = $t;
    return implode(" ", $result);
}

function table_no_prefix($name)
{
    $size = strlen("cbm_");
    $cbm = substr($name, 0, $size);
    // var_dump($cbm);
	$tbl_name = substr($name, $size, strlen($name)-$size);
    return ($cbm=='cbm_')?$tbl_name:$name;
}

function table_id($name)
{
	return table_no_prefix($name).ID_SUBFIX;
}

function table_no_id($name)
{
    $size = strlen(ID_SUBFIX);
	$id = substr($name, -1*$size);
	$tbl_name = substr($name, 0, -1*$size);
	return ($id == ID_SUBFIX)?$tbl_name:$name;
}

function obj_prefix($obj_name="")
{
	$prefix = $obj_name.".";
	if($obj_name == "" || $obj_name == "this") {
		$prefix = "(*this).";
	}
	return $prefix;
}

//单词变复数
function pluralize_word($word)
{
    $inflector = new Inflector();
    return $inflector->pluralize($word);
}
// var_dump(pluralize_word('cbm_tunnel'));

?>
