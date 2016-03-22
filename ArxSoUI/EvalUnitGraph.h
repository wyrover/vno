#pragma once

#include "Data.h"
#include "Graph.h"

#include <ArxHelper/HelperClass.h>
#include <thrift/gen-cpp/cbm_types.h>

// ú�㸳��ʾ��ͼ
class EvalUnitGraph : public BaseGraph
{
public:
	EvalUnitGraph(cbm::DesignEvalUnitPartition& deup);

protected:
	virtual void subDraw();
	//���ƹ�����
	void drawWorkSuf();
	//�������
	void drawTunnel();
	//�������۵�Ԫ
	void drawEvalUnits();
protected:
	//���۵�Ԫ��������
	cbm::DesignEvalUnitPartition& deup;
	//���򳤶Ⱥ����򳤶�
	double L1, L2;
	//ú�㳤�ȡ���Ⱥ����(����)
	double thick, angle;
	//����������Ŀ�Ⱥ͸߶�
	double L, w, h;

};