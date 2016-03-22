#include "stdafx.h"
#include "ThreadHelper.h"

#include <tlhelp32.h>
#include <vector>
#include <cassert>

// 获取当前模块的路径
CString ThreadHelper::GetAppPathDir( HINSTANCE hdllInstance/*=NULL*/ )
{
    TCHAR szMoudlePath[_MAX_PATH];
    GetModuleFileName( hdllInstance, szMoudlePath, _MAX_PATH );

    TCHAR drive[_MAX_DRIVE];
    TCHAR dir[_MAX_DIR];
    _tsplitpath( szMoudlePath, drive, dir, NULL, NULL );

    TCHAR path[_MAX_PATH];
    _tmakepath( path, drive, dir, NULL, NULL );

    return CString( path );
}

// 生成路径
CString ThreadHelper::BuildPath( const CString& dir, const CString& fileName )
{
    CString path;
    path.Format( _T( "%s%s" ), dir, fileName );
    return path;
}

void ThreadHelper::FindProcessIdByName( const CString& name, std::vector<DWORD>& pids )
{
    HANDLE hProcessSnap;
    //HANDLE hProcess;
    PROCESSENTRY32 pe32;
    //DWORD dwPriorityClass;

    // Take a snapshot of all processes in the system.
    hProcessSnap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
    if( hProcessSnap == INVALID_HANDLE_VALUE )
    {
        return ;
    }

    // Set the size of the structure before using it.
    pe32.dwSize = sizeof( PROCESSENTRY32 );

    // Retrieve information about the first process,
    // and exit if unsuccessful
    if( !Process32First( hProcessSnap, &pe32 ) )
    {
        CloseHandle( hProcessSnap );    // Must clean up the
        //   snapshot object!
        return ;
    }

    DWORD pid = -1;
    // Now walk the snapshot of processes, and
    // display information about each process in turn
    do
    {
        if( name.CompareNoCase( pe32.szExeFile ) == 0 )
        {
            pids.push_back( pe32.th32ProcessID );
        }

    }
    while( Process32Next( hProcessSnap, &pe32 ) );

    CloseHandle( hProcessSnap );

    //return pid;
}

void ThreadHelper::KillProcess( const CString& name )
{
    std::vector<DWORD> pids;
    FindProcessIdByName( name, pids );
    for( int i = 0; i < pids.size(); i++ )
    {
        HANDLE hProcess = OpenProcess( PROCESS_ALL_ACCESS, FALSE, pids[i] );
        if( hProcess != NULL )
        {
            // 4代表什么意思???
            TerminateProcess( hProcess, 4 );
            CloseHandle( hProcess );
        }
    }
}

int ThreadHelper::ProcessNum( const CString& name )
{
    std::vector<DWORD> pids;
    FindProcessIdByName( name, pids );
    return ( int )pids.size();
}

bool ThreadHelper::IsProcessActive( const CString& name )
{
    std::vector<DWORD> pids;
    FindProcessIdByName( name, pids );
    return !pids.empty();
}

bool ThreadHelper::IsProcessActive2( HANDLE hProcess )
{
    DWORD exitCode;
    GetExitCodeProcess( hProcess, &exitCode );
    return ( exitCode == STILL_ACTIVE );
}

bool ThreadHelper::RunProecess( const CString& exePath, const CString& cmdLine, const CString& cwdPath, HANDLE& hProcess, HANDLE& hThread, bool bShow )
{
    PROCESS_INFORMATION pi;
    STARTUPINFO si;
    memset( &si, 0, sizeof( si ) );
    si.cb = sizeof( si );
    si.wShowWindow = bShow ? SW_SHOW : SW_HIDE;
    si.dwFlags = STARTF_USESHOWWINDOW;

    BOOL ret = CreateProcess( ( LPCTSTR )exePath, ( LPTSTR )( LPCTSTR )cmdLine, NULL, FALSE, NULL, NULL, NULL, ( LPCTSTR )cwdPath, &si, &pi );
    if( ret )
    {
        //WaitForSingleObject(pi.hProcess, INFINITE);
        //CloseHandle(pi.hThread);
        //CloseHandle(pi.hProcess);

        // 返回进程和线程句柄
        hProcess = pi.hProcess;
        hThread = pi.hThread;
    }
    return ( ret == TRUE );
}

void ThreadHelper::MsgWaitForThread( HANDLE hThread )
{
    // http://www.cnblogs.com/Sunwayking/articles/1976980.html
    while( TRUE )
    {
        //wait for m_hThread to be over，and wait for
        //QS_ALLINPUT（Any message is in the queue)
        DWORD dwRet = MsgWaitForMultipleObjects( 1, &hThread, FALSE, INFINITE, QS_ALLINPUT );
        if( WAIT_OBJECT_0 + 1 == dwRet )
        {
            //get the message from Queue
            //and dispatch it to specific window
            MSG msg;
            PeekMessage( &msg, NULL, 0, 0, PM_REMOVE );
            DispatchMessage( &msg );
            continue;
        }
        else
        {
            break;
        }
    }
}

/*
向AutoCAD发送命令消息
http://wenku.baidu.com/link?url=scWyZaJCKCR4qqDcx7vxMVyyWkwi7XFZcgJRaMloR9JYHNupWTLOWzQF-HBqOto1gBN5cgN4-69nwzPcpSH844IGw66eub9_KCdawIgKOFa
http://wenku.baidu.com/link?url=_I1yuEpWBkLnp5ZtDnVeSp9BGuwai1MUShyJbus_SwGYK5Ml0GdfWhCLb-CR49MSV4QwPNqKHFPX1jgYXD6WQmoX5K9q00fla7v5p3xS75i
http://www.cnblogs.com/wdhust/archive/2011/04/11/2012004.html  (最终好使的)
http://www.cnblogs.com/BiffoLee/archive/2011/12/24/2300539.html
http://www.cnblogs.com/pswzone/archive/2012/07/25/2609121.html
http://www.cnblogs.com/ganmk/archive/2009/10/29/1592557.html
http://blog.csdn.net/wawj522527/article/details/7946656
http://blog.sina.com.cn/s/blog_77a10c8d01019rva.html

*/

typedef struct
{
	HWND hwnd;
	ThreadHelper::WindowNameCmpFunc cmp;
	CString caption;
}WndNameInfo;

typedef struct
{
	HWND hwnd;
	ThreadHelper::WndCmpFunc cmp;
	DWORD dwProcessId;
}WndProcInfo;

BOOL CALLBACK EnumWindowsByProcId(HWND hwnd, LPARAM lParam)
{
	WndProcInfo* pInfo = (WndProcInfo*)lParam;

	// 比较进程id
	DWORD dwProcessId;
	::GetWindowThreadProcessId(hwnd, &dwProcessId);
	/*CString msg;
	msg.Format(_T("进程id:%ld 句柄:%ld"), dwProcessId, hwnd);
	AfxMessageBox(msg);*/

	//注意：当查找到了，应该返回FALSE中止枚举下去
	if(pInfo->dwProcessId != dwProcessId) return TRUE;

	//判断进程上的窗口是否符合我们的要求
	if(pInfo->cmp(hwnd))
	{
		pInfo->hwnd = hwnd;
		return FALSE;
	}
	return TRUE;
}

//http://www.cnblogs.com/wdhust/archive/2011/04/11/2012004.html
//查找cad进程
BOOL CALLBACK EnumWindowsByName(HWND hwnd, LPARAM lParam)
{
	WndNameInfo* pInfo = (WndNameInfo*)lParam;

	// 比较窗口标题
	const int MAX_LEN = 256;
	TCHAR caption[MAX_LEN];
	assert(hwnd != NULL);
	::GetWindowText(hwnd,caption,MAX_LEN);

	if(pInfo->cmp(caption, pInfo->caption))
	{
		pInfo->hwnd = hwnd;
		//注意：当查找到了，应该返回FALSE中止枚举下去
		return FALSE;
	}
	return TRUE;
}

HWND ThreadHelper::GetHwndByWindowName(const CString& name, ThreadHelper::WindowNameCmpFunc cmp)
{
	WndNameInfo info = {NULL, cmp, name};
	EnumWindows(EnumWindowsByName, (LPARAM)&info);
	return info.hwnd;
}

HWND ThreadHelper::GetHwndByProcId( DWORD procId, WndCmpFunc cmp )
{
	WndProcInfo info = {NULL, cmp, procId};
	EnumWindows(EnumWindowsByProcId, (LPARAM)&info);
	return info.hwnd;
}