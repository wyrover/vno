#pragma once

#include "dlimexp.h"

// 属性字段管理辅助类
class ARXHELPER_API FieldHelper
{
public:
    //字段操作
    static bool AddField( const CString& type, const CString& field );      // 添加字段
    static bool RemoveField( const CString& type, const CString& field );   // 删除字段
    static void RemoveAllFields( const CString& type );                     // 删除所有字段
    static int FindField( const CString& type, const CString& field );      // 查找字段的索引位置
    static void GetAllFields( const CString& type, AcStringArray& fields ); // 获取图元所有的字段
    static int CountFields( const CString& type );                          // 统计图元的字段个数

    //从文件读数据初始化字段
    static void InitDataField( const CString& fileName );
    static void InitDataFieldWithMoreInfo( const CString& fileName );
};

class ARXHELPER_API FuncFieldHelper
{
public:
    static bool GetFunctions( AcStringArray& funcs );                               // 获取所有功能
    static bool GetTypes( const CString& f, AcStringArray& types );                 // 获取功能下所有的类型
    static bool GetFields( const CString& f, const CString& type, AcStringArray& fields );    // 获取字段
    static bool AddField( const CString& f, const CString& type, const CString& field );      // 添加字段
    static bool RemoveFunction( const CString& f );                                           // 删除功能
    static bool RemoveType( const CString& f, const CString& type );                          // 删除类型
    static bool RemoveField( const CString& f, const CString& type, const CString& field );   // 删除字段
};
