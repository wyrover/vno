#include "StdAfx.h"
#include "ArxEntityHelper.h"

/* ȫ�ֺ���(ʵ����ZoomHelper.cpp��) */
extern void ExecuteZoomCommand1( const AcGePoint3d& minPt, const AcGePoint3d& maxPt );
extern void ExecuteZoomCommand2( const AcGePoint3d& minPt, const AcGePoint3d& maxPt );
//extern void ZommWindowUseCom(const AcGePoint3d& minPt, const AcGePoint3d& maxPt);
extern void ZoomWindowUseView( const AcGePoint3d& minPt, const AcGePoint3d& maxPt );
// ��Ч
extern void ZoomWindowUseGSView( const AcGePoint3d& minPt, const AcGePoint3d& maxPt );


void ArxEntityHelper::EraseObject( const AcDbObjectId& objId, Adesk::Boolean erasing )
{
    AcTransaction* pTrans = actrTransactionManager->startTransaction();
    if( pTrans == 0 ) return;

    AcDbObject* pObj;
    if( Acad::eOk == pTrans->getObject( pObj, objId, AcDb::kForWrite, !erasing ) )
    {
        pObj->erase( erasing ); // (��)ɾ��ͼԪ
    }
    actrTransactionManager->endTransaction();
}

void ArxEntityHelper::EraseObject2( const AcDbObjectId& objId, Adesk::Boolean erasing )
{
    AcDbObject* pObj;
    if( Acad::eOk == acdbOpenAcDbObject( pObj, objId, AcDb::kForWrite, !erasing ) )
    {
        pObj->erase( erasing );
        pObj->close();
        //acutPrintf(_T("\nʹ��Open/close����ɾ������ɹ�"));
    }
}

void ArxEntityHelper::EraseObjects( const AcDbObjectIdArray& objIds, Adesk::Boolean erasing )
{
    if( objIds.isEmpty() ) return;

    AcTransaction* pTrans = actrTransactionManager->startTransaction();
    if( pTrans == 0 ) return;

    int len = objIds.length();
    for( int i = 0; i < len; i++ )
    {
        AcDbObject* pObj;
        if( Acad::eOk != pTrans->getObject( pObj, objIds[i], AcDb::kForWrite, !erasing ) ) continue;
        pObj->erase( erasing ); // (��)ɾ��ͼԪ
    }
    actrTransactionManager->endTransaction();
}

void ArxEntityHelper::EraseObjects2( const AcDbObjectIdArray& objIds, Adesk::Boolean erasing )
{
    if( objIds.isEmpty() ) return;

    int len = objIds.length();
    for( int i = 0; i < len; i++ )
    {
        EraseObject2( objIds[i], erasing );
    }
}

void ArxEntityHelper::TransformEntities2( const AcDbObjectIdArray& objIds, const AcGeMatrix3d& xform )
{
    if( objIds.isEmpty() ) return;

    int len = objIds.length();
    for( int i = 0; i < len; i++ )
    {
        AcDbEntity* pEnt;
        if( Acad::eOk == acdbOpenAcDbEntity( pEnt, objIds[i], AcDb::kForWrite ) )
        {
            pEnt->transformBy( xform );
            pEnt->close();
        }
    }
}

void ArxEntityHelper::TransformEntities( const AcDbObjectIdArray& objIds, const AcGeMatrix3d& xform )
{
    if( objIds.isEmpty() ) return;

    AcTransaction* pTrans = actrTransactionManager->startTransaction();
    if( pTrans == 0 ) return;

    int len = objIds.length();
    for( int i = 0; i < len; i++ )
    {
        AcDbObject* pObj;
        if( Acad::eOk != pTrans->getObject( pObj, objIds[i], AcDb::kForWrite ) ) continue;

        AcDbEntity* pEnt = AcDbEntity::cast( pObj );
        if( pEnt == 0 ) continue;

        pEnt->transformBy( xform );
    }
    actrTransactionManager->endTransaction();
}

void ArxEntityHelper::DrawEntities( const AcDbObjectIdArray& objIds, AcGiWorldDraw* mode )
{
    AcTransaction* pTrans = actrTransactionManager->startTransaction();
    if( pTrans == 0 ) return;

    int len = objIds.length();
    for( int i = 0; i < len; i++ )
    {
        AcDbObject* pObj;
        if( Acad::eOk != pTrans->getObject( pObj, objIds[i], AcDb::kForRead ) ) continue;

        AcDbEntity* pEnt = AcDbEntity::cast( pObj );
        if( pEnt == 0 ) continue;

        //acutPrintf(_T("\n���Ƶ�%d��ͼԪ"), i);
        pEnt->worldDraw( mode );
    }

    actrTransactionManager->endTransaction();
}

void ArxEntityHelper::ShowEntities( const AcDbObjectIdArray& objIds, bool isVisible )
{
    AcTransaction* pTrans = actrTransactionManager->startTransaction();
    if( pTrans == 0 ) return;

    int len = objIds.length();
    for( int i = 0; i < len; i++ )
    {
        AcDbObject* pObj;
        if( Acad::eOk != pTrans->getObject( pObj, objIds[i], AcDb::kForWrite ) ) continue;;

        AcDbEntity* pEnt = AcDbEntity::cast( pObj );
        if( pEnt == 0 ) continue;

        pEnt->setVisibility( isVisible ? AcDb::kVisible : AcDb::kInvisible ); // ��ʾ������ͼԪ(�޸�)
    }

    actrTransactionManager->endTransaction();
}

void ArxEntityHelper::ShowEntity( const AcDbObjectId& objId, bool isVisible )
{
    AcTransaction* pTrans = actrTransactionManager->startTransaction();
    if( pTrans == 0 ) return;

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

    pEnt->setVisibility( isVisible ? AcDb::kVisible : AcDb::kInvisible ); // ��ʾ������ͼԪ(�޸�)

    actrTransactionManager->endTransaction();
}

// ʹ������
static void UpdateEntity1( const AcDbObjectId& objId )
{
    AcTransaction* pTrans = actrTransactionManager->startTransaction();
    if( pTrans == 0 ) return;

    AcDbObject* pObj;
    if( Acad::eOk != pTrans->getObject( pObj, objId, AcDb::kForWrite ) ) // ��ͼԪʧ��
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
    pEnt->recordGraphicsModified( true ); // ��ǩͼԪ״̬���޸ģ���Ҫ����ͼ��
    actrTransactionManager->endTransaction();
}

// ʹ�ó����Open/Close����
static void UpdateEntity2( const AcDbObjectId& objId )
{
    AcDbEntity* pEnt;
    if( Acad::eOk != acdbOpenObject( pEnt, objId, AcDb::kForWrite ) ) return;

    pEnt->recordGraphicsModified( true ); // ��ǩͼԪ״̬���޸ģ���Ҫ����ͼ��
    pEnt->close();
}

void ArxEntityHelper::Update( const AcDbObjectId& objId )
{
    if( objId.isNull() ) return;
    /*
     * ʹ�ó����Open/Close���Ƹ���ʵ��
     * ע��ʹ��������Ƹ���ʵ����ʱ���ʹ, ��ʱ�򲻺�ʹ
     *      ԭ����ʱ����
     */
    UpdateEntity2( objId );
}

static void ForceUpdate()
{
    actrTransactionManager->queueForGraphicsFlush();
    actrTransactionManager->flushGraphics();
    acedUpdateDisplay();
}

static void ZoomEntity_Helper( const AcGePoint3d& minPt, const AcGePoint3d& maxPt )
{
    //acutPrintf(_T("\n��С��:(%.3f,%.3f,%.3f)\t����:(%.3f,%.3f,%.3f)\n"), minPt.x, minPt.y, minPt.z, maxPt.x, maxPt.y, maxPt.z);

    AcGeVector3d v = maxPt - minPt;

    // ���ŶԽ�����������Ŵ�(��С���С��������)
    double c = 0.618; // �ƽ����ֵ

    // 1) ʹ��sendStringToExecute����
    // ȱ��:����������ʾһЩ��ʾ�ַ������е㷳��(����: "���zoom w ָ����һ��λ�� ... ")
    //ExecuteZoomCommand1(minPt-c*v, maxPt+c*v);

    // 2) ʹ��acedCommand����
    // ȱ��: ��modelss dialog���޷�ʹ��(�����˵����application context���޷�ִ��)
    // �μ���arxdoc.chm->Advanced Topics->The Multiple Document Interface
    //        ->Application Execution Context
    //        ->Code Differences under the Application Execution Context
    //ExecuteZoomCommand2(minPt-c*v, maxPt+c*v);

    // 3) ʹ��com
    // ȱ��: ��ʾһЩ�յ�������ʾ(����"����: ")
    //ZommWindowUseCom(minPt-c*v, maxPt+c*v);

    // 4) ʹ��view
    // ȱ�㣺��������ŵ�ʱ�򣬶�ͼԪ�������޸ģ������޸���ɫ�����������ϸ���
    //        ֻ�е�ǰ������cad�Ļ�ͼ����ʱ���Ż����
    // �μ���<<ObjectARX����ʵ���̳�-20090826>>�е�"4.4 ��ͼ"С��
    ZoomWindowUseView( minPt - c * v, maxPt + c * v );
    acedGetAcadFrame()->SetFocus(); // �л�����(���ͼ���޸ĵ�����)

    // 5) ʹ��AcGsView(ʧ��)
    // AcGsViewֻ������3dģʽ
    //ZoomWindowUseGSView(minPt-c*v, maxPt+c*v);
}

static bool IsValidExtent( const AcDbExtents& ext )
{
    AcGeVector3d v = ext.maxPoint() - ext.minPoint();
    //acutPrintf(_T("\nextents:x=%.3f,%y=%.3f,z=%.3f\n"), v.x, v.y, v.z);
    return ( v.x >= 0 && v.y >= 0 && v.z >= 0 ); // x,y,z�Ĳ�ֵ����>=0
}

void ArxEntityHelper::ZoomToEntityForModeless( const AcDbObjectId& objId )
{
    // �ڷ�ģ̬�Ի������޷�ʹ��
    //ads_name en;
    //if(Acad::eOk != acdbGetAdsName(en, objId)) return;
    //acedCommand(RTSTR, _T("ZOOM"), RTSTR, _T("O"), RTENAME, en, RTSTR, _T(""), 0);

    // ��ʱʹ��sendStringToExecute������Ŷ�λ����
    CString cmd;
    cmd.Format( _T( "ZOOM O \003" ) ); // ���ո����ѡ�����Ȼ��esc(��ֹ����Ŀո��ظ�ִ������)
    acDocManager->sendStringToExecute( curDoc(), cmd, true, false, false );
}

void ArxEntityHelper::ZoomToEntity( const AcDbObjectId& objId )
{
    AcTransaction* pTrans = actrTransactionManager->startTransaction();
    if( pTrans == 0 ) return;

    AcDbObject* pObj;
    if( Acad::eOk != pTrans->getObject( pObj, objId, AcDb::kForRead ) )
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

    AcDbExtents extents;
    bool ret = ( Acad::eOk == pEnt->getGeomExtents( extents ) );

    actrTransactionManager->endTransaction();

    if( ret && IsValidExtent( extents ) )
    {
        ZoomEntity_Helper( extents.minPoint(), extents.maxPoint() );
    }
}

void ArxEntityHelper::ZoomToEntities( const AcDbObjectIdArray& objIds )
{
    AcTransaction* pTrans = actrTransactionManager->startTransaction();
    if( pTrans == 0 ) return;

    AcDbExtents exts;
    int len = objIds.length();
    for( int i = 0; i < len; i++ )
    {
        AcDbObject* pObj;
        if( Acad::eOk != pTrans->getObject( pObj, objIds[i], AcDb::kForRead ) ) continue;

        AcDbEntity* pEnt = AcDbEntity::cast( pObj );
        if( pEnt == 0 ) continue;

        AcDbExtents extents;
        if( Acad::eOk != pEnt->getGeomExtents( extents ) ) continue;

        exts.addPoint( extents.minPoint() );
        exts.addPoint( extents.maxPoint() );
    }

    actrTransactionManager->endTransaction();

    AcGePoint3d minPt = exts.minPoint();
    AcGePoint3d maxPt = exts.maxPoint();
    if( minPt.x <= maxPt.x && minPt.y <= maxPt.y && minPt.z <= maxPt.z )
    {
        ZoomEntity_Helper( minPt, maxPt );
    }
}

bool ArxEntityHelper::GetEntityColor( const AcDbObjectId& objId, Adesk::UInt16& colorIndex )
{
    AcTransaction* pTrans = actrTransactionManager->startTransaction();
    if( pTrans == 0 ) return false;

    AcDbObject* pObj;
    if( Acad::eOk != pTrans->getObject( pObj, objId, AcDb::kForRead ) )
    {
        actrTransactionManager->abortTransaction();
        return false;
    }
    AcDbEntity* pEnt = AcDbEntity::cast( pObj );
    if( pEnt == 0 )
    {
        actrTransactionManager->abortTransaction();
        return false;
    }

    colorIndex = pEnt->colorIndex();
    actrTransactionManager->endTransaction();

    return true;
}

bool ArxEntityHelper::GetEntitiesColor( const AcDbObjectIdArray& objIds, AcArray<Adesk::UInt16>& colors )
{
    AcTransaction* pTrans = actrTransactionManager->startTransaction();
    if( pTrans == 0 ) return false;

    bool ret = true;  // Ĭ�Ϸ���true
    int len = objIds.length();
    for( int i = 0; i < len; i++ )
    {
        AcDbObject* pObj;
        if( Acad::eOk != pTrans->getObject( pObj, objIds[i], AcDb::kForRead ) )
        {
            actrTransactionManager->abortTransaction();
            ret = false;
            colors.removeAll(); // ���
            break;
        }
        AcDbEntity* pEnt = AcDbEntity::cast( pObj );
        if( pEnt == 0 )
        {
            actrTransactionManager->abortTransaction();
            ret = false;
            colors.removeAll(); // ���
            break;
        }
        Adesk::UInt16 ci = pEnt->colorIndex();
        colors.append( ci ); // ��¼ԭ�е���ɫ
    }
    actrTransactionManager->endTransaction();
    return ret;
}

bool ArxEntityHelper::SetEntityColor( const AcDbObjectId& objId, unsigned short colorIndex )
{
    AcTransaction* pTrans = actrTransactionManager->startTransaction();
    if( pTrans == 0 ) return false;

    AcDbObject* pObj;
    if( Acad::eOk != pTrans->getObject( pObj, objId, AcDb::kForWrite ) )
    {
        actrTransactionManager->abortTransaction();
        return false;
    }

    AcDbEntity* pGE = AcDbEntity::cast( pObj );
    if( pGE == 0 )
    {
        actrTransactionManager->abortTransaction();
        return false;
    }

    // ������ɫ
    pGE->setColorIndex( colorIndex );
    actrTransactionManager->endTransaction();
    return true;
}

bool ArxEntityHelper::SetEntitiesColor( AcDbObjectIdArray& objIds, unsigned short colorIndex )
{
    AcTransaction* pTrans = actrTransactionManager->startTransaction();
    if( pTrans == 0 ) return false;

    bool ret = true; // Ĭ�Ϸ���true
    int len = objIds.length();
    for( int i = 0; i < len; i++ )
    {
        AcDbObject* pObj;
        if( Acad::eOk != pTrans->getObject( pObj, objIds[i], AcDb::kForWrite ) )
        {
            actrTransactionManager->abortTransaction();
            ret = false;
            break;
        }

        AcDbEntity* pGE = AcDbEntity::cast( pObj );
        if( pGE == 0 )
        {
            actrTransactionManager->abortTransaction();
            ret = false;
            break;
        }

        // ������ɫ
        pGE->setColorIndex( colorIndex );
    }
    actrTransactionManager->endTransaction();

    return ret;
}

bool ArxEntityHelper::SetEntitiesColor2( const AcDbObjectIdArray& objIds, const AcArray<Adesk::UInt16>& colors )
{
    AcTransaction* pTrans = actrTransactionManager->startTransaction();
    if( pTrans == 0 ) return false;

    bool ret = true; // Ĭ�Ϸ���true
    int len = objIds.length();
    for( int i = 0; i < len; i++ )
    {
        AcDbObject* pObj;
        if( Acad::eOk != pTrans->getObject( pObj, objIds[i], AcDb::kForWrite ) )
        {
            actrTransactionManager->abortTransaction();
            ret = false;
            break;
        }
        AcDbEntity* pEnt = AcDbEntity::cast( pObj );
        if( pEnt == 0 )
        {
            actrTransactionManager->abortTransaction();
            ret = false;
            break;
        }
        pEnt->setColorIndex( colors[i] ); // �ָ�ԭ�ȵ���ɫ
    }
    actrTransactionManager->endTransaction();
    return ret;
}


/*
 * �����ĵ���acedSSSetFirst�Լ�acedSSGetFirst
 * Ҫ��ʹ����������Ӧ�ÿ���ACRX_CMD_USEPICKSET��ACRX_CMD_REDRAWѡ��
 * �����Խ����ʾ��ò�Ʋ�ʹ��Ҳ����??????
 */
bool ArxEntityHelper::SelectEntity( const AcDbObjectId& objId )
{
    //acedSSSetFirst(NULL, NULL);

    if( objId.isNull() ) return false;

    ads_name ename;
    if( Acad::eOk != acdbGetAdsName( ename, objId ) ) return false;;

    ads_name ss;
    if( RTNORM != acedSSAdd( ename, NULL, ss ) ) return false; // ����ѡ��

    acedSSSetFirst( ss, NULL ); // ����ѡ��
    acedSSFree( ss );           // �ͷ�ѡ��

    return true;
}

bool ArxEntityHelper::SelectEntities( const AcDbObjectIdArray& objIds )
{
    //acedSSSetFirst(NULL, NULL);

    if( objIds.isEmpty() ) return false;

    ads_name ss;
    //����һ���յ�ѡ��
    if( RTNORM != acedSSAdd( NULL, NULL, ss ) ) return false;
    bool ret = true;
    for( int i = 0; i < objIds.length(); i++ )
    {
        ads_name ename;
        if( Acad::eOk != acdbGetAdsName( ename, objIds[i] ) )
        {
            ret = false;;
            break;
        }
        if( RTNORM != acedSSAdd( ename, ss, ss ) )  // ��ӵ�ѡ��
        {
            ret = false;;
            break;
        }
    }

    if( ret )
    {
        acedSSSetFirst( ss, NULL ); // ����ѡ��
    }
    acedSSFree( ss );           // �ͷ�ѡ��

    return ret;
}
