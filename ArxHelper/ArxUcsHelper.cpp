#include "StdAfx.h"
#include "HelperClass.h"

/****************************************************************************
**
**	ArxCoordSystemHelper::transformToWcs
**
**	**jma
**
*************************************/

void ArxUcsHelper::transformToWcs( AcDbEntity* ent, AcDbDatabase* db )
{
    ASSERT( ent->isWriteEnabled() );
    ASSERT( db != NULL );

    AcGeMatrix3d m;
    getUcsToWcsMatrix( m, db );
    Acad::ErrorStatus es = ent->transformBy( m );

    ASSERT( es == Acad::eOk );
}

/****************************************************************************
**
**	ArxCoordSystemHelper::transformToUcs
**
**	**jma
**
*************************************/

void ArxUcsHelper::transformToUcs( AcDbEntity* ent, AcDbDatabase* db )
{
    ASSERT( ent->isWriteEnabled() );
    ASSERT( db != NULL );

    AcGeMatrix3d m;
    getWcsToUcsMatrix( m, db );
    Acad::ErrorStatus es = ent->transformBy( m );

    ASSERT( es == Acad::eOk );
}

/****************************************************************************
**
**	ArxCoordSystemHelper::getUcsXAxis
**		returns current UCS X Axis, even if currently the paperSpace viewport
**
**	**jma
**
*************************************/

AcGeVector3d ArxUcsHelper::getUcsXAxis( AcDbDatabase* db )
{
    ASSERT( db != NULL );

    AcGeMatrix3d m;

    if ( acdbUcsMatrix( m, db ) )
    {
        AcGePoint3d origin;
        AcGeVector3d xDir, yDir, zDir;

        m.getCoordSystem( origin, xDir, yDir, zDir );
        return xDir;
    }
    else
    {
        ASSERT( 0 );
        return AcGeVector3d::kXAxis;
    }
}

/****************************************************************************
**
**	ArxCoordSystemHelper::getUcsYAxis
**		returns current UCS Y Axis, even if currently the paperSpace viewport
**
**	**jma
**
*************************************/

AcGeVector3d ArxUcsHelper::getUcsYAxis( AcDbDatabase* db )
{
    ASSERT( db != NULL );

    AcGeMatrix3d m;

    if ( acdbUcsMatrix( m, db ) )
    {
        AcGePoint3d origin;
        AcGeVector3d xDir, yDir, zDir;

        m.getCoordSystem( origin, xDir, yDir, zDir );
        return yDir;
    }
    else
    {
        ASSERT( 0 );
        return AcGeVector3d::kYAxis;
    }
}

/****************************************************************************
**
**	ArxCoordSystemHelper::getUcsZAxis
**
**	**jma
**
*************************************/

AcGeVector3d ArxUcsHelper::getUcsZAxis( AcDbDatabase* db )
{
    ASSERT( db != NULL );

    AcGeMatrix3d m;

    if ( acdbUcsMatrix( m, db ) )
    {
        AcGePoint3d origin;
        AcGeVector3d xDir, yDir, zDir;

        m.getCoordSystem( origin, xDir, yDir, zDir );
        return zDir;
    }
    else
    {
        ASSERT( 0 );
        return AcGeVector3d::kZAxis;
    }
}

/****************************************************************************
**
**	ArxCoordSystemHelper::getUcsPlane
**
**	**jma
**
*************************************/

AcGePlane ArxUcsHelper::getUcsPlane( AcDbDatabase* db )
{
    ASSERT( db != NULL );

    AcGeMatrix3d m;

    if ( acdbUcsMatrix( m, db ) )
    {
        AcGePoint3d origin;
        AcGeVector3d xDir, yDir, zDir;

        m.getCoordSystem( origin, xDir, yDir, zDir );
        AcGePlane ucsPlane( origin, xDir, yDir );
        return ucsPlane;
    }
    else
    {
        ASSERT( 0 );
        AcGePlane ucsPlane( AcGePoint3d::kOrigin, AcGeVector3d::kIdentity );
        return ucsPlane;
    }
}

/****************************************************************************
**
**    ArxCoordSystemHelper::getUcsToWcsMatrix
**
**    **jma
**
*************************************/

void ArxUcsHelper::getUcsToWcsMatrix( AcGeMatrix3d& m, AcDbDatabase* db )
{
    ASSERT( db != NULL );

    if ( !acdbUcsMatrix( m, db ) )
    {
        m.setToIdentity();
        ASSERT( 0 );
    }
}

/****************************************************************************
**
**	ArxCoordSystemHelper::getWcsToUcsMatrix
**
**	**jma
**
*************************************/

void ArxUcsHelper::getWcsToUcsMatrix( AcGeMatrix3d& m, AcDbDatabase* db )
{
    getUcsToWcsMatrix( m, db );
    m.invert();
}

/****************************************************************************
**
**	ArxCoordSystemHelper::getUcsToWcsOriginMatrix
**		move an object form one coordinate system to another.
**
**	NOTE:    The basePt must be passed in as a WCS point!
**
**	**jma
**
*************************************/

void ArxUcsHelper::getUcsToWcsOriginMatrix( AcGeMatrix3d& m,
        const AcGePoint3d& wcsBasePt, AcDbDatabase* db )
{
    ASSERT( db != NULL );

    AcGeMatrix3d tmpMat;

    if ( acdbUcsMatrix( tmpMat, db ) )
    {
        AcGePoint3d origin;
        AcGeVector3d xDir, yDir, zDir;

        tmpMat.getCoordSystem( origin, xDir, yDir, zDir );
        origin += wcsBasePt.asVector();

        m.setToAlignCoordSys( origin, xDir, yDir, zDir,
                              AcGePoint3d::kOrigin, AcGeVector3d::kXAxis,
                              AcGeVector3d::kYAxis, AcGeVector3d::kZAxis );
    }
    else
    {
        ASSERT( 0 );
        m = AcGeMatrix3d::kIdentity;
    }
}

/****************************************************************************
**
**	ArxCoordSystemHelper::getEcsPlane
**		This is the ECS plane for an AutoCAD entity. It can then be used to
**	calculate angles relative to the ECS plane, for instance, angles of
**	AcDbArc, AcDbBlockReference
**
**	**jma
**
*************************************/

void ArxUcsHelper::getEcsPlane( const AcGeVector3d& entNormal, AcGePlane& ecsPlane )
{
    AcGeMatrix3d ecsMat;
    getEcsToWcsMatrix( AcGePoint3d::kOrigin, entNormal, ecsMat );

    AcGePoint3d origin;
    AcGeVector3d xAxis, yAxis, zAxis;
    ecsMat.getCoordSystem( origin, xAxis, yAxis, zAxis );
    ecsPlane.set( origin, xAxis, yAxis );
}

/****************************************************************************
**
**	ArxCoordSystemHelper::getEcsPlane
**	same as above, but also return the XAxis of ECS, and use the origin
**	passed in for the plane
**
**	**jma
**
*************************************/

void ArxUcsHelper::getEcsPlane( const AcGePoint3d& origin,
                                const AcGeVector3d& entNormal, AcGePlane& ecsPlane,
                                AcGeVector3d& ecsXAxis )
{
    AcGeMatrix3d ecsMat;
    getEcsToWcsMatrix( origin, entNormal, ecsMat );

    AcGePoint3d tmpOrigin;
    AcGeVector3d yAxis, zAxis;
    ecsMat.getCoordSystem( tmpOrigin, ecsXAxis, yAxis, zAxis );
    ecsPlane.set( tmpOrigin, ecsXAxis, yAxis );
}

/****************************************************************************
**
**	ArxCoordSystemHelper::getEcsXAxis
**
**	**jma
**
*************************************/

void ArxUcsHelper::getEcsXAxis( const AcGeVector3d& ecsZAxis, AcGeVector3d& xAxis )
{
    AcGeMatrix3d arbMat;
    getEcsToWcsMatrix( AcGePoint3d::kOrigin, ecsZAxis, arbMat );

    AcGePoint3d origin;
    AcGeVector3d yAxis, zAxis;

    arbMat.getCoordSystem( origin, xAxis, yAxis, zAxis );  // return xAxis;
}

/****************************************************************************
**
**	ArxCoordSystemHelper::getEcsToWcsMatrix
**		run AutoCAD's arbitrary matrix algorithm for ECS entities
**
**	**jma
**
*************************************/

void ArxUcsHelper::getEcsToWcsMatrix( const AcGePoint3d& origin, const AcGeVector3d& zAxis, AcGeMatrix3d& mat )
{
    const double kArbBound = 0.015625;         //  1/64th

    // short circuit if in WCS already
    if ( zAxis == AcGeVector3d::kZAxis )
    {
        mat.setToIdentity();
        return;
    }

    AcGeVector3d xAxis, yAxis;

    ASSERT( zAxis.isUnitLength() );

    if ( ( fabs( zAxis.x ) < kArbBound ) && ( fabs( zAxis.y ) < kArbBound ) )
        xAxis = AcGeVector3d::kYAxis.crossProduct( zAxis );
    else
        xAxis = AcGeVector3d::kZAxis.crossProduct( zAxis );

    xAxis.normalize();
    yAxis = zAxis.crossProduct( xAxis );
    yAxis.normalize();

    mat.setCoordSystem( AcGePoint3d::kOrigin, xAxis, yAxis, zAxis );
}

/****************************************************************************
**
**	ArxCoordSystemHelper::wcsToUcs
**
**	**jma
**
*************************************/

AcGePoint3d ArxUcsHelper::wcsToUcs( const AcGePoint3d& pt )
{
    AcDbDatabase* db = acdbHostApplicationServices()->workingDatabase();
    ASSERT( db != NULL );

    AcGeMatrix3d m;

    getWcsToUcsMatrix( m, db );
    return m * pt;
}

/****************************************************************************
**
**	ArxCoordSystemHelper::wcsToUcs
**
**	**jma
**
*************************************/

AcGeVector3d ArxUcsHelper::wcsToUcs( const AcGeVector3d& vec )
{
    AcDbDatabase* db = acdbHostApplicationServices()->workingDatabase();
    ASSERT( db != NULL );

    AcGeMatrix3d m;

    getWcsToUcsMatrix( m, db );

    AcGeVector3d newv = vec;
    newv.transformBy( m );

    return newv;
}

/****************************************************************************
**
**	ArxCoordSystemHelper::wcsToUcs
**
**	**jma
**
*************************************/

void ArxUcsHelper::wcsToUcs( AcGePoint3dArray& ptArray )
{
    AcDbDatabase* db = acdbHostApplicationServices()->workingDatabase();
    ASSERT( db != NULL );

    AcGeMatrix3d m;
    getWcsToUcsMatrix( m, db );

    int len = ptArray.length();
    for ( int i = 0; i < len; i++ )
        ptArray[i] = m * ptArray[i];
}

/****************************************************************************
**
**	ArxCoordSystemHelper::ucsToWcs
**
**	**jma
**
*************************************/

AcGePoint3d ArxUcsHelper::ucsToWcs( const AcGePoint3d& pt )
{
    AcDbDatabase* db = acdbHostApplicationServices()->workingDatabase();
    ASSERT( db != NULL );

    AcGeMatrix3d m;

    getUcsToWcsMatrix( m, db );
    return m * pt;
}

/****************************************************************************
**
**	ArxCoordSystemHelper::ucsToWcs
**
**	**jma
**
*************************************/

AcGeVector3d ArxUcsHelper::ucsToWcs( const AcGeVector3d& vec )
{
    AcDbDatabase* db = acdbHostApplicationServices()->workingDatabase();
    ASSERT( db != NULL );

    AcGeMatrix3d m;

    getUcsToWcsMatrix( m, db );

    AcGeVector3d newv = vec;
    newv.transformBy( m );

    return newv;
}

/****************************************************************************
**
**	ArxCoordSystemHelper::ucsToWcs
**
**	**jma
**
*************************************/

void ArxUcsHelper::ucsToWcs( AcGePoint3dArray& ptArray )
{
    AcDbDatabase* db = acdbHostApplicationServices()->workingDatabase();
    ASSERT( db != NULL );

    AcGeMatrix3d m;
    getUcsToWcsMatrix( m, db );

    int len = ptArray.length();
    for ( int i = 0; i < len; i++ )
        ptArray[i] = m * ptArray[i];
}

/************************************************************************
**
**	ArxCoordSystemHelper::ecsToWcs
**
**	**jma
**
***************************************/

AcGePoint3d ArxUcsHelper::ecsToWcs( const AcGePoint3d& pt, const AcGeVector3d& entNormal )
{
    AcGeMatrix3d m;
    getEcsToWcsMatrix( AcGePoint3d::kOrigin, entNormal, m );

    return m * pt;
}

/************************************************************************
**
**	ArxCoordSystemHelper::ecsToWcs
**
**	**jma
**
***************************************/

AcGeVector3d ArxUcsHelper::ecsToWcs( const AcGeVector3d& vec, const AcGeVector3d& entNormal )
{
    AcGeMatrix3d m;
    getEcsToWcsMatrix( AcGePoint3d::kOrigin, entNormal, m );

    return m * vec;
}

/************************************************************************
**
**	ArxCoordSystemHelper::dcsToUcs
**
**	**jma
**
***************************************/

AcGePoint3d ArxUcsHelper::dcsToUcs( const AcGePoint2d& pt )
{
    resbuf fromRb, toRb;
    ads_point newPt;

    fromRb.restype = RTSHORT;
    fromRb.resval.rint = AcDb::kCurDisplayCS;

    toRb.restype = RTSHORT;
    toRb.resval.rint = AcDb::kUserCS;

    short result = acedTrans( asDblArray( pt ), &fromRb, &toRb, FALSE, newPt );
    ASSERT( result == RTNORM );

    return asPnt3d( newPt );
}

/************************************************************************
**
**	ArxCoordSystemHelper::ucsToDcs
**
**	**jma
**
***************************************/

AcGePoint2d ArxUcsHelper::ucsToDcs( const AcGePoint3d& pt )
{
    resbuf fromRb, toRb;
    ads_point newPt;

    fromRb.restype = RTSHORT;
    fromRb.resval.rint = AcDb::kUserCS;

    toRb.restype = RTSHORT;
    toRb.resval.rint = AcDb::kCurDisplayCS;

    short result = acedTrans( asDblArray( pt ), &fromRb, &toRb, FALSE, newPt );
    ASSERT( result == RTNORM );

    return asPnt2d( newPt );
}

//ucs参考代码
//http://forums.autodesk.com/t5/objectarx/how-to-set-current-ucs/td-p/2513614
/*
AcGeMatrix3d mat;

// Set to world UCS
mat.setCoordSystem(AcGePoint3d(0,0,0), AcGeVector3d::kXAxis, AcGeVector3d::kYAxis, AcGeVector3d::kZAxis);
acedSetCurrentUCS(mat);

// Setup the new UCS
AcGePoint3d ucsOrig(5, 10, 12);
AcGeVector3d zAxis(0.3, 1.92, 0.89);
AcGeVector3d xAxis = zAxis.perpVector();
AcGeVector3d yAxis = zAxis.crossProduct(xAxis);
xAxis.normalize();
yAxis.normalize();
zAxis.normalize();
mat.setCoordSystem(ucsOrig, xAxis, yAxis, zAxis);
acedSetCurrentUCS(mat);

// Translate the UCS (world) origin for use in acedGetPoint (optional).
AcGePoint3d transPnt;
acdbWcs2Ucs(asDblArray(ucsOrig), asDblArray(transPnt), false);

AcGePoint3d pnt;
if(acedGetPoint(asDblArray(transPnt), _T("\nPick UCS origin: "), asDblArray(pnt)) != RTNORM)
return;
pnt.transformBy(mat);

// Set the UCS to the point picked.
mat.setCoordSystem(pnt, xAxis, yAxis, zAxis);
acedSetCurrentUCS(mat);
*/
//http://blog.csdn.net/foreverling/article/details/28393085

AcDbObjectId ArxUcsHelper::CreateUCS( const AcGePoint3d& origin, const AcGeVector3d& xAxis, const AcGeVector3d& yAxis )
{
    //生成一个GUIID的临时字符串
    CString name;
    if( !ArxUtilHelper::NewGUID( name ) ) return AcDbObjectId::kNull;

    AcDbUCSTable* pUcsTbl;
    acdbHostApplicationServices()->workingDatabase()
    ->getUCSTable( pUcsTbl, AcDb::kForWrite );

    AcDbUCSTableRecord* pUcsTblRcd;
    pUcsTblRcd = new AcDbUCSTableRecord();

    Acad::ErrorStatus es = pUcsTblRcd->setName( name );
    if( es != Acad::eOk )
    {
        delete pUcsTblRcd;
        pUcsTbl->close();
        return AcDbObjectId::kNull;
    }

    pUcsTblRcd->setOrigin( origin );
    pUcsTblRcd->setXAxis( xAxis );
    pUcsTblRcd->setYAxis( yAxis );

    es = pUcsTbl->add( pUcsTblRcd );
    if( es != Acad::eOk )
    {
        delete pUcsTblRcd;
        pUcsTbl->close();
        return AcDbObjectId::kNull;
    }
    pUcsTblRcd->close();
    pUcsTbl->close();

    return pUcsTblRcd->objectId();
}

static bool GetUCSMatrix( const AcDbObjectId& ucsId, AcGeMatrix3d& mat )
{
    if( ucsId.isNull() ) return false;

    AcTransaction* pTrans = actrTransactionManager->startTransaction();
    if( pTrans == 0 ) return false;

    //AcDb::OpenMode om = ( save ? ( AcDb::kForWrite ) : ( AcDb::kForRead ) );
    AcDbObject* pObj;
    if( Acad::eOk != pTrans->getObject( pObj, ucsId, AcDb::kForRead ) )
    {
        actrTransactionManager->abortTransaction();
        return false;
    }
    AcDbUCSTableRecord* pUcsTblRcd = AcDbUCSTableRecord::cast( pObj );
    if( pUcsTblRcd == 0 )
    {
        actrTransactionManager->abortTransaction();
        return false;
    }

    AcGeVector3d vecXAxis, vecYAxis, vecZAxis;
    vecXAxis = pUcsTblRcd->xAxis();
    vecYAxis = pUcsTblRcd->yAxis();
    vecZAxis = vecXAxis.crossProduct( vecYAxis );
    mat.setCoordSystem( pUcsTblRcd->origin(), vecXAxis, vecYAxis, vecZAxis );

    actrTransactionManager->endTransaction();
    return true;
}

bool ArxUcsHelper::SetCurrentUCS( const AcDbObjectId& ucsId )
{
    AcGeMatrix3d mat;
    if( !GetUCSMatrix( ucsId, mat ) ) return false;
    Acad::ErrorStatus es = acedSetCurrentUCS( mat );
    return ( Acad::eOk == es );
}

void ArxUcsHelper::MoveCurrentUCSOrigin( const AcGeVector3d& v )
{
    // 获得当前UCS的变换矩阵
    AcGeMatrix3d mat;
    Acad::ErrorStatus es = acedGetCurrentUCS( mat );

    // 根据变换矩阵获得UCS的参数
    AcGePoint3d ptOrigin;
    AcGeVector3d vecXAxis, vecYAxis, vecZAxis;
    mat.getCoordSystem( ptOrigin, vecXAxis, vecYAxis, vecZAxis );

    // 移动UCS的原点
    ptOrigin += v;

    // 更新变换矩阵
    mat.setCoordSystem( ptOrigin, vecXAxis, vecYAxis, vecZAxis );

    // 应用新的UCS
    acedSetCurrentUCS( mat );
}

void ArxUcsHelper::RotateCurrentUCS( double angle, int axis )
{
    if( axis < 0 || axis > 2 ) return;

    // 获得当前UCS的变换矩阵
    AcGeMatrix3d mat;
    Acad::ErrorStatus es = acedGetCurrentUCS( mat );

    // 根据变换矩阵获得UCS的参数
    AcGePoint3d ptOrigin;
    AcGeVector3d vecXAxis, vecYAxis, vecZAxis;
    mat.getCoordSystem( ptOrigin, vecXAxis, vecYAxis, vecZAxis );

    AcGeVector3d vAxis;
    if( axis == 0 ) vAxis = vecXAxis;
    else if( axis == 1 ) vAxis = vecYAxis;
    else if( axis == 2 ) vAxis = vecZAxis;

    // 绕某一轴旋转
    vecXAxis.rotateBy( angle, vAxis );
    vecYAxis.rotateBy( angle, vAxis );

    // 更新变换矩阵
    mat.setCoordSystem( ptOrigin, vecXAxis, vecYAxis, vecZAxis );

    // 应用新的UCS
    acedSetCurrentUCS( mat );
}

ArxUcsSwitch::ArxUcsSwitch( const AcGePoint3d& origin, const AcGeVector3d& xAxis, const AcGeVector3d& yAxis )
{
    //备份原有的ucs
    acedGetCurrentUCS( m_origMat );
    //创建新的ucs
    m_ucsId = ArxUcsHelper::CreateUCS( origin, xAxis, yAxis );
    //设置新建的ucs为当前ucs
    ArxUcsHelper::SetCurrentUCS( m_ucsId );
}

ArxUcsSwitch::~ArxUcsSwitch()
{
    if( !m_ucsId.isNull() )
    {
        //还原到wcs(或者上一个ucs)
        acedSetCurrentUCS( m_origMat );
        //删除ucs
        ArxEntityHelper::EraseObject( m_ucsId, Adesk::kTrue );
    }
}

void ArxUcsHelper::ucsToWcs( const AcDbObjectIdArray& ents )
{
    AcGeMatrix3d mat;
    ArxUcsHelper::getUcsToWcsMatrix( mat, acdbHostApplicationServices()->workingDatabase() );

    ArxUcsHelper::TransformEntities( ents, mat );
}

void ArxUcsHelper::MakeTransformMatrix( AcGeMatrix3d& mat, const AcGePoint3d& origin, const AcGeVector3d& xAxis, const AcGeVector3d& yAxis )
{
    AcGeVector3d vecZAxis = xAxis.crossProduct( yAxis );
    mat.setCoordSystem( origin, xAxis, yAxis, vecZAxis );
}

void ArxUcsHelper::TransformEntities( const AcDbObjectIdArray& ents, const AcGeMatrix3d& mat )
{
    AcTransaction* pTrans = actrTransactionManager->startTransaction();
    if( pTrans == 0 ) return;

    for( int i = 0; i < ents.length(); i++ )
    {
        //AcDb::OpenMode om = ( save ? ( AcDb::kForWrite ) : ( AcDb::kForRead ) );
        AcDbObject* pObj;
        if( Acad::eOk != pTrans->getObject( pObj, ents[i], AcDb::kForWrite ) ) continue;
        AcDbEntity* pEnt = AcDbEntity::cast( pObj );
        if( pEnt == 0 ) continue;

        pEnt->transformBy( mat );
    }
    actrTransactionManager->endTransaction();
}
