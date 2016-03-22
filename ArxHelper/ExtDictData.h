#pragma once

#include "DataMapper.h"

/*
 * �������ӻ���(������չ�ʵ�ʵ��)
 */
class ARXHELPER_API ExtDictData : public DataMapper
{
    // �ṩ��2����̬�������ڶ�д��չ����
    // ���ǵ�ʵ��Ч�ʲ����ߣ������ڶ�ȡ�����ֶε����
    // �����ҪҪ������ȡһ��ͼԪ�Ĵ�������,���Կ��Ǵ�ExtDictData������
public:
    //��ʼ������
    static void Init( const AcDbObjectId& objId, const AcStringArray& fields, const AcStringArray& values );

    // ��ȡ��������
    // ����ֶβ����ڣ�����false
    static bool Get( const AcDbObjectId& objId, const CString& field, CString& value );

    // �޸���������
    // ����ֶβ����ڣ�����false
    static bool Set( const AcDbObjectId& objId, const CString& field, const CString& value );

    // ������������(δʵ��)
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
