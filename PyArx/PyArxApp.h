// PyArx.h : PyArx DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPyArxApp
// �йش���ʵ�ֵ���Ϣ������� PyArx.cpp
//

class CPyArxApp : public CWinApp
{
public:
	CPyArxApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
