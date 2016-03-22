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
	//��ʼ��ʾ������(����Ŀ󾮺�ú��)
	static void InitSampleRegion();
	//��ѯ�ѵ�¼�û���id
	static int32_t GetOnlineAccountId();
	//��ȡ�ѵ�¼�û��Ŀ�����
	static void GetOnlineMine(cbm::Mine& _return);
	//��֤�û���������
	static int32_t VerifyMineAccount(const std::string& username, const std::string& pwd);
	//��ѯ�������еĿ���
	static void GetMineRegionsOfBase(std::vector<std::string> & _return, const std::string& baseName);
	//���ݿ����������
	static void GetBaseByRegion(std::string& _return, const std::string& regionName);
	//��ѯʾ�������������
	static void GetSampleMineOfRegion(cbm::Mine& _return, const std::string& regionName);
	//��ѯʾ������������ú��
	static void GetSampleCoalOfRegion(cbm::Coal& _return, const std::string& regionName);
	//��ѯ�����е�ú������
	static void GetCoalNamesOfMine(std::vector<std::string> & _return, const int32_t mine_id);
	//��ѯ�����е�ú��id
	static void GetCoalIdsOfMine(std::vector<int32_t> & _return, const int32_t mine_id);
	//��ѯ�����еĲ���
	static void GetWorkAreasOfMine(std::vector<cbm::WorkArea> & _return, const int32_t mine_id);
	//��ѯ�����еĹ�����
	static void GetWorkSurfsOfMine(std::vector<cbm::WorkSurf> & _return, const int32_t mine_id);
	//��ѯ�����еľ����
	static void GetDrillingSurfsOfMine(std::vector<cbm::DrillingSurf> & _return, const int32_t mine_id);
	//��ѯ�����еĲ���id
	static void GetWorkAreaIdsOfMine(std::vector<int32_t> & _return, const int32_t mine_id);
	//��ѯ�����еĹ�����id
	static void GetWorkSurfIdsOfMine(std::vector<int32_t> & _return, const int32_t mine_id);
	//��ѯ�����еľ����id
	static void GetDrillingSurfIdsOfMine(std::vector<int32_t> & _return, const int32_t mine_id);
	//������׳̶�����
	static int32_t DifficultEval(const cbm::Coal& coal);
	static void DifficultEvalString(std::string& _return, const cbm::Coal& coal);
	//�ɲ�ú����˹ӿ��������W1
	static double MineGasReservesW1(const int32_t mine_id);
	//���ɲ�ú����˹ӿ��������W2
	static double MineGasReservesW2(const int32_t mine_id);
	//�����������˹ӿ����
	static double WorkAreaGasFlow(const cbm::WorkArea& work_area, const double K1);
	//����󾮵���˹ӿ����
	static double MineGasFlow(const cbm::Mine& mine);
	//�����濪�ɲ���˹ӿ����
	static double WorkSurfGasFlow1(const cbm::Coal& coal, const cbm::WorkArea& work_area, const cbm::WorkSurf& work_surf);
	//�������ڽ�����˹ӿ����
	static double WorkSurfGasFlow2(const cbm::Coal& coal, const cbm::WorkArea& work_area, const cbm::WorkSurf& work_surf);
	//�������˹ӿ����
	static void DrillingSurfGasFlow(cbm::DrillingSurfGasFlowResult& _return, const cbm::Coal& coal, const cbm::DrillingSurf& drilling_surf, const cbm::Tunnel& tunnel);
	//��ѯ��Ʒ����µ��������
	static void GetAllPores(std::vector<cbm::DesignPore> & _return, const int32_t design_id);

	//�������cad,��2��������ʾ�Ƿ񼤻�cad���ڵ���ǰ��
	static bool SendCommandToCAD(const std::string& cmd, bool switch_to_cad=false);
	//��cad����ȡ����
	static std::string GetJsonDatasFromCAD(const std::string& input_datas="{}", int wait_seconds=2);
	//cad������rpc��������,rpc�Ὣ���ݽ��л���
	static void PostJsonDatasFromCAD(const std::string& secret_key, const std::string& input_datas, const std::string& out_datas);
};
