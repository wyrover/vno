#pragma once

#include "DataMapper.h"

/*
 * 数据链接基类(基于扩展词典实现)
 */
class ARXHELPER_API ExtDictData : public DataMapper
{
    // 提供了2个静态方法用于读写扩展数据
    // 它们的实现效率并不高，适用于读取少量字段的情况
    // 如果需要要连续读取一个图元的大量数据,可以考虑从ExtDictData类派生
public:
    //初始化数据
    static void Init( const AcDbObjectId& objId, const AcStringArray& fields, const AcStringArray& values );

    // 获取属性数据
    // 如果字段不存在，返回false
    static bool Get( const AcDbObjectId& objId, const CString& field, CString& value );

    // 修改属性数据
    // 如果字段不存在，返回false
    static bool Set( const AcDbObjectId& objId, const CString& field, const CString& value );

    // 复制属性数据(未实现)
    static void Copy( const AcDbObjectId& sourceObjId, const AcDbObjectId& targetObjId );

protected:
    void mapString( const CString& field, CString* pValue );
    void mapInt( const CString& field, int* pValue );
    void mapDouble( const CString& field, double* pValue );
    void mapBool( const CString& field, bool* pValue );
    void mapDateTime( const CString& field, COleDateTime* pValue );
    void mapPoint( const CString& field, AcGePoint3d* pValue );
    void mapVector( const CString& field, AcGeVector3d* pValue );

protected:
    virtual Dao* createDao( const AcDbObjectId& objId );
};
