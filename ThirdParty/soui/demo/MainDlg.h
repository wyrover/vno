/**
* Copyright (C) 2014-2050 
* All rights reserved.
* 
* @file       MainDlg.h
* @brief      
* @version    v1.0      
* @author     SOUI group   
* @date       2014/08/15
* 
* Describe    ������ʵ��
*/

#pragma once

#include "../controls.extend/SChromeTabCtrl.h"

/**
* @class      CMainDlg
* @brief      ������ʵ��
* 
* Describe    ��ģʽ���ڴ�SHostWnd������ģʽ���ڴ�SHostDialog����
*/
class CMainDlg : public SHostWnd
{
public:

    /**
     * CMainDlg
     * @brief    ���캯��
     * Describe  ʹ��uires.idx�ж����maindlg��Ӧ��xml���ִ���UI
     */    
    CMainDlg() : SHostWnd(_T("maindlg")),m_bLayoutInited(FALSE)
    {
    } 

protected:
    //////////////////////////////////////////////////////////////////////////
    //  Window��Ϣ��Ӧ����
    LRESULT OnInitDialog(HWND hWnd, LPARAM lParam);
    void OnDestory();

	void OnClose()
	{
		AnimateHostWindow(200,AW_CENTER|AW_HIDE);
        PostMessage(WM_QUIT);
	}
	void OnMaximize()
	{
		GetNative()->SendMessage(WM_SYSCOMMAND,SC_MAXIMIZE);
	}
	void OnRestore()
	{
		GetNative()->SendMessage(WM_SYSCOMMAND,SC_RESTORE);
	}
	void OnMinimize()
	{
		GetNative()->SendMessage(WM_SYSCOMMAND,SC_MINIMIZE);
	}

	void OnSize(UINT nType, CSize size)
	{
		SetMsgHandled(FALSE);   //��һ�к���Ҫ����֤��Ϣ�������ݸ�SHostWnd������ȻҲ������SHostWnd::OnSize(nType,size);���棬��������ʹ�õķ������򵥣�ͨ��
		if(!m_bLayoutInited) return;
		if(nType==SIZE_MAXIMIZED)
		{
			FindChildByID(3)->SetVisible(TRUE);
			FindChildByID(2)->SetVisible(FALSE);
		}else if(nType==SIZE_RESTORED)
		{
			FindChildByID(3)->SetVisible(FALSE);
			FindChildByID(2)->SetVisible(TRUE);
		}
	}
    
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void OnShowWindow(BOOL bShow, UINT nStatus);
    
    //��ʾ�����Ӧ�ò�ʹ�ö�ʱ��
    void OnTimer(UINT_PTR idEvent);

    //DUI�˵���Ӧ����
    void OnCommand(UINT uNotifyCode, int nID, HWND wndCtl);
        
protected:
    //////////////////////////////////////////////////////////////////////////
    // SOUI�¼�������
	//��ʾ����ָ��edit�ؼ����Ҽ��˵�
	BOOL OnEditMenu(CPoint pt)
	{
		return TRUE;
	}

    //��ť�ؼ�����Ӧ
    void OnBtnSelectGIF();
    void OnBtnMenu();

    void OnBtnInsertGif2RE();
    void OnBtnAppendMsg();
    void OnBtnRtfSave();
    void OnBtnRtfOpen();
    
    void OnBtnHideTest();
    void OnBtnMsgBox();

    void OnBtnWebkitGo();
    void OnBtnWebkitBackward();
    void OnBtnWebkitForeward();
    void OnBtnWebkitRefresh();

    void OnSkiaTest();
    
    //��ʾ���ʹ��subscribeEvent����ʹ���¼�ӳ���ʵ���¼���Ӧ
    bool OnListHeaderClick(EventArgs *pEvt);

    //��ʾ�����Ӧ��listboxex,treeboxex�е�item�а����ؼ����¼���
    void OnListBoxExEvent(EventArgs *pEvt);
    void OnTreeBoxEvent(EventArgs *pEvt);
    
    void OnTreeBoxQueryItemHeight(EventArgs * pEvt);
    
    void OnChromeTabNew(EventArgs *pEvt);

    void OnTabPageRadioSwitch(int nID);
    
    void OnBtnFileWnd();

    void OnUrlReNotify(EventArgs *pEvt);

    //UI�ؼ����¼�����Ӧ����ӳ���
	EVENT_MAP_BEGIN()
		EVENT_ID_COMMAND(1, OnClose)
		EVENT_ID_COMMAND(2, OnMaximize)
		EVENT_ID_COMMAND(3, OnRestore)
		EVENT_ID_COMMAND(5, OnMinimize)
		EVENT_NAME_CONTEXTMENU(L"edit_1140",OnEditMenu)
		EVENT_NAME_COMMAND(L"btn_msgbox",OnBtnMsgBox)
		EVENT_NAME_COMMAND(L"btnSelectGif",OnBtnSelectGIF)
        EVENT_NAME_COMMAND(L"btn_menu",OnBtnMenu)
        EVENT_NAME_COMMAND(L"btn_webkit_go",OnBtnWebkitGo)
        EVENT_NAME_COMMAND(L"btn_webkit_back",OnBtnWebkitBackward)
        EVENT_NAME_COMMAND(L"btn_webkit_fore",OnBtnWebkitForeward)
        EVENT_NAME_COMMAND(L"btn_webkit_refresh",OnBtnWebkitRefresh)
        EVENT_NAME_COMMAND(L"btn_hidetst",OnBtnHideTest)
//      EVENT_NAME_COMMAND(L"btn_insert_gif",OnBtnInsertGif2RE)
        EVENT_ID_COMMAND(STR2ID(L"id_test1"),OnBtnInsertGif2RE) //��init.xml������֧��id����һ�к�����һ��Ч��һ����
        EVENT_NAME_COMMAND(L"btn_append_msg",OnBtnAppendMsg)
        EVENT_NAME_COMMAND(L"btn_richedit_save",OnBtnRtfSave)
        EVENT_NAME_COMMAND(L"btn_richedit_open",OnBtnRtfOpen)
        EVENT_NAME_COMMAND(L"btn_skiatest",OnSkiaTest)
        EVENT_NAME_HANDLER(L"lbe_test",EVT_OFPANEL,OnListBoxExEvent)//��ӦEVT_OFPANEL�¼�
        EVENT_NAME_HANDLER(L"tb_test",EVT_OFPANEL,OnTreeBoxEvent)//��ӦEVT_OFPANEL�¼�
        EVENT_NAME_HANDLER(L"tb_test",EVT_TB_QUERYITEMHEIGHT,OnTreeBoxQueryItemHeight)//��Ӧ��̬��ѯ�߶��¼�
        EVENT_ID_COMMAND_RANGE(10000,10005,OnTabPageRadioSwitch)    //10000-10005��XML�ж����radio2��ID
        EVENT_NAME_HANDLER(L"chromeTab",EVT_CHROMETAB_NEW,OnChromeTabNew)
        EVENT_NAME_COMMAND(L"btn_filewnd",OnBtnFileWnd)
        EVENT_NAME_HANDLER(L"edit_url",EVT_RE_NOTIFY,OnUrlReNotify)
	EVENT_MAP_END()	

    //HOST��Ϣ����Ӧ����ӳ���
	BEGIN_MSG_MAP_EX(CMainDlg)
		MSG_WM_CREATE(OnCreate)
        MSG_WM_INITDIALOG(OnInitDialog)
        MSG_WM_DESTROY(OnDestory)
		MSG_WM_CLOSE(OnClose)
		MSG_WM_SIZE(OnSize)
		MSG_WM_COMMAND(OnCommand)
		MSG_WM_SHOWWINDOW(OnShowWindow)
		CHAIN_MSG_MAP(SHostWnd)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

protected:
    //////////////////////////////////////////////////////////////////////////
    //  ��������
    void InitListCtrl();
private:
	BOOL			m_bLayoutInited;/**<UI��ɲ��ֱ�־ */
};
