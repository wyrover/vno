#pragma once

// �Զ�����Ϣ -- ��ʼ���
#define WM_BEGIN_MONITOR WM_USER+100
// �Զ�����Ϣ -- �������
#define WM_END_MONITOR WM_USER+101

class MonitorThread;

//�߳�����
struct MonitorThreadData
{
    HANDLE hThread;  // Ҫ���ӵ�exe����(�߳̾��)
    HANDLE hProcess; // Ҫ���ӵ�exe����(���̾��)
    HWND hWnd;       // ���ھ��
    MonitorThread* monitor; // ������
    void* value;      // ��������
};

/*
�ο�:
	http://www.cnblogs.com/pugang/archive/2012/08/24/2654278.html
	http://blog.csdn.net/gencheng/article/details/9376899
��Ϣ�����������̵߳ģ�Post��Ϣ���ǰ���Ϣ�ŵ�Ŀ���̵߳���Ϣ�����С�
�����ߵ��������ڣ�PostMessageͨ��ָ��Ŀ�괰�ھ����ȷ��Ŀ���̣߳�
ͨ��������ɴ��ڹ�����������Ϣ��PostThreadMessageֱ��ָ���߳�ID��ȷ��Ŀ���̣߳�
û��Ŀ�괰�ڣ�ֻ������Ϣѭ����ֱ�Ӹ�����Ϣ��������Ӧ�Ĵ���
�ڳ�����Ƶ�ѡ���棬�����UI�̣߳���Ӧʹ��PostMessage��
����ǹ����̣߳���Ӧʹ��PostThreadMessage����ҪΪ�˽�����Ϣ���������ڡ�
*/

//�����ʾ����ĳ��exe������߳�
class MonitorThread
{
public:
    static HANDLE GetProcess();
    // �û��Ƿ�Ҫ���߳̽���
    static bool IsAskForEnd();
    // �����߳̽������
    static void AskForEnd( bool flag );

public:
    //����������
    virtual ~MonitorThread( void ) {}
    //��Ϣ����: ��������֮ǰ��׼������(������Ӧ���ظú���)
    virtual LRESULT OnMonitorBegin( WPARAM wParam, LPARAM lParam );
    //��Ϣ����: ���̽��������β������(������Ӧ���ظú���)
    virtual LRESULT OnMonitorEnd( WPARAM wParam, LPARAM lParam );

public:
    //����exe����·��
    void SetExePath( const CString& exePath )
    {
        m_exePath = exePath;
    }
    //���������в���
    void SetCmdLine( const CString& cmdLine )
    {
        m_cmdLine = cmdLine;
    }
    //���ý��̵Ĺ���·��
    void SetWorkDirectory( const CString& workDir )
    {
        m_workDir = workDir;
    }
    //��ʾ/���ؽ��̴���
    void ShowWindow( bool bShow )
    {
        m_bShow = bShow;
    }
    //��������
    void SetWndHandle( HWND hWnd )
    {
        m_hWnd = hWnd;
    }
    //����
    bool Run( HANDLE& hThread );

protected:
    //���캯��
    MonitorThread();

    //Ҫ��ص�exe����·��
    CString m_exePath;
    //�����в���
    CString m_cmdLine;
    //���ھ��
    HWND m_hWnd;
    //exe����ĵ�ǰ����·��
    CString m_workDir;
    //�Ƿ�����exe����Ĵ���(Ĭ����ʾ-true)
    bool m_bShow;
    //�û�Ҫ������߳�
    static bool thread_end;
    // ȫ���߳�����
    static MonitorThreadData thread_data;
};
