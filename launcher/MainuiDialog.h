#pragma once
#include "SouiDialog.h"
#include "MonitorThread.h"

class MainuiDialog : public SouiDialog
{

    /** 构造和析构函数 */
public:
    MainuiDialog( BOOL bModal = FALSE );
    ~MainuiDialog( void );

    /** 自定义监控消息 */
protected:
    LRESULT OnBeginMonitor( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );
    LRESULT OnEndMonitor( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );

    /** 控件消息处理 */
protected:
    void OnCadButtonClick();
    void OnCadfileButtonClick();
    void OnClose();

    /** 菜单消息 */
protected:
    //处理菜单消息(菜单在一个单独的xml文件中描述，每个菜单项都有一个id号)
    void OnCommand( UINT uNotifyCode, int nID, HWND wndCtl );

    /** 窗口消息 */
protected:
    //对话框初始化过程
    LRESULT OnInitDialog( HWND hWnd, LPARAM lParam );
    //窗口关闭前做一些清理工作
    virtual void OnDestroyWindow();

    //控件消息映射表
    EVENT_MAP_BEGIN()
    EVENT_NAME_COMMAND( _T( "btn_close" ), OnClose )
    EVENT_NAME_COMMAND( _T( "cad" ), OnCadButtonClick )
    EVENT_NAME_COMMAND( _T( "cadfile" ), OnCadfileButtonClick )
    CHAIN_EVENT_MAP( SouiDialog )
    EVENT_MAP_END()

//HOST消息(WINDOWS消息)映射表
    BEGIN_MSG_MAP_EX( MainuiDialog )
    MSG_WM_INITDIALOG( OnInitDialog )
    MSG_WM_COMMAND( OnCommand )
    MESSAGE_HANDLER( WM_BEGIN_MONITOR, OnBeginMonitor )
    MESSAGE_HANDLER( WM_END_MONITOR, OnEndMonitor )
    CHAIN_MSG_MAP( SouiDialog )
    REFLECT_NOTIFICATIONS_EX()
    END_MSG_MAP()
};
