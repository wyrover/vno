#pragma once

#include "Data.h"
#include "Graph.h"

#include <ArxHelper/HelperClass.h>
#include <thrift/gen-cpp/cbm_types.h>

#include <vector>
typedef std::vector<int> IntArray;

namespace P32
{

	// ������������
	class PoreHelper
	{
	public:
		PoreHelper( cbm::Coal& coal, cbm::DesignGoafTechnology& tech, std::vector<cbm::DesignGoafPore>& close_pores );
		void cacl();

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
		//��װ뾶�����ѹ�糤��
		double radius, pore_stubble;
		// �ɿ��������(Ĭ��Ϊ20)
		double goaf_w;

		/** ��������������Ǵ���2������ָ������ȡ������. */
	protected:
		cbm::Coal& coal;                 // ú��ָ��
		cbm::DesignGoafTechnology& tech;     // ��Ƴ�ɼ�������ָ��
		std::vector<cbm::DesignGoafPore>& close_pores; // �տ���Ʋ���
	};

    //����ͼ���ƻ���
    class Graph : public BaseGraph
    {
    protected:
		// �����곡
		virtual void drawSites() = 0;
		//�������
        virtual void drawPores() = 0;
        //�������
        virtual void drawTunnel() = 0;
        //����ú��
        virtual void drawCoal() = 0;

    protected:
        //���캯��
        Graph( cbm::Coal& coal, cbm::DesignGoafTechnology& tech, std::vector<cbm::DesignGoafPore>& close_pores );
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
		//�곡������Լ��곡���
		double Ls, Ws, Hs, site_gap;
        //��װ뾶�����ѹ�糤��
        double radius, pore_stubble;
		// �ɿ��������(Ĭ��Ϊ20)
		double goaf_w;

        //�������ұ߾�(�����ڻ�ͼ����,������ʵ�ʼ���)
        double left_margin, right_margin, top_margin, bottom_margin;

        /** ��������������Ǵ���3������ָ������ȡ������. */
    protected:
        cbm::Coal& coal;                 // ú��ָ��
        cbm::DesignGoafTechnology& tech;     // ��Ƴ�ɼ�������ָ��
		std::vector<cbm::DesignGoafPore>& close_pores; // �տ���Ʋ���
    }; // class Graph

    //ƽ��ͼ
    class PlanGraph : public Graph
    {
    public:
        PlanGraph( cbm::Coal& coal, cbm::DesignGoafTechnology& tech, std::vector<cbm::DesignGoafPore>& close_pores );

    protected:
		//�����곡
		virtual void drawSites();
        //�������
        virtual void drawPores();
        //�������
        virtual void drawTunnel();
        //����ú��
        virtual void drawCoal();

    }; // class PlanGraph

	class HeadGraph : public Graph
	{
	public:
		HeadGraph( cbm::Coal& coal, cbm::DesignGoafTechnology& tech, std::vector<cbm::DesignGoafPore>& close_pores );

	protected:
		//�����곡
		virtual void drawSites();
		//�������
		virtual void drawPores();
		//�������
		virtual void drawTunnel();
		//����ú��
		virtual void drawCoal();
	
	}; // class HeadGraph

} // namespace P32