#pragma once

#include "DataMapper.h"

/*
 * 数据链接基类(基于扩展数据实现)
 */
class ARXHELPER_API XData : public DataMapper
{
    // 提供了2个静态方法用于读写扩展数据
    // 它们的实现效率并不高，适用于读取少量字段的情况
    // 如果需要要连续读取一个图元的大量数据,可以考虑从XData类派生
public:
    //初始化扩展数据
    static void Init( const AcDbObjectId& objId, int n );
    static void Init( const AcDbObjectId& objId, const AcStringArray& values );
    // 获取属性数据
    // 如果字段不存在，返回false
    static bool Get( const AcDbObjectId& objId, int pos, CString& value );
    // 修改属性数据
    // 如果字段不存在，返回false
    static bool Set( const AcDbObjectId& objId, int pos, const CString& value );

    // 复制属性数据(未实现)
    static void Copy( const AcDbObjectId& sourceObjId, const AcDbObjectId& targetObjId );

protected:
    void mapString( int pos, CString* pValue );
    void mapInt( int pos, int* pValue );
    void mapDouble( int pos, double* pValue );
    void mapBool( int pos, bool* pValue );
    void mapDateTime( int pos, COleDateTime* pValue );
    void mapPoint( int pos, AcGePoint3d* pValue );
    void mapVector( int pos, AcGeVector3d* pValue );

protected:
    virtual Dao* createDao( const AcDbObjectId& objId );
};
