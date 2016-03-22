#pragma once

#include "Singleton.h"

// ����log�Ĵ�����Դ:
// http://www.codeproject.com/KB/edit/RichEditLog_Demo.aspx
//	1) AppendToLog()
//	2) AppendToLogAndScroll()
//	3) GetNumVisibleLines()

// �Զ�����Ϣ -- ����׷����־
#define WM_APPEND_LOG WM_USER+1
// �Զ�����Ϣ -- ���������־
#define WM_CLEAR_LOG WM_USER+2

struct Msg
{
	CString str;
	COLORREF color;
};

// ��־��Ϣ
class LogMsg : public Singleton<LogMsg>
{
public:
	//��־��Ϣ����
	void append( HWND hWnd, const CString& str, COLORREF color = RGB( 0, 0 , 0 ) );
	void clear( HWND hWnd );

private:
	Msg m_msg_data;
};
