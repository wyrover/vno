#pragma once

class ThreadHelper
{
public:
	static CString GetAppPathDir(HINSTANCE hdllInstance=NULL);
	static CString BuildPath(const CString& dir, const CString& fileName);
	static void KillProcess(const CString& name);
	static bool IsProcessActive(const CString& name);
	static bool IsProcessActive2(HANDLE hProcess);
	static bool RunProecess(const CString& exePath, const CString& cmdLine, const CString& cwdPath, HANDLE& hProcess, HANDLE& hThread, bool bShow);
	static void MsgWaitForThread(HANDLE hThread);
};
