#pragma once

#include "dlimexp.h"

class Dao
{
public:
    virtual ~Dao() {}
    virtual void clear() = 0;
    virtual bool set( const CString& key, const CString& value ) = 0;
    virtual bool get( const CString& key, CString& value ) = 0;
};

/*
 * 数据链接基类
 */
class ARXHELPER_API DataMapper
{
public:
    virtual ~DataMapper( void );

    /*
     * 设置数据源
     */
    void setDataSource( const AcDbObjectId& objId );

    /*
     * 获取数据源
     */
    AcDbObjectId getDataSource() const;

    /*
     * 读取或更新数据
     * 参数：
     *    save -- false表示将数据更新到变量
     *            true表示将变量更新到数据对象
     */
    bool update( bool save = false );

public:
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

protected:
    virtual void regDatas() = 0;
    virtual Dao* createDao( const AcDbObjectId& objId ) = 0;

protected:
    DataMapper();
    void linkByField( const CString& field, short rtype, void* pValue );
    void linkByPos( int pos, short rtype, void* pValue );

protected:
    // 数据格式：字段名称->字段类型->映射的变量指针->...
    resbuf* m_pDatasToFileds;
    AcDbObjectId m_objId;
};
