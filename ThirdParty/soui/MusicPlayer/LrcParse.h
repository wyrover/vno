/****************************************************************************
*  ��    �ܣ�LRC����ļ�����                                                *
*  �� �� �ˣ�С��                                                           *
*  ���ʱ�䣺2015.04.10 04��27                                              *
*  �汾���ͣ���ʼ�汾                                                       *
*  ��ϵ��ʽ��QQ-1035144170                                                  *
****************************************************************************/
#pragma once

#include <vector>
#include "atlstr.h"//ʹ��CString������
#include <tchar.h>
#include<algorithm>
#include <atlconv.h>
using namespace std;

#define MAX_LINE_LENGHT 100

typedef struct tagTime
{
	int     nNum;
	float   fTimeValu;
	int     ndd;//�������(����ˮƽ����ģʽ)
}TIMETAG;

class CLrcParse
{
public:
	CLrcParse(void);
	~CLrcParse(void);
public:
	std::vector<TIMETAG> m_vTimeTags;  //�洢ʱ���ǩ
	std::vector<CString> m_vWords;     //�洢ÿ����

	BOOL   ReadFile(LPCSTR lpszFile);  //��ȡ����ļ�(.lrc)
	int    GetLine(FILE* fp,char* szLine) const;
	BOOL   ParseLine( LPCSTR lpsz, int lineNumber);
	void   AddWord(LPCSTR lpszWord);
	void   AddTimeTag(LPCSTR lpszTag, int Number);
	void   SortForTime();
	double StringToDouble( LPCTSTR str );
};