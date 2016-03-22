#pragma once

#include "dlimexp.h"

// ARX������
class ARXHELPER_API ArxUtilHelper
{
public:
    // ���½���ͼԪ��ӵ�CADͼ�����ݿ�
    static bool PostToModelSpace( AcDbEntity* pEnt );

    // �����ѡ��һ��ʵ��
    static AcDbObjectId SelectEntity( const CString& msg );
    // �����ѡ����ʵ��
    static void SelectEntities( AcDbObjectIdArray& objIds );

    // ��ȡ��ǰ��ѡ���ͼԪ(PickSet)
    static void GetPickSetEntity( AcDbObjectIdArray& objIds );
    static void GetPickSetEntity2( AcDbObjectIdArray& objIds );

    static double Angle( AcGePoint3d& startPt, AcGePoint3d& endPt );

    // ����ѡ��һ��������
    static bool PromptPt( const CString& msg, AcGePoint3d& pt );
    static bool PromptPt2( const CString& msg, const AcGePoint3d& basePt, AcGePoint3d& pt );
    static bool PromptSEPt( AcGePoint3d& startPt, AcGePoint3d& endPt );

    // ��������v��x����ʱ����ת�ĽǶ�
    static double AngleToXAxis( const AcGeVector3d& v );

    // ��ͣ
    static void Pause( const CString& msg = _T( "\n�밴�س���ո������..." ) );

    // �Ƿ�ָ�����͵�ͼԪ
    static bool IsEqualType( const CString& type, const AcDbObjectId& objId, bool isDerivedFromParent = true );

    // ��ʱ��һ����ɫ��ʾһ��ͼԪ
    // �Ự�����󣬻ָ�ԭ����ɫ
    static void ShowEntityWithColor( const AcDbObjectId& objId, unsigned short colorIndex );

    // ��ʱ��һ����ɫ��ʾ���ͼԪ
    // �Ự�����󣬻ָ�ԭ����ɫ
    static void ShowEntitiesWithColor( AcDbObjectIdArray& objIds, unsigned short colorIndex );

    // ��ʱ�ö�����ɫ��ʾ���ͼԪ
    // �Ự�����󣬻ָ�ԭ����ɫ
    static void ShowEntitiesWithColor2( AcDbObjectIdArray& objIds, const AcArray<Adesk::UInt16>& colors );

    // �����н����������ͼԪ
    static void BrowserEntities( const AcDbObjectIdArray& objIds );

    // �����Ƕ�(��ֵ��[0, 2*PI])
    // �������������С�ĽǶ�(��������������ֵ���Գ���[0, 2*PI]���䷶Χ)
    static double AdjustAngle( double angle );

    // string-->int, double֮���ת��
    static bool StringToDouble( const CString& value, double& v );
    static bool StringToInt( const CString& value, int& v );
    static void DoubleToString( double v, CString& value );
    static void IntToString( int v, CString& value );

    //�ж��ַ�����һ�����֣������򸡵�����
    static bool IsNum( const CString& str );

    // �ж��ַ����Ƿ���һ���Ϸ���������
    // ��ʽ[+/-][0-9]
    static bool IsInteger( LPCTSTR pSrc );

    // �ж��ַ����Ƿ���һ���Ϸ��ĸ�������
    // ��ʽ[+/-][0-9][.][0-9]
    static bool IsNumeric( LPCTSTR pSrc );

    // ����GUID�ַ���
    static bool NewGUID( CString& strGUID );

    //��ȡģ������·��
    static CString GetAppPathDir( HINSTANCE hInstance );

    //����·��
    static CString BuildPath( const CString& dir, const CString& fileName );

    //cstring <--> acgepoint3d֮���ת��
    static CString Point3dToString( const AcGePoint3d& pt );
    static bool StringToPoint3d( const CString& value, AcGePoint3d& pt );

    static CString Vector3dToString( const AcGeVector3d& v );
    static bool StringToVector3d( const CString& value, AcGeVector3d& v );

    //�ָ��ַ���
    // tokens��ʾ�ָ���(�����ж���ָ���)
    static void SplitCString( const CString& str, const CString& tokens, CStringArray& values );
};
