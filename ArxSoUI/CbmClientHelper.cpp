#include "StdAfx.h"
#include "CbmClientHelper.h"
#include "RpcClient.h"

void CbmClientHelper::InitSampleRegion()
{
	try 
	{
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->InitSampleRegion();
		service_client.close();
	} 
	catch (TException &tx) 
	{
		std::string error_msg = tx.what();
		//printf("ERROR: %s\n", tx.what());
	}
}

//查询已登录用户的id
int32_t CbmClientHelper::GetOnlineAccountId()
{
	int32_t ret = -1;
	try 
	{
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetOnlineAccountId();
		service_client.close();
	} 
	catch (TException &tx) 
	{
		std::string error_msg = tx.what();
		//printf("ERROR: %s\n", tx.what());
	}
	return ret;
}

//获取已登录用户的矿井数据
void CbmClientHelper::GetOnlineMine(cbm::Mine& _return)
{
	try 
	{
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetOnlineMine(_return);
		service_client.close();
	} 
	catch (TException &tx) 
	{
		std::string error_msg = tx.what();
		//printf("ERROR: %s\n", tx.what());
	}
}

//验证用户名和密码
int32_t CbmClientHelper::VerifyMineAccount(const std::string& username, const std::string& pwd)
{
	int32_t ret = -2;
	try 
	{
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->VerifyMineAccount(username, pwd);
		service_client.close();
	} 
	catch (TException &tx) 
	{
		std::string error_msg = tx.what();
		//printf("ERROR: %s\n", tx.what());
	}
	return ret;
}

//查询基地所有的矿区
void CbmClientHelper::GetMineRegionsOfBase(std::vector<std::string> & _return, const std::string& baseName)
{
	try 
	{
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetMineRegionsOfBase(_return, baseName);
		service_client.close();
	} 
	catch (TException &tx) 
	{
		std::string error_msg = tx.what();
		//printf("ERROR: %s\n", tx.what());
	}
}

//根据矿区反查基地
void CbmClientHelper::GetBaseByRegion(std::string& _return, const std::string& regionName)
{
	try 
	{
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetBaseByRegion(_return, regionName);
		service_client.close();
	} 
	catch (TException &tx) 
	{
		std::string error_msg = tx.what();
		//printf("ERROR: %s\n", tx.what());
	}
}

//查询示范矿区的虚拟矿井
void CbmClientHelper::GetSampleMineOfRegion(cbm::Mine& _return, const std::string& regionName)
{
	try 
	{
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetSampleMineOfRegion(_return, regionName);
		service_client.close();
	} 
	catch (TException &tx) 
	{
		std::string error_msg = tx.what();
		//printf("ERROR: %s\n", tx.what());
	}
}

//查询示范矿区的虚拟煤层
void CbmClientHelper::GetSampleCoalOfRegion(cbm::Coal& _return, const std::string& regionName)
{
	try 
	{
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetSampleCoalOfRegion(_return, regionName);
		service_client.close();
	} 
	catch (TException &tx) 
	{
		std::string error_msg = tx.what();
		//printf("ERROR: %s\n", tx.what());
	}
}

//查询矿井所有的煤层名称
void CbmClientHelper::GetCoalNamesOfMine(std::vector<std::string> & _return, const int32_t mine_id)
{
	try 
	{
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetCoalNamesOfMine(_return, mine_id);
		service_client.close();
	} 
	catch (TException &tx) 
	{
		std::string error_msg = tx.what();
		//printf("ERROR: %s\n", tx.what());
	}
}

//查询矿井所有的煤层id
void CbmClientHelper::GetCoalIdsOfMine(std::vector<int32_t> & _return, const int32_t mine_id)
{
	try 
	{
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetCoalIdsOfMine(_return, mine_id);
		service_client.close();
	} 
	catch (TException &tx) 
	{
		std::string error_msg = tx.what();
		//printf("ERROR: %s\n", tx.what());
	}
}

//查询矿井所有的采区
void CbmClientHelper::GetWorkAreasOfMine(std::vector<cbm::WorkArea> & _return, const int32_t mine_id)
{
	try 
	{
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetWorkAreasOfMine(_return, mine_id);
		service_client.close();
	} 
	catch (TException &tx) 
	{
		std::string error_msg = tx.what();
		//printf("ERROR: %s\n", tx.what());
	}
}

//查询矿井所有的工作面
void CbmClientHelper::GetWorkSurfsOfMine(std::vector<cbm::WorkSurf> & _return, const int32_t mine_id)
{
	try 
	{
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetWorkSurfsOfMine(_return, mine_id);
		service_client.close();
	} 
	catch (TException &tx) 
	{
		std::string error_msg = tx.what();
		//printf("ERROR: %s\n", tx.what());
	}
}

//查询矿井所有的掘进面
void CbmClientHelper::GetDrillingSurfsOfMine(std::vector<cbm::DrillingSurf> & _return, const int32_t mine_id)
{
	try 
	{
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDrillingSurfsOfMine(_return, mine_id);
		service_client.close();
	} 
	catch (TException &tx) 
	{
		std::string error_msg = tx.what();
		//printf("ERROR: %s\n", tx.what());
	}
}

//查询矿井所有的采区id
void CbmClientHelper::GetWorkAreaIdsOfMine(std::vector<int32_t> & _return, const int32_t mine_id)
{
	try 
	{
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetWorkAreaIdsOfMine(_return, mine_id);
		service_client.close();
	} 
	catch (TException &tx) 
	{
		std::string error_msg = tx.what();
		//printf("ERROR: %s\n", tx.what());
	}
}

//查询矿井所有的工作面id
void CbmClientHelper::GetWorkSurfIdsOfMine(std::vector<int32_t> & _return, const int32_t mine_id)
{
	try 
	{
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetWorkSurfIdsOfMine(_return, mine_id);
		service_client.close();
	} 
	catch (TException &tx) 
	{
		std::string error_msg = tx.what();
		//printf("ERROR: %s\n", tx.what());
	}
}

//查询矿井所有的掘进面id
void CbmClientHelper::GetDrillingSurfIdsOfMine(std::vector<int32_t> & _return, const int32_t mine_id)
{
	try 
	{
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDrillingSurfIdsOfMine(_return, mine_id);
		service_client.close();
	} 
	catch (TException &tx) 
	{
		std::string error_msg = tx.what();
		//printf("ERROR: %s\n", tx.what());
	}
}
//抽采难易程度评价
int32_t CbmClientHelper::DifficultEval(const cbm::Coal& coal)
{
	int32_t ret = 0;
	try 
	{
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->DifficultEval(coal);
		service_client.close();
	} 
	catch (TException &tx) 
	{
		std::string error_msg = tx.what();
		//printf("ERROR: %s\n", tx.what());
		ret = 0;
	}
	return ret;
}
void CbmClientHelper::DifficultEvalString(std::string& _return, const cbm::Coal& coal)
{
	try 
	{
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->DifficultEvalString(_return, coal);
		service_client.close();
	} 
	catch (TException &tx) 
	{
		std::string error_msg = tx.what();
		//printf("ERROR: %s\n", tx.what());
	}
}
//可采煤层瓦斯涌出量计算W1
double CbmClientHelper::MineGasReservesW1(const int32_t mine_id)
{
	double ret = 0;
	try 
	{
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->MineGasReservesW1(mine_id);
		service_client.close();
	} 
	catch (TException &tx) 
	{
		std::string error_msg = tx.what();
		//printf("ERROR: %s\n", tx.what());
		ret = 0;
	}
	return ret;
}
//不可采煤层瓦斯涌出量计算W2
double CbmClientHelper::MineGasReservesW2(const int32_t mine_id)
{
	double ret = 0;
	try 
	{
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->MineGasReservesW2(mine_id);
		service_client.close();
	} 
	catch (TException &tx) 
	{
		std::string error_msg = tx.what();
		//printf("ERROR: %s\n", tx.what());
		ret = 0;
	}
	return ret;
}
//计算采区的瓦斯涌出量
double CbmClientHelper::WorkAreaGasFlow(const cbm::WorkArea& work_area, const double K1)
{
	double ret = 0;
	try 
	{
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->WorkAreaGasFlow(work_area, K1);
		service_client.close();
	} 
	catch (TException &tx) 
	{
		std::string error_msg = tx.what();
		//printf("ERROR: %s\n", tx.what());
		ret = 0;
	}
	return ret;
}
//计算矿井的瓦斯涌出量
double CbmClientHelper::MineGasFlow(const cbm::Mine& mine)
{
	double ret = 0;
	try 
	{
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->MineGasFlow(mine);
		service_client.close();
	} 
	catch (TException &tx) 
	{
		std::string error_msg = tx.what();
		//printf("ERROR: %s\n", tx.what());
		ret = 0;
	}
	return ret;
}
//工作面开采层瓦斯涌出量
double CbmClientHelper::WorkSurfGasFlow1(const cbm::Coal& coal, const cbm::WorkArea& work_area, const cbm::WorkSurf& work_surf)
{
	double ret = 0;
	try 
	{
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->WorkSurfGasFlow1(coal, work_area, work_surf);
		service_client.close();
	} 
	catch (TException &tx) 
	{
		std::string error_msg = tx.what();
		//printf("ERROR: %s\n", tx.what());
		ret = 0;
	}
	return ret;
}
//工作面邻近层瓦斯涌出量
double CbmClientHelper::WorkSurfGasFlow2(const cbm::Coal& coal, const cbm::WorkArea& work_area, const cbm::WorkSurf& work_surf)
{
	double ret = 0;
	try 
	{
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->WorkSurfGasFlow2(coal, work_area, work_surf);
		service_client.close();
	} 
	catch (TException &tx) 
	{
		std::string error_msg = tx.what();
		//printf("ERROR: %s\n", tx.what());
		ret = 0;
	}
	return ret;
}
//掘进面瓦斯涌出量
void CbmClientHelper::DrillingSurfGasFlow(cbm::DrillingSurfGasFlowResult& _return, const cbm::Coal& coal, const cbm::DrillingSurf& drilling_surf, const cbm::Tunnel& tunnel)
{
	try 
	{
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->DrillingSurfGasFlow(_return, coal, drilling_surf, tunnel);
		service_client.close();
	} 
	catch (TException &tx) 
	{
		std::string error_msg = tx.what();
		//printf("ERROR: %s\n", tx.what());
	}
}

void CbmClientHelper::GetAllPores(std::vector<cbm::DesignPore> & _return, const int32_t design_id)
{
	try 
	{
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetAllPores(_return, design_id);
		service_client.close();
	} 
	catch (TException &tx) 
	{
		std::string error_msg = tx.what();
		//printf("ERROR: %s\n", tx.what());
	}
}

bool CbmClientHelper::SendCommandToCAD(const std::string& cmd, bool switch_to_cad)
{
	bool ret = false;
	try
	{
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->SendCommandToCAD(cmd, switch_to_cad);
		service_client.close();
	} 
	catch (TException &tx) 
	{
		std::string error_msg = tx.what();
		//printf("ERROR: %s\n", tx.what());
	}
	return ret;
}

std::string CbmClientHelper::GetJsonDatasFromCAD(const std::string& input_datas, int wait_seconds)
{
	if(wait_seconds <= 0) wait_seconds = 3;
	if(wait_seconds > 10) wait_seconds = 10;

	std::string ret = "{}";
	try
	{
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		//需要一些cad的数据，向rpc请求,rpc分配一个密钥
		std::string secret_key = "#";
		service_client.get()->RequestJsonDatasFromCAD(secret_key, input_datas);
		//等待几秒钟
		::Sleep(wait_seconds*1000);
		//从rpc缓存中提取数据
		service_client.get()->GetJsonDatasFromRpcCache(ret, secret_key);
		service_client.close();
	}
	catch (TException &tx)
	{
		std::string error_msg = tx.what();
		//printf("ERROR: %s\n", tx.what());
		ret = "{}";
	}
	return ret;
}

void CbmClientHelper::PostJsonDatasFromCAD(const std::string& secret_key, const std::string& input_datas, const std::string& out_datas)
{
	try
	{
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->PostJsonDatasFromCAD(secret_key, input_datas, out_datas);
		service_client.close();
	} 
	catch (TException &tx) 
	{
		std::string error_msg = tx.what();
		//printf("ERROR: %s\n", tx.what());
	}
}
