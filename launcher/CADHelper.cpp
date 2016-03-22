#include "stdafx.h"
#include "CADHelper.h"
#include "ThreadHelper.h"
#include "Registry.h"
#include "RegEntry.h"

#include <shlwapi.h>

typedef BOOL ( WINAPI* LPFN_ISWOW64PROCESS ) ( HANDLE, PBOOL );
static BOOL IsWow64()
{
    BOOL bIsWow64 = FALSE;
    LPFN_ISWOW64PROCESS fnIsWow64Process = ( LPFN_ISWOW64PROCESS ) GetProcAddress(
            GetModuleHandle( TEXT( "kernel32" ) ), "IsWow64Process" );
    if ( NULL != fnIsWow64Process )
    {
        if ( !fnIsWow64Process( GetCurrentProcess(), &bIsWow64 ) )
        {
            // handle error
            //AfxMessageBox(_T("IsWow64 error!"));
        }
    }
    return bIsWow64;
}

enum pathType
{
    CURRENT_USER = 0, //�õ���Ŀ¼C:\Users\hd\AppData\Roaming\Autodesk\AutoCAD 2010\R18.0\chs\Support
    LOCAL_MACHINE = 1, //�õ���Ŀ¼��CAD�İ�װĿ¼
};

static CString GetCADPathByWinAPI( TCHAR* locationKey , pathType pat )
{
    CString cadPath;

    TCHAR cadKey[MAX_PATH];
    _tcscpy( cadKey, _T( "Software\\Autodesk\\AutoCAD\\R18.0\\ACAD-8001:804" ) );

    HKEY hRoot = ( CURRENT_USER == pat ) ? HKEY_CURRENT_USER : HKEY_LOCAL_MACHINE;
    CRegistry reg;

    DWORD dwAccess = KEY_ALL_ACCESS;
    //�ж��Ƿ�64λ
    if( IsWow64() )
    {
        dwAccess |= KEY_WOW64_64KEY;
    }
    bool ret = reg.Open( cadKey, hRoot, dwAccess );
    if( ret )
    {
        ret = false;
        int n = reg.Count();
        for( int i = 0; i < n; i++ )
        {
            CRegEntry* entry = reg.GetAt( i );
            if( !_tcscmp( locationKey, entry->lpszName ) )
            {
                cadPath = ( CString ) * entry;
                ret = true;
                break;
            }
        }
        //SubKeyExists����ʹ!
        //std::string name = locationKey.toStdString();
        //ret = reg.SubKeyExists(name.c_str());
        //if(ret)
        //{
        //	cadPath = QString::fromStdString((std::string)reg[name.c_str()]);
        //}
    }
    reg.Close();

    return cadPath;
}

static CString GetWorkDir()
{
    //TCHAR pFileName[MAX_PATH];
    //int nPos = GetCurrentDirectory( MAX_PATH, pFileName);

    //CString csFullPath(pFileName);
    //if( nPos < 0 )
    //	return CString(_T(""));
    //else
    //	return csFullPath;
    HMODULE module = GetModuleHandle( 0 );
    TCHAR pFileName[MAX_PATH];
    GetModuleFileName( module, pFileName, MAX_PATH );

    CString csFullPath( pFileName );
    int nPos = csFullPath.ReverseFind( _T( '\\' ) );
    if( nPos < 0 )
        return CString( "" );
    else
        return csFullPath.Left( nPos );
}

bool writeTestKeybyWinAPI( CString& currentPath )
{
    TCHAR cadKey[MAX_PATH];
    _tcscpy( cadKey, _T( "Software\\Autodesk\\AutoCAD\\R18.0\\ACAD-8001:804\\Applications\\CBM" ) );

    DWORD dwAccess = KEY_ALL_ACCESS;
    //�ж��Ƿ�64λ
    if( IsWow64() )
    {
        dwAccess |= KEY_WOW64_64KEY;
    }

    CRegistry reg;
    bool ret = reg.Open( cadKey, HKEY_LOCAL_MACHINE, dwAccess );
    if( ret )
    {
        //if(reg.Count()>0)
        //{
        reg[_T( "LOADCTRLS" )] = ( DWORD )2;
        currentPath.Append( _T( "\\VVLoader.arx" ) );
        reg[_T( "LOADER" )] = currentPath;
        //}
    }
    reg.Close();

    return ret;
}

//dataΪ0ȥ�������͵�¼��Ϊ1ʱ��ʾ
static bool MotifiInfomationKey( int data )
{
    TCHAR cadKey[MAX_PATH];
    _tcscpy( cadKey, _T( "Software\\Autodesk\\AutoCAD\\R18.0\\ACAD-8001:804\\InfoCenter" ) );

    DWORD dwAccess = KEY_ALL_ACCESS;
    //�ж��Ƿ�64λ
    if( IsWow64() )
    {
        dwAccess |= KEY_WOW64_64KEY;
    }

    CRegistry reg;
    bool ret = reg.Open( cadKey, HKEY_CURRENT_USER, dwAccess );
    if( ret )
    {
        ret = false;
        if( reg.Count() > 0 )
        {
            int n = reg.Count();
            for( int i = 0; i < n; i++ )
            {
                CRegEntry* entry = reg.GetAt( i );
                if( 0 == _tcscmp( _T( "InfoCenterOn" ), entry->lpszName ) )
                {
                    *entry = data;
                    ret = true;
                    break;
                }
            }
        }
    }
    reg.Close();

    return ret;
}

static bool delTestKeybyWinAPI()
{
    TCHAR cadKey[MAX_PATH];
    _tcscpy( cadKey, _T( "Software\\Autodesk\\AutoCAD\\R18.0\\ACAD-8001:804\\Applications" ) );

    DWORD dwAccess = KEY_ALL_ACCESS;
    //�ж��Ƿ�64λ
    if( IsWow64() )
    {
        dwAccess |= KEY_WOW64_64KEY;
    }

    CRegistry reg;
    reg.Clear( HKEY_LOCAL_MACHINE, cadKey, _T( "CBM" ), dwAccess );

    return true;
}

static BOOL CopyCUIXandMNR( LPCTSTR cuixPath, LPCTSTR mnrPath )
{
    CString cadPath = GetCADPathByWinAPI( _T( "RoamableRootFolder" ), CURRENT_USER );
    cadPath.Append( _T( "Support" ) );
    //CString CADcuixPath = cadPath + _T("\\acad.CUIX");
    CString CADcuixPath = cadPath + _T( "\\acad.CUIX" );
    CString CADmnrPath = cadPath + _T( "\\acad.mnr" );

    //��ȡ��ǰ����(.exe)���ڵ�·��
    CString CurrentPath = GetWorkDir();

    CString JLcuixPath = CurrentPath;
    //JLcuixPath.Append("\\Datas\\JL\\acad.CUIX");
    JLcuixPath.Append( cuixPath );
    CString JLmnrPath = CurrentPath + mnrPath;

    if( !CopyFile( JLcuixPath, CADcuixPath, false ) ) return FALSE;
    //if(!CopyFile(JLmnrPath,CADmnrPath,false)) return FALSE;
    return TRUE;
}

BOOL CADHelper::IsAutoCADExist()
{
    //CAD�İ�װĿ¼
    CString cadPath = GetCADPathByWinAPI( _T( "AcadLocation" ), LOCAL_MACHINE );
    return cadPath.IsEmpty() ? FALSE : TRUE;
}

CString CADHelper::GetCADPath()
{
    CString cadPath = GetCADPathByWinAPI( _T( "AcadLocation" ), LOCAL_MACHINE );
    cadPath.Append( _T( "\\acad.exe" ) );
    return cadPath;
}

BOOL CADHelper::CopyCADFile()
{
    if( !CopyCUIXandMNR( _T( "\\Datas\\JL\\acad.CUIX" ), _T( "\\Datas\\JL\\acad.mnr" ) ) ) return FALSE;
    return TRUE;
}

BOOL CADHelper::RecoverCADFile()
{
    if( !CopyCUIXandMNR( _T( "\\Datas\\CAD\\acad.CUIX" ), _T( "\\Datas\\CAD\\acad.mnr" ) ) ) return FALSE;
    return TRUE;
}

BOOL CADHelper::WriteLaunchInfo()
{
    CString CurrentPath = GetWorkDir();
    if( !writeTestKeybyWinAPI( CurrentPath ) ) return FALSE;
    if( !MotifiInfomationKey( 0 ) ) return FALSE;
    return TRUE;
}

BOOL CADHelper::DeleteLaunchInfo()
{
    if( !delTestKeybyWinAPI() ) return FALSE;
    if( !MotifiInfomationKey( 1 ) ) return FALSE;
    return TRUE;
}

static void GetDefaultPath( CString& defaultPath )
{
    TCHAR pPath[MAX_PATH] = {0};
    SHGetSpecialFolderPath( NULL, pPath, CSIDL_PERSONAL, 0 );

    defaultPath.Format( _T( "%s" ), pPath );
}

BOOL CADHelper::SelectFile( CString& fileName, const CString& szFileFilter, const CString& szFileExt )
{
    CString defaultPath;
    GetDefaultPath( defaultPath );

    CFileDialog dlg( TRUE, szFileExt, defaultPath, OFN_OVERWRITEPROMPT, szFileFilter ); ///TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���

    dlg.m_ofn.lpstrFile[0] = NULL;
    CString selectedPath;
    if( IDOK == dlg.DoModal() )
    {
        selectedPath = dlg.GetPathName();
    }
    else
    {
        return FALSE;
    }

    fileName = selectedPath;
    return TRUE;
}

bool CADHelper::InitCAD()
{
    if ( ThreadHelper::IsProcessActive( _T( "acad.exe" ) ) )
    {
        //MessageBox( NULL, _T( "CAD��������!" ), _T( "����" ), MB_OK | MB_ICONWARNING );
        return false;
    }
    if( !CADHelper::IsAutoCADExist() )
    {
        MessageBox( NULL, _T( "δ��װCAD!" ), _T( "����!" ), MB_OK | MB_ICONWARNING );
        return false;
    }
    //if( !CADHelper::CopyCADFile() )
    //{
    //    MessageBox( NULL, _T( "�����ʼ��ʧ��!" ), _T( "������ʾ" ), MB_OK | MB_ICONSTOP );
    //    return false;
    //}
    if( !CADHelper::WriteLaunchInfo() )
    {
        MessageBox( NULL, _T( "ע���д��ʧ��!" ), _T( "������ʾ" ), MB_OK | MB_ICONSTOP );
        return false;
    }
    return true;
}

bool CADHelper::CleanCAD()
{
    //ɾ��ע�����Ϣ���ָ�CADԭʼ��CUIX�ļ�
    if( !CADHelper::DeleteLaunchInfo() ) return false;
    //if( !CADHelper::RecoverCADFile() ) return false;
    return true;
}

void SendCommandToCAD_Helper(HWND cadMainWnd, const CString& cmd, bool useEsc)
{
	// \003��ʾESC
	// \r��ʾ�س�
	CString cmdText;
	if(useEsc)
	{
		cmdText.Format(_T("\003\003%s\r"),cmd);
	}
	else
	{
		cmdText.Format(_T("%s\r"),cmd);
	}

	COPYDATASTRUCT cmdMsg;
	cmdMsg.dwData=(DWORD)1;
	cmdMsg.cbData=(DWORD)(_tcslen(cmdText)+1)*sizeof(TCHAR);;
	cmdMsg.lpData=cmdText.GetBuffer(cmdText.GetLength()+1);
	SendMessage(cadMainWnd,WM_COPYDATA,(WPARAM)cadMainWnd,(LPARAM)&cmdMsg);
}

//�Ƚ�AutoCAD���ڱ���Ĺ���(ֻȡǰ7����ĸ)
static bool CmpAutoCADName(const CString& caption1, const CString& caption2)
{
	return caption1.Mid(0,7) == caption2;
}

bool CADHelper::SendCommandToAutoCAD(const CString& cmd, bool useEsc)
{
	std::vector<DWORD> pids;
	ThreadHelper::FindProcessIdByName(_T("acad.exe"), pids);
	if(pids.empty())
	{
		AfxMessageBox(_T("AutoCADδ����!!"));
		return false;
	}
	else
	{
		// ���ݽ���id���Ҵ��ھ��(ֻ�ҵ�һ��)
		HWND hwnd = ThreadHelper::GetHwndByWindowName(_T("AutoCAD"), &CmpAutoCADName);
		if(hwnd != NULL)
		{
			//��ӡ���ڵı���
			//TCHAR title[80];
			//GetWindowText(hwnd, title, 80);
			//AfxMessageBox(title);
			SendCommandToCAD_Helper(hwnd, cmd, useEsc);
		}
		return (hwnd != NULL);
	}
}
