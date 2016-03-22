#include "SQLite.h"
#include <cstdlib>
#include <cstdio>
#include <clocale>
#include <iostream> 

#include <fstream>
// ��Ҫ����<fstream>����ʹ��
#include "AcFStream.h"
using namespace std;

void CreatPropertyTable(SQLite& sqlite)
{
	// �������ݿ��
    //******************************************************
	TCHAR sql[512] = {0};
	_stprintf_s(sql,_T("%s"),
		_T("CREATE TABLE [PropertyTable] (")
		_T("[id] INTEGER NOT NULL PRIMARY KEY, ")
		_T("[catagory_id] INTEGER REFERENCES [Category]([id]), ")
		_T("[speed] INTEGER, ")
		_T("[power] REAL, ")
		_T("[maxQ] REAL,")
		_T("[maxP] INTEGER, ")
		_T("[absP] INTEGER);")
		_T("CREATE INDEX [Property_id] ON [PropertyTable] ([id]);")
		);
	if(!sqlite.ExcuteNonQuery(sql))
	{
		_tprintf(_T("Create database table failed...\n"));
	}
	//******************************************************


	// �������ݡ�ͨ�������󶨵ķ�ʽ���ύ��������ʱ�����������ͨģʽЧ�ʸ��ߣ����Լ45%����ͬʱ��֧�ֲ�����������ݡ�
	DWORD dwBeginTick = GetTickCount();
    //******************************************************
	// ��һ���Բ��������¼ʱ�򣬲�������ķ�ʽ�����Ч��
	sqlite.BeginTransaction();
	memset(sql,0,sizeof(sql));
	_stprintf_s(sql,_T("insert into PropertyTable(catagory_id,speed,power,maxQ,maxP,absP) values(?,?,?,?,?,?)"));
	SQLiteCommand cmd(&sqlite,sql);
	// ������������
	AcIfstream in(_T("PropertyTable.txt"));  
	if (! in.is_open())  
	{ 
		cout << _T("�ļ���ʧ��..."); 
		return; 
	}  
	while (!in.eof() )  
	{  
		TCHAR id[256],spped[256],power[256],maxQ[256],maxP[256],absP[256];  
		//in.getline (buffer,100);
		in >> id >> spped >> power >> maxQ >> maxP >> absP;
		if(in.fail()) break;
		cmd.BindParam(1,_ttoi(id));
		cmd.BindParam(2,_ttoi(spped));
		cmd.BindParam(3,_tstof(power));
		cmd.BindParam(4,_tstof(maxQ));
		cmd.BindParam(5,_ttoi(maxP));
		cmd.BindParam(6,_ttoi(absP));
		if(!sqlite.ExcuteNonQuery(&cmd))
		{
			_tprintf(_T("%s\n"),sqlite.GetLastErrorMsg());
			break;
		}

		//cout << id << "\t" << spped << "\t" << power << "\t" << maxQ << "\t" << maxP << "\t" << absP << endl;  
		//cout << buffer[0] << endl;
	}

	// ���cmd
	cmd.Clear();
	// �ύ����
	sqlite.CommitTransaction();
	_tprintf(_T("Insert Data Take %dMS...\n"),GetTickCount()-dwBeginTick);
    //******************************************************
}

void CreatTypeTable(SQLite& sqlite)
{
	// �������ݿ��
    //******************************************************
	TCHAR sql[512] = {0};
	_stprintf_s(sql,_T("%s"),
		_T("CREATE TABLE [TypeTable] (")
		_T("[id] INTEGER NOT NULL PRIMARY KEY, ")
		_T("[catagory_id] INTEGER REFERENCES [Category]([id]), ")
		_T("[type] NVARCHAR(20), ")
		_T("[absP] INTEGER, ")
		_T("[weight] INTEGER, ")
		_T("[length] INTEGER,")
		_T("[weidth] INTEGER,")
		_T("[heigth] INTEGER,")
		_T("[factoryName] NVARCHAR(100));")
		_T("CREATE INDEX [Property_id] ON [TypeTable] ([id]);")
		);
	if(!sqlite.ExcuteNonQuery(sql))
	{
		_tprintf(_T("Create database table failed...\n"));
	}
	//******************************************************


	// �������ݡ�ͨ�������󶨵ķ�ʽ���ύ��������ʱ�����������ͨģʽЧ�ʸ��ߣ����Լ45%����ͬʱ��֧�ֲ�����������ݡ�
	DWORD dwBeginTick = GetTickCount();
    //******************************************************
	// ��һ���Բ��������¼ʱ�򣬲�������ķ�ʽ�����Ч��
	sqlite.BeginTransaction();
	memset(sql,0,sizeof(sql));
	_stprintf_s(sql,_T("insert into TypeTable(catagory_id,type,absP,weight,length,weidth,heigth,factoryName) values(?,?,?,?,?,?,?,?)"));
	SQLiteCommand cmd(&sqlite,sql);
	// ������������
	AcIfstream in(_T("TypeTable.txt"));  
	if (! in.is_open())  
	{ 
		cout << _T("�ļ���ʧ��..."); 
		return; 
	}  
	while (!in.eof() )  
	{  
		TCHAR id[256],type[256],absP[256],weight[256],length[256],weidth[256],heigth[256],factoryName[256];  
		//in.getline (buffer,100);
		in >> id >> type >> absP >> weight >> length >> weidth >> heigth >> factoryName;
		if(in.fail()) break;

		cmd.BindParam(1,_ttoi(id));
		cmd.BindParam(2,type);
		cmd.BindParam(3,_ttoi(absP));
		cmd.BindParam(4,_ttoi(weight));
		cmd.BindParam(5,_ttoi(length));
		cmd.BindParam(6,_ttoi(weidth));
		cmd.BindParam(7,_ttoi(heigth));
		cmd.BindParam(8,factoryName);
		if(!sqlite.ExcuteNonQuery(&cmd))
		{
			_tprintf(_T("%s\n"),sqlite.GetLastErrorMsg());
			break;
		}

		//cout << id << "\t" << type << "\t" << absP << "\t" << weight << "\t" << length << "\t" << weidth << "\t" << heigth << "\t" << factoryName << endl;  
		//cout << buffer[0] << endl;
	}

	// ���cmd
	cmd.Clear();
	// �ύ����
	sqlite.CommitTransaction();
	_tprintf(_T("Insert Data Take %dMS...\n"),GetTickCount()-dwBeginTick);
    //******************************************************
}

void SqliteOperate()
{
	TCHAR *szDbPath = _T("pump.db");

	::DeleteFile(szDbPath);

	SQLite sqlite;

	// �򿪻򴴽����ݿ�
	//******************************************************
	if(!sqlite.Open(szDbPath))
	{
		_tprintf(_T("%s\n"),sqlite.GetLastErrorMsg());
		return;
	}
    //******************************************************
	CreatPropertyTable(sqlite);
	CreatTypeTable(sqlite);

	TCHAR sql[512] = {0};
	// ��ѯ
	DWORD dwBeginTick = GetTickCount();
	//******************************************************
	//memset(sql,0,sizeof(sql));
	//_stprintf(sql,_T("%s"),_T("select * from Book where name = '���Ĺ�5'"));
	_stprintf_s(sql,_T("%s"),_T("select * from PropertyTable"));

	SQLiteDataReader Reader = sqlite.ExcuteQuery(sql);

	int index = 0;
	while(Reader.Read())
	{
		_tprintf( _T("***************����%d����¼��***************\n"),++index);
		_tprintf( _T("�ֶ���:%s �ֶ�ֵ:%d\n"),Reader.GetName(0),Reader.GetIntValue(0));
		_tprintf( _T("�ֶ���:%s �ֶ�ֵ:%s\n"),Reader.GetName(1),Reader.GetStringValue(1));
		_tprintf( _T("�ֶ���:%s �ֶ�ֵ:%s\n"),Reader.GetName(2),Reader.GetStringValue(2));
		_tprintf( _T("�ֶ���:%s �ֶ�ֵ:%d\n"),Reader.GetName(3),Reader.GetIntValue(3));
		_tprintf( _T("�ֶ���:%s �ֶ�ֵ:%s\n"),Reader.GetName(4),Reader.GetStringValue(4));
		_tprintf( _T("�ֶ���:%s �ֶ�ֵ:%s\n"),Reader.GetName(5),Reader.GetStringValue(5));
		_tprintf( _T("*******************************************\n"));
	}
	Reader.Close();
	_tprintf(_T("Query Take %dMS...\n"),GetTickCount()-dwBeginTick);
   // ******************************************************

	_stprintf_s(sql,_T("%s"),_T("select * from TypeTable where catagory_id = 1"));

	SQLiteDataReader Reader2 = sqlite.ExcuteQuery(sql);

	index = 0;
	while(Reader2.Read())
	{
		_tprintf( _T("***************����%d����¼��***************\n"),++index);
		_tprintf( _T("�ֶ���:%s �ֶ�ֵ:%d\n"),Reader2.GetName(0),Reader2.GetIntValue(0));
		_tprintf( _T("�ֶ���:%s �ֶ�ֵ:%s\n"),Reader2.GetName(1),Reader2.GetStringValue(1));
		_tprintf( _T("�ֶ���:%s �ֶ�ֵ:%s\n"),Reader2.GetName(2),Reader2.GetStringValue(2));
		_tprintf( _T("�ֶ���:%s �ֶ�ֵ:%d\n"),Reader2.GetName(3),Reader2.GetIntValue(3));
		_tprintf( _T("�ֶ���:%s �ֶ�ֵ:%s\n"),Reader2.GetName(4),Reader2.GetStringValue(4));
		_tprintf( _T("�ֶ���:%s �ֶ�ֵ:%s\n"),Reader2.GetName(5),Reader2.GetStringValue(5));
		_tprintf( _T("�ֶ���:%s �ֶ�ֵ:%s\n"),Reader2.GetName(6),Reader2.GetStringValue(6));
		_tprintf( _T("�ֶ���:%s �ֶ�ֵ:%s\n"),Reader2.GetName(7),Reader2.GetStringValue(7));
		_tprintf( _T("�ֶ���:%s �ֶ�ֵ:%s\n"),Reader2.GetName(8),Reader2.GetStringValue(8));
		_tprintf( _T("*******************************************\n"));
	}
	Reader2.Close();
	_tprintf(_T("Query Take %dMS...\n"),GetTickCount()-dwBeginTick);

	// �ر����ݿ�
	sqlite.Close();
}

int main()
{
	/**
	* �ο�:http://blog.csdn.net/cdn_founder/article/details/7679137
	*/
	setlocale(LC_ALL, "chs");//��Ҫʵ�ֱ��ػ�����ʵ�������������
	SqliteOperate();
	return 0;
}

//void SqliteOperate()
//{
//	TCHAR *szDbPath = _T("Book.db");
//
//	::DeleteFile(szDbPath);
//
//	SQLite sqlite;
//
//	// �򿪻򴴽����ݿ�
//	//******************************************************
//	if(!sqlite.Open(szDbPath))
//	{
//		_tprintf(_T("%s\n"),sqlite.GetLastErrorMsg());
//		return;
//	}
//    //******************************************************
//
//	// �������ݿ��
//    //******************************************************
//	TCHAR sql[512] = {0};
//	_stprintf(sql,_T("%s"),
//		_T("CREATE TABLE [Book] (")
//		_T("[id] INTEGER NOT NULL PRIMARY KEY, ")
//		_T("[name] NVARCHAR(20), ")
//		_T("[author] NVARCHAR(20), ")
//		_T("[catagory_id] INTEGER REFERENCES [Category]([id]), ")
//		_T("[abstruct] NVARCHAR(100) ,")
//		_T("[path] sqNVARCHAR(50), ")
//		_T("[image] BLOB);")
//		_T("CREATE INDEX [Book_id] ON [Book] ([id]);")
//		);
//	if(!sqlite.ExcuteNonQuery(sql))
//	{
//		_tprintf(_T("Create database table failed...\n"));
//	}
//	//******************************************************
//
//	// �������ݡ���ͨ��ʽ��
//	DWORD dwBeginTick = GetTickCount();
//	//******************************************************
//	// ��һ���Բ��������¼ʱ�򣬲�������ķ�ʽ�����Ч��
//	sqlite.BeginTransaction();
//	// ������������
//	for(int i=0;i<10;i++)
//	{
//		memset(sql,0,sizeof(sql));
//		_stprintf(sql,_T("insert into Book(name,author,catagory_id) values('�����%d','Ī��',1)"),i);
//		if(!sqlite.ExcuteNonQuery(sql))
//		{
//			_tprintf(_T("%s\n"),sqlite.GetLastErrorMsg());
//			break;
//		}
//	}
//	// �ύ����
//	sqlite.CommitTransaction();
//	_tprintf(_T("Insert Data Take %dMS...\n"),GetTickCount()-dwBeginTick);
//    //******************************************************
//
//
//	// �������ݡ�ͨ�������󶨵ķ�ʽ���ύ��������ʱ�����������ͨģʽЧ�ʸ��ߣ����Լ45%����ͬʱ��֧�ֲ�����������ݡ�
//	dwBeginTick = GetTickCount();
//    //******************************************************
//	// ��һ���Բ��������¼ʱ�򣬲�������ķ�ʽ�����Ч��
//	sqlite.BeginTransaction();
//	memset(sql,0,sizeof(sql));
//	_stprintf(sql,_T("insert into Book(name,author,catagory_id,image) values(?,'����',?,?)"));
//	SQLiteCommand cmd(&sqlite,sql);
//	// ������������
//	for(int i=0;i<10;i++)
//	{
//		TCHAR strValue[16] = {0};
//		_stprintf(strValue,_T("���Ĺ�%d"),i);
//		// �󶨵�һ��������name�ֶ�ֵ��
//		cmd.BindParam(1,strValue);
//		// �󶨵ڶ���������catagory_id�ֶ�ֵ��
//		cmd.BindParam(2,20);
//		BYTE imageBuf[] = {0xff,0xff,0xff,0xff};
//		// �󶨵�����������image�ֶ�ֵ,���������ݣ�
//		cmd.BindParam(3,imageBuf,sizeof(imageBuf));
//		if(!sqlite.ExcuteNonQuery(&cmd))
//		{
//			_tprintf(_T("%s\n"),sqlite.GetLastErrorMsg());
//			break;
//		}
//	}
//	// ���cmd
//	cmd.Clear();
//	// �ύ����
//	sqlite.CommitTransaction();
//	_tprintf(_T("Insert Data Take %dMS...\n"),GetTickCount()-dwBeginTick);
//    //******************************************************
//
//	// ��ѯ
//	dwBeginTick = GetTickCount();
//	//******************************************************
//	memset(sql,0,sizeof(sql));
//	//_stprintf(sql,_T("%s"),_T("select * from Book where name = '���Ĺ�5'"));
//	_stprintf(sql,_T("%s"),_T("select * from Book"));
//
//	SQLiteDataReader Reader = sqlite.ExcuteQuery(sql);
//
//	int index = 0;
//	int len = 0;
//	while(Reader.Read())
//	{
//		_tprintf( _T("***************����%d����¼��***************\n"),++index);
//		_tprintf( _T("�ֶ���:%s �ֶ�ֵ:%d\n"),Reader.GetName(0),Reader.GetIntValue(0));
//		_tprintf( _T("�ֶ���:%s �ֶ�ֵ:%s\n"),Reader.GetName(1),Reader.GetStringValue(1));
//		_tprintf( _T("�ֶ���:%s �ֶ�ֵ:%s\n"),Reader.GetName(2),Reader.GetStringValue(2));
//		_tprintf( _T("�ֶ���:%s �ֶ�ֵ:%d\n"),Reader.GetName(3),Reader.GetIntValue(3));
//		_tprintf( _T("�ֶ���:%s �ֶ�ֵ:%s\n"),Reader.GetName(4),Reader.GetStringValue(4));
//		// ��ȡͼƬ�������ļ�
//		const BYTE *ImageBuf = Reader.GetBlobValue(6,len);
//		_tprintf( _T("*******************************************\n"));
//	}
//	Reader.Close();
//	_tprintf(_T("Query Take %dMS...\n"),GetTickCount()-dwBeginTick);
//    //******************************************************
//
//	// �ر����ݿ�
//	sqlite.Close();
//}
