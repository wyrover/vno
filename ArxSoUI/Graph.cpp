#include "StdAfx.h"
#include "Graph.h"
#include "DoubleLine.h"

#include <ArxHelper/HelperClass.h>

BaseGraph::BaseGraph()
{
    //默认为单位矩阵(即不做任何变换)
    m_mat.setToIdentity();
}

void BaseGraph::setPoint( const AcGePoint3d& pt )
{
    this->m_basePt = pt;
}

AcGePoint3d BaseGraph::getPoint() const
{
    return this->m_basePt;
}

void BaseGraph::addEnt( const AcDbObjectId& objId )
{
    if( objId.isNull() ) return;
    if( ArxUtilHelper::IsEqualType( _T( "AcDbGroup" ), objId ) )
    {
        ArxGroupHelper::GetObjectIds( objId, m_ents );
    }
    else if( ArxUtilHelper::IsEqualType( _T( "AcDbEntity" ), objId ) )
    {
        m_ents.append( objId );
    }
}

void BaseGraph::draw()
{
    ArxDocLockSwitch lock_switch;
    //坐标系变换为ucs
    m_mat.setTranslation( getPoint().asVector() );

    //当前坐标系为ucs,需要将基点设置为原点
    setPoint( AcGePoint3d::kOrigin );

    //绘制图形(由派生类具体实现)
    subDraw();

    //将ucs坐标系下绘制的图形变换到wcs坐标系
    ArxUcsHelper::TransformEntities( m_ents, m_mat );
}

void BaseGraph::setUcs( const AcGePoint3d& origin, const AcGeVector3d& xAxis, const AcGeVector3d& yAxis )
{
    ArxUcsHelper::MakeTransformMatrix( m_mat, origin, xAxis, yAxis );
}

AcDbObjectId BaseGraph::drawRect( const AcGePoint3d& cnt, double angle, double width, double height )
{
    AcDbObjectId objId = ArxDrawHelper::DrawRect( cnt, angle, width, height );
    this->addEnt( objId );
    return objId;
}

AcDbObjectId BaseGraph::drawRect2( const AcGePoint3d& pt, double angle, double width, double height )
{
    AcDbObjectId objId = ArxDrawHelper::DrawRect2( pt, angle, width, height );
    this->addEnt( objId );
    return objId;
}

AcDbObjectId BaseGraph::drawCircle( const AcGePoint3d& pt, double radius )
{
    AcDbObjectId objId = ArxDrawHelper::DrawCircle( pt, radius );
    this->addEnt( objId );
    return objId;
}

AcDbObjectId BaseGraph::drawDoubleLine( const AcGePoint3d& spt, const AcGePoint3d& ept, double width )
{
    AcDbObjectId objId = DoubleLine::Draw( spt, ept, width );
    this->addEnt( objId );
    return objId;
}

AcDbObjectId BaseGraph::drawMText( const AcGePoint3d& pt, double angle, const CString& text, double height, AcDbMText::AttachmentPoint ap )
{
    AcDbObjectId objId = ArxDrawHelper::DrawMText( pt, angle, text, height, ap );
    this->addEnt( objId );
    return objId;
}

AcDbObjectId BaseGraph::drawLine( const AcGePoint3d& pt, double angle, double length )
{
    AcDbObjectId objId = ArxDrawHelper::DrawLine( pt, angle, length );
    this->addEnt( objId );
    return objId;
}

AcDbObjectId BaseGraph::drawLine( const AcGePoint3d& spt, const AcGePoint3d& ept )
{
    AcDbObjectId objId = ArxDrawHelper::DrawLine( spt, ept );
    this->addEnt( objId );
    return objId;
}

AcDbObjectId BaseGraph::drawAlignedDim( const AcGePoint3d& pt1, const AcGePoint3d& pt2, const CString& text, double offset /*= 30*/, bool clockwise/*=true*/, const CString& dimStyle )
{
    AcDbObjectId objId = ArxDrawHelper::MakeAlignedDim( pt1, pt2, text, offset, clockwise, dimStyle );
    this->addEnt( objId );
    return objId;
}

AcDbObjectId BaseGraph::drawPolygonHatch(const AcGePoint3dArray& pts, const CString& patName, double scale)
{
	AcDbObjectId objId = ArxDrawHelper::DrawPolygonHatch( pts, patName, scale );
	this->addEnt( objId );
	return objId;
}
