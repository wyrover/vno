#include "stdafx.h"
#include "MonitorDialog.h"
#include "SouiCADThread.h"

MonitorDialog::MonitorDialog(BOOL bModal) : SouiDialog(_T("layout:monitor"), bModal)
{
}

MonitorDialog::~MonitorDialog()
{
}

void MonitorDialog::OnCommand( UINT uNotifyCode, int nID, HWND wndCtl )
{
	if(uNotifyCode==0)
	{
		//if(nID==6)
		//{
		//}
	}
}

LRESULT MonitorDialog::OnInitDialog( HWND hWnd, LPARAM lParam )
{
	SouiDialog::OnInitDialog(hWnd, lParam);
	//do something
	return 0;
}

void MonitorDialog::OnMonitorButtonClick()
{
	SouiCADThread::RunCAD(this);
}

LRESULT MonitorDialog::OnBeginMonitor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	MonitorThreadData* pData = ( MonitorThreadData* )wParam;
	if(pData != 0 && pData->monitor != 0)
	{
		pData->monitor->OnMonitorBegin(wParam, lParam);
	}
	return 0;
}

LRESULT MonitorDialog::OnEndMonitor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	MonitorThreadData* pData = ( MonitorThreadData* )wParam;
	if(pData != 0 && pData->monitor != 0)
	{
		pData->monitor->OnMonitorEnd(wParam, lParam);
	}
	return 0;
}
