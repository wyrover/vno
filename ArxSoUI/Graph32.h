#pragma once

#include "Data.h"
#include "Graph.h"

#include <ArxHelper/HelperClass.h>
#include <thrift/gen-cpp/cbm_types.h>

#include <vector>
typedef std::vector<int> IntArray;

namespace P32
{

	// 钻孔坐标计算类
	class PoreHelper
	{
	public:
		PoreHelper( cbm::Coal& coal, cbm::DesignGoafTechnology& tech, std::vector<cbm::DesignGoafPore>& close_pores );
		void cacl();

		/** 计算和绘图用到的参数. */
	protected:
		//倾向长度和走向长度
		double L1, L2;
		//煤层厚度和倾角(弧度)
		double thick, angle;
		//工作面巷道的宽度和高度
		double w, h;
		//钻场长宽高以及钻场间距
		double Ls, Ws, Hs, site_gap;
		//钻孔半径、钻孔压茬长度
		double radius, pore_stubble;
		// 采空区的深度(默认为20)
		double goaf_w;

		/** 上述计算参数都是从这2个对象指针中提取出来的. */
	protected:
		cbm::Coal& coal;                 // 煤层指针
		cbm::DesignGoafTechnology& tech;     // 设计抽采技术参数指针
		std::vector<cbm::DesignGoafPore>& close_pores; // 终孔设计参数
	};

    //剖面图绘制基类
    class Graph : public BaseGraph
    {
    protected:
		// 绘制钻场
		virtual void drawSites() = 0;
		//绘制钻孔
        virtual void drawPores() = 0;
        //绘制巷道
        virtual void drawTunnel() = 0;
        //绘制煤层
        virtual void drawCoal() = 0;

    protected:
        //构造函数
        Graph( cbm::Coal& coal, cbm::DesignGoafTechnology& tech, std::vector<cbm::DesignGoafPore>& close_pores );
        //执行具体的绘图工作(绘制煤层、工作面巷道、钻场、钻孔等等)
        virtual void subDraw();

        /** 辅助计算方法. */
    protected:
        //计算煤层的尺寸(长-倾向, 宽-走向, 高-厚度)
        void caclCoalExtent( double& Lc, double& Wc, double& Hc ) const;

        /** 计算和绘图用到的参数. */
    protected:
        //倾向长度和走向长度
        double L1, L2;
        //煤层厚度和倾角(弧度)
        double thick, angle;
        //工作面巷道的宽度和高度
        double w, h;
		//钻场长宽高以及钻场间距
		double Ls, Ws, Hs, site_gap;
        //钻孔半径、钻孔压茬长度
        double radius, pore_stubble;
		// 采空区的深度(默认为20)
		double goaf_w;

        //上下左右边距(仅用于绘图美观,不参与实际计算)
        double left_margin, right_margin, top_margin, bottom_margin;

        /** 上述计算参数都是从这3个对象指针中提取出来的. */
    protected:
        cbm::Coal& coal;                 // 煤层指针
        cbm::DesignGoafTechnology& tech;     // 设计抽采技术参数指针
		std::vector<cbm::DesignGoafPore>& close_pores; // 终孔设计参数
    }; // class Graph

    //平面图
    class PlanGraph : public Graph
    {
    public:
        PlanGraph( cbm::Coal& coal, cbm::DesignGoafTechnology& tech, std::vector<cbm::DesignGoafPore>& close_pores );

    protected:
		//绘制钻场
		virtual void drawSites();
        //绘制钻孔
        virtual void drawPores();
        //绘制巷道
        virtual void drawTunnel();
        //绘制煤层
        virtual void drawCoal();

    }; // class PlanGraph

	class HeadGraph : public Graph
	{
	public:
		HeadGraph( cbm::Coal& coal, cbm::DesignGoafTechnology& tech, std::vector<cbm::DesignGoafPore>& close_pores );

	protected:
		//绘制钻场
		virtual void drawSites();
		//绘制钻孔
		virtual void drawPores();
		//绘制巷道
		virtual void drawTunnel();
		//绘制煤层
		virtual void drawCoal();
	
	}; // class HeadGraph

} // namespace P32