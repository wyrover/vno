/** ��������Դ��MingQQ */

#pragma once

#include "dlimexp.h"

#include <string>

#if defined(UNICODE) || defined(_UNICODE)
typedef std::wstring tstring;
#else
typedef std::string tstring;
#endif

// 2012.4.26 modify

class ARXHELPER_API PathHelper
{
public:
    PathHelper( void );
    ~PathHelper( void );

    static tstring GetAppPath();	// ��ȡӦ�ó���ִ��·��
    static tstring GetCurDir();	// ��ȡӦ�ó���ǰĿ¼
    static tstring GetTempPath();	// ��ȡ��ǰϵͳ����ʱ�ļ��е�·��
    static tstring GetTempFileName( LPCTSTR lpszFileName );	// ��ȡ��ǰϵͳ����ʱ�ļ��е�·���µ�Ψһ��������ʱ�ļ���(ȫ·��)
    static tstring GetRandomFileName( LPCTSTR lpszPath, LPCTSTR lpszFileName );	// ��ȡ����ļ���(ȫ·��)

    static BOOL IsDirectory( LPCTSTR lpszPath );	// ���ָ��·���Ƿ�Ŀ¼
    static BOOL IsFileExist( LPCTSTR lpszFileName );	// ���ָ���ļ��Ƿ����
    static BOOL IsDirectoryExist( LPCTSTR lpszPath );	// ���ָ��Ŀ¼�Ƿ����
    static BOOL CreateDirectory( LPCTSTR lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes );

    static tstring GetPathRoot( LPCTSTR lpszPath );	// ��ȡָ��·���ĸ�Ŀ¼��Ϣ
    static tstring GetDirectoryName( LPCTSTR lpszPath );	// ����ָ��·���ַ�����Ŀ¼��Ϣ
    static tstring GetFileName( LPCTSTR lpszPath ); // ����ָ��·���ַ������ļ�������չ��
    static tstring GetFileNameWithoutExtension( LPCTSTR lpszPath );	// ���ز�������չ����·���ַ������ļ���
    static tstring GetExtension( LPCTSTR lpszPath );	// ����ָ����·���ַ�������չ��
    static tstring GetFullPath( LPCTSTR lpszPath );	// ����ָ�������·����ȡ����·��
};
