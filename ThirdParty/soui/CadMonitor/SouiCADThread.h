#pragma once

#include "MonitorThread.h"
#include "SouiDialog.h"

class SouiCADThread : public MonitorThread
{
	//其实这是一个全局函数,放在别处也可以
	//这里为了方便,就作为SouiAutoCADThread类的静态成员函数了
public:
	static void RunCAD(SouiDialog* pWnd);

public:
	SouiCADThread();
	~SouiCADThread(void);
	//将cuix备份(同时修改注册表)
	virtual void OnMonitorBegin(WPARAM wParam, LPARAM lParam);
	//将cuix还原(同时修改注册表)
	virtual void OnMonitorEnd(WPARAM wParam, LPARAM lParam);

protected:
	virtual bool getExePath(CString& path);
	virtual CString getCmdLine();
	virtual void* attachData();

public:
	SouiDialog* pWnd;
};

extern void RunCADFromSouiDialog(SouiDialog* pWnd);
