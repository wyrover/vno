#pragma once

#include "MonitorThread.h"
#include "SouiDialog.h"

class SouiCADThread : public MonitorThread
{
	//��ʵ����һ��ȫ�ֺ���,���ڱ�Ҳ����
	//����Ϊ�˷���,����ΪSouiAutoCADThread��ľ�̬��Ա������
public:
	static void RunCAD(SouiDialog* pWnd);

public:
	SouiCADThread();
	~SouiCADThread(void);
	//��cuix����(ͬʱ�޸�ע���)
	virtual void OnMonitorBegin(WPARAM wParam, LPARAM lParam);
	//��cuix��ԭ(ͬʱ�޸�ע���)
	virtual void OnMonitorEnd(WPARAM wParam, LPARAM lParam);

protected:
	virtual bool getExePath(CString& path);
	virtual CString getCmdLine();
	virtual void* attachData();

public:
	SouiDialog* pWnd;
};

extern void RunCADFromSouiDialog(SouiDialog* pWnd);
