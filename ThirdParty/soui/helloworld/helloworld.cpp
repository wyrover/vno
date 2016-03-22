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
	//dlg->SetWindowTitle(_T("�ı���,�������!"));
	if(dlg->isModal() == TRUE)
	{
		dlg->Run(hParent);
	}
	else
	{
		dlg->Run(hParent);
		//������Ϊ0��һ�㶼��������
		if(hParent == NULL)
		{
			//ֻ�������ڲ���Ҫ��getApp()->Run()������Ϣѭ��
			//MFC��InitInstance()����ִ�е�ʱ��,��ʱ��û����Ϣѭ��,���Ҫ��ʾ������,��ô��Ҫ�����˹�������Ϣѭ��
			//ͬ��,win32�����WinMain������������Ҳ����Ҫ�Ⱥ�MFC�����������Ϣѭ����,����Ҫ��getApp()->Run()������Ϣѭ��
			SoUILoader::getSingletonPtr()->getApp()->Run(dlg->m_hWnd);
		}
	}
}

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPTSTR lpCmdLine, int nCmdShow)
{
	InitSouiEnviroment(hInstance);
	if(1)
	{
		//��ģ̬��ʽ����
		SouiDialog dlg(_T("layout:main"), TRUE);
		StartFromSoui(&dlg, NULL);
	}
	else
	{
		// �����Է�ģ̬��ʽ����
		SouiDialog* dlg = new SouiDialog(_T("layout:main"), FALSE);
		StartFromSoui(dlg, NULL);
	}
	UnInitSouiEnviroment();

	return 0;
}