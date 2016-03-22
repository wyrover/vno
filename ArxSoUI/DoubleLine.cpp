#include "StdAfx.h"
#include "DoubleLine.h"

#include <ArxHelper/HelperClass.h>

//��ʼ���ྲ̬��Ա����
int DoubleLine::count = 0;

AcDbObjectId DoubleLine::Draw( const AcGePoint3d& spt, const AcGePoint3d& ept, double width )
{
    DoubleLine line( spt, ept, width );
    return line.draw();
}

DoubleLine::DoubleLine( const AcGePoint3d& spt, const AcGePoint3d& ept, double width )
    : m_spt( spt ), m_ept( ept ), m_width( width )
{

}
AcDbObjectId DoubleLine::draw()
{
    //����ʼ�˵�2������
    AcGePoint3d m_leftStartPt, m_leftEndPt;
    AcGePoint3d m_rightStartPt, m_rightEndPt;
    caclStartPoint( m_leftStartPt, m_rightStartPt );
    //����ĩ�˵�2������
    caclEndPoint( m_leftEndPt, m_rightEndPt );
    //����2��ֱ��
    AcDbObjectId line1 = ArxDrawHelper::DrawLine( m_leftStartPt, m_leftEndPt );
    AcDbObjectId line2 = ArxDrawHelper::DrawLine( m_rightStartPt, m_rightEndPt );

    //����group
    AcDbObjectIdArray objIds;
    objIds.append( line1 );
    objIds.append( line2 );
    //������ʱ������
    CString name;
    name.Format( _T( "���%d" ), count++ );
    AcDbObjectId groupId = ArxGroupHelper::CreateGroup( name, objIds );
    if( !groupId.isNull() )
    {
        ArxGroupHelper::ConvertToAnonymousGroup( groupId );
    }
    return groupId;
}

void DoubleLine::caclStartPoint( AcGePoint3d& startPt1, AcGePoint3d& startPt2 )
{
    AcGeVector3d v = m_ept - m_spt;
    v.normalize();

    v.rotateBy( PI * 0.5, AcGeVector3d::kZAxis );
    startPt1 = m_spt + v * m_width * 0.5;

    v.rotateBy( PI, AcGeVector3d::kZAxis );
    startPt2 = m_spt + v * m_width * 0.5;
}

void DoubleLine::caclEndPoint( AcGePoint3d& endPt1, AcGePoint3d& endPt2 )
{
    AcGeVector3d v = m_ept - m_spt;
    v.normalize();

    v.rotateBy( PI * 0.5, AcGeVector3d::kZAxis );
    endPt1 = m_ept + v * m_width * 0.5;

    v.rotateBy( PI, AcGeVector3d::kZAxis );
    endPt2 = m_ept + v * m_width * 0.5;
}
