#include "StdAfx.h"
#include "GraphHelper.h"

#include <ArxHelper/HelperClass.h>
#include "CbmClientHelper.h"
#include "SQLClientHelper.h"

#include <numeric>
#include <algorithm>
#include <iterator>
#include <sstream>

std::string GraphHelper::Int2Str(int i)
{
	std::stringstream ss;
	ss << i;
	return ss.str();
}

// ɾ����ɼ����µ������곡�����
void GraphHelper::DeleteAllSiteAndPore(int design_id)
{
	// ������ü��������������곡
	std::vector<int32_t> site_ids;
	SQLClientHelper::GetDesignSiteIdListByForeignKey(site_ids, "design_technology_id", design_id);

	// ɾ�����е��곡(���ݿ���Զ�ɾ�����������)
	SQLClientHelper::DeleteMoreDesignSite(site_ids);
}

void GraphHelper::CaclSitesOnTunnel( AcGePoint3dArray& pts, const AcGePoint3d& spt, const AcGePoint3d& ept, double gap_x, double gap_y, double w, double h, double angle, bool excludeFirst )
{
	//AcGePoint3dArray temp_pts;
	ArxDrawHelper::Divide( spt, ept, gap_x, gap_y, pts, false, excludeFirst );
	//acutPrintf(_T("\n�����곡����ʱ�����:%d"), temp_pts.length());
	//int start = excludeFirst ? 1 : 0; // �Ƿ���Ƶ�һ���곡
	//for(int i=start;i<temp_pts.length();i++)
	//{
	//	pts.append(temp_pts[i]);
	//}
}

void GraphHelper::CreateSite(cbm::DesignSite& site, int num, const AcGePoint3d& pt, int32_t tech_id)
{
	//�½��곡
	site.name = GraphHelper::Int2Str(num);
	site.x = pt.x; site.y = pt.y; site.z = pt.z;
	site.design_technology_id = tech_id; // ��������id

}

void GraphHelper::CreatePore(cbm::DesignPore& pore, const CString& num, const AcGePoint3d& spt, const AcGePoint3d& ept, int32_t site_id)
{
	pore.name = W2C((LPCTSTR)num);
	pore.x1 = spt.x; pore.y1 = spt.y; pore.z1 = spt.z;
	pore.x2 = ept.x; pore.y2 = ept.y; pore.z2 = ept.z;
	AcGeVector3d v = ept - spt;
	pore.length = v.length();  // ��׳���
	ArxDrawHelper::VectorToAngle(v, pore.angle1, pore.angle2);  // ��׽Ƕ�
	pore.design_site_id = site_id;
}