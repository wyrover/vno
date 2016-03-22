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
 * �������ӻ���
 */
class ARXHELPER_API DataMapper
{
public:
    virtual ~DataMapper( void );

    /*
     * ��������Դ
     */
    void setDataSource( const AcDbObjectId& objId );

    /*
     * ��ȡ����Դ
     */
    AcDbObjectId getDataSource() const;

    /*
     * ��ȡ���������
     * ������
     *    save -- false��ʾ�����ݸ��µ�����
     *            true��ʾ���������µ����ݶ���
     */
    bool update( bool save = false );

public:
    enum DATA_TYPE
    {
        DT_STRING   = 0, // �ַ���
        DT_INT      = 1, // ����
        DT_NUMERIC  = 2, // ������
        DT_BOOL     = 3, // ��������
        DT_DATE     = 4, // ��������
        DT_LIST     = 5, // �б�����(�������ɢ����)
        DT_POINT    = 6, // �����
        DT_VECTOR   = 7  //����
    };

protected:
    virtual void regDatas() = 0;
    virtual Dao* createDao( const AcDbObjectId& objId ) = 0;

protected:
    DataMapper();
    void linkByField( const CString& field, short rtype, void* pValue );
    void linkByPos( int pos, short rtype, void* pValue );

protected:
    // ���ݸ�ʽ���ֶ�����->�ֶ�����->ӳ��ı���ָ��->...
    resbuf* m_pDatasToFileds;
    AcDbObjectId m_objId;
};
