#pragma once

// �Զ�����Ϣ -- ��ʼ���
#define WM_BEGIN_MONITOR WM_USER+3

// �Զ�����Ϣ -- �������
#define WM_END_MONITOR WM_USER+4

class MonitorThread;

//�߳�����
struct MonitorThreadData
{
	HANDLE hThread;  // Ҫ���ӵ�exe����(�߳̾��)
	HANDLE hProcess; // Ҫ���ӵ�exe����(���̾��)
	HWND hWnd;       // ���ھ��
	MonitorThread* monitor; // ������
	void* data;      // ��������
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
	static void AskForEnd(bool flag);

public:
	//����������
	virtual ~MonitorThread(void) {}
	//��Ϣ����: ��������֮ǰ��׼������(������Ӧ���ظú���)
	virtual void OnMonitorBegin(WPARAM wParam, LPARAM lParam) {}
	//��Ϣ����: ���̽��������β������(������Ӧ���ظú���)
	virtual void OnMonitorEnd(WPARAM wParam, LPARAM lParam) {}

public:
	//���ý��̵Ĺ���·��
	void SetWorkDirectory(const CString& workDir);
	//��ʾ/���ؽ��̴���
	void ShowWindow(bool bShow);
	//��������
	void SetWndHandle(HWND hWnd);
	//����
	bool Run(HANDLE hThread);

protected:
	MonitorThread();
	//��ȡexe��·��(һ�㶼��ͨ��ע���õ�)
	virtual bool getExePath(CString& path) { return false; }
	virtual CString getCmdLine() { return _T(""); }
	virtual void* attachData() { return 0; }

private:
	//���ھ��
	HWND m_hWnd;
	//exe����ĵ�ǰ����·��
	CString m_workDir;
	//�Ƿ�����exe����Ĵ���
	bool m_bShow;
	//�û�Ҫ������߳�
	static bool thread_end;
	// ȫ���߳�����
	static MonitorThreadData thread_data;
};
