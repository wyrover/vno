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

// 删除抽采技术下的所有钻场和钻孔
void GraphHelper::DeleteAllSiteAndPore(int design_id)
{
	// 查找与该技术关联的所有钻场
	std::vector<int32_t> site_ids;
	SQLClientHelper::GetDesignSiteIdListByForeignKey(site_ids, "design_technology_id", design_id);

	// 删除所有的钻场(数据库会自动删除包含的钻孔)
	SQLClientHelper::DeleteMoreDesignSite(site_ids);
}

void GraphHelper::CaclSitesOnTunnel( AcGePoint3dArray& pts, const AcGePoint3d& spt, const AcGePoint3d& ept, double gap_x, double gap_y, double w, double h, double angle, bool excludeFirst )
{
	//AcGePoint3dArray temp_pts;
	ArxDrawHelper::Divide( spt, ept, gap_x, gap_y, pts, false, excludeFirst );
	//acutPrintf(_T("\n划分钻场的临时点个数:%d"), temp_pts.length());
	//int start = excludeFirst ? 1 : 0; // 是否绘制第一个钻场
	//for(int i=start;i<temp_pts.length();i++)
	//{
	//	pts.append(temp_pts[i]);
	//}
}

void GraphHelper::CreateSite(cbm::DesignSite& site, int num, const AcGePoint3d& pt, int32_t tech_id)
{
	//新建钻场
	site.name = GraphHelper::Int2Str(num);
	site.x = pt.x; site.y = pt.y; site.z = pt.z;
	site.design_technology_id = tech_id; // 关联技术id

}

void GraphHelper::CreatePore(cbm::DesignPore& pore, const CString& num, const AcGePoint3d& spt, const AcGePoint3d& ept, int32_t site_id)
{
	pore.name = W2C((LPCTSTR)num);
	pore.x1 = spt.x; pore.y1 = spt.y; pore.z1 = spt.z;
	pore.x2 = ept.x; pore.y2 = ept.y; pore.z2 = ept.z;
	AcGeVector3d v = ept - spt;
	pore.length = v.length();  // 钻孔长度
	ArxDrawHelper::VectorToAngle(v, pore.angle1, pore.angle2);  // 钻孔角度
	pore.design_site_id = site_id;
}