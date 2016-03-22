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

// Ψһ��һ�� CCadMonitorApp ����
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

static void StartFromMFC(CDialog* dlg)
{
	//����MFC������
	AfxGetApp()->m_pMainWnd = dlg;
	//����ģ̬��Ϣѭ��,ֱ���رնԻ���
	INT_PTR nResponse = dlg->DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
}

BOOL CCadMonitorApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);
	CWinAppEx::InitInstance();
	AfxEnableControlContainer();
	AfxInitRichEdit2();
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	InitSouiEnviroment(m_hInstance);

	if(IDYES == MessageBox(NULL, _T("����ģ̬ ���� ��ģ̬???"), _T("ѯ��"), MB_YESNO))
	{
		//��ģ̬��ʽ����
		MonitorDialog dlg(TRUE);
		StartFromSoui(&dlg, NULL);
	}
	else
	{
		//�����Է�ģ̬��ʽ����
		MonitorDialog* dlg = new MonitorDialog(FALSE);
		StartFromSoui(dlg, NULL);
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}
