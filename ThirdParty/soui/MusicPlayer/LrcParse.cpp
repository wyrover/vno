#include "stdafx.h"
#include "LrcParse.h"


CLrcParse::CLrcParse(void)
{

}
CLrcParse::~CLrcParse(void)
{

}


/*===================================================================
*  �� �� ����CompareTimeRise                                          
*  ��������: ����ǩ��ʱ�併������
*  ���������TIMETAG& tag1, TIMETAG& tag2     
*  �������: ��
*  �� �� ֵ��true  ִ�гɹ�
* 		     false ִ��ʧ��
*  �׳��쳣����
====================================================================*/
bool CompareTimeLand(TIMETAG& tag1, TIMETAG& tag2)
{
	return tag1.fTimeValu > tag2.fTimeValu;
}


/*===================================================================
*  �� �� ����CompareTimeLand                                         
*  ��������: ����ǩ��ʱ����������
*  ���������TIMETAG& tag1, TIMETAG& tag2     
*  �������: ��
*  �� �� ֵ��true  ִ�гɹ�
* 		     false ִ��ʧ��
*  �׳��쳣����
====================================================================*/
bool CompareTimeRise(TIMETAG& tag1, TIMETAG& tag2)
{
	return tag1.fTimeValu < tag2.fTimeValu;
}


/*===================================================================
*  �� �� ����StrToSS                                          
*  ��������: ���ַ�����ʱ��ת��Ϊ����Ϊ��λ�ĸ���ֵ
*  ���������LPCSTR lpszTag  
*  �������: ��
*  �� �� ֵ��float
*  �׳��쳣����
====================================================================*/
float StrToSS(LPCSTR lpszTag)
{
	int paramNums = 0;
	int minutes;
	float seconds;
	USES_CONVERSION;
	paramNums = _stscanf(A2W(lpszTag), L"%d:%f", &minutes, &seconds);
	if(paramNums != 2)
	{
		return 1000000.f;
	}
	return 60*minutes + seconds;
}


/*===================================================================
*  �� �� ����GetLine                                        
*  ��������: ���ı��ļ���ȡһ���ı��غ��� 
*  ���������fp:     �ļ�ָ�룬����ʱ��֤�ǿ�
*            szLine: �����е�ָ�룬����ΪMAX_LINE_LENGTH 
*  �������: ��
*  �� �� ֵ��int ���е��ַ��� 
*  �׳��쳣����
====================================================================*/
int CLrcParse::GetLine(FILE* fp,char* szLine) const 
{ 
	int ch = fgetc(fp); 
	int nIndex = 0; 
	while(!feof(fp) && (ch != '\n') && (nIndex < MAX_LINE_LENGHT)) 
	{ 
		szLine[nIndex++] = (char)ch; 
		ch = fgetc(fp); 
	} 
	szLine[nIndex] = 0; 
	return nIndex; 
}  


/*===================================================================
*  �� �� ����ReadFile                                        
*  ��������: �����ļ�·����ȡ����ַ� 
*  ���������LPCSTR lpszFile
*  �������: ��
*  �� �� ֵ��TRUE  ִ�гɹ�
* 		     FALSE ִ��ʧ��
*  �׳��쳣����
====================================================================*/
BOOL CLrcParse::ReadFile(LPCSTR lpszFile)
{
	FILE *stream; 
	char line[100];
	//CString line;
	int i=0;

	m_vTimeTags.clear();
	m_vWords.clear();

	if( (stream = fopen( "E:\\Project\\Lrc_Soui�������\\Lrc_Soui\\Debug\\��ѧ�� - ����ⶼ���㰮.lrc", "r" )) != NULL ) 
	{ 

		while( fgets( line, 100, stream ) != NULL) 
		{
			//printf( "%s \n" ,line); 
			if(ParseLine(line,i))//���ǿ���
			{
				i++;

			}
		}
		fclose( stream ); 

	}
	STRACE(_T("TimeTag Count: %d, Word Count: %d \n"), m_vTimeTags.size(), m_vWords.size());

	////�������һ���޸�ʵĿ���
	//m_vWords.push_back("");
	//TIMETAG tm;
	//tm.nNum = m_vWords.size()-1;
	//tm.fTimeValu = ((CLrc_TestDlg*)AfxGetMainWnd())->GetSongTotalTime(); //ʱ��ֵΪ�ļ�����ʱ�䳤��
	//m_vTimeTags.push_back(tm);

	SortForTime();

	//TRACE("TimeTag Count: %d, Word Count: %d \n", m_vTimeTags.size(), m_vWords.size());


	//SetHorzData();

	return TRUE;
}


/*===================================================================
*  �� �� ����ParseLine                                        
*  ��������: ���������ÿ���ַ���ʱ��͸���ַ���Ԫ��ʱ���ǩ�洢����  
*  ��m_vTimeTags��,ÿ���ʴ洢������m_vWords���������ͨ��nNumber
*  ��ӳ�䣬���ʱ���ǩ���Զ�Ӧm_vWords����ͬ�ĸ�����ݡ�
*  ��������� LPCSTR lpsz, int lineNumber
*  �������: ��
*  �� �� ֵ��TRUE  ִ�гɹ�
* 		     FALSE ִ��ʧ��
*  �׳��쳣����
====================================================================*/
BOOL CLrcParse::ParseLine( LPCSTR lpsz, int lineNumber)
{
	CString str(lpsz);
	CString sz_time_tag;
	CString strHead;

	str.TrimLeft();
	str.TrimRight();

	int pos, pos2;
	pos = str.Find(L"[");
	if(pos == -1)
		return FALSE;

	bool bAddStr = true;

	while(pos !=-1 )
	{

		str = str.Mid(pos+1);
		pos = str.Find(L"]");
		if(pos!=-1)
		{
			if(lineNumber<5)
			{
				if( (pos2 = str.Find(L":")) != -1)
				{
					strHead = str.Left(pos2);

					if( strHead== "ti" || strHead== "ar" || strHead=="by" || strHead=="al" || strHead == "offset" )
					{
						str = str.Left(str.GetLength()-1);
						bAddStr = false;
						break;
					}
				}  
			}
			USES_CONVERSION;
			AddTimeTag(T2A(str.Left(pos)),lineNumber);
			str = str.Mid(pos+1);
		}
		else
		{
			bAddStr = false;
			return bAddStr;
		}

		pos = str.Find(L"[");

	}//end while


	if(bAddStr)
	{
		str.TrimLeft();
		str.TrimRight();
		USES_CONVERSION;
		AddWord(T2A(str));
	}

	//STRACE("%d, %d \n", m_vTimeTags.size(), m_vWords.size());

	return bAddStr;
}


/*===================================================================
*  �� �� ����AddWord                                        
*  ��������: ����һ���ʵ����� 
*  ���������LPCSTR lpszWord
*  �������: ��
*  �� �� ֵ����
*  �׳��쳣����
====================================================================*/
void CLrcParse::AddWord(LPCSTR lpszWord)
{
	m_vWords.push_back(lpszWord);
	//	STRACE("%s\n", lpszWord);
}


/*===================================================================
*  �� �� ����AddTimeTag                                        
*  ��������: ����һ��ʱ���ǩ������
*  ���������LPCSTR lpszTag, int Number
*  �������: ��
*  �� �� ֵ����
*  �׳��쳣����
====================================================================*/
void CLrcParse::AddTimeTag(LPCSTR lpszTag, int Number)
{
	TIMETAG tag;
	tag.nNum   = Number;
	//tag.fTimeValu = _tstof(lpszTag.GetBuffer()); 
	//tag.fTimeValu=(float)_ttoi(lpszTag);
	//tag.fTimeValu=(float)atof(lpszTag);
	//tag.fTimeValu=_wtof(lpszTag);
	tag.fTimeValu = StrToSS(lpszTag);
	m_vTimeTags.push_back(tag);

	//STRACE( "%f\n", tag.fTimeValu*1000 );
}


/*===================================================================
*  �� �� ����SortForTime                                        
*  ��������: ��ʱ���С����
*  �����������
*  �������: ��
*  �� �� ֵ����
*  �׳��쳣����
====================================================================*/
void CLrcParse::SortForTime()
{
	//ʹ��stl�����㷨��ʱ���С����
	std::sort(m_vTimeTags.begin(),m_vTimeTags.end(), CompareTimeRise);
}


/*===================================================================
*  ����ԭ��: double CLrcParse::StringToDouble( LPCTSTR str )
*  �� �� ����StringToDouble                                        
*  ��������: CString ת���� double ( ֧��Unicode )
*  ���������LPCTSTR str
*  �������: ��
*  �� �� ֵ��double
*  �׳��쳣����
====================================================================*/
double CLrcParse::StringToDouble( LPCTSTR str )
{
	TCHAR szBuff[ 20 ], *p;
	p = szBuff;

#ifdef _UNICODE
	return wcstod( str, &p );   
#else
	return strtod( str, &p );   
#endif
}