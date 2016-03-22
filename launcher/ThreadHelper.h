#pragma once

#include <vector>

class ThreadHelper
{
public:
	//函数指针(用于定义比较2个窗口的name是否相等)
	typedef bool (*WindowNameCmpFunc)(const CString& caption1, const CString& caption2);

public:
    static CString GetAppPathDir( HINSTANCE hdllInstance = NULL );
    static CString BuildPath( const CString& dir, const CString& fileName );
    static void KillProcess( const CString& name );
    static int ProcessNum( const CString& name );
    static bool IsProcessActive( const CString& name );
    static bool IsProcessActive2( HANDLE hProcess );
    static bool RunProecess( const CString& exePath, const CString& cmdLine, const CString& cwdPath, HANDLE& hProcess, HANDLE& hThread, bool bShow );
    static void MsgWaitForThread( HANDLE hThread );
	static void FindProcessIdByName( const CString& name, std::vector<DWORD>& pids );
	static HWND GetHwndByWindowName( const CString& name, WindowNameCmpFunc cmp );
};
