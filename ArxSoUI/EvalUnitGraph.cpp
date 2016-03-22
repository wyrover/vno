#include "stdafx.h"
#include "EvalUnitGraph.h"

#include <ArxHelper/HelperClass.h>
#include "CbmClientHelper.h"
#include "SQLClientHelper.h"

EvalUnitGraph::EvalUnitGraph(cbm::DesignEvalUnitPartition& _deup) 
	: deup(_deup)
{
	L = deup.l;
	L1 = deup.l1;
	L2 = deup.l2;
	w = deup.w;
	h = deup.h;

	L = (std::min)(L, L1);
	thick = 4; // 煤层厚度(暂时人为给定,目前还不需要)
	angle = 0; // 煤层倾角(暂时人为给定,目前还不需要)
}

void EvalUnitGraph::subDraw()
{
	//绘制图形
	drawWorkSuf();
	//绘制巷道
	drawTunnel();
	//绘制评价单元
	drawEvalUnits();
}

void EvalUnitGraph::drawWorkSuf()
{
	this->drawRect2( getPoint(), angle, L, L2 );
}

void EvalUnitGraph::drawTunnel()
{
	AcGeVector3d v1(AcGeVector3d::kXAxis), v2(AcGeVector3d::kYAxis);
	acutPrintf(_T("\n巷道宽度:%.3f"), w);
	AcGePoint3d pt = getPoint() + v2*0.5*w;
	// 绘制巷道
	this->drawDoubleLine(pt, pt+v1*L, w);
	// 绘制巷道始末点文字
	this->drawMText(pt+v1*(0-3), 0, _T("巷道\n起点"), 8, AcDbMText::kMiddleRight);
	this->drawMText(pt+v1*(L+3), 0, _T("巷道\n末点"), 8, AcDbMText::kMiddleLeft);
	// 标注巷道
	CString dimText;
	dimText.Format(_T("%d 米"), (int)L);
	this->drawAlignedDim(pt, pt+v1*L, dimText, 20, false);
}

void EvalUnitGraph::drawEvalUnits()
{
	//前提:已计算并划分评价单元
	//查询关联的评价单元
	std::vector<cbm::DesignEvalUnit> eval_units;
	SQLClientHelper::GetDesignEvalUnitListByForeignKey(eval_units, "design_eval_unit_partition_id", deup.id);
	if(eval_units.empty())
	{
		AfxMessageBox(_T("尚未划分评价单元!!!"));
	}
	else
	{
		AcGeVector3d v1(AcGeVector3d::kXAxis), v2(AcGeVector3d::kYAxis);
		AcGePoint3d pt = getPoint();
		double Ln_1 = 0;
		for(int i=0;i<eval_units.size();i++)
		{
			cbm::DesignEvalUnit& eval_unit = eval_units[i];
			acutPrintf(_T("\n评价单元:%d  距离:%.1f  抽采时间:%d"), eval_unit.num, eval_unit.l, eval_unit.t);
			//绘制单元边界线
			double Ln = eval_unit.l;
			AcGePoint3d spt = pt + v1*Ln;
			AcGePoint3d ept = spt + v2*L2;
			this->drawLine(spt, ept);

			// 绘制评价单元长度标注
			CString dimText;
			dimText.Format(_T("%d 米"), (int)eval_unit.l);
			this->drawAlignedDim(pt + v1*Ln_1 + v2*L2, ept, dimText, 20, false);

			//绘制单元编号
			AcGePoint3d textPt = spt - v1*(Ln-Ln_1)*0.5 + v2*L2*0.5;
			CString text;
			text.Format(_T("%d单元\n抽采时间:%d 天"), eval_unit.num, (int)eval_unit.t);
			this->drawMText(textPt, 0, text, 8, AcDbMText::kMiddleCenter);

			//更新
			Ln_1 = Ln;
		}
	}
}
