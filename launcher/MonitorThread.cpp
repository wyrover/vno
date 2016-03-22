#include "StdAfx.h"
#include "MonitorThread.h"
#include "ThreadHelper.h"
#include "CADHelper.h"

// ���̲߳�ѯʱ����
#define THREAD_CHECK_TIME_INTERVAL 1000

// ȫ���߳�����
MonitorThreadData MonitorThread::thread_data;
// ȫ�ֱ���--�û��Ƿ�Ҫ���߳̽���
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

MonitorThread::MonitorThread() : m_bShow( true )
{

}

static DWORD MonitorThreadProc( LPVOID lpParam )
{
    MonitorThreadData* pData = ( MonitorThreadData* )lpParam;

    while( true )
    {
        Sleep( THREAD_CHECK_TIME_INTERVAL );

        if( !ThreadHelper::IsProcessActive2( MonitorThread::GetProcess() ) )
        {
            break;
        }
        else if( MonitorThread::IsAskForEnd() )
        {
            CloseHandle( pData->hThread );
            CloseHandle( pData->hProcess );

            // ��ͼ�˳��߳�(û�гɹ�???)
            //DWORD exitCode;
            //GetExitCodeProcess(pData->hProcess, &exitCode);
            //ExitProcess(exitCode);
            break;
        }
    }

	if( !CADHelper::CleanCAD() )
	{
		return FALSE;
	}
	else
	{
		//���ռ�ض��������(MonitorThread* monitor)
		MonitorThreadData* pData = ( MonitorThreadData* )lpParam;
		if( pData != 0 && pData->monitor != 0 )
		{
			delete pData->monitor;
			pData->monitor = 0;
		}
	}

    //ִ��������β����
    //SendMessage( pData->hWnd, WM_END_MONITOR, ( WPARAM )NULL, ( LPARAM )pData );
    return 0;
}

bool MonitorThread::Run( HANDLE& hThread )
{
    //��ȡexe��·��
    //��:����Ӧ�ö�exe·����һЩ���(�����Ƿ�exe��׺,�Ƿ���Ч��exe�ȵ�)
    if( m_exePath.GetLength() == 0 ) return false;

    MonitorThreadData data;
    data.monitor = this;
    data.hProcess = NULL;
    data.hThread = NULL;
    data.hWnd = m_hWnd;
    //data.value = attachData();

    //��������ǰ��һЩ׼������
    //LRESULT lResult = SendMessage( this->m_hWnd, WM_BEGIN_MONITOR, ( WPARAM )NULL, ( LPARAM )&data );
    //if( lResult == 0 ) return false;
	//��ʼ��CAD
	if( !CADHelper::InitCAD() )
	{
		return false;
	}

    //��������
    if( !ThreadHelper::RunProecess(
                m_exePath,    // exe·��
                m_cmdLine,    // �����в���
                m_workDir,    // ��ǰ����·��
                data.hProcess,
                data.hThread,
                m_bShow ) )
    {
        CString msg;
        msg.Format( _T( "error id:%d" ), GetLastError() );
        AfxMessageBox( msg );
        return false;
    }

    // ���ݸ�ȫ�ֱ���(����һЩδ֪���̴߳���)
    thread_data = data;

    // ���������߳�
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

LRESULT MonitorThread::OnMonitorBegin( WPARAM wParam, LPARAM lParam )
{
    return TRUE;
}

LRESULT MonitorThread::OnMonitorEnd( WPARAM wParam, LPARAM lParam )
{
    //���ռ�ض��������(MonitorThread* monitor)
    MonitorThreadData* pData = ( MonitorThreadData* )lParam;
    if( pData != 0 && pData->monitor != 0 )
    {
        delete pData->monitor;
        pData->monitor = 0;
    }
    return TRUE;
}
