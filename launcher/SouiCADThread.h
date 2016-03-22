#pragma once

#include "MonitorThread.h"
#include "SouiDialog.h"

class SouiCADThread : public MonitorThread
{
    //��ʵ����һ��ȫ�ֺ���,���ڱ�Ҳ����
    //����Ϊ�˷���,����ΪSouiAutoCADThread��ľ�̬��Ա������
public:
    static void RunCAD( SouiDialog* pWnd, const CString& dwgFile = _T( "" ) );

public:
    SouiCADThread( const CString& dwgFile = _T( "" ) );
    ~SouiCADThread( void );
    //������cadǰ��һЩ׼������(�滻cuix,�޸�ע�����Ϣ��)
    virtual LRESULT OnMonitorBegin( WPARAM wParam, LPARAM lParam );
    //��cad�رպ���һЩ������(��ԭcuix,�ָ�ע�����Ϣ��)
    virtual LRESULT OnMonitorEnd( WPARAM wParam, LPARAM lParam );

public:
    SouiDialog* pWnd;
};
