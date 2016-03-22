#pragma once

#include "Data.h"
#include "Graph.h"

#include <ArxHelper/HelperClass.h>
#include <thrift/gen-cpp/cbm_types.h>

#include <vector>
typedef std::vector<int> IntArray;

namespace P21
{

	// ������������
	class PoreHelper
	{
	public:
		PoreHelper( cbm::Coal& coal, cbm::DesignWorkSurfTechnology& tech );
		void cacl();

	private:
		void assingPores(IntArray& nums, int S, int n, int step);
		void drawPores1(const AcGePoint3dArray& site_pts, const IntArray& nums, const AcGePoint3dArray& pore_pts, int nx, int r1, int r2, int c1, int c2, std::vector<cbm::DesignPore>& pores);

		/** ����ͻ�ͼ�õ��Ĳ���. */
	protected:
		//���򳤶Ⱥ����򳤶�
		double L1, L2;
		//ú���Ⱥ����(����)
		double thick, angle;
		//����������Ŀ�Ⱥ͸߶�
		double w, h;
		//�곡������Լ��곡���
		double Ls, Ws, Hs, site_gap;
		//�װ���Ŀ�Ⱥ͸߶�
		double wd, hd;
		//�������°��
		double left, right, top, bottom;
		//����͹������ˮƽͶӰ���롢����
		double h_offset, v_offset;
		//��װ뾶�ͳ�ɰ뾶
		double radius, pore_gap;
		//ֻ����һ���װ�����
		bool single_rock_tunnel;
		//2������֮���ˮƽ����
		double d_offset;
		//�װ����빤�������۵�ˮƽͶӰ����
		double p_offset;

		/** ��������������Ǵ���2������ָ������ȡ������. */
	protected:
		cbm::Coal& coal;                 // ú��ָ��
		cbm::DesignWorkSurfTechnology& tech;  // ��ƻزɹ�����ָ��
	};

	//����ͼ���ƻ���
    class Graph : public BaseGraph
    {
    protected:
        //�����곡
        virtual void drawSites() = 0;
        //�������
        virtual void drawPores() = 0;
        //���Ƶװ�����
        virtual void drawRockTunnel() = 0;
        //���ƹ������3�����
        virtual void drawTunnel() = 0;
        //����ú��
        virtual void drawCoal() = 0;

    protected:
        //���캯��
        Graph( cbm::Coal& coal, cbm::DesignWorkSurfTechnology& tech );
        //ִ�о���Ļ�ͼ����(����ú�㡢������������곡����ס��װ�����)
        virtual void subDraw();

        /** �������㷽��. */
    protected:
        //����ú��ĳߴ�(��-����, ��-����, ��-���)
        void caclCoalExtent( double& Lc, double& Wc, double& Hc ) const;
        AcGePoint3d caclCoalBasePoint1() const;
        AcGePoint3d caclCoalBasePoint2() const;
        AcGePoint3d caclCoalBasePoint3() const;
        //������׵ĳߴ�(�����)
        void caclPoreExtent( double& Lp, double& Wp, double& Hp ) const;
        AcGePoint3d caclPoreBasePoint1() const;
        AcGePoint3d caclPoreBasePoint2() const;
        //����һ���������ϵ��곡(gap_y������֮��,�����곡���������һ��)
        void drawSitesOnTunnel( const AcGePoint3d& spt, const AcGePoint3d& ept, double gap_x, double gap_y, double w, double h, double angle = 0, bool excludeFirst = true, bool tunning = true );

        /** ����ͻ�ͼ�õ��Ĳ���. */
    protected:
        //���򳤶Ⱥ����򳤶�
        double L1, L2;
        //ú���Ⱥ����(����)
        double thick, angle;
        //����������Ŀ�Ⱥ͸߶�
        double w, h;
        //�곡������Լ��곡���
        double Ls, Ws, Hs, site_gap;
        //�װ���Ŀ�Ⱥ͸߶�
        double wd, hd;
        //�������°��
        double left, right, top, bottom;
        //�����ú���ˮƽͶӰ���롢����
        double h_offset, v_offset;
        //��װ뾶�ͳ�ɰ뾶
        double radius, pore_gap;
        //�������ұ߾�(�����ڻ�ͼ����,������ʵ�ʼ���)
        double left_margin, right_margin, top_margin, bottom_margin;
        //ֻ����һ���װ�����
        bool single_rock_tunnel;
        //2������֮���ˮƽ����
        double d_offset;
        //�װ����빤�������۵�ˮƽͶӰ����
        double p_offset;

        /** ��������������Ǵ���2������ָ������ȡ������. */
    protected:
        cbm::Coal& coal;                 // ú��ָ��
        cbm::DesignWorkSurfTechnology& tech;  // ��ƻزɹ�����ָ��

    }; // class Graph

//ƽ��ͼ(ע:�ڲ��������������Ŀ��ֵ)
//�Թ���������������е�Ϊԭ��,ú��������Ϊx��������,������(����->����)Ϊy��������
    class PlanGraph : public Graph
    {
    public:
        PlanGraph( cbm::Coal& coal, cbm::DesignWorkSurfTechnology& tech );

    protected:
        //�����곡
        virtual void drawSites();
        //�������
        virtual void drawPores();
        //���Ƶװ�����
        virtual void drawRockTunnel();
        //���ƹ������3�����
        virtual void drawTunnel();
        //����ú��
        virtual void drawCoal();
    }; // class PlanGraph

//��������ͼ
//�Թ����������������������ĵ��е�Ϊԭ��,ú��������Ϊx��������,����ĸ߶ȷ���Ϊy��������
    class HeadGraph : public Graph
    {
    public:
        HeadGraph( cbm::Coal& coal, cbm::DesignWorkSurfTechnology& tech );

    protected:
        //�����곡
        virtual void drawSites();
        //�������
        virtual void drawPores();
        //���Ƶװ�����
        virtual void drawRockTunnel();
        //���ƹ������3�����
        virtual void drawTunnel();
        //����ú��
        virtual void drawCoal();
    }; // class HeadGraph

//��������ͼ(�����Զ���ucs�򻯼������)
//�Թ���������������е�Ϊԭ��,ú��������(����->����)Ϊx��������,��������Ϸ���Ϊy��������
    class DipGraph : public Graph
    {
    public:
        DipGraph( cbm::Coal& coal, cbm::DesignWorkSurfTechnology& tech );

    protected:
        //�����곡
        virtual void drawSites();
        //�������
        virtual void drawPores();
        //���Ƶװ�����
        virtual void drawRockTunnel();
        //���ƹ������3�����
        virtual void drawTunnel();
        //����ú��
        virtual void drawCoal();
    }; // class DipGraph

} // namespace P21