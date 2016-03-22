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

// �ֶ���Ϣ
class ARXHELPER_API FieldInfo
{
public:
    FieldInfo();

    /*
     * Ĭ������
     * ����3����������ͬʱ����
     *     1) m_dt = DT_STRING
     *     2) m_enable = true
     *     3) m_descr = _T("")
     */
    bool isDefault() const;
    bool isObjectListType() const;
    void revise();                     //  У����������
    void copyFrom( const FieldInfo& info );

public:
    // ��������ö��
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
    // �б���������
    enum LIST_TYPE
    {
        LT_STRING = 0, // �ַ����б�
        LT_INT    = 1, // �����б�
        LT_OBJECT = 2  // AcDbObject�б�
    };
public:

    DATA_TYPE m_dt;                    // Ĭ��Ϊ�ַ�������(DT_STRING)

    int m_minValue2, m_maxValue2;      // ��������

    double m_minValue, m_maxValue;     // ����������

    LIST_TYPE m_lt;                    // �б�����
    CString m_varName;                 // �б��������

    bool m_enable;                     // Ĭ�����Կɱ༭(true)
    CString m_descr;                   // ��Ҫ˵��

    int m_tolrance;						//����

    bool m_showInTooltip;              // �Ƿ���tooltip����ʾ

private:
    void initDefault();                // �ָ�Ĭ������
    void initIntMinMaxValue();         // ����������Ĭ��ֵm_minValue2=m_maxValue2=0
    void initNumericMinMaxValue();     // ���ø�����Ĭ��ֵm_minValue=m_maxValue=0
    void initListType();               // �����б�Ĭ������m_lt=DT_LIST m_varName=_T("")
};

// �ֶ���Ϣ������(�洢�ڴʵ�PROPERTY_DATA_FIELD_INFO_DICT��)
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
