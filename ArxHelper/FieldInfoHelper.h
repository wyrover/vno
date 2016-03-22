#pragma once

#include "dlimexp.h"

class FieldInfo;

class ARXHELPER_API FieldInfoHelper
{
public:
    static void AddFieldInfo( const CString& type, const CString& field, const FieldInfo& info );
    static void RemoveFieldInfo( const CString& type, const CString& field );
    static bool FindFieldInfo( const CString& type, const CString& field );

    static void ReadFieldInfo( const CString& type, const CString& field, FieldInfo& info );
    static void WriteFieldInfo( const CString& type, const CString& field, const FieldInfo& info );
};

// 字段信息
class ARXHELPER_API FieldInfo
{
public:
    FieldInfo();

    /*
     * 默认设置
     * 以下3个条件必须同时满足
     *     1) m_dt = DT_STRING
     *     2) m_enable = true
     *     3) m_descr = _T("")
     */
    bool isDefault() const;
    bool isObjectListType() const;
    void revise();                     //  校正属性设置
    void copyFrom( const FieldInfo& info );

public:
    // 数据类型枚举
    enum DATA_TYPE
    {
        DT_STRING   = 0, // 字符串
        DT_INT      = 1, // 整数
        DT_NUMERIC  = 2, // 浮点数
        DT_BOOL     = 3, // 布尔类型
        DT_DATE     = 4, // 日期类型
        DT_LIST     = 5, // 列表类型(特殊的离散类型)
        DT_POINT    = 6, // 坐标点
        DT_VECTOR   = 7  //向量
    };
    // 列表数据类型
    enum LIST_TYPE
    {
        LT_STRING = 0, // 字符串列表
        LT_INT    = 1, // 整数列表
        LT_OBJECT = 2  // AcDbObject列表
    };
public:

    DATA_TYPE m_dt;                    // 默认为字符串类型(DT_STRING)

    int m_minValue2, m_maxValue2;      // 整数区间

    double m_minValue, m_maxValue;     // 浮点数区间

    LIST_TYPE m_lt;                    // 列表类型
    CString m_varName;                 // 列表变量名称

    bool m_enable;                     // 默认属性可编辑(true)
    CString m_descr;                   // 简要说明

    int m_tolrance;						//精度

    bool m_showInTooltip;              // 是否在tooltip中显示

private:
    void initDefault();                // 恢复默认设置
    void initIntMinMaxValue();         // 设置整型数默认值m_minValue2=m_maxValue2=0
    void initNumericMinMaxValue();     // 设置浮点数默认值m_minValue=m_maxValue=0
    void initListType();               // 设置列表默认设置m_lt=DT_LIST m_varName=_T("")
};

// 字段信息的载体(存储在词典PROPERTY_DATA_FIELD_INFO_DICT中)
class FieldInfoObject : public AcDbObject
{
public:
    ACRX_DECLARE_MEMBERS( FieldInfoObject ) ;

protected:
    static Adesk::UInt32 kCurrentVersionNumber ;

public:
    FieldInfoObject () ;
    virtual ~FieldInfoObject () ;

    virtual Acad::ErrorStatus dwgOutFields ( AcDbDwgFiler* pFiler ) const ;
    virtual Acad::ErrorStatus dwgInFields ( AcDbDwgFiler* pFiler ) ;

public:
    FieldInfo m_info;
} ;

#ifdef MINEGE_MODULE
ACDB_REGISTER_OBJECT_ENTRY_AUTO( FieldInfoObject )
#endif
