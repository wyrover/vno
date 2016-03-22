#include "StdAfx.h"
#include "LogMsg.h"

//��ʼ����̬��Ա����
template<> LogMsg* Singleton<LogMsg>::ms_Singleton = 0;

// ������Ϣ׷����־
void LogMsg::append( HWND hWnd, const CString& str, COLORREF color )
{
	Sleep( 0 );
	// ���ݸ�ȫ�ֱ���(����һЩδ֪���̴߳���)
	m_msg_data.str.Format( _T( "%s\n" ), str ); // �Զ���ӻ���
	m_msg_data.color = color;

	SendMessage( hWnd, WM_APPEND_LOG, ( WPARAM )&m_msg_data, 0 );
}

// ������Ϣ�����־
void LogMsg::clear( HWND hWnd )
{
	SendMessage( hWnd, WM_CLEAR_LOG, 0, 0 );
}
