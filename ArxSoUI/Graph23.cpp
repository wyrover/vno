#include "StdAfx.h"
#include "Graph23.h"

#include <ArxHelper/HelperClass.h>
#include "CbmClientHelper.h"
#include "SQLClientHelper.h"

#include <numeric>
#include <algorithm>
#include <cmath>

#include "GraphHelper.h"

namespace P23
{

	PoreHelper::PoreHelper(cbm::Coal& _coal, cbm::DesignWorkSurfTechnology& _tech)
		: coal( _coal ), tech( _tech )
	{
		//倾向长度和走向长度
		L1 = tech.l1, L2 = tech.l2;
		//煤层厚度和倾角(弧度)
		thick = coal.thick, angle = DegToRad( coal.dip_angle );
		//工作面巷道的宽度和高度
		w = tech.w, h = tech.h;
		//钻孔半径和钻孔底间距(孔径的单位是mm)
		radius = tech.dp * 0.5 * 0.001, pore_gap = tech.gp;
		//钻孔压茬长度
		pore_stubble = tech.pore_stubble;
		//顺层斜交钻孔倾角
		pore_angle = DegToRad( tech.pore_angle );
		//顺层钻孔类型
		pore_type = tech.pore_type;
	}

	void PoreHelper::drawParallelPores(std::vector<cbm::DesignPore>& pores)
	{
		//巷道的中点位置作为基点
		AcGePoint3d basePt = AcGePoint3d::kOrigin;
		AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis, v3 = AcGeVector3d::kZAxis;

		//新建1#钻场(负责下方机巷的钻孔,从右向左打钻)
		cbm::DesignSite site1;
		GraphHelper::CreateSite(site1, 1, basePt + v1 * L1 + v2 * L2 * 0.5, tech.design_technology_id);
		// 提交到数据库
		int32_t site_id1 = SQLClientHelper::AddDesignSite(site1);
		if(site_id1 <= 0) 
		{
			acutPrintf(_T("\n添加钻场1#到数据库失败!!!"));
			return;
		}

		//新建2#钻场(负责上方风巷的钻孔,从左向右打钻)
		cbm::DesignSite site2;
		GraphHelper::CreateSite(site2, 2, basePt + v2 * L2 * 0.5, tech.design_technology_id);
		// 提交到数据库
		int32_t site_id2 = SQLClientHelper::AddDesignSite(site1);
		if(site_id2 <= 0) 
		{
			acutPrintf(_T("\n添加钻场2#到数据库失败!!!"));
			return;
		}

		// 水平划分钻孔
		double PL = pore_stubble + L2 * 0.5; // 加上压茬长度
		AcGePoint3dArray pts;
		ArxDrawHelper::Divide( basePt + v1 * w * 0.5 - v2 * L2 * 0.5, basePt + v1 * L1 - v2 * L2 * 0.5, pore_gap, 0, pts );

		// 计算1#钻场(机巷)控制的钻孔
		int num = 1;
		for( int i = 0; i < pts.length(); i++ )
		{
			AcGePoint3d pt = pts[i];

			// 编号规则: 巷道编号-钻场编号-钻孔编号
			CString name;
			name.Format(_T("%d-%d"), 1, num++);
			// 新建钻孔
			cbm::DesignPore pore;
			GraphHelper::CreatePore(pore, name, pt, pt + v2 * PL, site_id1);

			// 记录新建的钻孔对象
			pores.push_back(pore);
		}

		// 计算2#钻场(机巷)控制的钻孔
		num = 1;
		v2.rotateBy( PI, AcGeVector3d::kZAxis );
		for( int i = 0; i < pts.length(); i++ )
		{
			AcGePoint3d pt = pts[i] - v2 * L2 + v1 * pore_gap * 0.5;

			// 编号规则: 巷道编号-钻场编号-钻孔编号
			CString name;
			name.Format(_T("%d-%d"), 2, num++);
			// 新建钻孔
			cbm::DesignPore pore;
			GraphHelper::CreatePore(pore, name, pt, pt + v2 * PL, site_id2);

			// 记录新建的钻孔对象
			pores.push_back(pore);
		}

		// 添加到数据库
		SQLClientHelper::AddMoreDesignPore(pores);
	}

	void PoreHelper::cacl()
	{
		if( pore_gap <= 0 ) return;

		// 删除所有的钻场和钻孔
		GraphHelper::DeleteAllSiteAndPore(tech.design_technology_id);

		// 记录所有的钻孔
		std::vector<cbm::DesignPore> pores;

		//顺层平行钻孔
		if( pore_type == 1 )
		{
			drawParallelPores(pores);
		}
		//顺层倾斜平行钻孔
		else if( pore_type == 2 )
		{
			acutPrintf(_T("\n目前只实现了顺层平行钻孔的计算...."));
			//drawCrossPores();
		}
		else if( pore_type == 3 )
		{
			acutPrintf(_T("\n目前只实现了顺层平行钻孔的计算...."));
		}
		else if( pore_type == 4 )
		{
			acutPrintf(_T("\n目前只实现了顺层平行钻孔的计算...."));
			//drawParallelPores();
			//drawCrossPores();
		}
		acutPrintf(_T("type:%d  钻孔个数:%d"), pore_type, pores.size());
	}

    Graph::Graph( cbm::Coal& _coal, cbm::DesignWorkSurfTechnology& _tech )
        : BaseGraph(), coal( _coal ), tech( _tech )
    {
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
        //钻孔半径和钻孔底间距(孔径的单位是mm)
        radius = tech.dp * 0.5 * 0.001, pore_gap = tech.gp;
        //钻孔压茬长度
        pore_stubble = tech.pore_stubble;
        //顺层斜交钻孔倾角
        pore_angle = DegToRad( tech.pore_angle );
        //顺层钻孔类型
        pore_type = tech.pore_type;
    }

    void Graph::subDraw()
    {
        //绘制图形
        drawCoal();
        drawTunnel();
        drawPores();
    }

    void Graph::caclCoalExtent( double& Lc, double& Wc, double& Hc ) const
    {
        //计算宽度(倾向长度L2+工作面左帮控制范围left+偏移)
        //Lc = (L1 + left_margin + right_margin)*cos(angle);
        Lc = L1 + left_margin + right_margin;
        Wc = L2 + bottom_margin + top_margin;
        Hc = thick;
    }

    PlanGraph::PlanGraph( cbm::Coal& coal, cbm::DesignWorkSurfTechnology& tech ) : Graph( coal,  tech )
    {
    }

    void PlanGraph::drawParallelPores()
    {
        //巷道的中点位置作为基点
        AcGePoint3d basePt = getPoint();
        AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;

        double PL = pore_stubble + L2 * 0.5;
        AcGePoint3dArray pts;
        ArxDrawHelper::Divide( basePt + v1 * w * 0.5 + v2 * L2 * 0.5, basePt + v1 * L1 + v2 * L2 * 0.5, pore_gap, 0, pts );
        v2.rotateBy( PI, AcGeVector3d::kZAxis );
        for( int i = 0; i < pts.length(); i++ )
        {
            AcGePoint3d pt = pts[i];
            this->drawLine( pt, pt + v2 * PL );
        }
        v2.rotateBy( PI, AcGeVector3d::kZAxis );
        for( int i = 0; i < pts.length(); i++ )
        {
            AcGePoint3d pt = pts[i] - v2 * L2 + v1 * pore_gap * 0.5;
            this->drawLine( pt, pt + v2 * PL );
        }
    }

    void PlanGraph::drawCrossPores()
    {
        //巷道的中点位置作为基点
        AcGePoint3d basePt = getPoint();
        AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;

        double d = 0.5 * L2 / tan( pore_angle );
        AcGePoint3dArray pts;
        ArxDrawHelper::Divide( basePt + v1 * 0.5 * w, basePt + v1 * ( L1 - d ), pore_gap, 0, pts, true );
        AcGePoint3dArray pts1;
        ArxDrawHelper::Divide( basePt + v1 * ( d + w * 0.5 ) + v2 * L2 * 0.5, basePt + v1 * L1 + v2 * L2 * 0.5, pore_gap, 0, pts1, true );
        for( int i = 0; i < pts.length(); i++ )
        {
            this->drawLine( pts1[i], pts[i] );
        }
        AcGePoint3dArray pts2;
        ArxDrawHelper::Divide( basePt + v1 * ( d + w * 0.5 ) - v2 * L2 * 0.5, basePt + v1 * L1 - v2 * L2 * 0.5, pore_gap, 0, pts2, true );
        for( int i = 0; i < pts.length(); i++ )
        {
            this->drawLine( pts2[i] + v1 * pore_gap * 0.5, pts[i] + v1 * pore_gap * 0.5 );
        }
    }

    void PlanGraph::drawPores()
    {
        if( pore_gap <= 0 ) return;

        //巷道的中点位置作为基点
        AcGePoint3d basePt = getPoint();
        AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;

        //顺层平行钻孔
        if( pore_type == 1 )
        {
            drawParallelPores();
        }
        //顺层倾斜平行钻孔
        else if( pore_type == 2 )
        {
            drawCrossPores();
        }
        else if( pore_type == 3 )
        {

        }
        else if( pore_type == 4 )
        {
            drawParallelPores();
            drawCrossPores();
        }
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
        //绘制工作面切眼
        AcDbObjectId t3 = this->drawDoubleLine( basePt - v2 * L2 * 0.5, basePt + v2 * L2 * 0.5, w );
    }

    void PlanGraph::drawCoal()
    {
        //计算煤层的长宽高
        double Lc = 0, Wc = 0, Hc = 0;
        caclCoalExtent( Lc, Wc, Hc );

        //计算平面图中煤层的左下角基点坐标
        AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
        AcGePoint3d basePt = ArxDrawHelper::CaclPt( getPoint(), v1, -1 * left_margin, v2, -0.5 * Wc );

        //绘制煤层面
        AcDbObjectId coalId = this->drawRect2( basePt, 0, Lc, Wc );
        this->drawAlignedDim( basePt, basePt + v1 * Lc, _T(""), 30, false );
        this->drawAlignedDim( basePt, basePt + v2 * Wc, _T(""), 30, true );
    }

} // namespace P23