
// mfc.demo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CmfcdemoApp:
// �йش����ʵ�֣������ mfc.demo.cpp
//

class CmfcdemoApp : public CWinApp
{
public:
	CmfcdemoApp();

// ��д
	public:
	virtual BOOL InitInstance();

};

extern CmfcdemoApp theApp;