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
    CURRENT_USER = 0, //得到的目录C:\Users\hd\AppData\Roaming\Autodesk\AutoCAD 2010\R18.0\chs\Support
    LOCAL_MACHINE = 1, //得到的目录是CAD的安装目录
};

static CString GetCADPathByWinAPI( TCHAR* locationKey , pathType pat )
{
    CString cadPath;

    TCHAR cadKey[MAX_PATH];
    _tcscpy( cadKey, _T( "Software\\Autodesk\\AutoCAD\\R18.0\\ACAD-8001:804" ) );

    HKEY hRoot = ( CURRENT_USER == pat ) ? HKEY_CURRENT_USER : HKEY_LOCAL_MACHINE;
    CRegistry reg;

    DWORD dwAccess = KEY_ALL_ACCESS;
    //判断是否64位
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
        //SubKeyExists不好使!
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
    //判断是否64位
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

//data为0去掉搜索和登录框，为1时显示
static bool MotifiInfomationKey( int data )
{
    TCHAR cadKey[MAX_PATH];
    _tcscpy( cadKey, _T( "Software\\Autodesk\\AutoCAD\\R18.0\\ACAD-8001:804\\InfoCenter" ) );

    DWORD dwAccess = KEY_ALL_ACCESS;
    //判断是否64位
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
    //判断是否64位
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

    //获取当前程序(.exe)所在的路径
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
    //CAD的安装目录
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

    CFileDialog dlg( TRUE, szFileExt, defaultPath, OFN_OVERWRITEPROMPT, szFileFilter ); ///TRUE为OPEN对话框，FALSE为SAVE AS对话框

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
        MessageBox( NULL, _T( "CAD正在运行!" ), _T( "警告" ), MB_OK | MB_ICONWARNING );
        return false;
    }
    if( !CADHelper::IsAutoCADExist() )
    {
        MessageBox( NULL, _T( "未安装CAD!" ), _T( "警告!" ), MB_OK | MB_ICONWARNING );
        return false;
    }
    //if( !CADHelper::CopyCADFile() )
    //{
    //    MessageBox( NULL, _T( "程序初始化失败!" ), _T( "错误提示" ), MB_OK | MB_ICONSTOP );
    //    return false;
    //}
    if( !CADHelper::WriteLaunchInfo() )
    {
        MessageBox( NULL, _T( "注册表写入失败!" ), _T( "错误提示" ), MB_OK | MB_ICONSTOP );
        return false;
    }
    return true;
}

bool CADHelper::CleanCAD()
{
    //删除注册表信息并恢复CAD原始的CUIX文件
    if( !CADHelper::DeleteLaunchInfo() ) return false;
    //if( !CADHelper::RecoverCADFile() ) return false;
    return true;
}

static void SplitCString( const CString& str, const CString& tokens, CStringArray& values )
{
	int nTokenPos = 0;
	CString strToken = str.Tokenize( tokens, nTokenPos );
	while ( !strToken.IsEmpty() )
	{
		values.Add( strToken );
		strToken = str.Tokenize( tokens, nTokenPos );
	}
}

void SendCommandToCAD_Helper(HWND cadMainWnd, const CString& cmd, bool useEsc)
{
	CStringArray values;
	SplitCString(cmd, _T(" "), values);
	if(values.IsEmpty()) return;

	// \003表示ESC
	// \r表示回车
	int n = (int)values.GetCount();
	for(int i=0;i<n;i++)
	{
		if(values[i].CompareNoCase(_T("esc")) == 0)
		{
			values[i]= _T("\003");
		}
		else if(values[i].CompareNoCase(_T("enter")) == 0)
		{
			values[i] = _T("\r");
		}
	}
	
	CString cmdText;	
	for(int i=0;i<n;i++)
	{
		values[i].MakeLower();
		cmdText.AppendFormat(_T("%s"), values[i]);
		if(i < n-1)
		{
			cmdText.AppendFormat(_T(" "));
		}
	}
	if(values[0].CompareNoCase(_T("\003")) != 0 && useEsc)
	{
		CString temp_str = cmdText;
		cmdText.Format(_T("\003\003%s"), temp_str);
	}
	if(values[n-1].CompareNoCase(_T("\r")) != 0)
	{
		cmdText.AppendFormat(_T("\r"));
	}
	//AfxMessageBox(cmdText);

	COPYDATASTRUCT cmdMsg;
	cmdMsg.dwData=(DWORD)1;
	cmdMsg.cbData=(DWORD)(_tcslen(cmdText)+1)*sizeof(TCHAR);;
	cmdMsg.lpData=cmdText.GetBuffer(cmdText.GetLength()+1);
	SendMessage(cadMainWnd,WM_COPYDATA,(WPARAM)cadMainWnd,(LPARAM)&cmdMsg);
}

//比较AutoCAD窗口标题的规则(只取前7个字母)
static bool CmpAutoCADName(const CString& caption1, const CString& caption2)
{
	return caption1.Mid(0,7) == caption2;
}

static bool CmpAutoCADWnd(HWND hwnd)
{
	// 获取窗口样式
	LONG wndStyle = ::GetWindowLong(hwnd, GWL_STYLE);
	// 只有CAD的可见主窗口才是我们需要的!!!
	if((wndStyle & (WS_OVERLAPPED | WS_VISIBLE)) > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CADHelper::SendCommandToAutoCAD(const CString& cmd, bool useEsc, bool switch_to_cad)
{
	std::vector<DWORD> pids;
	ThreadHelper::FindProcessIdByName(_T("acad.exe"), pids);
	if(pids.empty())
	{
		//AfxMessageBox(_T("AutoCAD未启动!!"));
		return false;
	}
	else
	{
		// 根据窗口名称查找句柄(不好使!!!AutoCAD有2个主窗口,一个是主界面,一个是AutoCAD命令行窗口,在后台隐藏的一个窗口)
		//HWND hwnd = ThreadHelper::GetHwndByWindowName(_T("AutoCAD"), &CmpAutoCADName);
		// 根据进程id查找cad主窗口句柄
		HWND hwnd = ThreadHelper::GetHwndByProcId(pids[0], &CmpAutoCADWnd);
		if(hwnd != NULL)
		{
			//激活并切换到CAD窗口
			if(switch_to_cad)
			{
				//注释的3行函数无效(不能起到切换cad窗口的作用)
				//::ShowWindow(hwnd, SW_SHOWNA);
				//::SetActiveWindow(hwnd);
				//::SetForegroundWindow(hwnd);
				//这个API属于微软未公开的API,但时好时坏!!!
				::SwitchToThisWindow(hwnd, TRUE);
				//AfxMessageBox(_T("激活并切换到CAD窗口"));
			}
			//打印窗口的标题
			//TCHAR title[80];
			//GetWindowText(hwnd, title, 80);
			//CString msg;
			//msg.Format(_T("句柄:%ld  窗口标题:%s"), hwnd, title);
			//AfxMessageBox(msg);
			//发送命令消息给CAD
			SendCommandToCAD_Helper(hwnd, cmd, useEsc);
		}
		else
		{
			//AfxMessageBox(_T("没有找到CAD主窗口!!!"));
		}
		return (hwnd != NULL);
	}
}
