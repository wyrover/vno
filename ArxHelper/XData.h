#pragma once

#include "DataMapper.h"

/*
 * �������ӻ���(������չ����ʵ��)
 */
class ARXHELPER_API XData : public DataMapper
{
    // �ṩ��2����̬�������ڶ�д��չ����
    // ���ǵ�ʵ��Ч�ʲ����ߣ������ڶ�ȡ�����ֶε����
    // �����ҪҪ������ȡһ��ͼԪ�Ĵ�������,���Կ��Ǵ�XData������
public:
    //��ʼ����չ����
    static void Init( const AcDbObjectId& objId, int n );
    static void Init( const AcDbObjectId& objId, const AcStringArray& values );
    // ��ȡ��������
    // ����ֶβ����ڣ�����false
    static bool Get( const AcDbObjectId& objId, int pos, CString& value );
    // �޸���������
    // ����ֶβ����ڣ�����false
    static bool Set( const AcDbObjectId& objId, int pos, const CString& value );

    // ������������(δʵ��)
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
