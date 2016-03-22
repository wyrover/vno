#pragma once

#include "Data.h"
#include "Graph.h"

#include <ArxHelper/HelperClass.h>
#include <thrift/gen-cpp/cbm_types.h>

#include <vector>
typedef std::vector<int> IntArray;

namespace P23
{

	// ������������
	class PoreHelper
	{
	public:
		PoreHelper( cbm::Coal& coal, cbm::DesignWorkSurfTechnology& tech );
		void cacl();

	private:
		void drawParallelPores(std::vector<cbm::DesignPore>& pores);

		/** ����ͻ�ͼ�õ��Ĳ���. */
	protected:
		//���򳤶Ⱥ����򳤶�
		double L1, L2;
		//ú���Ⱥ����(����)
		double thick, angle;
		//����������Ŀ�Ⱥ͸߶�
		double w, h;
		//��װ뾶����׵׼�ࡢ���ѹ�糤�ȡ�˳��б��������
		double radius, pore_gap, pore_stubble, pore_angle;
		//˳���������
		int pore_type;

		/** ��������������Ǵ���2������ָ������ȡ������. */
	protected:
		cbm::Coal& coal;                 // ú��ָ��
		cbm::DesignWorkSurfTechnology& tech;     // ��Ƴ�ɼ�������ָ��
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
        Graph( cbm::Coal& coal, cbm::DesignWorkSurfTechnology& tech );
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
        //��װ뾶����׵׼�ࡢ���ѹ�糤�ȡ�˳��б��������
        double radius, pore_gap, pore_stubble, pore_angle;
        //˳���������
        int pore_type;

        //�������ұ߾�(�����ڻ�ͼ����,������ʵ�ʼ���)
        double left_margin, right_margin, top_margin, bottom_margin;

        /** ��������������Ǵ���3������ָ������ȡ������. */
    protected:
        cbm::Coal& coal;                 // ú��ָ��
        cbm::DesignWorkSurfTechnology& tech;     // ��Ƴ�ɼ�������ָ��

    }; // class Graph

    //ƽ��ͼ
    //�Ծ����������Ϊԭ��,���������Ϊx�������򣬴�ֱ���ϵķ���Ϊy��������
    class PlanGraph : public Graph
    {
    public:
        PlanGraph( cbm::Coal& coal, cbm::DesignWorkSurfTechnology& tech );

    protected:
        //�������
        virtual void drawPores();
        //�������
        virtual void drawTunnel();
        //����ú��
        virtual void drawCoal();

    private:
        void drawParallelPores();
        void drawCrossPores();
    }; // class PlanGraph

} // namespace P23