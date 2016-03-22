#pragma once

// 自定义消息 -- 开始监控
#define WM_BEGIN_MONITOR WM_USER+100
// 自定义消息 -- 结束监控
#define WM_END_MONITOR WM_USER+101

class MonitorThread;

//线程数据
struct MonitorThreadData
{
    HANDLE hThread;  // 要监视的exe程序(线程句柄)
    HANDLE hProcess; // 要监视的exe程序(进程句柄)
    HWND hWnd;       // 窗口句柄
    MonitorThread* monitor; // 监视器
    void* value;      // 任意数据
};

/*
参考:
	http://www.cnblogs.com/pugang/archive/2012/08/24/2654278.html
	http://blog.csdn.net/gencheng/article/details/9376899
消息队列是属于线程的，Post消息就是把消息放到目标线程的消息队列中。
这两者的区别在于，PostMessage通过指定目标窗口句柄来确定目标线程，
通常情况下由窗口过程来处理消息；PostThreadMessage直接指定线程ID来确定目标线程，
没有目标窗口，只能在消息循环中直接根据消息类型做相应的处理。
在程序设计的选择方面，如果是UI线程，则应使用PostMessage；
如果是工作线程，则应使用PostThreadMessage，不要为了接收消息而创建窗口。
*/

//该类表示监视某个exe程序的线程
class MonitorThread
{
public:
    static HANDLE GetProcess();
    // 用户是否要求线程结束
    static bool IsAskForEnd();
    // 设置线程结束标记
    static void AskForEnd( bool flag );

public:
    //虚析构函数
    virtual ~MonitorThread( void ) {}
    //消息处理: 进程运行之前的准备工作(派生类应重载该函数)
    virtual LRESULT OnMonitorBegin( WPARAM wParam, LPARAM lParam );
    //消息处理: 进程结束后的收尾清理工作(派生类应重载该函数)
    virtual LRESULT OnMonitorEnd( WPARAM wParam, LPARAM lParam );

public:
    //设置exe程序路径
    void SetExePath( const CString& exePath )
    {
        m_exePath = exePath;
    }
    //设置命令行参数
    void SetCmdLine( const CString& cmdLine )
    {
        m_cmdLine = cmdLine;
    }
    //设置进程的工作路径
    void SetWorkDirectory( const CString& workDir )
    {
        m_workDir = workDir;
    }
    //显示/隐藏进程窗口
    void ShowWindow( bool bShow )
    {
        m_bShow = bShow;
    }
    //关联窗口
    void SetWndHandle( HWND hWnd )
    {
        m_hWnd = hWnd;
    }
    //运行
    bool Run( HANDLE& hThread );

protected:
    //构造函数
    MonitorThread();

    //要监控的exe程序路径
    CString m_exePath;
    //命令行参数
    CString m_cmdLine;
    //窗口句柄
    HWND m_hWnd;
    //exe程序的当前工作路径
    CString m_workDir;
    //是否隐藏exe程序的窗口(默认显示-true)
    bool m_bShow;
    //用户要求结束线程
    static bool thread_end;
    // 全局线程数据
    static MonitorThreadData thread_data;
};
