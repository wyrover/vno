#include "stdafx.h"
#include "MainuiDialog.h"
#include "CADHelper.h"
#include "ThreadHelper.h"
#include "SouiCADThread.h"

MainuiDialog::MainuiDialog( BOOL bModal ) : SouiDialog( _T( "layout:cbm" ), bModal )
{
}

MainuiDialog::~MainuiDialog()
{
}

void MainuiDialog::OnCommand( UINT uNotifyCode, int nID, HWND wndCtl )
{
    if( uNotifyCode == 0 )
    {
        //if(nID==6)
        //{
        //}
    }
}

LRESULT MainuiDialog::OnInitDialog( HWND hWnd, LPARAM lParam )
{
    SouiDialog::OnInitDialog( hWnd, lParam );
    //do something
    return 0;
}

void MainuiDialog::OnCadButtonClick()
{
    //启动CAD进程
    SouiCADThread::RunCAD( this );
	//CADHelper::SendCommandToAutoCAD(_T("regen"));
	//CADHelper::SendCommandToAutoCAD(_T("redraw"), false);
}

void MainuiDialog::OnCadfileButtonClick()
{
    //弹出文件选择对话框,用于选择dwg文件
    CString dwgFile;
    TCHAR szFileFilter[] = _T( "DWG文件(*.dwg)|*.dwg|DXF文件(*.dxf)|*.dxf|所有文件(*.*)|*.*||" );
    TCHAR szFileExt[] = _T( "dwg" );
    if( !CADHelper::SelectFile( dwgFile, szFileFilter, szFileExt ) ) return;

    //启动CAD进程
    SouiCADThread::RunCAD( this, dwgFile );
}

void MainuiDialog::OnDestroyWindow()
{
}

LRESULT MainuiDialog::OnBeginMonitor( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
    MonitorThreadData* pData = ( MonitorThreadData* )lParam;
    if( pData != 0 && pData->monitor != 0 )
    {
        return pData->monitor->OnMonitorBegin( wParam, lParam );
    }
    return FALSE;
}

LRESULT MainuiDialog::OnEndMonitor( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
    MonitorThreadData* pData = ( MonitorThreadData* )lParam;
    if( pData != 0 && pData->monitor != 0 )
    {
        return pData->monitor->OnMonitorEnd( wParam, lParam );
    }
    return FALSE;
}

void MainuiDialog::OnClose()
{
    if ( ThreadHelper::IsProcessActive( _T( "acad.exe" ) ) )
    {
        MessageBox( NULL, _T( "请先关闭CAD!" ), _T( "警告" ), MB_OK | MB_ICONWARNING );
        return;
    }
    SouiDialog::OnClose();
}