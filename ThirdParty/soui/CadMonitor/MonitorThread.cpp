#include "StdAfx.h"
#include "MonitorThread.h"
#include "ThreadHelper.h"

// 多线程查询时间间隔
#define THREAD_CHECK_TIME_INTERVAL 1000

// 全局线程数据
MonitorThreadData MonitorThread::thread_data;
// 全局变量--用户是否要求线程结束
bool MonitorThread::thread_end;

bool MonitorThread::IsAskForEnd()
{
	return thread_end;
}

void MonitorThread::AskForEnd( bool flag )
{
	thread_end = flag;
}

HANDLE MonitorThread::GetProcess()
{
	return thread_data.hProcess;
}

MonitorThread::MonitorThread() : m_bShow(true)
{

}

static DWORD MonitorThreadProc( LPVOID lpParam )
{
	MonitorThreadData* pData = ( MonitorThreadData* )lpParam;

	while( true )
	{
		Sleep( THREAD_CHECK_TIME_INTERVAL );

		if(!ThreadHelper::IsProcessActive2(MonitorThread::GetProcess()))
		{
			break;
		}
		else if( MonitorThread::IsAskForEnd())
		{
			CloseHandle( pData->hThread );
			CloseHandle( pData->hProcess );

			// 试图退出线程(没有成功???)
			//DWORD exitCode;
			//GetExitCodeProcess(pData->hProcess, &exitCode);
			//ExitProcess(exitCode);
			break;
		}
	}
	//执行清理收尾工作
	SendMessage(pData->hWnd, WM_END_MONITOR, (WPARAM)pData, NULL);
	return 0;
}

bool MonitorThread::Run(HANDLE hThread)
{
	//读取exe的路径
	CString ExePath;
	if( !getExePath( ExePath ) ) return false;

	MonitorThreadData data;
	data.monitor = this;
	data.hProcess = NULL;
	data.hThread = NULL;
	data.hWnd = m_hWnd;
	data.data = attachData();

	CString cmdLine = getCmdLine();

	//启动进程前做一些准备工作
	SendMessage(this->m_hWnd, WM_BEGIN_MONITOR, (WPARAM)&data, NULL);

	//启动进程
	if( !ThreadHelper::RunProecess(
		ExePath,    // exe路径
		cmdLine,    // 命令行参数
		m_workDir,  // 当前工作路径
		data.hProcess,
		data.hThread,
		m_bShow ) )
	{
		CString msg;
		msg.Format(_T("error id:%d"), GetLastError());
		AfxMessageBox(msg);
		return false;
	}

	// 传递给全局变量(避免一些未知的线程错误)
	thread_data = data;

	// 创建监视线程
	DWORD dwThreadId;
	/*HANDLE*/
	hThread = CreateThread(
		NULL,              // default security attributes
		0,                 // use default stack size
		( LPTHREAD_START_ROUTINE )MonitorThreadProc,        // thread function
		&thread_data,             // argument to thread function
		0,                 // use default creation flags
		&dwThreadId );  // returns the thread identifier

	return true;
}

void MonitorThread::SetWndHandle(HWND hWnd)
{
	m_hWnd = hWnd;
}

void MonitorThread::ShowWindow(bool bShow)
{
	m_bShow = bShow;
}

void MonitorThread::SetWorkDirectory(const CString& workDir)
{
	m_workDir = workDir;
}
