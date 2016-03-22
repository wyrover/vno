#pragma once

#include <event/Events.h>
#include <control/SListCtrl.h>

#define EVT_LC_DBL_CLICK (SOUI::EVT_EXTERNAL_BEGIN+500)
#define EVT_LC_RBUTTON_UP (SOUI::EVT_EXTERNAL_BEGIN+501)

//˫����Ϣ
class /*SOUI_EXP*/ EventLCDblClick : public SOUI::TplEventArgs<EventLCDblClick>
{
	SOUI_CLASS_NAME(EventLCDblClick,L"on_listctrl2_dbl_click")
public:
	EventLCDblClick(SOUI::SObject *pSender):SOUI::TplEventArgs<EventLCDblClick>(pSender){}
	enum{EventID=EVT_LC_DBL_CLICK};
	int nCurSel;
};

/**
* soui�ṩ��SListCtrl�޷��������˫����Ϣ
* ����soui�ṩ����������Ҳ�ǳ���
* 1����ԭ�ؼ�����(SOUI_CLASS_NAME����겻����)
* 2������Ҫ�������Ϣӳ���Ҫ�������Ϣ
* 3��Ϊ�˱�����չʹ��,��˫����Ϣת����ȥ
*    �Զ�����ϢEventLCDblClick,�������ϢID���Լ���Ҫ�Ĳ���
* 4����������Ĺ��캯�������������Զ������Ϣ
* 5��Ȼ����˫������Ϣ�����н��Զ�����Ϣת����ȥ(�μ�OnLButtonDblClick��ʵ��)
* 6�������Ŀؼ�һ��Ҫע�ᵽsoui��(�μ�UiHelper3.cpp���MySoUiLoader3::initExtendControls()����
*/
class SListCtrl2 : public SOUI::SListCtrl
{
	SOUI_CLASS_NAME(SListCtrl2,L"listctrl2")
public:
	SListCtrl2() 
	{
		GetEventSet()->addEvent(EVENTID(EventLCDblClick));
	}

protected:
	void OnLButtonDblClick(UINT nFlags, SOUI::CPoint pt);
	void OnRButtonDown(UINT nFlags, SOUI::CPoint pt);

protected://��Ϣ����SOUI�ؼ�����Ϣ�����WTL��MFC�����ƣ��������Ƶ�ӳ�����ͬ�������Ƶ���Ϣӳ���
	//SOUI�ؼ���Ϣӳ���
	SOUI_MSG_MAP_BEGIN()	
		MSG_WM_LBUTTONDBLCLK(OnLButtonDblClick)   
		MSG_WM_RBUTTONDOWN(OnRButtonDown)
	SOUI_MSG_MAP_END()
};