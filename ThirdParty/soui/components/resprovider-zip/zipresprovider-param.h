#pragma once

namespace SOUI
{
    struct IRenderFactory;
    struct ZIPRES_PARAM
    {
        enum {ZIPFILE,PEDATA} type;
        IRenderFactory *pRenderFac;
        union{
            LPCTSTR pszZipFile;
            struct{
                HINSTANCE hInst;
                LPCTSTR pszResName;
                LPCTSTR pszResType;
            }peInfo;
        };
        LPCSTR          pszPsw; //ZIP����

        void ZipFile(IRenderFactory *_pRenderFac,LPCTSTR _pszFile,LPCSTR _pszPsw =NULL)
        {
            type=ZIPFILE;
            pszZipFile = _pszFile;
            pRenderFac = _pRenderFac;
            pszPsw     = _pszPsw;
        }
        void ZipResource(IRenderFactory *_pRenderFac,HINSTANCE hInst,LPCTSTR pszResName,LPCTSTR pszResType=_T("zip"),LPCSTR _pszPsw =NULL)
        {
            type=PEDATA;
            pRenderFac = _pRenderFac;
            peInfo.hInst=hInst;
            peInfo.pszResName=pszResName;
            peInfo.pszResType=pszResType;
            pszPsw     = _pszPsw;
        }
    };
}