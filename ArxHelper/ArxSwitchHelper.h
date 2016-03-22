#pragma once

#include "dlimexp.h"

// ϵͳ����������
// ���ڵ����ꡢ����������ж�
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
ʹ�÷���:
ArxTolSetter ts(0.001); // ����������ʱ���Զ���ԭϵͳ���

�ȼ���:
// ����ϵͳ���
double ep = AcGeContext::gTol.equalPoint();
// �������
AcGeContext::gTol.setEqualPoint(0.001); // 10-3

// do something
// ...

// ��ԭϵͳ���
AcGeContext::gTol.setEqualPoint(ep);
*/

//��ģ̬���ĵ������л�
class ARXHELPER_API ArxDocLockSwitch
{
public:
    ArxDocLockSwitch();
    ~ArxDocLockSwitch();
};

//�л�controlbar��ʾ
class ARXHELPER_API ArxCtrlBarShowSwitch
{
public:
    //���캯������controlbar
    ArxCtrlBarShowSwitch( CWnd* _dlg );
    //����������ʾcontrolbar
    ~ArxCtrlBarShowSwitch();

private:
    static void ShowParentControlBar( CWnd* pWnd, BOOL bShow );
    CWnd* dlg;
};

//�л�������ʾ/����
class ARXHELPER_API ArxDialogShowSwitch
{
public:
    //���캯������
    ArxDialogShowSwitch( CWnd* _dlg );
    //����������ʾ
    ~ArxDialogShowSwitch();
    CWnd* dlg;
};