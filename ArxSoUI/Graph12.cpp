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
		//���򳤶Ⱥ����򳤶�
		//����������Lm ���� ú�����򳤶�L1
		L1 = tech.lm, L2 = tech.l2;
		//ú���Ⱥ����(����)
		thick = coal.thick, angle = DegToRad( coal.dip_angle );
		//����������Ŀ�Ⱥ͸߶�
		w = tech.w, h = tech.h;
		//�������°��
		left = tech.left_side, right = tech.right_side;
		top = tech.top_side, bottom = tech.bottom_side;
		//��װ뾶����׵׼��(�׾��ĵ�λ��mm)
		radius = tech.dp * 0.5 * 0.001, pore_gap = tech.gbp;
		//��׳�ǰ��
		leading = tech.leading_dist;
		//��׿�����������
		L_stripe = tech.l_stripe;
	}

	void PoreHelper::drawVerticalSectionPores(const AcGePoint3d& basePt, const AcGePoint3d& center_pt, const AcGePoint3d& site_pt, int32_t site_id, int site_num, std::vector<cbm::DesignPore>& pores, int& num)
	{
		AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis, v3 = AcGeVector3d::kZAxis;

		// ������������ڳ�������ߵ�ˮƽ���
		double D = pore_gap, Ls = L_stripe;

		// ����������������ĵ㵽ˮƽ�����ߵ���׵ĳ���
		AcGeVector3d v = center_pt - basePt;
		// ����б�����ϰ벿�ֵ���״���
		DoubleArray vv_dists;
		ArxDrawHelper::Solve2( v.length(), top, D, vv_dists );
		// б�����ϰ벿�ֵ����
		double v_pore_dist = 0;
		for( int j = 0; j < vv_dists.size(); j++ )
		{
			// �½����
			cbm::DesignPore pore;
			CString name;
			name.Format(_T("%d-%d"), site_num, num++);
			// �������¼������
			GraphHelper::CreatePore(pore, name, site_pt, center_pt + v3*( top + v_pore_dist ), site_id);
			// ��¼�½�����׶���
			pores.push_back(pore);
			// ���μ������
			v_pore_dist -= vv_dists[j];
		}

		vv_dists.clear();
		// ����б�����ϰ벿�ֵ���״���
		ArxDrawHelper::Solve2( v.length(), bottom, D, vv_dists );

		// б�����°벿�ֵ����
		v_pore_dist = 0;
		for( int j = 0; j < vv_dists.size(); j++ )
		{
			// �½����
			cbm::DesignPore pore;
			CString name;
			name.Format(_T("%d-%d"), site_num, num++);
			// �������ϼ������
			GraphHelper::CreatePore(pore, name, site_pt, center_pt - v3*( bottom + v_pore_dist ), site_id);
			// ��¼�½�����׶���
			pores.push_back(pore);
			// ���μ������
			v_pore_dist -= vv_dists[j];
		}
	}

	void PoreHelper::drawSidePores(bool bLeftSide, const AcGePoint3d& basePt, const AcGePoint3d& site_pt, int32_t site_id, int site_num, std::vector<cbm::DesignPore>& pores, int& num)
	{
		AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis, v3 = AcGeVector3d::kZAxis;

		// ������������ڳ�������ߵ�ˮƽ���
		int c = bLeftSide?1:-1;
		double L0 = leading, W0 = bLeftSide?left:right, D = pore_gap, Ls = L_stripe;

		DoubleArray h_dists;
		ArxDrawHelper::Solve1( L0, W0, D, L_stripe - leading, h_dists );

		// ��ǰ��Ķ������ĵ�����
		AcGePoint3d poreBeginPt = basePt + v1 * L0;

		// ���������ߵ��������
		double h_pore_dist = 0;
		for( int j = 0; j < h_dists.size(); j++ )
		{
			// б���������ߵ��������(�����������Ҳ�???)
			AcGePoint3d pt = poreBeginPt + v1 * h_pore_dist + v2 * W0 * c;
			// �Ծ������������ĵ���Ϊ�곡����: site_pt
			// ����б��������
			drawVerticalSectionPores(basePt, pt, site_pt, site_id, site_num, pores, num);
			// �½�б�������ĵ����
			cbm::DesignPore pore;
			CString name;
			name.Format(_T("%d-%d"), site_num, num++);
			// �������ϼ������
			GraphHelper::CreatePore(pore, name, site_pt, pt, site_id);
			// ��¼�½�����׶���
			pores.push_back(pore);

			// �����������ˮƽ��������
			h_pore_dist += h_dists[j];
		}
	}

	void PoreHelper::drawSectionPores(bool bLeftSide, const AcGePoint3d& basePt, const AcGePoint3d& site_pt, int32_t site_id, int site_num, std::vector<cbm::DesignPore>& pores, int& num)
	{
		AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis, v3 = AcGeVector3d::kZAxis;

		// ������������ڳ�������ߵ�ˮƽ���
		double L0 = leading, W0 = bLeftSide?left:right, D = pore_gap, Ls = L_stripe;

		// ������������������߽��ϵĴ�ֱ���
		DoubleArray v_dists;
		ArxDrawHelper::Solve2( Ls, W0, D, v_dists );

		// ��ǰ��Ķ������ĵ�����
		int c = bLeftSide?1:-1;
		AcGePoint3d poreBeginPt = basePt + v1 * Ls;

		// �����������������������
		double v_pore_dist = 0;
		for( int j = 0; j < v_dists.size(); j++ )
		{
			// б���������ߵ��������(�����������Ҳ�???)
			AcGePoint3d pt = poreBeginPt + v2 * (W0 - v_pore_dist) * c;
			// ����б��������
			drawVerticalSectionPores(basePt, pt, site_pt, site_id, site_num, pores, num);
			// �½�б�������ĵ����
			cbm::DesignPore pore;
			CString name;
			name.Format(_T("%d-%d"), site_num, num++);
			// �������ϼ������
			GraphHelper::CreatePore(pore, name, site_pt, pt, site_id);
			// ��¼�½�����׶���
			pores.push_back(pore);
			// �������Ҽ���
			v_pore_dist -= v_dists[j];
		}
	}

	void PoreHelper::cacl()
	{
		// ɾ�����е��곡�����
		GraphHelper::DeleteAllSiteAndPore(tech.design_technology_id);
		if( pore_gap <= 0 ) return;

		// ����
		AcGePoint3d basePt = AcGePoint3d::kOrigin;

		// ֻ����1��ѭ������ײ���

		// �곡����x,y,z
		AcGePoint3d site_pt = basePt;
		//�½��곡
		cbm::DesignSite site;
		GraphHelper::CreateSite(site, 1, site_pt, tech.design_technology_id);
		// �ύ�����ݿ�
		int32_t site_id = SQLClientHelper::AddDesignSite(site);
		if(site_id <= 0) 
		{
			acutPrintf(_T("\n����곡�����ݿ�ʧ��!!!"));
			return;
		}

		// ��¼���е����
		std::vector<cbm::DesignPore> pores;
		// ��ױ��
		int num = 1;
		// ����ˮƽ�����ߵ�������
		drawSidePores(true, basePt, site_pt, site_id, 1, pores, num);
		// ����ˮƽ�����ߵ��Ҳ����
		drawSidePores(false, basePt, site_pt, site_id, 1, pores, num);
		// ���Ƴ�ǰ������������
		drawSectionPores(true, basePt, site_pt, site_id, 1, pores, num);
		// ���Ƴ�ǰ�������Ҳ����
		drawSectionPores(false, basePt, site_pt, site_id, 1, pores, num);

		// ��ӵ����ݿ�
		SQLClientHelper::AddMoreDesignPore(pores);
	}

    Graph::Graph( cbm::Coal& _coal, cbm::DesignDrillingSurfTechnology& _tech )
        : BaseGraph(), coal( _coal ), tech( _tech )
    {
        left_margin = 20;
        right_margin = 20;
        bottom_margin = 20;
        top_margin = 20;

        //���򳤶Ⱥ����򳤶�
        L1 = tech.lm, L2 = tech.l2;
        //ú���Ⱥ����(����)
        thick = coal.thick, angle = DegToRad( coal.dip_angle );
        //����������Ŀ�Ⱥ͸߶�
        w = tech.w, h = tech.h;
        //�������°��
        left = tech.left_side, right = tech.right_side;
        top = tech.top_side, bottom = tech.bottom_side;
        //��װ뾶����׵׼��(�׾��ĵ�λ��mm)
        radius = tech.dp * 0.5 * 0.001, pore_gap = tech.gbp;
        //��׳�ǰ��
        leading = tech.leading_dist;
        //��׿�����������
        L_stripe = tech.l_stripe;
    }

    void Graph::subDraw()
    {
        //����ͼ��
        drawCoal();
        drawTunnel();
        drawPores();
    }

    void Graph::caclCoalExtent( double& Lc, double& Wc, double& Hc ) const
    {
        //������(���򳤶�L2+�����������Ʒ�Χleft+ƫ��)
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

        //������е�λ����Ϊ����
        AcGePoint3d basePt = getPoint();
        AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;

        double Lp = L1, Wp = left + right, Hp = 0;

        //������������ڳ�������ߵ�ˮƽ���
        double L0 = leading, W0 = left, D = pore_gap, Ls = L_stripe;
        DoubleArray h_dists;
        ArxDrawHelper::Solve1( L0, W0, D, L_stripe - leading, h_dists );

        //������������������߽��ϵĴ�ֱ���
        DoubleArray v_dists;
        ArxDrawHelper::Solve2( Ls, W0, D, v_dists );

        //��ע
		CString text;
		text.Format(_T("%dm"), (int)Ls);
		//������Χ
        this->drawAlignedDim(basePt-v2*right, basePt+v1*Ls-v2*right, text, 15, false);
		text.Format(_T("%dm"), (int)L0);
        //��׳�ǰ��
		this->drawAlignedDim(basePt+v1*(Ls-L0)+v2*left, basePt+v1*Ls+v2*left, text, -15, false);

        //����ÿ����������ʼλ��
        AcGePoint3dArray pts;
        ArxDrawHelper::Divide( basePt, basePt + v1 * L1, L_stripe - leading, 0, pts, false, true, false );
		acutPrintf(_T("\n��������:%d"), pts.length());
        for( int i = 0; i < pts.length(); i++ )
        {
            //���ƾ����
            AcGePoint3d pt = pts[i];
            drawLine( pt - v2 * w * 0.5, pt + v2 * w * 0.5 );
            //���ƾ�������ʼ����
            drawLine( pt - v2 * W0, pt + v2 * W0 );

            //��¼���ͼԪid
            AcDbObjectIdArray objIds;

            //��ǰ��Ķ������ĵ�����
            AcGePoint3d poreBeginPt = pt + v1 * L0;
            //������������ߵ��������
            double pore_dist = 0;
            for( int j = 0; j < h_dists.size(); j++ )
            {
                AcDbObjectId poreId = drawLine( pt, poreBeginPt + v1 * pore_dist + v2 * W0 );
                pore_dist += h_dists[j];
                objIds.append( poreId );
            }
            //�����Ҳ������ߵ��������
            pore_dist = 0;
            for( int j = 0; j < h_dists.size(); j++ )
            {
                AcDbObjectId poreId = drawLine( pt, poreBeginPt + v1 * pore_dist - v2 * W0 );
                pore_dist += h_dists[j];
                objIds.append( poreId );
            }

            //�����������������������
            pore_dist = 0;
            for( int j = 0; j < v_dists.size(); j++ )
            {
                AcDbObjectId poreId = drawLine( pt, pt + v1 * Ls + v2 * ( W0 + pore_dist ) );
                pore_dist -= v_dists[j];
                objIds.append( poreId );
            }
            //�����Ҳ�����������������
            pore_dist = 0;
            for( int j = 0; j < v_dists.size(); j++ )
            {
                AcDbObjectId poreId = drawLine( pt, pt + v1 * Ls - v2 * ( W0 + pore_dist ) );
                pore_dist -= v_dists[j];
                objIds.append( poreId );
            }

            //���������ߵ����
            {
                AcDbObjectId poreId = drawLine( pt, pt + v1 * Ls );
                objIds.append( poreId );
            }

            // ������������
            AcGePoint3d poreEndPt = pt + v1 * L_stripe;
            drawLine( poreEndPt - v2 * W0, poreEndPt + v2 * W0 );

            //iΪ�����޸�����Ϊ����
            if( i % 2 != 0 )
            {
                ArxDrawHelper::SetLineType( objIds, _T( "JIS_02_0.7" ) );
            }
            objIds.removeAll();
        }

		//������׳�ɿ��Ʒ�Χ
		//drawLine( basePt + v1 * 0 + v2 * Wp * 0.5, 0, Lp );
		//drawLine( basePt + v1 * 0 - v2 * Wp * 0.5, 0, Lp );
		// ΢��
		double L11 =  pts.length()*(L_stripe - leading) + leading;
		drawLine( basePt + v1 * 0 + v2 * Wp * 0.5, 0, L11 );
		drawLine( basePt + v1 * 0 - v2 * Wp * 0.5, 0, L11 );
    }

    void PlanGraph::drawTunnel()
    {
        //������е�λ����Ϊ����
        AcGePoint3d basePt = getPoint();
        //���ƾ����
        AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
		AcGePoint3dArray pts;
		ArxDrawHelper::Divide( basePt, basePt + v1 * L1, L_stripe - leading, 0, pts, false, true, false );
        //AcDbObjectId t1 = this->drawDoubleLine( basePt, basePt + v1 * L1, w );
		// ΢��
		double L11 =  pts.length()*(L_stripe - leading) + leading;
		AcDbObjectId t1 = this->drawDoubleLine( basePt, basePt + v1*L11, w );

		//��ע�����Ұ�
		CString text;
		text.Format(_T("%dm"), (int)left);
		this->drawAlignedDim( basePt + v2 * left, basePt + v2*w*0.5, text, 15, false );
		text.Format(_T("%dm"), (int)right);
		this->drawAlignedDim( basePt - v2*w*0.5, basePt - v2 * right, text, 15, false );
    }

    void PlanGraph::drawCoal()
    {
        //����ú��ĳ����
        double Lc = 0, Wc = 0, Hc = 0;
        caclCoalExtent( Lc, Wc, Hc );

        //����ƽ��ͼ��ú������½ǻ�������
        AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
        AcGePoint3d basePt = ArxDrawHelper::CaclPt( getPoint(), v1, -1 * left_margin, v2, -0.5 * Wc );

        //����ú����
        AcDbObjectId coalId = this->drawRect2( basePt, 0, Lc, Wc );
        //this->drawAlignedDim( basePt, basePt + v1 * Lc, _T(""), 30, false );
        //this->drawAlignedDim( basePt, basePt + v2 * Wc, _T(""), 30, true );
    }

} // namespace P12