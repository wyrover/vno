#include "stdafx.h"
#include "CADHelper.h"
#include "ThreadHelper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// 初始化 MFC 并在失败时显示错误
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		_tprintf(_T("错误: MFC 初始化失败\n"));
		nRetCode = 1;
	}
	else
	{
		if(argc > 1)
		{
			//是否激活cad
			bool switch_to_cad = (_ttoi(argv[1]) != 0);

			//发送到cad的命令消息
			CString cmd;
			for(int i=2;i<argc;i++)
			{
				cmd.AppendFormat(_T("%s"), argv[i]);
				if(i < argc-1)
				{
					cmd.AppendFormat(_T(" "));
				}
			}
			if(!CADHelper::SendCommandToAutoCAD(cmd, true, switch_to_cad))
			{
				nRetCode = 2; // 执行cad命令失败
			}
		}
		else
		{
			nRetCode = 3; // 参数不足
		}
	}

	return nRetCode;
}
