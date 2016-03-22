#include "StdAfx.h"
#include "CmdHelper.h"

#include "SQLClientHelper.h"
#include "CbmClientHelper.h"

#include "OccurrenceGraph.h"
#include "EvalUnitGraph.h"
#include "Graph11.h"
#include "Graph12.h"
#include "Graph21.h"
#include "Graph23.h"
#include "Graph32.h"

#include <fstream>
//#include <WinHttpClient.h>
#include <ArxHelper/HelperClass.h>

void CmdHelper::InitAllData()
{
	//��ʼ����������(�����ʵ䡢��չ����appname��)
	SystemHelper::Start();
	//��ȡ�ֶ�
	CString appDir = ArxUtilHelper::GetAppPathDir( _hdllInstance );
	//FieldHelper::InitDataField( ArxUtilHelper::BuildPath( appDir, _T( "Datas\\ú�������-�ֶ�-ͼԪ����.txt" ) ) );
	//��������
	acdbHostApplicationServices()->workingDatabase()->loadLineTypeFile( _T( "JIS_02_0.7" ), _T( "acadiso.lin" ) );
}

void CmdHelper::PostJsonDatasToRpc()
{
	TCHAR strFileName[MAX_PATH];
	if(acedGetString(0, _T("��ָ�������ļ�����:"), strFileName) != RTNORM) return;

	std::ifstream infile(W2C(strFileName));
	if(!infile) return;

	//��Щ���������Ҫ���ݸ�cadһЩ����
	std::string input_datas = "{}";
	infile >> input_datas;

	//���������ɵ���Կ
	std::string secret_key = "#";
	infile >> secret_key;
	infile.close();

	acutPrintf(_T("\n1:%s\n2:%s"), C2W(input_datas), C2W(secret_key));
	if(secret_key == "#") return;

	// �ռ�����(����input_datas�����ݽ����ж�:input_datas��һ��json����)

	//����rpc���������л���
	std::string out_datas = "{'name':'dlj'}";
	CbmClientHelper::PostJsonDatasFromCAD(secret_key, input_datas, out_datas);
}

void CmdHelper::xxx()
{
	std::string json_data = CbmClientHelper::GetJsonDatasFromCAD("{}");
	//int ret = CbmClientHelper::VerifyMineAccount("dlj", "123");
	//acutPrintf(_T("\n��֤���:%d"), ret);	
	CbmClientHelper::SendCommandToCAD("regen");
}

void CmdHelper::TestWinHttpClient()
{
	//// Set URL.
	//WinHttpClient client(_T("http://localhost/tt/test.php"));

	//// Send http request, a GET request by default.
	//client.SendHttpRequest();
	//string data = "title=����1&content=�������";
	//client.SetAdditionalDataToSend((BYTE *)data.c_str(), data.size());

	//// The response header.
	//CString httpResponseHeader = client.GetResponseHeader().c_str();
	//// The response content.
	//CString httpResponseContent = client.GetResponseContent().c_str();
}

void CmdHelper::DrawOccurrenceGraph()
{
	int mine_id = -1;
	if(RTNORM != acedGetInt(NULL, &mine_id)) return;
	if(mine_id == -1) return;

	cbm::Mine mine;
	SQLClientHelper::GetMineById(mine, mine_id);
	if( mine.id < 0 ) return;

	// ú�����򳤶ȱ�������,������ʾЧ�� 
	double factor = 1.0;
	if(RTNORM != acedGetReal(NULL, &factor)) return;

	//����ѡ���������
	AcGePoint3d pt;
	ArxUtilHelper::PromptPt( _T( "��ѡ��һ��:" ), pt );

	//����ú�㸳��ͼ
	OccurrenceGraph graph( mine, factor );
	graph.setPoint( pt );
	graph.draw();
}

void CmdHelper::DrawEvalUnitGraph()
{
	//int coal_id = -1;
	//if(RTNORM != acedGetInt(NULL, &coal_id)) return;
	//if(coal_id == -1) return;

	int eval_unit_partition_id = -1;
	if(RTNORM != acedGetInt(NULL, &eval_unit_partition_id)) return;
	if(eval_unit_partition_id == -1) return;

	//cbm::Coal coal;
	//SQLClientHelper::GetCoalById(coal, coal_id);
	//if( coal.id < 0 ) return;

	cbm::DesignEvalUnitPartition deup;
	SQLClientHelper::GetDesignEvalUnitPartitionById(deup, eval_unit_partition_id);
	if(deup.id < 0 ) return;

	acutPrintf(_T("\n������:%.3f"), deup.w);

	//����ѡ���������
	AcGePoint3d pt;
	ArxUtilHelper::PromptPt( _T( "��ѡ��һ��:" ), pt );

	//����ú�㸳��ͼ
	EvalUnitGraph graph( deup );
	graph.setPoint( pt );
	graph.draw();
}

void CmdHelper::GeneratePore11()
{
	int coal_id = -1;
	if(RTNORM != acedGetInt(NULL, &coal_id)) return;
	if(coal_id == -1) return;

	int tech_id = -1;
	if(RTNORM != acedGetInt(NULL, &tech_id)) return;
	if(tech_id == -1) return;

	cbm::Coal coal;
	SQLClientHelper::GetCoalById(coal, coal_id);
	if( coal.id < 0 ) return;

	cbm::DesignDrillingSurfTechnology tws_tech;
	SQLClientHelper::GetDesignDrillingSurfTechnologyById(tws_tech, tech_id);
	if(tws_tech.id < 0 ) return;

	// ����������������ļ�(������)
	P11::PoreHelper ph(coal, tws_tech);
	ph.cacl();

	AfxMessageBox(_T("\n����������ݳɹ�!"));
}

void CmdHelper::GeneratePore12()
{
	int coal_id = -1;
	if(RTNORM != acedGetInt(NULL, &coal_id)) return;
	if(coal_id == -1) return;

	int tech_id = -1;
	if(RTNORM != acedGetInt(NULL, &tech_id)) return;
	if(tech_id == -1) return;

	cbm::Coal coal;
	SQLClientHelper::GetCoalById(coal, coal_id);
	if( coal.id < 0 ) return;

	cbm::DesignDrillingSurfTechnology tws_tech;
	SQLClientHelper::GetDesignDrillingSurfTechnologyById(tws_tech, tech_id);
	if(tws_tech.id < 0 ) return;

	// ����������������ļ�(������)
	P12::PoreHelper ph(coal, tws_tech);
	ph.cacl();

	AfxMessageBox(_T("\n����������ݳɹ�!"));
}

void CmdHelper::GeneratePore21()
{
	int coal_id = -1;
	if(RTNORM != acedGetInt(NULL, &coal_id)) return;
	if(coal_id == -1) return;

	int tech_id = -1;
	if(RTNORM != acedGetInt(NULL, &tech_id)) return;
	if(tech_id == -1) return;

	cbm::Coal coal;
	SQLClientHelper::GetCoalById(coal, coal_id);
	if( coal.id < 0 ) return;

	cbm::DesignWorkSurfTechnology ws_tech;
	SQLClientHelper::GetDesignWorkSurfTechnologyById(ws_tech, tech_id);
	if(ws_tech.id < 0 ) return;

	// ����������������ļ�(������)
	P21::PoreHelper ph(coal, ws_tech);
	ph.cacl();

	AfxMessageBox(_T("\n����������ݳɹ�!"));
}

void CmdHelper::GeneratePore23()
{
	int coal_id = -1;
	if(RTNORM != acedGetInt(NULL, &coal_id)) return;
	if(coal_id == -1) return;

	int tech_id = -1;
	if(RTNORM != acedGetInt(NULL, &tech_id)) return;
	if(tech_id == -1) return;

	cbm::Coal coal;
	SQLClientHelper::GetCoalById(coal, coal_id);
	if( coal.id < 0 ) return;

	cbm::DesignWorkSurfTechnology ws_tech;
	SQLClientHelper::GetDesignWorkSurfTechnologyById(ws_tech, tech_id);
	if(ws_tech.id < 0 ) return;

	// ����������������ļ�(������)
	P23::PoreHelper ph(coal, ws_tech);
	ph.cacl();

	AfxMessageBox(_T("\n����������ݳɹ�!"));
}

void CmdHelper::GeneratePore32()
{
	int coal_id = -1;
	if(RTNORM != acedGetInt(NULL, &coal_id)) return;
	if(coal_id == -1) return;

	int tech_id = -1;
	if(RTNORM != acedGetInt(NULL, &tech_id)) return;
	if(tech_id == -1) return;

	cbm::Coal coal;
	SQLClientHelper::GetCoalById(coal, coal_id);
	if( coal.id < 0 ) return;

	cbm::DesignGoafTechnology goaf_tech;
	SQLClientHelper::GetDesignGoafTechnologyById(goaf_tech, tech_id);
	if(goaf_tech.id < 0 ) return;

	std::vector<cbm::DesignGoafPore> close_pores;
	SQLClientHelper::GetDesignGoafPoreListByForeignKey(close_pores, "design_goaf_technology_id", goaf_tech.id);
	if(close_pores.empty()) return;

	// ����������������ļ�(������)
	P32::PoreHelper ph(coal, goaf_tech, close_pores);
	ph.cacl();

	AfxMessageBox(_T("\n����������ݳɹ�!"));
}

void CmdHelper::DrawPlaneGraph11()
{
	int coal_id = -1;
	if(RTNORM != acedGetInt(NULL, &coal_id)) return;
	if(coal_id == -1) return;

	int tech_id = -1;
	if(RTNORM != acedGetInt(NULL, &tech_id)) return;
	if(tech_id == -1) return;

	cbm::Coal coal;
	SQLClientHelper::GetCoalById(coal, coal_id);
	if( coal.id < 0 ) return;

	cbm::DesignDrillingSurfTechnology tws_tech;
	SQLClientHelper::GetDesignDrillingSurfTechnologyById(tws_tech, tech_id);
	if(tws_tech.id < 0 ) return;

	//����ѡ���������
	AcGePoint3d pt;
	ArxUtilHelper::PromptPt( _T( "��ѡ��һ��:" ), pt );

	//����ƽ��ͼ
	P11::PlanGraph graph( coal, tws_tech );
	graph.setPoint( pt );
	graph.draw();
}

void CmdHelper::DrawHeadGraph11()
{
	int coal_id = -1;
	if(RTNORM != acedGetInt(NULL, &coal_id)) return;
	if(coal_id == -1) return;

	int tech_id = -1;
	if(RTNORM != acedGetInt(NULL, &tech_id)) return;
	if(tech_id == -1) return;

	cbm::Coal coal;
	SQLClientHelper::GetCoalById(coal, coal_id);
	if( coal.id < 0 ) return;

	cbm::DesignDrillingSurfTechnology tws_tech;
	SQLClientHelper::GetDesignDrillingSurfTechnologyById(tws_tech, tech_id);
	if(tws_tech.id < 0 ) return;

	//����ѡ���������
	AcGePoint3d pt;
	ArxUtilHelper::PromptPt( _T( "��ѡ��һ��:" ), pt );

	//������������ͼ
	P11::HeadGraph graph( coal, tws_tech );
	graph.setPoint( pt );
	graph.draw();
}

void CmdHelper::DrawDipGraph11()
{
	int coal_id = -1;
	if(RTNORM != acedGetInt(NULL, &coal_id)) return;
	if(coal_id == -1) return;

	int tech_id = -1;
	if(RTNORM != acedGetInt(NULL, &tech_id)) return;
	if(tech_id == -1) return;

	cbm::Coal coal;
	SQLClientHelper::GetCoalById(coal, coal_id);
	if( coal.id < 0 ) return;

	cbm::DesignDrillingSurfTechnology tws_tech;
	SQLClientHelper::GetDesignDrillingSurfTechnologyById(tws_tech, tech_id);
	if(tws_tech.id < 0 ) return;

	//����ѡ���������
	AcGePoint3d pt;
	ArxUtilHelper::PromptPt( _T( "��ѡ��һ��:" ), pt );

	//������������ͼ
	P11::DipGraph graph( coal, tws_tech );
	graph.setPoint( pt );
	graph.draw();
}


void CmdHelper::DrawPlaneGraph12()
{
	int coal_id = -1;
	if(RTNORM != acedGetInt(NULL, &coal_id)) return;
	if(coal_id == -1) return;

	int tech_id = -1;
	if(RTNORM != acedGetInt(NULL, &tech_id)) return;
	if(tech_id == -1) return;

	cbm::Coal coal;
	SQLClientHelper::GetCoalById(coal, coal_id);
	if( coal.id < 0 ) return;

	cbm::DesignDrillingSurfTechnology tws_tech;
	SQLClientHelper::GetDesignDrillingSurfTechnologyById(tws_tech, tech_id);
	if(tws_tech.id < 0 ) return;

	//����ѡ���������
	AcGePoint3d pt;
	ArxUtilHelper::PromptPt( _T( "��ѡ��һ��:" ), pt );

	//����ƽ��ͼ
	P12::PlanGraph graph( coal, tws_tech );
	graph.setPoint( pt );
	graph.draw();
}

void CmdHelper::DrawHeadGraph12()
{
	int coal_id = -1;
	if(RTNORM != acedGetInt(NULL, &coal_id)) return;
	if(coal_id == -1) return;

	int tech_id = -1;
	if(RTNORM != acedGetInt(NULL, &tech_id)) return;
	if(tech_id == -1) return;

	cbm::Coal coal;
	SQLClientHelper::GetCoalById(coal, coal_id);
	if( coal.id < 0 ) return;

	cbm::DesignDrillingSurfTechnology tws_tech;
	SQLClientHelper::GetDesignDrillingSurfTechnologyById(tws_tech, tech_id);
	if(tws_tech.id < 0 ) return;

	//����ѡ���������
	AcGePoint3d pt;
	ArxUtilHelper::PromptPt( _T( "��ѡ��һ��:" ), pt );

	//������������ͼ
	//P12::HeadGraph graph( coal, tws_tech );
	//graph.setPoint( pt );
	//graph.draw();
}

void CmdHelper::DrawDipGraph12()
{
	int coal_id = -1;
	if(RTNORM != acedGetInt(NULL, &coal_id)) return;
	if(coal_id == -1) return;

	int tech_id = -1;
	if(RTNORM != acedGetInt(NULL, &tech_id)) return;
	if(tech_id == -1) return;

	cbm::Coal coal;
	SQLClientHelper::GetCoalById(coal, coal_id);
	if( coal.id < 0 ) return;

	cbm::DesignDrillingSurfTechnology tws_tech;
	SQLClientHelper::GetDesignDrillingSurfTechnologyById(tws_tech, tech_id);
	if(tws_tech.id < 0 ) return;

	//����ѡ���������
	AcGePoint3d pt;
	ArxUtilHelper::PromptPt( _T( "��ѡ��һ��:" ), pt );

	//������������
	//P12::DipGraph graph( coal, tws_tech );
	//graph.setPoint( pt );
	//graph.draw();
}

void CmdHelper::DrawPlaneGraph21()
{
	int coal_id = -1;
	if(RTNORM != acedGetInt(NULL, &coal_id)) return;
	if(coal_id == -1) return;

	int tech_id = -1;
	if(RTNORM != acedGetInt(NULL, &tech_id)) return;
	if(tech_id == -1) return;

	cbm::Coal coal;
	SQLClientHelper::GetCoalById(coal, coal_id);
	if( coal.id < 0 ) return;

	cbm::DesignWorkSurfTechnology ws_tech;
	SQLClientHelper::GetDesignWorkSurfTechnologyById(ws_tech, tech_id);
	if(ws_tech.id < 0 ) return;

	//����ѡ���������
	AcGePoint3d pt;
	ArxUtilHelper::PromptPt( _T( "��ѡ��һ��:" ), pt );

	//����ƽ��ͼ
	P21::PlanGraph graph( coal, ws_tech );
	graph.setPoint( pt );
	graph.draw();
}

void CmdHelper::DrawHeadGraph21()
{
	int coal_id = -1;
	if(RTNORM != acedGetInt(NULL, &coal_id)) return;
	if(coal_id == -1) return;

	int tech_id = -1;
	if(RTNORM != acedGetInt(NULL, &tech_id)) return;
	if(tech_id == -1) return;

	cbm::Coal coal;
	SQLClientHelper::GetCoalById(coal, coal_id);
	if( coal.id < 0 ) return;

	cbm::DesignWorkSurfTechnology ws_tech;
	SQLClientHelper::GetDesignWorkSurfTechnologyById(ws_tech, tech_id);
	if(ws_tech.id < 0 ) return;

	//����ѡ���������
	AcGePoint3d pt;
	ArxUtilHelper::PromptPt( _T( "��ѡ��һ��:" ), pt );

	//������������ͼ
	P21::HeadGraph graph( coal, ws_tech );
	graph.setPoint( pt );
	graph.draw();
}

void CmdHelper::DrawDipGraph21()
{
	int coal_id = -1;
	if(RTNORM != acedGetInt(NULL, &coal_id)) return;
	if(coal_id == -1) return;

	int tech_id = -1;
	if(RTNORM != acedGetInt(NULL, &tech_id)) return;
	if(tech_id == -1) return;

	cbm::Coal coal;
	SQLClientHelper::GetCoalById(coal, coal_id);
	if( coal.id < 0 ) return;

	cbm::DesignWorkSurfTechnology ws_tech;
	SQLClientHelper::GetDesignWorkSurfTechnologyById(ws_tech, tech_id);
	if(ws_tech.id < 0 ) return;

	//����ѡ���������
	AcGePoint3d pt;
	ArxUtilHelper::PromptPt( _T( "��ѡ��һ��:" ), pt );

	//������������ͼ
	P21::DipGraph graph( coal, ws_tech );
	graph.setPoint( pt );
	graph.draw();
}

void CmdHelper::DrawPlaneGraph23()
{
	int coal_id = -1;
	if(RTNORM != acedGetInt(NULL, &coal_id)) return;
	if(coal_id == -1) return;

	int tech_id = -1;
	if(RTNORM != acedGetInt(NULL, &tech_id)) return;
	if(tech_id == -1) return;

	cbm::Coal coal;
	SQLClientHelper::GetCoalById(coal, coal_id);
	if( coal.id < 0 ) return;

	cbm::DesignWorkSurfTechnology ws_tech;
	SQLClientHelper::GetDesignWorkSurfTechnologyById(ws_tech, tech_id);
	if(ws_tech.id < 0 ) return;

	//����ѡ���������
	AcGePoint3d pt;
	ArxUtilHelper::PromptPt( _T( "��ѡ��һ��:" ), pt );

	//����ƽ��ͼ
	P23::PlanGraph graph( coal, ws_tech );
	graph.setPoint( pt );
	graph.draw();
}

void CmdHelper::DrawHeadGraph23()
{
	int coal_id = -1;
	if(RTNORM != acedGetInt(NULL, &coal_id)) return;
	if(coal_id == -1) return;

	int tech_id = -1;
	if(RTNORM != acedGetInt(NULL, &tech_id)) return;
	if(tech_id == -1) return;

	cbm::Coal coal;
	SQLClientHelper::GetCoalById(coal, coal_id);
	if( coal.id < 0 ) return;

	cbm::DesignWorkSurfTechnology ws_tech;
	SQLClientHelper::GetDesignWorkSurfTechnologyById(ws_tech, tech_id);
	if(ws_tech.id < 0 ) return;

	//����ѡ���������
	AcGePoint3d pt;
	ArxUtilHelper::PromptPt( _T( "��ѡ��һ��:" ), pt );

	//������������ͼ
	//P23::HeadGraph graph( coal, ws_tech );
	//graph.setPoint( pt );
	//graph.draw();
}

void CmdHelper::DrawDipGraph23()
{
	int coal_id = -1;
	if(RTNORM != acedGetInt(NULL, &coal_id)) return;
	if(coal_id == -1) return;

	int tech_id = -1;
	if(RTNORM != acedGetInt(NULL, &tech_id)) return;
	if(tech_id == -1) return;

	cbm::Coal coal;
	SQLClientHelper::GetCoalById(coal, coal_id);
	if( coal.id < 0 ) return;

	cbm::DesignWorkSurfTechnology ws_tech;
	SQLClientHelper::GetDesignWorkSurfTechnologyById(ws_tech, tech_id);
	if(ws_tech.id < 0 ) return;

	//����ѡ���������
	AcGePoint3d pt;
	ArxUtilHelper::PromptPt( _T( "��ѡ��һ��:" ), pt );

	//������������ͼ
	//P23::DipGraph graph( coal, ws_tech );
	//graph.setPoint( pt );
	//graph.draw();
}

void CmdHelper::DrawPlaneGraph32()
{
	int coal_id = -1;
	if(RTNORM != acedGetInt(NULL, &coal_id)) return;
	if(coal_id == -1) return;

	int tech_id = -1;
	if(RTNORM != acedGetInt(NULL, &tech_id)) return;
	if(tech_id == -1) return;

	cbm::Coal coal;
	SQLClientHelper::GetCoalById(coal, coal_id);
	if( coal.id < 0 ) return;

	cbm::DesignGoafTechnology goaf_tech;
	SQLClientHelper::GetDesignGoafTechnologyById(goaf_tech, tech_id);
	if(goaf_tech.id < 0 ) return;

	std::vector<cbm::DesignGoafPore> close_pores;
	SQLClientHelper::GetDesignGoafPoreListByForeignKey(close_pores, "design_goaf_technology_id", goaf_tech.id);
	if(close_pores.empty()) return;

	//����ѡ���������
	AcGePoint3d pt;
	ArxUtilHelper::PromptPt( _T( "��ѡ��һ��:" ), pt );

	//����ƽ��ͼ
	P32::PlanGraph graph( coal, goaf_tech, close_pores );
	graph.setPoint( pt );
	graph.draw();
}

void CmdHelper::DrawHeadGraph32()
{
	int coal_id = -1;
	if(RTNORM != acedGetInt(NULL, &coal_id)) return;
	if(coal_id == -1) return;

	int tech_id = -1;
	if(RTNORM != acedGetInt(NULL, &tech_id)) return;
	if(tech_id == -1) return;

	cbm::Coal coal;
	SQLClientHelper::GetCoalById(coal, coal_id);
	if( coal.id < 0 ) return;

	cbm::DesignGoafTechnology goaf_tech;
	SQLClientHelper::GetDesignGoafTechnologyById(goaf_tech, tech_id);
	if(goaf_tech.id < 0 ) return;

	std::vector<cbm::DesignGoafPore> close_pores;
	SQLClientHelper::GetDesignGoafPoreListByForeignKey(close_pores, "design_goaf_technology_id", goaf_tech.id);
	if(close_pores.empty()) return;

	//����ѡ���������
	AcGePoint3d pt;
	ArxUtilHelper::PromptPt( _T( "��ѡ��һ��:" ), pt );

	//������������ͼ
	P32::HeadGraph graph( coal, goaf_tech, close_pores );
	graph.setPoint( pt );
	graph.draw();
}

void CmdHelper::DrawDipGraph32()
{
	int coal_id = -1;
	if(RTNORM != acedGetInt(NULL, &coal_id)) return;
	if(coal_id == -1) return;

	int tech_id = -1;
	if(RTNORM != acedGetInt(NULL, &tech_id)) return;
	if(tech_id == -1) return;

	cbm::Coal coal;
	SQLClientHelper::GetCoalById(coal, coal_id);
	if( coal.id < 0 ) return;

	cbm::DesignGoafTechnology goaf_tech;
	SQLClientHelper::GetDesignGoafTechnologyById(goaf_tech, tech_id);
	if(goaf_tech.id < 0 ) return;
	
	std::vector<cbm::DesignGoafPore> close_pores;
	SQLClientHelper::GetDesignGoafPoreListByForeignKey(close_pores, "design_goaf_technology_id", goaf_tech.id);
	if(close_pores.empty()) return;

	//����ѡ���������
	AcGePoint3d pt;
	ArxUtilHelper::PromptPt( _T( "��ѡ��һ��:" ), pt );

	//������������ͼ
	//P32::DipGraph graph( coal, goaf_tech, close_pores );
	//graph.setPoint( pt );
	//graph.draw();
}
