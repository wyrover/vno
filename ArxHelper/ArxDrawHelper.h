#pragma once

#include "dlimexp.h"
#include "config.h"
#include <math.h>
#include <vector>

#ifndef PI
#define PI 3.1415926535897932384626433832795
#endif

//����ת����
#define DegToRad(x) x*0.01745329251994329576923690768489
//����ת����
#define RadToDeg(x) x*57.295779513082320876798154814105
//ƽ��
#define square(x)  x*x
//����
#define cot(x) 1.0/tan(x)

//����ͼ�λ��ƺ���
class ARXHELPER_API ArxDrawHelper
{
public:
	static void VectorToAngle(const AcGeVector3d& v, double& ang1, double& ang2);
	static void VectorToAngleTest();

    static AcGePoint2d Point3D_To_2D( const AcGePoint3d& pt );
    static AcGePoint3d Point2D_To_3D( const AcGePoint2d& pt );
    static AcGePoint3d MidPoint( const AcGePoint3d& pt1, const AcGePoint3d& pt2 );
    static CString MakeUpperText( const CString& inStr );
    static CString MakeLowerText( const CString& inStr );
    //����2��˳��������׵�ˮƽ���
    //�ü�����̱Ƚϸ���,������matlab�ķ�������������Ĺ�ʽ
    static double Solve1( double L0, double W0, double d );
    //�ڳ���ΪL�ķ�Χ��������ˮƽ���
    static void Solve1( double L0, double W0, double d, double L, std::vector<double>& dists );
    //����2��˳��������׵Ĵ�ֱ���(��������->��������ߣ���ֱ����)
    //�ü�����̱Ƚϸ���,������matlab�ķ�������������Ĺ�ʽ
    static double Solve2( double Ls, double W0, double d );
    //�ڸ߶�ΪW0�ķ�Χ�������״�ֱ���
    static void Solve2( double Ls, double W0, double d, std::vector<double>& dists );
    static void Shuffle( int n, int m, std::vector<int>& nums );
    static int DivideNum( double L, double gap, bool round = false );
    static void MakeGridWithHole( const AcGePoint3d& basePt, double w, double h, double gap_x, double gap_y, double left, double right, double top, double bottom, AcGePoint3dArray& pts, bool round = true );
    static void MakeGridWithHole( const AcGePoint3d& basePt, double w, double h, int nx, int ny, double left, double right, double top, double bottom, AcGePoint3dArray& pts, bool round = true );
    static void MakeGrid( const AcGePoint3d& basePt, double w, double h, double gap_x, double gap_y, AcGePoint3dArray& pts, bool round = true );
    static void MakeGrid( const AcGePoint3d& basePt, double w, double h, int nx, int ny, AcGePoint3dArray& pts, bool round = true );
    static void Divide( const AcGePoint3d& spt, const AcGePoint3d& ept, double gap_x, double gap_y, AcGePoint3dArray& pts, bool round = true, bool excludeFirst = false, bool tunning = true );
    static AcGePoint3d CacLineClosePt( const AcGePoint3d& spt, const AcGePoint3d& ept, const AcGePoint3d& pt );
    static AcGePoint3d CaclPt( const AcGePoint3d& pt, const AcGeVector3d& v1, double width, const AcGeVector3d& v2, double height );
	static AcGePoint3d CaclPt2(const AcGePoint3d& pt, double angle, double width, double height);
    static void BuildRect( const AcGePoint3d& cnt, double angle, double width, double height, AcGePoint3dArray& pts );
	static void BuildRect2( const AcGePoint3d& pt, double angle, double width, double height, AcGePoint3dArray& pts );
    static int ClockWise( const AcGePoint3dArray& polygon );
    static bool OffSetPolygon( const AcGePoint3dArray& polygon, double offset, bool is_inner, AcGePoint3dArray& offset_polygon );

    static AcDbObjectId GetTextStyle( const CString& style );
    static AcDbObjectId CreateTextStyle( const CString& style, const CString& winFont, Adesk::Boolean bold, Adesk::Boolean italic, int charset, int pitchAndFamily );
    static AcDbObjectId DrawText( const AcGePoint3d& pt, const CString& text, double height, AcDb::TextHorzMode hm = AcDb::kTextLeft, AcDb::TextVertMode vm = AcDb::kTextBase );
    static AcDbObjectId DrawMText( const AcGePoint3d& pt, double angle, const CString& text, double height, AcDbMText::AttachmentPoint ap =  AcDbMText::kMiddleLeft );

    static AcDbObjectId DrawArc( const AcGePoint3d& spt, const AcGePoint3d& pt, const AcGePoint3d& ept );
    static AcDbObjectId DrawCircle( const AcGePoint3d& pt, double radius );
    static AcDbObjectId DrawEllipse( const AcGePoint3d& pt, double width, double height );

    static AcDbObjectId DrawLine( const AcGePoint3d& spt, const AcGePoint3d& ept );
    static AcDbObjectId DrawLine( const AcGePoint3d& pt, double angle, double length );
    static AcDbObjectId DrawPolyLine( const AcGePoint3d& spt, const AcGePoint3d& ept, double width );
    static AcDbObjectId DrawPolyLine( const AcGePoint3d& pt, double angle, double length, double width );
    static AcDbObjectId DrawPolyLine( const AcGePoint3dArray& pts, bool isClosed = false );
    static AcDbObjectId DrawSpline( const AcGePoint3dArray& pts );

    static void DrawArrow( const AcGePoint3d& pt, double angle, double width, double length );
    static void DrawLines( const AcGePoint3dArray& pts );
    static AcDbObjectId DrawRect( const AcGePoint3d& cnt, double angle, double width, double height );
    static AcDbObjectId DrawRect2( const AcGePoint3d& pt, double angle, double width, double height );

    static void CreatePolygonLoop( AcDbHatch* pHatch, const AcGePoint3dArray& pts );
    static void CreateCircleLoop( AcDbHatch* pHatch, const AcGePoint3d& pt, double radius );
    static void CreatePreDefinedHatch( AcDbHatch* pHatch, const CString& patName, double scale );
    static void CreateGradientObject( AcDbHatch* pHatch, const CString& gradName, const AcCmColor& c1, const AcCmColor& c2 );
    static AcDbObjectId DrawPolygonHatch( const AcGePoint3dArray& pts, const CString& patName, double scale );
    static AcDbObjectId DrawCircleGradient( const AcGePoint3d& pt, double radius, const CString& gradName, const AcCmColor& c1, const AcCmColor& c2 );

    //����ֱ�߼нǵĽǶȱ�ע
    static AcDbObjectId Make2LineAngularDim( const AcGePoint3d& pt1, const AcGePoint3d& pt2,
            const AcGePoint3d& pt3, const AcGePoint3d& pt4, const AcGePoint3d& textPt );
    //Բ��Բ���ĽǶȱ�ע
    static AcDbObjectId Make3PointAngularDim( const AcGePoint3d& centerPt, const AcGePoint3d& pt1,
            const AcGePoint3d& pt2, const AcGePoint3d& textPt );
    //�����ע
    static AcDbObjectId MakeAlignedDim( const AcGePoint3d& pt1, const AcGePoint3d& pt2, const CString& text=_T(""), double offset = 30, bool clockwise = true, const CString& dimStyle=DIM_STYLE_NAME );
    //ֱ����ע
    static AcDbObjectId MakeDiametricDim( const AcGePoint3d& centerPt, double radius, const AcGePoint3d& textPt );
    //����/����/������ע
    static AcDbObjectId MakeOrdinateDim( Adesk::Boolean useXAxis, const AcGePoint3d& featurePt, const AcGePoint3d& leaderPt );
    //�뾶/�����ע
    static AcDbObjectId MakeRadialDim( const AcGePoint3d& centerPt, double radius, const AcGePoint3d& textPt );
    static AcDbObjectId MakeRotatedDim( const AcGePoint3d& pt1, const AcGePoint3d& pt2, double ang, const AcGePoint3d& textPt );

    //����������ʽ
    static AcDbObjectId CreateTextstyle( const CString& textStyleName, bool modifyExistStyle = false );
    //��ȡ������ʽid
    static AcDbObjectId GetTextStyleId( const CString& textStyleName );
    //������ע��ʽ
    static AcDbObjectId CreateDimStyle( const CString& dimStyleName, bool modifyExistStyle = false, double bili = 1.0 );
    //��ȡ��ע��ʽid
    static AcDbObjectId GetDimStyle( const CString& dimStyleName );
    //��������
    static void SetLineType( const AcDbObjectId& objId, const CString& ltName );
    static void SetLineType( const AcDbObjectIdArray& objIds, const CString& ltName );
};
