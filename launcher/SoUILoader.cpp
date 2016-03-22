#include "stdafx.h"
#include "SoUILoader.h"
using namespace SOUI;

//#define RES_TYPE 0   //从文件中加载资源
#define RES_TYPE 1   //从PE资源中加载UI资源
// #define RES_TYPE 2   //从zip包中加载资源

#ifdef _DEBUG
#define SYS_NAMED_RESOURCE _T("soui-sys-resourced.dll")
#else
#define SYS_NAMED_RESOURCE _T("soui-sys-resource.dll")
#endif

//初始化单例模式的静态成员变量
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
    //卸载菜单边框绘制hook
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

//设置uires文件夹的所在路径
LPCTSTR SoUILoader::getSkinDir() const
{
    return _T( "" );
}

bool SoUILoader::initRender()
{
    //加载render组件(render_gdi或render_skia)
    //bLoaded = pComMgr->CreateRender_Skia((IObjRef**)&pRenderFactory)
    BOOL bLoaded = getComMrg()->CreateRender_GDI( ( IObjRef** )&pRenderFactory );
    SASSERT_FMT( bLoaded, _T( "load interface [%s] failed!" ), _T( "render-gdi" ) );

    //加载图片解码模块(imggid或imgwic)
    bLoaded = getComMrg()->CreateImgDecoder( ( IObjRef** )&pImgDecoderFactory );
    SASSERT_FMT( bLoaded, _T( "load interface [%s] failed!" ), _T( "imgdecoder" ) );

    //为渲染模块设置它需要引用的图片解码模块
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
    //将程序的运行路径修改到demo所在的目录
    //某些复杂情况下使用SetCurrentDirectory会导致程序莫名其妙的挂掉(慎用!)
    //SetCurrentDirectory(strResDir);
    //SOUI系统总是从appdir去查找资源
    //注:这个说法是不准确的,soui的源代码中并没有使用GetAppDir(),主要还是依赖SetCurrentDirectory()设置当前路径
    //所以initResource()的时候,最好是使用绝对路径,这样可以避开SetCurrentDirectory()的影响
    pSouiApp->SetAppDir( strResDir );
    return true;
}

bool SoUILoader::initResource()
{
    //定义一个资源提供对象,SOUI系统中实现了3种资源加载方式
    //分别是从文件加载，从EXE的资源加载及从ZIP压缩包加载
    CAutoRefPtr<IResProvider>   pResProvider;
    BOOL bLoaded = FALSE;

#if (RES_TYPE == 0)//从文件加载
    CreateResProvider( RES_FILE, ( IObjRef** )&pResProvider );
    SStringT skinDir = getApp()->GetAppDir() + _T( "\\uires" );
    bLoaded = pResProvider->Init( ( LPARAM )( LPCTSTR )skinDir, 0 );
#elif (RES_TYPE==1)//从EXE资源加载
    CreateResProvider( RES_PE, ( IObjRef** )&pResProvider );
    bLoaded = pResProvider->Init( ( WPARAM )hInstance, 0 );
#elif (RES_TYPE==2)//从ZIP包加载
    bLoaded = getComMrg()->CreateResProvider_ZIP( ( IObjRef** )&pResProvider );
    SASSERT_FMT( bLoaded, _T( "load interface [%s] failed!" ), _T( "resprovider_zip" ) );

    ZIPRES_PARAM param;
    param.ZipFile( pRenderFactory, _T( "uires.zip" ), "souizip" );
    bLoaded = pResProvider->Init( ( WPARAM )&param, 0 );
    SASSERT( bLoaded );
#endif

    if( bLoaded == TRUE )
    {
        //将创建的IResProvider交给SApplication对象
        //从资源加载皮肤
        pSouiApp->AddResProvider( pResProvider );
    }
    return ( bLoaded == TRUE );
}

bool SoUILoader::initScripts()
{
    BOOL bLoaded = FALSE;
#ifdef DLL_CORE
    //加载LUA脚本模块，注意，脚本模块只有在SOUI内核是以DLL方式编译时才能使用。
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
    //加载系统资源
    //从DLL加载系统资源
    HMODULE hModSysResource = LoadLibrary( SYS_NAMED_RESOURCE );
    if ( hModSysResource )
    {
        CAutoRefPtr<IResProvider> sysResProvider;
        CreateResProvider( RES_PE, ( IObjRef** )&sysResProvider );
        bool bRet = ( sysResProvider->Init( ( WPARAM )hModSysResource, 0 ) == TRUE );
        if( bRet )
        {
            getApp()->LoadSystemNamedResource( sysResProvider );
            //采用hook绘制菜单的边框
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
    //加载全局资源描述XML
    //初始化SOUI全局资源
    return ( TRUE == pSouiApp->Init( _T( "xml_init" ), _T( "uidef" ) ) );
}

