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
	thick = 4; // ú����(��ʱ��Ϊ����,Ŀǰ������Ҫ)
	angle = 0; // ú�����(��ʱ��Ϊ����,Ŀǰ������Ҫ)
}

void EvalUnitGraph::subDraw()
{
	//����ͼ��
	drawWorkSuf();
	//�������
	drawTunnel();
	//�������۵�Ԫ
	drawEvalUnits();
}

void EvalUnitGraph::drawWorkSuf()
{
	this->drawRect2( getPoint(), angle, L, L2 );
}

void EvalUnitGraph::drawTunnel()
{
	AcGeVector3d v1(AcGeVector3d::kXAxis), v2(AcGeVector3d::kYAxis);
	acutPrintf(_T("\n������:%.3f"), w);
	AcGePoint3d pt = getPoint() + v2*0.5*w;
	// �������
	this->drawDoubleLine(pt, pt+v1*L, w);
	// �������ʼĩ������
	this->drawMText(pt+v1*(0-3), 0, _T("���\n���"), 8, AcDbMText::kMiddleRight);
	this->drawMText(pt+v1*(L+3), 0, _T("���\nĩ��"), 8, AcDbMText::kMiddleLeft);
	// ��ע���
	CString dimText;
	dimText.Format(_T("%d ��"), (int)L);
	this->drawAlignedDim(pt, pt+v1*L, dimText, 20, false);
}

void EvalUnitGraph::drawEvalUnits()
{
	//ǰ��:�Ѽ��㲢�������۵�Ԫ
	//��ѯ���������۵�Ԫ
	std::vector<cbm::DesignEvalUnit> eval_units;
	SQLClientHelper::GetDesignEvalUnitListByForeignKey(eval_units, "design_eval_unit_partition_id", deup.id);
	if(eval_units.empty())
	{
		AfxMessageBox(_T("��δ�������۵�Ԫ!!!"));
	}
	else
	{
		AcGeVector3d v1(AcGeVector3d::kXAxis), v2(AcGeVector3d::kYAxis);
		AcGePoint3d pt = getPoint();
		double Ln_1 = 0;
		for(int i=0;i<eval_units.size();i++)
		{
			cbm::DesignEvalUnit& eval_unit = eval_units[i];
			acutPrintf(_T("\n���۵�Ԫ:%d  ����:%.1f  ���ʱ��:%d"), eval_unit.num, eval_unit.l, eval_unit.t);
			//���Ƶ�Ԫ�߽���
			double Ln = eval_unit.l;
			AcGePoint3d spt = pt + v1*Ln;
			AcGePoint3d ept = spt + v2*L2;
			this->drawLine(spt, ept);

			// �������۵�Ԫ���ȱ�ע
			CString dimText;
			dimText.Format(_T("%d ��"), (int)eval_unit.l);
			this->drawAlignedDim(pt + v1*Ln_1 + v2*L2, ept, dimText, 20, false);

			//���Ƶ�Ԫ���
			AcGePoint3d textPt = spt - v1*(Ln-Ln_1)*0.5 + v2*L2*0.5;
			CString text;
			text.Format(_T("%d��Ԫ\n���ʱ��:%d ��"), eval_unit.num, (int)eval_unit.t);
			this->drawMText(textPt, 0, text, 8, AcDbMText::kMiddleCenter);

			//����
			Ln_1 = Ln;
		}
	}
}
