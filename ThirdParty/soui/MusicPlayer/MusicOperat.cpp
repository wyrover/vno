/****************************************************************************
*  ��    �ܣ���Ƶ�ļ�������                                                 *
*  �� �� �ˣ�С��                                                           *
*  ���ʱ�䣺2015.01.17 12��27                                              *
*  �汾���ͣ���ʼ�汾                                                       *
*  ��ϵ��ʽ��QQ-1035144170                                                  *
****************************************************************************/

#include "StdAfx.h"
#include "MusicOperat.h"

CMusicOpreat::CMusicOpreat(HWND m_PWnd)
{
	m_ParenhWnd=m_PWnd;
	nIndex=0;         //��������
	hStream=NULL;     //������
	m_pBassMusic=NULL;
	m_pMainState=NULL;

	//���ԣ�
	CLrcParse lrcPar;
	lrcPar.ReadFile("");

}

CMusicOpreat::~CMusicOpreat(void)
{
	
	if (hStream)
	{
		BASS_ChannelStop(hStream);
		hStream=NULL;
	}
}
//CMusicOpreat * CMusicOpreat::GetInstance()
//{
//	static CMusicOpreat _Instance;
//
//	return &_Instance;
//}

void CMusicOpreat::InitDatas()
{
	//��ʼ���������
	m_pBassMusic = CBassMusicEngine::GetInstance();
	if ( m_pBassMusic == NULL )
	{
		if ( SMessageBox(NULL,TEXT("���������ʼ��ʧ��"),_T("����"),MB_OK|MB_ICONEXCLAMATION) == IDOK )
		{
			PostQuitMessage(0);
		}
	}
	m_pBassMusic->Init(m_hWnd,this);

}

void CMusicOpreat::InsertMapInfo(int nNum, CString strPath, tagMusicInfo &pMuInfo)
{
	//�����ļ�
	HSTREAM hStream = m_pBassMusic->LoadFile(strPath);
	if ( hStream == -1 ) return;

	//��ȡý���ǩ
	tagMusicInfo *pInfo = m_pBassMusic->GetInfo(hStream);

	//ͨ��map��ListBox��ϣ�һ��������б�
	tagMusicInfo *pMusicInfo = new tagMusicInfo;

	pMusicInfo->dwTime = pInfo->dwTime;
	pMusicInfo->hStream = pInfo->hStream;
	lstrcpyn(pMusicInfo->szArtist,pInfo->szArtist,CountArray(pMusicInfo->szArtist));
	lstrcpyn(pMusicInfo->szTitle,pInfo->szTitle,CountArray(pMusicInfo->szTitle));

	pMuInfo=*pMusicInfo;
	m_MusicManager.insert(pair<int,tagMusicInfo*>(nNum,pMusicInfo));
}

void CMusicOpreat::OnButPrev()         // ��һ��
{
	m_pBassMusic->Stop(hStream);

	nIndex--;
	if (nIndex<0)
	{
		nIndex=m_MusicManager.size()-1;
	}

	CMusicManagerMap::iterator iter = m_MusicManager.find(nIndex);
	if ( iter == m_MusicManager.end() ) return;

	hStream = iter->second->hStream;

	if( m_pBassMusic->Play(hStream,true) )
	{
		int i=0;
	}
}

void CMusicOpreat::OnButPlay()         // ����
{

	m_pBassMusic->Stop(hStream);

	CMusicManagerMap::iterator iter = m_MusicManager.find(nIndex);
	if ( iter == m_MusicManager.end() )
	{
		return;
	}else
	{
		hStream = iter->second->hStream;
		if( m_pBassMusic->Play(hStream,/*(++nIndex!= nIndex) ? false : true)*/true ))
		{
			int i=0;
		}
	}

}

void CMusicOpreat::OnButPause()        // ��ͣ
{
	if ( m_pBassMusic->IsPlaying(hStream) == FALSE ) return;

	if( m_pBassMusic->Pause(hStream) )
	{
		int i=0;

	}
}

void CMusicOpreat::OnButPlayNext()     // ��һ��
{
	m_pBassMusic->Stop(hStream);

	nIndex++;
	if (nIndex>=m_MusicManager.size())
	{
		nIndex=0;
	}

	CMusicManagerMap::iterator iter = m_MusicManager.find(nIndex);
	if ( iter == m_MusicManager.end() ) return;

	hStream = iter->second->hStream;

	if( m_pBassMusic->Play(hStream,true) )
	{
		int i=0;
	}
}

void CMusicOpreat::OnStop()
{
	//�Զ��л���һ�׸�
	OnButPlayNext();
	//::PostMessage(GetContainer()->GetHostHwnd(), MSG_USER_SEARCH_DMTASKDLG, 0, 0);
	::PostMessage(m_ParenhWnd,MSG_USER_REDRAW,0,0);
}