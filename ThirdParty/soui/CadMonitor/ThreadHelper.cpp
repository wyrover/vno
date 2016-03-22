#include "stdafx.h"
#include "ThreadHelper.h"

#include <tlhelp32.h>
#include <vector>

// 获取当前模块的路径
CString ThreadHelper::GetAppPathDir(HINSTANCE hdllInstance/*=NULL*/)
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

static void FindProcessIdByName( const CString& name, std::vector<DWORD>& pids )
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

    int n = pids.size();
    for( int i = 0; i < n; i++ )
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
