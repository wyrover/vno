#pragma once

#include "dlimexp.h"
#include <string>

/**
* 字符串编码转换.
*/
class ARXHELPER_API EncodeHelper
{
public:
    static std::string UnicodeToANSI( const std::wstring& str );
    static std::wstring ANSIToUnicode( const std::string& str );
    static std::string ANSIToUtf8( const std::string& str );
    static std::string Utf8ToANSI( const std::string& str );
    static std::string UnicodeToUtf8( const std::wstring& str );
    static std::wstring Utf8ToUnicode( const std::string& str );
};

/**
* C表示ANSI(string), W表示Unicode(wstring), U表示Utf8(string)
*/
#define C2W(s) EncodeHelper::ANSIToUnicode(s).c_str()
#define W2C(s) EncodeHelper::UnicodeToANSI(s).c_str()
#define C2U(s) EncodeHelper::ANSIToUtf8(s).c_str()
#define U2C(s) EncodeHelper::Utf8ToANSI(s).c_str()
#define W2U(s) EncodeHelper::UnicodeToUtf8(s).c_str()
#define U2W(s) EncodeHelper::Utf8ToUnicode(s).c_str()
