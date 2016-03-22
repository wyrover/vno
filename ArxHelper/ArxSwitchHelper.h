#pragma once

#include "dlimexp.h"

// 系统精度设置器
// 用于点坐标、向量的相等判断
class ARXHELPER_API ArxTolSetter
{
public:
    ArxTolSetter( double eq );
    void setEq( double eq );
    ~ArxTolSetter();
private:
    double m_originEq;
};

/*
使用方法:
ArxTolSetter ts(0.001); // 对象析构的时候自动还原系统误差

等价于:
// 备份系统误差
double ep = AcGeContext::gTol.equalPoint();
// 设置误差
AcGeContext::gTol.setEqualPoint(0.001); // 10-3

// do something
// ...

// 还原系统误差
AcGeContext::gTol.setEqualPoint(ep);
*/

//非模态下文档锁定切换
class ARXHELPER_API ArxDocLockSwitch
{
public:
    ArxDocLockSwitch();
    ~ArxDocLockSwitch();
};

//切换controlbar显示
class ARXHELPER_API ArxCtrlBarShowSwitch
{
public:
    //构造函数隐藏controlbar
    ArxCtrlBarShowSwitch( CWnd* _dlg );
    //析构函数显示controlbar
    ~ArxCtrlBarShowSwitch();

private:
    static void ShowParentControlBar( CWnd* pWnd, BOOL bShow );
    CWnd* dlg;
};

//切换窗口显示/隐藏
class ARXHELPER_API ArxDialogShowSwitch
{
public:
    //构造函数隐藏
    ArxDialogShowSwitch( CWnd* _dlg );
    //析构函数显示
    ~ArxDialogShowSwitch();
    CWnd* dlg;
};