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

	// ��ʼ�� MFC ����ʧ��ʱ��ʾ����
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		_tprintf(_T("����: MFC ��ʼ��ʧ��\n"));
		nRetCode = 1;
	}
	else
	{
		if(argc > 1)
		{
			//�Ƿ񼤻�cad
			bool switch_to_cad = (_ttoi(argv[1]) != 0);

			//���͵�cad��������Ϣ
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
				nRetCode = 2; // ִ��cad����ʧ��
			}
		}
		else
		{
			nRetCode = 3; // ��������
		}
	}

	return nRetCode;
}
