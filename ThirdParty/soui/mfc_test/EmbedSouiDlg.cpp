#include "stdafx.h"
#include "mfc_test.h"
#include "EmbedSouiDlg.h"
#include "SouiXmlName.h"

// EmbedSouiDlg 对话框
IMPLEMENT_DYNAMIC(EmbedSouiDlg, CDialog)

EmbedSouiDlg::EmbedSouiDlg(CWnd* pParent /*=NULL*/)
	: CDialog(EmbedSouiDlg::IDD, pParent), dlg(RES_NAME, FALSE)
{

}

EmbedSouiDlg::~EmbedSouiDlg()
{
}

void EmbedSouiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(EmbedSouiDlg, CDialog)
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEHOVER()
END_MESSAGE_MAP()


// EmbedSouiDlg 消息处理程序

BOOL EmbedSouiDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	dlg.setAsChild(TRUE);
	dlg.Run(GetSafeHwnd());
	//dlg.Create(GetSafeHwnd(), WS_VISIBLE | WS_CHILD | WS_CLIPCHILDREN, NULL, 0,0,0,0);
	//dlg.SendMessage(WM_INITDIALOG);
	//dlg.CenterWindow();
	//dlg.ShowWindow(SW_SHOW);

	SOUI::CRect rect;
	dlg.SWindow::GetWindowRect(&rect);
	rect.bottom += 15;
	MoveWindow(&rect);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

BOOL EmbedSouiDlg::PreTranslateMessage(MSG* pMsg)
{
	//对话框的按键处理 PreTranslateMessage、OnKeyDown和OnChar
	//http://blog.csdn.net/wang_cong0214/article/details/8280324
	//soui窗口作为mfc窗口的子窗口的时候,当我们按一个键的时候
	//mfc内部的PreTranslateMessage会过滤掉WM_CHAR消息,导致soui接收不到WM_CHAR消息,使得edit无法输入文字
	if(pMsg->message == WM_CHAR)
	{
		return dlg.SendMessage(pMsg->message, pMsg->wParam, pMsg->lParam);
	}
	else
	{
		return CDialog::PreTranslateMessage(pMsg);
	}
}

void EmbedSouiDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnMouseMove(nFlags, point);
}

void EmbedSouiDlg::OnMouseLeave()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnMouseLeave();
}

void EmbedSouiDlg::OnMouseHover(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnMouseHover(nFlags, point);
}
