#include "StdAfx.h"
#include "Graph32.h"

#include <ArxHelper/HelperClass.h>
#include "CbmClientHelper.h"
#include "SQLClientHelper.h"

#include <numeric>
#include <algorithm>
#include <cmath>
#include <map>
#include <string>

#include "GraphHelper.h"

namespace P32
{

	PoreHelper::PoreHelper(cbm::Coal& _coal, cbm::DesignGoafTechnology& _tech, std::vector<cbm::DesignGoafPore>& _close_pores)
		: coal( _coal ), tech( _tech ), close_pores(_close_pores)
	{
		goaf_w = 20;

		//倾向长度和走向长度
		L1 = tech.l1, L2 = tech.l2;
		//煤层厚度和倾角(弧度)
		thick = coal.thick, angle = DegToRad( coal.dip_angle );
		//工作面巷道的宽度和高度
		w = tech.w, h = tech.h;
		//钻孔半径(孔径的单位是mm)
		radius = tech.dp * 0.5 * 0.001;
		//钻孔压茬长度
		pore_stubble = tech.pore_stubble;
		//钻场长度、宽度和高度
		Ls = tech.ls, Ws = tech.ws, Hs = tech.hs;
		//钻场间距
		site_gap = tech.gs;
	}

	void PoreHelper::cacl()
	{
		// 删除所有的钻场和钻孔
		GraphHelper::DeleteAllSiteAndPore(tech.design_technology_id);

		AcGePoint3d basePt = AcGePoint3d::kOrigin;
		AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis, v3 = AcGeVector3d::kZAxis;

		// 记录所有的钻孔
		std::vector<cbm::DesignPore> pores;

		// 钻场的最大长度
		double Ld = L1 + goaf_w - (site_gap + pore_stubble);
		if(Ld > L1) Ld = L1;

		// 计算钻场坐标
		AcGePoint3dArray pts;
		ArxDrawHelper::Divide( basePt + v1*Ld, basePt, site_gap, 0, pts, false, false, false );
		// 逆序
		pts.reverse();

		bool ret = true;
		// 记录钻场的数据库id
		IntArray site_ids;

		// 绘制钻场
		for( int i = 0; i < pts.length(); i++ )
		{
			cbm::DesignSite site;
			GraphHelper::CreateSite(site, i+1, pts[i], tech.design_technology_id);
			// 提交到数据库
			int32_t site_id = SQLClientHelper::AddDesignSite(site);
			if(site_id <= 0) 
			{
				acutPrintf(_T("\n添加钻场到数据库失败!!!"));
				ret = false;
				break;
			}
			site_ids.push_back(site_id);

			// 绘制每个钻场的钻孔
			for(int j=0;j<close_pores.size();j++)
			{
				AcGePoint3d pt = pts[i];
				double Lp = site_gap + pore_stubble, Wp = close_pores[j].h_offset, Hp = close_pores[j].v_offset;
				// 标注钻孔
				CString poreName;
				poreName.Format(_T("%d-%s"), i+1, C2W(close_pores[j].name));

				cbm::DesignPore pore;
				GraphHelper::CreatePore(pore, poreName, pt, pt + v1*Lp - v2*Wp + v3*Hp, site_id);

				// 记录钻孔
				pores.push_back(pore);
			}
		}
		if(!ret)
		{
			// 删除所有的钻场(数据库会自动删除包含的钻孔)
			SQLClientHelper::DeleteMoreDesignSite(site_ids);
		}
		else
		{
			// 添加到数据库
			SQLClientHelper::AddMoreDesignPore(pores);

			acutPrintf(_T("钻孔个数:%d"), pores.size());
		}
	}

    Graph::Graph( cbm::Coal& _coal, cbm::DesignGoafTechnology& _tech, std::vector<cbm::DesignGoafPore>& _close_pores )
        : BaseGraph(), coal( _coal ), tech( _tech ), close_pores(_close_pores)
    {
		goaf_w = 20;

        left_margin = 8;
        right_margin = 8;
        bottom_margin = 8;
        top_margin = 8;

        //倾向长度和走向长度
        L1 = tech.l1, L2 = tech.l2;
        //煤层厚度和倾角(弧度)
        thick = coal.thick, angle = DegToRad( coal.dip_angle );
        //工作面巷道的宽度和高度
        w = tech.w, h = tech.h;
        //钻孔半径(孔径的单位是mm)
        radius = tech.dp * 0.5 * 0.001;
        //钻孔压茬长度
        pore_stubble = tech.pore_stubble;
		//钻场长度、宽度和高度
		Ls = tech.ls, Ws = tech.ws, Hs = tech.hs;
		//钻场间距
		site_gap = tech.gs;
    }

    void Graph::subDraw()
    {
        //绘制图形
        drawCoal();
        drawTunnel();
        drawPores();
		drawSites();
    }

    void Graph::caclCoalExtent( double& Lc, double& Wc, double& Hc ) const
    {
        //计算宽度(倾向长度L2+工作面左帮控制范围left+偏移)
        //Lc = (L1 + left_margin + right_margin)*cos(angle);
        Lc = L1 + left_margin + right_margin;
        Wc = L2 + bottom_margin + top_margin;
        Hc = thick;
    }

    PlanGraph::PlanGraph( cbm::Coal& coal, cbm::DesignGoafTechnology& tech, std::vector<cbm::DesignGoafPore>& close_pores ) : Graph( coal, tech, close_pores )
    {
    }

	void PlanGraph::drawSites()
	{
		AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
		//AcGePoint3d basePt = ArxDrawHelper::CaclPt( getPoint(), v1, right, v2, h_offset );
		
		// 钻场的最大长度
		double Ld = L1 + goaf_w - (site_gap + pore_stubble);
		if(Ld > L1) Ld = L1;

		// 风巷的起点
		AcGePoint3d basePt = getPoint() + v2 * L2 * 0.5;

		// 计算钻场坐标
		AcGePoint3dArray pts;
		ArxDrawHelper::Divide( basePt + v1*Ld, basePt, site_gap, 0, pts, false, false, false );
		// 逆序
		pts.reverse();

		// 钻场、钻孔标注次数
		int site_dim_count = 0, pore_dim_count = 0;

		// 记录钻孔id
		AcDbObjectIdArray objIds;
		// 绘制钻场
		for( int i = 0; i < pts.length(); i++ )
		{
			acutPrintf(_T("\n钻场%d  x:%.1f"), i+1, pts[i].x);
			AcDbObjectId siteId = this->drawRect( pts[i], 0, Ls, Ws );

			// 标注钻场
			CString siteName;
			siteName.Format(_T("%d#"), i+1);
			this->drawMText(pts[i]+v2*w*2, 0, siteName, 6);

			if(site_dim_count == 0)
			{
				CString text;
				text.Format(_T("%dm"), (int)site_gap);
				//钻场间距
				this->drawAlignedDim(pts[i], pts[i]+v1*site_gap, text, 12, true);

				//压茬
				text.Format(_T("%dm"), (int)pore_stubble);
				this->drawAlignedDim(pts[i]+v1*site_gap, pts[i]+v1*site_gap+v1*pore_stubble, text, 12, true);

				site_dim_count++;
			}

			// 绘制每个钻场的钻孔
			for(int j=0;j<close_pores.size();j++)
			{
				AcGePoint3d pt = pts[i];
				double Lp = site_gap + pore_stubble, Wp = close_pores[j].h_offset;

				if(j == close_pores.size()-1)
				{
					// 绘制终孔分界线
					this->drawLine(pt + v1*Lp - v2*w*0.5,  pt + v1*Lp - v2*Wp);
				}

				AcDbObjectId objId = this->drawLine(pt, pt + v1*Lp - v2*Wp);
				objIds.append(objId);

				// 标注钻孔
				CString poreName;
				poreName.Format(_T("%d-%s"), i+1, C2W(close_pores[j].name));
				this->drawMText(pt + v1*Lp - v2*Wp, 0, poreName, 6, AcDbMText::kMiddleRight);

				if(pore_dim_count < close_pores.size())
				{
					CString text;
					text.Format(_T("%dm"), (int)Wp);
					//钻场间距
					this->drawAlignedDim( pt + v1*Lp - v2*w*0.5,  pt + v1*Lp - v2*Wp, text, 12+pore_dim_count*6, true,DIM_STYLE_NAME3);
					pore_dim_count++;
				}
			}
		}
		// 钻孔直线设置为虚线
		ArxDrawHelper::SetLineType( objIds, _T( "JIS_02_0.7" ) );
	}

    void PlanGraph::drawPores()
    {
    }

    void PlanGraph::drawTunnel()
    {
        //巷道的中点位置作为基点
        AcGePoint3d basePt = getPoint();
        //绘制工作面
        AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
        AcDbObjectId t1 = this->drawDoubleLine( basePt - v2 * L2 * 0.5, basePt + v1 * L1 - v2 * L2 * 0.5, w );
        //绘制风巷
        AcDbObjectId t2 = this->drawDoubleLine( basePt + v2 * L2 * 0.5, basePt + v1 * L1 + v2 * L2 * 0.5, w );
        //绘制切眼
        AcDbObjectId t3 = this->drawDoubleLine( basePt + v1 * L1 - v2 * L2 * 0.5, basePt + v1*L1 + v2 * L2 * 0.5, w );

		// 绘制采空区
		AcGePoint3dArray pts;
		double goaf_h = L2 + w;
		this->drawRect2(basePt + v1 * (L1+0.5*w) - v2 * (L2+w) * 0.5, 0, goaf_w, goaf_h);
		ArxDrawHelper::BuildRect2(basePt + v1 * (L1+0.5*w) - v2 * (L2+w) * 0.5, 0, goaf_w, goaf_h, pts);
		this->drawPolygonHatch(pts, _T( "GRAVEL" ), 1.0);

		this->drawMText( basePt + v1 * L1*0.5 - v2 * (L2 * 0.5+2*w), 0, _T( "机巷" ), 6 );
		this->drawMText( basePt + v1 * L1*0.5 + v2 * (L2 * 0.5+2*w), 0, _T( "回风巷" ), 6 );
		this->drawMText( basePt + v1 * (L1 - 2*w), 0, _T( "工作面" ), 6, AcDbMText::kMiddleRight );
    }

    void PlanGraph::drawCoal()
    {
    }

	HeadGraph::HeadGraph( cbm::Coal& coal, cbm::DesignGoafTechnology& tech, std::vector<cbm::DesignGoafPore>& close_pores ) : Graph( coal, tech, close_pores )
	{
	}

	class NameBuilder
	{
	public:
		NameBuilder(std::vector<cbm::DesignGoafPore>& _close_pores, int _site): close_pores(_close_pores), site(_site)
		{
			for(int i=0;i<close_pores.size();i++)
			{
				CString poreName;
				poreName.Format(_T("%d-%s"), site, C2W(close_pores[i].name));
				name_map[i] = poreName;
			}

			for(int i=0;i<close_pores.size();i++)
			{
				for(int j=i+1;j<close_pores.size();j++)
				{
					if(fabs(close_pores[j].v_offset - close_pores[i].v_offset) < 0.1)
					{
						CString poreName;
						poreName.Format(_T("%s、%s"), name_map[i], name_map[j]);
						name_map[i] = poreName;
						name_map.erase(name_map.find(j));
					}
				}
			}
		}

		bool getName(CString& name, int i)
		{
			if(name_map.find(i) != name_map.end())
			{
				name = name_map[i];
				return true;
			}
			else
			{
				return false;
			}
		}

	private:
		std::vector<cbm::DesignGoafPore>& close_pores;
		typedef std::map<int, CString> StringMap;
		StringMap name_map;
		int site;
	};

	void HeadGraph::drawSites()
	{
		AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
		//AcGePoint3d basePt = ArxDrawHelper::CaclPt( getPoint(), v1, right, v2, h_offset );

		// 钻场的最大长度
		double Ld = L1 + goaf_w - (site_gap + pore_stubble);
		if(Ld > L1) Ld = L1;

		// 风巷的起点
		AcGePoint3d basePt = getPoint();

		// 钻场、钻孔标注次数
		int site_dim_count = 0, pore_dim_count = 0;

		// 计算钻场坐标
		AcGePoint3dArray pts;
		ArxDrawHelper::Divide( basePt + v1*Ld, basePt, site_gap, 0, pts, false, false, false );
		// 逆序
		pts.reverse();

		// 记录钻孔id
		AcDbObjectIdArray objIds;
		// 绘制钻场
		for( int i = 0; i < pts.length(); i++ )
		{
			acutPrintf(_T("\n钻场%d  x:%.1f"), i+1, pts[i].x);
			AcDbObjectId siteId = this->drawRect( pts[i], 0, Ls, Ws );

			// 标注钻场
			CString siteName;
			siteName.Format(_T("%d#"), i+1);
			this->drawMText(pts[i]-v2*w*2, 0, siteName, 6);

			if(site_dim_count == 0)
			{
				CString text;
				text.Format(_T("%dm"), (int)site_gap);
				//钻场间距
				this->drawAlignedDim(pts[i], pts[i]+v1*site_gap, text, 12, false);

				//压茬
				text.Format(_T("%dm"), (int)pore_stubble);
				this->drawAlignedDim(pts[i]+v1*site_gap, pts[i]+v1*site_gap+v1*pore_stubble, text, 12, false);
				site_dim_count++;
			}

			NameBuilder builder(close_pores, i+1);
			// 绘制每个钻场的钻孔
			for(int j=0;j<close_pores.size();j++)
			{
				AcGePoint3d pt = pts[i];
				double Lp = site_gap + pore_stubble, Wp = close_pores[j].v_offset;
				if(j == close_pores.size()-1)
				{
					// 绘制终孔分界线
					this->drawLine(pt + v1*Lp + v2*h*0.5,  pt + v1*Lp + v2*Wp);
				}

				CString poreName;
				if(!builder.getName(poreName, j)) continue;

				AcDbObjectId objId = this->drawLine(pt, pt + v1*Lp + v2*Wp);
				objIds.append(objId);

				// 标注钻孔
				//CString poreName;
				//poreName.Format(_T("%d-%s"), i+1, C2W(close_pores[j].name));
				AcGeVector3d v = v1*Lp + v2*Wp;
				double angle = v.angleTo(AcGeVector3d::kXAxis, -AcGeVector3d::kZAxis);
				this->drawMText(pt + v1*Lp*0.5 + v2*Wp*0.5, angle, poreName, 6, AcDbMText::kBottomCenter);

				if(pore_dim_count < close_pores.size())
				{
					CString text;
					text.Format(_T("%dm"), (int)Wp);
					//钻场间距
					this->drawAlignedDim( pt + v1*Lp + v2*w*0.5,  pt + v1*Lp + v2*Wp, text, 12+pore_dim_count*6, true, DIM_STYLE_NAME3);
					pore_dim_count++;
				}
			}
		}
		// 钻孔直线设置为虚线
		ArxDrawHelper::SetLineType( objIds, _T( "JIS_02_0.7" ) );
	}

	void HeadGraph::drawPores()
	{
	}

	void HeadGraph::drawTunnel()
	{
		//巷道的中点位置作为基点
		AcGePoint3d basePt = getPoint();
		AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
		//绘制风巷
		AcDbObjectId t2 = this->drawDoubleLine( basePt, basePt + v1 * L1, h );

		this->drawMText( basePt + v1 * L1*0.5 + v2 * 2*h, 0, _T( "回风巷" ), 6 );
	}

	void HeadGraph::drawCoal()
	{
	}

} // namespace P32