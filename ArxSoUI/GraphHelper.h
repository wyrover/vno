#pragma once

#include <thrift/gen-cpp/cbm_types.h>

class GraphHelper
{
public:
	static std::string Int2Str(int i);
	static void DeleteAllSiteAndPore(int design_id);
	static void CaclSitesOnTunnel( AcGePoint3dArray& pts, const AcGePoint3d& spt, const AcGePoint3d& ept, double gap_x, double gap_y, double w=0, double h=0, double angle=0, bool excludeFirst=true );
	static void CreateSite(cbm::DesignSite& site, int num, const AcGePoint3d& pt, int32_t tech_id);
	static void CreatePore(cbm::DesignPore& pore, const CString& num, const AcGePoint3d& spt, const AcGePoint3d& ept, int32_t site_id);
};