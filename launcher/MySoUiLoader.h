#pragma once

#include "SoUILoader.h"

//#include <controls.extend/SListCtrl2.h>
//#include <controls.extend/SVscrollbar.h>
//#include <controls.extend/SIPAddressCtrl.h>
//#include <controls.extend/SChatEdit.h>
//#include <controls.extend/SScrollText.h>
//#include <controls.extend/SListCtrlEx.h>
//#include <controls.extend/gif/SGifPlayer.h>
//#include <controls.extend/gif/SSkinGif.h>

using namespace SOUI;

class MySoUiLoader : public SoUILoader
{
public:
    MySoUiLoader( HINSTANCE hInstance ) : SoUILoader( hInstance )
    {
    }

    virtual ~MySoUiLoader()
    {
        //�˳�GDI+����
        //SSkinGif::Gdiplus_Shutdown();
    }

protected:
    virtual LPCTSTR getSkinDir() const
    {
        return _T( "..\\..\\Skin\\demo4" );
    }

    virtual bool initExtendControls()
    {
        //pSouiApp->RegisterWndFactory(TplSWindowFactory<SGifPlayer>());//ע��GIFPlayer
        //pSouiApp->RegisterSkinFactory(TplSkinFactory<SSkinGif>());//ע��SkinGif
        ////pSouiApp->RegisterSkinFactory(TplSkinFactory<SSkinAPNG>());//ע��SSkinAPNG
        //pSouiApp->RegisterSkinFactory(TplSkinFactory<SSkinVScrollbar>());//ע�����������Ƥ��

        //pSouiApp->RegisterWndFactory(TplSWindowFactory<SIPAddressCtrl>());//ע��IP�ؼ�
        //pSouiApp->RegisterWndFactory(TplSWindowFactory<SChatEdit>());//ע��ChatEdit
        //pSouiApp->RegisterWndFactory(TplSWindowFactory<SScrollText>());//ע��SScrollText
        //pSouiApp->RegisterWndFactory(TplSWindowFactory<SListCtrlEx>());//ע��SListCtrlEx
        //pSouiApp->RegisterWndFactory(TplSWindowFactory<SListCtrl2>()); //ע��SListCtrl2
        ////if(SUCCEEDED(CUiAnimation::Init()))
        ////{
        ////	pSouiApp->RegisterWndFactory(TplSWindowFactory<SUiAnimationWnd>());//ע�ᶯ���ؼ�
        ////}
        ////pSouiApp->RegisterWndFactory(TplSWindowFactory<SFlyWnd>());//ע����ж����ؼ�
        ////pSouiApp->RegisterWndFactory(TplSWindowFactory<SFadeFrame>());//ע�ὥ���������ؼ�
        ////pSouiApp->RegisterWndFactory(TplSWindowFactory<SRadioBox2>());//ע��RadioBox2
        ////pSouiApp->RegisterWndFactory(TplSWindowFactory<SCalendar2>());//ע��SCalendar2

        ////��ʼ��GDI+����
        //SSkinGif::Gdiplus_Startup();
        return SoUILoader::initExtendControls();
    }

    virtual bool initRealWnd()
    {
        //�����洰�ڴ���ӿ�
        //CSouiRealWndHandler * pRealWndHandler = new CSouiRealWndHandler();
        //pSouiApp->SetRealWndHandler(pRealWndHandler);
        //pRealWndHandler->Release();

        return SoUILoader::initRealWnd();
    }

    virtual bool initGlobalStyle()
    {
        //����ȫ����Դ����XML
        //��ʼ��SOUIȫ����Դ
        return ( TRUE == pSouiApp->Init( _T( "init" ), _T( "uidef" ) ) );
    }
};