#pragma once

#include "MonitorThread.h"
#include "SouiDialog.h"

class SouiCADThread : public MonitorThread
{
    //其实这是一个全局函数,放在别处也可以
    //这里为了方便,就作为SouiAutoCADThread类的静态成员函数了
public:
    static void RunCAD( SouiDialog* pWnd, const CString& dwgFile = _T( "" ) );

public:
    SouiCADThread( const CString& dwgFile = _T( "" ) );
    ~SouiCADThread( void );
    //在启动cad前做一些准备工作(替换cuix,修改注册表信息等)
    virtual LRESULT OnMonitorBegin( WPARAM wParam, LPARAM lParam );
    //在cad关闭后做一些清理工作(还原cuix,恢复注册表信息等)
    virtual LRESULT OnMonitorEnd( WPARAM wParam, LPARAM lParam );

public:
    SouiDialog* pWnd;
};
