#include "stdafx.h"
#include "ArxDrawHelper.h"
#include "ArxUtilHelper.h"
#include "config.h"

void ArxDrawHelper::VectorToAngle(const AcGeVector3d& v, double& ang1, double& ang2)
{
	//������xoyƽ���ϵ�����ͶӰ
	AcGeVector3d u = v.orthoProject(AcGeVector3d::kZAxis);
	//acutPrintf(_T("\nͶӰֵ:x=%.3f, y=%.3f z=%.3f"), u.x, u.y, u.z);

	//angleTo����Ǽнǣ���Χ��[0,180]
	//��������u��Y��ļн�(ƫ��)
	ang1 = u.angleTo(AcGeVector3d::kYAxis);
	if(u.x < 0) ang1 *= -1;

	//��������u��v�ļн�(����)����Χ��[0,180]
	ang2 = u.angleTo(v);
	if(v.z < 0) ang2 *= -1;

	ang1 = RadToDeg(ang1);
	ang2 = RadToDeg(ang2);
}

void ArxDrawHelper::VectorToAngleTest()
{
	AcGeVector3d v(1,1,1);
	double ang1, ang2;
	ArxDrawHelper::VectorToAngle(v, ang1, ang2);
	acutPrintf(_T("\n����:(%.3f, %.3f, %.3f)"), v.x, v.y, v.z);
	acutPrintf(_T("\n����-->�����1:%f  ���ǣ�%f"), ang1, ang2);
	acutPrintf(_T("\n�Ƕ�-->�����1:%f  ���ǣ�%f"), ang1*57.295, ang2*57.295);

	AcGeVector3d v1(1,0,0);
	ArxDrawHelper::VectorToAngle(v1, ang1, ang2);
	acutPrintf(_T("\n����:(%.3f, %.3f, %.3f)"), v1.x, v1.y, v1.z);
	acutPrintf(_T("\n����-->�����1:%f  ���ǣ�%f"), ang1, ang2);
	acutPrintf(_T("\n�Ƕ�-->�����1:%f  ���ǣ�%f"), ang1*57.295, ang2*57.295);

	AcGeVector3d v2(-1,-1,1);
	ArxDrawHelper::VectorToAngle(v2, ang1, ang2);
	acutPrintf(_T("\n����:(%.3f, %.3f, %.3f)"), v2.x, v2.y, v2.z);
	acutPrintf(_T("\n����-->�����1:%f  ���ǣ�%f"), ang1, ang2);
	acutPrintf(_T("\n�Ƕ�-->�����1:%f  ���ǣ�%f"), ang1*57.295, ang2*57.295);
}

AcGePoint2d ArxDrawHelper::Point3D_To_2D( const AcGePoint3d& pt )
{
    return AcGePoint2d( pt.x, pt.y );
}

AcGePoint3d ArxDrawHelper::Point2D_To_3D( const AcGePoint2d& pt )
{
    return AcGePoint3d( pt.x, pt.y, 0 );
}

AcGePoint3d ArxDrawHelper::MidPoint( const AcGePoint3d& pt1, const AcGePoint3d& pt2 )
{
    return pt1 + ( pt2 - pt1 ) * 0.5;
}

CString ArxDrawHelper::MakeUpperText( const CString& inStr )
{
    CString str;
    str.Format( _T( "{\\H0.618x;\\S%s^;}" ), inStr );
    return str;
}

CString ArxDrawHelper::MakeLowerText( const CString& inStr )
{
    CString str;
    str.Format( _T( "{\\H0.618x;\\S^%s;}" ), inStr );
    return str;
}

double ArxDrawHelper::Solve1( double L0, double W0, double d )
{
    double x = W0 * sqrt( L0 * L0 + W0 * W0 - d * d );
    //double x = -1*W0*sqrt(L0*L0+W0*W0-d*d);
    x += d * L0;
    x *= -1 * d;
    x /= ( d * d - W0 * W0 );
    return x;
}

void ArxDrawHelper::Solve1( double L0, double W0, double d, double Lp, std::vector<double>& dists )
{
    double Ld = L0;
    double nd = ArxDrawHelper::Solve1( Ld, W0, d );
    if( nd <= 0 ) return;

    //��ʾʣ��ĳ���
    double L = Lp;
    while( L - nd > 0 )
    {
        dists.push_back( nd );
        L -= nd;
        Ld += nd;
        nd = ArxDrawHelper::Solve1( Ld, W0, d );
    }
    if( L > 0 )
    {
        dists.push_back( L );
    }
}

double ArxDrawHelper::Solve2( double Ls, double W0, double d )
{
    return d * sqrt( W0 * W0 + Ls * Ls ) / Ls;
}

void ArxDrawHelper::Solve2( double Ls, double W0, double d, std::vector<double>& dists )
{
    double W = W0;
    double nd = ArxDrawHelper::Solve2( Ls, W, d );
    if( nd <= 0 ) return;

    //W��ʾʣ��ĸ߶�
    while( W - nd > 0 )
    {
        dists.push_back( nd );
        W -= nd;
        nd = ArxDrawHelper::Solve2( Ls, W, d );
    }
    if( W > 0 )
    {
        dists.push_back( W );
    }
}

void ArxDrawHelper::Shuffle( int n, int m, std::vector<int>& nums )
{
    int d = ArxDrawHelper::DivideNum( n, m );
    int dn = n - d * m;
    for( int i = 0; i < m; i++ )
    {
        nums.push_back( d );
    }
    int c = ( dn < 0 ) ? -1 : 1;
    for( int i = 0; i < abs( dn ); i++ )
    {
        nums[i] += c;
    }
}

int ArxDrawHelper::DivideNum( double L, double gap, bool round/*=false*/ )
{
    double detla = round ? 0.5 : 0;
    return floor( L / gap + detla );
}

void ArxDrawHelper::MakeGridWithHole( const AcGePoint3d& basePt, double w, double h, double gap_x, double gap_y, double left, double right, double top, double bottom, AcGePoint3dArray& pts, bool round )
{
    if( gap_x <= 0 || gap_y <= 0 ) return;
    int nx = ArxDrawHelper::DivideNum( w, gap_x, round );
    int ny = ArxDrawHelper::DivideNum( h, gap_y, round );
    MakeGridWithHole( basePt, w, h, nx, ny, left, right, top, bottom, pts, round );
}

void ArxDrawHelper::MakeGridWithHole( const AcGePoint3d& basePt, double w, double h, int nx, int ny, double left, double right, double top, double bottom, AcGePoint3dArray& pts, bool round )
{
    if( nx <= 0 || ny <= 0 ) return;
    double gap_x = w / nx, gap_y = h / ny;
    int x1 = ArxDrawHelper::DivideNum( left, gap_x, round );
    int x2 = ArxDrawHelper::DivideNum( w - right, gap_x, round );
    int y1 = ArxDrawHelper::DivideNum( bottom, gap_y, round );
    int y2 = ArxDrawHelper::DivideNum( h - top, gap_y, round );
    AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
    for( int i = 0; i < nx; i++ )
    {
        for( int j = 0; j < ny; j++ )
        {
            if( x1 < i && i < x2 && y1 < j && j < y2 ) continue;
            pts.append( basePt + v1 * i * gap_x + v2 * j * gap_y );
        }
    }
}

void ArxDrawHelper::MakeGrid( const AcGePoint3d& basePt, double w, double h, double gap_x, double gap_y, AcGePoint3dArray& pts, bool round )
{
    if( gap_x <= 0 || gap_y <= 0 ) return;
    int nx = ArxDrawHelper::DivideNum( w, gap_x, round );
    int ny = ArxDrawHelper::DivideNum( h, gap_y, round );
    ArxDrawHelper::MakeGrid( basePt, w, h, nx, ny, pts );
}

void ArxDrawHelper::MakeGrid( const AcGePoint3d& basePt, double w, double h, int nx, int ny, AcGePoint3dArray& pts, bool round )
{
    ArxDrawHelper::MakeGridWithHole( basePt, w, h, nx, ny, 0, 0, 0, 0, pts, round );
}

void ArxDrawHelper::Divide( const AcGePoint3d& spt, const AcGePoint3d& ept, double gap_x, double gap_y,  AcGePoint3dArray& pts, bool round, bool excludeFirst, bool tunning )
{
    if( gap_x <= 0 ) return;

    AcGeVector3d v1 = ept - spt;
    int n = ArxDrawHelper::DivideNum( v1.length(), gap_x, round );
	//ȥ����һ��
	if(excludeFirst) n--;

	// ʣ�µ�һ������,��һ��������һ����԰�ƽ��
	double d = (v1.length() - n*gap_x)*0.5;
	//acutPrintf(_T("\n��������-����:%.2f, ���:%.2f, ����:%d"), v1.length(), gap_x, n);
    v1.normalize();

    int c = ( gap_y < 0 ) ? -1 : 1;
    AcGeVector3d v2 = v1;
    v2.rotateBy( c * PI * 0.5, AcGeVector3d::kZAxis );

	gap_y = abs( gap_y );
	d = tunning?d:0; // �Ƿ���Ҫ΢��
	AcGePoint3d pt = spt + v1 * d + v2 * gap_y;
    for( int i = 0; i < n+1; i++ )
    {
        //pts.append( spt + v1 * i * gap_x + v2 * gap_y );
		pts.append(pt);
		pt = pt + v1*gap_x;
    }
}

AcGePoint3d ArxDrawHelper::CaclPt( const AcGePoint3d& pt,
                                   const AcGeVector3d& v1, double width,
                                   const AcGeVector3d& v2, double height )
{
    return ( pt + v1 * width + v2 * height );
}

AcGePoint3d ArxDrawHelper::CaclPt2(const AcGePoint3d& pt, double angle, double width, double height)
{
	AcGeVector3d v1(AcGeVector3d::kXAxis), v2(AcGeVector3d::kYAxis);
	v1.rotateBy(angle, AcGeVector3d::kZAxis);
	v2.rotateBy(angle, AcGeVector3d::kZAxis);
	return ( pt + v1 * width + v2 * height );
}

AcGePoint3d ArxDrawHelper::CacLineClosePt( const AcGePoint3d& spt, const AcGePoint3d& ept, const AcGePoint3d& pt )
{
    // ����һ�������߶�
    AcGeLineSeg3d line( spt, ept );
    return line.closestPointTo( pt ); // ���������������ĵ�
}

void ArxDrawHelper::BuildRect( const AcGePoint3d& cnt, double angle, double width, double height, AcGePoint3dArray& pts )
{
    AcGeVector3d v1( AcGeVector3d::kXAxis ), v2( AcGeVector3d::kXAxis );
    v1.rotateBy( angle, AcGeVector3d::kZAxis );
    v2.rotateBy( angle + PI * 0.5, AcGeVector3d::kZAxis );

    pts.append( ArxDrawHelper::CaclPt( cnt, v1, width * 0.5, v2, height * 0.5 ) );

    v1.rotateBy( PI, AcGeVector3d::kZAxis );
    pts.append( ArxDrawHelper::CaclPt( cnt, v1, width * 0.5, v2, height * 0.5 ) );

    v2.rotateBy( PI, AcGeVector3d::kZAxis );
    pts.append( ArxDrawHelper::CaclPt( cnt, v1, width * 00.5, v2, height * 0.5 ) );

    v1.rotateBy( PI, AcGeVector3d::kZAxis );
    pts.append( ArxDrawHelper::CaclPt( cnt, v1, width * 0.5, v2, height * 0.5 ) );
}

void ArxDrawHelper::BuildRect2(const AcGePoint3d& pt, double angle, double width, double height, AcGePoint3dArray& pts)
{
	AcGeVector3d v1(AcGeVector3d::kXAxis), v2(AcGeVector3d::kYAxis);
	ArxDrawHelper::BuildRect(pt + v1*0.5*width + v2*0.5*height, angle, width, height, pts);
}

AcDbObjectId ArxDrawHelper::DrawEllipse( const AcGePoint3d& pt, double width, double height )
{
    AcGeVector3d v( AcGeVector3d::kXAxis );
    v *= width / 2;
    double ratio = height / width;
    AcDbEllipse* pEllipse = new AcDbEllipse( pt, AcGeVector3d::kZAxis, v, ratio );
    if( !ArxUtilHelper::PostToModelSpace( pEllipse ) )
    {
        delete pEllipse;
        return AcDbObjectId::kNull;
    }
    else
    {
        return pEllipse->objectId();
    }
}

//AcDbObjectId createTextStyle(CString fontName,CString bigFontName,CString textStyleName)
//{
//	AcGiTextStyle *TextStyle=new AcGiTextStyle
//		(fontName,
//		bigFontName,
//		0,
//		0.67,
//		0,
//		0,
//		Adesk::kFalse,
//		Adesk::kFalse,
//		Adesk::kFalse,
//		Adesk::kFalse,
//		Adesk::kFalse,
//		textStyleName); //������
//	AcDbObjectId textStyleId;
//	toAcDbTextStyle(*TextStyle,textStyleId);
//	return textStyleId;
//}
//
//AcDbObjectId createMutiText(AcGePoint3d BasePoint,AcDb::TextHorzMode hMode,CString Text,double texthight,double widthfactor,double angle,int color,CString smallFontName,CString bigFontName)
//{
//	AcDbMText *pMText=new AcDbMText();
//	AcDbObjectId TextStyleId;
//	TextStyleId=createTextStyle(smallFontName,bigFontName,"xianlu");
//	pMText->setTextStyle(TextStyleId);
//	pMText->setContents(Text.GetBuffer(Text.GetLength()));
//	pMText->setTextHeight(texthight);
//	pMText->setRotation(angle);
//	pMText->setLineSpacingFactor(0.8);
//	pMText->setColorIndex(color);
//	return TextStyleId;
//}

/*
 �ο�����
 https://msdn.microsoft.com/zh-cn/library/ms858335.aspx
 https://msdn.microsoft.com/en-us/library/cc194829.aspx
 http://bbs.mjtd.com/thread-1560-1-1.html
 http://blog.csdn.net/sw283632534/article/details/5401999
 http://blog.csdn.net/jiangdong2007/article/details/39637369
 */

AcDbObjectId ArxDrawHelper::GetTextStyle( const CString& style )
{
    AcDbTextStyleTable* pTextStyleTbl;
    acdbHostApplicationServices()->workingDatabase()->getSymbolTable( pTextStyleTbl, AcDb::kForWrite );
    AcDbObjectId fontId;
    pTextStyleTbl->getAt( style, fontId );
    pTextStyleTbl->close();

    return fontId;
}

AcDbObjectId ArxDrawHelper::CreateTextStyle( const CString& style, const CString& winFont, Adesk::Boolean bold, Adesk::Boolean italic, int charset, int pitchAndFamily )
{
    /*
    //pTextStyleTblRcd->setFileName(_T("simfang.ttf"));
    //pTextStyleTblRcd->setBigFontFileName("hzdx");
    pTextStyleTblRcd->setXScale(0.8);
    //pTextStyleTblRcd->setFont("_T(����_GB2312"),Adesk::kFalse,Adesk::kFalse,GB2312_CHARSET,49);
    //pTextStyleTblRcd->setFont(_T("����"),Adesk::kFalse,Adesk::kFalse,GB2312_CHARSET,2);
    pTextStyleTblRcd->setFont(winFont,Adesk::kFalse,Adesk::kFalse,GB2312_CHARSET,16);
    */

    AcDbTextStyleTable* pTextStyleTbl;
    acdbHostApplicationServices()->workingDatabase()->getSymbolTable( pTextStyleTbl, AcDb::kForWrite );
    AcDbObjectId fontId;
    if( pTextStyleTbl->getAt( style, fontId ) == Acad::eKeyNotFound )
    {
        AcDbTextStyleTableRecord* pTextStyleTblRcd = new AcDbTextStyleTableRecord;
        pTextStyleTblRcd->setName( style );
        pTextStyleTblRcd->setFont( winFont, bold, italic, charset, pitchAndFamily );
        pTextStyleTbl->add( fontId, pTextStyleTblRcd );
        pTextStyleTblRcd->close();
    }
    pTextStyleTbl->close();

    return fontId;
    //acdbHostApplicationServices()->workingDatabase()->setTextstyle(fontId);
}

AcDbObjectId ArxDrawHelper::DrawText( const AcGePoint3d& pt, const CString& text, double height,
                                      AcDb::TextHorzMode hm /*= AcDb::kTextLeft*/, AcDb::TextVertMode vm /*= AcDb::kTextBase*/ )
{
    AcDbText* pText = new AcDbText();
    pText->setTextString( text );
    pText->setHeight( height );
    pText->setHorizontalMode( hm );
    pText->setVerticalMode( vm );
    /*
     * ����AcDbText::setHorizontalMode()��˵��
     * �������ΪAcDb::kTextLeft��Ӧʹ��setPosition()�������ò����
     * �������Ϊ��AcDb::kTextLeft��Ӧʹ��setAlignmentPoint()�������ò����
     * AcDbText::setVerticalMode()����ͬ��!!!
     */
    if( hm != AcDb::kTextLeft || vm == AcDb::kTextBase )
    {
        pText->setAlignmentPoint( pt );
    }
    else
    {
        pText->setPosition( pt );
    }
    // ��������
    /*
    AcGeVector3d v1(AcGeVector3d::kXAxis), v2(AcGeVector3d::kXAxis);
    v1.rotateBy(PI, AcGeVector3d::kZAxis);
    v2.rotateBy(PI*1.5, AcGeVector3d::kZAxis);
    pText->setPosition(pt + (v1*width + v2*height)/2);

    pText->setAlignmentPoint(pt + (v2*height)/2);
    pText->setAlignmentPoint(pt);
    */

    if( !ArxUtilHelper::PostToModelSpace( pText ) )
    {
        delete pText;
        return AcDbObjectId::kNull;
    }
    else
    {
        return pText->objectId();
    }
}

AcDbObjectId ArxDrawHelper::DrawMText( const AcGePoint3d& pt, double angle, const CString& text, double height, AcDbMText::AttachmentPoint ap )
{
    AcDbMText* pMText = new AcDbMText;
    //AcDbObjectId style; // ������ʽ
    //pMText->setTextStyle(style);
    pMText->setLocation( pt );
    pMText->setRotation( angle );
    //pMText->setWidth(width); // �����ÿ�ȣ��Զ�����
    pMText->setTextHeight( height );
    pMText->setAttachment( ap ); // Ĭ�Ͼ���
    pMText->setContents( text );

    //acutPrintf(_T("\n���ֿ��:%.3f"), pMText->actualWidth());

    if( !ArxUtilHelper::PostToModelSpace( pMText ) )
    {
        delete pMText;
        return AcDbObjectId::kNull;
    }
    else
    {
        return pMText->objectId();
    }
}

void ArxDrawHelper::DrawLines( const AcGePoint3dArray& pts )
{
    // ������ֱͨ��
    // �ö���ֱ�����ӳ�һ����֧
    int len = pts.length();
    AcDbPolyline* pPline = new AcDbPolyline( len );
    for( int i = 0; i < len - 1; i++ )
    {
        AcDbLine* pLine = new AcDbLine( pts[i], pts[i + 1] );
        ArxUtilHelper::PostToModelSpace( pLine );
    }
}

AcDbObjectId ArxDrawHelper::DrawPolyLine( const AcGePoint3dArray& pts, bool isClosed )
{
    // ���ƶ����
    int len = pts.length();
    if( len < 2 ) return AcDbObjectId::kNull;

    AcDbPolyline* pPline = new AcDbPolyline( len );
    for( int i = 0; i < len; i++ )
    {
        AcGePoint2d pt;
        pt.set( pts[i].x, pts[i].y );
        pPline->addVertexAt( i, pt );
    }
    pPline->setClosed( isClosed );
    if( !ArxUtilHelper::PostToModelSpace( pPline ) )
    {
        delete pPline;
        return AcDbObjectId::kNull;
    }
    else
    {
        return pPline->objectId();
    }
}

AcDbObjectId ArxDrawHelper::DrawSpline( const AcGePoint3dArray& pts )
{
    // ������������
    AcDbSpline* pSpline = new AcDbSpline( pts );
    if( !ArxUtilHelper::PostToModelSpace( pSpline ) )
    {
        delete pSpline;
        return AcDbObjectId::kNull;
    }
    else
    {
        return pSpline->objectId();
    }
}

static void Swap( double& a, double& b )
{
    double temp = a;
    a = b;
    b = temp;
}

AcDbObjectId ArxDrawHelper::DrawArc( const AcGePoint3d& spt, const AcGePoint3d& pt, const AcGePoint3d& ept )
{
    AcGeCircArc3d arc( spt, pt, ept );
    AcGePoint3d cnt = arc.center();
    double radius = arc.radius();
    AcGeVector3d sv = spt - cnt;
    AcGeVector3d ev = ept - cnt;
    double sa = sv.angleTo( AcGeVector3d::kXAxis, -AcGeVector3d::kZAxis );
    double ea = ev.angleTo( AcGeVector3d::kXAxis, -AcGeVector3d::kZAxis );

    if( arc.normal().z <= 0 )
    {
        Swap( sa, ea );
    }

    AcDbArc* pArc = new AcDbArc( cnt, radius, sa, ea );
    if( !ArxUtilHelper::PostToModelSpace( pArc ) )
    {
        delete pArc;
        return AcDbObjectId::kNull;
    }
    else
    {
        return pArc->objectId();
    }
}

AcDbObjectId ArxDrawHelper::DrawLine( const AcGePoint3d& spt, const AcGePoint3d& ept )
{
    AcDbLine* pLine = new AcDbLine( spt, ept );
    if( !ArxUtilHelper::PostToModelSpace( pLine ) )
    {
        delete pLine;
        return AcDbObjectId::kNull;
    }
    else
    {
        return pLine->objectId();
    }
}

AcDbObjectId ArxDrawHelper::DrawLine( const AcGePoint3d& pt, double angle, double length )
{
    AcGeVector3d v( AcGeVector3d::kXAxis );
    v.rotateBy( angle, AcGeVector3d::kZAxis );
    return DrawLine( pt, pt + v * length );
}

AcDbObjectId ArxDrawHelper::DrawCircle( const AcGePoint3d& pt, double radius )
{
    AcDbCircle* pCircle = new AcDbCircle( pt, AcGeVector3d::kZAxis, radius );
    if( !ArxUtilHelper::PostToModelSpace( pCircle ) )
    {
        delete pCircle;
        return AcDbObjectId::kNull;
    }
    else
    {
        return pCircle->objectId();
    }
}

AcDbObjectId ArxDrawHelper::DrawPolyLine( const AcGePoint3d& spt, const AcGePoint3d& ept, double width )
{
    AcDbPolyline* pl = new AcDbPolyline( 2 );
    pl->addVertexAt( 0, Point3D_To_2D( spt ) );
    pl->addVertexAt( 1, Point3D_To_2D( ept ) );
    pl->setConstantWidth( width );
    if( !ArxUtilHelper::PostToModelSpace( pl ) )
    {
        delete pl;
        return AcDbObjectId::kNull;
    }
    else
    {
        return pl->objectId();
    }
}

AcDbObjectId ArxDrawHelper::DrawPolyLine( const AcGePoint3d& pt, double angle, double length, double width )
{
    AcGeVector3d v( AcGeVector3d::kXAxis );
    v.rotateBy( angle, AcGeVector3d::kZAxis );

    AcDbPolyline* pl = new AcDbPolyline( 2 );
    pl->addVertexAt( 0, Point3D_To_2D( pt ) );
    pl->addVertexAt( 1, Point3D_To_2D( pt + v * length ) );
    pl->setConstantWidth( width );
    if( !ArxUtilHelper::PostToModelSpace( pl ) )
    {
        delete pl;
        return AcDbObjectId::kNull;
    }
    else
    {
        return pl->objectId();
    }
}

// ���Ƽ�ͷ
void ArxDrawHelper::DrawArrow( const AcGePoint3d& pt, double angle, double width, double length )
{
    AcGeVector3d v( AcGeVector3d::kXAxis );
    v.rotateBy( angle, AcGeVector3d::kZAxis );

    AcDbPolyline* pl = new AcDbPolyline( 2 );
    pl->addVertexAt( 0, Point3D_To_2D( pt ) );
    pl->addVertexAt( 1, Point3D_To_2D( pt + v * length ) );
    pl->setWidthsAt( 0, width, 0 );
    pl->setWidthsAt( 1, 0, 0 );
    ArxUtilHelper::PostToModelSpace( pl );
}

AcDbObjectId ArxDrawHelper::DrawRect( const AcGePoint3d& cnt, double angle, double width, double height )
{
    AcGePoint3dArray pts;
    BuildRect( cnt, angle, width, height, pts );
    return ArxDrawHelper::DrawPolyLine( pts, true );
}

AcDbObjectId ArxDrawHelper::DrawRect2( const AcGePoint3d& pt, double angle, double width, double height )
{
    AcGePoint3d insertPt = ArxDrawHelper::CaclPt2( pt, angle, 0.5 * width, 0.5 * height );
    return ArxDrawHelper::DrawRect( insertPt, angle, width, height );
}

void ArxDrawHelper::CreatePolygonLoop( AcDbHatch* pHatch, const AcGePoint3dArray& pts )
{
    AcGeIntArray edgeTypes;
    AcGeVoidPointerArray edgePtrs;

    int n = pts.length();
    for( int i = 0; i < n; i++ )
    {
        AcGePoint2d p1 = Point3D_To_2D( pts[i] );
        AcGePoint2d p2 = Point3D_To_2D( pts[( i + 1 ) % n] );
        AcGeLineSeg2d* pLine = new AcGeLineSeg2d( p1, p2 );

        edgePtrs.append( pLine );
        edgeTypes.append( AcDbHatch::kLine );
    }

    pHatch->appendLoop( AcDbHatch::kDefault, edgePtrs, edgeTypes );
}

void ArxDrawHelper::CreateCircleLoop( AcDbHatch* pHatch, const AcGePoint3d& pt, double radius )
{
    AcGeCircArc2d* cirArc = new AcGeCircArc2d();
    cirArc->setCenter( Point3D_To_2D( pt ) );
    cirArc->setRadius( radius );
    cirArc->setAngles( 0.0, PI * 2 );

    AcGeIntArray edgeTypes;
    AcGeVoidPointerArray edgePtrs;

    edgeTypes.append( AcDbHatch::kCirArc );
    edgePtrs.append( ( void* )cirArc );

    pHatch->appendLoop( AcDbHatch::kDefault, edgePtrs, edgeTypes );
}

void ArxDrawHelper::CreatePreDefinedHatch( AcDbHatch* pHatch, const CString& patName, double scale )
{
    // Set hatch plane
    pHatch->setNormal( AcGeVector3d::kZAxis );
    pHatch->setElevation( 0.0 );

    // Set non associative hatch
    pHatch->setAssociative( Adesk::kFalse );

    // Set hatch pattern to SolidFill type
    // ����hatch pattern֮���ٵ���setPattern������Ч
    pHatch->setPatternScale( scale );
    pHatch->setPattern( AcDbHatch::kPreDefined, patName );

    // Set hatch style to kNormal
    pHatch->setHatchStyle( AcDbHatch::kNormal );
}

void ArxDrawHelper::CreateGradientObject( AcDbHatch* pHatch, const CString& gradName, const AcCmColor& c1, const AcCmColor& c2 )
{
    // Set hatch plane
    pHatch->setNormal( AcGeVector3d::kZAxis );
    pHatch->setElevation( 0.0 );

    // Set non associative hatch
    pHatch->setAssociative( Adesk::kFalse );

    // Set hatch pattern to SolidFill type
    //pHatch->setPattern(AcDbHatch::kPreDefined, _T("SOLID"));

    // Set hatch style to kNormal
    //pHatch->setHatchStyle(AcDbHatch::kNormal);

    // ����Ϊ����ɫ���
    pHatch->setHatchObjectType( AcDbHatch::kGradientObject );

    // set gradient
    pHatch->setGradient( AcDbHatch::kPreDefinedGradient, gradName );
    pHatch->setGradientOneColorMode( false ); // ʵ���϶���˫ɫ

    AcCmColor colors[2] = {c1, c2};
    float values[2] = {0.0f, 1.0f};

    pHatch->setGradientColors( 2, colors, values );
}

AcDbObjectId ArxDrawHelper::DrawPolygonHatch( const AcGePoint3dArray& pts, const CString& patName, double scale )
{
    if( pts.isEmpty() ) return AcDbObjectId::kNull;

    AcDbHatch* hatch = new AcDbHatch;
    // set color
    //AcCmColor color;
    //color.setRGB(r, g, b);
    //pHatch->setColor(color);

    CreatePreDefinedHatch( hatch, patName, scale );
    CreatePolygonLoop( hatch, pts );

    // Elaborate solid fill
    hatch->evaluateHatch();
    if( !ArxUtilHelper::PostToModelSpace( hatch ) )
    {
        delete hatch;
        return AcDbObjectId::kNull;
    }
    else
    {
        return hatch->objectId();
    }
}

AcDbObjectId ArxDrawHelper::DrawCircleGradient( const AcGePoint3d& pt, double radius, const CString& gradName, const AcCmColor& c1, const AcCmColor& c2 )
{
    AcDbHatch* hatch = new AcDbHatch;

    CreateGradientObject( hatch, gradName, c1, c2 );
    CreateCircleLoop( hatch, pt, radius );

    //pHatch->evaluateHatch();
    if( !ArxUtilHelper::PostToModelSpace( hatch ) )
    {
        delete hatch;
        return AcDbObjectId::kNull;
    }
    else
    {
        return hatch->objectId();
    }
}

// ����ֵ:
//		0  -- ����
//		1  -- ˳ʱ��
//	   -1  -- ��ʱ��
int ArxDrawHelper::ClockWise( const AcGePoint3dArray& polygon )
{
    int n = polygon.length();
    if ( n < 3 ) return 0;

    int count = 0;
    for( int i = 0; i < n; i++ )
    {
        int j = ( i + 1 ) % n;
        int k = ( i + 2 ) % n;
        double z  = ( polygon[j].x - polygon[i].x ) * ( polygon[k].y - polygon[j].y );
        z -= ( polygon[j].y - polygon[i].y ) * ( polygon[k].x - polygon[j].x );
        if ( z < 0 )
        {
            count--;
        }
        else if ( z > 0 )
        {
            count++;
        }
    }
    if ( count > 0 )
        return -1;
    else if ( count < 0 )
        return 1;
    else
        return 0;
}

// �պ϶��������ƫ��
bool ArxDrawHelper::OffSetPolygon( const AcGePoint3dArray& polygon, double offset, bool is_inner, AcGePoint3dArray& offset_polygon )
{
    // �ж϶���η���
    int dir = ClockWise( polygon );
    if( dir == 0 ) return false;

    // ���ڻ�����???
    int c = ( is_inner ? -1 : 1 );

    // ƫ�Ʒ���Ƕ�
    //		1) �����εķ����й�(dir)
    //		2) ��Ҫƫ�Ƶķ����й�(is_inner)
    double angle = c * dir * PI * 0.5;

    bool ret = true;

    int n = polygon.length();
    for( int i = 0; i < n; i++ )
    {
        int p1 = ( n + i - 1 ) % n, p2 = i % n, p3 = ( i + 1 ) % n;

        // �Ե����ƫ��
        // ����ƫ������
        AcGeVector3d v1 = polygon[p2] - polygon[p1];
        v1.normalize();
        v1.rotateBy( angle, AcGeVector3d::kZAxis );

        AcGeVector3d v2 = polygon[p3] - polygon[p2];
        v2.normalize();
        v2.rotateBy( angle, AcGeVector3d::kZAxis );

        // �����������ļн�
        double angle = v1.angleTo( v2 );
        double L = abs( offset / cos( angle * 0.5 ) );

        AcGeVector3d v = v1 + v2;
        v.normalize();

        offset_polygon.append( polygon[p2] + v * L );
    }
    return ret;
}

static Acad::ErrorStatus GetLinetypeId( const CString& linetype, AcDbObjectId& linetypeId )
{
    AcDbLinetypeTable* pLtpTbl;
    acdbHostApplicationServices()->workingDatabase()->getLinetypeTable( pLtpTbl, AcDb::kForRead );
    if ( !pLtpTbl->has( linetype ) )
    {
        pLtpTbl->close();
        return Acad::eBadLinetypeName;
    }
    pLtpTbl->getAt( linetype, linetypeId );
    pLtpTbl->close();
    return Acad::eOk;
}

static void AddLineType( CString lineTypeName )
{
    // �������ͣ����ַ�����
    Acad::ErrorStatus es;
    //es = acdbHostApplicationServices()->workingDatabase()->loadLineTypeFile(_T("CENTER"), _T("acadiso.lin"));
    es = acdbLoadLineTypeFile( lineTypeName, _T( "acadiso.lin" ), acdbHostApplicationServices()->workingDatabase() );
    // �����µ�AcDbMlineStyle����
    AcDbMlineStyle* pMlStyle = new AcDbMlineStyle;
    pMlStyle->initMlineStyle();
    pMlStyle->setName( _T( "NewStyle" ) );
    int index; // ������ʽ�е�Ԫ������
    //AcCmColor color; // ��ɫ
    AcDbObjectId linetypeId; // ���͵�ID
    // ��ӵ�һ��Ԫ�أ���ɫ�������ߣ�
    //color.setColorIndex(1); // ��ɫ
    GetLinetypeId( lineTypeName, linetypeId );
    //pMlStyle->addElement(index, 0, color, linetypeId);
    //// ��ӵڶ���Ԫ�أ���ɫ�����ߣ�
    //color.setColorIndex(5); // ��ɫ
    //GetLinetypeId("HIDDEN", linetypeId);
    //pMlStyle->addElement(index, 0.5, color, linetypeId);
    //// ��ӵ�����Ԫ�أ���ɫ�����ߣ�
    //pMlStyle->addElement(index, -0.5, color, linetypeId);
    //// ��������ʽ��ӵ�������ʽ�ֵ���
    AcDbDictionary* pDict;
    acdbHostApplicationServices()->workingDatabase()->getMLStyleDictionary( pDict, AcDb::kForWrite );
    AcDbObjectId mlStyleId;
    es = pDict->setAt( _T( "NewStyle" ), pMlStyle, mlStyleId );
    pDict->close();
    pMlStyle->close();
}

static void DrawDotLine( const AcGePoint3d& spt, const AcGePoint3d& ept )
{
    AddLineType( _T( "CENTER" ) );
    AcDbLine line( spt, ept );
    line.setLinetype( _T( "CENTER" ) );
}

AcDbObjectId ArxDrawHelper::Make2LineAngularDim( const AcGePoint3d& pt1, const AcGePoint3d& pt2,
        const AcGePoint3d& pt3, const AcGePoint3d& pt4,
        const AcGePoint3d& textPt )
{
    AcDb2LineAngularDimension* dim = new AcDb2LineAngularDimension( pt1, pt2, pt3, pt4, textPt );

    // arcPt automatically set from where text was placed,
    // unless you deliberately set the arcPt
    dim->setHorizontalRotation( 0 );
    dim->setTextPosition( textPt );
    dim->useSetTextPosition();    // make text go where user picked
    dim->setDatabaseDefaults();

    AcDbObjectId dimStyleId = ArxDrawHelper::GetDimStyle( DIM_STYLE_NAME );
    if( !dimStyleId.isNull() )
    {
        dim->setDimensionStyle( dimStyleId );
    }

    if( !ArxUtilHelper::PostToModelSpace( dim ) )
    {
        delete dim;
        return AcDbObjectId::kNull;
    }
    else
    {
        return dim->objectId();
    }
}

AcDbObjectId ArxDrawHelper::Make3PointAngularDim( const AcGePoint3d& centerPt, const AcGePoint3d& pt1,
        const AcGePoint3d& pt2, const AcGePoint3d& textPt )
{
    AcDb3PointAngularDimension* dim = new AcDb3PointAngularDimension( centerPt, pt1, pt2, textPt );

    // arcPt automatically set from where text was placed,
    // unless you deliberately set the arcPt
    dim->setHorizontalRotation( 0 );
    dim->setTextPosition( textPt );
    dim->useSetTextPosition();    // make text go where user picked
    dim->setDatabaseDefaults();

    AcDbObjectId dimStyleId = ArxDrawHelper::GetDimStyle( DIM_STYLE_NAME );
    if( !dimStyleId.isNull() )
    {
        dim->setDimensionStyle( dimStyleId );
    }

    if( !ArxUtilHelper::PostToModelSpace( dim ) )
    {
        delete dim;
        return AcDbObjectId::kNull;
    }
    else
    {
        return dim->objectId();
    }
}

AcDbObjectId ArxDrawHelper::MakeAlignedDim( const AcGePoint3d& pt1, const AcGePoint3d& pt2, const CString& text, double offset, bool clockwise, const CString& dimStyle )
{
    AcGeVector3d v = pt2 - pt1;
    double angle = v.angleTo( AcGeVector3d::kXAxis, -AcGeVector3d::kZAxis );
    v.normalize();
    int c = clockwise ? 1 : -1;
    v.rotateBy( c * PI * 0.5, AcGeVector3d::kZAxis );
    AcGePoint3d dimLinePoint = ArxDrawHelper::MidPoint( pt1, pt2 ) + v * offset;

    AcDbAlignedDimension* dim = new AcDbAlignedDimension;
    dim->setXLine1Point( pt1 );
    dim->setXLine2Point( pt2 );

    // dimLinePt automatically set from where text was placed,
    // unless you deliberately set the dimLinePt
    dim->setHorizontalRotation( angle );
    dim->setTextPosition( dimLinePoint );
	if(text != _T("")) {
		dim->setDimensionText(text);
	}
    dim->useSetTextPosition();    // make text go where user picked
    dim->setDatabaseDefaults();

	CString style = dimStyle;
	if(dimStyle == _T("")) style = DIM_STYLE_NAME;
    AcDbObjectId dimStyleId = ArxDrawHelper::GetDimStyle( style );
    if( !dimStyleId.isNull() )
    {
        dim->setDimensionStyle( dimStyleId );
    }

    if( !ArxUtilHelper::PostToModelSpace( dim ) )
    {
        delete dim;
        return AcDbObjectId::kNull;
    }
    else
    {
        return dim->objectId();
    }
}

AcDbObjectId ArxDrawHelper::MakeDiametricDim( const AcGePoint3d& centerPt, double radius, const AcGePoint3d& textPt )
{
    // get direction of dim line
    AcGeVector3d vDir = textPt - centerPt;
    vDir.normalize();

    AcDbDiametricDimension* dim = new AcDbDiametricDimension;
    dim->setChordPoint( centerPt + ( vDir * radius ) );
    dim->setFarChordPoint( centerPt + ( -vDir * radius ) );

    dim->setHorizontalRotation( 0 );
    dim->setTextPosition( textPt );
    dim->useSetTextPosition();    // make text go where user picked
    dim->setDatabaseDefaults();

    AcDbObjectId dimStyleId = ArxDrawHelper::GetDimStyle( DIM_STYLE_NAME );
    if( !dimStyleId.isNull() )
    {
        dim->setDimensionStyle( dimStyleId );
    }

    if( !ArxUtilHelper::PostToModelSpace( dim ) )
    {
        delete dim;
        return AcDbObjectId::kNull;
    }
    else
    {
        return dim->objectId();
    }
}

AcDbObjectId ArxDrawHelper::MakeOrdinateDim( Adesk::Boolean useXAxis, const AcGePoint3d& featurePt, const AcGePoint3d& leaderPt )
{
    AcDbOrdinateDimension* dim = new AcDbOrdinateDimension( useXAxis, featurePt, leaderPt );
    dim->setDatabaseDefaults();

    AcDbObjectId dimStyleId = ArxDrawHelper::GetDimStyle( DIM_STYLE_NAME );
    if( !dimStyleId.isNull() )
    {
        dim->setDimensionStyle( dimStyleId );
    }

    if( !ArxUtilHelper::PostToModelSpace( dim ) )
    {
        delete dim;
        return AcDbObjectId::kNull;
    }
    else
    {
        return dim->objectId();
    }
}

AcDbObjectId ArxDrawHelper::MakeRadialDim( const AcGePoint3d& centerPt, double radius, const AcGePoint3d& textPt )
{
    acutPrintf( _T( "\nTesting make of AcDbRadialDimension..." ) );

    // get direction of dim line
    AcGeVector3d vDir = textPt - centerPt;
    vDir.normalize();

    AcDbRadialDimension* dim = new AcDbRadialDimension;
    dim->setCenter( centerPt );
    dim->setChordPoint( centerPt + ( vDir * radius ) );

    dim->setHorizontalRotation( 0 );
    dim->setTextPosition( textPt );
    dim->useSetTextPosition();    // make text go where user picked
    dim->setDatabaseDefaults();

    AcDbObjectId dimStyleId = ArxDrawHelper::GetDimStyle( DIM_STYLE_NAME );
    if( !dimStyleId.isNull() )
    {
        dim->setDimensionStyle( dimStyleId );
    }

    if( !ArxUtilHelper::PostToModelSpace( dim ) )
    {
        delete dim;
        return AcDbObjectId::kNull;
    }
    else
    {
        return dim->objectId();
    }
}

AcDbObjectId ArxDrawHelper::MakeRotatedDim(	const AcGePoint3d& pt1, const AcGePoint3d& pt2, double ang, const AcGePoint3d& textPt )
{
    AcDbRotatedDimension* dim = new AcDbRotatedDimension;
    dim->setXLine1Point( pt1 );
    dim->setXLine2Point( pt2 );
    dim->setRotation( ang );

    // dimLinePt automatically set from where text was placed,
    // unless you deliberately set the dimLinePt
    dim->setHorizontalRotation( 0 );
    dim->setTextPosition( textPt );
    dim->useSetTextPosition();    // make text go where user picked
    dim->setDatabaseDefaults();

    AcDbObjectId dimStyleId = ArxDrawHelper::GetDimStyle( DIM_STYLE_NAME );
    if( !dimStyleId.isNull() )
    {
        dim->setDimensionStyle( dimStyleId );
    }

    if( !ArxUtilHelper::PostToModelSpace( dim ) )
    {
        delete dim;
        return AcDbObjectId::kNull;
    }
    else
    {
        return dim->objectId();
    }
}

//http://blog.csdn.net/foreverling/article/details/28267307
/*
static void qxzyOperateLayer_AddStyle(void)
{
AcDbTextStyleTable *pTextStyleTbl;
acdbHostApplicationServices()->workingDatabase()
->getTextStyleTable(pTextStyleTbl, AcDb::kForWrite);

AcDbTextStyleTableRecord *pTextStyleTblRcd;
pTextStyleTblRcd = new AcDbTextStyleTableRecord();
pTextStyleTblRcd->setName(_T("������"));
pTextStyleTblRcd->setFileName(_T("simfang.ttf"));
pTextStyleTblRcd->setXScale(0.7);

pTextStyleTbl->add(pTextStyleTblRcd);

pTextStyleTblRcd->close();
pTextStyleTbl->close();
}

��������Ʋ�һ���������ļ���������ͬ���򿪿�����壬���롰���塱�ļ��У��Ҽ������������塱ͼ�꣬�ӵ����Ŀ�ݲ˵���ѡ�����ԡ��˵��ϵͳ�ᵯ���Ի�����ʾ�����ļ������ơ�
*/
AcDbObjectId ArxDrawHelper::CreateTextstyle( const CString& textStyleName, bool modifyExistStyle )
{
    AcDbTextStyleTable* pTextStyleTbl;
    if( Acad::eOk != acdbHostApplicationServices()->workingDatabase()->getTextStyleTable( pTextStyleTbl, AcDb::kForRead ) )
        return AcDbObjectId::kNull;

    AcDbTextStyleTableRecord* pTextStyleTblRcd;
    AcDbObjectId textRecordId;
    if ( !pTextStyleTbl->has( textStyleName ) )
    {
        pTextStyleTblRcd = new AcDbTextStyleTableRecord();
        pTextStyleTbl->add( textRecordId, pTextStyleTblRcd );
    }
    else
    {
        if( !modifyExistStyle )
        {
            pTextStyleTbl->getAt( textStyleName, textRecordId );
            pTextStyleTbl->close();
            return textRecordId;
        }
        else
        {
            pTextStyleTbl->getAt( textStyleName, pTextStyleTblRcd, AcDb::kForWrite );
        }
    }
    pTextStyleTbl->close();

    //����������ʽ������
    pTextStyleTblRcd->setName( textStyleName );
    pTextStyleTblRcd->setFileName( _T( "romans" ) );
    pTextStyleTblRcd->setBigFontFileName( _T( "hzdx" ) );
    pTextStyleTblRcd->setXScale( 0.8 );
    pTextStyleTblRcd->setFont( _T( "����_GB2312" ), 0, 0, 134, 49 );
    pTextStyleTblRcd->close();
    //acdbHostApplicationServices()->workingDatabase()->setTextstyle(fontId);

    return pTextStyleTblRcd->objectId();
}

AcDbObjectId ArxDrawHelper::GetTextStyleId( const CString& textStyleName )
{
    AcDbTextStyleTable* pTextStyleTbl;
    if( Acad::eOk != acdbHostApplicationServices()->workingDatabase()->getTextStyleTable( pTextStyleTbl, AcDb::kForRead ) )
        return AcDbObjectId::kNull;

    AcDbObjectId textStyleId;
    pTextStyleTbl->getAt( textStyleName, textStyleId );
    pTextStyleTbl->close();

    return textStyleId;
}

//http://blog.csdn.net/foreverling/article/details/28268811
/*
static void qxzyAddDimStyle_AddDimStyle(void)
{
ACHAR styleName[50];
if(acedGetString(Adesk::kFalse, _T("��������ʽ����:"), styleName) != RTNORM)
{
return;
}

AcDbDimStyleTable *pDimStyleTbl;
acdbHostApplicationServices()->workingDatabase()
->getDimStyleTable(pDimStyleTbl, AcDb::kForWrite);

if(pDimStyleTbl->has(styleName))
{
pDimStyleTbl->close();
return;
}

AcDbDimStyleTableRecord *pDimStyleTblRcd;
pDimStyleTblRcd = new AcDbDimStyleTableRecord();

pDimStyleTblRcd->setName(styleName);//��ʽ����
pDimStyleTblRcd->setDimasz(3);//��ͷ����
pDimStyleTblRcd->setDimexe(3);//�ߴ�������ע
pDimStyleTblRcd->setDimtad(1);//����λ�ڱ�ע�ߵ��Ϸ�
pDimStyleTblRcd->setDimtxt(3);//��ע���ֵĸ߶�

pDimStyleTbl->add(pDimStyleTblRcd);

pDimStyleTblRcd->close();
pDimStyleTbl->close();
}
*/
AcDbObjectId ArxDrawHelper::CreateDimStyle( const CString& dimStyleName, bool modifyExistStyle, double bili )
{
    AcDbDimStyleTable* pDimStyleTbl;
    if( Acad::eOk != acdbHostApplicationServices()->workingDatabase()->getSymbolTable( pDimStyleTbl, AcDb::kForWrite ) )
        return AcDbObjectId::kNull;

    AcDbDimStyleTableRecord* pDimStyleTblRcd = 0;
    AcDbObjectId dimRecordId;
    if ( !pDimStyleTbl->has( dimStyleName ) )
    {
        pDimStyleTblRcd = new AcDbDimStyleTableRecord();
        pDimStyleTbl->add( dimRecordId, pDimStyleTblRcd );
    }
    else
    {
        if( !modifyExistStyle )
        {
            pDimStyleTbl->getAt( dimStyleName, dimRecordId );
            pDimStyleTbl->close();
            return dimRecordId;
        }
        else
        {
            pDimStyleTbl->getAt( dimStyleName, pDimStyleTblRcd, AcDb::kForWrite );
        }
    }
    pDimStyleTbl->close();

    //���ñ�ע��ʽ������
    pDimStyleTblRcd->setName( dimStyleName ); // ��ʽ����
    pDimStyleTblRcd->setDimasz( 5 * bili ); // ��ͷ����
    //pDimStyleTblRcd->setDimblk("_Oblique");//���ü�ͷ����״Ϊ�������
    pDimStyleTblRcd->setDimexe( 10 * bili ); // ָ���ߴ���߳����ߴ��ߵľ���
    pDimStyleTblRcd->setDimlfac( 1 ); //��������
    pDimStyleTblRcd->setDimdec( 0 ); //���ñ�ע����λ��ʾ��С��λλ����0Ϊbyblock��256Ϊbylayer
    AcCmColor clr;
    clr.setColorIndex( 256 );
    pDimStyleTblRcd->setDimclrd( clr ); //Ϊ�ߴ��ߡ���ͷ�ͱ�ע����ָ����ɫ��0Ϊbyblock��256Ϊbylayer
    pDimStyleTblRcd->setDimclre( clr ); //Ϊ�ߴ����ָ����ɫ������ɫ������������Ч����ɫ���
    pDimStyleTblRcd->setDimclrt( clr ); //Ϊ��ע����ָ����ɫ��0Ϊbyblock��256Ϊbylayer
    pDimStyleTblRcd->setDimexo( 1 * bili ); //ָ���ߴ����ƫ��ԭ��ľ���
    pDimStyleTblRcd->setDimgap( 2 * bili ); //���ִӳߴ���ƫ�� '���ߴ��߷ֳɶ���������֮����ñ�ע����ʱ�����ñ�ע������Χ�ľ���
    pDimStyleTblRcd->setDimjust( 0 ); //���Ʊ�ע���ֵ�ˮƽλ��
    pDimStyleTblRcd->setDimtix( 1 ); //���ñ�ע����ʼ�ջ����ڳߴ����֮��

    //'.SetVariable "DimJust", 0       '���Ʊ�ע���ֵ�ˮƽλ��
    // '0  ���������ڳߴ���֮�ϣ����ڳߴ����֮�����ж���
    // '1  ���ڵ�һ���ߴ���߷��ñ�ע����
    // '2  ���ڵڶ����ߴ���߷��ñ�ע����
    // '3  ����ע���ַ��ڵ�һ���ߴ�������ϣ�����֮����
    //'4  ����ע���ַ��ڵڶ����ߴ�������ϣ�����֮����
    pDimStyleTblRcd->setDimtmove( 0 ); //���ñ�ע���ֵ��ƶ�����
    //'0  �ߴ��ߺͱ�ע����һ���ƶ�
    //'1  ���ƶ���ע����ʱ���һ������
    // '2  �����ע���������ƶ��������������

    //AcDbObjectId textStyleId = ArxDrawHelper::GetTextStyleId(textStyleName);
    //if(!textStyleId.isNull())
    //{
    //	pDimStyleTblRcd->setDimtxsty(textStyleId);//ָ����ע��������ʽ
    //}
    pDimStyleTblRcd->setDimtxt( 5*bili ); //ָ����ע���ֵĸ߶ȣ����ǵ�ǰ������ʽ���й̶��ĸ߶�
    pDimStyleTblRcd->setDimtad( 1 * bili ); // ����λ�ڱ�ע�ߵ��Ϸ�

    pDimStyleTblRcd->close();

    return pDimStyleTblRcd->objectId();
}

AcDbObjectId ArxDrawHelper::GetDimStyle( const CString& dimStyleName )
{
    AcDbDimStyleTable* pDimStyleTbl;
    if( Acad::eOk != acdbHostApplicationServices()->workingDatabase()->getDimStyleTable( pDimStyleTbl, AcDb::kForRead ) )
        return AcDbObjectId::kNull;

    AcDbObjectId dimStyleId;
    pDimStyleTbl->getAt( dimStyleName, dimStyleId );
    pDimStyleTbl->close();

    return dimStyleId;
}

void ArxDrawHelper::SetLineType( const AcDbObjectId& objId, const CString& ltName )
{
    AcTransaction* pTrans = actrTransactionManager->startTransaction();
    if( pTrans == 0 ) return;

    //AcDb::OpenMode om = ( save ? ( AcDb::kForWrite ) : ( AcDb::kForRead ) );
    AcDbObject* pObj;
    if( Acad::eOk != pTrans->getObject( pObj, objId, AcDb::kForWrite ) )
    {
        actrTransactionManager->abortTransaction();
        return;
    }

    AcDbEntity* pEnt = AcDbEntity::cast( pObj );
    if( pEnt == 0 )
    {
        actrTransactionManager->abortTransaction();
        return;
    }

    pEnt->setLinetype( ltName );

    actrTransactionManager->endTransaction();
}

void ArxDrawHelper::SetLineType( const AcDbObjectIdArray& objIds, const CString& ltName )
{
    AcTransaction* pTrans = actrTransactionManager->startTransaction();
    if( pTrans == 0 ) return;

    for( int i = 0; i < objIds.length(); i++ )
    {
        //AcDb::OpenMode om = ( save ? ( AcDb::kForWrite ) : ( AcDb::kForRead ) );
        AcDbObject* pObj;
        if( Acad::eOk != pTrans->getObject( pObj, objIds[i], AcDb::kForWrite ) ) continue;

        AcDbEntity* pEnt = AcDbEntity::cast( pObj );
        if( pEnt == 0 ) continue;;

        pEnt->setLinetype( ltName );
    }
    actrTransactionManager->endTransaction();
}
