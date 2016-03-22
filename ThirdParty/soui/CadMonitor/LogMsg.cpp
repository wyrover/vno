#include "StdAfx.h"
#include "LogMsg.h"

//初始化静态成员变量
template<> LogMsg* Singleton<LogMsg>::ms_Singleton = 0;

// 发送消息追加日志
void LogMsg::append( HWND hWnd, const CString& str, COLORREF color )
{
	Sleep( 0 );
	// 传递给全局变量(避免一些未知的线程错误)
	m_msg_data.str.Format( _T( "%s\n" ), str ); // 自动添加换行
	m_msg_data.color = color;

	SendMessage( hWnd, WM_APPEND_LOG, ( WPARAM )&m_msg_data, 0 );
}

// 发送消息清空日志
void LogMsg::clear( HWND hWnd )
{
	SendMessage( hWnd, WM_CLEAR_LOG, 0, 0 );
}
