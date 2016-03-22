#pragma once

#include "Data.h"
#include "Graph.h"

#include <ArxHelper/HelperClass.h>
#include <thrift/gen-cpp/cbm_types.h>

// ú�㸳��ʾ��ͼ
class OccurrenceGraph : public BaseGraph
{
public:
	OccurrenceGraph(cbm::Mine& mine, double factor=1.0);

protected:
	virtual void subDraw();
	//��������ú��
	void drawAllCoals(cbm::Mine& mine);
	//����һ��ú��
	void drawCoal(cbm::Coal& coal, const AcGePoint3d& basePt);
protected:
	// ������
	cbm::Mine& mine;
	// ú�����򳤶�
	//�����ݲ����ڣ�Ϊ�˻�ͼЧ�����ۣ��ڲ��趨һ��ֵ
	double L1;
	//ú�����򳤶ȱ�������
	double factor;
};