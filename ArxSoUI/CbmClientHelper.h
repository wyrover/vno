#pragma once

#include <thrift/gen-cpp/cbm_types.h>

#include <vector>
#include <string>
typedef std::vector<std::string> StringArray;
typedef std::vector<int> IntArray;
typedef std::vector<double> DoubleArray;

class CbmClientHelper
{
public:
	//初始化示范矿区(虚拟的矿井和煤层)
	static void InitSampleRegion();
	//查询已登录用户的id
	static int32_t GetOnlineAccountId();
	//获取已登录用户的矿井数据
	static void GetOnlineMine(cbm::Mine& _return);
	//验证用户名和密码
	static int32_t VerifyMineAccount(const std::string& username, const std::string& pwd);
	//查询基地所有的矿区
	static void GetMineRegionsOfBase(std::vector<std::string> & _return, const std::string& baseName);
	//根据矿区反查基地
	static void GetBaseByRegion(std::string& _return, const std::string& regionName);
	//查询示范矿区的虚拟矿井
	static void GetSampleMineOfRegion(cbm::Mine& _return, const std::string& regionName);
	//查询示范矿区的虚拟煤层
	static void GetSampleCoalOfRegion(cbm::Coal& _return, const std::string& regionName);
	//查询矿井所有的煤层名称
	static void GetCoalNamesOfMine(std::vector<std::string> & _return, const int32_t mine_id);
	//查询矿井所有的煤层id
	static void GetCoalIdsOfMine(std::vector<int32_t> & _return, const int32_t mine_id);
	//查询矿井所有的采区
	static void GetWorkAreasOfMine(std::vector<cbm::WorkArea> & _return, const int32_t mine_id);
	//查询矿井所有的工作面
	static void GetWorkSurfsOfMine(std::vector<cbm::WorkSurf> & _return, const int32_t mine_id);
	//查询矿井所有的掘进面
	static void GetDrillingSurfsOfMine(std::vector<cbm::DrillingSurf> & _return, const int32_t mine_id);
	//查询矿井所有的采区id
	static void GetWorkAreaIdsOfMine(std::vector<int32_t> & _return, const int32_t mine_id);
	//查询矿井所有的工作面id
	static void GetWorkSurfIdsOfMine(std::vector<int32_t> & _return, const int32_t mine_id);
	//查询矿井所有的掘进面id
	static void GetDrillingSurfIdsOfMine(std::vector<int32_t> & _return, const int32_t mine_id);
	//抽采难易程度评价
	static int32_t DifficultEval(const cbm::Coal& coal);
	static void DifficultEvalString(std::string& _return, const cbm::Coal& coal);
	//可采煤层瓦斯涌出量计算W1
	static double MineGasReservesW1(const int32_t mine_id);
	//不可采煤层瓦斯涌出量计算W2
	static double MineGasReservesW2(const int32_t mine_id);
	//计算采区的瓦斯涌出量
	static double WorkAreaGasFlow(const cbm::WorkArea& work_area, const double K1);
	//计算矿井的瓦斯涌出量
	static double MineGasFlow(const cbm::Mine& mine);
	//工作面开采层瓦斯涌出量
	static double WorkSurfGasFlow1(const cbm::Coal& coal, const cbm::WorkArea& work_area, const cbm::WorkSurf& work_surf);
	//工作面邻近层瓦斯涌出量
	static double WorkSurfGasFlow2(const cbm::Coal& coal, const cbm::WorkArea& work_area, const cbm::WorkSurf& work_surf);
	//掘进面瓦斯涌出量
	static void DrillingSurfGasFlow(cbm::DrillingSurfGasFlowResult& _return, const cbm::Coal& coal, const cbm::DrillingSurf& drilling_surf, const cbm::Tunnel& tunnel);
	//查询设计方案下的所有钻孔
	static void GetAllPores(std::vector<cbm::DesignPore> & _return, const int32_t design_id);

	//发送命令到cad,第2个参数表示是否激活cad窗口到最前面
	static bool SendCommandToCAD(const std::string& cmd, bool switch_to_cad=false);
	//从cad中提取数据
	static std::string GetJsonDatasFromCAD(const std::string& input_datas="{}", int wait_seconds=2);
	//cad主动向rpc发送数据,rpc会将数据进行缓存
	static void PostJsonDatasFromCAD(const std::string& secret_key, const std::string& input_datas, const std::string& out_datas);
};
