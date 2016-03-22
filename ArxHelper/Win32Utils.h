/** 本代码来源于MingQQ */

#pragma once

#include <vector>
#include <string>
#include <time.h>
#include <WinSock2.h>
#include <gdiplus.h>

#if defined(UNICODE) || defined(_UNICODE)
typedef std::wstring tstring;
#else
typedef std::string tstring;
#endif

#include "dlimexp.h"

namespace Win32Utils
{
    extern ARXHELPER_API WCHAR* AnsiToUnicode( const CHAR* lpszStr );
    extern ARXHELPER_API CHAR* UnicodeToAnsi( const WCHAR* lpszStr );
    extern ARXHELPER_API CHAR* AnsiToUtf8( const CHAR* lpszStr );
    extern ARXHELPER_API CHAR* Utf8ToAnsi( const CHAR* lpszStr );
    extern ARXHELPER_API CHAR* UnicodeToUtf8( const WCHAR* lpszStr );
    extern ARXHELPER_API WCHAR* Utf8ToUnicode( const CHAR* lpszStr );

    extern ARXHELPER_API BOOL AnsiToUnicode( const CHAR* lpszAnsi, WCHAR* lpszUnicode, int nLen );
    extern ARXHELPER_API BOOL UnicodeToAnsi( const WCHAR* lpszUnicode, CHAR* lpszAnsi, int nLen );
    extern ARXHELPER_API BOOL AnsiToUtf8( const CHAR* lpszAnsi, CHAR* lpszUtf8, int nLen );
    extern ARXHELPER_API BOOL Utf8ToAnsi( const CHAR* lpszUtf8, CHAR* lpszAnsi, int nLen );
    extern ARXHELPER_API BOOL UnicodeToUtf8( const WCHAR* lpszUnicode, CHAR* lpszUtf8, int nLen );
    extern ARXHELPER_API BOOL Utf8ToUnicode( const CHAR* lpszUtf8, WCHAR* lpszUnicode, int nLen );

    extern ARXHELPER_API std::wstring AnsiToUnicode( const std::string& strAnsi );
    extern ARXHELPER_API std::string UnicodeToAnsi( const std::wstring& strUnicode );
    extern ARXHELPER_API std::string AnsiToUtf8( const std::string& strAnsi );
    extern ARXHELPER_API std::string Utf8ToAnsi( const std::string& strUtf8 );
    extern ARXHELPER_API std::string UnicodeToUtf8( const std::wstring& strUnicode );
    extern ARXHELPER_API std::wstring Utf8ToUnicode( const std::string& strUtf8 );

    extern ARXHELPER_API BOOL ToHexStr( const CHAR* lpStr, int nSrcLen, CHAR* lpHex, int nDestLen );
    extern ARXHELPER_API BOOL StrToHex( const CHAR* lpStr, CHAR* lpHex, int nLen );

    extern ARXHELPER_API u_short Swap16( u_short nValue );		// 16位整型数据网络字节序与正常字节序转换
    extern ARXHELPER_API u_long Swap32( u_long nValue );		// 32位整型数据网络字节序与正常字节序转换

    extern ARXHELPER_API COLORREF HexStrToRGB( LPCTSTR lpszStr );
    extern ARXHELPER_API void RGBToHexStr( COLORREF color, TCHAR* lpBuf, int nLen );

    extern ARXHELPER_API void FormatTime( time_t lTime, LPCTSTR lpFmt, TCHAR* lpBuf, int nLen );
    extern ARXHELPER_API BOOL IsToday( time_t lTime );

    extern ARXHELPER_API BOOL IsToday( SYSTEMTIME* lpTime );
    extern ARXHELPER_API BOOL GetFileLastWriteTime( LPCTSTR lpszFileName, SYSTEMTIME* lpSysTime );	// 获取文件最后修改时间

    extern ARXHELPER_API BOOL File_ReadAll( const TCHAR* lpszFileName, CHAR** lpData, LONG* lSize );	// 读取整个文件

    extern ARXHELPER_API BOOL my_isalnum( unsigned char cChar );		// 检测指定字符是否是字母(A-Z，a-z)或数字(0-9)
    extern ARXHELPER_API BOOL my_isalnum( wchar_t cChar );				// 检测指定字符是否是字母(A-Z，a-z)或数字(0-9)

    extern ARXHELPER_API BOOL EnumSysFont( std::vector<tstring>* arrSysFont );	// 枚举系统字体
    extern ARXHELPER_API BOOL FlashWindowEx( HWND hWnd, int nCount );				// 闪烁窗口标题栏
    extern ARXHELPER_API BOOL GetTrayWndRect( RECT* lpRect );						// 获取系统任务栏区域

    extern ARXHELPER_API BOOL IsDigit( const WCHAR* lpStr );
    extern ARXHELPER_API void Replace( std::string& strText, const CHAR* lpOldStr, const CHAR* lpNewStr );
    extern ARXHELPER_API void Replace( std::wstring& strText, const WCHAR* lpOldStr, const WCHAR* lpNewStr );
    extern ARXHELPER_API WCHAR ToLower( WCHAR c );
    extern ARXHELPER_API void ToLower( WCHAR* lpText );
    extern ARXHELPER_API void ToLower( std::wstring& strText );
    extern ARXHELPER_API WCHAR ToUpper( WCHAR c );
    extern ARXHELPER_API void ToUpper( WCHAR* lpText );
    extern ARXHELPER_API void ToUpper( std::wstring& strText );
    extern ARXHELPER_API void EncodeHtmlSpecialChars( std::wstring& strText );		// 编码Html特殊字符
    extern ARXHELPER_API void DecodeHtmlSpecialChars( std::wstring& strText );		// 解码Html特殊字符

    extern ARXHELPER_API tstring GetBetweenString( const TCHAR* pStr, TCHAR cStart, TCHAR cEnd );
    extern ARXHELPER_API int GetBetweenInt( const TCHAR* pStr, TCHAR cStart, TCHAR cEnd, int nDefValue = 0 );

    extern ARXHELPER_API tstring GetBetweenString( const WCHAR* pStr, const WCHAR* pStart, const WCHAR* pEnd );
    extern ARXHELPER_API int GetBetweenInt( const WCHAR* pStr, const WCHAR* pStart,
                              const WCHAR* pEnd, int nDefValue = 0 );

    extern ARXHELPER_API BOOL DllRegisterServer( LPCTSTR lpszFileName );
    extern ARXHELPER_API BOOL DllUnregisterServer( LPCTSTR lpszFileName );

    extern ARXHELPER_API tstring GetMimeTypeByExtension( const TCHAR* lpExtension );
    extern ARXHELPER_API GUID GetFileTypeGuidByExtension( const WCHAR* lpExtension );
    extern ARXHELPER_API CLSID GetEncoderClsidByExtension( const WCHAR* lpExtension );
    extern ARXHELPER_API CLSID GetEncoderClsidByFileType( REFGUID guidFileType );
    extern ARXHELPER_API CLSID GetEncoderClsidByMimeType( const WCHAR* lpMimeType );

    extern ARXHELPER_API time_t httpdate_parse( const TCHAR* date );

} // namespace cbm
