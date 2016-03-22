
#include "StdAfx.h"
#include "LrcDowl.h"


CLrcDownload::CLrcDownload(void)
{

}
CLrcDownload::~CLrcDownload(void)
{

}

CLrcDownload * CLrcDownload::GetInstance()
{
	static CLrcDownload _Instance;

	return &_Instance;
}
void CLrcDownload::download(const char *Url,const char *save_as)  //��Urlָ��ĵ�ַ���ļ����ص�save_asָ��ı����ļ�
{  
	byte Temp[MAXBLOCKSIZE];   
	ULONG Number = 1;   
	FILE *stream;   
	HINTERNET hSession = InternetOpen(L"RookIE/1.0", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0); 
	if (hSession != NULL)
	{  
		HINTERNET handle2 = InternetOpenUrl(hSession, (LPCWSTR)Url, NULL, 0, INTERNET_FLAG_DONT_CACHE, 0);  
		if (handle2 != NULL)  
		{
			if( (stream = fopen( save_as, "wb" )) != NULL )   
			{   
				while (Number > 0)    
				{     
					InternetReadFile(handle2, Temp, MAXBLOCKSIZE - 1, &Number);          
					fwrite(Temp, sizeof (char), Number , stream);  
				}    
				fclose( stream );  
			}      
			InternetCloseHandle(handle2);   
			handle2 = NULL; 
		}  
		InternetCloseHandle(hSession); 
		hSession = NULL; 
	}
}

void CLrcDownload::FileToStr (string& str,char* path) //��Path·���ƶ����ļ����ݸ��Ƶ��ַ���
{
	fstream ft;
	ft.open(path,ios::in);
	int i=0;
	char c;
	while(!ft.eof())
	{ 
		ft.read(&c,1);
		str.insert(i,1,c);
		i++;
	}
	ft.close();
}

string CLrcDownload::UTF8ToGBK(const std::string& strUTF8)  //��UTF8�ַ���ת��ΪGBK����
{  
	int len = MultiByteToWideChar(CP_UTF8, 0, strUTF8.c_str(), -1, NULL, 0);  
	unsigned short * wszGBK = new unsigned short[len + 1];  
	memset(wszGBK, 0, len * 2 + 2);  
	MultiByteToWideChar(CP_UTF8, 0, strUTF8.c_str(), -1, (LPWSTR)wszGBK, len);  

	len = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)wszGBK, -1, NULL, 0, NULL, NULL);  
	char *szGBK = new char[len + 1];  
	memset(szGBK, 0, len + 1);  
	WideCharToMultiByte(CP_ACP,0, (LPCWSTR)wszGBK, -1, szGBK, len, NULL, NULL);  
	//strUTF8 = szGBK;  
	std::string strTemp(szGBK);  
	delete[]szGBK;  
	delete[]wszGBK;  
	return strTemp;  
} 

string CLrcDownload::GetStr (string&str, int start,int end) //��ȡ�ַ����� ĳһ������
{	
	string out;
	int len=end-start;
	for(int i=0;i<len;i++)
	{	
		char c=str[start+i];
		out.insert(i,1,c);
	}
	return out;
}
string CLrcDownload::getsongid(string& songname) //���ݸ�������ȡ����ID
{		
	string json;
	string urls;
	for(int i=1;; i++)
	{   
		//cout<<"���Ե�"<<i<<"������������Ϣ"<<endl;
		urls="http://mp3.baidu.com/dev/api/?tn=getinfo&ct=0&word="+songname+"&format=json";
		const char*urlc=urls.c_str();
		download(urlc,"songid.json");	
		FileToStr( json,"songid.json");
		if ( json.size()>5 )
		{
			//cout<<endl<<"��ȡ����ID�ɹ�"<<endl;	
			break;
		}
		if(i==20)
		{			
			//cout<<endl<<"��ȡ����IDʧ��"<<endl;
			exit(0);
		}
		json="";
	}	

	int start,end;
	start=json.find("song_id");
	end=json.find("singer");
	start+=10;
	end-=3;
	return GetStr ( json,start,end );
}

string CLrcDownload::getlrcid(string& songid)  //���ݸ���ID��ȡ���ID
{
	string urls;
	string json;
	urls="http://ting.baidu.com/data/music/links?songIds="+songid;
	const char*urlc=urls.c_str();
	download(urlc,"lrcid.json");
	FileToStr( json,"lrcid.json");
	int start,end;
	start=json.find("lrcLink")+24;
	end=json.find("version")-7;
	end=start+(end-start) /2-1;	
	if(GetStr ( json,start,end )=="")
	{
		//cout<<endl<<"��ȡ���IDʧ��"<<endl;
		exit(0);
	}
	else
	{
		//cout<<endl<<"��ȡ���ID�ɹ�"<<endl;
		return GetStr ( json,start,end );
	}
}

string CLrcDownload::getlrc(string& lrcid) // ���ݸ��ID��ȡ����ļ�
{
	string lrc;
	string urls;
	urls="http://ting.baidu.com/data2/lrc/"+lrcid+"/"+lrcid+".lrc";
	const char*urlc=urls.c_str();
	download(urlc,"lyric.lrc");
	FileToStr( lrc,"lyric.lrc");
	return lrc;
}

string CLrcDownload::downloadlrc(/*string& name*/) //���ظ��
{		
	string songid;
	string name="ϲ����";

	songid=getsongid(name);	
	//cout<<"SongID="<<songid<<endl<<endl;

	string lrcid;
	lrcid=getlrcid(songid);
	//cout<<"LyricID="<<lrcid<<endl<<endl;

	string lrc;
	lrc=getlrc(lrcid);
	lrc=UTF8ToGBK(lrc);
	//cout<<lrc<<endl;
	return lrc;
}