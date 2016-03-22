#pragma once

class CADHelper
{
public:
    //这5个方法基本只在LauncherHelper的内部使用
    static BOOL IsAutoCADExist();
    static BOOL CopyCADFile();
    static BOOL RecoverCADFile();
    static BOOL WriteLaunchInfo();
    static BOOL DeleteLaunchInfo();

    //公共方法(供其他类或模块调用)
    static CString GetCADPath();
    static bool InitCAD();
    static bool CleanCAD();
    static BOOL SelectFile( CString& fileName, const CString& szFileFilter, const CString& szFileExt );

	// 通过SendMessage给AutoCAD发送命令消息
	static bool SendCommandToAutoCAD(const CString& cmd, bool useEsc=true);
};
