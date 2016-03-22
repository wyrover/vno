#include "stdafx.h"
#include "SouiDialog.h"
using namespace SOUI;

//OnMouseMove��Ϣ�����õ���_TrackMouseEvent����
#include <CommCtrl.h>
#pragma comment(lib, "comctl32.lib")

//��OnCreate��Ϣ����������AeroЧ����Ҫdwmapi��֧��
//#include <dwmapi.h>
//#pragma comment(lib,"dwmapi.lib")

SouiDialog::SouiDialog(LPCTSTR pszXmlName, BOOL bModal) 
	: SHostDialog(pszXmlName), 
	  m_bLayoutInited(FALSE),
	  m_bModal(bModal),
	  m_mouseInWindow(TRUE), 
	  m_bTracking(FALSE),
	  m_bChild(FALSE)
{
}

SouiDialog::~SouiDialog(void)
{
}

HWND SouiDialog::GetSafeHwnd() const
{
	return m_hWnd;
}

void SouiDialog::SetWindowTitle(LPCTSTR title)
{
	m_title = title;
	//���ñ���
	SStatic* titleLabel = FindChildByName2<SStatic>(L"wnd_title");
	if(titleLabel != 0)
	{
		titleLabel->SetWindowText(m_title);
	}
}

void SouiDialog::setAsChild(BOOL bChild) 
{ 
	m_bChild = bChild; 
	if(bChild) m_bModal = FALSE;
}

INT_PTR SouiDialog::Run(HWND hParent)
{
	if(m_bModal)
	{
		return this->DoModal(hParent);
	}
	else
	{
		if(m_bChild)
		{
			Create(hParent,WS_VISIBLE | WS_CHILD | WS_CLIPCHILDREN, NULL, 0,0,0,0);
		}
		else
		{
			Create(hParent,0,0,0,0);
		}
		SendMessage(WM_INITDIALOG);
		//CenterWindow();
		return ShowWindow(SW_SHOWNORMAL);
	}
}

void SouiDialog::OnOK()
{
	if(m_bChild) return;

	m_bTracking = FALSE;
	if(m_bModal)
	{
		SHostDialog::OnOK();
	}
	else
	{
		DestroyWindow();
	}
}

void SouiDialog::OnCancel()
{
	if(m_bChild) return;

	m_bTracking = FALSE;
	OnDestroyWindow();
	if(m_bModal)
	{
		SHostDialog::OnCancel();
	}
	else
	{
		//���������Ϊ��,��ô�����������
		//���ٴ��ں�Ӧ�˳�����
		if(::GetParent(m_hWnd) == NULL)
		{
			PostMessage(WM_QUIT);
		}
		else
		{
			DestroyWindow();
		}
	}
}

LRESULT SouiDialog::OnInitDialog( HWND hWnd, LPARAM lParam )
{
	m_bLayoutInited = TRUE;
	if(m_title.GetLength() > 0)
	{
		this->SetWindowTitle(m_title);
	}
	return FALSE;
}

void SouiDialog::OnFinalMessage( HWND hWnd )
{
	SHostDialog::OnFinalMessage(hWnd);
	if(!m_bModal && !m_bChild)
	{
		//һ���ģ̬�ĶԻ�����new������,��ģ̬���Ǿֲ�����
		delete this;
	}
}

void SouiDialog::OnDestroyWindow()
{
}

static void SetVisible_Helper(SWindow* wnd, BOOL bVisible)
{
	if(wnd != 0)
	{
		wnd->SetVisible(bVisible);
	}
}

void SouiDialog::OnSize(UINT nType, SOUI::CSize size)
{
	SetMsgHandled(FALSE);   //��һ�к���Ҫ����֤��Ϣ�������ݸ�SOUI::SHostDialog������ȻҲ������SouiDialog::OnSize(nType,size);���棬��������ʹ�õķ������򵥣�ͨ��
	if(!m_bLayoutInited) return;

	/**
	 *���if������ڴ�����󻯺ͻ�ԭ��ʱ��,��������2����ť����ʾ״̬
	 �÷���Ҫ���������4����ť�ù涨��name��������
		<imgbtn name="btn_close" skin="_skin.sys.btn.close"    pos="-45,0" tip="close" animate="1"/>
		<imgbtn name="btn_max" skin="_skin.sys.btn.maximize"  pos="-83,0" animate="1" />
		<imgbtn name="btn_restore" skin="_skin.sys.btn.restore"  pos="-83,0" show="0" animate="1" />
		<imgbtn name="btn_min" skin="_skin.sys.btn.minimize" pos="-121,0" animate="1" />
	*/
	if(nType==SIZE_MAXIMIZED)
	{
		SetVisible_Helper(FindChildByName(_T("btn_restore")), TRUE);
		SetVisible_Helper(FindChildByName(_T("btn_max")), FALSE);
	}
	else if(nType==SIZE_RESTORED)
	{
		SetVisible_Helper(FindChildByName(_T("btn_restore")), FALSE);
		SetVisible_Helper(FindChildByName(_T("btn_max")), TRUE);
	}
}

void SouiDialog::OnShowWindow( BOOL bShow, UINT nStatus )
{
	SetMsgHandled(FALSE);
	//if(m_bModal && bShow)
	//{
	//	//���д�����ʵ�ִ��ڵĶ�������Ч������С���Ĺ��̣�
	//	AnimateHostWindow(200, AW_CENTER);
	//}
}

//int SouiDialog::OnCreate( LPCREATESTRUCT lpCreateStruct )
//{
//	//����AeroЧ��
//	//MARGINS mar = {5,5,30,5};
//	//DwmExtendFrameIntoClientArea ( m_hWnd, &mar );
//
//	SetMsgHandled(FALSE);
//	return 0;
//}

void SouiDialog::OnClose()
{
	m_bTracking = FALSE;
	SouiDialog::OnCancel();
}

void SouiDialog::OnMaximize()
{
	GetNative()->SendMessage(WM_SYSCOMMAND,SC_MAXIMIZE);
}

void SouiDialog::OnRestore()
{
	GetNative()->SendMessage(WM_SYSCOMMAND,SC_RESTORE);
}

void SouiDialog::OnMinimize()
{
	GetNative()->SendMessage(WM_SYSCOMMAND,SC_MINIMIZE);
}

void SouiDialog::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if(nChar == VK_ESCAPE) 
	{
		SetMsgHandled(TRUE);
		OnClose();
	}
	else
	{
		SetMsgHandled(FALSE);
	}
}

BOOL SouiDialog::isLayoutInited() const
{
	return m_bLayoutInited;
}

BOOL SouiDialog::isModal() const
{
	return m_bModal;
}

BOOL SouiDialog::keepFocus() const
{
	return isModal()?TRUE:m_mouseInWindow;
}

void SouiDialog::OnMouseMove(UINT nFlags, SOUI::CPoint point)
{
	SetMsgHandled(FALSE);
	if(isModal()) return;

	if (!m_bTracking)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(TRACKMOUSEEVENT);
		tme.dwFlags = TME_LEAVE | TME_HOVER;//Ҫ��������Ϣ
		tme.hwndTrack = this->m_hWnd;
		tme.dwHoverTime = 50;// ������˲��������޷�����mouseHover

		if (::_TrackMouseEvent(&tme)) //MOUSELEAVE|MOUSEHOVER��Ϣ�ɴ˺�������
		{
			m_bTracking = TRUE;   
		}
	}
}

void SouiDialog::OnMouseLeave()
{
	SetMsgHandled(FALSE);
	if(isModal()) return;

	m_bTracking = FALSE;
	m_mouseInWindow = FALSE;
}

void SouiDialog::OnMouseHover(WPARAM wParam, SOUI::CPoint point)
{
	SetMsgHandled(FALSE);
	if(isModal()) return;

	m_bTracking = FALSE;
	m_mouseInWindow = TRUE;
}
