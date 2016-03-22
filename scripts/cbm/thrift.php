<?php

require_once("php_utils.php");

//生成实体的头文件
function __gen_entity_type_thrift($file, $tbl_name, $fields, $relations)
{
	//去掉cbm前缀,作为文件名
	$fname = table_no_prefix($tbl_name);

	//得到类名
	$clsname = camel_case($fname);

	fwrite($file, ENTER."struct ".$clsname." {".ENTER);
	
	//下标序号
	$count = 1;
	//字段变量
	foreach ($fields as $name => $type) {
		$param_type = cpp_type_to_thrift_type($type);
		$var_name = $name;
		$field_name = table_no_prefix(table_no_id($name));
		// if($name == 'id') continue;
		//该字段是外键(所有的外键ID都是以_id结尾的)
		// if($field_name != $name && $name != 'id') {
		// 	$param_type = "orm::RecordPtr";
		// 	$var_name = $field_name;
		// }
		fwrite($file, TAB.$count.": ".$param_type." ".$var_name);
		// if($count < count($fields)) {
			fwrite($file, ',');
		// }
		fwrite($file, ENTER);
		$count++;
	}
	fwrite($file, "}".ENTER);
}

function __gen_sql_service_thrift($file, $tbl_name, $fields, $relations)
{
	//去掉cbm前缀,作为文件名
	$fname = table_no_prefix($tbl_name);

	//得到类名
	$clsname = camel_case($fname);

	fwrite($file, TAB."//$clsname 类型的CRUD操作".ENTER);
	fwrite($file, TAB."i32 Add".$clsname."(1:$clsname $fname),".ENTER);
	fwrite($file, TAB."bool Delete".$clsname."(1:i32 id),".ENTER);
	fwrite($file, TAB."bool Update".$clsname."(1:$clsname $fname),".ENTER);
	fwrite($file, TAB."$clsname Get".$clsname."ById(1:i32 id),".ENTER);
	fwrite($file, TAB."$clsname Get".$clsname."ByForeignKey(1:string fkey, 2:i32 id),".ENTER);
	fwrite($file, TAB."i32 Get".$clsname."IdByForeignKey(1:string fkey, 2:i32 id),".ENTER);
	fwrite($file, TAB."list<$clsname> Get".$clsname."List(),".ENTER);
	fwrite($file, TAB."list<i32> Get".$clsname."Ids(),".ENTER);
	fwrite($file, TAB."list<string> Get".$clsname."Names(),".ENTER);
	fwrite($file, TAB."void AddMore".$clsname."(1:list<$clsname> objs),".ENTER);
	fwrite($file, TAB."void DeleteMore".$clsname."(1:list<i32> obj_ids),".ENTER);

	fwrite($file, TAB."$clsname Get".$clsname."ByFields(1:map<string, string> fields),".ENTER);
	fwrite($file, TAB."$clsname Get".$clsname."ByField1(1:string field, 2:string value),".ENTER);
	fwrite($file, TAB."$clsname Get".$clsname."ByField2(1:string field1, 2:string value1, 3:string field2, 4:string value2),".ENTER);

	fwrite($file, TAB."list<$clsname> Get".$clsname."ListByFields(1:map<string, string> fields),".ENTER);
	fwrite($file, TAB."list<$clsname> Get".$clsname."ListByField1(1:string field, 2:string value),".ENTER);
	fwrite($file, TAB."list<$clsname> Get".$clsname."ListByField2(1:string field1, 2:string value1, 3:string field2, 4:string value2),".ENTER);
	
	fwrite($file, TAB."i32 Get".$clsname."IdByFields(1:map<string, string> fields),".ENTER);
	fwrite($file, TAB."i32 Get".$clsname."IdByField1(1:string field, 2:string value),".ENTER);
	fwrite($file, TAB."i32 Get".$clsname."IdByField2(1:string field1, 2:string value1, 3:string field2, 4:string value2),".ENTER);

	fwrite($file, TAB."list<i32> Get".$clsname."IdListByFields(1:map<string, string> fields),".ENTER);
	fwrite($file, TAB."list<i32> Get".$clsname."IdListByField1(1:string field, 2:string value),".ENTER);
	fwrite($file, TAB."list<i32> Get".$clsname."IdListByField2(1:string field1, 2:string value1, 3:string field2, 4:string value2),".ENTER);

	fwrite($file, TAB."list<$clsname> Get".$clsname."ListByForeignKey(1:string fkey, 2:i32 id),".ENTER);
	fwrite($file, TAB."list<i32> Get".$clsname."IdListByForeignKey(1:string fkey, 2:i32 id),".ENTER);

	fwrite($file, ENTER);
}

function gen_entity_type_thrift($file, $tables, $relations)
{
	//查找表中的所有字段
	foreach($tables as $tbl => $fields) {
		__gen_entity_type_thrift($file, $tbl, $fields, $relations);
	}
}

function gen_sql_service_thrift($file, $tables, $relations)
{
	fwrite($file, ENTER.'//service SQLService {'.ENTER);
	foreach($tables as $tbl => $fields) {
		__gen_sql_service_thrift($file, $tbl, $fields, $relations);
	}
	fwrite($file, ENTER.'//}'.ENTER);
}

function __gen_sql_service_handler_of_py_server($file, $tbl_name, $fields, $relations)
{
	//去掉cbm前缀,作为文件名
	$fname = table_no_prefix($tbl_name);
	//得到类名
	$clsname = camel_case($fname);

	fwrite($file, TAB."#$clsname 类型的CRUD操作".ENTER);


	fwrite($file, TAB."def Add".$clsname."(self, $fname):".ENTER);
	fwrite($file, TWO_TAB."sql_obj = SQL.$clsname()".ENTER);
	fwrite($file, TWO_TAB."CbmUtil.CopyAttribsOfCbmType(".DBL_QUOT.$clsname.DBL_QUOT.", $fname, sql_obj, False)".ENTER);
	fwrite($file, TWO_TAB."sql_obj.id = None".ENTER);
    fwrite($file, TWO_TAB."self.session.add(sql_obj)".ENTER);
    fwrite($file, TWO_TAB."self.session.flush()".ENTER);
    fwrite($file, TWO_TAB."self.session.commit()".ENTER);
    fwrite($file, TWO_TAB."return sql_obj.id".ENTER);


	fwrite($file, TAB."def Delete".$clsname."(self, id):".ENTER);
	fwrite($file, TWO_TAB."ret=True".ENTER);
	fwrite($file, TWO_TAB."try:".ENTER);
	fwrite($file, THREE_TAB."self.session.query(SQL.$clsname).filter(SQL.$clsname.id==id).delete(synchronize_session=False)".ENTER);
	fwrite($file, THREE_TAB."self.session.commit()".ENTER);
	fwrite($file, TWO_TAB."except Exception, e:".ENTER);
	fwrite($file, THREE_TAB."print e".ENTER);
	fwrite($file, THREE_TAB."ret=False".ENTER);
	fwrite($file, TWO_TAB."return ret".ENTER);


	fwrite($file, TAB."def Update".$clsname."(self, $fname):".ENTER);
	fwrite($file, TWO_TAB."ret=True".ENTER);
	fwrite($file, TWO_TAB."try:".ENTER);
	fwrite($file, THREE_TAB."sql_obj = SQL.$clsname()".ENTER);
	fwrite($file, THREE_TAB."CbmUtil.CopyAttribsOfCbmType(".DBL_QUOT.$clsname.DBL_QUOT.", $fname, sql_obj, False)".ENTER);
	fwrite($file, THREE_TAB."attribs = CbmUtil.GetAttribsOfCbmType(".DBL_QUOT.$clsname.DBL_QUOT.", sql_obj)".ENTER);
	fwrite($file, THREE_TAB."del attribs['id']".ENTER);
	fwrite($file, THREE_TAB."self.session.query(SQL.$clsname).filter(SQL.$clsname.id==sql_obj.id).update(attribs, synchronize_session=False)".ENTER);
	fwrite($file, THREE_TAB."self.session.commit()".ENTER);
	fwrite($file, TWO_TAB."except Exception, e:".ENTER);
	fwrite($file, THREE_TAB."print e".ENTER);
	fwrite($file, THREE_TAB."ret=False".ENTER);
	fwrite($file, TWO_TAB."return ret".ENTER);


	fwrite($file, TAB."def Get".$clsname."ById(self, id):".ENTER);
	fwrite($file, TWO_TAB."query=self.session.query(SQL.$clsname).filter(SQL.$clsname.id==id).first()".ENTER);
	fwrite($file, TWO_TAB."obj = $clsname()".ENTER);
	fwrite($file, TWO_TAB."if query is None:".ENTER);
	fwrite($file, THREE_TAB."obj.id = -1".ENTER);
	fwrite($file, TWO_TAB."else:".ENTER);
	fwrite($file, THREE_TAB."CbmUtil.CopyAttribsOfCbmType(".DBL_QUOT.$clsname.DBL_QUOT.", query, obj, True)".ENTER);
	fwrite($file, TWO_TAB."return obj".ENTER);

	
	fwrite($file, TAB."def Get".$clsname."ByForeignKey(self, fkey, id):".ENTER);
	fwrite($file, TWO_TAB."return self.Get".$clsname."ByFields({fkey:id})".ENTER);


	fwrite($file, TAB."def Get".$clsname."IdByForeignKey(self, fkey, id):".ENTER);
	fwrite($file, TWO_TAB."return self.Get".$clsname."IdByFields({fkey:id})".ENTER);


	fwrite($file, TAB."def Get".$clsname."List(self):".ENTER);
	fwrite($file, TWO_TAB."query = self.session.query(SQL.$clsname).order_by(SQL.$clsname.id).all()".ENTER);
	fwrite($file, TWO_TAB."n = len(query)".ENTER);
	fwrite($file, TWO_TAB."obj_list = [$clsname() for i in range(n)]".ENTER);
    fwrite($file, TWO_TAB."for i in range(n):".ENTER);
    fwrite($file, THREE_TAB."CbmUtil.CopyAttribsOfCbmType(".DBL_QUOT.$clsname.DBL_QUOT.", query[i], obj_list[i], True)".ENTER);
    fwrite($file, TWO_TAB."return obj_list".ENTER);

	
	fwrite($file, TAB."def Get".$clsname."Ids(self):".ENTER);
	fwrite($file, TWO_TAB."query=self.session.query(SQL.$clsname).order_by(SQL.$clsname.id).all()".ENTER);
	fwrite($file, TWO_TAB."return [obj.id for obj in query]".ENTER);
	

    fwrite($file, TAB."def Get".$clsname."Names(self):".ENTER);
	fwrite($file, TWO_TAB."query=self.session.query(SQL.$clsname).all()".ENTER);
	fwrite($file, TWO_TAB."if len(query) == 0 or not hasattr(query[0], 'name'):".ENTER);
	fwrite($file, THREE_TAB."return []".ENTER);
	fwrite($file, TWO_TAB."else:".ENTER);
	fwrite($file, THREE_TAB."return [obj.name for obj in query]".ENTER);

	fwrite($file, TAB."def AddMore".$clsname."(self, objs):".ENTER);
	fwrite($file, TWO_TAB."n = len(objs)".ENTER);
	fwrite($file, TWO_TAB."sql_objs = [SQL.$clsname() for i in range(n)]".ENTER);
    fwrite($file, TWO_TAB."for i in range(n):".ENTER);
    fwrite($file, THREE_TAB."CbmUtil.CopyAttribsOfCbmType(".DBL_QUOT.$clsname.DBL_QUOT.", objs[i], sql_objs[i], False)".ENTER);
    fwrite($file, THREE_TAB."sql_objs[i].id = None".ENTER);
    fwrite($file, THREE_TAB."self.session.add(sql_objs[i])".ENTER);
    fwrite($file, TWO_TAB."self.session.flush()".ENTER);
    fwrite($file, TWO_TAB."self.session.commit()".ENTER);


	fwrite($file, TAB."def DeleteMore".$clsname."(self, obj_ids):".ENTER);
	fwrite($file, TWO_TAB."if len(obj_ids) == 0:return".ENTER);
	fwrite($file, TWO_TAB."self.session.query(SQL.$clsname).filter(SQL.$clsname.id.in_(obj_ids)).delete(synchronize_session=False)".ENTER);
	fwrite($file, TWO_TAB."self.session.commit()".ENTER);
	
	
	fwrite($file, TAB."def __Get".$clsname."ByFields(self, fields):".ENTER);
	fwrite($file, TWO_TAB."sql_fields = CbmUtil.map_fields(".DBL_QUOT.$clsname.DBL_QUOT.", fields)".ENTER);
	fwrite($file, TWO_TAB."query = self.session.query(SQL.$clsname).filter_by(**sql_fields).order_by(SQL.$clsname.id).all()".ENTER);
	fwrite($file, TWO_TAB."if len(query) == 0:".ENTER);
	fwrite($file, THREE_TAB."return []".ENTER);
	fwrite($file, TWO_TAB."else:".ENTER);
	fwrite($file, THREE_TAB."n = len(query)".ENTER);
	fwrite($file, THREE_TAB."obj_list = [$clsname() for i in range(n)]".ENTER);
    fwrite($file, THREE_TAB."for i in range(n):".ENTER);
    fwrite($file, TWO_TAB.TWO_TAB."CbmUtil.CopyAttribsOfCbmType(".DBL_QUOT.$clsname.DBL_QUOT.", query[i], obj_list[i], True)".ENTER);
    fwrite($file, THREE_TAB."return obj_list".ENTER);


    fwrite($file, TAB."def __Get".$clsname."IdsByFields(self, fields):".ENTER);
    fwrite($file, TWO_TAB."sql_fields = CbmUtil.map_fields(".DBL_QUOT.$clsname.DBL_QUOT.", fields)".ENTER);
	fwrite($file, TWO_TAB."query = self.session.query(SQL.$clsname).filter_by(**sql_fields).order_by(SQL.$clsname.id).all()".ENTER);
	fwrite($file, TWO_TAB."if len(query) == 0:".ENTER);
	fwrite($file, THREE_TAB."return []".ENTER);
	fwrite($file, TWO_TAB."else:".ENTER);
	fwrite($file, THREE_TAB."return [obj.id for obj in query]".ENTER);
	

	fwrite($file, TAB."def Get".$clsname."ByFields(self, fields):".ENTER);
	fwrite($file, TWO_TAB."objs = self.__Get".$clsname."ByFields(fields)".ENTER);
	fwrite($file, TWO_TAB."if len(objs) == 0:".ENTER);
	fwrite($file, THREE_TAB."obj = $clsname()".ENTER);
	fwrite($file, THREE_TAB."obj.id = -1".ENTER);
	fwrite($file, THREE_TAB."return obj".ENTER);
	fwrite($file, TWO_TAB."else:".ENTER);
	fwrite($file, THREE_TAB."return objs[0]".ENTER);


	fwrite($file, TAB."def Get".$clsname."ByField1(self, field, value):".ENTER);
	fwrite($file, TWO_TAB."return self.Get".$clsname."ByFields({field:value})".ENTER);

	fwrite($file, TAB."def Get".$clsname."ByField2(self, field1, value1, field2, value2):".ENTER);
	fwrite($file, TWO_TAB."return self.Get".$clsname."ByFields({field1:value1, field2:value2})".ENTER);

	fwrite($file, TAB."def Get".$clsname."ListByFields(self, fields):".ENTER);
	fwrite($file, TWO_TAB."return self.__Get".$clsname."ByFields(fields)".ENTER);

	fwrite($file, TAB."def Get".$clsname."ListByField1(self, field, value):".ENTER);
	fwrite($file, TWO_TAB."return self.Get".$clsname."ListByFields({field:value})".ENTER);

	fwrite($file, TAB."def Get".$clsname."ListByField2(self, field1, value1, field2, value2):".ENTER);
	fwrite($file, TWO_TAB."return self.Get".$clsname."ListByFields({field1:value1, field2:value2})".ENTER);


	fwrite($file, TAB."def Get".$clsname."IdByFields(self, fields):".ENTER);
	fwrite($file, TWO_TAB."obj_ids = self.__Get".$clsname."IdsByFields(fields)".ENTER);
	fwrite($file, TWO_TAB."if len(obj_ids) == 0:".ENTER);
	fwrite($file, THREE_TAB."return -1".ENTER);
	fwrite($file, TWO_TAB."else:".ENTER);
	fwrite($file, THREE_TAB."return obj_ids[0]".ENTER);


	fwrite($file, TAB."def Get".$clsname."IdByField1(self, field, value):".ENTER);
	fwrite($file, TWO_TAB."return self.Get".$clsname."IdByFields({field:value})".ENTER);

	fwrite($file, TAB."def Get".$clsname."IdByField2(self, field1, value1, field2, value2):".ENTER);
	fwrite($file, TWO_TAB."return self.Get".$clsname."IdByFields({field1:value1, field2:value2})".ENTER);

	fwrite($file, TAB."def Get".$clsname."IdListByFields(self, fields):".ENTER);
	fwrite($file, TWO_TAB."return self.__Get".$clsname."IdsByFields(fields)".ENTER);

	fwrite($file, TAB."def Get".$clsname."IdListByField1(self, field, value):".ENTER);
	fwrite($file, TWO_TAB."return self.Get".$clsname."IdListByFields({field:value})".ENTER);

	fwrite($file, TAB."def Get".$clsname."IdListByField2(self, field1, value1, field2, value2):".ENTER);
	fwrite($file, TWO_TAB."return self.Get".$clsname."IdListByFields({field1:value1, field2:value2})".ENTER);

	fwrite($file, TAB."def Get".$clsname."ListByForeignKey(self, fkey, id):".ENTER);
	fwrite($file, TWO_TAB."return self.Get".$clsname."ListByFields({fkey:id})".ENTER);

	fwrite($file, TAB."def Get".$clsname."IdListByForeignKey(self, fkey, id):".ENTER);
	fwrite($file, TWO_TAB."return self.Get".$clsname."IdListByFields({fkey:id})".ENTER);

	fwrite($file, ENTER);
}


function gen_sql_service_handler_of_py_server($file, $tables, $relations)
{
	fwrite($file, '#-*- coding:utf-8 -*-'.TWO_ENTER);
	fwrite($file, 'from cbm.ttypes import *'.ENTER);
	fwrite($file, 'import SQL'.ENTER);
	fwrite($file, 'import CbmUtil'.ENTER);

	fwrite($file, TWO_ENTER.'class SQLServiceHandler(object):'.ENTER);
	fwrite($file, TAB.'def __init__(self, session):'.ENTER);
	fwrite($file, TWO_TAB.'self.session = session'.TWO_ENTER);

	foreach($tables as $tbl => $fields) {
		__gen_sql_service_handler_of_py_server($file, $tbl, $fields, $relations);
	}
}

function __gen_sql_helper_of_hpp_client($file, $tbl_name, $fields, $relations)
{
	//去掉cbm前缀,作为文件名
	$fname = table_no_prefix($tbl_name);

	//得到类名
	$clsname = camel_case($fname);

	fwrite($file, TAB."//$clsname 类型的CRUD操作".ENTER);

	fwrite($file, TAB."static int32_t Add".$clsname."(const cbm::$clsname & $fname);".ENTER);
	fwrite($file, TAB."static bool Delete".$clsname."(const int32_t id);".ENTER);
	fwrite($file, TAB."static bool Update".$clsname."(const cbm::$clsname & $fname);".ENTER);
	fwrite($file, TAB."static void Get".$clsname."ById(cbm::$clsname & _return, const int32_t id);".ENTER);
	fwrite($file, TAB."static void Get".$clsname."ByForeignKey(cbm::$clsname & _return, const std::string& fkey, const int32_t id);".ENTER);
	fwrite($file, TAB."static int32_t Get".$clsname."IdByForeignKey(const std::string& fkey, const int32_t id);".ENTER);
	fwrite($file, TAB."static void Get".$clsname."List(std::vector<cbm::$clsname> & _return);".ENTER);
	fwrite($file, TAB."static void Get".$clsname."Ids(std::vector<int32_t> & _return);".ENTER);	
    fwrite($file, TAB."static void Get".$clsname."Names(std::vector<std::string> & _return);".ENTER);
	fwrite($file, TAB."static void AddMore".$clsname."(const std::vector<cbm::$clsname> & objs);".ENTER);
	fwrite($file, TAB."static void DeleteMore".$clsname."(const std::vector<int32_t> & obj_ids);".ENTER);
	fwrite($file, TAB."static void Get".$clsname."ByFields(cbm::$clsname & _return, const std::map<std::string, std::string> & fields);".ENTER);
	fwrite($file, TAB."static void Get".$clsname."ByField1(cbm::$clsname & _return, const std::string& field, const std::string& value);".ENTER);
	fwrite($file, TAB."static void Get".$clsname."ByField2(cbm::$clsname & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2);".ENTER);
	fwrite($file, TAB."static void Get".$clsname."ListByFields(std::vector<cbm::$clsname> & _return, const std::map<std::string, std::string> & fields);".ENTER);
	fwrite($file, TAB."static void Get".$clsname."ListByField1(std::vector<cbm::$clsname> & _return, const std::string& field, const std::string& value);".ENTER);
	fwrite($file, TAB."static void Get".$clsname."ListByField2(std::vector<cbm::$clsname> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2);".ENTER);
	fwrite($file, TAB."static int32_t Get".$clsname."IdByFields(const std::map<std::string, std::string> & fields);".ENTER);
	fwrite($file, TAB."static int32_t Get".$clsname."IdByField1(const std::string& field, const std::string& value);".ENTER);
	fwrite($file, TAB."static int32_t Get".$clsname."IdByField2(const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2);".ENTER);
	fwrite($file, TAB."static void Get".$clsname."IdListByFields(std::vector<int32_t> & _return, const std::map<std::string, std::string> & fields);".ENTER);
	fwrite($file, TAB."static void Get".$clsname."IdListByField1(std::vector<int32_t> & _return, const std::string& field, const std::string& value);".ENTER);
	fwrite($file, TAB."static void Get".$clsname."IdListByField2(std::vector<int32_t> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2);".ENTER);

	fwrite($file, TAB."static void Get".$clsname."ListByForeignKey(std::vector<cbm::$clsname> & _return, const std::string& fkey, const int32_t id);".ENTER);
	fwrite($file, TAB."static void Get".$clsname."IdListByForeignKey(std::vector<int32_t> & _return, const std::string& fkey, const int32_t id);".ENTER);

	fwrite($file, ENTER);
}

function __gen_sql_helper_of_cpp_client($file, $tbl_name, $fields, $relations)
{
	//去掉cbm前缀,作为文件名
	$fname = table_no_prefix($tbl_name);

	//得到类名
	$clsname = camel_case($fname);

	fwrite($file, "//$clsname 类型的CRUD操作".ENTER);

	fwrite($file, "int32_t SQLClientHelper::Add".$clsname."(const cbm::$clsname & $fname) {".ENTER);
	fwrite($file, TAB."int32_t ret = -1;".ENTER);
	fwrite($file, TAB."try {".ENTER);
	fwrite($file, TWO_TAB."RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);".ENTER);
	fwrite($file, TWO_TAB."service_client.start();".ENTER);
	fwrite($file, TWO_TAB."ret = service_client.get()->Add".$clsname."($fname);".ENTER);
	fwrite($file, TWO_TAB."service_client.close();".ENTER);
	fwrite($file, TAB."}".ENTER);
	fwrite($file, TAB."catch (TException &tx) {".ENTER);
	fwrite($file, TWO_TAB."std::string error_msg = tx.what();".ENTER);
	fwrite($file, TWO_TAB."ret = -1;".ENTER);
	fwrite($file, TAB."}".ENTER);
	fwrite($file, TAB."return ret;".ENTER);
	fwrite($file, "}".ENTER);
 

	fwrite($file, "bool SQLClientHelper::Delete".$clsname."(const int32_t id) {".ENTER);
	fwrite($file, TAB."bool ret = false;".ENTER);
	fwrite($file, TAB."try {".ENTER);
	fwrite($file, TWO_TAB."RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);".ENTER);
	fwrite($file, TWO_TAB."service_client.start();".ENTER);
	fwrite($file, TWO_TAB."ret = service_client.get()->Delete".$clsname."(id);".ENTER);
	fwrite($file, TWO_TAB."service_client.close();".ENTER);
	fwrite($file, TAB."}".ENTER);
	fwrite($file, TAB."catch (TException &tx) {".ENTER);
	fwrite($file, TWO_TAB."std::string error_msg = tx.what();".ENTER);
	fwrite($file, TWO_TAB."ret = false;".ENTER);
	fwrite($file, TAB."}".ENTER);
	fwrite($file, TAB."return ret;".ENTER);
	fwrite($file, "}".ENTER);


	fwrite($file, "bool SQLClientHelper::Update".$clsname."(const cbm::$clsname & $fname) {".ENTER);
	fwrite($file, TAB."bool ret = false;".ENTER);
	fwrite($file, TAB."try {".ENTER);
	fwrite($file, TWO_TAB."RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);".ENTER);
	fwrite($file, TWO_TAB."service_client.start();".ENTER);
	fwrite($file, TWO_TAB."ret = service_client.get()->Update".$clsname."($fname);".ENTER);
	fwrite($file, TWO_TAB."service_client.close();".ENTER);
	fwrite($file, TAB."}".ENTER);
	fwrite($file, TAB."catch (TException &tx) {".ENTER);
	fwrite($file, TWO_TAB."std::string error_msg = tx.what();".ENTER);
	fwrite($file, TWO_TAB."ret = false;".ENTER);
	fwrite($file, TAB."}".ENTER);
	fwrite($file, TAB."return ret;".ENTER);
	fwrite($file, "}".ENTER);


	fwrite($file, "void SQLClientHelper::Get".$clsname."ById(cbm::$clsname & _return, const int32_t id) {".ENTER);
	fwrite($file, TAB."try {".ENTER);
	fwrite($file, TWO_TAB."RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);".ENTER);
	fwrite($file, TWO_TAB."service_client.start();".ENTER);
	fwrite($file, TWO_TAB."service_client.get()->Get".$clsname."ById(_return, id);".ENTER);
	fwrite($file, TWO_TAB."service_client.close();".ENTER);
	fwrite($file, TAB."}".ENTER);
	fwrite($file, TAB."catch (TException &tx) {".ENTER);
	fwrite($file, TWO_TAB."std::string error_msg = tx.what();".ENTER);
	fwrite($file, TAB."}".ENTER);
	fwrite($file, "}".ENTER);

	
	fwrite($file, "void SQLClientHelper::Get".$clsname."ByForeignKey(cbm::$clsname & _return, const std::string& fkey, const int32_t id) {".ENTER);
	fwrite($file, TAB."try {".ENTER);
	fwrite($file, TWO_TAB."RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);".ENTER);
	fwrite($file, TWO_TAB."service_client.start();".ENTER);
	fwrite($file, TWO_TAB."service_client.get()->Get".$clsname."ByForeignKey(_return, fkey, id);".ENTER);
	fwrite($file, TWO_TAB."service_client.close();".ENTER);
	fwrite($file, TAB."}".ENTER);
	fwrite($file, TAB."catch (TException &tx) {".ENTER);
	fwrite($file, TWO_TAB."std::string error_msg = tx.what();".ENTER);
	fwrite($file, TAB."}".ENTER);
	fwrite($file, "}".ENTER);


	fwrite($file, "int32_t SQLClientHelper::Get".$clsname."IdByForeignKey(const std::string& fkey, const int32_t id) {".ENTER);
	fwrite($file, TAB."int32_t ret = -1;".ENTER);
	fwrite($file, TAB."try {".ENTER);
	fwrite($file, TWO_TAB."RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);".ENTER);
	fwrite($file, TWO_TAB."service_client.start();".ENTER);
	fwrite($file, TWO_TAB."ret = service_client.get()->Get".$clsname."IdByForeignKey(fkey, id);".ENTER);
	fwrite($file, TWO_TAB."service_client.close();".ENTER);
	fwrite($file, TAB."}".ENTER);
	fwrite($file, TAB."catch (TException &tx) {".ENTER);
	fwrite($file, TWO_TAB."std::string error_msg = tx.what();".ENTER);
	fwrite($file, TWO_TAB."ret = -1;".ENTER);
	fwrite($file, TAB."}".ENTER);
	fwrite($file, "return ret;".ENTER);
	fwrite($file, "}".ENTER);
	

	fwrite($file, "void SQLClientHelper::Get".$clsname."List(std::vector<cbm::$clsname> & _return) {".ENTER);
	fwrite($file, TAB."try {".ENTER);
	fwrite($file, TWO_TAB."RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);".ENTER);
	fwrite($file, TWO_TAB."service_client.start();".ENTER);
	fwrite($file, TWO_TAB."service_client.get()->Get".$clsname."List(_return);".ENTER);
	fwrite($file, TWO_TAB."service_client.close();".ENTER);
	fwrite($file, TAB."}".ENTER);
	fwrite($file, TAB."catch (TException &tx) {".ENTER);
	fwrite($file, TWO_TAB."std::string error_msg = tx.what();".ENTER);
	fwrite($file, TAB."}".ENTER);
	fwrite($file, "}".ENTER);

	
	fwrite($file, "void SQLClientHelper::Get".$clsname."Ids(std::vector<int32_t> & _return) {".ENTER);
	fwrite($file, TAB."try {".ENTER);
	fwrite($file, TWO_TAB."RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);".ENTER);
	fwrite($file, TWO_TAB."service_client.start();".ENTER);
	fwrite($file, TWO_TAB."service_client.get()->Get".$clsname."Ids(_return);".ENTER);
	fwrite($file, TWO_TAB."service_client.close();".ENTER);
	fwrite($file, TAB."}".ENTER);
	fwrite($file, TAB."catch (TException &tx) {".ENTER);
	fwrite($file, TWO_TAB."std::string error_msg = tx.what();".ENTER);
	fwrite($file, TAB."}".ENTER);
	fwrite($file, "}".ENTER);
	

    fwrite($file, "void SQLClientHelper::Get".$clsname."Names(std::vector<std::string> & _return) {".ENTER);
	fwrite($file, TAB."try {".ENTER);
	fwrite($file, TWO_TAB."RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);".ENTER);
	fwrite($file, TWO_TAB."service_client.start();".ENTER);
	fwrite($file, TWO_TAB."service_client.get()->Get".$clsname."Names(_return);".ENTER);
	fwrite($file, TWO_TAB."service_client.close();".ENTER);
	fwrite($file, TAB."}".ENTER);
	fwrite($file, TAB."catch (TException &tx) {".ENTER);
	fwrite($file, TWO_TAB."std::string error_msg = tx.what();".ENTER);
	fwrite($file, TAB."}".ENTER);
	fwrite($file, "}".ENTER);


	fwrite($file, "void SQLClientHelper::AddMore".$clsname."(const std::vector<cbm::$clsname> & objs) {".ENTER);
	fwrite($file, TAB."try {".ENTER);
	fwrite($file, TWO_TAB."RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);".ENTER);
	fwrite($file, TWO_TAB."service_client.start();".ENTER);
	fwrite($file, TWO_TAB."service_client.get()->AddMore".$clsname."(objs);".ENTER);
	fwrite($file, TWO_TAB."service_client.close();".ENTER);
	fwrite($file, TAB."}".ENTER);
	fwrite($file, TAB."catch (TException &tx) {".ENTER);
	fwrite($file, TWO_TAB."std::string error_msg = tx.what();".ENTER);
	fwrite($file, TAB."}".ENTER);
	fwrite($file, "}".ENTER);

	fwrite($file, "void SQLClientHelper::DeleteMore".$clsname."(const std::vector<int32_t> & obj_ids) {".ENTER);
	fwrite($file, TAB."if(obj_ids.empty()) return;".ENTER);
	fwrite($file, TAB."try {".ENTER);
	fwrite($file, TWO_TAB."RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);".ENTER);
	fwrite($file, TWO_TAB."service_client.start();".ENTER);
	fwrite($file, TWO_TAB."service_client.get()->DeleteMore".$clsname."(obj_ids);".ENTER);
	fwrite($file, TWO_TAB."service_client.close();".ENTER);
	fwrite($file, TAB."}".ENTER);
	fwrite($file, TAB."catch (TException &tx) {".ENTER);
	fwrite($file, TWO_TAB."std::string error_msg = tx.what();".ENTER);
	fwrite($file, TAB."}".ENTER);
	fwrite($file, "}".ENTER);


	fwrite($file, "void SQLClientHelper::Get".$clsname."ByFields(cbm::$clsname & _return, const std::map<std::string, std::string> & fields) {".ENTER);
	fwrite($file, TAB."try {".ENTER);
	fwrite($file, TWO_TAB."RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);".ENTER);
	fwrite($file, TWO_TAB."service_client.start();".ENTER);
	fwrite($file, TWO_TAB."service_client.get()->Get".$clsname."ByFields(_return, fields);".ENTER);
	fwrite($file, TWO_TAB."service_client.close();".ENTER);
	fwrite($file, TAB."}".ENTER);
	fwrite($file, TAB."catch (TException &tx) {".ENTER);
	fwrite($file, TWO_TAB."std::string error_msg = tx.what();".ENTER);
	fwrite($file, TAB."}".ENTER);
	fwrite($file, "}".ENTER);


	fwrite($file, "void SQLClientHelper::Get".$clsname."ByField1(cbm::$clsname & _return, const std::string& field, const std::string& value) {".ENTER);
	fwrite($file, TAB."try {".ENTER);
	fwrite($file, TWO_TAB."RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);".ENTER);
	fwrite($file, TWO_TAB."service_client.start();".ENTER);
	fwrite($file, TWO_TAB."service_client.get()->Get".$clsname."ByField1(_return, field, value);".ENTER);
	fwrite($file, TWO_TAB."service_client.close();".ENTER);
	fwrite($file, TAB."}".ENTER);
	fwrite($file, TAB."catch (TException &tx) {".ENTER);
	fwrite($file, TWO_TAB."std::string error_msg = tx.what();".ENTER);
	fwrite($file, TAB."}".ENTER);
	fwrite($file, "}".ENTER);


	fwrite($file, "void SQLClientHelper::Get".$clsname."ByField2(cbm::$clsname & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {".ENTER);
	fwrite($file, TAB."try {".ENTER);
	fwrite($file, TWO_TAB."RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);".ENTER);
	fwrite($file, TWO_TAB."service_client.start();".ENTER);
	fwrite($file, TWO_TAB."service_client.get()->Get".$clsname."ByField2(_return, field1, value1, field2, value2);".ENTER);
	fwrite($file, TWO_TAB."service_client.close();".ENTER);
	fwrite($file, TAB."}".ENTER);
	fwrite($file, TAB."catch (TException &tx) {".ENTER);
	fwrite($file, TWO_TAB."std::string error_msg = tx.what();".ENTER);
	fwrite($file, TAB."}".ENTER);
	fwrite($file, "}".ENTER);


	fwrite($file, "void SQLClientHelper::Get".$clsname."ListByFields(std::vector<cbm::$clsname> & _return, const std::map<std::string, std::string> & fields) {".ENTER);
	fwrite($file, TAB."try {".ENTER);
	fwrite($file, TWO_TAB."RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);".ENTER);
	fwrite($file, TWO_TAB."service_client.start();".ENTER);
	fwrite($file, TWO_TAB."service_client.get()->Get".$clsname."ListByFields(_return, fields);".ENTER);
	fwrite($file, TWO_TAB."service_client.close();".ENTER);
	fwrite($file, TAB."}".ENTER);
	fwrite($file, TAB."catch (TException &tx) {".ENTER);
	fwrite($file, TWO_TAB."std::string error_msg = tx.what();".ENTER);
	fwrite($file, TAB."}".ENTER);
	fwrite($file, "}".ENTER);


	fwrite($file, "void SQLClientHelper::Get".$clsname."ListByField1(std::vector<cbm::$clsname> & _return, const std::string& field, const std::string& value) {".ENTER);
	fwrite($file, TAB."try {".ENTER);
	fwrite($file, TWO_TAB."RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);".ENTER);
	fwrite($file, TWO_TAB."service_client.start();".ENTER);
	fwrite($file, TWO_TAB."service_client.get()->Get".$clsname."ListByField1(_return, field, value);".ENTER);
	fwrite($file, TWO_TAB."service_client.close();".ENTER);
	fwrite($file, TAB."}".ENTER);
	fwrite($file, TAB."catch (TException &tx) {".ENTER);
	fwrite($file, TWO_TAB."std::string error_msg = tx.what();".ENTER);
	fwrite($file, TAB."}".ENTER);
	fwrite($file, "}".ENTER);


	fwrite($file, "void SQLClientHelper::Get".$clsname."ListByField2(std::vector<cbm::$clsname> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {".ENTER);
	fwrite($file, TAB."try {".ENTER);
	fwrite($file, TWO_TAB."RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);".ENTER);
	fwrite($file, TWO_TAB."service_client.start();".ENTER);
	fwrite($file, TWO_TAB."service_client.get()->Get".$clsname."ListByField2(_return, field1, value1, field2, value2);".ENTER);
	fwrite($file, TWO_TAB."service_client.close();".ENTER);
	fwrite($file, TAB."}".ENTER);
	fwrite($file, TAB."catch (TException &tx) {".ENTER);
	fwrite($file, TWO_TAB."std::string error_msg = tx.what();".ENTER);
	fwrite($file, TAB."}".ENTER);
	fwrite($file, "}".ENTER);


	fwrite($file, "int32_t SQLClientHelper::Get".$clsname."IdByFields(const std::map<std::string, std::string> & fields) {".ENTER);
	fwrite($file, TAB."int32_t ret = -1;".ENTER);
	fwrite($file, TAB."try {".ENTER);
	fwrite($file, TWO_TAB."RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);".ENTER);
	fwrite($file, TWO_TAB."service_client.start();".ENTER);
	fwrite($file, TWO_TAB."ret = service_client.get()->Get".$clsname."IdByFields(fields);".ENTER);
	fwrite($file, TWO_TAB."service_client.close();".ENTER);
	fwrite($file, TAB."}".ENTER);
	fwrite($file, TAB."catch (TException &tx) {".ENTER);
	fwrite($file, TWO_TAB."std::string error_msg = tx.what();".ENTER);
	fwrite($file, TWO_TAB."ret = -1;".ENTER);
	fwrite($file, TAB."}".ENTER);
	fwrite($file, "return ret;".ENTER);
	fwrite($file, "}".ENTER);


	fwrite($file, "int32_t SQLClientHelper::Get".$clsname."IdByField1(const std::string& field, const std::string& value) {".ENTER);
	fwrite($file, TAB."int32_t ret = -1;".ENTER);
	fwrite($file, TAB."try {".ENTER);
	fwrite($file, TWO_TAB."RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);".ENTER);
	fwrite($file, TWO_TAB."service_client.start();".ENTER);
	fwrite($file, TWO_TAB."ret = service_client.get()->Get".$clsname."IdByField1(field, value);".ENTER);
	fwrite($file, TWO_TAB."service_client.close();".ENTER);
	fwrite($file, TAB."}".ENTER);
	fwrite($file, TAB."catch (TException &tx) {".ENTER);
	fwrite($file, TWO_TAB."std::string error_msg = tx.what();".ENTER);
	fwrite($file, TWO_TAB."ret = -1;".ENTER);
	fwrite($file, TAB."}".ENTER);
	fwrite($file, "return ret;".ENTER);
	fwrite($file, "}".ENTER);


	fwrite($file, "int32_t SQLClientHelper::Get".$clsname."IdByField2(const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {".ENTER);
	fwrite($file, TAB."int32_t ret = -1;".ENTER);
	fwrite($file, TAB."try {".ENTER);
	fwrite($file, TWO_TAB."RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);".ENTER);
	fwrite($file, TWO_TAB."service_client.start();".ENTER);
	fwrite($file, TWO_TAB."ret = service_client.get()->Get".$clsname."IdByField2(field1, value1, field2, value2);".ENTER);
	fwrite($file, TWO_TAB."service_client.close();".ENTER);
	fwrite($file, TAB."}".ENTER);
	fwrite($file, TAB."catch (TException &tx) {".ENTER);
	fwrite($file, TWO_TAB."std::string error_msg = tx.what();".ENTER);
	fwrite($file, TWO_TAB."ret = -1;".ENTER);
	fwrite($file, TAB."}".ENTER);
	fwrite($file, "return ret;".ENTER);	
	fwrite($file, "}".ENTER);


	fwrite($file, "void SQLClientHelper::Get".$clsname."IdListByFields(std::vector<int32_t> & _return, const std::map<std::string, std::string> & fields) {".ENTER);
	fwrite($file, TAB."try {".ENTER);
	fwrite($file, TWO_TAB."RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);".ENTER);
	fwrite($file, TWO_TAB."service_client.start();".ENTER);
	fwrite($file, TWO_TAB."service_client.get()->Get".$clsname."IdListByFields(_return, fields);".ENTER);
	fwrite($file, TWO_TAB."service_client.close();".ENTER);
	fwrite($file, TAB."}".ENTER);
	fwrite($file, TAB."catch (TException &tx) {".ENTER);
	fwrite($file, TWO_TAB."std::string error_msg = tx.what();".ENTER);
	fwrite($file, TAB."}".ENTER);
	fwrite($file, "}".ENTER);


	fwrite($file, "void SQLClientHelper::Get".$clsname."IdListByField1(std::vector<int32_t> & _return, const std::string& field, const std::string& value) {".ENTER);
	fwrite($file, TAB."try {".ENTER);
	fwrite($file, TWO_TAB."RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);".ENTER);
	fwrite($file, TWO_TAB."service_client.start();".ENTER);
	fwrite($file, TWO_TAB."service_client.get()->Get".$clsname."IdListByField1(_return, field, value);".ENTER);
	fwrite($file, TWO_TAB."service_client.close();".ENTER);
	fwrite($file, TAB."}".ENTER);
	fwrite($file, TAB."catch (TException &tx) {".ENTER);
	fwrite($file, TWO_TAB."std::string error_msg = tx.what();".ENTER);
	fwrite($file, TAB."}".ENTER);
	fwrite($file, "}".ENTER);


	fwrite($file, "void SQLClientHelper::Get".$clsname."IdListByField2(std::vector<int32_t> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {".ENTER);
	fwrite($file, TAB."try {".ENTER);
	fwrite($file, TWO_TAB."RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);".ENTER);
	fwrite($file, TWO_TAB."service_client.start();".ENTER);
	fwrite($file, TWO_TAB."service_client.get()->Get".$clsname."IdListByField2(_return, field1, value1, field2, value2);".ENTER);
	fwrite($file, TWO_TAB."service_client.close();".ENTER);
	fwrite($file, TAB."}".ENTER);
	fwrite($file, TAB."catch (TException &tx) {".ENTER);
	fwrite($file, TWO_TAB."std::string error_msg = tx.what();".ENTER);
	fwrite($file, TAB."}".ENTER);
	fwrite($file, "}".ENTER);

	fwrite($file, "void SQLClientHelper::Get".$clsname."ListByForeignKey(std::vector<cbm::$clsname> & _return, const std::string& fkey, const int32_t id) {".ENTER);
	fwrite($file, TAB."try {".ENTER);
	fwrite($file, TWO_TAB."RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);".ENTER);
	fwrite($file, TWO_TAB."service_client.start();".ENTER);
	fwrite($file, TWO_TAB."service_client.get()->Get".$clsname."ListByForeignKey(_return, fkey, id);".ENTER);
	fwrite($file, TWO_TAB."service_client.close();".ENTER);
	fwrite($file, TAB."}".ENTER);
	fwrite($file, TAB."catch (TException &tx) {".ENTER);
	fwrite($file, TWO_TAB."std::string error_msg = tx.what();".ENTER);
	fwrite($file, TAB."}".ENTER);
	fwrite($file, "}".ENTER);

	fwrite($file, "void SQLClientHelper::Get".$clsname."IdListByForeignKey(std::vector<int32_t> & _return, const std::string& fkey, const int32_t id) {".ENTER);
	fwrite($file, TAB."try {".ENTER);
	fwrite($file, TWO_TAB."RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);".ENTER);
	fwrite($file, TWO_TAB."service_client.start();".ENTER);
	fwrite($file, TWO_TAB."service_client.get()->Get".$clsname."IdListByForeignKey(_return, fkey, id);".ENTER);
	fwrite($file, TWO_TAB."service_client.close();".ENTER);
	fwrite($file, TAB."}".ENTER);
	fwrite($file, TAB."catch (TException &tx) {".ENTER);
	fwrite($file, TWO_TAB."std::string error_msg = tx.what();".ENTER);
	fwrite($file, TAB."}".ENTER);
	fwrite($file, "}".ENTER);

	fwrite($file, ENTER);
}

function gen_sql_helper_of_hpp_client($file, $tables, $relations)
{
	fwrite($file, '#pragma once'.TWO_ENTER);
	fwrite($file, '#include "RpcClient.h"'.ENTER);
	// fwrite($file, 'using namespace cbm;'.ENTER);


	fwrite($file, TWO_ENTER.'class SQLClientHelper {'.ENTER);
	fwrite($file, TWO_ENTER.'public:'.ENTER);
	foreach($tables as $tbl => $fields) {
		__gen_sql_helper_of_hpp_client($file, $tbl, $fields, $relations);
	}
	fwrite($file, ENTER.'};'.ENTER);
}

function gen_sql_helper_of_cpp_client($file, $tables, $relations)
{
	fwrite($file, '#include "stdafx.h"'.ENTER);
	fwrite($file, '#include "SQLClientHelper.h"'.ENTER);

	foreach($tables as $tbl => $fields) {
		__gen_sql_helper_of_cpp_client($file, $tbl, $fields, $relations);
	}
}

function __gen_sql_helper_of_py_client($file, $tbl_name, $fields, $relations)
{
	//去掉cbm前缀,作为文件名
	$fname = table_no_prefix($tbl_name);

	//得到类名
	$clsname = camel_case($fname);

	fwrite($file, ENTER."#$clsname 类型的CRUD操作".ENTER);

	fwrite($file, "def Add".$clsname."($fname):".ENTER);
	fwrite($file, TAB."ret = -1".ENTER);
	fwrite($file, TAB."try:".ENTER);
	fwrite($file, TWO_TAB."service_client = RpcClient(CbmService, host=HOST, port=PORT2)".ENTER);
	fwrite($file, TWO_TAB."service_client.start()".ENTER);
	fwrite($file, TWO_TAB."ret = service_client.get().Add".$clsname."($fname)".ENTER);
	fwrite($file, TWO_TAB."service_client.close()".ENTER);
	fwrite($file, TAB."except Exception, e:".ENTER);
	fwrite($file, TWO_TAB."print 'client exception:',e".ENTER);
	fwrite($file, TWO_TAB."ret = -1".ENTER);
	fwrite($file, TAB."return ret".ENTER);
	

	fwrite($file, "def Delete".$clsname."(id):".ENTER);
	fwrite($file, TAB."ret = False".ENTER);
	fwrite($file, TAB."try:".ENTER);
	fwrite($file, TWO_TAB."service_client = RpcClient(CbmService, host=HOST, port=PORT2)".ENTER);
	fwrite($file, TWO_TAB."service_client.start()".ENTER);
	fwrite($file, TWO_TAB."ret = service_client.get().Delete".$clsname."(int(id))".ENTER);
	fwrite($file, TWO_TAB."service_client.close()".ENTER);
	fwrite($file, TAB."except Exception, e:".ENTER);
	fwrite($file, TWO_TAB."print 'client exception:',e".ENTER);
	fwrite($file, TWO_TAB."ret = False".ENTER);
	fwrite($file, TAB."return ret".ENTER);
	

	fwrite($file, "def Update".$clsname."($fname):".ENTER);
	fwrite($file, TAB."ret = False".ENTER);
	fwrite($file, TAB."try:".ENTER);
	fwrite($file, TWO_TAB."service_client = RpcClient(CbmService, host=HOST, port=PORT2)".ENTER);
	fwrite($file, TWO_TAB."service_client.start()".ENTER);
	fwrite($file, TWO_TAB."ret = service_client.get().Update".$clsname."($fname)".ENTER);
	fwrite($file, TWO_TAB."service_client.close()".ENTER);
	fwrite($file, TAB."except Exception, e:".ENTER);
	fwrite($file, TWO_TAB."print 'client exception:',e".ENTER);
	fwrite($file, TWO_TAB."ret = False".ENTER);
	fwrite($file, TAB."return ret".ENTER);
	

	fwrite($file, "def Get".$clsname."ById(id):".ENTER);
	fwrite($file, TAB."_return = $clsname()".ENTER);
	fwrite($file, TAB."try:".ENTER);
	fwrite($file, TWO_TAB."service_client = RpcClient(CbmService, host=HOST, port=PORT2)".ENTER);
	fwrite($file, TWO_TAB."service_client.start()".ENTER);
	fwrite($file, TWO_TAB."_return = service_client.get().Get".$clsname."ById(int(id))".ENTER);
	fwrite($file, TWO_TAB."service_client.close()".ENTER);
	fwrite($file, TAB."except Exception, e:".ENTER);
	fwrite($file, TWO_TAB."print 'client exception:',e".ENTER);
	fwrite($file, TWO_TAB."_return.id = -1".ENTER);
	fwrite($file, TAB."return _return".ENTER);
	
	
	fwrite($file, "def Get".$clsname."ByForeignKey(fkey, id):".ENTER);
	fwrite($file, TAB."_return = $clsname()".ENTER);
	fwrite($file, TAB."try:".ENTER);
	fwrite($file, TWO_TAB."service_client = RpcClient(CbmService, host=HOST, port=PORT2)".ENTER);
	fwrite($file, TWO_TAB."service_client.start()".ENTER);
	fwrite($file, TWO_TAB."_return = service_client.get().Get".$clsname."ByForeignKey(fkey, int(id))".ENTER);
	fwrite($file, TWO_TAB."service_client.close()".ENTER);
	fwrite($file, TAB."except Exception, e:".ENTER);
	fwrite($file, TWO_TAB."print 'client exception:',e".ENTER);
	fwrite($file, TWO_TAB."_return.id = -1".ENTER);
	fwrite($file, TAB."return _return".ENTER);


	fwrite($file, "def Get".$clsname."IdByForeignKey(fkey, id):".ENTER);
	fwrite($file, TAB."_return = -1".ENTER);
	fwrite($file, TAB."try:".ENTER);
	fwrite($file, TWO_TAB."service_client = RpcClient(CbmService, host=HOST, port=PORT2)".ENTER);
	fwrite($file, TWO_TAB."service_client.start()".ENTER);
	fwrite($file, TWO_TAB."_return = service_client.get().Get".$clsname."IdByForeignKey(fkey, int(id))".ENTER);
	fwrite($file, TWO_TAB."service_client.close()".ENTER);
	fwrite($file, TAB."except Exception, e:".ENTER);
	fwrite($file, TWO_TAB."print 'client exception:',e".ENTER);
	fwrite($file, TWO_TAB."_return = -1".ENTER);
	fwrite($file, TAB."return _return".ENTER);

	fwrite($file, "def Get".$clsname."List():".ENTER);
	fwrite($file, TAB."_return = []".ENTER);
	fwrite($file, TAB."try:".ENTER);
	fwrite($file, TWO_TAB."service_client = RpcClient(CbmService, host=HOST, port=PORT2)".ENTER);
	fwrite($file, TWO_TAB."service_client.start()".ENTER);
	fwrite($file, TWO_TAB."_return = service_client.get().Get".$clsname."List()".ENTER);
	fwrite($file, TWO_TAB."service_client.close()".ENTER);
	fwrite($file, TAB."except Exception, e:".ENTER);
	fwrite($file, TWO_TAB."print 'client exception:',e".ENTER);
	fwrite($file, TWO_TAB."_return = []".ENTER);
	fwrite($file, TAB."return _return".ENTER);
	

	fwrite($file, "def Get".$clsname."Ids():".ENTER);
	fwrite($file, TAB."_return = []".ENTER);
	fwrite($file, TAB."try:".ENTER);
	fwrite($file, TWO_TAB."service_client = RpcClient(CbmService, host=HOST, port=PORT2)".ENTER);
	fwrite($file, TWO_TAB."service_client.start()".ENTER);
	fwrite($file, TWO_TAB."_return = service_client.get().Get".$clsname."Ids()".ENTER);
	fwrite($file, TWO_TAB."service_client.close()".ENTER);
	fwrite($file, TAB."except Exception, e:".ENTER);
	fwrite($file, TWO_TAB."print 'client exception:',e".ENTER);
	fwrite($file, TWO_TAB."_return = []".ENTER);
	fwrite($file, TAB."return _return".ENTER);
	

    fwrite($file, "def Get".$clsname."Names():".ENTER);
    fwrite($file, TAB."_return = []".ENTER);
	fwrite($file, TAB."try:".ENTER);
	fwrite($file, TWO_TAB."service_client = RpcClient(CbmService, host=HOST, port=PORT2)".ENTER);
	fwrite($file, TWO_TAB."service_client.start()".ENTER);
	fwrite($file, TWO_TAB."_return = service_client.get().Get".$clsname."Names()".ENTER);
	fwrite($file, TWO_TAB."service_client.close()".ENTER);
	fwrite($file, TAB."except Exception, e:".ENTER);
	fwrite($file, TWO_TAB."print 'client exception:',e".ENTER);
	fwrite($file, TWO_TAB."_return = []".ENTER);
	fwrite($file, TAB."return _return".ENTER);
	

	fwrite($file, "def AddMore".$clsname."(objs):".ENTER);
	fwrite($file, TAB."try:".ENTER);
	fwrite($file, TWO_TAB."service_client = RpcClient(CbmService, host=HOST, port=PORT2)".ENTER);
	fwrite($file, TWO_TAB."service_client.start()".ENTER);
	fwrite($file, TWO_TAB."service_client.get().AddMore".$clsname."(objs)".ENTER);
	fwrite($file, TWO_TAB."service_client.close()".ENTER);
	fwrite($file, TAB."except Exception, e:".ENTER);
	fwrite($file, TWO_TAB."print 'client exception:',e".ENTER);
	

	fwrite($file, "def DeleteMore".$clsname."(obj_ids):".ENTER);
	fwrite($file, TAB."if len(obj_ids) == 0:return".ENTER);
	fwrite($file, TAB."try:".ENTER);
	fwrite($file, TWO_TAB."service_client = RpcClient(CbmService, host=HOST, port=PORT2)".ENTER);
	fwrite($file, TWO_TAB."service_client.start()".ENTER);
	fwrite($file, TWO_TAB."service_client.get().DeleteMore".$clsname."(obj_ids)".ENTER);
	fwrite($file, TWO_TAB."service_client.close()".ENTER);
	fwrite($file, TAB."except Exception, e:".ENTER);
	fwrite($file, TWO_TAB."print 'client exception:',e".ENTER);
	

	fwrite($file, "def Get".$clsname."ByFields(fields):".ENTER);
	fwrite($file, TAB."_return = $clsname()".ENTER);
	fwrite($file, TAB."try:".ENTER);
	fwrite($file, TWO_TAB."service_client = RpcClient(CbmService, host=HOST, port=PORT2)".ENTER);
	fwrite($file, TWO_TAB."service_client.start()".ENTER);
	fwrite($file, TWO_TAB."_return = service_client.get().Get".$clsname."ByFields(fields)".ENTER);
	fwrite($file, TWO_TAB."service_client.close()".ENTER);
	fwrite($file, TAB."except Exception, e:".ENTER);
	fwrite($file, TWO_TAB."print 'client exception:',e".ENTER);
	fwrite($file, TWO_TAB."_return.id = -1".ENTER);
	fwrite($file, TAB."return _return".ENTER);


	fwrite($file, "def Get".$clsname."ByField1(field, value):".ENTER);
	fwrite($file, TAB."_return = $clsname()".ENTER);
	fwrite($file, TAB."try:".ENTER);
	fwrite($file, TWO_TAB."service_client = RpcClient(CbmService, host=HOST, port=PORT2)".ENTER);
	fwrite($file, TWO_TAB."service_client.start()".ENTER);
	fwrite($file, TWO_TAB."_return = service_client.get().Get".$clsname."ByField1(field, str(value))".ENTER);
	fwrite($file, TWO_TAB."service_client.close()".ENTER);
	fwrite($file, TAB."except Exception, e:".ENTER);
	fwrite($file, TWO_TAB."print 'client exception:',e".ENTER);
	fwrite($file, TWO_TAB."_return.id = -1".ENTER);
	fwrite($file, TAB."return _return".ENTER);
	
	
	fwrite($file, "def Get".$clsname."ByField2(field1, value1, field2, value2):".ENTER);
	fwrite($file, TAB."_return = $clsname()".ENTER);
	fwrite($file, TAB."try:".ENTER);
	fwrite($file, TWO_TAB."service_client = RpcClient(CbmService, host=HOST, port=PORT2)".ENTER);
	fwrite($file, TWO_TAB."service_client.start()".ENTER);
	fwrite($file, TWO_TAB."_return = service_client.get().Get".$clsname."ByField2(field1, str(value1), field2, str(value2))".ENTER);
	fwrite($file, TWO_TAB."service_client.close()".ENTER);
	fwrite($file, TAB."except Exception, e:".ENTER);
	fwrite($file, TWO_TAB."print 'client exception:',e".ENTER);
	fwrite($file, TWO_TAB."_return.id = -1".ENTER);
	fwrite($file, TAB."return _return".ENTER);
	

	fwrite($file, "def Get".$clsname."ListByFields(fields):".ENTER);
	fwrite($file, TAB."_return = []".ENTER);
	fwrite($file, TAB."try:".ENTER);
	fwrite($file, TWO_TAB."service_client = RpcClient(CbmService, host=HOST, port=PORT2)".ENTER);
	fwrite($file, TWO_TAB."service_client.start()".ENTER);
	fwrite($file, TWO_TAB."_return = service_client.get().Get".$clsname."ListByFields(fields)".ENTER);
	fwrite($file, TWO_TAB."service_client.close()".ENTER);
	fwrite($file, TAB."except Exception, e:".ENTER);
	fwrite($file, TWO_TAB."print 'client exception:',e".ENTER);
	fwrite($file, TWO_TAB."_return = []".ENTER);
	fwrite($file, TAB."return _return".ENTER);
	

	fwrite($file, "def Get".$clsname."ListByField1(field, value):".ENTER);
	fwrite($file, TAB."_return = []".ENTER);
	fwrite($file, TAB."try:".ENTER);
	fwrite($file, TWO_TAB."service_client = RpcClient(CbmService, host=HOST, port=PORT2)".ENTER);
	fwrite($file, TWO_TAB."service_client.start()".ENTER);
	fwrite($file, TWO_TAB."_return = service_client.get().Get".$clsname."ListByField1(field, str(value))".ENTER);
	fwrite($file, TWO_TAB."service_client.close()".ENTER);
	fwrite($file, TAB."except Exception, e:".ENTER);
	fwrite($file, TWO_TAB."print 'client exception:',e".ENTER);
	fwrite($file, TWO_TAB."_return = []".ENTER);
	fwrite($file, TAB."return _return".ENTER);


	fwrite($file, "def Get".$clsname."ListByField2(field1, value1, field2, value2):".ENTER);
	fwrite($file, TAB."_return = []".ENTER);
	fwrite($file, TAB."try:".ENTER);
	fwrite($file, TWO_TAB."service_client = RpcClient(CbmService, host=HOST, port=PORT2)".ENTER);
	fwrite($file, TWO_TAB."service_client.start()".ENTER);
	fwrite($file, TWO_TAB."_return = service_client.get().Get".$clsname."ListByField2(field1, str(value1), field2, str(value2))".ENTER);
	fwrite($file, TWO_TAB."service_client.close()".ENTER);
	fwrite($file, TAB."except Exception, e:".ENTER);
	fwrite($file, TWO_TAB."print 'client exception:',e".ENTER);
	fwrite($file, TWO_TAB."_return = []".ENTER);
	fwrite($file, TAB."return _return".ENTER);


	fwrite($file, "def Get".$clsname."IdByFields(fields):".ENTER);
	fwrite($file, TAB."_return = -1".ENTER);
	fwrite($file, TAB."try:".ENTER);
	fwrite($file, TWO_TAB."service_client = RpcClient(CbmService, host=HOST, port=PORT2)".ENTER);
	fwrite($file, TWO_TAB."service_client.start()".ENTER);
	fwrite($file, TWO_TAB."_return = service_client.get().Get".$clsname."IdByFields(fields)".ENTER);
	fwrite($file, TWO_TAB."service_client.close()".ENTER);
	fwrite($file, TAB."except Exception, e:".ENTER);
	fwrite($file, TWO_TAB."print 'client exception:',e".ENTER);
	fwrite($file, TWO_TAB."_return = -1".ENTER);
	fwrite($file, TAB."return _return".ENTER);


	fwrite($file, "def Get".$clsname."IdByField1(field, value):".ENTER);
	fwrite($file, TAB."_return = -1".ENTER);
	fwrite($file, TAB."try:".ENTER);
	fwrite($file, TWO_TAB."service_client = RpcClient(CbmService, host=HOST, port=PORT2)".ENTER);
	fwrite($file, TWO_TAB."service_client.start()".ENTER);
	fwrite($file, TWO_TAB."_return = service_client.get().Get".$clsname."IdByField1(field, str(value))".ENTER);
	fwrite($file, TWO_TAB."service_client.close()".ENTER);
	fwrite($file, TAB."except Exception, e:".ENTER);
	fwrite($file, TWO_TAB."print 'client exception:',e".ENTER);
	fwrite($file, TWO_TAB."_return = -1".ENTER);
	fwrite($file, TAB."return _return".ENTER);
	

	fwrite($file, "def Get".$clsname."IdByField2(field1, value1, field2, value2):".ENTER);
	fwrite($file, TAB."_return = -1".ENTER);
	fwrite($file, TAB."try:".ENTER);
	fwrite($file, TWO_TAB."service_client = RpcClient(CbmService, host=HOST, port=PORT2)".ENTER);
	fwrite($file, TWO_TAB."service_client.start()".ENTER);
	fwrite($file, TWO_TAB."_return = service_client.get().Get".$clsname."IdByField2(field1, str(value1), field2, str(value2))".ENTER);
	fwrite($file, TWO_TAB."service_client.close()".ENTER);
	fwrite($file, TAB."except Exception, e:".ENTER);
	fwrite($file, TWO_TAB."print 'client exception:',e".ENTER);
	fwrite($file, TWO_TAB."_return = -1".ENTER);
	fwrite($file, TAB."return _return".ENTER);
	

	fwrite($file, "def Get".$clsname."IdListByFields(fields):".ENTER);
	fwrite($file, TAB."_return = []".ENTER);
	fwrite($file, TAB."try:".ENTER);
	fwrite($file, TWO_TAB."service_client = RpcClient(CbmService, host=HOST, port=PORT2)".ENTER);
	fwrite($file, TWO_TAB."service_client.start()".ENTER);
	fwrite($file, TWO_TAB."_return = service_client.get().Get".$clsname."IdListByFields(fields)".ENTER);
	fwrite($file, TWO_TAB."service_client.close()".ENTER);
	fwrite($file, TAB."except Exception, e:".ENTER);
	fwrite($file, TWO_TAB."print 'client exception:',e".ENTER);
	fwrite($file, TWO_TAB."_return = []".ENTER);
	fwrite($file, TAB."return _return".ENTER);
	

	fwrite($file, "def Get".$clsname."IdListByField1(field, value):".ENTER);
	fwrite($file, TAB."_return = []".ENTER);
	fwrite($file, TAB."try:".ENTER);
	fwrite($file, TWO_TAB."service_client = RpcClient(CbmService, host=HOST, port=PORT2)".ENTER);
	fwrite($file, TWO_TAB."service_client.start()".ENTER);
	fwrite($file, TWO_TAB."_return = service_client.get().Get".$clsname."IdListByField1(field, str(value))".ENTER);
	fwrite($file, TWO_TAB."service_client.close()".ENTER);
	fwrite($file, TAB."except Exception, e:".ENTER);
	fwrite($file, TWO_TAB."print 'client exception:',e".ENTER);
	fwrite($file, TWO_TAB."_return = []".ENTER);
	fwrite($file, TAB."return _return".ENTER);


	fwrite($file, "def Get".$clsname."IdListByField2(field1, value1, field2, value2):".ENTER);
	fwrite($file, TAB."_return = []".ENTER);
	fwrite($file, TAB."try:".ENTER);
	fwrite($file, TWO_TAB."service_client = RpcClient(CbmService, host=HOST, port=PORT2)".ENTER);
	fwrite($file, TWO_TAB."service_client.start()".ENTER);
	fwrite($file, TWO_TAB."_return = service_client.get().Get".$clsname."IdListByField2(field1, str(value1), field2, str(value2))".ENTER);
	fwrite($file, TWO_TAB."service_client.close()".ENTER);
	fwrite($file, TAB."except Exception, e:".ENTER);
	fwrite($file, TWO_TAB."print 'client exception:',e".ENTER);
	fwrite($file, TWO_TAB."_return = []".ENTER);
	fwrite($file, TAB."return _return".ENTER);


	fwrite($file, "def Get".$clsname."ListByForeignKey(fkey, id):".ENTER);
	fwrite($file, TAB."_return = []".ENTER);
	fwrite($file, TAB."try:".ENTER);
	fwrite($file, TWO_TAB."service_client = RpcClient(CbmService, host=HOST, port=PORT2)".ENTER);
	fwrite($file, TWO_TAB."service_client.start()".ENTER);
	fwrite($file, TWO_TAB."_return = service_client.get().Get".$clsname."ListByForeignKey(fkey, int(id))".ENTER);
	fwrite($file, TWO_TAB."service_client.close()".ENTER);
	fwrite($file, TAB."except Exception, e:".ENTER);
	fwrite($file, TWO_TAB."print 'client exception:',e".ENTER);
	fwrite($file, TWO_TAB."_return = []".ENTER);
	fwrite($file, TAB."return _return".ENTER);


	fwrite($file, "def Get".$clsname."IdListByForeignKey(fkey, id):".ENTER);
	fwrite($file, TAB."_return = []".ENTER);
	fwrite($file, TAB."try:".ENTER);
	fwrite($file, TWO_TAB."service_client = RpcClient(CbmService, host=HOST, port=PORT2)".ENTER);
	fwrite($file, TWO_TAB."service_client.start()".ENTER);
	fwrite($file, TWO_TAB."_return = service_client.get().Get".$clsname."IdListByForeignKey(fkey, int(id))".ENTER);
	fwrite($file, TWO_TAB."service_client.close()".ENTER);
	fwrite($file, TAB."except Exception, e:".ENTER);
	fwrite($file, TWO_TAB."print 'client exception:',e".ENTER);
	fwrite($file, TWO_TAB."_return = []".ENTER);
	fwrite($file, TAB."return _return".ENTER);

	fwrite($file, TWO_ENTER);
}

function gen_sql_helper_of_py_client($file, $tables, $relations)
{
	fwrite($file, '#-*- coding:utf-8 -*-'.TWO_ENTER);
	fwrite($file, 'from cbm.ttypes import *'.ENTER);
	fwrite($file, 'from cbm import CbmService'.ENTER);
	fwrite($file, 'from RpcClient import RpcClient, HOST, PORT1, PORT2'.ENTER);
	fwrite($file, 'import CbmUtil'.TWO_ENTER);
	
	foreach($tables as $tbl => $fields) {
		__gen_sql_helper_of_py_client($file, $tbl, $fields, $relations);
	}
}

function __gen_sql_helper_of_php_client($file, $tbl_name, $fields, $relations)
{
	//去掉cbm前缀,作为文件名
	$fname = table_no_prefix($tbl_name);

	//得到类名
	$clsname = camel_case($fname);
	$service_class = '\'\cbm\CbmServiceClient\'';

	fwrite($file, '//$clsname 类型的CRUD操作'.TWO_ENTER);

	fwrite($file, 'function Add'.$clsname.'($fname) {'.ENTER);
	fwrite($file, TAB.'$ret = -1;'.ENTER);
	fwrite($file, TAB.'try {'.ENTER);
	fwrite($file, TWO_TAB.'$service_client = new ThriftClient('.$service_class.', HOST, PORT2);'.ENTER);
	fwrite($file, TWO_TAB.'$client = $service_client->getClient();'.ENTER);
	fwrite($file, TWO_TAB.'$ret = $client->Add'.$clsname.'($fname);'.ENTER);
	fwrite($file, TAB.'} catch (TException $tx) {'.ENTER);
	fwrite($file, TWO_TAB.'print \'TException: \'.$tx->getMessage()."\n";'.ENTER);
	fwrite($file, TWO_TAB.'$ret = -1;'.ENTER);
	fwrite($file, TAB.'}'.ENTER);
	fwrite($file, TAB.'return $ret;'.ENTER);
	fwrite($file, '}'.TWO_ENTER);
	

	fwrite($file, 'function Delete'.$clsname.'($id) {'.ENTER);
	fwrite($file, TAB.'$ret = false;'.ENTER);
	fwrite($file, TAB.'try {'.ENTER);
	fwrite($file, TWO_TAB.'$service_client = new ThriftClient('.$service_class.', HOST, PORT2);'.ENTER);
	fwrite($file, TWO_TAB.'$client = $service_client->getClient();'.ENTER);
	fwrite($file, TWO_TAB.'$ret = $client->Delete'.$clsname.'(intval($id));'.ENTER);
	fwrite($file, TAB.'} catch (TException $tx) {'.ENTER);
	fwrite($file, TWO_TAB.'print \'TException: \'.$tx->getMessage()."\n";'.ENTER);
	fwrite($file, TWO_TAB.'$ret = false;'.ENTER);
	fwrite($file, TAB.'}'.ENTER);
	fwrite($file, TAB.'return $ret;'.ENTER);
	fwrite($file, '}'.TWO_ENTER);
	

	fwrite($file, 'function Update'.$clsname.'($fname) {'.ENTER);
	fwrite($file, TAB.'$ret = false;'.ENTER);
	fwrite($file, TAB.'try {'.ENTER);
	fwrite($file, TWO_TAB.'$service_client = new ThriftClient('.$service_class.', HOST, PORT2);'.ENTER);
	fwrite($file, TWO_TAB.'$client = $service_client->getClient();'.ENTER);
	fwrite($file, TWO_TAB.'$ret = $client->Update'.$clsname.'($fname);'.ENTER);
	fwrite($file, TAB.'} catch (TException $tx) {'.ENTER);
	fwrite($file, TWO_TAB.'print \'TException: \'.$tx->getMessage()."\n";'.ENTER);
	fwrite($file, TWO_TAB.'$ret = false;'.ENTER);
	fwrite($file, TAB.'}'.ENTER);
	fwrite($file, TAB.'return $ret;'.ENTER);
	fwrite($file, '}'.TWO_ENTER);
	

	fwrite($file, 'function Get'.$clsname.'ById($id) {'.ENTER);
	fwrite($file, TAB.'$_return = new '.$clsname.'();'.ENTER);
	fwrite($file, TAB.'try {'.ENTER);
	fwrite($file, TWO_TAB.'$service_client = new ThriftClient('.$service_class.', HOST, PORT2);'.ENTER);
	fwrite($file, TWO_TAB.'$client = $service_client->getClient();'.ENTER);
	fwrite($file, TWO_TAB.'$_return = $client->Get'.$clsname.'ById(intval($id));'.ENTER);
	fwrite($file, TAB.'} catch (TException $tx) {'.ENTER);
	fwrite($file, TWO_TAB.'print \'TException: \'.$tx->getMessage()."\n";'.ENTER);
	fwrite($file, TWO_TAB.'$_return->id = -1;'.ENTER);
	fwrite($file, TAB.'}'.ENTER);
	fwrite($file, TAB.'return $_return;'.ENTER);
	fwrite($file, '}'.TWO_ENTER);
	
	
	fwrite($file, 'function Get'.$clsname.'ByForeignKey($fkey, $id) {'.ENTER);
	fwrite($file, TAB.'$_return = new '.$clsname.'();'.ENTER);
	fwrite($file, TAB.'try {'.ENTER);
	fwrite($file, TWO_TAB.'$service_client = new ThriftClient('.$service_class.', HOST, PORT2);'.ENTER);
	fwrite($file, TWO_TAB.'$client = $service_client->getClient();'.ENTER);
	fwrite($file, TWO_TAB.'$_return = $client->Get'.$clsname.'ByForeignKey($fkey, intval($id));'.ENTER);
	fwrite($file, TAB.'} catch (TException $tx) {'.ENTER);
	fwrite($file, TWO_TAB.'print \'TException: \'.$tx->getMessage()."\n";'.ENTER);
	fwrite($file, TWO_TAB.'$_return->id = -1;'.ENTER);
	fwrite($file, TAB.'}'.ENTER);
	fwrite($file, TAB.'return $_return;'.ENTER);
	fwrite($file, '}'.TWO_ENTER);


	fwrite($file, 'function Get'.$clsname.'IdByForeignKey($fkey, $id) {'.ENTER);
	fwrite($file, TAB.'$_return = -1;'.ENTER);
	fwrite($file, TAB.'try {'.ENTER);
	fwrite($file, TWO_TAB.'$service_client = new ThriftClient('.$service_class.', HOST, PORT2);'.ENTER);
	fwrite($file, TWO_TAB.'$client = $service_client->getClient();'.ENTER);
	fwrite($file, TWO_TAB.'$_return = $client->Get'.$clsname.'IdByForeignKey($fkey, intval($id));'.ENTER);
	fwrite($file, TAB.'} catch (TException $tx) {'.ENTER);
	fwrite($file, TWO_TAB.'print \'TException: \'.$tx->getMessage()."\n";'.ENTER);
	fwrite($file, TWO_TAB.'$_return = -1;'.ENTER);
	fwrite($file, TAB.'}'.ENTER);
	fwrite($file, TAB.'return $_return;'.ENTER);
	fwrite($file, '}'.TWO_ENTER);

	fwrite($file, 'function Get'.$clsname.'List() {'.ENTER);
	fwrite($file, TAB.'$_return = array();'.ENTER);
	fwrite($file, TAB.'try {'.ENTER);
	fwrite($file, TWO_TAB.'$service_client = new ThriftClient('.$service_class.', HOST, PORT2);'.ENTER);
	fwrite($file, TWO_TAB.'$client = $service_client->getClient();'.ENTER);
	fwrite($file, TWO_TAB.'$_return = $client->Get'.$clsname.'List();'.ENTER);
	fwrite($file, TAB.'} catch (TException $tx) {'.ENTER);
	fwrite($file, TWO_TAB.'print \'TException: \'.$tx->getMessage()."\n";'.ENTER);
	fwrite($file, TWO_TAB.'$_return = array();'.ENTER);
	fwrite($file, TAB.'}'.ENTER);
	fwrite($file, TAB.'return $_return;'.ENTER);
	fwrite($file, '}'.TWO_ENTER);
	

	fwrite($file, 'function Get'.$clsname.'Ids() {'.ENTER);
	fwrite($file, TAB.'$_return = array();'.ENTER);
	fwrite($file, TAB.'try {'.ENTER);
	fwrite($file, TWO_TAB.'$service_client = new ThriftClient('.$service_class.', HOST, PORT2);'.ENTER);
	fwrite($file, TWO_TAB.'$client = $service_client->getClient();'.ENTER);
	fwrite($file, TWO_TAB.'$_return = $client->Get'.$clsname.'Ids();'.ENTER);
	fwrite($file, TAB.'} catch (TException $tx) {'.ENTER);
	fwrite($file, TWO_TAB.'print \'TException: \'.$tx->getMessage()."\n";'.ENTER);
	fwrite($file, TWO_TAB.'$_return = array();'.ENTER);
	fwrite($file, TAB.'}'.ENTER);
	fwrite($file, TAB.'return $_return;'.ENTER);
	fwrite($file, '}'.TWO_ENTER);
	

    fwrite($file, 'function Get'.$clsname.'Names() {'.ENTER);
    fwrite($file, TAB.'$_return = array();'.ENTER);
	fwrite($file, TAB.'try {'.ENTER);
	fwrite($file, TWO_TAB.'$service_client = new ThriftClient('.$service_class.', HOST, PORT2);'.ENTER);
	fwrite($file, TWO_TAB.'$client = $service_client->getClient();'.ENTER);
	fwrite($file, TWO_TAB.'$_return = $client->Get'.$clsname.'Names();'.ENTER);
	fwrite($file, TAB.'} catch (TException $tx) {'.ENTER);
	fwrite($file, TWO_TAB.'print \'TException: \'.$tx->getMessage()."\n";'.ENTER);
	fwrite($file, TWO_TAB.'$_return = array();'.ENTER);
	fwrite($file, TAB.'}'.ENTER);
	fwrite($file, TAB.'return $_return;'.ENTER);
	fwrite($file, '}'.TWO_ENTER);
	

	fwrite($file, 'function AddMore'.$clsname.'($objs) {'.ENTER);
	fwrite($file, TAB.'try {'.ENTER);
	fwrite($file, TWO_TAB.'$service_client = new ThriftClient('.$service_class.', HOST, PORT2);'.ENTER);
	fwrite($file, TWO_TAB.'$client = $service_client->getClient();'.ENTER);
	fwrite($file, TWO_TAB.'$client->AddMore'.$clsname.'($objs);'.ENTER);
	fwrite($file, TAB.'} catch (TException $tx) {'.ENTER);
	fwrite($file, TWO_TAB.'print \'TException: \'.$tx->getMessage()."\n";'.ENTER);
	fwrite($file, TAB.'}'.ENTER);
	fwrite($file, '}'.TWO_ENTER);
	

	fwrite($file, 'function DeleteMore'.$clsname.'($obj_ids) {'.ENTER);
	fwrite($file, TAB.'if(empty($obj_ids)) return;'.ENTER);
	fwrite($file, TAB.'try {'.ENTER);
	fwrite($file, TWO_TAB.'$service_client = new ThriftClient('.$service_class.', HOST, PORT2);'.ENTER);
	fwrite($file, TWO_TAB.'$client = $service_client->getClient();'.ENTER);
	fwrite($file, TWO_TAB.'$client->DeleteMore'.$clsname.'($obj_ids);'.ENTER);
	fwrite($file, TAB.'} catch (TException $tx) {'.ENTER);
	fwrite($file, TWO_TAB.'print \'TException: \'.$tx->getMessage()."\n";'.ENTER);
	fwrite($file, TAB.'}'.ENTER);
	fwrite($file, '}'.TWO_ENTER);
	

	fwrite($file, 'function Get'.$clsname.'ByFields($fields) {'.ENTER);
	fwrite($file, TAB.'$_return = new '.$clsname.'();'.ENTER);
	fwrite($file, TAB.'try {'.ENTER);
	fwrite($file, TWO_TAB.'$service_client = new ThriftClient('.$service_class.', HOST, PORT2);'.ENTER);
	fwrite($file, TWO_TAB.'$client = $service_client->getClient();'.ENTER);
	fwrite($file, TWO_TAB.'$_return = $client->Get'.$clsname.'ByFields($fields);'.ENTER);
	fwrite($file, TAB.'} catch (TException $tx) {'.ENTER);
	fwrite($file, TWO_TAB.'print \'TException: \'.$tx->getMessage()."\n";'.ENTER);
	fwrite($file, TWO_TAB.'$_return->id = -1;'.ENTER);
	fwrite($file, TAB.'}'.ENTER);
	fwrite($file, TAB.'return $_return;'.ENTER);
	fwrite($file, '}'.TWO_ENTER);


	fwrite($file, 'function Get'.$clsname.'ByField1($field, $value) {'.ENTER);
	fwrite($file, TAB.'$_return = new '.$clsname.'();'.ENTER);
	fwrite($file, TAB.'try {'.ENTER);
	fwrite($file, TWO_TAB.'$service_client = new ThriftClient('.$service_class.', HOST, PORT2);'.ENTER);
	fwrite($file, TWO_TAB.'$client = $service_client->getClient();'.ENTER);
	fwrite($file, TWO_TAB.'$_return = $client->Get'.$clsname.'ByField1($field, strval($value));'.ENTER);
	fwrite($file, TAB.'} catch (TException $tx) {'.ENTER);
	fwrite($file, TWO_TAB.'print \'TException: \'.$tx->getMessage()."\n";'.ENTER);
	fwrite($file, TWO_TAB.'$_return->id = -1;'.ENTER);
	fwrite($file, TAB.'}'.ENTER);
	fwrite($file, TAB.'return $_return;'.ENTER);
	fwrite($file, '}'.TWO_ENTER);
	
	
	fwrite($file, 'function Get'.$clsname.'ByField2($field1, $value1, $field2, $value2) {'.ENTER);
	fwrite($file, TAB.'$_return = new '.$clsname.'();'.ENTER);
	fwrite($file, TAB.'try {'.ENTER);
	fwrite($file, TWO_TAB.'$service_client = new ThriftClient('.$service_class.', HOST, PORT2);'.ENTER);
	fwrite($file, TWO_TAB.'$client = $service_client->getClient();'.ENTER);
	fwrite($file, TWO_TAB.'$_return = $client->Get'.$clsname.'ByField2($field1, strval($value1), $field2, str($value2));'.ENTER);
	fwrite($file, TAB.'} catch (TException $tx) {'.ENTER);
	fwrite($file, TWO_TAB.'print \'TException: \'.$tx->getMessage()."\n";'.ENTER);
	fwrite($file, TWO_TAB.'$_return->id = -1;'.ENTER);
	fwrite($file, TAB.'}'.ENTER);
	fwrite($file, TAB.'return $_return;'.ENTER);
	fwrite($file, '}'.TWO_ENTER);
	

	fwrite($file, 'function Get'.$clsname.'ListByFields($fields) {'.ENTER);
	fwrite($file, TAB.'$_return = array();'.ENTER);
	fwrite($file, TAB.'try {'.ENTER);
	fwrite($file, TWO_TAB.'$service_client = new ThriftClient('.$service_class.', HOST, PORT2);'.ENTER);
	fwrite($file, TWO_TAB.'$client = $service_client->getClient();'.ENTER);
	fwrite($file, TWO_TAB.'$_return = $client->Get'.$clsname.'ListByFields($fields);'.ENTER);
	fwrite($file, TAB.'} catch (TException $tx) {'.ENTER);
	fwrite($file, TWO_TAB.'print \'TException: \'.$tx->getMessage()."\n";'.ENTER);
	fwrite($file, TWO_TAB.'$_return = array();'.ENTER);
	fwrite($file, TAB.'}'.ENTER);
	fwrite($file, TAB.'return $_return;'.ENTER);
	fwrite($file, '}'.TWO_ENTER);
	

	fwrite($file, 'function Get'.$clsname.'ListByField1($field, $value) {'.ENTER);
	fwrite($file, TAB.'$_return = array();'.ENTER);
	fwrite($file, TAB.'try {'.ENTER);
	fwrite($file, TWO_TAB.'$service_client = new ThriftClient('.$service_class.', HOST, PORT2);'.ENTER);
	fwrite($file, TWO_TAB.'$client = $service_client->getClient();'.ENTER);
	fwrite($file, TWO_TAB.'$_return = $client->Get'.$clsname.'ListByField1($field, strval($value));'.ENTER);
	fwrite($file, TAB.'} catch (TException $tx) {'.ENTER);
	fwrite($file, TWO_TAB.'print \'TException: \'.$tx->getMessage()."\n";'.ENTER);
	fwrite($file, TWO_TAB.'$_return = array();'.ENTER);
	fwrite($file, TAB.'}'.ENTER);
	fwrite($file, TAB.'return $_return;'.ENTER);
	fwrite($file, '}'.TWO_ENTER);


	fwrite($file, 'function Get'.$clsname.'ListByField2($field1, $value1, $field2, $value2) {'.ENTER);
	fwrite($file, TAB.'$_return = array();'.ENTER);
	fwrite($file, TAB.'try {'.ENTER);
	fwrite($file, TWO_TAB.'$service_client = new ThriftClient('.$service_class.', HOST, PORT2);'.ENTER);
	fwrite($file, TWO_TAB.'$client = $service_client->getClient();'.ENTER);
	fwrite($file, TWO_TAB.'$_return = $client->Get'.$clsname.'ListByField2($field1, strval($value1), $field2, strval($value2));'.ENTER);
	fwrite($file, TAB.'} catch (TException $tx) {'.ENTER);
	fwrite($file, TWO_TAB.'print \'TException: \'.$tx->getMessage()."\n";'.ENTER);
	fwrite($file, TWO_TAB.'$_return = array();'.ENTER);
	fwrite($file, TAB.'}'.ENTER);
	fwrite($file, TAB.'return $_return;'.ENTER);
	fwrite($file, '}'.TWO_ENTER);


	fwrite($file, 'function Get'.$clsname.'IdByFields($fields) {'.ENTER);
	fwrite($file, TAB.'$_return = -1;'.ENTER);
	fwrite($file, TAB.'try {'.ENTER);
	fwrite($file, TWO_TAB.'$service_client = new ThriftClient('.$service_class.', HOST, PORT2);'.ENTER);
	fwrite($file, TWO_TAB.'$client = $service_client->getClient();'.ENTER);
	fwrite($file, TWO_TAB.'$_return = $client->Get'.$clsname.'IdByFields($fields);'.ENTER);
	fwrite($file, TAB.'} catch (TException $tx) {'.ENTER);
	fwrite($file, TWO_TAB.'print \'TException: \'.$tx->getMessage()."\n";'.ENTER);
	fwrite($file, TWO_TAB.'$_return = -1;'.ENTER);
	fwrite($file, TAB.'}'.ENTER);
	fwrite($file, TAB.'return $_return;'.ENTER);
	fwrite($file, '}'.TWO_ENTER);


	fwrite($file, 'function Get'.$clsname.'IdByField1($field, $value) {'.ENTER);
	fwrite($file, TAB.'$_return = -1;'.ENTER);
	fwrite($file, TAB.'try {'.ENTER);
	fwrite($file, TWO_TAB.'$service_client = new ThriftClient('.$service_class.', HOST, PORT2);'.ENTER);
	fwrite($file, TWO_TAB.'$client = $service_client->getClient();'.ENTER);
	fwrite($file, TWO_TAB.'$_return = $client->Get'.$clsname.'IdByField1($field, strval($value));'.ENTER);
	fwrite($file, TAB.'} catch (TException $tx) {'.ENTER);
	fwrite($file, TWO_TAB.'print \'TException: \'.$tx->getMessage()."\n";'.ENTER);
	fwrite($file, TWO_TAB.'$_return = -1;'.ENTER);
	fwrite($file, TAB.'}'.ENTER);
	fwrite($file, TAB.'return $_return;'.ENTER);
	fwrite($file, '}'.TWO_ENTER);
	

	fwrite($file, 'function Get'.$clsname.'IdByField2($field1, $value1, $field2, $value2) {'.ENTER);
	fwrite($file, TAB.'$_return = -1;'.ENTER);
	fwrite($file, TAB.'try {'.ENTER);
	fwrite($file, TWO_TAB.'$service_client = new ThriftClient('.$service_class.', HOST, PORT2);'.ENTER);
	fwrite($file, TWO_TAB.'$client = $service_client->getClient();'.ENTER);
	fwrite($file, TWO_TAB.'$_return = $client->Get'.$clsname.'IdByField2($field1, strval($value1), $field2, strval($value2));'.ENTER);
	fwrite($file, TAB.'} catch (TException $tx) {'.ENTER);
	fwrite($file, TWO_TAB.'print \'TException: \'.$tx->getMessage()."\n";'.ENTER);
	fwrite($file, TWO_TAB.'$_return = -1;'.ENTER);
	fwrite($file, TAB.'}'.ENTER);
	fwrite($file, TAB.'return $_return;'.ENTER);
	fwrite($file, '}'.TWO_ENTER);
	

	fwrite($file, 'function Get'.$clsname.'IdListByFields($fields) {'.ENTER);
	fwrite($file, TAB.'$_return = array();'.ENTER);
	fwrite($file, TAB.'try {'.ENTER);
	fwrite($file, TWO_TAB.'$service_client = new ThriftClient('.$service_class.', HOST, PORT2);'.ENTER);
	fwrite($file, TWO_TAB.'$client = $service_client->getClient();'.ENTER);
	fwrite($file, TWO_TAB.'$_return = $client->Get'.$clsname.'IdListByFields($fields);'.ENTER);
	fwrite($file, TAB.'} catch (TException $tx) {'.ENTER);
	fwrite($file, TWO_TAB.'print \'TException: \'.$tx->getMessage()."\n";'.ENTER);
	fwrite($file, TWO_TAB.'$_return = array();'.ENTER);
	fwrite($file, TAB.'}'.ENTER);
	fwrite($file, TAB.'return $_return;'.ENTER);
	fwrite($file, '}'.TWO_ENTER);
	

	fwrite($file, 'function Get'.$clsname.'IdListByField1($field, $value) {'.ENTER);
	fwrite($file, TAB.'$_return = array();'.ENTER);
	fwrite($file, TAB.'try {'.ENTER);
	fwrite($file, TWO_TAB.'$service_client = new ThriftClient('.$service_class.', HOST, PORT2);'.ENTER);
	fwrite($file, TWO_TAB.'$client = $service_client->getClient();'.ENTER);
	fwrite($file, TWO_TAB.'$_return = $client->Get'.$clsname.'IdListByField1($field, strval($value));'.ENTER);
	fwrite($file, TAB.'} catch (TException $tx) {'.ENTER);
	fwrite($file, TWO_TAB.'print \'TException: \'.$tx->getMessage()."\n";'.ENTER);
	fwrite($file, TWO_TAB.'$_return = array();'.ENTER);
	fwrite($file, TAB.'}'.ENTER);
	fwrite($file, TAB.'return $_return;'.ENTER);
	fwrite($file, '}'.TWO_ENTER);


	fwrite($file, 'function Get'.$clsname.'IdListByField2($field1, $value1, $field2, $value2) {'.ENTER);
	fwrite($file, TAB.'$_return = array();'.ENTER);
	fwrite($file, TAB.'try {'.ENTER);
	fwrite($file, TWO_TAB.'$service_client = new ThriftClient('.$service_class.', HOST, PORT2);'.ENTER);
	fwrite($file, TWO_TAB.'$client = $service_client->getClient();'.ENTER);
	fwrite($file, TWO_TAB.'$_return = $client->Get'.$clsname.'IdListByField2($field1, strval($value1), $field2, strval($value2));'.ENTER);
	fwrite($file, TAB.'} catch (TException $tx) {'.ENTER);
	fwrite($file, TWO_TAB.'print \'TException: \'.$tx->getMessage()."\n";'.ENTER);
	fwrite($file, TWO_TAB.'$_return = array();'.ENTER);
	fwrite($file, TAB.'}'.ENTER);
	fwrite($file, TAB.'return $_return;'.ENTER);
	fwrite($file, '}'.TWO_ENTER);

	fwrite($file, 'function Get'.$clsname.'ListByForeignKey($fkey, $id) {'.ENTER);
	fwrite($file, TAB.'$_return = array();'.ENTER);
	fwrite($file, TAB.'try {'.ENTER);
	fwrite($file, TWO_TAB.'$service_client = new ThriftClient('.$service_class.', HOST, PORT2);'.ENTER);
	fwrite($file, TWO_TAB.'$client = $service_client->getClient();'.ENTER);
	fwrite($file, TWO_TAB.'$_return = $client->Get'.$clsname.'ListByForeignKey($fkey, intval($id));'.ENTER);
	fwrite($file, TAB.'} catch (TException $tx) {'.ENTER);
	fwrite($file, TWO_TAB.'print \'TException: \'.$tx->getMessage()."\n";'.ENTER);
	fwrite($file, TWO_TAB.'$_return = array();'.ENTER);
	fwrite($file, TAB.'}'.ENTER);
	fwrite($file, TAB.'return $_return;'.ENTER);
	fwrite($file, '}'.TWO_ENTER);


	fwrite($file, 'function Get'.$clsname.'IdListByForeignKey($fkey, $id) {'.ENTER);
	fwrite($file, TAB.'$_return = array();'.ENTER);
	fwrite($file, TAB.'try {'.ENTER);
	fwrite($file, TWO_TAB.'$service_client = new ThriftClient('.$service_class.', HOST, PORT2);'.ENTER);
	fwrite($file, TWO_TAB.'$client = $service_client->getClient();'.ENTER);
	fwrite($file, TWO_TAB.'$_return = $client->Get'.$clsname.'IdListByForeignKey($fkey, intval($id));'.ENTER);
	fwrite($file, TAB.'} catch (TException $tx) {'.ENTER);
	fwrite($file, TWO_TAB.'print \'TException: \'.$tx->getMessage()."\n";'.ENTER);
	fwrite($file, TWO_TAB.'$_return = array();'.ENTER);
	fwrite($file, TAB.'}'.ENTER);
	fwrite($file, TAB.'return $_return;'.ENTER);
	fwrite($file, '}'.TWO_ENTER);


	fwrite($file, TWO_ENTER);
}

function gen_sql_helper_of_php_client($file, $tables, $relations)
{
	fwrite($file, '<?php'.TWO_ENTER);
	fwrite($file, 'namespace SQLClientHelper;'.ENTER);
	fwrite($file, "require_once __DIR__.'/ThriftClient.php';".ENTER);
	fwrite($file, 'use \ThriftClient\ThriftClient;'.TWO_ENTER);
	
	foreach($tables as $tbl => $fields) {
		__gen_sql_helper_of_php_client($file, $tbl, $fields, $relations);
	}
}

function __gen_sql_type_py_file($file, $tbl_name, $fields, $relations)
{
	//去掉cbm前缀,作为文件名
	$fname = table_no_prefix($tbl_name);

	//得到类名
	$clsname = camel_case($fname);

	fwrite($file, ENTER.DBL_QUOT.$clsname.DBL_QUOT.":{".ENTER);
	//下标序号
	$count = 1;
	//字段变量
	foreach ($fields as $name => $type) {
		$py_type_func = cpp_type_to_py_type_func_dict($type);
		$var_name = $name;
		$field_name = table_no_prefix(table_no_id($name));
		// if($name == 'id') continue;
		//该字段是外键(所有的外键ID都是以_id结尾的)
		// if($field_name != $name && $name != 'id') {
		// 	$param_type = "orm::RecordPtr";
		// 	$var_name = $field_name;
		// }
		fwrite($file, TAB.DBL_QUOT.$var_name.DBL_QUOT.":".$py_type_func);
		if($count < count($fields)) {
			fwrite($file, ',');
		}
		fwrite($file, ENTER);
		$count++;
	}
	fwrite($file, "}");
}

function __gen_sql_fkey_py_file($file, $tbl_name, $fields, $relations)
{
	//去掉cbm前缀,作为文件名
	$fname = table_no_prefix($tbl_name);

	//得到类名
	$clsname = camel_case($fname);

	fwrite($file, ENTER.DBL_QUOT.$clsname.DBL_QUOT.":{".ENTER);
	//下标序号
	$count = 1;
	//字段变量
	foreach ($fields as $name => $type) {
		$var_name = $name;
		$field_name = table_no_prefix(table_no_id($name));
		$key_type = 0;
		if($name == 'id') {
			$key_type = 1; // 主键
		}
		//该字段是外键(所有的外键ID都是以_id结尾的)
		else if($field_name != $name && $name != 'id') {
			$var_name = $field_name;
			$key_type = 2; // 外键
		}
		
		fwrite($file, TAB.DBL_QUOT.$name.DBL_QUOT.":".$key_type);
		if($count < count($fields)) {
			fwrite($file, ',');
		}
		fwrite($file, ENTER);
		$count++;
	}
	fwrite($file, "}");
}
function gen_sql_type_py_file($file, $tables, $relations)
{
	$count = 1;

	fwrite($file, 'info = {'.ENTER);
	foreach($tables as $tbl => $fields) {
		__gen_sql_type_py_file($file, $tbl, $fields, $relations);

		if($count < count($tables)) {
			fwrite($file, ',');
		}
		$count++;
	}
	fwrite($file, ENTER.'}'.ENTER);

	$count = 1;
	fwrite($file, ENTER."fkey = {".ENTER);
	// 写入外键关系
	foreach($tables as $tbl => $fields) {
		__gen_sql_fkey_py_file($file, $tbl, $fields, $relations);
	
		if($count < count($tables)) {
			fwrite($file, ',');
		}
		$count++;
	}
	fwrite($file, ENTER.'}'.ENTER);
}

function gen_thrift_file($tables, $relations)
{
	$entity_thrift_file = fopen('sql_service_types.thrift', 'w');
	gen_entity_type_thrift($entity_thrift_file, $tables, $relations);
	fclose($entity_thrift_file);

	$sql_thrift_file = fopen('sql_service.thrift', 'w');
	gen_sql_service_thrift($sql_thrift_file, $tables, $relations);
	fclose($sql_thrift_file);

	$py_file = fopen('SQLServerHelper.py', 'w');
	gen_sql_service_handler_of_py_server($py_file, $tables, $relations);
	fclose($py_file);

	$hpp_file = fopen('SQLClientHelper.h', 'w');
	gen_sql_helper_of_hpp_client($hpp_file, $tables, $relations);
	fclose($hpp_file);

	$cpp_file = fopen('SQLClientHelper.cpp', 'w');
	gen_sql_helper_of_cpp_client($cpp_file, $tables, $relations);
	fclose($cpp_file);

	$py_file = fopen('SQLClientHelper.py', 'w');
	gen_sql_helper_of_py_client($py_file, $tables, $relations);
	fclose($py_file);

	$php_file = fopen('SQLClientHelper.php', 'w');
	gen_sql_helper_of_php_client($php_file, $tables, $relations);
	fclose($php_file);

	$py_file = fopen('CbmRtti.py', 'w');
	gen_sql_type_py_file($py_file, $tables, $relations);
	fclose($py_file);
}

function make_thrift_files($tables, $relations)
{
	//生成thrift的IDL接口
	gen_thrift_file($tables, $relations);
}

function merge_thrift_files()
{
	$file = fopen('cbm.thrift', 'w');
	fwrite($file, ENTER."namespace cpp cbm");
	fwrite($file, ENTER."namespace php cbm");
	fwrite($file, ENTER."namespace py cbm".ENTER);

	$c1 = file_get_contents('sql_service_types.thrift');
	$c2 = file_get_contents('cbm_service_types.thrift');
	$c3 = file_get_contents('sql_service.thrift');
	$c4 = file_get_contents('cbm_service.thrift');

	fwrite($file, $c1);
	fwrite($file, $c2);

	fwrite($file, ENTER.'service CbmService {'.ENTER);
	fwrite($file, $c3.ENTER);
	fwrite($file, $c4.ENTER);
	fwrite($file, ENTER.'}');

	fclose($file);
}

?>
