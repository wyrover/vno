#pragma once

#include "Singleton.h"

// 关于log的代码来源:
// http://www.codeproject.com/KB/edit/RichEditLog_Demo.aspx
//	1) AppendToLog()
//	2) AppendToLogAndScroll()
//	3) GetNumVisibleLines()

// 自定义消息 -- 用于追加日志
#define WM_APPEND_LOG WM_USER+1
// 自定义消息 -- 用于清空日志
#define WM_CLEAR_LOG WM_USER+2

struct Msg
{
	CString str;
	COLORREF color;
};

// 日志消息
class LogMsg : public Singleton<LogMsg>
{
public:
	//日志消息处理
	void append( HWND hWnd, const CString& str, COLORREF color = RGB( 0, 0 , 0 ) );
	void clear( HWND hWnd );

private:
	Msg m_msg_data;
};
