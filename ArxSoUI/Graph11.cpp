#include "StdAfx.h"
#include "Graph11.h"

#include <ArxHelper/HelperClass.h>
#include "CbmClientHelper.h"
#include "SQLClientHelper.h"

#include <numeric>
#include <algorithm>
#include <iterator>
#include <cmath>

#include "GraphHelper.h"

namespace P11
{

	PoreHelper::PoreHelper(cbm::Coal& _coal, cbm::DesignDrillingSurfTechnology& _tech)
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
	}

	/*
	����˵��:
		site_pts   - ����ϵ��곡����(�������ҵ�˳�����)
		pore_nums  - ÿ���곡���Ƶ��������������(�����������й�,����ͷ����Ӧ��������, �������Ӧ��������)
		pore_pts   - ú����Ʒ�Χ�ڵ��������(��1ά�����ʾ��������, ����֮��ļ�������׼��)
		nx         - ���ε�����(��pore_pts�������ʹ��)
		r1, r2     - ������Ƶ��������
		c1, c2     - ������Ƶ��������
		pores      - ��¼�½������
	*/
	//���ƻ������
	void PoreHelper::drawPores1(const AcGePoint3dArray& site_pts, const IntArray& pore_nums, const AcGePoint3dArray& pore_pts, int nx, int r1, int r2, int c1, int c2, std::vector<cbm::DesignPore>& pores)
	{
		// (1)������������
		int n = site_pts.length();
		// ��ױ��
		int num = 1;
		for(int i=n-1;i>=0;i--)
		{
			// �곡���
			int site_num = n - i;
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
				break;
			}

			// �곡��������ʼλ��
			r2 -= pore_nums[i];
			acutPrintf(_T("\n����---�곡%d����:%d~%d, ��:%d~%d"), n-i, r1, r2, c1, c2);
			// �������
			for(int j=r1-1;j>=r2;j--)
			{
				for(int k=c1-1;k>=c2;k--)
				{
					// ��Ź���: ������-�곡���-��ױ��
					CString name;
					name.Format(_T("%d-%d-%d"), 1, site_num, num++);
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

	//���Ʒ������
	void PoreHelper::drawPores2(const AcGePoint3dArray& site_pts, const IntArray& pore_nums, const AcGePoint3dArray& pore_pts, int nx, int r1, int r2, int c1, int c2, std::vector<cbm::DesignPore>& pores)
	{
		// (1)������������
		int n = site_pts.length();
		// ��ױ��
		int num = 1;
		for(int i=n-1;i>=0;i--)
		{
			// �곡���
			int site_num = n - i;
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
				break;
			}

			// �곡��������ʼλ��
			r2 -= pore_nums[i];
			acutPrintf(_T("\n����---�곡%d����:%d~%d, ��:%d~%d"), n-i, r1, r2, c1, c2);
			// �������
			for(int j=r1-1;j>=r2;j--)
			{
				for(int k=c1;k<c2;k++)
				{
					// ��Ź���: ������-�곡���-��ױ��
					CString name;
					name.Format(_T("%d-%d-%d"), 2, site_num, num++);
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

	//���ƹ��������
	void PoreHelper::drawPores3(const AcGePoint3dArray& site_pts, const IntArray& pore_nums, const AcGePoint3dArray& pore_pts, int nx, int r1, int r2, int c1, int c2, std::vector<cbm::DesignPore>& pores)
	{
		// (1)������������
		int n = site_pts.length();
		// ��ױ��
		int num = 1;
		for(int i=n-1;i>=0;i--)
		{
			// �곡���
			int site_num = n - i;
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
				break;
			}

			// �곡��������ʼλ��
			c2 -= pore_nums[i];
			acutPrintf(_T("\n����������---�곡%d����:%d~%d, ��:%d~%d"), n-i, r1, r2, c1, c2);
			// �������
			for(int k=c1-1;k>=c2;k--)
			{
				for(int j=r1-1;j>=r2;j--)
				{
					// ��Ź���: ������-�곡���-��ױ��
					CString name;
					name.Format(_T("%d-%d-%d"), 3, site_num, num++);
					// �������
					AcGePoint3d pore_pt = pore_pts[j*nx+k];

					// �½����
					cbm::DesignPore pore;
					GraphHelper::CreatePore(pore, name, site_pt, pore_pt, site_id);

					// ��¼�½�����׶���
					pores.push_back(pore);
				}
			}
			c1 = c2;
		}
	}

	/*
	 �����곡���Ƶ��������������
	 nums -  ��¼�곡��Ӧ����׸���
	 S  -  ������������
	 n  -  �곡����
	 firstNum - ��һ���곡���������
	 step - ÿ���곡֮�����׸���
	 */ 
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
		// ɾ�����е��곡�����
		GraphHelper::DeleteAllSiteAndPore(tech.design_technology_id);

		// ������������е���Ϊԭ��
		AcGePoint3d orig(AcGePoint3d::kOrigin);

		// ��׿��Ʒ�Χ
		double Lc = left + L1, Wc = L2 + top + bottom;
		// ���Ʒ�Χ���½�(ú�㶥��)������(��׵�ԭ��)
		AcGeVector3d v1(AcGeVector3d::kXAxis), v2(AcGeVector3d::kYAxis), v3(AcGeVector3d::kZAxis);
		AcGePoint3d pore_orig = orig - v1*left - v2*(0.5*L2+left) + v3*top;
		
		//�۳��Ұ�
		double Ld = L1 - right;

		// ��������������е��������
		// �������е��տ׶���ͬһ��ˮƽ����
		AcGePoint3dArray pore_pts;
		ArxDrawHelper::MakeGridWithHole( pore_orig, Lc, Wc, pore_gap, pore_gap, 0, Lc, 0, Wc, pore_pts, true );

		//�������������(��)������(��)�ĸ���(�л���)
		int nx = ArxDrawHelper::DivideNum( Lc, pore_gap, false ) + 1;
		int ny = ArxDrawHelper::DivideNum( Wc, pore_gap, false ) + 1;
		//��������(��)������곡��(�л���)
		int mx = ArxDrawHelper::DivideNum( Ld, site_gap, false ) + 1;
		//��������(��)������곡��(�л���)
		int my = ArxDrawHelper::DivideNum( L2, site_gap, false ) + 1;
		//�������ﷶΧ�ڵ������(�л���)
		int d1 = ArxDrawHelper::DivideNum( left + right, pore_gap, false ) + 1;
		//ÿ���곡֮�����׸���
		int d2 = ArxDrawHelper::DivideNum( site_gap, pore_gap, false ) + 1;

		acutPrintf(_T("\n����������:%d  �������:%d  ��׵��ܸ���:%d"), nx, ny, pore_pts.length());
		acutPrintf(_T("\n�곡�������:%d  �������:%d, ���ﷶΧ��׸���:%d  �곡֮��ĸ���:%d"), mx, my, d1, d2);
		// �����곡������(CaclSitesOnTunnel�����ĺ�3������Ŀǰû���õ�!!!)
		// (0)������װ�������е�����
		AcGePoint3d site_orig = orig + v1*right + v2*h_offset - v3*v_offset;
		// (1)���������곡����
		AcGePoint3dArray site_pts1;
		GraphHelper::CaclSitesOnTunnel( site_pts1, site_orig - v2 * L2 * 0.5, site_orig + v1 * Ld - v2 * 0.5 * L2, site_gap, -0.5 * ( Ws + wd ), Ls, Ws, 0 );
		// (2)���������곡����
		AcGePoint3dArray site_pts2;
		GraphHelper::CaclSitesOnTunnel( site_pts2, site_orig + v2 * L2 * 0.5, site_orig + v1 * Ld + v2 * L2 * 0.5, site_gap, -0.5 * ( Ws + wd ), Ls, Ws, 0 );
		// (3)���㹤����װ�������곡����
		AcGePoint3dArray site_pts3;
		GraphHelper::CaclSitesOnTunnel( site_pts3, site_orig - v2 * L2 * 0.5, site_orig + v2 * L2 * 0.5, site_gap, 0.5 * ( Ws + wd ), Ls, Ws, -PI * 0.5, false );

		// ˮƽ�������ҳ�Ϊ"��", ��ֱ���µ��ϳ�Ϊ"��"(�봫ͳ�����и����෴)
		// ���乤����װ�������Ƶ����(ÿ���곡����xx��,�����ǹ̶���)
		IntArray pore_nums3;
		assingPores(pore_nums3, ny-d1, site_pts3.length(), d2);
		pore_nums3[0] += d1;

		// ���������Ƶ����(ÿ���곡����xx��)
		IntArray pore_nums1;
		assingPores(pore_nums1, nx-d1, site_pts1.length(), d2);
		// ���������Ƶ����
		IntArray pore_nums2;
		std::copy(pore_nums1.begin(), pore_nums1.end(), std::back_inserter(pore_nums2));

		// ��¼���е����
		std::vector<cbm::DesignPore> pores;

		// (1)������������
		drawPores1(site_pts1, pore_nums1, pore_pts, ny, nx, nx, d1, 0, pores);
		// (2)������������
		drawPores2(site_pts2, pore_nums2, pore_pts, ny, nx, nx, ny-d1, ny, pores);
		// (3)���������װ����������
		drawPores3(site_pts3, pore_nums3, pore_pts, ny, d1, 0, ny, ny, pores);

		// ��ӵ����ݿ�
		SQLClientHelper::AddMoreDesignPore(pores);
	}

    Graph::Graph( cbm::Coal& _coal, cbm::DesignDrillingSurfTechnology& _tech )
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
        //int start = excludeFirst ? 1 : 0; // �Ƿ���Ƶ�һ���곡
        for( int i = 0; i < pts.length(); i++ )
        {
            AcDbObjectId siteId = this->drawRect( pts[i], angle, w, h );
        }
    }

    PlanGraph::PlanGraph( cbm::Coal& coal, cbm::DesignDrillingSurfTechnology& tech ) : Graph( coal, tech )
    {
    }

    void PlanGraph::drawSites()
    {
        //�۳��Ұ�
        double Ld = L1 - right;

        AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
        AcGePoint3d basePt = ArxDrawHelper::CaclPt( getPoint(), v1, right, v2, h_offset );
        //���ƻ����곡
        drawSitesOnTunnel( basePt - v2 * L2 * 0.5, basePt + v1 * Ld - v2 * 0.5 * L2, site_gap, -0.5 * ( Ws + wd ), Ls, Ws, 0 );
		//���ƹ����������곡
        drawSitesOnTunnel( basePt - v2 * L2 * 0.5, basePt + v2 * L2 * 0.5, site_gap, 0.5 * ( Ws + wd ), Ls, Ws, -PI * 0.5, false );
		//���Ʒ����곡
        drawSitesOnTunnel( basePt + v2 * L2 * 0.5, basePt + v1 * Ld + v2 * L2 * 0.5, site_gap, -0.5 * ( Ws + wd ), Ls, Ws, 0 );
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
        ArxDrawHelper::MakeGridWithHole( basePt, Lp, Wp, pore_gap, pore_gap, left + right, 0, left + right, left + right, pts, true );
        for( int i = 0; i < pts.length(); i++ )
        {
            AcDbObjectId poreId = this->drawCircle( pts[i], radius );
        }
    }

    void PlanGraph::drawRockTunnel()
    {
        //�۳�ƫ�ƵĲ���
        double Ld = L1 - right;

        //���Ƶװ�����
        AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
        AcGePoint3d basePt = ArxDrawHelper::CaclPt( getPoint(), v1, right, v2, h_offset );
        AcDbObjectId t1 = this->drawDoubleLine( basePt - v2 * L2 * 0.5, basePt + v1 * Ld - v2 * L2 * 0.5, wd );
        //��������������
        AcDbObjectId t2 = this->drawDoubleLine( basePt + 0.5 * v2 * L2, basePt + v1 * Ld + 0.5 * v2 * L2, wd );
        //��������
        AcDbObjectId t3 = this->drawDoubleLine( basePt - v2 * L2 * 0.5, basePt + v2 * L2 * 0.5, wd );
        this->drawMText( basePt + v1 * Ld - v2 * L2 * 0.5, 0, _T( "�װ�����" ), 6 );
        this->drawMText( basePt + v1 * Ld + v2 * L2 * 0.5, 0, _T( "����������" ), 6 );
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
        this->drawAlignedDim( basePt, basePt + AcGeVector3d::kXAxis * Lc, _T(""), 50, false );
        this->drawAlignedDim( basePt, basePt + AcGeVector3d::kYAxis * Wc, _T(""), 30, true );
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

    HeadGraph::HeadGraph( cbm::Coal& coal, cbm::DesignDrillingSurfTechnology& tech ) : Graph( coal, tech )
    {

    }

    void HeadGraph::drawSites()
    {
        //�۳��Ұ�
        double Ld = L1 - right;

        AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
        AcGePoint3d basePt = ArxDrawHelper::CaclPt( getPoint(), v1, right, v2, -1 * ( v_offset + 0.5 * thick ) );
        //�����곡
        drawSitesOnTunnel( basePt, basePt + v1 * Ld, site_gap, 0, Ls, Ws, 0, false, false );
    }

    void HeadGraph::drawPores()
    {
        //�۳��Ұ�
        double Ld = L1 - right;

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
        AcGePoint3d siteBasePt = ArxDrawHelper::CaclPt( getPoint(), v1, right, v2, -1 * ( v_offset + 0.5 * thick ) );
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
        //�۳�ƫ�ƵĲ���
        double Ld = L1 - right;

        //���Ƶװ�����
        AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
        AcGePoint3d basePt = ArxDrawHelper::CaclPt( getPoint(), v1, right, v2, -1 * ( v_offset + 0.5 * thick ) );
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

    DipGraph::DipGraph( cbm::Coal& coal, cbm::DesignDrillingSurfTechnology& tech ) : Graph( coal, tech )
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
        //������׷�Χ
        double Lp = 0, Wp = 0, Hp = 0;
        caclPoreExtent( Lp, Wp, Hp );

        //���������������ĸ���(ֻ�����ڿ��Ʒ�Χ�ڵ�)
        int nx = ArxDrawHelper::DivideNum( left + right, pore_gap, true );

        //������׵Ļ���
        AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;

        //�����곡�Ļ���
        AcGePoint3d rockBasePt = ArxDrawHelper::CaclPt( getPoint(), v1, -1 * h_offset, v2, -1 * v_offset ); //���������е�

        AcGePoint3d poreBasePt1 = ArxDrawHelper::CaclPt( getPoint(), v1, -0.5 * Wp, v2, 0.5 * thick + Hp );
        AcGePoint3d siteBasePt1 = rockBasePt - v1 * L2 * 0.5; // ����������
        for( int i = 0; i < nx; i++ )
        {
            AcGePoint3d pore_pt = poreBasePt1 + v1 * i * pore_gap + v2 * 0; // �������Ҽ���
            AcDbObjectId poreId = this->drawLine( siteBasePt1, pore_pt );
        }

        AcGePoint3d poreBasePt2 = ArxDrawHelper::CaclPt( getPoint(), v1, 0.5 * Wp, v2, 0.5 * thick + Hp );
        AcGePoint3d siteBasePt2 = rockBasePt + v1 * L2 * 0.5; // �װ�����
        for( int i = 0; i < nx; i++ )
        {
            AcGePoint3d pore_pt = poreBasePt2 - v1 * i * pore_gap + v2 * 0; // �����������
            AcDbObjectId poreId = this->drawLine( siteBasePt2, pore_pt );
        }
    }

    void DipGraph::drawRockTunnel()
    {
        AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
        AcGePoint3d basePt = ArxDrawHelper::CaclPt( getPoint(), v1, -1 * h_offset, v2, -1 * v_offset );
        AcDbObjectId t3 = this->drawDoubleLine( basePt - v1 * L2 * 0.5, basePt + v1 * L2 * 0.5, hd ); // �װ�����
        //Ϊ�˻����������(����)��ˮƽ��,���⴦����(��ת)
        AcDbObjectId t2 = this->drawRect( basePt - v1 * L2 * 0.5, angle, wd, hd ); // ����������
        AcDbObjectId t1 = this->drawRect( basePt + v1 * L2 * 0.5, angle, wd, hd ); // �װ�����
    }

    void DipGraph::drawTunnel()
    {
        AcGePoint3d basePt = getPoint();
        AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
        //Ϊ�˻����������(����)��ˮƽ��,���⴦����(��ת)
        AcDbObjectId t1 = this->drawRect( basePt + v1 * L2 * 0.5, angle, w, h ); // �������
        AcDbObjectId t2 = this->drawRect( basePt - v1 * L2 * 0.5, angle, w, h ); // �������
        AcDbObjectId t3 = this->drawDoubleLine( basePt-v1*L2*0.5, basePt+v1*L2*0.5, h ); //����������
    }

    void DipGraph::drawCoal()
    {
        double Lc = 0, Wc = 0, Hc = 0;
        caclCoalExtent( Lc, Wc, Hc );
        AcGePoint3d basePt = caclCoalBasePoint3();

        //����ú��
        AcDbObjectId coalId = this->drawRect2( basePt, 0, Wc, Hc );
    }

} // namespace P11