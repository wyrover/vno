#include "StdAfx.h"
#include "SouiCADThread.h"
#include "ThreadHelper.h"
#include "CADHelper.h"

SouiCADThread::SouiCADThread( const CString& dwgFile )
{
    //设置cad的路径
    SetExePath( CADHelper::GetCADPath() );
    //设置命令行参数
    CString strArg;
    if( dwgFile.GetLength() > 0 )
    {
        strArg = _T( "motifi " ) + dwgFile;
    }
    SetCmdLine( strArg );
    //设置当前工作路径
    SetWorkDirectory( ThreadHelper::GetAppPathDir( NULL ) );
    //显示CAD窗口
    ShowWindow( true );
}

SouiCADThread::~SouiCADThread( void )
{
}

LRESULT SouiCADThread::OnMonitorBegin( WPARAM wParam, LPARAM lParam )
{
    //初始化CAD
    if( !CADHelper::InitCAD() )
    {
        return FALSE;
    }
    else
    {
        //隐藏窗口
        return pWnd->ShowWindow( SW_HIDE );
        //调用基类方法
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
        //显示窗口
        pWnd->ShowWindow( SW_SHOW );
        //调用基类的方法,回收内存
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
        //等待线程,同时处理其他消息
        ThreadHelper::MsgWaitForThread( hThread );
        //等待线程结束(不能接受消息)
        //WaitForSingleObject( hThread, INFINITE );
        CloseHandle( hThread );
    }
}
