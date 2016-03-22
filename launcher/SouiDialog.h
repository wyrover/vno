#pragma once

/**
 * soui对话框封装类.
 * 用法:
	(1)非模态对话框(必须new，否则会导致内存错误)
    HWND hWnd = getWindowHandle();  // 必须要指定有效的父窗口句柄
	LoginDlg* dlg = new LoginDlg(FALSE);
	dlg->Run(hWnd);

	(2)模态对话框(最好是用局部变量,不要new)
	HWND hWnd = getWindowHandle();  // 必须要指定有效的父窗口句柄
	LoginDlg dlg(TRUE);
	dlg.Run(hWnd);
*/
class SouiDialog : public SOUI::SHostDialog
{
public:
    //构造函数
    //bModal参数指定是模态对话框还是非模态对话框
    SouiDialog( LPCTSTR pszXmlName, BOOL bModal = FALSE );
    //析构函数
    virtual ~SouiDialog( void );
    //设置窗口标题
    void SetWindowTitle( LPCTSTR title );
    //获取窗口句柄
    HWND GetSafeHwnd() const;
    //标记为子窗口
    //理论上期望是可以嵌入到其他窗口使用,但目前尚不完善,慎用!
    void setAsChild( BOOL bChild );
    //是否模态对话框?
    BOOL isModal() const;
    //运行对话框
    //注:非模态对话框的返回值没有意义,可以忽略
    INT_PTR Run( HWND hParent = NULL );

    //模仿对话框的OK和Cancel按钮处理
protected:
    void OnOK();
    void OnCancel();

    /** 窗口消息 */
protected:
    //对话框初始化过程
    LRESULT OnInitDialog( HWND hWnd, LPARAM lParam );
    //实现窗口的动画启动效果(从小变大的过程)
    //注:只有模态对话框才具备这个效果
    void OnShowWindow( BOOL bShow, UINT nStatus );
    //设置Aero特效(默认不使用,如果要使用该特性,请取消所有与OnCreate相关的代码注释)
    //int OnCreate(LPCREATESTRUCT lpCreateStruct);
    //非模态窗口的销毁处理
    //参考1:http://bbs.csdn.net/topics/350048650
    //参考2:http://blog.csdn.net/candyliuxj/article/details/6736032
    //参考3:http://blog.csdn.net/xiliang_pan/article/details/7178601
    //注1:soui没有PostNcDestory虚函数,用OnFinalMessage虚函数替代!!!
    //注2:如果响应WM_NCDESTORY消息,在该消息中delete this,会导致内存错误!!!
    virtual void OnFinalMessage( HWND hWnd );
    //手动添加的虚函数(用于在窗口销毁或关闭前做一些清理工作,默认什么也不做)
    virtual void OnDestroyWindow();
    //窗口关闭消息
    void OnClose();
    //窗口大小位置变化(最大/最小/复原这3个按钮要同步变化尺寸)
    void OnSize( UINT nType, SOUI::CSize size );

    /** 鼠标消息 */
protected:
    //鼠标移动消息(用于判断鼠标是否在窗口内)
    //参考:http://www.cnblogs.com/greatverve/archive/2013/02/06/TRACKMOUSEEVENT.html
    void OnMouseMove( UINT nFlags, SOUI::CPoint point );
    void OnMouseHover( WPARAM wParam, SOUI::CPoint point );
    void OnMouseLeave();

    /** 标题栏4个按钮消息 */
protected:
    //void OnClose(); //和窗口消息WM_CLOSE响应函数重名!
    void OnMaximize();
    void OnRestore();
    void OnMinimize();

    /** 键盘消息 */
protected:
    void OnChar( UINT nChar, UINT nRepCnt, UINT nFlags );

    /** 普通函数 */
protected:
    BOOL isLayoutInited() const;
    BOOL keepFocus() const;

    /** 成员变量 */
private:
    //是否子窗口(默认FALSE)
    BOOL m_bChild;
    //是否模态对话框(默认非模态FALSE)
    BOOL m_bModal;
    //UI完成布局标志
    BOOL m_bLayoutInited;
    //鼠标是否在窗口内
    BOOL m_mouseInWindow;
    //是否需要追踪鼠标移动消息
    BOOL m_bTracking;
    //窗口标题
    SOUI::SStringT m_title;

    /** 控件消息映射表 */
    EVENT_MAP_BEGIN()
    //标题栏的4个按钮消息(xml布局文件中必须用这4个名字!!!)
    EVENT_NAME_COMMAND( _T( "btn_close" ), OnClose )
    EVENT_NAME_COMMAND( _T( "btn_max" ), OnMaximize )
    EVENT_NAME_COMMAND( _T( "btn_restore" ), OnRestore )
    EVENT_NAME_COMMAND( _T( "btn_min" ), OnMinimize )
    EVENT_MAP_END()

    /** 窗口消息映射表 */
    BEGIN_MSG_MAP_EX( SouiDialog )
    MSG_WM_INITDIALOG( OnInitDialog )
    MSG_WM_SHOWWINDOW( OnShowWindow )
    MSG_WM_MOUSELEAVE( OnMouseLeave )
    MSG_WM_MOUSEHOVER( OnMouseHover )
    MSG_WM_MOUSEMOVE( OnMouseMove )
    MSG_WM_CHAR( OnChar )
    //MSG_WM_CREATE(OnCreate)
    MSG_WM_CLOSE( OnClose )
    MSG_WM_SIZE( OnSize )
    CHAIN_MSG_MAP( SOUI::SHostDialog )
    REFLECT_NOTIFICATIONS_EX()
    END_MSG_MAP()
};