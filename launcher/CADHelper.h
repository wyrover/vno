#pragma once

class CADHelper
{
public:
    //��5����������ֻ��LauncherHelper���ڲ�ʹ��
    static BOOL IsAutoCADExist();
    static BOOL CopyCADFile();
    static BOOL RecoverCADFile();
    static BOOL WriteLaunchInfo();
    static BOOL DeleteLaunchInfo();

    //��������(���������ģ�����)
    static CString GetCADPath();
    static bool InitCAD();
    static bool CleanCAD();
    static BOOL SelectFile( CString& fileName, const CString& szFileFilter, const CString& szFileExt );

	// ͨ��SendMessage��AutoCAD����������Ϣ
	static bool SendCommandToAutoCAD(const CString& cmd, bool useEsc=true);
};
