#pragma once

#include "dlimexp.h"

// �����ֶι�������
class ARXHELPER_API FieldHelper
{
public:
    //�ֶβ���
    static bool AddField( const CString& type, const CString& field );      // ����ֶ�
    static bool RemoveField( const CString& type, const CString& field );   // ɾ���ֶ�
    static void RemoveAllFields( const CString& type );                     // ɾ�������ֶ�
    static int FindField( const CString& type, const CString& field );      // �����ֶε�����λ��
    static void GetAllFields( const CString& type, AcStringArray& fields ); // ��ȡͼԪ���е��ֶ�
    static int CountFields( const CString& type );                          // ͳ��ͼԪ���ֶθ���

    //���ļ������ݳ�ʼ���ֶ�
    static void InitDataField( const CString& fileName );
    static void InitDataFieldWithMoreInfo( const CString& fileName );
};

class ARXHELPER_API FuncFieldHelper
{
public:
    static bool GetFunctions( AcStringArray& funcs );                               // ��ȡ���й���
    static bool GetTypes( const CString& f, AcStringArray& types );                 // ��ȡ���������е�����
    static bool GetFields( const CString& f, const CString& type, AcStringArray& fields );    // ��ȡ�ֶ�
    static bool AddField( const CString& f, const CString& type, const CString& field );      // ����ֶ�
    static bool RemoveFunction( const CString& f );                                           // ɾ������
    static bool RemoveType( const CString& f, const CString& type );                          // ɾ������
    static bool RemoveField( const CString& f, const CString& type, const CString& field );   // ɾ���ֶ�
};
