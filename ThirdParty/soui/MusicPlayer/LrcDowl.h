/****************************************************************************
*  ��    �ܣ�LRC����ļ�����                                                *
*  �� �� �ˣ�С��                                                           *
*  ���ʱ�䣺2015.04.10 05��01                                              *
*  �汾���ͣ��޸�                                                           *
*  ��ϵ��ʽ��QQ-1035144170                                                  *
****************************************************************************/

#include<iostream>
#include<fstream>
#include<string>
using namespace std;
#include <windows.h>  
#include <stdio.h>
#include <wininet.h>
#include<conio.h>
#define MAXBLOCKSIZE 1024
#pragma comment( lib, "wininet.lib" ) 

class CLrcDownload:public SHostWnd
{	
public:
	CLrcDownload(void);
	~CLrcDownload(void);
	static CLrcDownload *GetInstance();

public:
	void download(const char *Url,const char *save_as);
	void FileToStr (string& str,char* path);
	string UTF8ToGBK(const std::string& strUTF8);
	string GetStr (string&str, int start,int end);
	string getlrcid(string& songid);
	string getsongid(string& songname);
	string getlrc(string& lrcid);
	string downloadlrc(/*string& name*/);

};


