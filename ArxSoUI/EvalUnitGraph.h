#pragma once

#include "Data.h"
#include "Graph.h"

#include <ArxHelper/HelperClass.h>
#include <thrift/gen-cpp/cbm_types.h>

// 煤层赋存示意图
class EvalUnitGraph : public BaseGraph
{
public:
	EvalUnitGraph(cbm::DesignEvalUnitPartition& deup);

protected:
	virtual void subDraw();
	//绘制工作面
	void drawWorkSuf();
	//绘制巷道
	void drawTunnel();
	//绘制评价单元
	void drawEvalUnits();
protected:
	//评价单元划分数据
	cbm::DesignEvalUnitPartition& deup;
	//倾向长度和走向长度
	double L1, L2;
	//煤层长度、厚度和倾角(弧度)
	double thick, angle;
	//工作面巷道的宽度和高度
	double L, w, h;

};