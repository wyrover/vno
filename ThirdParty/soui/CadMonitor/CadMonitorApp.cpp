#include "stdafx.h"
#include "CadMonitorApp.h"
#include "MySoUiLoader.h"
#include "MonitorDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CCadMonitorApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

CCadMonitorApp::CCadMonitorApp()
{
}

// 唯一的一个 CCadMonitorApp 对象
CCadMonitorApp theApp;

static void InitSouiEnviroment(HINSTANCE hInstance)
{
	new MySoUiLoader(hInstance);
	SoUILoader::getSingletonPtr()->init();
}

static void UnInitSouiEnviroment()
{
	delete SoUILoader::getSingletonPtr();
}

static void StartFromSoui(SouiDialog* dlg, HWND hParent=NULL)
{
	//dlg->SetWindowTitle(_T("改标题,随便玩玩!"));
	if(dlg->isModal() == TRUE)
	{
		dlg->Run(hParent);
	}
	else
	{
		dlg->Run(hParent);
		//父窗口为0的一般都是主窗口
		if(hParent == NULL)
		{
			//只有主窗口才需要用getApp()->Run()启动消息循环
			//MFC的InitInstance()函数执行的时候,此时还没有消息循环,如果要显示主窗口,那么需要我们人工启动消息循环
			//同理,win32程序的WinMain函数中主窗口也是需要等候MFC程序本身就有消息循环了,不需要用getApp()->Run()启动消息循环
			SoUILoader::getSingletonPtr()->getApp()->Run(dlg->m_hWnd);
		}
	}
}

static void StartFromMFC(CDialog* dlg)
{
	//设置MFC主窗口
	AfxGetApp()->m_pMainWnd = dlg;
	//进入模态消息循环,直到关闭对话框
	INT_PTR nResponse = dlg->DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
}

BOOL CCadMonitorApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);
	CWinAppEx::InitInstance();
	AfxEnableControlContainer();
	AfxInitRichEdit2();
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	InitSouiEnviroment(m_hInstance);

	if(IDYES == MessageBox(NULL, _T("启动模态 或者 非模态???"), _T("询问"), MB_YESNO))
	{
		//以模态方式启动
		MonitorDialog dlg(TRUE);
		StartFromSoui(&dlg, NULL);
	}
	else
	{
		//或者以非模态方式启动
		MonitorDialog* dlg = new MonitorDialog(FALSE);
		StartFromSoui(dlg, NULL);
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}
