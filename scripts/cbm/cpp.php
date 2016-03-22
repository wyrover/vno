<?php

require_once("php_utils.php");

//包含所有enttity类的头文件
function begin_entity_head_file($file, $tables)
{
	fwrite($file, "#ifndef CBM_ALL_ENTITIES_H".ENTER);
	fwrite($file, "#define CBM_ALL_ENTITIES_H".ENTER);

	fwrite($file, ENTER."#include ".DBL_QUOT."Record.h".DBL_QUOT.ENTER);
	fwrite($file, ENTER."#include <vector>".ENTER);
	fwrite($file, "#include <boost/shared_ptr.hpp>".ENTER);
	fwrite($file, "using namespace boost;".ENTER);

	//开始定义命名空间
	fwrite($file, ENTER."namespace cbm {".TWO_ENTER);

	//前向声明
    foreach ($tables as $tbl_name => $fields) {
		//去掉cbm前缀,作为文件名
		$fname = table_no_prefix($tbl_name);
		//得到类名
		$clsname = camel_case($fname);

		fwrite($file, "class $clsname;".ENTER);
	}

	fwrite($file, ENTER);
	foreach ($tables as $tbl_name => $fields) {
		//去掉cbm前缀,作为文件名
		$fname = table_no_prefix($tbl_name);
		//得到类名
		$clsname = camel_case($fname);

		fwrite($file, "typedef boost::shared_ptr<$clsname> $clsname"."Ptr;".ENTER);
	}
	// fwrite($file, ENTER);
	// foreach ($tables as $tbl_name) {
	// 	//去掉cbm前缀,作为文件名
	// 	$fname = table_no_prefix($tbl_name);
	// 	//得到类名
	// 	$clsname = camel_case($fname);
	// 	fwrite($file, "typedef boost::shared_ptr< std::vector<$clsname"."Ptr> > $clsname"."List;".ENTER);
	// }
}

//包含所有enttity类的头文件
function end_entity_head_file($file, $tables)
{
	fwrite($file, ENTER."} // namespace cbm".ENTER);
	fwrite($file, ENTER."#endif // CBM_ALL_ENTITIES_H".ENTER);
}

//生成实体的头文件
function gen_entity_head_file($file, $tbl_name, $fields, $relations)
{
	//去掉cbm前缀,作为文件名
	$fname = table_no_prefix($tbl_name);

	//得到类名
	$clsname = camel_case($fname);

	fwrite($file, ENTER."class".DLL_EXPORT.$clsname." : public orm::Record".ENTER);
	fwrite($file, "{".ENTER);
	
	//静态成员函数
	fwrite($file, "public:".ENTER);
	fwrite($file, TAB."static CString Table();".ENTER);
	fwrite($file, TAB."static orm::RecordPtr Create();".ENTER);

	//成员函数
	fwrite($file, ENTER."public:".ENTER);
	//构造函数
    fwrite($file, TAB."$clsname();".ENTER);
	//生成成员变量定义
	// fwrite($file, ENTER."public:".ENTER);
	// //(1)1->n映射
 //    if(isset($relations[$tbl_name])) {
	// 	foreach ($relations[$tbl_name] as $name) {
	// 		$field_name = table_no_prefix($name);
	// 		$param_type = camel_case($field_name);
	// 		$var_name = $field_name;
	// 		fwrite($file, TAB."ObjGroup<$param_type> ".pluralize_word($var_name).";".ENTER);
	// 	}	
	// }
	//字段变量
	foreach ($fields as $name => $type) {
		$param_type = $type;
		$var_name = $name;
		$field_name = table_no_prefix(table_no_id($name));
		if($name == 'id') continue;
		//该字段是外键(所有的外键ID都是以_id结尾的)
		if($field_name != $name && $name != 'id') {
			//$param_type = camel_case($field_name)."Ptr";
			$param_type = "orm::RecordPtr";
			$var_name = $field_name;
		}
		fwrite($file, TAB.$param_type." ".$var_name.";".ENTER);
	}
	fwrite($file, ENTER."}; // class $clsname".ENTER);
}

function begin_entity_cpp_file($file, $tables)
{
	if(VC_PRECOM) {
		fwrite($file, "#include ".DBL_QUOT."stdafx.h".DBL_QUOT.ENTER);
	}
	fwrite($file, "#include ".DBL_QUOT."Entity.h".DBL_QUOT.ENTER);
	// fwrite($file, "#include <Util/HelperClass.h>".ENTER);

	//开始定义命名空间
	fwrite($file, ENTER."namespace cbm {".ENTER);
}

function end_entity_cpp_file($file, $tables)
{
	fwrite($file, ENTER."} // namespace cbm".ENTER);
}

//生成实体的源文件
function gen_entity_source_file($file, $tbl_name, $fields, $relations)
{
	//去掉cbm前缀,作为文件名
	$fname = table_no_prefix($tbl_name);
	//得到类名
	$clsname = camel_case($fname);

	fwrite($file, ENTER."CString $clsname::Table()".ENTER);
	fwrite($file, "{".ENTER);
	fwrite($file, TAB."return ".tchar($tbl_name).";".ENTER);
	fwrite($file, "}".ENTER);

	fwrite($file, ENTER."orm::RecordPtr $clsname::Create()".ENTER);
	fwrite($file, "{".ENTER);
	fwrite($file, TAB."return orm::RecordPtr(new $clsname());".ENTER);
	fwrite($file, "}".ENTER);

	//构造函数
    fwrite($file, ENTER."$clsname::$clsname() : orm::Record($clsname::Table())".ENTER);
    fwrite($file, "{".ENTER);

	//初始化成员变量
    foreach ($fields as $name => $type) {
		$param_type = $type;
		$var_name = $name;
		$field_name = table_no_prefix(table_no_id($name));
		if($name == 'id') continue;
		//该字段是外键(所有的外键ID都是以_id结尾的)
		if($field_name != $name && $name != 'id') {
			$param_type = camel_case($field_name);
			$var_name = $field_name;
		}
		else {
			$default_value = type_default($type);
    		fwrite($file, TAB.$name." = ".$default_value.";".ENTER);
    	}
	}

	//注册属性,并关联成员变量
	foreach ($fields as $name => $type) {
		$param_type = $type;
		$var_name = $name;
		$field_name = table_no_prefix(table_no_id($name));
		if($name == 'id') continue;
		//该字段是外键(所有的外键ID都是以_id结尾的)
		if($field_name != $name && $name != 'id') {
			$param_type = camel_case($field_name);
			$var_name = $field_name;
		}
		else {
			fwrite($file, TAB."REG_ATTRIB($name, $var_name);".ENTER);
		}
	}

    //注册属性,并关联成员变量
	foreach ($fields as $name => $type) {
		$param_type = $type;
		$var_name = $name;
		$field_name = table_no_prefix(table_no_id($name));
		if($name == 'id') continue;
		//该字段是外键(所有的外键ID都是以_id结尾的)
		if($field_name != $name && $name != 'id') {
			$param_type = camel_case($field_name);
			$var_name = $field_name;
			fwrite($file, TAB."REG_FOREGIN_KEY($name, $var_name, &$param_type::Create);".ENTER);
		}
	}
	
    fwrite($file, "}".ENTER);

}

function gen_dao_cpp_codes($tables, $relations)
{
	$entity_head_file = fopen('Entity.h', 'w');
	$entity_cpp_file = fopen('Entity.cpp', 'w');

	begin_entity_head_file($entity_head_file, $tables);
	begin_entity_cpp_file($entity_cpp_file, $tables);

	//查找表中的所有字段
	foreach($tables as $tbl => $fields) {    
		gen_entity_head_file($entity_head_file, $tbl, $fields, $relations);
		gen_entity_source_file($entity_cpp_file, $tbl, $fields, $relations);
	}

	end_entity_head_file($entity_head_file, $tables);
	end_entity_cpp_file($entity_cpp_file, $tables);

	fclose($entity_head_file);
	fclose($entity_cpp_file);
}

function make_cpp_files($tables, $relations)
{
	//生成c++代码
	gen_dao_cpp_codes($tables, $relations);
}

?>
