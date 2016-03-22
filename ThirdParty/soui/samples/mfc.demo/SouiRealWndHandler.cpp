#include "StdAfx.h"
#include "SouiRealWndHandler.h"

namespace SOUI
{
    CSouiRealWndHandler::CSouiRealWndHandler(void)
    {
    }

    CSouiRealWndHandler::~CSouiRealWndHandler(void)
    {
    }

    HWND CSouiRealWndHandler::OnRealWndCreate( SRealWnd *pRealWnd )
    {
        const SRealWndParam &param=pRealWnd->GetRealWndParam();
        if(param.m_strClassName==_T("button"))
        {//ֻʵ����button�Ĵ���
            //����һ��MFC CButton����
            CButton *pbtn=new CButton;
            //����CButton����,ע��ʹ��pRealWnd->GetContainer()->GetHostHwnd()��ΪCButton�ĸ�����
            //��pRealWnd->GetID()��Ϊ�洰�ڵ�ID
            pbtn->Create(param.m_strWindowName,WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,::CRect(0,0,0,0),CWnd::FromHandle(pRealWnd->GetContainer()->GetHostHwnd()),pRealWnd->GetID());
            //��pbtn��ָ��ŵ�SRealWnd��Data�б��棬�Ա��ڴ���destroyʱ�ͷ�pbtn����
            pRealWnd->SetData(pbtn);
            //���سɹ�������Ĵ��ھ��
            return pbtn->m_hWnd;
        }else
        {
            return 0;
        }
    }

    void CSouiRealWndHandler::OnRealWndDestroy( SRealWnd *pRealWnd )
    {
        const SRealWndParam &param=pRealWnd->GetRealWndParam();
        if(param.m_strClassName==_T("button"))
        {//�����洰�ڣ��ͷŴ���ռ�õ��ڴ�
            CButton *pbtn=(CButton*) pRealWnd->GetData();
            if(pbtn)
            {
                pbtn->DestroyWindow();
                delete pbtn;
            }
        }
    }
    
    //����������FALSE
    BOOL CSouiRealWndHandler::OnRealWndSize( SRealWnd *pRealWnd )
    {
        return FALSE;
    }

    //����������FALSE
    BOOL CSouiRealWndHandler::OnRealWndInit( SRealWnd *pRealWnd )
    {
        return FALSE;
    }
}
