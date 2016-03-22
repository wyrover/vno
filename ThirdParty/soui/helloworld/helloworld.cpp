#include "stdafx.h"
#include "helloworld.h"
#include "MySoUiLoader.h"
#include "SouiDialog.h"
//#include "SouiXmlName.h"

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

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPTSTR lpCmdLine, int nCmdShow)
{
	InitSouiEnviroment(hInstance);
	if(1)
	{
		//以模态方式启动
		SouiDialog dlg(_T("layout:main"), TRUE);
		StartFromSoui(&dlg, NULL);
	}
	else
	{
		// 或者以非模态方式启动
		SouiDialog* dlg = new SouiDialog(_T("layout:main"), FALSE);
		StartFromSoui(dlg, NULL);
	}
	UnInitSouiEnviroment();

	return 0;
}