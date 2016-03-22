#include "StdAfx.h"
#include "SouiCADThread.h"
#include "ThreadHelper.h"

// Gabmit��ע������Լ�·��
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
	//���ش���
	pWnd->ShowWindow(SW_HIDE);
}

void SouiCADThread::OnMonitorEnd(WPARAM wParam, LPARAM lParam)
{
	//��ʾ����
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
		//�ȴ��߳�,ͬʱ����������Ϣ
		ThreadHelper::MsgWaitForThread(hThread);
		//�ȴ��߳̽���(���ܽ�����Ϣ)
		//WaitForSingleObject( hThread, INFINITE );
		CloseHandle( hThread );
	}
}
