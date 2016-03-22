#include "StdAfx.h"
#include "ArxDataTool.h"
#include "ArxDbgXdata.h"

void ArxDataTool::RegAppName( AcDbDatabase* db, const CString& appName )
{
    // make sure application name is registered
    AcDbRegAppTable* regAppTbl;
    Acad::ErrorStatus es = db->getSymbolTable( regAppTbl, AcDb::kForRead );
    if ( es == Acad::eOk )
    {
        if ( regAppTbl->has( appName ) == false )
        {
            es = regAppTbl->upgradeOpen();
            if ( es == Acad::eOk )
            {
                AcDbRegAppTableRecord* newRec = new AcDbRegAppTableRecord;
                es = newRec->setName( appName );
                if ( es == Acad::eOk )
                {
                    es = regAppTbl->add( newRec );
                    if ( es == Acad::eOk )
                        newRec->close();
                    else
                    {
                        ASSERT( 0 );
                        delete newRec;
                    }
                }
                else
                {
                    ASSERT( 0 );
                    delete newRec;
                }
            }
            else
            {
                ASSERT( 0 );
            }
        }
        regAppTbl->close();
    }
    else
    {
        ASSERT( 0 );
    }
}

bool ArxDataTool::GetDataFromXData( AcDbObject* pObj, const CString& appName, int index, CString& value )
{
    resbuf* pAppNode = pObj->xData( appName ); // ������һ����չ��������
    if( pAppNode == 0 ) return false;

    int i = 0;
    resbuf* pTemp;
    for( pTemp = pAppNode; pTemp != NULL; pTemp = pTemp->rbnext )
    {
        if( i == index ) break;
        i++;
    }
    value = pTemp->resval.rstring;
    acutRelRb( pAppNode );

    return true;
}

bool ArxDataTool::GetDataFromXData( const AcDbObjectId& objId, const CString& appName, int index, CString& value )
{
    AcTransaction* pTrans = actrTransactionManager->startTransaction();
    if( pTrans == 0 ) return false;

    AcDbObject* pObj;
    if( Acad::eOk != pTrans->getObject( pObj, objId, AcDb::kForRead ) )
    {
        actrTransactionManager->abortTransaction();
        return false;
    }

    ArxDbgAppXdata xdata( appName, acdbHostApplicationServices()->workingDatabase() );
    xdata.getXdata( pObj );

    bool ret = false;
    if( !xdata.isEmpty() )
    {
        ret = xdata.getString( index, value );
    }
    actrTransactionManager->endTransaction();

    return ret;
}

bool ArxDataTool::SetDataToXData( const AcDbObjectId& objId, const CString& appName, int index, const CString& value )
{
    AcTransaction* pTrans = actrTransactionManager->startTransaction();
    if( pTrans == 0 ) return false;

    AcDbObject* pObj;
    if( Acad::eOk != pTrans->getObject( pObj, objId, AcDb::kForWrite ) )
    {
        actrTransactionManager->abortTransaction();
        return false;
    }

    ArxDbgAppXdata xdata( appName, acdbHostApplicationServices()->workingDatabase() );
    xdata.getXdata( pObj );
    xdata.setString( index, value );
    actrTransactionManager->endTransaction();

    return true;
}

bool ArxDataTool::SetDataToXData( AcDbObject* pObj, const CString& appName, int index, const CString& value )
{
    resbuf* pAppNode = pObj->xData( appName );
    if( pAppNode == 0 ) return false;

    int i = 0;
    resbuf* pTemp;
    for( pTemp = pAppNode; pTemp != NULL; pTemp = pTemp->rbnext )
    {
        if( i == index ) break;
        i++;
    }

    acutNewString( value, pTemp->resval.rstring );

    pObj->setXData( pAppNode );
    acutRelRb( pAppNode );

    return true;
}

// ע�⣺xdata�������һ�� regAppName�ڵ�
void ArxDataTool::AddDataToXData( AcDbObject* pObj, const CString& appName )
{
    // ���뱣֤ͼԪ����write״̬
    resbuf* pAppNode = pObj->xData( appName );
    if( pAppNode == 0 )
    {
        pAppNode = acutBuildList( AcDb::kDxfRegAppName, appName, AcDb::kDxfXdAsciiString, _T( "" ), 0 );
    }
    else
    {
        resbuf* pTemp;
        for( pTemp = pAppNode; pTemp->rbnext != NULL; pTemp = pTemp->rbnext )
        {
            ;    // ѭ����ĩβ
        }
        pTemp->rbnext = acutBuildList( AcDb::kDxfXdAsciiString, _T( "" ), 0 ); // ����һ���ַ���
    }

    pObj->setXData( pAppNode );
    acutRelRb( pAppNode );
}

// ע�⣺xdata�������һ�� regAppName�ڵ�
void ArxDataTool::RemoveDataFromXData( AcDbObject* pObj, const CString& appName, int index )
{
    // ���뱣֤ͼԪ����write״̬
    resbuf* pAppNode = pObj->xData( appName );
    if( pAppNode == 0 ) return ;

    int i = 0;
    resbuf* pPos, *pTemp;
    for( pTemp = pAppNode; pTemp != NULL; pTemp = pTemp->rbnext )
    {
        if( i + 1 == index ) break;
        i++;
    }
    pPos = pTemp->rbnext;
    pTemp->rbnext = pPos->rbnext;

    pObj->setXData( pAppNode );
    acutRelRb( pAppNode );

    pPos->rbnext = 0;
    acutRelRb( pPos );
}

void ArxDataTool::AddDataToObjects( const AcDbObjectIdArray& objIds, const CString& appName )
{
    AcTransaction* pTrans = actrTransactionManager->startTransaction();
    if( pTrans == 0 ) return;

    int len = objIds.length();
    for( int i = 0; i < len; i++ )
    {
        AcDbObject* pObj;
        if( Acad::eOk != pTrans->getObject( pObj, objIds.at( i ), AcDb::kForWrite ) ) continue;
        AddDataToXData( pObj, appName );
    }
    actrTransactionManager->endTransaction();
}

void ArxDataTool::RemoveDataFromObjects( const AcDbObjectIdArray& objIds, const CString& appName, int index )
{
    AcTransaction* pTrans = actrTransactionManager->startTransaction();
    if( pTrans == 0 ) return;

    int len = objIds.length();
    for( int i = 0; i < len; i++ )
    {
        AcDbObject* pObj;
        if( Acad::eOk != pTrans->getObject( pObj, objIds.at( i ), AcDb::kForWrite ) ) continue;
        RemoveDataFromXData( pObj, appName, index );
    }
    actrTransactionManager->endTransaction();
}

static bool IsEqualObject( AcRxClass* pClass, AcDbObject* pObj, bool isDerivedFromParent )
{
    bool ret;
    if( !isDerivedFromParent )
    {
        ret = ( pObj->isA() == pClass ); // ֻѡ���ض�����ͼԪ
    }
    else
    {
        ret = pObj->isKindOf( pClass ); // ͬʱ��ѡ��������
    }
    return ret;
}

// ʹ��open/close����
static bool IsEqualType1( const CString& type, const AcDbObjectId& objId, bool isDerivedFromParent )
{
    AcRxClass* pClass = AcRxClass::cast( acrxClassDictionary->at( type ) );
    if( pClass == 0 ) return false;

    AcDbObject* pObj;
    if( Acad::eOk != acdbOpenObject( pObj, objId, AcDb::kForRead ) ) return false;

    bool ret = IsEqualObject( pClass, pObj, isDerivedFromParent );
    pObj->close();

    return ret;
}

// ʹ������
static bool IsEqualType2( const CString& type, const AcDbObjectId& objId, bool isDerivedFromParent )
{
    AcRxClass* pClass = AcRxClass::cast( acrxClassDictionary->at( type ) );
    if( pClass == 0 ) return false;

    AcTransaction* pTrans = actrTransactionManager->startTransaction();
    if( pTrans == 0 )
    {
        acutPrintf( _T( "\n�ж�����:%sʱ��ȡtransaction����..." ), type );
        return false;
    }

    AcDbObject* pObj;
    if( Acad::eOk != pTrans->getObject( pObj, objId, AcDb::kForRead ) )
    {
        actrTransactionManager->abortTransaction();
        return false;
    }

    bool ret = IsEqualObject( pClass, pObj, isDerivedFromParent );

    actrTransactionManager->endTransaction();

    return ret;
}

//CString ArxDataTool::GetTypeName( const AcDbObjectId& objId )
//{
//	AcDbObject* pObj;
//	if(Acad::eOk != acdbOpenObject(pObj, objId, AcDb::kForRead)) return _T("");
//
//	pObj->close();
//
//	AcRxClass* pClass = AcRxClass::cast(acrxClassDictionary->at(type));
//	if(pClass == 0) return _T("");
//	return CString(pClass->name());
//}

bool ArxDataTool::IsEqualType( const CString& type, const AcDbObjectId& objId, bool isDerivedFromParent )
{
    //return IsEqualType1(type, objId, isDerivedFromParent);
    return IsEqualType2( type, objId, isDerivedFromParent );
}

// ���skipDeleted = true����ֻ���ҿɼ���ͼԪ����û��ɾ����ͼԪ
// ���skipDeleted = false����������е�ͼԪ
// �������÷��Ǵ����
// iteratorҲ�ṩ�˴򿪶���ָ��ķ�����
// �����ȡid����ȥ��open/close����(��������transaction)�򿪶���
// ���߼��Ͼ���Щì�ܣ�Ҳ���ܻᵼ��һЩĪ������Ĵ���
// ����startTransaction����NULL���޷���������
/*AcDbObjectId objId;
if(Acad::eOk != pBlkTblRcdItr->getEntityId(objId)) continue;

if(ArxDataTool::IsEqualType(type, objId, isDerivedFromParent))
{
objIds.append(objId);
}*/
static void GetEntsByType_Helper( const CString& type, AcDbObjectIdArray& objIds, bool isDerivedFromParent, bool skipDeleted )
{
    AcRxClass* pClass = AcRxClass::cast( acrxClassDictionary->at( type ) );
    if( pClass == 0 ) return;

    AcDbBlockTable* pBlkTbl;
    acdbHostApplicationServices()->workingDatabase()->getSymbolTable( pBlkTbl, AcDb::kForRead );

    AcDbBlockTableRecord* pBlkTblRcd;
    Acad::ErrorStatus es = pBlkTbl->getAt( ACDB_MODEL_SPACE, pBlkTblRcd, AcDb::kForRead );
    pBlkTbl->close();

    if( Acad::eOk != es ) return;

    AcDbBlockTableRecordIterator* pBlkTblRcdItr;
    if( Acad::eOk == pBlkTblRcd->newIterator( pBlkTblRcdItr, true, skipDeleted ) )
    {
        for ( pBlkTblRcdItr->start( true, skipDeleted ); !pBlkTblRcdItr->done(); pBlkTblRcdItr->step( true, skipDeleted ) )
        {
            AcDbEntity* pEnt;
            if( Acad::eOk != pBlkTblRcdItr->getEntity( pEnt, AcDb::kForRead ) ) continue;

            if( IsEqualObject( pClass, pEnt, isDerivedFromParent ) )
            {
                objIds.append( pEnt->objectId() );
            }
            pEnt->close();
        }
        delete pBlkTblRcdItr;
    }
    pBlkTblRcd->close();
}

void ArxDataTool::GetEntsByType( const CString& type, AcDbObjectIdArray& objIds, bool isDerivedFromParent )
{
    GetEntsByType_Helper( type, objIds, isDerivedFromParent, true );
}

void ArxDataTool::GetErasedEntsByType( const CString& type, AcDbObjectIdArray& objIds, bool isDerivedFromParent )
{
    AcDbObjectIdArray allObjIds;
    GetEntsByType_Helper( type, allObjIds, isDerivedFromParent, false );
    if( allObjIds.isEmpty() ) return;
    //acutPrintf(_T("\n����ͼԪ����(������ɾ��ͼԪ):%d"), allObjIds.length());

    AcTransaction* pTrans = actrTransactionManager->startTransaction();
    if( pTrans == 0 ) return;

    int len = allObjIds.length();
    for( int i = 0; i < len; i++ )
    {
        AcDbObject* pObj;
        if( Acad::eOk != pTrans->getObject( pObj, allObjIds[i], AcDb::kForRead ) ) continue;

        if( pObj->isErased() )
        {
            objIds.append( allObjIds[i] ); // ֻ���ɾ���˵�ͼԪ
        }
    }
    actrTransactionManager->endTransaction();
}

void ArxDataTool::FilterEntsByType( const CString& type, const AcDbObjectIdArray& allObjIds, AcDbObjectIdArray& objIds )
{
    int n = allObjIds.length();
    for( int i = 0; i < n; i++ )
    {
        if( IsEqualType( type, allObjIds[i] ) )
        {
            objIds.append( allObjIds[i] );
        }
    }
}
