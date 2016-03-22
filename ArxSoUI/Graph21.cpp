#include "StdAfx.h"
#include "Graph21.h"

#include <ArxHelper/HelperClass.h>
#include "CbmClientHelper.h"
#include "SQLClientHelper.h"

#include <numeric>
#include <algorithm>
#include <cmath>

#include "GraphHelper.h"

namespace P21
{

	PoreHelper::PoreHelper(cbm::Coal& _coal, cbm::DesignWorkSurfTechnology& _tech)
		: coal( _coal ), tech( _tech )
	{
		//���򳤶Ⱥ����򳤶�
		L1 = tech.l1, L2 = tech.l2;
		//ú���Ⱥ����(����)
		thick = coal.thick, angle = DegToRad( coal.dip_angle );
		//����������Ŀ�Ⱥ͸߶�
		w = tech.w, h = tech.h;
		//�װ���Ŀ�Ⱥ͸߶�
		wd = tech.wd, hd = tech.hd;
		//�������°��
		left = tech.left_side, right = tech.right_side;
		top = tech.top_side, bottom = tech.bottom_side;
		//�곡���ȡ���Ⱥ͸߶�
		Ls = tech.ls, Ws = tech.ws, Hs = tech.hs;
		//����͹������ˮƽͶӰ���롢����
		h_offset = tech.h_offset, v_offset = tech.v_offset;
		//��װ뾶�ͳ�ɰ뾶(�׾��ĵ�λ��mm)
		radius = tech.dp * 0.5 * 0.001, pore_gap = tech.gp;
		//�곡���
		site_gap = tech.gs;
		//ֻ����һ������
		single_rock_tunnel = ( tech.single_rock_tunnel != 0 );
		//��������֮��ľ���
		d_offset = tech.d_offset;
		//�װ����빤�������۵�ˮƽͶӰ����
		p_offset = tech.p_offset;
	}

	void PoreHelper::drawPores1(const AcGePoint3dArray& site_pts, const IntArray& col_nums, const AcGePoint3dArray& pore_pts, int nx, int r1, int r2, int c1, int c2, std::vector<cbm::DesignPore>& pores)
	{
		// ��ױ��
		int num = 1;

		// (1)������������
		int n = site_pts.length();
		for(int i=n-1;i>=0;i--)
		{
			// �곡����x,y,z
			AcGePoint3d site_pt = site_pts[i];

			//�½��곡
			cbm::DesignSite site;
			GraphHelper::CreateSite(site, n-i, site_pt, tech.design_technology_id);
			// �ύ�����ݿ�
			int32_t site_id = SQLClientHelper::AddDesignSite(site);
			if(site_id <= 0) 
			{
				acutPrintf(_T("\n����곡�����ݿ�ʧ��!!!"));
				pores.clear();
				break;
			}

			acutPrintf(_T("\n�곡:%d  id:%d"), n-i, site_id);

			// �곡��������ʼλ��
			r2 -= col_nums[i];
			acutPrintf(_T("\n����---�곡%d����:%d~%d, ��:%d~%d"), n-i, r1, r2, c1, c2);
			// �������
			for(int j=r1-1;j>=r2;j--)
			{
				for(int k=c1-1;k>=c2;k--)
				{
					// ��Ź���: ������-�곡���-��ױ��
					CString name;
					name.Format(_T("%d-%d-%d"), 1, n-i, num++);
					// �������
					AcGePoint3d pore_pt = pore_pts[j*nx+k];

					// �½����
					cbm::DesignPore pore;
					GraphHelper::CreatePore(pore, name, site_pt, pore_pt, site_id);

					// ��¼�½�����׶���
					pores.push_back(pore);
				}
			}
			r1 = r2;
		}
	}

	void PoreHelper::assingPores(IntArray& nums, int S, int n, int step)
	{
		nums.resize(n, 0);
		int d = S - n*step;
		nums[0] = d/2;
		for(int i=0;i<n;i++)
		{
			nums[i] += step;
		}
		nums[n-1] += d - d/2;
	}

	void PoreHelper::cacl()
	{
		if(!single_rock_tunnel) 
		{
			acutPrintf(_T("\nĿǰֻʵ���˵����������ײ���,�˳��������..."));
			return;
		}

		// ɾ�����е��곡�����
		GraphHelper::DeleteAllSiteAndPore(tech.design_technology_id);

		acutPrintf(_T("\nid1:%d  id2:%d"), tech.id, tech.design_technology_id);

		// ������������е���Ϊԭ��
		AcGePoint3d orig(AcGePoint3d::kOrigin);

		// ��׿��Ʒ�Χ
		double Lc = left + L1, Wc = L2 + top + bottom;
		// ���Ʒ�Χ���½ǵ�����(��׵�ԭ��)
		AcGeVector3d v1(AcGeVector3d::kXAxis), v2(AcGeVector3d::kYAxis), v3(AcGeVector3d::kZAxis);
		AcGePoint3d pore_orig = orig + v1*left*-1 + v2*(0.5*L2+left)*-1 + v3*top;

		//�۳��Ұ�
		double Ld = L1 - p_offset;

		// ��������������е��������
		// �������е��տ׶���ͬһ��ˮƽ����
		AcGePoint3dArray pore_pts;
		ArxDrawHelper::MakeGridWithHole( pore_orig, Lc, Wc, pore_gap, pore_gap, 0, Lc, 0, Wc, pore_pts, true );

		//�������������(��)������(��)�ĸ���(�л���)
		int nx = ArxDrawHelper::DivideNum( Lc, pore_gap, false ) + 1;
		int ny = ArxDrawHelper::DivideNum( Wc, pore_gap, false ) + 1;
		//��������(��)������곡��(�л���)
		int mx = ArxDrawHelper::DivideNum( Ld, site_gap, false ) + 1;
		//�������ﷶΧ�ڵ������(�л���)
		int d1 = ArxDrawHelper::DivideNum( left + p_offset, pore_gap, false ) + 1;
		//ÿ���곡֮�����׸���
		int d2 = ArxDrawHelper::DivideNum( site_gap, pore_gap, false ) + 1;

		acutPrintf(_T("\n����������:%d  �������:%d  ��׵��ܸ���:%d"), nx, ny, pore_pts.length());
		// �����곡������(CaclSitesOnTunnel�����ĺ�3������Ŀǰû���õ�!!!)
		// (0)������װ�������е�����
		double rock_L2 = h_offset;
		if(single_rock_tunnel) rock_L2 = 0;

		AcGePoint3d site_orig = orig + v1*p_offset + v2*rock_L2 - v3*v_offset;
		// (1)���������곡����
		AcGePoint3dArray site_pts1;
		GraphHelper::CaclSitesOnTunnel( site_pts1, site_orig, site_orig + v1 * Ld, site_gap, -0.5 * ( Ws + wd ), Ls, Ws, 0, false );

		// ���������Ƶ����(ÿ���곡����xx��)
		IntArray pore_nums1;
		assingPores(pore_nums1, nx-d1, site_pts1.length(), d2);
		pore_nums1[0] += d1;

		// ��¼���е����
		std::vector<cbm::DesignPore> pores;

		// (1)������������
		drawPores1(site_pts1, pore_nums1, pore_pts, ny, nx, nx, ny, 0, pores);

		acutPrintf(_T("\n��׸���:%d"), pores.size());
		// ��ӵ����ݿ�
		SQLClientHelper::AddMoreDesignPore(pores);
	}

    Graph::Graph( cbm::Coal& _coal, cbm::DesignWorkSurfTechnology& _tech )
        : BaseGraph(), coal( _coal ), tech( _tech )
    {
        left_margin = 20;
        right_margin = 20;
        bottom_margin = 20;
        top_margin = 40;

        //���򳤶Ⱥ����򳤶�
        L1 = tech.l1, L2 = tech.l2;
        //ú���Ⱥ����(����)
        thick = coal.thick, angle = DegToRad( coal.dip_angle );
        //����������Ŀ�Ⱥ͸߶�
        w = tech.w, h = tech.h;
        //�װ���Ŀ�Ⱥ͸߶�
        wd = tech.wd, hd = tech.hd;
        //�������°��
        left = tech.left_side, right = tech.right_side;
        top = tech.top_side, bottom = tech.bottom_side;
        //�곡���ȡ���Ⱥ͸߶�
        Ls = tech.ls, Ws = tech.ws, Hs = tech.hs;
        //����͹������ˮƽͶӰ���롢����
        h_offset = tech.h_offset, v_offset = tech.v_offset;
        //��װ뾶�ͳ�ɰ뾶(�׾��ĵ�λ��mm)
        radius = tech.dp * 0.5 * 0.001, pore_gap = tech.gp;
        //�곡���
        site_gap = tech.gs;
        //ֻ����һ������
        single_rock_tunnel = ( tech.single_rock_tunnel != 0 );
        //��������֮��ľ���
        d_offset = tech.d_offset;
        //�װ����빤�������۵�ˮƽͶӰ����
        p_offset = tech.p_offset;
    }

    void Graph::subDraw()
    {
        //����ͼ��
        drawCoal();
        drawTunnel();
        drawRockTunnel();
        drawPores();
        drawSites();
    }

    void Graph::caclCoalExtent( double& Lc, double& Wc, double& Hc ) const
    {
        //������(���򳤶�L2+�����������Ʒ�Χleft+ƫ��)
        //Lc = (L1 + left + left_margin + right_margin)*cos(angle);
        Lc = L1 + left + left_margin + right_margin;
        Wc = L2 + left + right + bottom_margin + top_margin;
        Hc = thick;
    }

    AcGePoint3d Graph::caclCoalBasePoint1() const
    {
        AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
        return ArxDrawHelper::CaclPt( getPoint(), v1, -1 * ( left + left_margin ), v2, -1 * ( 0.5 * L2 + left + bottom_margin ) );
    }

    AcGePoint3d Graph::caclCoalBasePoint2() const
    {
        AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
        return ArxDrawHelper::CaclPt( getPoint(), v1, -1 * ( left + left_margin ), v2, -0.5 * thick );;
    }

    AcGePoint3d Graph::caclCoalBasePoint3() const
    {
        double Lc = 0, Wc = 0, Hc = 0;
        caclCoalExtent( Lc, Wc, Hc );

        AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
        return ArxDrawHelper::CaclPt( getPoint(), v1, -0.5 * Wc, v2, -0.5 * thick );;
    }

    void Graph::caclPoreExtent( double& Lp, double& Wp, double& Hp ) const
    {
        //���㳤��(���򳤶�L2+�����������Ʒ�Χleft+ƫ��)
        //Lp = (L1 + left)*cos(angle);
        Lp = L1 + left;
        Wp = L2 + left + right;
        Hp = 0.5;
    }

    AcGePoint3d Graph::caclPoreBasePoint1() const
    {
        AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
        return ArxDrawHelper::CaclPt( getPoint(), v1, -1 * left, v2, -1 * ( left + 0.5 * L2 ) );
    }

    AcGePoint3d Graph::caclPoreBasePoint2() const
    {
        double Lp = 0, Wp = 0, Hp = 0;
        caclPoreExtent( Lp, Wp, Hp );
        AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
        return ArxDrawHelper::CaclPt( getPoint(), v1, -1 * left, v2, 0.5 * thick + Hp );
    }

	//����һ������ϵ��곡
    void Graph::drawSitesOnTunnel( const AcGePoint3d& spt, const AcGePoint3d& ept, double gap_x, double gap_y, double w, double h, double angle, bool excludeFirst, bool tunning )
    {
        AcGePoint3dArray pts;
        ArxDrawHelper::Divide( spt, ept, gap_x, gap_y, pts, false, excludeFirst, tunning );
        for( int i = 0; i < pts.length(); i++ )
        {
            AcDbObjectId siteId = this->drawRect( pts[i], angle, w, h );
        }
    }

    PlanGraph::PlanGraph( cbm::Coal& coal, cbm::DesignWorkSurfTechnology& tech ) : Graph( coal, tech )
    {
    }

    void PlanGraph::drawSites()
    {
        double right_offset = p_offset;
        double rock_L2 = d_offset;
		if(single_rock_tunnel) rock_L2 = 0;

        //�۳��Ұ�
        double Ld = L1 - right_offset;

        AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
        AcGePoint3d basePt = ArxDrawHelper::CaclPt( getPoint(), v1, right_offset, v2, 0 );
        //�����곡
        if( single_rock_tunnel )
        {
            drawSitesOnTunnel( basePt + v2 * rock_L2 * 0.5, basePt + v1 * Ld + v2 * 0.5 * rock_L2, site_gap, -0.5 * ( Ws + wd ), Ls, Ws, 0, false, false );
        }
        else
        {
			//���Ʒ����곡
            drawSitesOnTunnel( basePt - v2 * rock_L2 * 0.5, basePt + v1 * Ld - v2 * 0.5 * rock_L2, site_gap, -0.5 * ( Ws + wd ), Ls, Ws, 0 );
			//���ƹ����������곡
            drawSitesOnTunnel( basePt - v2 * rock_L2 * 0.5, basePt + v2 * rock_L2 * 0.5, site_gap, 0.5 * ( Ws + wd ), Ls, Ws, -PI * 0.5, false );
			//���ƻ����곡
            drawSitesOnTunnel( basePt + v2 * rock_L2 * 0.5, basePt + v1 * Ld + v2 * rock_L2 * 0.5, site_gap, -0.5 * ( Ws + wd ), Ls, Ws, 0 );
        }
    }

    void PlanGraph::drawPores()
    {
        if( pore_gap <= 0 ) return;

        //�������ƽ��ͶӰ��Χ
        double Lp = 0, Wp = 0, Hp = 0;
        caclPoreExtent( Lp, Wp, Hp );
        //ƽ��ͼ��׷�Χ�����½ǻ�������
        AcGePoint3d basePt = caclPoreBasePoint1();

        //�������
        AcGePoint3dArray pts;
        ArxDrawHelper::MakeGridWithHole( basePt, Lp, Wp, pore_gap, pore_gap, 0, Lp, 0, Wp, pts, true );
        for( int i = 0; i < pts.length(); i++ )
        {
            AcDbObjectId poreId = this->drawCircle( pts[i], radius );
        }
    }

    void PlanGraph::drawRockTunnel()
    {
        //double right_offset = right;
        double right_offset = p_offset;
        double rock_L2 = d_offset;
		if(single_rock_tunnel) rock_L2 = 0;

        //�۳�ƫ�ƵĲ���
        double Ld = L1 - right_offset;
		AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;

        if( !single_rock_tunnel )
        {
			//���Ƶװ�����
			AcGePoint3d basePt = ArxDrawHelper::CaclPt( getPoint(), v1, right_offset, v2, h_offset );
			AcDbObjectId t1 = this->drawDoubleLine( basePt-v2*rock_L2*0.5, basePt+v1*Ld-v2*rock_L2*0.5, wd );
			this->drawMText( basePt + v1 * Ld - v2 * rock_L2 * 0.5, 0, _T( "�װ�����" ), 6 );
            //��������������
            AcDbObjectId t2 = this->drawDoubleLine(basePt+0.5*v2*rock_L2, basePt+v1*Ld+0.5*v2*rock_L2, wd);
            //��������
            AcDbObjectId t3 = this->drawDoubleLine( basePt - v2 * rock_L2 * 0.5, basePt + v2 * rock_L2 * 0.5, wd );
            this->drawMText( basePt + v1 * Ld + v2 * rock_L2 * 0.5, 0, _T( "����������" ), 6 );
        }
		else
		{
			//���Ƶװ�����(���м�λ�û���)
			AcGePoint3d basePt = ArxDrawHelper::CaclPt( getPoint(), v1, right_offset, v2, 0 );
			AcDbObjectId t1 = this->drawDoubleLine( basePt+v2*rock_L2*0.5, basePt+v1*Ld+v2*rock_L2*0.5, wd );
			this->drawMText( basePt + v1 * Ld - v2 * rock_L2 * 0.5, 0, _T( "�װ�����" ), 6 );
		}
    }

    void PlanGraph::drawTunnel()
    {
        //������������е�λ����Ϊ����
        AcGePoint3d basePt = getPoint();
        //���ƻ���
        AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
        AcDbObjectId t1 = this->drawDoubleLine( basePt - v2 * L2 * 0.5, basePt + v1 * L1 - v2 * L2 * 0.5, w );
        //���Ʒ���
        AcDbObjectId t2 = this->drawDoubleLine( basePt + v2 * L2 * 0.5, basePt + v1 * L1 + v2 * L2 * 0.5, w );
        //���ƹ���������
        AcDbObjectId t3 = this->drawDoubleLine( basePt - v2 * L2 * 0.5, basePt + v2 * L2 * 0.5, w );
        this->drawMText( basePt + v1 * L1 - v2 * L2 * 0.5, 0, _T( "�������" ), 6 );
        this->drawMText( basePt + v1 * L1 + v2 * L2 * 0.5, 0, _T( "�������" ), 6 );
    }

    void PlanGraph::drawCoal()
    {
        //����ú��ĳ����
        double Lc = 0, Wc = 0, Hc = 0;
        caclCoalExtent( Lc, Wc, Hc );
        //����ƽ��ͼ��ú������½ǻ�������
        AcGePoint3d basePt = caclCoalBasePoint1();

        //����ú����
        AcDbObjectId coalId = this->drawRect2( basePt, 0, Lc, Wc );
        this->drawAlignedDim( basePt, basePt + AcGeVector3d::kXAxis * Lc, _T(""), 15, false );
        this->drawAlignedDim( basePt, basePt + AcGeVector3d::kYAxis * Wc, _T(""), 15, true );
        //��������
        if( !coalId.isNull() )
        {
            CoalData data;
            data.setDataSource( coalId );
            data.m_name = _T( "����" );
            data.m_thick = coal.thick;
            data.m_angle = coal.dip_angle;
            data.m_width = tech.l1;
            data.m_height = tech.l2;
            data.m_pt = basePt;
            data.update( true );
        }
    }

    HeadGraph::HeadGraph( cbm::Coal& coal, cbm::DesignWorkSurfTechnology& tech ) : Graph( coal, tech )
    {

    }

    void HeadGraph::drawSites()
    {
        double right_offset = p_offset;
        //�۳��Ұ�
        double Ld = L1 - right_offset;

        AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
        AcGePoint3d basePt = ArxDrawHelper::CaclPt( getPoint(), v1, right_offset, v2, -1*(v_offset + 0.5 * thick) );
        //�����곡
        drawSitesOnTunnel( basePt, basePt + v1 * Ld, site_gap, 0, Ls, Ws, 0, false, false );
    }

    void HeadGraph::drawPores()
    {
        double right_offset = p_offset;

        //�۳��Ұ�
        double Ld = L1 - right_offset;

        //������׷�Χ
        double Lp = 0, Wp = 0, Hp = 0;
        caclPoreExtent( Lp, Wp, Hp );

        //���������������ĸ���
        int nx = ArxDrawHelper::DivideNum( Lp, pore_gap, false ) + 1;
        //�����곡�ĸ���
        int nd = ArxDrawHelper::DivideNum( Ld, site_gap, false ) + 1;

        //��1���곡(����������ϵĲ��õ��곡)
        int n1 = ArxDrawHelper::DivideNum( left + right, pore_gap, true );
        //ÿ���곡֮�����׸���(������)
        int dn = ArxDrawHelper::DivideNum( nx, nd, true );
        //��2���곡
        int n2 = dn + dn / 2;

        //������׺��곡�ĸ�����ϵ
        IntArray nums;
        nums.push_back( n1 );
        nums.push_back( n2 );
        ArxDrawHelper::Shuffle( nx - n1 - n2, nd - 2, nums );

        //������׵Ļ���
        AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
        AcGePoint3d poreBasePt = caclPoreBasePoint2();

        //���μ����곡����׵Ĺ���
        AcGePoint3d siteBasePt = ArxDrawHelper::CaclPt( getPoint(), v1, right_offset, v2, -1 * ( v_offset + 0.5 * thick ) );
        int start = 0;
        for( int i = 0; i < nd; i++ )
        {
            AcGePoint3d site_pt = siteBasePt + v1 * i * site_gap + v2 * 0;
            int end = start + nums[i];
            for( int j = start; j < end; j++ )
            {
                AcGePoint3d pore_pt = poreBasePt + v1 * j * pore_gap + v2 * 0;
                AcDbObjectId poreId = this->drawLine( site_pt, pore_pt );
            }
            start = end;
        }
    }

    void HeadGraph::drawRockTunnel()
    {
        double right_offset = p_offset;

        //�۳�ƫ�ƵĲ���
        double Ld = L1 - right_offset;

        //���Ƶװ�����
        AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
        AcGePoint3d basePt = ArxDrawHelper::CaclPt( getPoint(), v1, right_offset, v2, -1 * ( v_offset + 0.5 * thick ) );
        AcDbObjectId t1 = this->drawDoubleLine( basePt - v1 * Hs * 0.5, basePt + v1 * Ld, wd );
    }

    void HeadGraph::drawTunnel()
    {

    }

    void HeadGraph::drawCoal()
    {
        double Lc = 0, Wc = 0, Hc = 0;
        caclCoalExtent( Lc, Wc, Hc );
        AcGePoint3d basePt = caclCoalBasePoint2();

        //����ú��
        AcDbObjectId coalId = this->drawRect2( basePt, 0, Lc, Hc );
    }

    DipGraph::DipGraph( cbm::Coal& coal, cbm::DesignWorkSurfTechnology& tech ) : Graph( coal, tech )
    {
        //����ucs
        AcGeVector3d xAxis( AcGeVector3d::kXAxis ), yAxis( AcGeVector3d::kYAxis );
        xAxis.rotateBy( -1 * angle, AcGeVector3d::kZAxis );
        yAxis.rotateBy( -1 * angle, AcGeVector3d::kZAxis );
        setUcs( AcGePoint3d::kOrigin, xAxis, yAxis );
    }

    void DipGraph::drawSites()
    {

    }

    void DipGraph::drawPores()
    {
        double rock_L2 = d_offset;
		if(single_rock_tunnel) rock_L2 = 0;

        //������׷�Χ
        double Lp = 0, Wp = 0, Hp = 0;
        caclPoreExtent( Lp, Wp, Hp );

        //���������������ĸ���(ֻ�����ڿ��Ʒ�Χ�ڵ�)
        int nx = ArxDrawHelper::DivideNum( 0.5 * Wp, pore_gap, true );

        //������׵Ļ���
        AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
        AcGePoint3d rockBasePt = ArxDrawHelper::CaclPt( getPoint(), v1, -1 * h_offset, v2, -1 * v_offset ); //���������е�
        AcGePoint3d siteBasePt1 = rockBasePt - v1 * rock_L2 * 0.5; // ����������
        AcGePoint3d siteBasePt2 = rockBasePt + v1 * rock_L2 * 0.5; // �װ�����

        if( single_rock_tunnel )
        {
            siteBasePt1 = siteBasePt2;
        }
        //�����곡�Ļ���
        AcGePoint3d poreBasePt1 = ArxDrawHelper::CaclPt( getPoint(), v1, -0.5 * Wp, v2, 0.5 * thick + Hp );
        for( int i = 0; i < nx; i++ )
        {
            AcGePoint3d pore_pt = poreBasePt1 + v1 * i * pore_gap + v2 * 0; // �������Ҽ���
            AcDbObjectId poreId = this->drawLine( siteBasePt1, pore_pt );
        }
        AcGePoint3d poreBasePt2 = ArxDrawHelper::CaclPt( getPoint(), v1, 0.5 * Wp, v2, 0.5 * thick + Hp );
        for( int i = 0; i < nx; i++ )
        {
            AcGePoint3d pore_pt = poreBasePt2 - v1 * i * pore_gap + v2 * 0; // �����������
            AcDbObjectId poreId = this->drawLine( siteBasePt2, pore_pt );
        }
    }

    void DipGraph::drawRockTunnel()
    {
        double rock_L2 = d_offset;
		if(single_rock_tunnel) rock_L2 = 0;

        AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
        AcGePoint3d basePt = ArxDrawHelper::CaclPt( getPoint(), v1, -1 * h_offset, v2, -1 * v_offset );
        if( !single_rock_tunnel )
        {
			AcDbObjectId t3 = this->drawDoubleLine( basePt - v1 * L2 * 0.5, basePt + v1 * L2 * 0.5, hd ); // �װ�����
			//Ϊ�˻����������(����)��ˮƽ��,���⴦����(��ת)
			AcDbObjectId t1 = this->drawRect( basePt + v1 * rock_L2 * 0.5, angle, wd, hd ); // �װ�����
            AcDbObjectId t2 = this->drawRect( basePt - v1 * rock_L2 * 0.5, angle, wd, hd ); // ����������
        }
		else
		{
			AcDbObjectId t3 = this->drawDoubleLine( basePt, basePt - v1 * L2 * 0.5, hd ); // �װ�����
			AcDbObjectId t1 = this->drawRect( basePt + v1 * rock_L2 * 0.5, angle, wd, hd ); // �װ�����
		}
    }

    void DipGraph::drawTunnel()
    {
        AcGePoint3d basePt = getPoint();
        AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
        //Ϊ�˻����������(����)��ˮƽ��,���⴦����(��ת)
        AcDbObjectId t1 = this->drawRect( basePt + v1 * L2 * 0.5, angle, w, h ); // �������
        AcDbObjectId t2 = this->drawRect( basePt - v1 * L2 * 0.5, angle, w, h ); // �������
        AcDbObjectId t3 = this->drawDoubleLine( basePt - v1 * L2 * 0.5, basePt + v1 * L2 * 0.5, h ); // ����������
    }

    void DipGraph::drawCoal()
    {
        double Lc = 0, Wc = 0, Hc = 0;
        caclCoalExtent( Lc, Wc, Hc );
        AcGePoint3d basePt = caclCoalBasePoint3();

        //����ú��
        AcDbObjectId coalId = this->drawRect2( basePt, 0, Wc, Hc );
    }

} // namespace P21