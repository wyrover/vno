#pragma once

#include "SouiDialog.h"
#include "MonitorThread.h"

class MonitorDialog : public SouiDialog
{

	/** ������������� */
public:
	MonitorDialog(BOOL bModal = FALSE);
	~MonitorDialog(void);

	/** �Զ�������Ϣ */
protected:
	LRESULT OnBeginMonitor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnEndMonitor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	/** �ؼ���Ϣ���� */
protected:
	void OnMonitorButtonClick();

	/** �˵���Ϣ */
protected:
	//����˵���Ϣ(�˵���һ��������xml�ļ���������ÿ���˵����һ��id��)
	void OnCommand(UINT uNotifyCode, int nID, HWND wndCtl);

	/** ������Ϣ */
protected:
	//�Ի����ʼ������
	LRESULT OnInitDialog(HWND hWnd, LPARAM lParam);

	//�ؼ���Ϣӳ���
	EVENT_MAP_BEGIN()
		EVENT_NAME_COMMAND(_T("monitor"), OnMonitorButtonClick)
		CHAIN_EVENT_MAP(SouiDialog)
	EVENT_MAP_END()
	
//HOST��Ϣ(WINDOWS��Ϣ)ӳ���
	BEGIN_MSG_MAP_EX(MonitorDialog)
		MESSAGE_HANDLER(WM_BEGIN_MONITOR, OnBeginMonitor)
		MESSAGE_HANDLER(WM_END_MONITOR, OnEndMonitor)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_COMMAND(OnCommand)
		CHAIN_MSG_MAP(SouiDialog)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

protected:
};
