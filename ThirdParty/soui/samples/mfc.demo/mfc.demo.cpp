
// mfc.demo.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "mfc.demo.h"
#include "mfc.demoDlg.h"
#include "SouiRealWndHandler.h"
#include <res.mgr/sobjdefattr.h>
#include <com-cfg.h>
#include <com-loader.hpp>

#include <helper/MenuWndHook.h>
#include <helper/mybuffer.h>


using namespace SOUI;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifdef _DEBUG
#define COM_IMGDECODER  _T("imgdecoder-wicd.dll")
#define COM_RENDER_GDI  _T("render-gdid.dll")
#else
#define COM_IMGDECODER  _T("imgdecoder-wic.dll")
#define COM_RENDER_GDI  _T("render-gdi.dll")
#endif


#ifdef _DEBUG
#define SYS_NAMED_RESOURCE _T("soui-sys-resourced.dll")
#else
#define SYS_NAMED_RESOURCE _T("soui-sys-resource.dll")
#endif

#define RES_TYPE 0   //���ļ��м�����Դ
// #define RES_TYPE 1   //��PE��Դ�м���UI��Դ
// #define RES_TYPE 2   //��zip���м�����Դ

class SoUILoader
{
public:
	SoUILoader(HINSTANCE _hInstance) : hInstance(_hInstance), pSouiApp(0)
	{
		HRESULT hRes = CoInitialize(NULL);
		SASSERT(SUCCEEDED(hRes));
		//�͹ٷ���������Щ��ͬ
		//��SetCurrentDirectoryǰ����dll
		hSysResource=LoadLibrary(SYS_NAMED_RESOURCE);
	}

	~SoUILoader()
	{
		hInstance = 0; hSysResource = 0;
		delete pSouiApp; pSouiApp = 0;
		//ж�ز˵��߿����hook
		CMenuWndHook::UnInstallHook();
		CoUninitialize();
	}

	SComMgr* getComMrg()
	{
		return &comMgrObj;
	}

	LPCTSTR getSkinDir() const
	{
		return _T("res");
	}

	bool initRender()
	{
		//����render���(render_gdi��render_skia)
		//bLoaded = pComMgr->CreateRender_Skia((IObjRef**)&pRenderFactory)
		BOOL bLoaded = getComMrg()->CreateRender_GDI((IObjRef**)&pRenderFactory);
		SASSERT_FMT(bLoaded,_T("load interface [%s] failed!"),_T("render-gdi"));

		//����ͼƬ����ģ��(imggid��imgwic)
		bLoaded=getComMrg()->CreateImgDecoder((IObjRef**)&pImgDecoderFactory);
		SASSERT_FMT(bLoaded,_T("load interface [%s] failed!"), _T("imgdecoder"));

		//Ϊ��Ⱦģ����������Ҫ���õ�ͼƬ����ģ��
		if(bLoaded == TRUE)
		{
			pRenderFactory->SetImgDecoderFactory(pImgDecoderFactory);
		}
		return bLoaded == TRUE;
	}

	bool initApp()
	{
		if(pSouiApp == 0)
		{
			pSouiApp=new SApplication(pRenderFactory, hInstance);
			SStringT strResDir = pSouiApp->GetAppDir();
			strResDir += getSkinDir();
			//�����������·���޸ĵ�demo���ڵ�Ŀ¼
			//ע��:������ڼ���soui-sys-resource.dll֮������,����souiϵͳ��Դ���ػ�ʧ��!!!
			SetCurrentDirectory(strResDir);
			//SOUIϵͳ���Ǵ�appdirȥ������Դ
			//ע:���˵���ǲ�׼ȷ��,soui��Դ�����в�û��ʹ��GetAppDir(),��Ҫ��������SetCurrentDirectory()���õ�ǰ·��
			pSouiApp->SetAppDir(strResDir);
		}
		return true;
	}

	bool initResource()
	{
		//����һ�˸���Դ�ṩ����,SOUIϵͳ��ʵ����3����Դ���ط�ʽ���ֱ��Ǵ��ļ����أ���EXE����Դ���ؼ���ZIPѹ��������
		CAutoRefPtr<IResProvider>   pResProvider;
		BOOL bLoaded = FALSE;

#if (RES_TYPE == 0)//���ļ�����
		CreateResProvider(RES_FILE,(IObjRef**)&pResProvider);
		bLoaded = pResProvider->Init((LPARAM)_T("uires"),0);
#elif (RES_TYPE==1)//��EXE��Դ����
		CreateResProvider(RES_PE,(IObjRef**)&pResProvider);
		bLoaded = pResProvider->Init((WPARAM)hInstance,0);
#elif (RES_TYPE==2)//��ZIP������
		bLoaded=getComMrg()->CreateResProvider_ZIP((IObjRef**)&pResProvider);
		SASSERT_FMT(bLoaded,_T("load interface [%s] failed!"),_T("resprovider_zip"));

		ZIPRES_PARAM param;
		param.ZipFile(pRenderFactory, _T("uires.zip"),"souizip");
		bLoaded = pResProvider->Init((WPARAM)&param,0);
		SASSERT(bLoaded);
#endif

		if(bLoaded == TRUE)
		{
			//��������IResProvider����SApplication����
			//����Դ����Ƥ��
			pSouiApp->AddResProvider(pResProvider);
		}
		return (bLoaded == TRUE);
	}

	bool initScripts()
	{
		BOOL bLoaded = FALSE;
#ifdef DLL_CORE
		//����LUA�ű�ģ�飬ע�⣬�ű�ģ��ֻ����SOUI�ں�����DLL��ʽ����ʱ����ʹ�á�
		bLoaded = getComMrg()->CreateScrpit_Lua((IObjRef**)&pScriptLua);
		SASSERT_FMT(bLoaded,_T("load interface [%s] failed!"),_T("scirpt_lua"));
		pSouiApp->SetScriptFactory(pScriptLua);
#endif//DLL_CORE

		return true;
	}

	bool initExtendControls()
	{
		//��SApplicationϵͳ��ע�����ⲿ��չ�Ŀؼ���SkinObj��
		//SWkeLoader wkeLoader;
		//if(wkeLoader.Init(_T("wke.dll")))        
		//{
		//	pSouiApp->RegisterWndFactory(TplSWindowFactory<SWkeWebkit>());//ע��WKE�����
		//}
		//pSouiApp->RegisterWndFactory(TplSWindowFactory<SGifPlayer>());//ע��GIFPlayer
		//pSouiApp->RegisterSkinFactory(TplSkinFactory<SSkinGif>());//ע��SkinGif
		//pSouiApp->RegisterSkinFactory(TplSkinFactory<SSkinAPNG>());//ע��SSkinAPNG
		//pSouiApp->RegisterSkinFactory(TplSkinFactory<SSkinVScrollbar>());//ע�����������Ƥ��

		//pSouiApp->RegisterWndFactory(TplSWindowFactory<SIPAddressCtrl>());//ע��IP�ؼ�
		//pSouiApp->RegisterWndFactory(TplSWindowFactory<SPropertyGrid>());//ע�����Ա�ؼ�
		//pSouiApp->RegisterWndFactory(TplSWindowFactory<SChromeTabCtrl>());//ע��ChromeTabCtrl
		//pSouiApp->RegisterWndFactory(TplSWindowFactory<SIECtrl>());//ע��IECtrl
		//pSouiApp->RegisterWndFactory(TplSWindowFactory<SChatEdit>());//ע��ChatEdit
		//pSouiApp->RegisterWndFactory(TplSWindowFactory<SScrollText>());//ע��SScrollText
		//pSouiApp->RegisterWndFactory(TplSWindowFactory<SListCtrlEx>());//ע��SListCtrlEx

		//if(SUCCEEDED(CUiAnimation::Init()))
		//{
		//	pSouiApp->RegisterWndFactory(TplSWindowFactory<SUiAnimationWnd>());//ע�ᶯ���ؼ�
		//}
		//pSouiApp->RegisterWndFactory(TplSWindowFactory<SFlyWnd>());//ע����ж����ؼ�
		//pSouiApp->RegisterWndFactory(TplSWindowFactory<SFadeFrame>());//ע�ὥ���������ؼ�
		//pSouiApp->RegisterWndFactory(TplSWindowFactory<SRadioBox2>());//ע��RadioBox2
		//pSouiApp->RegisterWndFactory(TplSWindowFactory<SCalendar2>());//ע��SCalendar2

		//SSkinGif::Gdiplus_Startup();
		return true;
	}

	bool initSysResource()
	{
		//����ϵͳ��Դ
		if(hSysResource == 0) return false;

		BOOL bLoaded = FALSE;
		CAutoRefPtr<IResProvider> sysSesProvider;
		CreateResProvider(RES_PE,(IObjRef**)&sysSesProvider);
		bLoaded = sysSesProvider->Init((WPARAM)hSysResource,0);

		if(bLoaded == TRUE)
		{
			pSouiApp->LoadSystemNamedResource(sysSesProvider);

			//����hook���Ʋ˵��ı߿�
			CMenuWndHook::InstallHook(hInstance,_T("_skin.sys.menu.border"));
		}

		return (bLoaded == TRUE);
	}

	bool initRealWnd()
	{
		//�����洰�ڴ���ӿ�
		CSouiRealWndHandler * pRealWndHandler = new CSouiRealWndHandler();
		pSouiApp->SetRealWndHandler(pRealWndHandler);
		pRealWndHandler->Release();
		return true;
	}

	bool initGlobalStyle()
	{
		//����ȫ����Դ����XML
		//��ʼ��SOUIȫ����Դ
		return (TRUE == pSouiApp->Init(_T("xml_init"), _T("xml"))); 
	}

private:
	HINSTANCE hInstance;                                //��ǰģ��(exe��dll�ľ��)
	HMODULE hSysResource;                               //souiϵͳ��Դdll�ľ��
	SComMgr comMgrObj;
	CAutoRefPtr<IImgDecoderFactory> pImgDecoderFactory; //ͼƬ������
	CAutoRefPtr<IRenderFactory> pRenderFactory;         //UI��Ⱦģ��,��render-gdi.dll��render-skia.dll�ṩ
	//CAutoRefPtr<ITranslatorMgr> trans;                //�����Է���ģ��,��translator.dll�ṩ
	CAutoRefPtr<IScriptFactory> pScriptLua;             //lua�ű�ģ��,��scriptmodule-lua.dll�ṩ
	SApplication* pSouiApp;
};


// CmfcdemoApp ����

CmfcdemoApp::CmfcdemoApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CmfcdemoApp ����

CmfcdemoApp theApp;


// CmfcdemoApp ��ʼ��

BOOL CmfcdemoApp::InitInstance()
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

	CWinApp::InitInstance();

	//HRESULT hRes = CoInitialize(NULL);
	//SASSERT(SUCCEEDED(hRes));

 //   {//��һ�����ź���Ҫ����֤���������ľֲ�������CoUninitialize()֮ǰ�ͷ�

 //       SComLoader imgDecLoader;
 //       SComLoader renderLoader;
 //       CAutoRefPtr<IImgDecoderFactory> pImgDecoderFactory;
 //       CAutoRefPtr<IRenderFactory> pRenderFactory;
 //       imgDecLoader.CreateInstance(COM_IMGDECODER,(IObjRef**)&pImgDecoderFactory);
 //       renderLoader.CreateInstance(COM_RENDER_GDI,(IObjRef**)&pRenderFactory);

 //       pRenderFactory->SetImgDecoderFactory(pImgDecoderFactory);

 //       SApplication *pSouiApp=new SApplication(pRenderFactory,theApp.m_hInstance);

 //       //����ϵͳ��Դ
 //       HMODULE hSysResource=LoadLibrary(SYS_NAMED_RESOURCE);
 //       if(hSysResource)
 //       {
 //           CAutoRefPtr<IResProvider> sysSesProvider;
 //           CreateResProvider(RES_PE,(IObjRef**)&sysSesProvider);
 //           sysSesProvider->Init((WPARAM)hSysResource,0);
 //           pSouiApp->LoadSystemNamedResource(sysSesProvider);
 //       }

 //       CAutoRefPtr<IResProvider>   pResProvider;
 //       CreateResProvider(RES_PE,(IObjRef**)&pResProvider);
 //       pResProvider->Init((WPARAM)theApp.m_hInstance,0);

 //       pSouiApp->AddResProvider(pResProvider);    //����Դ����Ƥ��

 //       //�����洰�ڴ���ӿ�
 //       CSouiRealWndHandler * pRealWndHandler = new CSouiRealWndHandler();
 //       pSouiApp->SetRealWndHandler(pRealWndHandler);
 //       pRealWndHandler->Release();

 //       pSouiApp->Init(_T("uidef"),_T("xml")); //��ʼ��SOUIȫ����Դ

	//    CmfcdemoDlg dlg;
	//    m_pMainWnd = &dlg;
	//    dlg.DoModal();
 //   	
 //       delete pSouiApp;

 //   }

	//CoUninitialize();

	//��arx�����ʵ�����ݹ���
	HINSTANCE hInstance = theApp.m_hInstance;

	SoUILoader suLoader(hInstance);
	if(!suLoader.initRender()) return FALSE;
	if(!suLoader.initApp()) return FALSE;
	if(!suLoader.initSysResource()) return FALSE;
	if(!suLoader.initResource()) return FALSE;
	if(!suLoader.initScripts()) return FALSE;
	if(!suLoader.initExtendControls()) return FALSE;
	if(!suLoader.initRealWnd()) return FALSE;
	if(!suLoader.initGlobalStyle()) return FALSE;

    CmfcdemoDlg dlg;
    m_pMainWnd = &dlg;
    dlg.DoModal();
   	
	return FALSE;
}
