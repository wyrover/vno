#pragma once

#include "dlimexp.h"

//http://blog.sina.com.cn/s/blog_768f3f5701013c1v.html
//http://blog.csdn.net/foreverling/article/details/28393085
//http://forums.autodesk.com/t5/objectarx/how-to-set-current-ucs/td-p/2513614
//《ObjectARX开发实例教程-20090826.pdf》的4.6小节
class ARXHELPER_API ArxUcsHelper
{
public:
    static void             transformToWcs( AcDbEntity* ent, AcDbDatabase* db );
    static void             transformToUcs( AcDbEntity* ent, AcDbDatabase* db );

    static AcGeVector3d		getUcsXAxis( AcDbDatabase* pDb );
    static AcGeVector3d     getUcsYAxis( AcDbDatabase* pDb );
    static AcGeVector3d     getUcsZAxis( AcDbDatabase* pDb );

    static AcGePlane		getUcsPlane( AcDbDatabase* pDb );
    static void             getUcsToWcsMatrix( AcGeMatrix3d& m, AcDbDatabase* pDb );
    static void             getWcsToUcsMatrix( AcGeMatrix3d& m, AcDbDatabase* pDb );
    static void             getUcsToWcsOriginMatrix( AcGeMatrix3d& m, const AcGePoint3d& wcsBasePt, AcDbDatabase* pDb );
    static void             getEcsPlane( const AcGeVector3d& entNormal, AcGePlane& ecsPlane );
    static void             getEcsPlane( const AcGePoint3d& origin, const AcGeVector3d& entNormal, AcGePlane& ecsPlane, AcGeVector3d& ecsXAxis );
    static void             getEcsXAxis( const AcGeVector3d& ecsZAxis, AcGeVector3d& xAxis );
    static void             getEcsToWcsMatrix( const AcGePoint3d& origin, const AcGeVector3d& zAxis, AcGeMatrix3d& mat );

    // these functions all assume current document for the AcDbDatabase*
    static AcGePoint3d      wcsToUcs( const AcGePoint3d& pt );
    static AcGeVector3d     wcsToUcs( const AcGeVector3d& vec );
    static void             wcsToUcs( AcGePoint3dArray& ptArray );
    static AcGePoint3d      ucsToWcs( const AcGePoint3d& pt );
    static AcGeVector3d     ucsToWcs( const AcGeVector3d& vec );
    static void             ucsToWcs( AcGePoint3dArray& ptArray );
    static AcGePoint3d      ecsToWcs( const AcGePoint3d& pt, const AcGeVector3d& entNormal );
    static AcGeVector3d     ecsToWcs( const AcGeVector3d& vec, const AcGeVector3d& entNormal );
    static AcGePoint2d      ucsToDcs( const AcGePoint3d& pt );
    static AcGePoint3d      dcsToUcs( const AcGePoint2d& pt );

    static AcDbObjectId CreateUCS( const AcGePoint3d& origin, const AcGeVector3d& xAxis, const AcGeVector3d& yAxis );
    static bool SetCurrentUCS( const AcDbObjectId& ucsId );
    static void MoveCurrentUCSOrigin( const AcGeVector3d& v );
    static void RotateCurrentUCS( double angle, int axis ); // axis表示绕哪个轴旋转(0-x, 1-y, 2-z)
    static void ucsToWcs( const AcDbObjectIdArray& ents );;

    //前面的这些方法都是针对的当前ucs

    //下面的方法提供坐标系转换(实质就是矩阵运算)
    static void MakeTransformMatrix( AcGeMatrix3d& mat, const AcGePoint3d& origin, const AcGeVector3d& xAxis, const AcGeVector3d& yAxis );
    static void TransformEntities( const AcDbObjectIdArray& ents, const AcGeMatrix3d& mat );
};

class ARXHELPER_API ArxUcsSwitch
{
public:
    ArxUcsSwitch( const AcGePoint3d& origin, const AcGeVector3d& xAxis, const AcGeVector3d& yAxis );
    ~ArxUcsSwitch();

private:
    AcDbObjectId m_ucsId;
    AcGeMatrix3d m_origMat;
};