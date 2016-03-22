<?php

namespace SQLClientHelper;
require_once __DIR__.'/ThriftClient.php';
use \ThriftClient\ThriftClient;

//$clsname 类型的CRUD操作

function AddAccount($fname) {
	$ret = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->AddAccount($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = -1;
	}
	return $ret;
}

function DeleteAccount($id) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->DeleteAccount(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function UpdateAccount($fname) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->UpdateAccount($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function GetAccountById($id) {
	$_return = new Account();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetAccountById(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetAccountByForeignKey($fkey, $id) {
	$_return = new Account();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetAccountByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetAccountIdByForeignKey($fkey, $id) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetAccountIdByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetAccountList() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetAccountList();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetAccountIds() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetAccountIds();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetAccountNames() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetAccountNames();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function AddMoreAccount($objs) {
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->AddMoreAccount($objs);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function DeleteMoreAccount($obj_ids) {
	if(empty($obj_ids)) return;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->DeleteMoreAccount($obj_ids);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function GetAccountByFields($fields) {
	$_return = new Account();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetAccountByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetAccountByField1($field, $value) {
	$_return = new Account();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetAccountByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetAccountByField2($field1, $value1, $field2, $value2) {
	$_return = new Account();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetAccountByField2($field1, strval($value1), $field2, str($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetAccountListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetAccountListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetAccountListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetAccountListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetAccountListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetAccountListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetAccountIdByFields($fields) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetAccountIdByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetAccountIdByField1($field, $value) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetAccountIdByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetAccountIdByField2($field1, $value1, $field2, $value2) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetAccountIdByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetAccountIdListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetAccountIdListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetAccountIdListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetAccountIdListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetAccountIdListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetAccountIdListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetAccountListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetAccountListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetAccountIdListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetAccountIdListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}



//$clsname 类型的CRUD操作

function AddAdjLayer($fname) {
	$ret = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->AddAdjLayer($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = -1;
	}
	return $ret;
}

function DeleteAdjLayer($id) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->DeleteAdjLayer(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function UpdateAdjLayer($fname) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->UpdateAdjLayer($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function GetAdjLayerById($id) {
	$_return = new AdjLayer();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetAdjLayerById(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetAdjLayerByForeignKey($fkey, $id) {
	$_return = new AdjLayer();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetAdjLayerByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetAdjLayerIdByForeignKey($fkey, $id) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetAdjLayerIdByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetAdjLayerList() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetAdjLayerList();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetAdjLayerIds() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetAdjLayerIds();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetAdjLayerNames() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetAdjLayerNames();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function AddMoreAdjLayer($objs) {
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->AddMoreAdjLayer($objs);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function DeleteMoreAdjLayer($obj_ids) {
	if(empty($obj_ids)) return;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->DeleteMoreAdjLayer($obj_ids);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function GetAdjLayerByFields($fields) {
	$_return = new AdjLayer();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetAdjLayerByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetAdjLayerByField1($field, $value) {
	$_return = new AdjLayer();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetAdjLayerByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetAdjLayerByField2($field1, $value1, $field2, $value2) {
	$_return = new AdjLayer();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetAdjLayerByField2($field1, strval($value1), $field2, str($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetAdjLayerListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetAdjLayerListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetAdjLayerListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetAdjLayerListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetAdjLayerListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetAdjLayerListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetAdjLayerIdByFields($fields) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetAdjLayerIdByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetAdjLayerIdByField1($field, $value) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetAdjLayerIdByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetAdjLayerIdByField2($field1, $value1, $field2, $value2) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetAdjLayerIdByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetAdjLayerIdListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetAdjLayerIdListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetAdjLayerIdListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetAdjLayerIdListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetAdjLayerIdListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetAdjLayerIdListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetAdjLayerListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetAdjLayerListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetAdjLayerIdListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetAdjLayerIdListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}



//$clsname 类型的CRUD操作

function AddCoal($fname) {
	$ret = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->AddCoal($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = -1;
	}
	return $ret;
}

function DeleteCoal($id) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->DeleteCoal(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function UpdateCoal($fname) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->UpdateCoal($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function GetCoalById($id) {
	$_return = new Coal();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetCoalById(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetCoalByForeignKey($fkey, $id) {
	$_return = new Coal();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetCoalByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetCoalIdByForeignKey($fkey, $id) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetCoalIdByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetCoalList() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetCoalList();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetCoalIds() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetCoalIds();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetCoalNames() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetCoalNames();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function AddMoreCoal($objs) {
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->AddMoreCoal($objs);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function DeleteMoreCoal($obj_ids) {
	if(empty($obj_ids)) return;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->DeleteMoreCoal($obj_ids);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function GetCoalByFields($fields) {
	$_return = new Coal();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetCoalByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetCoalByField1($field, $value) {
	$_return = new Coal();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetCoalByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetCoalByField2($field1, $value1, $field2, $value2) {
	$_return = new Coal();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetCoalByField2($field1, strval($value1), $field2, str($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetCoalListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetCoalListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetCoalListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetCoalListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetCoalListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetCoalListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetCoalIdByFields($fields) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetCoalIdByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetCoalIdByField1($field, $value) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetCoalIdByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetCoalIdByField2($field1, $value1, $field2, $value2) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetCoalIdByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetCoalIdListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetCoalIdListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetCoalIdListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetCoalIdListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetCoalIdListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetCoalIdListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetCoalListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetCoalListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetCoalIdListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetCoalIdListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}



//$clsname 类型的CRUD操作

function AddComplexity($fname) {
	$ret = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->AddComplexity($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = -1;
	}
	return $ret;
}

function DeleteComplexity($id) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->DeleteComplexity(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function UpdateComplexity($fname) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->UpdateComplexity($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function GetComplexityById($id) {
	$_return = new Complexity();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetComplexityById(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetComplexityByForeignKey($fkey, $id) {
	$_return = new Complexity();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetComplexityByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetComplexityIdByForeignKey($fkey, $id) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetComplexityIdByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetComplexityList() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetComplexityList();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetComplexityIds() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetComplexityIds();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetComplexityNames() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetComplexityNames();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function AddMoreComplexity($objs) {
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->AddMoreComplexity($objs);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function DeleteMoreComplexity($obj_ids) {
	if(empty($obj_ids)) return;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->DeleteMoreComplexity($obj_ids);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function GetComplexityByFields($fields) {
	$_return = new Complexity();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetComplexityByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetComplexityByField1($field, $value) {
	$_return = new Complexity();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetComplexityByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetComplexityByField2($field1, $value1, $field2, $value2) {
	$_return = new Complexity();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetComplexityByField2($field1, strval($value1), $field2, str($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetComplexityListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetComplexityListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetComplexityListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetComplexityListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetComplexityListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetComplexityListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetComplexityIdByFields($fields) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetComplexityIdByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetComplexityIdByField1($field, $value) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetComplexityIdByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetComplexityIdByField2($field1, $value1, $field2, $value2) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetComplexityIdByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetComplexityIdListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetComplexityIdListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetComplexityIdListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetComplexityIdListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetComplexityIdListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetComplexityIdListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetComplexityListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetComplexityListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetComplexityIdListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetComplexityIdListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}



//$clsname 类型的CRUD操作

function AddDesignDrillingSurfTechnology($fname) {
	$ret = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->AddDesignDrillingSurfTechnology($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = -1;
	}
	return $ret;
}

function DeleteDesignDrillingSurfTechnology($id) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->DeleteDesignDrillingSurfTechnology(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function UpdateDesignDrillingSurfTechnology($fname) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->UpdateDesignDrillingSurfTechnology($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function GetDesignDrillingSurfTechnologyById($id) {
	$_return = new DesignDrillingSurfTechnology();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignDrillingSurfTechnologyById(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignDrillingSurfTechnologyByForeignKey($fkey, $id) {
	$_return = new DesignDrillingSurfTechnology();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignDrillingSurfTechnologyByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignDrillingSurfTechnologyIdByForeignKey($fkey, $id) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignDrillingSurfTechnologyIdByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetDesignDrillingSurfTechnologyList() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignDrillingSurfTechnologyList();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignDrillingSurfTechnologyIds() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignDrillingSurfTechnologyIds();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignDrillingSurfTechnologyNames() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignDrillingSurfTechnologyNames();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function AddMoreDesignDrillingSurfTechnology($objs) {
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->AddMoreDesignDrillingSurfTechnology($objs);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function DeleteMoreDesignDrillingSurfTechnology($obj_ids) {
	if(empty($obj_ids)) return;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->DeleteMoreDesignDrillingSurfTechnology($obj_ids);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function GetDesignDrillingSurfTechnologyByFields($fields) {
	$_return = new DesignDrillingSurfTechnology();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignDrillingSurfTechnologyByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignDrillingSurfTechnologyByField1($field, $value) {
	$_return = new DesignDrillingSurfTechnology();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignDrillingSurfTechnologyByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignDrillingSurfTechnologyByField2($field1, $value1, $field2, $value2) {
	$_return = new DesignDrillingSurfTechnology();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignDrillingSurfTechnologyByField2($field1, strval($value1), $field2, str($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignDrillingSurfTechnologyListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignDrillingSurfTechnologyListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignDrillingSurfTechnologyListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignDrillingSurfTechnologyListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignDrillingSurfTechnologyListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignDrillingSurfTechnologyListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignDrillingSurfTechnologyIdByFields($fields) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignDrillingSurfTechnologyIdByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetDesignDrillingSurfTechnologyIdByField1($field, $value) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignDrillingSurfTechnologyIdByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetDesignDrillingSurfTechnologyIdByField2($field1, $value1, $field2, $value2) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignDrillingSurfTechnologyIdByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetDesignDrillingSurfTechnologyIdListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignDrillingSurfTechnologyIdListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignDrillingSurfTechnologyIdListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignDrillingSurfTechnologyIdListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignDrillingSurfTechnologyIdListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignDrillingSurfTechnologyIdListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignDrillingSurfTechnologyListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignDrillingSurfTechnologyListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignDrillingSurfTechnologyIdListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignDrillingSurfTechnologyIdListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}



//$clsname 类型的CRUD操作

function AddDesignEvalUnit($fname) {
	$ret = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->AddDesignEvalUnit($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = -1;
	}
	return $ret;
}

function DeleteDesignEvalUnit($id) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->DeleteDesignEvalUnit(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function UpdateDesignEvalUnit($fname) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->UpdateDesignEvalUnit($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function GetDesignEvalUnitById($id) {
	$_return = new DesignEvalUnit();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignEvalUnitById(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignEvalUnitByForeignKey($fkey, $id) {
	$_return = new DesignEvalUnit();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignEvalUnitByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignEvalUnitIdByForeignKey($fkey, $id) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignEvalUnitIdByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetDesignEvalUnitList() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignEvalUnitList();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignEvalUnitIds() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignEvalUnitIds();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignEvalUnitNames() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignEvalUnitNames();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function AddMoreDesignEvalUnit($objs) {
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->AddMoreDesignEvalUnit($objs);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function DeleteMoreDesignEvalUnit($obj_ids) {
	if(empty($obj_ids)) return;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->DeleteMoreDesignEvalUnit($obj_ids);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function GetDesignEvalUnitByFields($fields) {
	$_return = new DesignEvalUnit();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignEvalUnitByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignEvalUnitByField1($field, $value) {
	$_return = new DesignEvalUnit();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignEvalUnitByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignEvalUnitByField2($field1, $value1, $field2, $value2) {
	$_return = new DesignEvalUnit();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignEvalUnitByField2($field1, strval($value1), $field2, str($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignEvalUnitListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignEvalUnitListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignEvalUnitListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignEvalUnitListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignEvalUnitListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignEvalUnitListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignEvalUnitIdByFields($fields) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignEvalUnitIdByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetDesignEvalUnitIdByField1($field, $value) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignEvalUnitIdByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetDesignEvalUnitIdByField2($field1, $value1, $field2, $value2) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignEvalUnitIdByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetDesignEvalUnitIdListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignEvalUnitIdListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignEvalUnitIdListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignEvalUnitIdListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignEvalUnitIdListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignEvalUnitIdListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignEvalUnitListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignEvalUnitListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignEvalUnitIdListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignEvalUnitIdListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}



//$clsname 类型的CRUD操作

function AddDesignEvalUnitPartition($fname) {
	$ret = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->AddDesignEvalUnitPartition($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = -1;
	}
	return $ret;
}

function DeleteDesignEvalUnitPartition($id) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->DeleteDesignEvalUnitPartition(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function UpdateDesignEvalUnitPartition($fname) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->UpdateDesignEvalUnitPartition($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function GetDesignEvalUnitPartitionById($id) {
	$_return = new DesignEvalUnitPartition();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignEvalUnitPartitionById(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignEvalUnitPartitionByForeignKey($fkey, $id) {
	$_return = new DesignEvalUnitPartition();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignEvalUnitPartitionByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignEvalUnitPartitionIdByForeignKey($fkey, $id) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignEvalUnitPartitionIdByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetDesignEvalUnitPartitionList() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignEvalUnitPartitionList();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignEvalUnitPartitionIds() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignEvalUnitPartitionIds();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignEvalUnitPartitionNames() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignEvalUnitPartitionNames();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function AddMoreDesignEvalUnitPartition($objs) {
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->AddMoreDesignEvalUnitPartition($objs);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function DeleteMoreDesignEvalUnitPartition($obj_ids) {
	if(empty($obj_ids)) return;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->DeleteMoreDesignEvalUnitPartition($obj_ids);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function GetDesignEvalUnitPartitionByFields($fields) {
	$_return = new DesignEvalUnitPartition();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignEvalUnitPartitionByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignEvalUnitPartitionByField1($field, $value) {
	$_return = new DesignEvalUnitPartition();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignEvalUnitPartitionByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignEvalUnitPartitionByField2($field1, $value1, $field2, $value2) {
	$_return = new DesignEvalUnitPartition();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignEvalUnitPartitionByField2($field1, strval($value1), $field2, str($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignEvalUnitPartitionListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignEvalUnitPartitionListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignEvalUnitPartitionListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignEvalUnitPartitionListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignEvalUnitPartitionListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignEvalUnitPartitionListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignEvalUnitPartitionIdByFields($fields) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignEvalUnitPartitionIdByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetDesignEvalUnitPartitionIdByField1($field, $value) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignEvalUnitPartitionIdByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetDesignEvalUnitPartitionIdByField2($field1, $value1, $field2, $value2) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignEvalUnitPartitionIdByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetDesignEvalUnitPartitionIdListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignEvalUnitPartitionIdListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignEvalUnitPartitionIdListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignEvalUnitPartitionIdListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignEvalUnitPartitionIdListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignEvalUnitPartitionIdListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignEvalUnitPartitionListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignEvalUnitPartitionListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignEvalUnitPartitionIdListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignEvalUnitPartitionIdListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}



//$clsname 类型的CRUD操作

function AddDesignGoafPore($fname) {
	$ret = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->AddDesignGoafPore($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = -1;
	}
	return $ret;
}

function DeleteDesignGoafPore($id) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->DeleteDesignGoafPore(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function UpdateDesignGoafPore($fname) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->UpdateDesignGoafPore($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function GetDesignGoafPoreById($id) {
	$_return = new DesignGoafPore();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignGoafPoreById(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignGoafPoreByForeignKey($fkey, $id) {
	$_return = new DesignGoafPore();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignGoafPoreByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignGoafPoreIdByForeignKey($fkey, $id) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignGoafPoreIdByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetDesignGoafPoreList() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignGoafPoreList();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignGoafPoreIds() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignGoafPoreIds();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignGoafPoreNames() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignGoafPoreNames();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function AddMoreDesignGoafPore($objs) {
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->AddMoreDesignGoafPore($objs);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function DeleteMoreDesignGoafPore($obj_ids) {
	if(empty($obj_ids)) return;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->DeleteMoreDesignGoafPore($obj_ids);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function GetDesignGoafPoreByFields($fields) {
	$_return = new DesignGoafPore();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignGoafPoreByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignGoafPoreByField1($field, $value) {
	$_return = new DesignGoafPore();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignGoafPoreByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignGoafPoreByField2($field1, $value1, $field2, $value2) {
	$_return = new DesignGoafPore();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignGoafPoreByField2($field1, strval($value1), $field2, str($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignGoafPoreListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignGoafPoreListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignGoafPoreListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignGoafPoreListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignGoafPoreListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignGoafPoreListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignGoafPoreIdByFields($fields) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignGoafPoreIdByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetDesignGoafPoreIdByField1($field, $value) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignGoafPoreIdByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetDesignGoafPoreIdByField2($field1, $value1, $field2, $value2) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignGoafPoreIdByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetDesignGoafPoreIdListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignGoafPoreIdListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignGoafPoreIdListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignGoafPoreIdListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignGoafPoreIdListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignGoafPoreIdListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignGoafPoreListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignGoafPoreListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignGoafPoreIdListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignGoafPoreIdListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}



//$clsname 类型的CRUD操作

function AddDesignGoafTechnology($fname) {
	$ret = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->AddDesignGoafTechnology($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = -1;
	}
	return $ret;
}

function DeleteDesignGoafTechnology($id) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->DeleteDesignGoafTechnology(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function UpdateDesignGoafTechnology($fname) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->UpdateDesignGoafTechnology($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function GetDesignGoafTechnologyById($id) {
	$_return = new DesignGoafTechnology();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignGoafTechnologyById(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignGoafTechnologyByForeignKey($fkey, $id) {
	$_return = new DesignGoafTechnology();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignGoafTechnologyByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignGoafTechnologyIdByForeignKey($fkey, $id) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignGoafTechnologyIdByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetDesignGoafTechnologyList() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignGoafTechnologyList();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignGoafTechnologyIds() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignGoafTechnologyIds();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignGoafTechnologyNames() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignGoafTechnologyNames();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function AddMoreDesignGoafTechnology($objs) {
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->AddMoreDesignGoafTechnology($objs);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function DeleteMoreDesignGoafTechnology($obj_ids) {
	if(empty($obj_ids)) return;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->DeleteMoreDesignGoafTechnology($obj_ids);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function GetDesignGoafTechnologyByFields($fields) {
	$_return = new DesignGoafTechnology();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignGoafTechnologyByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignGoafTechnologyByField1($field, $value) {
	$_return = new DesignGoafTechnology();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignGoafTechnologyByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignGoafTechnologyByField2($field1, $value1, $field2, $value2) {
	$_return = new DesignGoafTechnology();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignGoafTechnologyByField2($field1, strval($value1), $field2, str($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignGoafTechnologyListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignGoafTechnologyListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignGoafTechnologyListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignGoafTechnologyListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignGoafTechnologyListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignGoafTechnologyListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignGoafTechnologyIdByFields($fields) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignGoafTechnologyIdByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetDesignGoafTechnologyIdByField1($field, $value) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignGoafTechnologyIdByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetDesignGoafTechnologyIdByField2($field1, $value1, $field2, $value2) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignGoafTechnologyIdByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetDesignGoafTechnologyIdListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignGoafTechnologyIdListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignGoafTechnologyIdListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignGoafTechnologyIdListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignGoafTechnologyIdListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignGoafTechnologyIdListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignGoafTechnologyListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignGoafTechnologyListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignGoafTechnologyIdListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignGoafTechnologyIdListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}



//$clsname 类型的CRUD操作

function AddDesignPore($fname) {
	$ret = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->AddDesignPore($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = -1;
	}
	return $ret;
}

function DeleteDesignPore($id) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->DeleteDesignPore(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function UpdateDesignPore($fname) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->UpdateDesignPore($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function GetDesignPoreById($id) {
	$_return = new DesignPore();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignPoreById(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignPoreByForeignKey($fkey, $id) {
	$_return = new DesignPore();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignPoreByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignPoreIdByForeignKey($fkey, $id) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignPoreIdByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetDesignPoreList() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignPoreList();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignPoreIds() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignPoreIds();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignPoreNames() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignPoreNames();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function AddMoreDesignPore($objs) {
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->AddMoreDesignPore($objs);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function DeleteMoreDesignPore($obj_ids) {
	if(empty($obj_ids)) return;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->DeleteMoreDesignPore($obj_ids);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function GetDesignPoreByFields($fields) {
	$_return = new DesignPore();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignPoreByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignPoreByField1($field, $value) {
	$_return = new DesignPore();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignPoreByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignPoreByField2($field1, $value1, $field2, $value2) {
	$_return = new DesignPore();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignPoreByField2($field1, strval($value1), $field2, str($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignPoreListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignPoreListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignPoreListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignPoreListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignPoreListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignPoreListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignPoreIdByFields($fields) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignPoreIdByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetDesignPoreIdByField1($field, $value) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignPoreIdByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetDesignPoreIdByField2($field1, $value1, $field2, $value2) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignPoreIdByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetDesignPoreIdListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignPoreIdListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignPoreIdListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignPoreIdListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignPoreIdListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignPoreIdListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignPoreListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignPoreListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignPoreIdListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignPoreIdListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}



//$clsname 类型的CRUD操作

function AddDesignSite($fname) {
	$ret = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->AddDesignSite($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = -1;
	}
	return $ret;
}

function DeleteDesignSite($id) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->DeleteDesignSite(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function UpdateDesignSite($fname) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->UpdateDesignSite($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function GetDesignSiteById($id) {
	$_return = new DesignSite();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignSiteById(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignSiteByForeignKey($fkey, $id) {
	$_return = new DesignSite();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignSiteByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignSiteIdByForeignKey($fkey, $id) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignSiteIdByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetDesignSiteList() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignSiteList();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignSiteIds() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignSiteIds();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignSiteNames() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignSiteNames();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function AddMoreDesignSite($objs) {
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->AddMoreDesignSite($objs);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function DeleteMoreDesignSite($obj_ids) {
	if(empty($obj_ids)) return;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->DeleteMoreDesignSite($obj_ids);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function GetDesignSiteByFields($fields) {
	$_return = new DesignSite();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignSiteByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignSiteByField1($field, $value) {
	$_return = new DesignSite();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignSiteByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignSiteByField2($field1, $value1, $field2, $value2) {
	$_return = new DesignSite();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignSiteByField2($field1, strval($value1), $field2, str($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignSiteListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignSiteListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignSiteListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignSiteListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignSiteListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignSiteListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignSiteIdByFields($fields) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignSiteIdByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetDesignSiteIdByField1($field, $value) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignSiteIdByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetDesignSiteIdByField2($field1, $value1, $field2, $value2) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignSiteIdByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetDesignSiteIdListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignSiteIdListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignSiteIdListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignSiteIdListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignSiteIdListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignSiteIdListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignSiteListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignSiteListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignSiteIdListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignSiteIdListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}



//$clsname 类型的CRUD操作

function AddDesignTechnology($fname) {
	$ret = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->AddDesignTechnology($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = -1;
	}
	return $ret;
}

function DeleteDesignTechnology($id) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->DeleteDesignTechnology(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function UpdateDesignTechnology($fname) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->UpdateDesignTechnology($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function GetDesignTechnologyById($id) {
	$_return = new DesignTechnology();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignTechnologyById(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignTechnologyByForeignKey($fkey, $id) {
	$_return = new DesignTechnology();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignTechnologyByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignTechnologyIdByForeignKey($fkey, $id) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignTechnologyIdByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetDesignTechnologyList() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignTechnologyList();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignTechnologyIds() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignTechnologyIds();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignTechnologyNames() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignTechnologyNames();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function AddMoreDesignTechnology($objs) {
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->AddMoreDesignTechnology($objs);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function DeleteMoreDesignTechnology($obj_ids) {
	if(empty($obj_ids)) return;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->DeleteMoreDesignTechnology($obj_ids);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function GetDesignTechnologyByFields($fields) {
	$_return = new DesignTechnology();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignTechnologyByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignTechnologyByField1($field, $value) {
	$_return = new DesignTechnology();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignTechnologyByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignTechnologyByField2($field1, $value1, $field2, $value2) {
	$_return = new DesignTechnology();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignTechnologyByField2($field1, strval($value1), $field2, str($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignTechnologyListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignTechnologyListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignTechnologyListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignTechnologyListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignTechnologyListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignTechnologyListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignTechnologyIdByFields($fields) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignTechnologyIdByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetDesignTechnologyIdByField1($field, $value) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignTechnologyIdByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetDesignTechnologyIdByField2($field1, $value1, $field2, $value2) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignTechnologyIdByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetDesignTechnologyIdListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignTechnologyIdListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignTechnologyIdListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignTechnologyIdListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignTechnologyIdListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignTechnologyIdListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignTechnologyListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignTechnologyListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignTechnologyIdListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignTechnologyIdListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}



//$clsname 类型的CRUD操作

function AddDesignTunnelControlPoint($fname) {
	$ret = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->AddDesignTunnelControlPoint($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = -1;
	}
	return $ret;
}

function DeleteDesignTunnelControlPoint($id) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->DeleteDesignTunnelControlPoint(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function UpdateDesignTunnelControlPoint($fname) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->UpdateDesignTunnelControlPoint($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function GetDesignTunnelControlPointById($id) {
	$_return = new DesignTunnelControlPoint();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignTunnelControlPointById(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignTunnelControlPointByForeignKey($fkey, $id) {
	$_return = new DesignTunnelControlPoint();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignTunnelControlPointByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignTunnelControlPointIdByForeignKey($fkey, $id) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignTunnelControlPointIdByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetDesignTunnelControlPointList() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignTunnelControlPointList();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignTunnelControlPointIds() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignTunnelControlPointIds();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignTunnelControlPointNames() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignTunnelControlPointNames();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function AddMoreDesignTunnelControlPoint($objs) {
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->AddMoreDesignTunnelControlPoint($objs);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function DeleteMoreDesignTunnelControlPoint($obj_ids) {
	if(empty($obj_ids)) return;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->DeleteMoreDesignTunnelControlPoint($obj_ids);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function GetDesignTunnelControlPointByFields($fields) {
	$_return = new DesignTunnelControlPoint();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignTunnelControlPointByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignTunnelControlPointByField1($field, $value) {
	$_return = new DesignTunnelControlPoint();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignTunnelControlPointByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignTunnelControlPointByField2($field1, $value1, $field2, $value2) {
	$_return = new DesignTunnelControlPoint();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignTunnelControlPointByField2($field1, strval($value1), $field2, str($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignTunnelControlPointListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignTunnelControlPointListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignTunnelControlPointListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignTunnelControlPointListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignTunnelControlPointListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignTunnelControlPointListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignTunnelControlPointIdByFields($fields) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignTunnelControlPointIdByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetDesignTunnelControlPointIdByField1($field, $value) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignTunnelControlPointIdByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetDesignTunnelControlPointIdByField2($field1, $value1, $field2, $value2) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignTunnelControlPointIdByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetDesignTunnelControlPointIdListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignTunnelControlPointIdListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignTunnelControlPointIdListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignTunnelControlPointIdListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignTunnelControlPointIdListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignTunnelControlPointIdListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignTunnelControlPointListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignTunnelControlPointListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignTunnelControlPointIdListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignTunnelControlPointIdListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}



//$clsname 类型的CRUD操作

function AddDesignWorkSurfControlPoint($fname) {
	$ret = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->AddDesignWorkSurfControlPoint($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = -1;
	}
	return $ret;
}

function DeleteDesignWorkSurfControlPoint($id) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->DeleteDesignWorkSurfControlPoint(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function UpdateDesignWorkSurfControlPoint($fname) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->UpdateDesignWorkSurfControlPoint($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function GetDesignWorkSurfControlPointById($id) {
	$_return = new DesignWorkSurfControlPoint();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignWorkSurfControlPointById(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignWorkSurfControlPointByForeignKey($fkey, $id) {
	$_return = new DesignWorkSurfControlPoint();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignWorkSurfControlPointByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignWorkSurfControlPointIdByForeignKey($fkey, $id) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignWorkSurfControlPointIdByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetDesignWorkSurfControlPointList() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignWorkSurfControlPointList();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignWorkSurfControlPointIds() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignWorkSurfControlPointIds();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignWorkSurfControlPointNames() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignWorkSurfControlPointNames();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function AddMoreDesignWorkSurfControlPoint($objs) {
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->AddMoreDesignWorkSurfControlPoint($objs);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function DeleteMoreDesignWorkSurfControlPoint($obj_ids) {
	if(empty($obj_ids)) return;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->DeleteMoreDesignWorkSurfControlPoint($obj_ids);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function GetDesignWorkSurfControlPointByFields($fields) {
	$_return = new DesignWorkSurfControlPoint();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignWorkSurfControlPointByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignWorkSurfControlPointByField1($field, $value) {
	$_return = new DesignWorkSurfControlPoint();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignWorkSurfControlPointByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignWorkSurfControlPointByField2($field1, $value1, $field2, $value2) {
	$_return = new DesignWorkSurfControlPoint();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignWorkSurfControlPointByField2($field1, strval($value1), $field2, str($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignWorkSurfControlPointListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignWorkSurfControlPointListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignWorkSurfControlPointListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignWorkSurfControlPointListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignWorkSurfControlPointListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignWorkSurfControlPointListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignWorkSurfControlPointIdByFields($fields) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignWorkSurfControlPointIdByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetDesignWorkSurfControlPointIdByField1($field, $value) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignWorkSurfControlPointIdByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetDesignWorkSurfControlPointIdByField2($field1, $value1, $field2, $value2) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignWorkSurfControlPointIdByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetDesignWorkSurfControlPointIdListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignWorkSurfControlPointIdListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignWorkSurfControlPointIdListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignWorkSurfControlPointIdListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignWorkSurfControlPointIdListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignWorkSurfControlPointIdListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignWorkSurfControlPointListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignWorkSurfControlPointListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignWorkSurfControlPointIdListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignWorkSurfControlPointIdListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}



//$clsname 类型的CRUD操作

function AddDesignWorkSurfTechnology($fname) {
	$ret = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->AddDesignWorkSurfTechnology($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = -1;
	}
	return $ret;
}

function DeleteDesignWorkSurfTechnology($id) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->DeleteDesignWorkSurfTechnology(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function UpdateDesignWorkSurfTechnology($fname) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->UpdateDesignWorkSurfTechnology($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function GetDesignWorkSurfTechnologyById($id) {
	$_return = new DesignWorkSurfTechnology();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignWorkSurfTechnologyById(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignWorkSurfTechnologyByForeignKey($fkey, $id) {
	$_return = new DesignWorkSurfTechnology();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignWorkSurfTechnologyByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignWorkSurfTechnologyIdByForeignKey($fkey, $id) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignWorkSurfTechnologyIdByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetDesignWorkSurfTechnologyList() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignWorkSurfTechnologyList();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignWorkSurfTechnologyIds() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignWorkSurfTechnologyIds();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignWorkSurfTechnologyNames() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignWorkSurfTechnologyNames();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function AddMoreDesignWorkSurfTechnology($objs) {
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->AddMoreDesignWorkSurfTechnology($objs);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function DeleteMoreDesignWorkSurfTechnology($obj_ids) {
	if(empty($obj_ids)) return;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->DeleteMoreDesignWorkSurfTechnology($obj_ids);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function GetDesignWorkSurfTechnologyByFields($fields) {
	$_return = new DesignWorkSurfTechnology();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignWorkSurfTechnologyByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignWorkSurfTechnologyByField1($field, $value) {
	$_return = new DesignWorkSurfTechnology();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignWorkSurfTechnologyByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignWorkSurfTechnologyByField2($field1, $value1, $field2, $value2) {
	$_return = new DesignWorkSurfTechnology();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignWorkSurfTechnologyByField2($field1, strval($value1), $field2, str($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDesignWorkSurfTechnologyListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignWorkSurfTechnologyListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignWorkSurfTechnologyListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignWorkSurfTechnologyListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignWorkSurfTechnologyListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignWorkSurfTechnologyListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignWorkSurfTechnologyIdByFields($fields) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignWorkSurfTechnologyIdByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetDesignWorkSurfTechnologyIdByField1($field, $value) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignWorkSurfTechnologyIdByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetDesignWorkSurfTechnologyIdByField2($field1, $value1, $field2, $value2) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignWorkSurfTechnologyIdByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetDesignWorkSurfTechnologyIdListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignWorkSurfTechnologyIdListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignWorkSurfTechnologyIdListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignWorkSurfTechnologyIdListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignWorkSurfTechnologyIdListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignWorkSurfTechnologyIdListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignWorkSurfTechnologyListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignWorkSurfTechnologyListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDesignWorkSurfTechnologyIdListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDesignWorkSurfTechnologyIdListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}



//$clsname 类型的CRUD操作

function AddDrillingRadiusParam($fname) {
	$ret = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->AddDrillingRadiusParam($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = -1;
	}
	return $ret;
}

function DeleteDrillingRadiusParam($id) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->DeleteDrillingRadiusParam(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function UpdateDrillingRadiusParam($fname) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->UpdateDrillingRadiusParam($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function GetDrillingRadiusParamById($id) {
	$_return = new DrillingRadiusParam();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDrillingRadiusParamById(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDrillingRadiusParamByForeignKey($fkey, $id) {
	$_return = new DrillingRadiusParam();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDrillingRadiusParamByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDrillingRadiusParamIdByForeignKey($fkey, $id) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDrillingRadiusParamIdByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetDrillingRadiusParamList() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDrillingRadiusParamList();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDrillingRadiusParamIds() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDrillingRadiusParamIds();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDrillingRadiusParamNames() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDrillingRadiusParamNames();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function AddMoreDrillingRadiusParam($objs) {
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->AddMoreDrillingRadiusParam($objs);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function DeleteMoreDrillingRadiusParam($obj_ids) {
	if(empty($obj_ids)) return;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->DeleteMoreDrillingRadiusParam($obj_ids);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function GetDrillingRadiusParamByFields($fields) {
	$_return = new DrillingRadiusParam();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDrillingRadiusParamByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDrillingRadiusParamByField1($field, $value) {
	$_return = new DrillingRadiusParam();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDrillingRadiusParamByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDrillingRadiusParamByField2($field1, $value1, $field2, $value2) {
	$_return = new DrillingRadiusParam();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDrillingRadiusParamByField2($field1, strval($value1), $field2, str($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDrillingRadiusParamListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDrillingRadiusParamListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDrillingRadiusParamListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDrillingRadiusParamListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDrillingRadiusParamListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDrillingRadiusParamListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDrillingRadiusParamIdByFields($fields) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDrillingRadiusParamIdByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetDrillingRadiusParamIdByField1($field, $value) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDrillingRadiusParamIdByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetDrillingRadiusParamIdByField2($field1, $value1, $field2, $value2) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDrillingRadiusParamIdByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetDrillingRadiusParamIdListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDrillingRadiusParamIdListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDrillingRadiusParamIdListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDrillingRadiusParamIdListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDrillingRadiusParamIdListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDrillingRadiusParamIdListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDrillingRadiusParamListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDrillingRadiusParamListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDrillingRadiusParamIdListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDrillingRadiusParamIdListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}



//$clsname 类型的CRUD操作

function AddDrillingSurf($fname) {
	$ret = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->AddDrillingSurf($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = -1;
	}
	return $ret;
}

function DeleteDrillingSurf($id) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->DeleteDrillingSurf(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function UpdateDrillingSurf($fname) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->UpdateDrillingSurf($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function GetDrillingSurfById($id) {
	$_return = new DrillingSurf();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDrillingSurfById(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDrillingSurfByForeignKey($fkey, $id) {
	$_return = new DrillingSurf();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDrillingSurfByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDrillingSurfIdByForeignKey($fkey, $id) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDrillingSurfIdByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetDrillingSurfList() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDrillingSurfList();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDrillingSurfIds() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDrillingSurfIds();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDrillingSurfNames() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDrillingSurfNames();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function AddMoreDrillingSurf($objs) {
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->AddMoreDrillingSurf($objs);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function DeleteMoreDrillingSurf($obj_ids) {
	if(empty($obj_ids)) return;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->DeleteMoreDrillingSurf($obj_ids);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function GetDrillingSurfByFields($fields) {
	$_return = new DrillingSurf();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDrillingSurfByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDrillingSurfByField1($field, $value) {
	$_return = new DrillingSurf();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDrillingSurfByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDrillingSurfByField2($field1, $value1, $field2, $value2) {
	$_return = new DrillingSurf();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDrillingSurfByField2($field1, strval($value1), $field2, str($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetDrillingSurfListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDrillingSurfListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDrillingSurfListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDrillingSurfListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDrillingSurfListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDrillingSurfListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDrillingSurfIdByFields($fields) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDrillingSurfIdByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetDrillingSurfIdByField1($field, $value) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDrillingSurfIdByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetDrillingSurfIdByField2($field1, $value1, $field2, $value2) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDrillingSurfIdByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetDrillingSurfIdListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDrillingSurfIdListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDrillingSurfIdListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDrillingSurfIdListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDrillingSurfIdListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDrillingSurfIdListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDrillingSurfListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDrillingSurfListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetDrillingSurfIdListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetDrillingSurfIdListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}



//$clsname 类型的CRUD操作

function AddHighDrillingPore($fname) {
	$ret = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->AddHighDrillingPore($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = -1;
	}
	return $ret;
}

function DeleteHighDrillingPore($id) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->DeleteHighDrillingPore(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function UpdateHighDrillingPore($fname) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->UpdateHighDrillingPore($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function GetHighDrillingPoreById($id) {
	$_return = new HighDrillingPore();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingPoreById(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetHighDrillingPoreByForeignKey($fkey, $id) {
	$_return = new HighDrillingPore();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingPoreByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetHighDrillingPoreIdByForeignKey($fkey, $id) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingPoreIdByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetHighDrillingPoreList() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingPoreList();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetHighDrillingPoreIds() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingPoreIds();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetHighDrillingPoreNames() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingPoreNames();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function AddMoreHighDrillingPore($objs) {
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->AddMoreHighDrillingPore($objs);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function DeleteMoreHighDrillingPore($obj_ids) {
	if(empty($obj_ids)) return;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->DeleteMoreHighDrillingPore($obj_ids);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function GetHighDrillingPoreByFields($fields) {
	$_return = new HighDrillingPore();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingPoreByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetHighDrillingPoreByField1($field, $value) {
	$_return = new HighDrillingPore();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingPoreByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetHighDrillingPoreByField2($field1, $value1, $field2, $value2) {
	$_return = new HighDrillingPore();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingPoreByField2($field1, strval($value1), $field2, str($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetHighDrillingPoreListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingPoreListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetHighDrillingPoreListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingPoreListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetHighDrillingPoreListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingPoreListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetHighDrillingPoreIdByFields($fields) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingPoreIdByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetHighDrillingPoreIdByField1($field, $value) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingPoreIdByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetHighDrillingPoreIdByField2($field1, $value1, $field2, $value2) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingPoreIdByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetHighDrillingPoreIdListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingPoreIdListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetHighDrillingPoreIdListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingPoreIdListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetHighDrillingPoreIdListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingPoreIdListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetHighDrillingPoreListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingPoreListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetHighDrillingPoreIdListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingPoreIdListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}



//$clsname 类型的CRUD操作

function AddHighDrillingPoreParam($fname) {
	$ret = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->AddHighDrillingPoreParam($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = -1;
	}
	return $ret;
}

function DeleteHighDrillingPoreParam($id) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->DeleteHighDrillingPoreParam(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function UpdateHighDrillingPoreParam($fname) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->UpdateHighDrillingPoreParam($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function GetHighDrillingPoreParamById($id) {
	$_return = new HighDrillingPoreParam();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingPoreParamById(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetHighDrillingPoreParamByForeignKey($fkey, $id) {
	$_return = new HighDrillingPoreParam();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingPoreParamByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetHighDrillingPoreParamIdByForeignKey($fkey, $id) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingPoreParamIdByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetHighDrillingPoreParamList() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingPoreParamList();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetHighDrillingPoreParamIds() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingPoreParamIds();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetHighDrillingPoreParamNames() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingPoreParamNames();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function AddMoreHighDrillingPoreParam($objs) {
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->AddMoreHighDrillingPoreParam($objs);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function DeleteMoreHighDrillingPoreParam($obj_ids) {
	if(empty($obj_ids)) return;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->DeleteMoreHighDrillingPoreParam($obj_ids);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function GetHighDrillingPoreParamByFields($fields) {
	$_return = new HighDrillingPoreParam();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingPoreParamByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetHighDrillingPoreParamByField1($field, $value) {
	$_return = new HighDrillingPoreParam();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingPoreParamByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetHighDrillingPoreParamByField2($field1, $value1, $field2, $value2) {
	$_return = new HighDrillingPoreParam();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingPoreParamByField2($field1, strval($value1), $field2, str($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetHighDrillingPoreParamListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingPoreParamListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetHighDrillingPoreParamListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingPoreParamListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetHighDrillingPoreParamListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingPoreParamListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetHighDrillingPoreParamIdByFields($fields) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingPoreParamIdByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetHighDrillingPoreParamIdByField1($field, $value) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingPoreParamIdByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetHighDrillingPoreParamIdByField2($field1, $value1, $field2, $value2) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingPoreParamIdByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetHighDrillingPoreParamIdListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingPoreParamIdListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetHighDrillingPoreParamIdListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingPoreParamIdListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetHighDrillingPoreParamIdListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingPoreParamIdListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetHighDrillingPoreParamListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingPoreParamListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetHighDrillingPoreParamIdListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingPoreParamIdListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}



//$clsname 类型的CRUD操作

function AddHighDrillingSiteParam($fname) {
	$ret = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->AddHighDrillingSiteParam($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = -1;
	}
	return $ret;
}

function DeleteHighDrillingSiteParam($id) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->DeleteHighDrillingSiteParam(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function UpdateHighDrillingSiteParam($fname) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->UpdateHighDrillingSiteParam($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function GetHighDrillingSiteParamById($id) {
	$_return = new HighDrillingSiteParam();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingSiteParamById(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetHighDrillingSiteParamByForeignKey($fkey, $id) {
	$_return = new HighDrillingSiteParam();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingSiteParamByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetHighDrillingSiteParamIdByForeignKey($fkey, $id) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingSiteParamIdByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetHighDrillingSiteParamList() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingSiteParamList();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetHighDrillingSiteParamIds() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingSiteParamIds();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetHighDrillingSiteParamNames() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingSiteParamNames();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function AddMoreHighDrillingSiteParam($objs) {
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->AddMoreHighDrillingSiteParam($objs);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function DeleteMoreHighDrillingSiteParam($obj_ids) {
	if(empty($obj_ids)) return;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->DeleteMoreHighDrillingSiteParam($obj_ids);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function GetHighDrillingSiteParamByFields($fields) {
	$_return = new HighDrillingSiteParam();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingSiteParamByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetHighDrillingSiteParamByField1($field, $value) {
	$_return = new HighDrillingSiteParam();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingSiteParamByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetHighDrillingSiteParamByField2($field1, $value1, $field2, $value2) {
	$_return = new HighDrillingSiteParam();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingSiteParamByField2($field1, strval($value1), $field2, str($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetHighDrillingSiteParamListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingSiteParamListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetHighDrillingSiteParamListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingSiteParamListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetHighDrillingSiteParamListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingSiteParamListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetHighDrillingSiteParamIdByFields($fields) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingSiteParamIdByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetHighDrillingSiteParamIdByField1($field, $value) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingSiteParamIdByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetHighDrillingSiteParamIdByField2($field1, $value1, $field2, $value2) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingSiteParamIdByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetHighDrillingSiteParamIdListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingSiteParamIdListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetHighDrillingSiteParamIdListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingSiteParamIdListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetHighDrillingSiteParamIdListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingSiteParamIdListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetHighDrillingSiteParamListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingSiteParamListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetHighDrillingSiteParamIdListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingSiteParamIdListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}



//$clsname 类型的CRUD操作

function AddHighDrillingTunnel($fname) {
	$ret = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->AddHighDrillingTunnel($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = -1;
	}
	return $ret;
}

function DeleteHighDrillingTunnel($id) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->DeleteHighDrillingTunnel(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function UpdateHighDrillingTunnel($fname) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->UpdateHighDrillingTunnel($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function GetHighDrillingTunnelById($id) {
	$_return = new HighDrillingTunnel();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingTunnelById(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetHighDrillingTunnelByForeignKey($fkey, $id) {
	$_return = new HighDrillingTunnel();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingTunnelByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetHighDrillingTunnelIdByForeignKey($fkey, $id) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingTunnelIdByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetHighDrillingTunnelList() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingTunnelList();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetHighDrillingTunnelIds() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingTunnelIds();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetHighDrillingTunnelNames() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingTunnelNames();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function AddMoreHighDrillingTunnel($objs) {
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->AddMoreHighDrillingTunnel($objs);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function DeleteMoreHighDrillingTunnel($obj_ids) {
	if(empty($obj_ids)) return;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->DeleteMoreHighDrillingTunnel($obj_ids);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function GetHighDrillingTunnelByFields($fields) {
	$_return = new HighDrillingTunnel();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingTunnelByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetHighDrillingTunnelByField1($field, $value) {
	$_return = new HighDrillingTunnel();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingTunnelByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetHighDrillingTunnelByField2($field1, $value1, $field2, $value2) {
	$_return = new HighDrillingTunnel();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingTunnelByField2($field1, strval($value1), $field2, str($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetHighDrillingTunnelListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingTunnelListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetHighDrillingTunnelListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingTunnelListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetHighDrillingTunnelListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingTunnelListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetHighDrillingTunnelIdByFields($fields) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingTunnelIdByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetHighDrillingTunnelIdByField1($field, $value) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingTunnelIdByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetHighDrillingTunnelIdByField2($field1, $value1, $field2, $value2) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingTunnelIdByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetHighDrillingTunnelIdListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingTunnelIdListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetHighDrillingTunnelIdListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingTunnelIdListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetHighDrillingTunnelIdListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingTunnelIdListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetHighDrillingTunnelListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingTunnelListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetHighDrillingTunnelIdListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHighDrillingTunnelIdListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}



//$clsname 类型的CRUD操作

function AddHydrGeo($fname) {
	$ret = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->AddHydrGeo($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = -1;
	}
	return $ret;
}

function DeleteHydrGeo($id) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->DeleteHydrGeo(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function UpdateHydrGeo($fname) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->UpdateHydrGeo($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function GetHydrGeoById($id) {
	$_return = new HydrGeo();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHydrGeoById(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetHydrGeoByForeignKey($fkey, $id) {
	$_return = new HydrGeo();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHydrGeoByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetHydrGeoIdByForeignKey($fkey, $id) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHydrGeoIdByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetHydrGeoList() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHydrGeoList();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetHydrGeoIds() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHydrGeoIds();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetHydrGeoNames() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHydrGeoNames();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function AddMoreHydrGeo($objs) {
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->AddMoreHydrGeo($objs);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function DeleteMoreHydrGeo($obj_ids) {
	if(empty($obj_ids)) return;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->DeleteMoreHydrGeo($obj_ids);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function GetHydrGeoByFields($fields) {
	$_return = new HydrGeo();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHydrGeoByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetHydrGeoByField1($field, $value) {
	$_return = new HydrGeo();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHydrGeoByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetHydrGeoByField2($field1, $value1, $field2, $value2) {
	$_return = new HydrGeo();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHydrGeoByField2($field1, strval($value1), $field2, str($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetHydrGeoListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHydrGeoListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetHydrGeoListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHydrGeoListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetHydrGeoListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHydrGeoListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetHydrGeoIdByFields($fields) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHydrGeoIdByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetHydrGeoIdByField1($field, $value) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHydrGeoIdByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetHydrGeoIdByField2($field1, $value1, $field2, $value2) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHydrGeoIdByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetHydrGeoIdListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHydrGeoIdListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetHydrGeoIdListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHydrGeoIdListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetHydrGeoIdListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHydrGeoIdListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetHydrGeoListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHydrGeoListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetHydrGeoIdListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetHydrGeoIdListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}



//$clsname 类型的CRUD操作

function AddMine($fname) {
	$ret = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->AddMine($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = -1;
	}
	return $ret;
}

function DeleteMine($id) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->DeleteMine(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function UpdateMine($fname) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->UpdateMine($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function GetMineById($id) {
	$_return = new Mine();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineById(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetMineByForeignKey($fkey, $id) {
	$_return = new Mine();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetMineIdByForeignKey($fkey, $id) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineIdByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetMineList() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineList();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetMineIds() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineIds();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetMineNames() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineNames();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function AddMoreMine($objs) {
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->AddMoreMine($objs);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function DeleteMoreMine($obj_ids) {
	if(empty($obj_ids)) return;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->DeleteMoreMine($obj_ids);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function GetMineByFields($fields) {
	$_return = new Mine();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetMineByField1($field, $value) {
	$_return = new Mine();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetMineByField2($field1, $value1, $field2, $value2) {
	$_return = new Mine();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineByField2($field1, strval($value1), $field2, str($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetMineListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetMineListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetMineListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetMineIdByFields($fields) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineIdByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetMineIdByField1($field, $value) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineIdByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetMineIdByField2($field1, $value1, $field2, $value2) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineIdByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetMineIdListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineIdListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetMineIdListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineIdListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetMineIdListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineIdListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetMineListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetMineIdListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineIdListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}



//$clsname 类型的CRUD操作

function AddMineBase($fname) {
	$ret = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->AddMineBase($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = -1;
	}
	return $ret;
}

function DeleteMineBase($id) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->DeleteMineBase(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function UpdateMineBase($fname) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->UpdateMineBase($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function GetMineBaseById($id) {
	$_return = new MineBase();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineBaseById(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetMineBaseByForeignKey($fkey, $id) {
	$_return = new MineBase();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineBaseByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetMineBaseIdByForeignKey($fkey, $id) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineBaseIdByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetMineBaseList() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineBaseList();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetMineBaseIds() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineBaseIds();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetMineBaseNames() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineBaseNames();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function AddMoreMineBase($objs) {
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->AddMoreMineBase($objs);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function DeleteMoreMineBase($obj_ids) {
	if(empty($obj_ids)) return;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->DeleteMoreMineBase($obj_ids);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function GetMineBaseByFields($fields) {
	$_return = new MineBase();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineBaseByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetMineBaseByField1($field, $value) {
	$_return = new MineBase();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineBaseByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetMineBaseByField2($field1, $value1, $field2, $value2) {
	$_return = new MineBase();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineBaseByField2($field1, strval($value1), $field2, str($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetMineBaseListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineBaseListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetMineBaseListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineBaseListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetMineBaseListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineBaseListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetMineBaseIdByFields($fields) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineBaseIdByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetMineBaseIdByField1($field, $value) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineBaseIdByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetMineBaseIdByField2($field1, $value1, $field2, $value2) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineBaseIdByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetMineBaseIdListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineBaseIdListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetMineBaseIdListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineBaseIdListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetMineBaseIdListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineBaseIdListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetMineBaseListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineBaseListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetMineBaseIdListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineBaseIdListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}



//$clsname 类型的CRUD操作

function AddMineRegion($fname) {
	$ret = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->AddMineRegion($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = -1;
	}
	return $ret;
}

function DeleteMineRegion($id) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->DeleteMineRegion(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function UpdateMineRegion($fname) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->UpdateMineRegion($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function GetMineRegionById($id) {
	$_return = new MineRegion();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineRegionById(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetMineRegionByForeignKey($fkey, $id) {
	$_return = new MineRegion();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineRegionByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetMineRegionIdByForeignKey($fkey, $id) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineRegionIdByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetMineRegionList() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineRegionList();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetMineRegionIds() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineRegionIds();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetMineRegionNames() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineRegionNames();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function AddMoreMineRegion($objs) {
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->AddMoreMineRegion($objs);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function DeleteMoreMineRegion($obj_ids) {
	if(empty($obj_ids)) return;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->DeleteMoreMineRegion($obj_ids);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function GetMineRegionByFields($fields) {
	$_return = new MineRegion();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineRegionByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetMineRegionByField1($field, $value) {
	$_return = new MineRegion();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineRegionByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetMineRegionByField2($field1, $value1, $field2, $value2) {
	$_return = new MineRegion();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineRegionByField2($field1, strval($value1), $field2, str($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetMineRegionListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineRegionListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetMineRegionListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineRegionListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetMineRegionListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineRegionListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetMineRegionIdByFields($fields) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineRegionIdByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetMineRegionIdByField1($field, $value) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineRegionIdByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetMineRegionIdByField2($field1, $value1, $field2, $value2) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineRegionIdByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetMineRegionIdListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineRegionIdListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetMineRegionIdListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineRegionIdListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetMineRegionIdListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineRegionIdListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetMineRegionListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineRegionListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetMineRegionIdListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetMineRegionIdListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}



//$clsname 类型的CRUD操作

function AddPoreFlow($fname) {
	$ret = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->AddPoreFlow($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = -1;
	}
	return $ret;
}

function DeletePoreFlow($id) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->DeletePoreFlow(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function UpdatePoreFlow($fname) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->UpdatePoreFlow($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function GetPoreFlowById($id) {
	$_return = new PoreFlow();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetPoreFlowById(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetPoreFlowByForeignKey($fkey, $id) {
	$_return = new PoreFlow();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetPoreFlowByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetPoreFlowIdByForeignKey($fkey, $id) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetPoreFlowIdByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetPoreFlowList() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetPoreFlowList();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetPoreFlowIds() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetPoreFlowIds();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetPoreFlowNames() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetPoreFlowNames();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function AddMorePoreFlow($objs) {
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->AddMorePoreFlow($objs);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function DeleteMorePoreFlow($obj_ids) {
	if(empty($obj_ids)) return;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->DeleteMorePoreFlow($obj_ids);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function GetPoreFlowByFields($fields) {
	$_return = new PoreFlow();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetPoreFlowByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetPoreFlowByField1($field, $value) {
	$_return = new PoreFlow();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetPoreFlowByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetPoreFlowByField2($field1, $value1, $field2, $value2) {
	$_return = new PoreFlow();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetPoreFlowByField2($field1, strval($value1), $field2, str($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetPoreFlowListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetPoreFlowListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetPoreFlowListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetPoreFlowListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetPoreFlowListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetPoreFlowListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetPoreFlowIdByFields($fields) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetPoreFlowIdByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetPoreFlowIdByField1($field, $value) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetPoreFlowIdByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetPoreFlowIdByField2($field1, $value1, $field2, $value2) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetPoreFlowIdByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetPoreFlowIdListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetPoreFlowIdListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetPoreFlowIdListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetPoreFlowIdListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetPoreFlowIdListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetPoreFlowIdListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetPoreFlowListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetPoreFlowListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetPoreFlowIdListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetPoreFlowIdListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}



//$clsname 类型的CRUD操作

function AddPoreSize($fname) {
	$ret = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->AddPoreSize($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = -1;
	}
	return $ret;
}

function DeletePoreSize($id) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->DeletePoreSize(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function UpdatePoreSize($fname) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->UpdatePoreSize($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function GetPoreSizeById($id) {
	$_return = new PoreSize();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetPoreSizeById(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetPoreSizeByForeignKey($fkey, $id) {
	$_return = new PoreSize();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetPoreSizeByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetPoreSizeIdByForeignKey($fkey, $id) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetPoreSizeIdByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetPoreSizeList() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetPoreSizeList();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetPoreSizeIds() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetPoreSizeIds();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetPoreSizeNames() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetPoreSizeNames();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function AddMorePoreSize($objs) {
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->AddMorePoreSize($objs);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function DeleteMorePoreSize($obj_ids) {
	if(empty($obj_ids)) return;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->DeleteMorePoreSize($obj_ids);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function GetPoreSizeByFields($fields) {
	$_return = new PoreSize();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetPoreSizeByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetPoreSizeByField1($field, $value) {
	$_return = new PoreSize();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetPoreSizeByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetPoreSizeByField2($field1, $value1, $field2, $value2) {
	$_return = new PoreSize();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetPoreSizeByField2($field1, strval($value1), $field2, str($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetPoreSizeListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetPoreSizeListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetPoreSizeListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetPoreSizeListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetPoreSizeListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetPoreSizeListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetPoreSizeIdByFields($fields) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetPoreSizeIdByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetPoreSizeIdByField1($field, $value) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetPoreSizeIdByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetPoreSizeIdByField2($field1, $value1, $field2, $value2) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetPoreSizeIdByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetPoreSizeIdListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetPoreSizeIdListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetPoreSizeIdListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetPoreSizeIdListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetPoreSizeIdListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetPoreSizeIdListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetPoreSizeListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetPoreSizeListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetPoreSizeIdListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetPoreSizeIdListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}



//$clsname 类型的CRUD操作

function AddResAbundance($fname) {
	$ret = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->AddResAbundance($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = -1;
	}
	return $ret;
}

function DeleteResAbundance($id) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->DeleteResAbundance(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function UpdateResAbundance($fname) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->UpdateResAbundance($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function GetResAbundanceById($id) {
	$_return = new ResAbundance();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetResAbundanceById(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetResAbundanceByForeignKey($fkey, $id) {
	$_return = new ResAbundance();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetResAbundanceByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetResAbundanceIdByForeignKey($fkey, $id) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetResAbundanceIdByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetResAbundanceList() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetResAbundanceList();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetResAbundanceIds() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetResAbundanceIds();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetResAbundanceNames() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetResAbundanceNames();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function AddMoreResAbundance($objs) {
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->AddMoreResAbundance($objs);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function DeleteMoreResAbundance($obj_ids) {
	if(empty($obj_ids)) return;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->DeleteMoreResAbundance($obj_ids);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function GetResAbundanceByFields($fields) {
	$_return = new ResAbundance();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetResAbundanceByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetResAbundanceByField1($field, $value) {
	$_return = new ResAbundance();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetResAbundanceByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetResAbundanceByField2($field1, $value1, $field2, $value2) {
	$_return = new ResAbundance();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetResAbundanceByField2($field1, strval($value1), $field2, str($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetResAbundanceListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetResAbundanceListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetResAbundanceListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetResAbundanceListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetResAbundanceListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetResAbundanceListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetResAbundanceIdByFields($fields) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetResAbundanceIdByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetResAbundanceIdByField1($field, $value) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetResAbundanceIdByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetResAbundanceIdByField2($field1, $value1, $field2, $value2) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetResAbundanceIdByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetResAbundanceIdListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetResAbundanceIdListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetResAbundanceIdListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetResAbundanceIdListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetResAbundanceIdListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetResAbundanceIdListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetResAbundanceListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetResAbundanceListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetResAbundanceIdListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetResAbundanceIdListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}



//$clsname 类型的CRUD操作

function AddRock($fname) {
	$ret = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->AddRock($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = -1;
	}
	return $ret;
}

function DeleteRock($id) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->DeleteRock(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function UpdateRock($fname) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->UpdateRock($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function GetRockById($id) {
	$_return = new Rock();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetRockById(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetRockByForeignKey($fkey, $id) {
	$_return = new Rock();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetRockByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetRockIdByForeignKey($fkey, $id) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetRockIdByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetRockList() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetRockList();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetRockIds() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetRockIds();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetRockNames() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetRockNames();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function AddMoreRock($objs) {
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->AddMoreRock($objs);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function DeleteMoreRock($obj_ids) {
	if(empty($obj_ids)) return;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->DeleteMoreRock($obj_ids);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function GetRockByFields($fields) {
	$_return = new Rock();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetRockByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetRockByField1($field, $value) {
	$_return = new Rock();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetRockByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetRockByField2($field1, $value1, $field2, $value2) {
	$_return = new Rock();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetRockByField2($field1, strval($value1), $field2, str($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetRockListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetRockListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetRockListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetRockListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetRockListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetRockListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetRockIdByFields($fields) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetRockIdByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetRockIdByField1($field, $value) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetRockIdByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetRockIdByField2($field1, $value1, $field2, $value2) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetRockIdByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetRockIdListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetRockIdListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetRockIdListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetRockIdListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetRockIdListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetRockIdListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetRockListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetRockListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetRockIdListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetRockIdListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}



//$clsname 类型的CRUD操作

function AddSysInfo($fname) {
	$ret = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->AddSysInfo($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = -1;
	}
	return $ret;
}

function DeleteSysInfo($id) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->DeleteSysInfo(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function UpdateSysInfo($fname) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->UpdateSysInfo($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function GetSysInfoById($id) {
	$_return = new SysInfo();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetSysInfoById(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetSysInfoByForeignKey($fkey, $id) {
	$_return = new SysInfo();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetSysInfoByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetSysInfoIdByForeignKey($fkey, $id) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetSysInfoIdByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetSysInfoList() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetSysInfoList();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetSysInfoIds() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetSysInfoIds();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetSysInfoNames() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetSysInfoNames();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function AddMoreSysInfo($objs) {
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->AddMoreSysInfo($objs);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function DeleteMoreSysInfo($obj_ids) {
	if(empty($obj_ids)) return;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->DeleteMoreSysInfo($obj_ids);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function GetSysInfoByFields($fields) {
	$_return = new SysInfo();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetSysInfoByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetSysInfoByField1($field, $value) {
	$_return = new SysInfo();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetSysInfoByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetSysInfoByField2($field1, $value1, $field2, $value2) {
	$_return = new SysInfo();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetSysInfoByField2($field1, strval($value1), $field2, str($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetSysInfoListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetSysInfoListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetSysInfoListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetSysInfoListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetSysInfoListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetSysInfoListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetSysInfoIdByFields($fields) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetSysInfoIdByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetSysInfoIdByField1($field, $value) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetSysInfoIdByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetSysInfoIdByField2($field1, $value1, $field2, $value2) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetSysInfoIdByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetSysInfoIdListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetSysInfoIdListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetSysInfoIdListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetSysInfoIdListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetSysInfoIdListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetSysInfoIdListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetSysInfoListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetSysInfoListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetSysInfoIdListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetSysInfoIdListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}



//$clsname 类型的CRUD操作

function AddTechMode($fname) {
	$ret = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->AddTechMode($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = -1;
	}
	return $ret;
}

function DeleteTechMode($id) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->DeleteTechMode(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function UpdateTechMode($fname) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->UpdateTechMode($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function GetTechModeById($id) {
	$_return = new TechMode();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTechModeById(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetTechModeByForeignKey($fkey, $id) {
	$_return = new TechMode();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTechModeByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetTechModeIdByForeignKey($fkey, $id) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTechModeIdByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetTechModeList() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTechModeList();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetTechModeIds() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTechModeIds();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetTechModeNames() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTechModeNames();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function AddMoreTechMode($objs) {
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->AddMoreTechMode($objs);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function DeleteMoreTechMode($obj_ids) {
	if(empty($obj_ids)) return;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->DeleteMoreTechMode($obj_ids);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function GetTechModeByFields($fields) {
	$_return = new TechMode();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTechModeByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetTechModeByField1($field, $value) {
	$_return = new TechMode();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTechModeByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetTechModeByField2($field1, $value1, $field2, $value2) {
	$_return = new TechMode();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTechModeByField2($field1, strval($value1), $field2, str($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetTechModeListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTechModeListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetTechModeListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTechModeListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetTechModeListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTechModeListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetTechModeIdByFields($fields) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTechModeIdByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetTechModeIdByField1($field, $value) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTechModeIdByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetTechModeIdByField2($field1, $value1, $field2, $value2) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTechModeIdByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetTechModeIdListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTechModeIdListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetTechModeIdListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTechModeIdListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetTechModeIdListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTechModeIdListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetTechModeListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTechModeListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetTechModeIdListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTechModeIdListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}



//$clsname 类型的CRUD操作

function AddTechnology($fname) {
	$ret = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->AddTechnology($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = -1;
	}
	return $ret;
}

function DeleteTechnology($id) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->DeleteTechnology(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function UpdateTechnology($fname) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->UpdateTechnology($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function GetTechnologyById($id) {
	$_return = new Technology();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTechnologyById(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetTechnologyByForeignKey($fkey, $id) {
	$_return = new Technology();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTechnologyByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetTechnologyIdByForeignKey($fkey, $id) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTechnologyIdByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetTechnologyList() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTechnologyList();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetTechnologyIds() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTechnologyIds();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetTechnologyNames() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTechnologyNames();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function AddMoreTechnology($objs) {
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->AddMoreTechnology($objs);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function DeleteMoreTechnology($obj_ids) {
	if(empty($obj_ids)) return;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->DeleteMoreTechnology($obj_ids);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function GetTechnologyByFields($fields) {
	$_return = new Technology();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTechnologyByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetTechnologyByField1($field, $value) {
	$_return = new Technology();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTechnologyByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetTechnologyByField2($field1, $value1, $field2, $value2) {
	$_return = new Technology();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTechnologyByField2($field1, strval($value1), $field2, str($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetTechnologyListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTechnologyListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetTechnologyListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTechnologyListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetTechnologyListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTechnologyListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetTechnologyIdByFields($fields) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTechnologyIdByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetTechnologyIdByField1($field, $value) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTechnologyIdByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetTechnologyIdByField2($field1, $value1, $field2, $value2) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTechnologyIdByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetTechnologyIdListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTechnologyIdListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetTechnologyIdListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTechnologyIdListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetTechnologyIdListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTechnologyIdListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetTechnologyListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTechnologyListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetTechnologyIdListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTechnologyIdListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}



//$clsname 类型的CRUD操作

function AddTopoGeo($fname) {
	$ret = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->AddTopoGeo($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = -1;
	}
	return $ret;
}

function DeleteTopoGeo($id) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->DeleteTopoGeo(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function UpdateTopoGeo($fname) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->UpdateTopoGeo($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function GetTopoGeoById($id) {
	$_return = new TopoGeo();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTopoGeoById(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetTopoGeoByForeignKey($fkey, $id) {
	$_return = new TopoGeo();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTopoGeoByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetTopoGeoIdByForeignKey($fkey, $id) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTopoGeoIdByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetTopoGeoList() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTopoGeoList();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetTopoGeoIds() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTopoGeoIds();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetTopoGeoNames() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTopoGeoNames();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function AddMoreTopoGeo($objs) {
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->AddMoreTopoGeo($objs);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function DeleteMoreTopoGeo($obj_ids) {
	if(empty($obj_ids)) return;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->DeleteMoreTopoGeo($obj_ids);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function GetTopoGeoByFields($fields) {
	$_return = new TopoGeo();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTopoGeoByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetTopoGeoByField1($field, $value) {
	$_return = new TopoGeo();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTopoGeoByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetTopoGeoByField2($field1, $value1, $field2, $value2) {
	$_return = new TopoGeo();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTopoGeoByField2($field1, strval($value1), $field2, str($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetTopoGeoListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTopoGeoListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetTopoGeoListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTopoGeoListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetTopoGeoListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTopoGeoListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetTopoGeoIdByFields($fields) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTopoGeoIdByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetTopoGeoIdByField1($field, $value) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTopoGeoIdByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetTopoGeoIdByField2($field1, $value1, $field2, $value2) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTopoGeoIdByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetTopoGeoIdListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTopoGeoIdListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetTopoGeoIdListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTopoGeoIdListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetTopoGeoIdListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTopoGeoIdListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetTopoGeoListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTopoGeoListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetTopoGeoIdListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTopoGeoIdListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}



//$clsname 类型的CRUD操作

function AddTunnel($fname) {
	$ret = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->AddTunnel($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = -1;
	}
	return $ret;
}

function DeleteTunnel($id) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->DeleteTunnel(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function UpdateTunnel($fname) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->UpdateTunnel($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function GetTunnelById($id) {
	$_return = new Tunnel();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTunnelById(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetTunnelByForeignKey($fkey, $id) {
	$_return = new Tunnel();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTunnelByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetTunnelIdByForeignKey($fkey, $id) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTunnelIdByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetTunnelList() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTunnelList();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetTunnelIds() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTunnelIds();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetTunnelNames() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTunnelNames();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function AddMoreTunnel($objs) {
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->AddMoreTunnel($objs);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function DeleteMoreTunnel($obj_ids) {
	if(empty($obj_ids)) return;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->DeleteMoreTunnel($obj_ids);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function GetTunnelByFields($fields) {
	$_return = new Tunnel();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTunnelByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetTunnelByField1($field, $value) {
	$_return = new Tunnel();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTunnelByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetTunnelByField2($field1, $value1, $field2, $value2) {
	$_return = new Tunnel();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTunnelByField2($field1, strval($value1), $field2, str($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetTunnelListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTunnelListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetTunnelListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTunnelListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetTunnelListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTunnelListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetTunnelIdByFields($fields) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTunnelIdByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetTunnelIdByField1($field, $value) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTunnelIdByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetTunnelIdByField2($field1, $value1, $field2, $value2) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTunnelIdByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetTunnelIdListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTunnelIdListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetTunnelIdListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTunnelIdListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetTunnelIdListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTunnelIdListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetTunnelListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTunnelListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetTunnelIdListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetTunnelIdListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}



//$clsname 类型的CRUD操作

function AddWorkArea($fname) {
	$ret = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->AddWorkArea($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = -1;
	}
	return $ret;
}

function DeleteWorkArea($id) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->DeleteWorkArea(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function UpdateWorkArea($fname) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->UpdateWorkArea($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function GetWorkAreaById($id) {
	$_return = new WorkArea();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetWorkAreaById(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetWorkAreaByForeignKey($fkey, $id) {
	$_return = new WorkArea();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetWorkAreaByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetWorkAreaIdByForeignKey($fkey, $id) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetWorkAreaIdByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetWorkAreaList() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetWorkAreaList();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetWorkAreaIds() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetWorkAreaIds();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetWorkAreaNames() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetWorkAreaNames();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function AddMoreWorkArea($objs) {
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->AddMoreWorkArea($objs);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function DeleteMoreWorkArea($obj_ids) {
	if(empty($obj_ids)) return;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->DeleteMoreWorkArea($obj_ids);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function GetWorkAreaByFields($fields) {
	$_return = new WorkArea();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetWorkAreaByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetWorkAreaByField1($field, $value) {
	$_return = new WorkArea();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetWorkAreaByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetWorkAreaByField2($field1, $value1, $field2, $value2) {
	$_return = new WorkArea();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetWorkAreaByField2($field1, strval($value1), $field2, str($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetWorkAreaListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetWorkAreaListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetWorkAreaListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetWorkAreaListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetWorkAreaListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetWorkAreaListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetWorkAreaIdByFields($fields) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetWorkAreaIdByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetWorkAreaIdByField1($field, $value) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetWorkAreaIdByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetWorkAreaIdByField2($field1, $value1, $field2, $value2) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetWorkAreaIdByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetWorkAreaIdListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetWorkAreaIdListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetWorkAreaIdListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetWorkAreaIdListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetWorkAreaIdListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetWorkAreaIdListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetWorkAreaListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetWorkAreaListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetWorkAreaIdListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetWorkAreaIdListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}



//$clsname 类型的CRUD操作

function AddWorkSurf($fname) {
	$ret = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->AddWorkSurf($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = -1;
	}
	return $ret;
}

function DeleteWorkSurf($id) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->DeleteWorkSurf(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function UpdateWorkSurf($fname) {
	$ret = false;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->UpdateWorkSurf($fname);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = false;
	}
	return $ret;
}

function GetWorkSurfById($id) {
	$_return = new WorkSurf();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetWorkSurfById(intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetWorkSurfByForeignKey($fkey, $id) {
	$_return = new WorkSurf();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetWorkSurfByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetWorkSurfIdByForeignKey($fkey, $id) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetWorkSurfIdByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetWorkSurfList() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetWorkSurfList();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetWorkSurfIds() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetWorkSurfIds();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetWorkSurfNames() {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetWorkSurfNames();
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function AddMoreWorkSurf($objs) {
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->AddMoreWorkSurf($objs);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function DeleteMoreWorkSurf($obj_ids) {
	if(empty($obj_ids)) return;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->DeleteMoreWorkSurf($obj_ids);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function GetWorkSurfByFields($fields) {
	$_return = new WorkSurf();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetWorkSurfByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetWorkSurfByField1($field, $value) {
	$_return = new WorkSurf();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetWorkSurfByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetWorkSurfByField2($field1, $value1, $field2, $value2) {
	$_return = new WorkSurf();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetWorkSurfByField2($field1, strval($value1), $field2, str($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return->id = -1;
	}
	return $_return;
}

function GetWorkSurfListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetWorkSurfListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetWorkSurfListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetWorkSurfListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetWorkSurfListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetWorkSurfListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetWorkSurfIdByFields($fields) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetWorkSurfIdByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetWorkSurfIdByField1($field, $value) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetWorkSurfIdByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetWorkSurfIdByField2($field1, $value1, $field2, $value2) {
	$_return = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetWorkSurfIdByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = -1;
	}
	return $_return;
}

function GetWorkSurfIdListByFields($fields) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetWorkSurfIdListByFields($fields);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetWorkSurfIdListByField1($field, $value) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetWorkSurfIdListByField1($field, strval($value));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetWorkSurfIdListByField2($field1, $value1, $field2, $value2) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetWorkSurfIdListByField2($field1, strval($value1), $field2, strval($value2));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetWorkSurfListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetWorkSurfListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}

function GetWorkSurfIdListByForeignKey($fkey, $id) {
	$_return = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$_return = $client->GetWorkSurfIdListByForeignKey($fkey, intval($id));
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$_return = array();
	}
	return $_return;
}



