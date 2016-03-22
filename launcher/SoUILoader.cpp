#include "stdafx.h"
#include "SoUILoader.h"
using namespace SOUI;

//#define RES_TYPE 0   //���ļ��м�����Դ
#define RES_TYPE 1   //��PE��Դ�м���UI��Դ
// #define RES_TYPE 2   //��zip���м�����Դ

#ifdef _DEBUG
#define SYS_NAMED_RESOURCE _T("soui-sys-resourced.dll")
#else
#define SYS_NAMED_RESOURCE _T("soui-sys-resource.dll")
#endif

//��ʼ������ģʽ�ľ�̬��Ա����
template<> SoUILoader* Singleton<SoUILoader>::ms_Singleton = 0;

SoUILoader::SoUILoader( HINSTANCE _hInstance ) : hInstance( _hInstance ), pSouiApp( 0 )
{
    HRESULT hRes = CoInitialize( NULL );
    SASSERT( SUCCEEDED( hRes ) );
}

SoUILoader::~SoUILoader()
{
    hInstance = 0;
    delete pSouiApp;
    pSouiApp = 0;
    //ж�ز˵��߿����hook
    CMenuWndHook::UnInstallHook();
    CoUninitialize();
}

SComMgr* SoUILoader::getComMrg()
{
    return &comMgrObj;
}

SApplication* SoUILoader::getApp()
{
    return pSouiApp;
}

bool SoUILoader::init()
{
    if( !initRender() ) return false;
    if( !initApp() ) return false;
    if( !initResource() ) return false;
    if( !initScripts() ) return false;
    if( !initExtendControls() ) return false;
    if( !initRealWnd() ) return false;
    if( !initSysResource() ) return false;
    if( !initGlobalStyle() ) return false;
    return true;
}

//����uires�ļ��е�����·��
LPCTSTR SoUILoader::getSkinDir() const
{
    return _T( "" );
}

bool SoUILoader::initRender()
{
    //����render���(render_gdi��render_skia)
    //bLoaded = pComMgr->CreateRender_Skia((IObjRef**)&pRenderFactory)
    BOOL bLoaded = getComMrg()->CreateRender_GDI( ( IObjRef** )&pRenderFactory );
    SASSERT_FMT( bLoaded, _T( "load interface [%s] failed!" ), _T( "render-gdi" ) );

    //����ͼƬ����ģ��(imggid��imgwic)
    bLoaded = getComMrg()->CreateImgDecoder( ( IObjRef** )&pImgDecoderFactory );
    SASSERT_FMT( bLoaded, _T( "load interface [%s] failed!" ), _T( "imgdecoder" ) );

    //Ϊ��Ⱦģ����������Ҫ���õ�ͼƬ����ģ��
    if( bLoaded == TRUE )
    {
        pRenderFactory->SetImgDecoderFactory( pImgDecoderFactory );
    }
    return bLoaded == TRUE;
}

bool SoUILoader::initApp()
{
    pSouiApp = new SApplication( pRenderFactory, hInstance );
    SStringT strResDir = pSouiApp->GetAppDir();
    if( strResDir.GetAt( strResDir.GetLength() - 1 ) != _T( '\\' ) )
    {
        strResDir += _T( "\\" );
    }
    strResDir += getSkinDir();
    //�����������·���޸ĵ�demo���ڵ�Ŀ¼
    //ĳЩ���������ʹ��SetCurrentDirectory�ᵼ�³���Ī������Ĺҵ�(����!)
    //SetCurrentDirectory(strResDir);
    //SOUIϵͳ���Ǵ�appdirȥ������Դ
    //ע:���˵���ǲ�׼ȷ��,soui��Դ�����в�û��ʹ��GetAppDir(),��Ҫ��������SetCurrentDirectory()���õ�ǰ·��
    //����initResource()��ʱ��,�����ʹ�þ���·��,�������Աܿ�SetCurrentDirectory()��Ӱ��
    pSouiApp->SetAppDir( strResDir );
    return true;
}

bool SoUILoader::initResource()
{
    //����һ����Դ�ṩ����,SOUIϵͳ��ʵ����3����Դ���ط�ʽ
    //�ֱ��Ǵ��ļ����أ���EXE����Դ���ؼ���ZIPѹ��������
    CAutoRefPtr<IResProvider>   pResProvider;
    BOOL bLoaded = FALSE;

#if (RES_TYPE == 0)//���ļ�����
    CreateResProvider( RES_FILE, ( IObjRef** )&pResProvider );
    SStringT skinDir = getApp()->GetAppDir() + _T( "\\uires" );
    bLoaded = pResProvider->Init( ( LPARAM )( LPCTSTR )skinDir, 0 );
#elif (RES_TYPE==1)//��EXE��Դ����
    CreateResProvider( RES_PE, ( IObjRef** )&pResProvider );
    bLoaded = pResProvider->Init( ( WPARAM )hInstance, 0 );
#elif (RES_TYPE==2)//��ZIP������
    bLoaded = getComMrg()->CreateResProvider_ZIP( ( IObjRef** )&pResProvider );
    SASSERT_FMT( bLoaded, _T( "load interface [%s] failed!" ), _T( "resprovider_zip" ) );

    ZIPRES_PARAM param;
    param.ZipFile( pRenderFactory, _T( "uires.zip" ), "souizip" );
    bLoaded = pResProvider->Init( ( WPARAM )&param, 0 );
    SASSERT( bLoaded );
#endif

    if( bLoaded == TRUE )
    {
        //��������IResProvider����SApplication����
        //����Դ����Ƥ��
        pSouiApp->AddResProvider( pResProvider );
    }
    return ( bLoaded == TRUE );
}

bool SoUILoader::initScripts()
{
    BOOL bLoaded = FALSE;
#ifdef DLL_CORE
    //����LUA�ű�ģ�飬ע�⣬�ű�ģ��ֻ����SOUI�ں�����DLL��ʽ����ʱ����ʹ�á�
    bLoaded = getComMrg()->CreateScrpit_Lua( ( IObjRef** )&pScriptLua );
    SASSERT_FMT( bLoaded, _T( "load interface [%s] failed!" ), _T( "scirpt_lua" ) );
    pSouiApp->SetScriptFactory( pScriptLua );
#endif//DLL_CORE

    return true;
}

bool SoUILoader::initExtendControls()
{
    return true;
}

bool SoUILoader::initSysResource()
{
    //����ϵͳ��Դ
    //��DLL����ϵͳ��Դ
    HMODULE hModSysResource = LoadLibrary( SYS_NAMED_RESOURCE );
    if ( hModSysResource )
    {
        CAutoRefPtr<IResProvider> sysResProvider;
        CreateResProvider( RES_PE, ( IObjRef** )&sysResProvider );
        bool bRet = ( sysResProvider->Init( ( WPARAM )hModSysResource, 0 ) == TRUE );
        if( bRet )
        {
            getApp()->LoadSystemNamedResource( sysResProvider );
            //����hook���Ʋ˵��ı߿�
            CMenuWndHook::InstallHook( hInstance, _T( "_skin.sys.menu.border" ) );
        }
        FreeLibrary( hModSysResource );
        return bRet;
    }
    else
    {
        return false;
    }
}

bool SoUILoader::initRealWnd()
{
    return true;
}

bool SoUILoader::initGlobalStyle()
{
    //����ȫ����Դ����XML
    //��ʼ��SOUIȫ����Դ
    return ( TRUE == pSouiApp->Init( _T( "xml_init" ), _T( "uidef" ) ) );
}

