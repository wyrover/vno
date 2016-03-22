<?php

namespace CbmClientHelper;

require_once __DIR__.'/ThriftClient.php';
use \ThriftClient\ThriftClient;

function InitSampleMine($region_id, $account_id, $name) {
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->InitSampleMine($region_id, $account_id, $name);
		
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function InitSampleRegion() {
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->InitSampleRegion();
		
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}

function GetOnlineAccountId() {
	$ret = -1;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->GetOnlineAccountId();
		
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = -1;
	}
	return $ret;
}

function GetOnlineMine() {
	$ret = new \cbm\Mine();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->GetOnlineMine();
		
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret->id = -1;
	}
	return $ret;
}

function VerifyMineAccount($username, $pwd) {
	$ret = -2;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->VerifyMineAccount($username, $pwd);
		
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = -2;
	}
	return $ret;
}

function GetAllMineBases() {
	$ret = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->GetAllMineBases();
		
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = array();
	}
	return $ret;
}

function GetMineRegionsOfBase($baseName) {
	$ret = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->GetMineRegionsOfBase($baseName);
		
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = array();
	}
	return $ret;
}

function GetBaseByRegion($regionName) {
	$ret = '';
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->GetBaseByRegion($regionName);
		
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = '';
	}
	return $ret;
}

function GetSampleMineOfRegion($regionName) {
	$ret = new \cbm\Mine();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->GetSampleMineOfRegion($regionName);
		
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret->id = -1;
	}
	return $ret;
}

function GetSampleCoalOfRegion($regionName) {
	$ret = new \cbm\Coal();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->GetSampleCoalOfRegion($regionName);
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret->id = -1;
	}
	return $ret;
}

function GetCoalNamesOfMine($mine_id) {
	$ret = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->GetCoalNamesOfMine($mine_id);
		
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = array();
	}
	return $ret;
}

function GetCoalIdsOfMine($mine_id) {
	$ret = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->GetCoalIdsOfMine($mine_id);
		
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = array();
	}
	return $ret;
}

function GetWorkAreasOfMine($mine_id) {
	$ret = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->GetWorkAreasOfMine($mine_id);
		
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = array();
	}
	return $ret;
}

function GetWorkSurfsOfMine($mine_id) {
	$ret = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->GetWorkSurfsOfMine($mine_id);
		
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = array();
	}
	return $ret;
}

function GetDrillingSurfsOfMine($mine_id) {
	$ret = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->GetDrillingSurfsOfMine($mine_id);
		
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = array();
	}
	return $ret;
}

function GetWorkAreaIdsOfMine($mine_id) {
	$ret = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->GetWorkAreaIdsOfMine($mine_id);
		
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = array();
	}
	return $ret;
}

function GetWorkSurfIdsOfMine($mine_id) {
	$ret = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->GetWorkSurfIdsOfMine($mine_id);
		
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = array();
	}
	return $ret;
}

function GetDrillingSurfIdsOfMine($mine_id) {
	$ret = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->GetDrillingSurfIdsOfMine($mine_id);
		
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = array();
	}
	return $ret;
}

function DifficultEval($coal) {
	$ret = 0.0;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->DifficultEval($coal);
		
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = 0.0;
	}
	return $ret;
}

function DifficultEvalString($coal) {
	$ret = '';
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->DifficultEvalString($coal);
		
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = '';
	}
	return $ret;
}

function MineGasReservesW1($mine_id) {
	$ret = 0.0;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->MineGasReservesW1($mine_id);
		
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = 0.0;
	}
	return $ret;
}

function MineGasReservesW2($mine_id) {
	$ret = 0.0;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->MineGasReservesW2($mine_id);
		
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = 0.0;
	}
	return $ret;
}

function WorkAreaGasFlow($work_area, $K1) {
	$ret = -1.0;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->WorkAreaGasFlow($work_area, $K1);
		
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = -1.0;
	}
	return $ret;
}

function MineGasFlow($mine) {
	$ret = 0.0;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->MineGasFlow($mine);
		
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = 0.0;
	}
	return $ret;
}

function WorkSurfGasFlow1($coal, $work_area, $work_surf) {
	$ret = 0.0;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->WorkSurfGasFlow1($coal, $work_area, $work_surf);
		
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = 0.0;
	}
	return $ret;
}

function WorkSurfGasFlow2($coal, $work_area, $work_surf) {
	$ret = 0.0;
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->WorkSurfGasFlow2($coal, $work_area, $work_surf);
		
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = 0.0;
	}
	return $ret;
}

function DrillingSurfGasFlow($coal, $drilling_surf, $tunnel) {
	$ret = new DrillingSurfGasFlowResult();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->DrillingSurfGasFlow($coal, $drilling_surf, $tunnel);
		
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret->q0 = 0.0;
		$ret->q3 = 0.0;
		$ret->q4 = 0.0;
		$ret->qa = 0.0;
	}
	return $ret;
}

function GetAllPores($design_id) {
	$ret = array();
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->GetAllPores($design_id);
		
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = array();
	}
	return $ret;
}

function SendCommandToCAD($cmd, $switch_to_cad=false) {
	$ret = false
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$ret = $client->SendCommandToCAD($cmd, $switch_to_cad);
		
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
	return $ret
}

function GetJsonDatasFromCAD($input_datas="{}", $wait_seconds=2) {
	$ret = "{}";
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		# 需要一些cad的数据，向rpc请求,rpc分配一个密钥
		$secret_key = $client->RequestJsonDatasFromCAD($input_datas);
		# 等待几秒钟
		sleep($wait_seconds);
		# 从rpc缓存中提取数据
		$ret = $client->GetJsonDatasFromRpcCache($secret_key);
		
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
		$ret = "{}";
	}
	return $ret;
}

function PostJsonDatasFromCAD($secret_key, $input_datas, $out_datas)
{
	try {
		$service_client = new ThriftClient('\cbm\CbmServiceClient', HOST, PORT2);
		$client = $service_client->getClient();
		$client->PostJsonDatasFromCAD($secret_key, $input_datas, $out_datas);
		
	} catch (TException $tx) {
		print 'TException: '.$tx->getMessage()."\n";
	}
}