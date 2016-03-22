#pragma once

#include "Singleton.h"

//单例模式
class SoUILoader : public Singleton<SoUILoader>
{
public:
    SoUILoader( HINSTANCE _hInstance );
    virtual ~SoUILoader();
    bool init();
    SOUI::SApplication* getApp();

protected:
    //设置uires文件夹的所在路径
    virtual LPCTSTR getSkinDir() const;
    virtual bool initRender();
    virtual bool initApp();
    virtual bool initResource();
    virtual bool initScripts();
    virtual bool initExtendControls();
    virtual bool initSysResource();
    virtual bool initRealWnd();
    virtual bool initGlobalStyle();
    SComMgr* getComMrg();
protected:
    HINSTANCE hInstance;                                //当前模块(exe、dll的句柄)
    SComMgr comMgrObj;                                  // 组件加载管理器
    SOUI::CAutoRefPtr<SOUI::IImgDecoderFactory> pImgDecoderFactory; //图片解码器
    SOUI::CAutoRefPtr<SOUI::IRenderFactory> pRenderFactory;         //UI渲染模块,由render-gdi.dll或render-skia.dll提供
    //SOUI::CAutoRefPtr<ITranslatorMgr> trans;                //多语言翻译模块,由translator.dll提供
    SOUI::CAutoRefPtr<SOUI::IScriptFactory> pScriptLua;             //lua脚本模块,由scriptmodule-lua.dll提供
    SOUI::SApplication* pSouiApp;
};
