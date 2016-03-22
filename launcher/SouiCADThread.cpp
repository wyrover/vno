#include "StdAfx.h"
#include "SouiCADThread.h"
#include "ThreadHelper.h"
#include "CADHelper.h"

SouiCADThread::SouiCADThread( const CString& dwgFile )
{
    //����cad��·��
    SetExePath( CADHelper::GetCADPath() );
    //���������в���
    CString strArg;
    if( dwgFile.GetLength() > 0 )
    {
        strArg = _T( "motifi " ) + dwgFile;
    }
    SetCmdLine( strArg );
    //���õ�ǰ����·��
    SetWorkDirectory( ThreadHelper::GetAppPathDir( NULL ) );
    //��ʾCAD����
    ShowWindow( true );
}

SouiCADThread::~SouiCADThread( void )
{
}

LRESULT SouiCADThread::OnMonitorBegin( WPARAM wParam, LPARAM lParam )
{
    //��ʼ��CAD
    if( !CADHelper::InitCAD() )
    {
        return FALSE;
    }
    else
    {
        //���ش���
        return pWnd->ShowWindow( SW_HIDE );
        //���û��෽��
        return MonitorThread::OnMonitorBegin( wParam, lParam );;
    }
}

LRESULT SouiCADThread::OnMonitorEnd( WPARAM wParam, LPARAM lParam )
{
    if( !CADHelper::CleanCAD() )
    {
        return FALSE;
    }
    else
    {
        //��ʾ����
        pWnd->ShowWindow( SW_SHOW );
        //���û���ķ���,�����ڴ�
        return MonitorThread::OnMonitorEnd( wParam, lParam );
    }
}

void SouiCADThread::RunCAD( SouiDialog* pWnd, const CString& dwgFile )
{
    SouiCADThread* cad = new SouiCADThread( dwgFile );
    //cad->SetWndHandle( pWnd->GetSafeHwnd() );
    //cad->pWnd = pWnd;

    HANDLE hThread = NULL;
    bool ret = cad->Run( hThread );
    if( ret )
    {
        //�ȴ��߳�,ͬʱ����������Ϣ
        ThreadHelper::MsgWaitForThread( hThread );
        //�ȴ��߳̽���(���ܽ�����Ϣ)
        //WaitForSingleObject( hThread, INFINITE );
        CloseHandle( hThread );
    }
}
