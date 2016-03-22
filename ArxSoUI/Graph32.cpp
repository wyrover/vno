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

		//���򳤶Ⱥ����򳤶�
		L1 = tech.l1, L2 = tech.l2;
		//ú���Ⱥ����(����)
		thick = coal.thick, angle = DegToRad( coal.dip_angle );
		//����������Ŀ�Ⱥ͸߶�
		w = tech.w, h = tech.h;
		//��װ뾶(�׾��ĵ�λ��mm)
		radius = tech.dp * 0.5 * 0.001;
		//���ѹ�糤��
		pore_stubble = tech.pore_stubble;
		//�곡���ȡ���Ⱥ͸߶�
		Ls = tech.ls, Ws = tech.ws, Hs = tech.hs;
		//�곡���
		site_gap = tech.gs;
	}

	void PoreHelper::cacl()
	{
		// ɾ�����е��곡�����
		GraphHelper::DeleteAllSiteAndPore(tech.design_technology_id);

		AcGePoint3d basePt = AcGePoint3d::kOrigin;
		AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis, v3 = AcGeVector3d::kZAxis;

		// ��¼���е����
		std::vector<cbm::DesignPore> pores;

		// �곡����󳤶�
		double Ld = L1 + goaf_w - (site_gap + pore_stubble);
		if(Ld > L1) Ld = L1;

		// �����곡����
		AcGePoint3dArray pts;
		ArxDrawHelper::Divide( basePt + v1*Ld, basePt, site_gap, 0, pts, false, false, false );
		// ����
		pts.reverse();

		bool ret = true;
		// ��¼�곡�����ݿ�id
		IntArray site_ids;

		// �����곡
		for( int i = 0; i < pts.length(); i++ )
		{
			cbm::DesignSite site;
			GraphHelper::CreateSite(site, i+1, pts[i], tech.design_technology_id);
			// �ύ�����ݿ�
			int32_t site_id = SQLClientHelper::AddDesignSite(site);
			if(site_id <= 0) 
			{
				acutPrintf(_T("\n����곡�����ݿ�ʧ��!!!"));
				ret = false;
				break;
			}
			site_ids.push_back(site_id);

			// ����ÿ���곡�����
			for(int j=0;j<close_pores.size();j++)
			{
				AcGePoint3d pt = pts[i];
				double Lp = site_gap + pore_stubble, Wp = close_pores[j].h_offset, Hp = close_pores[j].v_offset;
				// ��ע���
				CString poreName;
				poreName.Format(_T("%d-%s"), i+1, C2W(close_pores[j].name));

				cbm::DesignPore pore;
				GraphHelper::CreatePore(pore, poreName, pt, pt + v1*Lp - v2*Wp + v3*Hp, site_id);

				// ��¼���
				pores.push_back(pore);
			}
		}
		if(!ret)
		{
			// ɾ�����е��곡(���ݿ���Զ�ɾ�����������)
			SQLClientHelper::DeleteMoreDesignSite(site_ids);
		}
		else
		{
			// ��ӵ����ݿ�
			SQLClientHelper::AddMoreDesignPore(pores);

			acutPrintf(_T("��׸���:%d"), pores.size());
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

        //���򳤶Ⱥ����򳤶�
        L1 = tech.l1, L2 = tech.l2;
        //ú���Ⱥ����(����)
        thick = coal.thick, angle = DegToRad( coal.dip_angle );
        //����������Ŀ�Ⱥ͸߶�
        w = tech.w, h = tech.h;
        //��װ뾶(�׾��ĵ�λ��mm)
        radius = tech.dp * 0.5 * 0.001;
        //���ѹ�糤��
        pore_stubble = tech.pore_stubble;
		//�곡���ȡ���Ⱥ͸߶�
		Ls = tech.ls, Ws = tech.ws, Hs = tech.hs;
		//�곡���
		site_gap = tech.gs;
    }

    void Graph::subDraw()
    {
        //����ͼ��
        drawCoal();
        drawTunnel();
        drawPores();
		drawSites();
    }

    void Graph::caclCoalExtent( double& Lc, double& Wc, double& Hc ) const
    {
        //������(���򳤶�L2+�����������Ʒ�Χleft+ƫ��)
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
		
		// �곡����󳤶�
		double Ld = L1 + goaf_w - (site_gap + pore_stubble);
		if(Ld > L1) Ld = L1;

		// ��������
		AcGePoint3d basePt = getPoint() + v2 * L2 * 0.5;

		// �����곡����
		AcGePoint3dArray pts;
		ArxDrawHelper::Divide( basePt + v1*Ld, basePt, site_gap, 0, pts, false, false, false );
		// ����
		pts.reverse();

		// �곡����ױ�ע����
		int site_dim_count = 0, pore_dim_count = 0;

		// ��¼���id
		AcDbObjectIdArray objIds;
		// �����곡
		for( int i = 0; i < pts.length(); i++ )
		{
			acutPrintf(_T("\n�곡%d  x:%.1f"), i+1, pts[i].x);
			AcDbObjectId siteId = this->drawRect( pts[i], 0, Ls, Ws );

			// ��ע�곡
			CString siteName;
			siteName.Format(_T("%d#"), i+1);
			this->drawMText(pts[i]+v2*w*2, 0, siteName, 6);

			if(site_dim_count == 0)
			{
				CString text;
				text.Format(_T("%dm"), (int)site_gap);
				//�곡���
				this->drawAlignedDim(pts[i], pts[i]+v1*site_gap, text, 12, true);

				//ѹ��
				text.Format(_T("%dm"), (int)pore_stubble);
				this->drawAlignedDim(pts[i]+v1*site_gap, pts[i]+v1*site_gap+v1*pore_stubble, text, 12, true);

				site_dim_count++;
			}

			// ����ÿ���곡�����
			for(int j=0;j<close_pores.size();j++)
			{
				AcGePoint3d pt = pts[i];
				double Lp = site_gap + pore_stubble, Wp = close_pores[j].h_offset;

				if(j == close_pores.size()-1)
				{
					// �����տ׷ֽ���
					this->drawLine(pt + v1*Lp - v2*w*0.5,  pt + v1*Lp - v2*Wp);
				}

				AcDbObjectId objId = this->drawLine(pt, pt + v1*Lp - v2*Wp);
				objIds.append(objId);

				// ��ע���
				CString poreName;
				poreName.Format(_T("%d-%s"), i+1, C2W(close_pores[j].name));
				this->drawMText(pt + v1*Lp - v2*Wp, 0, poreName, 6, AcDbMText::kMiddleRight);

				if(pore_dim_count < close_pores.size())
				{
					CString text;
					text.Format(_T("%dm"), (int)Wp);
					//�곡���
					this->drawAlignedDim( pt + v1*Lp - v2*w*0.5,  pt + v1*Lp - v2*Wp, text, 12+pore_dim_count*6, true,DIM_STYLE_NAME3);
					pore_dim_count++;
				}
			}
		}
		// ���ֱ������Ϊ����
		ArxDrawHelper::SetLineType( objIds, _T( "JIS_02_0.7" ) );
	}

    void PlanGraph::drawPores()
    {
    }

    void PlanGraph::drawTunnel()
    {
        //������е�λ����Ϊ����
        AcGePoint3d basePt = getPoint();
        //���ƹ�����
        AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
        AcDbObjectId t1 = this->drawDoubleLine( basePt - v2 * L2 * 0.5, basePt + v1 * L1 - v2 * L2 * 0.5, w );
        //���Ʒ���
        AcDbObjectId t2 = this->drawDoubleLine( basePt + v2 * L2 * 0.5, basePt + v1 * L1 + v2 * L2 * 0.5, w );
        //��������
        AcDbObjectId t3 = this->drawDoubleLine( basePt + v1 * L1 - v2 * L2 * 0.5, basePt + v1*L1 + v2 * L2 * 0.5, w );

		// ���Ʋɿ���
		AcGePoint3dArray pts;
		double goaf_h = L2 + w;
		this->drawRect2(basePt + v1 * (L1+0.5*w) - v2 * (L2+w) * 0.5, 0, goaf_w, goaf_h);
		ArxDrawHelper::BuildRect2(basePt + v1 * (L1+0.5*w) - v2 * (L2+w) * 0.5, 0, goaf_w, goaf_h, pts);
		this->drawPolygonHatch(pts, _T( "GRAVEL" ), 1.0);

		this->drawMText( basePt + v1 * L1*0.5 - v2 * (L2 * 0.5+2*w), 0, _T( "����" ), 6 );
		this->drawMText( basePt + v1 * L1*0.5 + v2 * (L2 * 0.5+2*w), 0, _T( "�ط���" ), 6 );
		this->drawMText( basePt + v1 * (L1 - 2*w), 0, _T( "������" ), 6, AcDbMText::kMiddleRight );
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
						poreName.Format(_T("%s��%s"), name_map[i], name_map[j]);
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

		// �곡����󳤶�
		double Ld = L1 + goaf_w - (site_gap + pore_stubble);
		if(Ld > L1) Ld = L1;

		// ��������
		AcGePoint3d basePt = getPoint();

		// �곡����ױ�ע����
		int site_dim_count = 0, pore_dim_count = 0;

		// �����곡����
		AcGePoint3dArray pts;
		ArxDrawHelper::Divide( basePt + v1*Ld, basePt, site_gap, 0, pts, false, false, false );
		// ����
		pts.reverse();

		// ��¼���id
		AcDbObjectIdArray objIds;
		// �����곡
		for( int i = 0; i < pts.length(); i++ )
		{
			acutPrintf(_T("\n�곡%d  x:%.1f"), i+1, pts[i].x);
			AcDbObjectId siteId = this->drawRect( pts[i], 0, Ls, Ws );

			// ��ע�곡
			CString siteName;
			siteName.Format(_T("%d#"), i+1);
			this->drawMText(pts[i]-v2*w*2, 0, siteName, 6);

			if(site_dim_count == 0)
			{
				CString text;
				text.Format(_T("%dm"), (int)site_gap);
				//�곡���
				this->drawAlignedDim(pts[i], pts[i]+v1*site_gap, text, 12, false);

				//ѹ��
				text.Format(_T("%dm"), (int)pore_stubble);
				this->drawAlignedDim(pts[i]+v1*site_gap, pts[i]+v1*site_gap+v1*pore_stubble, text, 12, false);
				site_dim_count++;
			}

			NameBuilder builder(close_pores, i+1);
			// ����ÿ���곡�����
			for(int j=0;j<close_pores.size();j++)
			{
				AcGePoint3d pt = pts[i];
				double Lp = site_gap + pore_stubble, Wp = close_pores[j].v_offset;
				if(j == close_pores.size()-1)
				{
					// �����տ׷ֽ���
					this->drawLine(pt + v1*Lp + v2*h*0.5,  pt + v1*Lp + v2*Wp);
				}

				CString poreName;
				if(!builder.getName(poreName, j)) continue;

				AcDbObjectId objId = this->drawLine(pt, pt + v1*Lp + v2*Wp);
				objIds.append(objId);

				// ��ע���
				//CString poreName;
				//poreName.Format(_T("%d-%s"), i+1, C2W(close_pores[j].name));
				AcGeVector3d v = v1*Lp + v2*Wp;
				double angle = v.angleTo(AcGeVector3d::kXAxis, -AcGeVector3d::kZAxis);
				this->drawMText(pt + v1*Lp*0.5 + v2*Wp*0.5, angle, poreName, 6, AcDbMText::kBottomCenter);

				if(pore_dim_count < close_pores.size())
				{
					CString text;
					text.Format(_T("%dm"), (int)Wp);
					//�곡���
					this->drawAlignedDim( pt + v1*Lp + v2*w*0.5,  pt + v1*Lp + v2*Wp, text, 12+pore_dim_count*6, true, DIM_STYLE_NAME3);
					pore_dim_count++;
				}
			}
		}
		// ���ֱ������Ϊ����
		ArxDrawHelper::SetLineType( objIds, _T( "JIS_02_0.7" ) );
	}

	void HeadGraph::drawPores()
	{
	}

	void HeadGraph::drawTunnel()
	{
		//������е�λ����Ϊ����
		AcGePoint3d basePt = getPoint();
		AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
		//���Ʒ���
		AcDbObjectId t2 = this->drawDoubleLine( basePt, basePt + v1 * L1, h );

		this->drawMText( basePt + v1 * L1*0.5 + v2 * 2*h, 0, _T( "�ط���" ), 6 );
	}

	void HeadGraph::drawCoal()
	{
	}

} // namespace P32