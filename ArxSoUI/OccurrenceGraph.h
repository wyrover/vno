#pragma once

#include "Data.h"
#include "Graph.h"

#include <ArxHelper/HelperClass.h>
#include <thrift/gen-cpp/cbm_types.h>

// 煤层赋存示意图
class OccurrenceGraph : public BaseGraph
{
public:
	OccurrenceGraph(cbm::Mine& mine, double factor=1.0);

protected:
	virtual void subDraw();
	//绘制所有煤层
	void drawAllCoals(cbm::Mine& mine);
	//绘制一个煤层
	void drawCoal(cbm::Coal& coal, const AcGePoint3d& basePt);
protected:
	// 矿井数据
	cbm::Mine& mine;
	// 煤层倾向长度
	//该数据不存在，为了绘图效果美观，内部设定一个值
	double L1;
	//煤层走向长度比例因子
	double factor;
};