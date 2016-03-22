#pragma once

#include "Singleton.h"

//����ģʽ
class SoUILoader : public Singleton<SoUILoader>
{
public:
    SoUILoader( HINSTANCE _hInstance );
    virtual ~SoUILoader();
    bool init();
    SOUI::SApplication* getApp();

protected:
    //����uires�ļ��е�����·��
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
    HINSTANCE hInstance;                                //��ǰģ��(exe��dll�ľ��)
    SComMgr comMgrObj;                                  // ������ع�����
    SOUI::CAutoRefPtr<SOUI::IImgDecoderFactory> pImgDecoderFactory; //ͼƬ������
    SOUI::CAutoRefPtr<SOUI::IRenderFactory> pRenderFactory;         //UI��Ⱦģ��,��render-gdi.dll��render-skia.dll�ṩ
    //SOUI::CAutoRefPtr<ITranslatorMgr> trans;                //�����Է���ģ��,��translator.dll�ṩ
    SOUI::CAutoRefPtr<SOUI::IScriptFactory> pScriptLua;             //lua�ű�ģ��,��scriptmodule-lua.dll�ṩ
    SOUI::SApplication* pSouiApp;
};
