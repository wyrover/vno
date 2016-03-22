#pragma once

#include "Data.h"
#include "Graph.h"

#include <ArxHelper/HelperClass.h>
#include <thrift/gen-cpp/cbm_types.h>

#include <vector>
typedef std::vector<int> IntArray;

namespace P12
{

	// ������������
	class PoreHelper
	{
	public:
		PoreHelper(cbm::Coal& coal, cbm::DesignDrillingSurfTechnology& tech);
		void cacl();

	private:
		void drawSidePores(bool bLeftSide, const AcGePoint3d& basePt, const AcGePoint3d& site_pt, int32_t site_id, int site_num, std::vector<cbm::DesignPore>& pores, int& num);
		void drawSectionPores(bool bLeftSide, const AcGePoint3d& basePt, const AcGePoint3d& site_pt, int32_t site_id, int site_num, std::vector<cbm::DesignPore>& pores, int& num);
		void drawVerticalSectionPores(const AcGePoint3d& basePt, const AcGePoint3d& center_pt, const AcGePoint3d& site_pt, int32_t site_id, int site_num, std::vector<cbm::DesignPore>& pores, int& num);

		/** ����ͻ�ͼ�õ��Ĳ���. */
	protected:
		//���򳤶Ⱥ����򳤶�
		double L1, L2;
		//ú���Ⱥ����(����)
		double thick, angle;
		//����������Ŀ�Ⱥ͸߶�
		double w, h;
		//�������°��
		double left, right, top, bottom;
		//��װ뾶����׵׼�ࡢ��׳�ǰ���롢�����������
		double radius, pore_gap, L_stripe, leading;

		/** ��������������Ǵ���2������ָ������ȡ������. */
	protected:
		cbm::Coal& coal;                 // ú��ָ��
		cbm::DesignDrillingSurfTechnology& tech;     // ��Ƴ�ɼ�������ָ��
	};

    //����ͼ���ƻ���
    class Graph : public BaseGraph
    {
    protected:
        //�������
        virtual void drawPores() = 0;
        //�������
        virtual void drawTunnel() = 0;
        //����ú��
        virtual void drawCoal() = 0;

    protected:
        //���캯��
        Graph( cbm::Coal& coal, cbm::DesignDrillingSurfTechnology& tech );
        //ִ�о���Ļ�ͼ����(����ú�㡢������������곡����׵ȵ�)
        virtual void subDraw();

        /** �������㷽��. */
    protected:
        //����ú��ĳߴ�(��-����, ��-����, ��-���)
        void caclCoalExtent( double& Lc, double& Wc, double& Hc ) const;

        /** ����ͻ�ͼ�õ��Ĳ���. */
    protected:
        //���򳤶Ⱥ����򳤶�
        double L1, L2;
        //ú���Ⱥ����(����)
        double thick, angle;
        //����������Ŀ�Ⱥ͸߶�
        double w, h;
        //�������°��
        double left, right, top, bottom;
        //��װ뾶����׵׼�ࡢ��׳�ǰ���롢�����������
        double radius, pore_gap, L_stripe, leading;

        //�������ұ߾�(�����ڻ�ͼ����,������ʵ�ʼ���)
        double left_margin, right_margin, top_margin, bottom_margin;

        /** ��������������Ǵ���3������ָ������ȡ������. */
    protected:
        cbm::Coal& coal;                 // ú��ָ��
        cbm::DesignDrillingSurfTechnology& tech;     // ��Ƴ�ɼ�������ָ��

    }; // class Graph

    //ƽ��ͼ
    //�Ծ����������Ϊԭ��,���������Ϊx�������򣬴�ֱ���ϵķ���Ϊy��������
    class PlanGraph : public Graph
    {
    public:
        PlanGraph( cbm::Coal& coal, cbm::DesignDrillingSurfTechnology& tech );

    protected:
        //�������
        virtual void drawPores();
        //�������
        virtual void drawTunnel();
        //����ú��
        virtual void drawCoal();

    }; // class PlanGraph

} // namespace P12