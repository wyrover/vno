#include "StdAfx.h"
#include "ArxGroupHelper.h"

static AcDbObjectId CreateGroupHelper( const CString& groupName, const AcDbObjectIdArray& objIds )
{
    CString name = groupName;
    name.Trim();
    if( name.GetLength() == 0 )
    {
        return AcDbObjectId::kNull;
    }

    // Put the group in the group dictionary which resides
    // in the named object dictionary.
    //
    AcDbDictionary* pGroupDict;
    Acad::ErrorStatus es =
        acdbHostApplicationServices()->workingDatabase()->getGroupDictionary( pGroupDict, AcDb::kForWrite );
    if( es != Acad::eOk ) return AcDbObjectId::kNull;

    AcDbObjectId groupId;
    if( pGroupDict->has( name ) )
    {
        pGroupDict->getAt( name, groupId );
        pGroupDict->close();
        return groupId;
    }

    AcDbGroup* pGroup = new AcDbGroup( name );
    es = pGroupDict->setAt( name, pGroup, groupId );
    pGroupDict->close();

    if( es != Acad::eOk ) return AcDbObjectId::kNull;

    // Now that the group has been added, it has an ObjectID.
    // This is important since the group will become a persistent
    // reactor for the added entities...
    for ( int i = 0; i < objIds.length(); i++ )
    {
        if( objIds[i].isNull() ) continue;
        pGroup->append( objIds[i] );
    }

    //默认情况AcDbGroup是全部选择的
    pGroup->setSelectable( true );
    pGroup->close();

    return groupId;
}

bool ArxGroupHelper::ConvertToAnonymousGroup( const AcDbObjectId& groupId )
{
    if( groupId.isNull() ) return false;

    AcTransaction* pTrans = actrTransactionManager->startTransaction();
    if( pTrans == 0 ) return false;

    //AcDb::OpenMode om = ( save ? ( AcDb::kForWrite ) : ( AcDb::kForRead ) );
    AcDbObject* pObj;
    if( Acad::eOk != pTrans->getObject( pObj, groupId, AcDb::kForWrite ) )
    {
        actrTransactionManager->abortTransaction();
        return false;
    }
    AcDbGroup* pGroup = AcDbGroup::cast( pObj );
    if( pGroup == 0 )
    {
        actrTransactionManager->abortTransaction();
        return false;
    }
    Acad::ErrorStatus es = pGroup->setAnonymous();
    actrTransactionManager->endTransaction();

    return ( es == Acad::eOk );
}

AcDbObjectId ArxGroupHelper::CreateGroup( const CString& groupName, const AcDbObjectIdArray& objIds )
{
    return CreateGroupHelper( groupName, objIds );
}

void ArxGroupHelper::GetObjectIds( const AcDbObjectId& groupId, AcDbObjectIdArray& objIds )
{
    AcTransaction* pTrans = actrTransactionManager->startTransaction();
    if( pTrans == 0 ) return;

    //AcDb::OpenMode om = ( save ? ( AcDb::kForWrite ) : ( AcDb::kForRead ) );
    AcDbObject* pObj;
    if( Acad::eOk != pTrans->getObject( pObj, groupId, AcDb::kForRead ) )
    {
        actrTransactionManager->abortTransaction();
        return;
    }
    AcDbGroup* pGroup = AcDbGroup::cast( pObj );
    if( pGroup == 0 )
    {
        actrTransactionManager->abortTransaction();
        return;
    }

    AcDbGroupIterator* pIter = pGroup->newIterator();
    for ( ; !pIter->done(); pIter->next() )
    {
        objIds.append( pIter->objectId() );
    }
    delete pIter;

    actrTransactionManager->endTransaction();
}

void ArxGroupHelper::GetObjectIds( const CString& groupName, AcDbObjectIdArray& objIds )
{
    AcDbObjectId groupId = ArxGroupHelper::GetGroup( groupName );
    if( groupId.isNull() ) return;

    ArxGroupHelper::GetObjectIds( groupId, objIds );
}

AcDbObjectId ArxGroupHelper::GetGroup( const CString& groupName )
{
    AcDbDictionary* pGroupDict;
    Acad::ErrorStatus es =
        acdbHostApplicationServices()->workingDatabase()->getGroupDictionary( pGroupDict, AcDb::kForRead );

    if( es != Acad::eOk ) return AcDbObjectId::kNull;

    AcDbObjectId groupId;
    es = pGroupDict->getAt( groupName, groupId );
    pGroupDict->close();

    return groupId;
}

bool ArxGroupHelper::GetGroupName( const AcDbObjectId& groupId, CString& groupName )
{
    AcTransaction* pTrans = actrTransactionManager->startTransaction();
    if( pTrans == 0 ) return false;

    //AcDb::OpenMode om = ( save ? ( AcDb::kForWrite ) : ( AcDb::kForRead ) );
    AcDbObject* pObj;
    if( Acad::eOk != pTrans->getObject( pObj, groupId, AcDb::kForRead ) )
    {
        actrTransactionManager->abortTransaction();
        return false;
    }
    AcDbGroup* pGroup = AcDbGroup::cast( pObj );
    if( pGroup == 0 )
    {
        actrTransactionManager->abortTransaction();
        return false;
    }

    groupName = pGroup->name();

    actrTransactionManager->endTransaction();

    return true;
}

void ArxGroupHelper::SetGroupName( const AcDbObjectId& groupId, const CString& groupName )
{
    AcTransaction* pTrans = actrTransactionManager->startTransaction();
    if( pTrans == 0 ) return;

    //AcDb::OpenMode om = ( save ? ( AcDb::kForWrite ) : ( AcDb::kForRead ) );
    AcDbObject* pObj;
    if( Acad::eOk != pTrans->getObject( pObj, groupId, AcDb::kForRead ) )
    {
        actrTransactionManager->abortTransaction();
        return;
    }
    AcDbGroup* pGroup = AcDbGroup::cast( pObj );
    if( pGroup == 0 )
    {
        actrTransactionManager->abortTransaction();
        return;
    }

    pGroup->setName( groupName );

    actrTransactionManager->endTransaction();
}

bool ArxGroupHelper::RemoveGroup( const AcDbObjectId& groupId )
{
    AcTransaction* pTrans = actrTransactionManager->startTransaction();
    if( pTrans == 0 ) return false;

    //AcDb::OpenMode om = ( save ? ( AcDb::kForWrite ) : ( AcDb::kForRead ) );
    AcDbObject* pObj;
    if( Acad::eOk != pTrans->getObject( pObj, groupId, AcDb::kForWrite ) )
    {
        actrTransactionManager->abortTransaction();
        return false;
    }
    AcDbGroup* pGroup = AcDbGroup::cast( pObj );
    if( pGroup == 0 )
    {
        actrTransactionManager->abortTransaction();
        return false;
    }

    //删除所有的实体
    AcDbGroupIterator* pIter = pGroup->newIterator();
    for ( ; !pIter->done(); pIter->next() )
    {
        AcDbObject* pEnt;
        if( Acad::eOk == pIter->getObject( pEnt, AcDb::kForWrite ) )
        {
            pEnt->erase();
        }
    }
    delete pIter;

    //删除group自身
    pGroup->erase();

    actrTransactionManager->endTransaction();

    return true;
}

bool ArxGroupHelper::RemoveGroup( const CString& groupName )
{
    AcDbObjectId groupId = ArxGroupHelper::GetGroup( groupName );
    if( groupId.isNull() ) return false;

    return ArxGroupHelper::RemoveGroup( groupId );
}

bool ArxGroupHelper::ClearGroup( const CString& groupName )
{
    AcDbObjectId groupId = ArxGroupHelper::GetGroup( groupName );
    if( groupId.isNull() ) return false;
    return ArxGroupHelper::ClearGroup( groupId );
}

bool ArxGroupHelper::ClearGroup( const AcDbObjectId& groupId )
{
    AcTransaction* pTrans = actrTransactionManager->startTransaction();
    if( pTrans == 0 ) return false;

    //AcDb::OpenMode om = ( save ? ( AcDb::kForWrite ) : ( AcDb::kForRead ) );
    AcDbObject* pObj;
    if( Acad::eOk != pTrans->getObject( pObj, groupId, AcDb::kForWrite ) )
    {
        actrTransactionManager->abortTransaction();
        return false;
    }
    AcDbGroup* pGroup = AcDbGroup::cast( pObj );
    if( pGroup == 0 )
    {
        actrTransactionManager->abortTransaction();
        return false;
    }
    //清空group
    Acad::ErrorStatus es = pGroup->clear();

    actrTransactionManager->endTransaction();

    return ( es == Acad::eOk );
}
