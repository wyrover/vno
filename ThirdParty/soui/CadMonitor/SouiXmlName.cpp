#include "stdafx.h"
#include "SoUILoader.h"
using namespace SOUI;

//读取uires/ResName.txt(该路径是soui程序资源文件的路径)
//本例是cbm/Skin/demo4/uires/ResName.txt
CString GetResName()
{
    SStringT strResDir = SoUILoader::getSingletonPtr()->getApp()->GetAppDir();
    if( strResDir.GetAt( strResDir.GetLength() - 1 ) != _T( '\\' ) )
    {
        strResDir += _T( "\\" );
    }
    CString filename = strResDir + _T( "uires\\ResName.txt" );

    CStdioFile myFile;
    if( myFile.Open( filename, CFile::modeRead ) )
    {
        CString resName;
        if( myFile.ReadString( resName ) )
        {
            return resName;
        }
        else
        {
            return _T( "" );
        }
    }
    else
    {
        return _T( "" );
    }
}