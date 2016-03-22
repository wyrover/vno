#include "StdAfx.h"
#include "Graph12.h"

#include <ArxHelper/HelperClass.h>
#include "CbmClientHelper.h"
#include "SQLClientHelper.h"

#include <numeric>
#include <algorithm>
#include <cmath>

#include "GraphHelper.h"

namespace P12
{
	PoreHelper::PoreHelper(cbm::Coal& _coal, cbm::DesignDrillingSurfTechnology& _tech)
		: coal( _coal ), tech( _tech )
	{
		//倾向长度和走向长度
		//掘进巷道长度Lm 代替 煤层走向长度L1
		L1 = tech.lm, L2 = tech.l2;
		//煤层厚度和倾角(弧度)
		thick = coal.thick, angle = DegToRad( coal.dip_angle );
		//工作面巷道的宽度和高度
		w = tech.w, h = tech.h;
		//左右上下帮距
		left = tech.left_side, right = tech.right_side;
		top = tech.top_side, bottom = tech.bottom_side;
		//钻孔半径和钻孔底间距(孔径的单位是mm)
		radius = tech.dp * 0.5 * 0.001, pore_gap = tech.gbp;
		//钻孔超前距
		leading = tech.leading_dist;
		//钻孔控制条带长度
		L_stripe = tech.l_stripe;
	}

	void PoreHelper::drawVerticalSectionPores(const AcGePoint3d& basePt, const AcGePoint3d& center_pt, const AcGePoint3d& site_pt, int32_t site_id, int site_num, std::vector<cbm::DesignPore>& pores, int& num)
	{
		AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis, v3 = AcGeVector3d::kZAxis;

		// 计算扇形钻孔在抽采轮廓线的水平间距
		double D = pore_gap, Ls = L_stripe;

		// 计算掘进面巷道的中心点到水平轮廓线的钻孔的长度
		AcGeVector3d v = center_pt - basePt;
		// 计算斜切面上半部分的钻孔垂距
		DoubleArray vv_dists;
		ArxDrawHelper::Solve2( v.length(), top, D, vv_dists );
		// 斜切面上半部分的钻孔
		double v_pore_dist = 0;
		for( int j = 0; j < vv_dists.size(); j++ )
		{
			// 新建钻孔
			cbm::DesignPore pore;
			CString name;
			name.Format(_T("%d-%d"), site_num, num++);
			// 从上至下计算钻孔
			GraphHelper::CreatePore(pore, name, site_pt, center_pt + v3*( top + v_pore_dist ), site_id);
			// 记录新建的钻孔对象
			pores.push_back(pore);
			// 依次计算钻孔
			v_pore_dist -= vv_dists[j];
		}

		vv_dists.clear();
		// 计算斜切面上半部分的钻孔垂距
		ArxDrawHelper::Solve2( v.length(), bottom, D, vv_dists );

		// 斜切面下半部分的钻孔
		v_pore_dist = 0;
		for( int j = 0; j < vv_dists.size(); j++ )
		{
			// 新建钻孔
			cbm::DesignPore pore;
			CString name;
			name.Format(_T("%d-%d"), site_num, num++);
			// 从下至上计算钻孔
			GraphHelper::CreatePore(pore, name, site_pt, center_pt - v3*( bottom + v_pore_dist ), site_id);
			// 记录新建的钻孔对象
			pores.push_back(pore);
			// 依次计算钻孔
			v_pore_dist -= vv_dists[j];
		}
	}

	void PoreHelper::drawSidePores(bool bLeftSide, const AcGePoint3d& basePt, const AcGePoint3d& site_pt, int32_t site_id, int site_num, std::vector<cbm::DesignPore>& pores, int& num)
	{
		AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis, v3 = AcGeVector3d::kZAxis;

		// 计算扇形钻孔在抽采轮廓线的水平间距
		int c = bLeftSide?1:-1;
		double L0 = leading, W0 = bLeftSide?left:right, D = pore_gap, Ls = L_stripe;

		DoubleArray h_dists;
		ArxDrawHelper::Solve1( L0, W0, D, L_stripe - leading, h_dists );

		// 超前距的断面中心点坐标
		AcGePoint3d poreBeginPt = basePt + v1 * L0;

		// 绘制轮廓线的扇形钻孔
		double h_pore_dist = 0;
		for( int j = 0; j < h_dists.size(); j++ )
		{
			// 斜切面中心线的钻孔坐标(考虑在左侧或右侧???)
			AcGePoint3d pt = poreBeginPt + v1 * h_pore_dist + v2 * W0 * c;
			// 以掘进面巷道的中心点作为钻场坐标: site_pt
			// 计算斜切面的钻孔
			drawVerticalSectionPores(basePt, pt, site_pt, site_id, site_num, pores, num);
			// 新建斜切面中心的钻孔
			cbm::DesignPore pore;
			CString name;
			name.Format(_T("%d-%d"), site_num, num++);
			// 从下至上计算钻孔
			GraphHelper::CreatePore(pore, name, site_pt, pt, site_id);
			// 记录新建的钻孔对象
			pores.push_back(pore);

			// 钻孔沿轮廓线水平方向延伸
			h_pore_dist += h_dists[j];
		}
	}

	void PoreHelper::drawSectionPores(bool bLeftSide, const AcGePoint3d& basePt, const AcGePoint3d& site_pt, int32_t site_id, int site_num, std::vector<cbm::DesignPore>& pores, int& num)
	{
		AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis, v3 = AcGeVector3d::kZAxis;

		// 计算扇形钻孔在抽采轮廓线的水平间距
		double L0 = leading, W0 = bLeftSide?left:right, D = pore_gap, Ls = L_stripe;

		// 计算扇形钻孔在条带边界上的垂直间距
		DoubleArray v_dists;
		ArxDrawHelper::Solve2( Ls, W0, D, v_dists );

		// 超前距的断面中心点坐标
		int c = bLeftSide?1:-1;
		AcGePoint3d poreBeginPt = basePt + v1 * Ls;

		// 绘制左侧条带断面的扇形钻孔
		double v_pore_dist = 0;
		for( int j = 0; j < v_dists.size(); j++ )
		{
			// 斜切面中心线的钻孔坐标(考虑在左侧或右侧???)
			AcGePoint3d pt = poreBeginPt + v2 * (W0 - v_pore_dist) * c;
			// 计算斜切面的钻孔
			drawVerticalSectionPores(basePt, pt, site_pt, site_id, site_num, pores, num);
			// 新建斜切面中心的钻孔
			cbm::DesignPore pore;
			CString name;
			name.Format(_T("%d-%d"), site_num, num++);
			// 从下至上计算钻孔
			GraphHelper::CreatePore(pore, name, site_pt, pt, site_id);
			// 记录新建的钻孔对象
			pores.push_back(pore);
			// 从左至右计算
			v_pore_dist -= v_dists[j];
		}
	}

	void PoreHelper::cacl()
	{
		// 删除所有的钻场和钻孔
		GraphHelper::DeleteAllSiteAndPore(tech.design_technology_id);
		if( pore_gap <= 0 ) return;

		// 基点
		AcGePoint3d basePt = AcGePoint3d::kOrigin;

		// 只计算1个循环的钻孔参数

		// 钻场坐标x,y,z
		AcGePoint3d site_pt = basePt;
		//新建钻场
		cbm::DesignSite site;
		GraphHelper::CreateSite(site, 1, site_pt, tech.design_technology_id);
		// 提交到数据库
		int32_t site_id = SQLClientHelper::AddDesignSite(site);
		if(site_id <= 0) 
		{
			acutPrintf(_T("\n添加钻场到数据库失败!!!"));
			return;
		}

		// 记录所有的钻孔
		std::vector<cbm::DesignPore> pores;
		// 钻孔编号
		int num = 1;
		// 绘制水平轮廓线的左侧钻孔
		drawSidePores(true, basePt, site_pt, site_id, 1, pores, num);
		// 绘制水平轮廓线的右侧钻孔
		drawSidePores(false, basePt, site_pt, site_id, 1, pores, num);
		// 绘制超前距断面的左侧钻孔
		drawSectionPores(true, basePt, site_pt, site_id, 1, pores, num);
		// 绘制超前距断面的右侧钻孔
		drawSectionPores(false, basePt, site_pt, site_id, 1, pores, num);

		// 添加到数据库
		SQLClientHelper::AddMoreDesignPore(pores);
	}

    Graph::Graph( cbm::Coal& _coal, cbm::DesignDrillingSurfTechnology& _tech )
        : BaseGraph(), coal( _coal ), tech( _tech )
    {
        left_margin = 20;
        right_margin = 20;
        bottom_margin = 20;
        top_margin = 20;

        //倾向长度和走向长度
        L1 = tech.lm, L2 = tech.l2;
        //煤层厚度和倾角(弧度)
        thick = coal.thick, angle = DegToRad( coal.dip_angle );
        //工作面巷道的宽度和高度
        w = tech.w, h = tech.h;
        //左右上下帮距
        left = tech.left_side, right = tech.right_side;
        top = tech.top_side, bottom = tech.bottom_side;
        //钻孔半径和钻孔底间距(孔径的单位是mm)
        radius = tech.dp * 0.5 * 0.001, pore_gap = tech.gbp;
        //钻孔超前距
        leading = tech.leading_dist;
        //钻孔控制条带长度
        L_stripe = tech.l_stripe;
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
        //Lc = (L1 + left + left_margin + right_margin)*cos(angle);
        Lc = L1 + left + left_margin + right_margin;
        //Wc = L2 + left + right + bottom_margin + top_margin;
        Wc = w + left + right + bottom_margin + top_margin;
        Hc = thick;
    }

    PlanGraph::PlanGraph( cbm::Coal& coal, cbm::DesignDrillingSurfTechnology& tech ) : Graph( coal,  tech )
    {
    }

    void PlanGraph::drawPores()
    {
        if( pore_gap <= 0 ) return;

        //巷道的中点位置作为基点
        AcGePoint3d basePt = getPoint();
        AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;

        double Lp = L1, Wp = left + right, Hp = 0;

        //计算扇形钻孔在抽采轮廓线的水平间距
        double L0 = leading, W0 = left, D = pore_gap, Ls = L_stripe;
        DoubleArray h_dists;
        ArxDrawHelper::Solve1( L0, W0, D, L_stripe - leading, h_dists );

        //计算扇形钻孔在条带边界上的垂直间距
        DoubleArray v_dists;
        ArxDrawHelper::Solve2( Ls, W0, D, v_dists );

        //标注
		CString text;
		text.Format(_T("%dm"), (int)Ls);
		//条带范围
        this->drawAlignedDim(basePt-v2*right, basePt+v1*Ls-v2*right, text, 15, false);
		text.Format(_T("%dm"), (int)L0);
        //钻孔超前距
		this->drawAlignedDim(basePt+v1*(Ls-L0)+v2*left, basePt+v1*Ls+v2*left, text, -15, false);

        //计算每个条带的起始位置
        AcGePoint3dArray pts;
        ArxDrawHelper::Divide( basePt, basePt + v1 * L1, L_stripe - leading, 0, pts, false, true, false );
		acutPrintf(_T("\n条带个数:%d"), pts.length());
        for( int i = 0; i < pts.length(); i++ )
        {
            //绘制掘进面
            AcGePoint3d pt = pts[i];
            drawLine( pt - v2 * w * 0.5, pt + v2 * w * 0.5 );
            //绘制掘进面的起始垂线
            drawLine( pt - v2 * W0, pt + v2 * W0 );

            //记录钻孔图元id
            AcDbObjectIdArray objIds;

            //超前距的断面中心点坐标
            AcGePoint3d poreBeginPt = pt + v1 * L0;
            //绘制左侧轮廓线的扇形钻孔
            double pore_dist = 0;
            for( int j = 0; j < h_dists.size(); j++ )
            {
                AcDbObjectId poreId = drawLine( pt, poreBeginPt + v1 * pore_dist + v2 * W0 );
                pore_dist += h_dists[j];
                objIds.append( poreId );
            }
            //绘制右侧轮廓线的扇形钻孔
            pore_dist = 0;
            for( int j = 0; j < h_dists.size(); j++ )
            {
                AcDbObjectId poreId = drawLine( pt, poreBeginPt + v1 * pore_dist - v2 * W0 );
                pore_dist += h_dists[j];
                objIds.append( poreId );
            }

            //绘制左侧条带断面的扇形钻孔
            pore_dist = 0;
            for( int j = 0; j < v_dists.size(); j++ )
            {
                AcDbObjectId poreId = drawLine( pt, pt + v1 * Ls + v2 * ( W0 + pore_dist ) );
                pore_dist -= v_dists[j];
                objIds.append( poreId );
            }
            //绘制右侧条带断面的扇形钻孔
            pore_dist = 0;
            for( int j = 0; j < v_dists.size(); j++ )
            {
                AcDbObjectId poreId = drawLine( pt, pt + v1 * Ls - v2 * ( W0 + pore_dist ) );
                pore_dist -= v_dists[j];
                objIds.append( poreId );
            }

            //绘制中心线的钻孔
            {
                AcDbObjectId poreId = drawLine( pt, pt + v1 * Ls );
                objIds.append( poreId );
            }

            // 绘制条带断面
            AcGePoint3d poreEndPt = pt + v1 * L_stripe;
            drawLine( poreEndPt - v2 * W0, poreEndPt + v2 * W0 );

            //i为奇数修改线型为虚线
            if( i % 2 != 0 )
            {
                ArxDrawHelper::SetLineType( objIds, _T( "JIS_02_0.7" ) );
            }
            objIds.removeAll();
        }

		//绘制钻孔抽采控制范围
		//drawLine( basePt + v1 * 0 + v2 * Wp * 0.5, 0, Lp );
		//drawLine( basePt + v1 * 0 - v2 * Wp * 0.5, 0, Lp );
		// 微调
		double L11 =  pts.length()*(L_stripe - leading) + leading;
		drawLine( basePt + v1 * 0 + v2 * Wp * 0.5, 0, L11 );
		drawLine( basePt + v1 * 0 - v2 * Wp * 0.5, 0, L11 );
    }

    void PlanGraph::drawTunnel()
    {
        //巷道的中点位置作为基点
        AcGePoint3d basePt = getPoint();
        //绘制掘进巷
        AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
		AcGePoint3dArray pts;
		ArxDrawHelper::Divide( basePt, basePt + v1 * L1, L_stripe - leading, 0, pts, false, true, false );
        //AcDbObjectId t1 = this->drawDoubleLine( basePt, basePt + v1 * L1, w );
		// 微调
		double L11 =  pts.length()*(L_stripe - leading) + leading;
		AcDbObjectId t1 = this->drawDoubleLine( basePt, basePt + v1*L11, w );

		//标注左帮和右帮
		CString text;
		text.Format(_T("%dm"), (int)left);
		this->drawAlignedDim( basePt + v2 * left, basePt + v2*w*0.5, text, 15, false );
		text.Format(_T("%dm"), (int)right);
		this->drawAlignedDim( basePt - v2*w*0.5, basePt - v2 * right, text, 15, false );
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
        //this->drawAlignedDim( basePt, basePt + v1 * Lc, _T(""), 30, false );
        //this->drawAlignedDim( basePt, basePt + v2 * Wc, _T(""), 30, true );
    }

} // namespace P12