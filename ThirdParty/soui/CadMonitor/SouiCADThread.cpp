#include "StdAfx.h"
#include "SouiCADThread.h"
#include "ThreadHelper.h"

// Gabmit的注册表项以及路径
#define GAMBIT_KEY HKEY_CURRENT_USER
#define GAMBIT_SUB_KEY _T("Software\\Fluent Inc Products\\Exe")

SouiCADThread::SouiCADThread()
{
}

SouiCADThread::~SouiCADThread(void)
{
}

bool SouiCADThread::getExePath(CString& path)
{
	path = _T("C:\\Program Files\\AutoCAD 2010\\acad.exe");
	return true;
}

CString SouiCADThread::getCmdLine()
{
	return _T("");
}

void* SouiCADThread::attachData()
{
	CString appDir = ThreadHelper::GetAppPathDir();
	return 0;
}

void SouiCADThread::OnMonitorBegin(WPARAM wParam, LPARAM lParam)
{
	//隐藏窗口
	pWnd->ShowWindow(SW_HIDE);
}

void SouiCADThread::OnMonitorEnd(WPARAM wParam, LPARAM lParam)
{
	//显示窗口
	pWnd->ShowWindow(SW_SHOW);
}

void SouiCADThread::RunCAD(SouiDialog* pWnd)
{
	SouiCADThread* cad = new SouiCADThread();
	cad->SetWorkDirectory(ThreadHelper::GetAppPathDir(NULL));
	cad->ShowWindow(true);
	cad->SetWndHandle(pWnd->GetSafeHwnd());
	cad->pWnd = pWnd;

	HANDLE hThread = NULL;
	bool ret = cad->Run(hThread);
	if(ret)
	{
		//等待线程,同时处理其他消息
		ThreadHelper::MsgWaitForThread(hThread);
		//等待线程结束(不能接受消息)
		//WaitForSingleObject( hThread, INFINITE );
		CloseHandle( hThread );
	}
}
