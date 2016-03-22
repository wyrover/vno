#include "StdAfx.h"
#include "ArxDictTool.h"
#include "ArxXRecordManager.h"
#include "HelperClass.h"

static AcDbDictionary* GetDictObject( const AcDbObjectId& dictId )
{
    AcDbDictionary* pDict = 0;
    if( Acad::eOk != acdbOpenAcDbObject( ( AcDbObject*& ) pDict, dictId, AcDb::kForWrite ) )
        return 0;
    else
        return pDict;
}

static ArxXRecordManager* GetXRecordManager( const AcDbObjectId& dictId, const CString& key, bool createNewKey = false )
{
    //acutPrintf(_T("\n注册: %s"), dictName);

    AcDbDictionary* pDict = GetDictObject( dictId );
    if( pDict == 0 ) return 0;

    AcDbXrecord* pXrec = 0;
    // key不存在或者其它原因
    Acad::ErrorStatus es = pDict->getAt( key, ( AcDbObject*& ) pXrec, AcDb::kForWrite );
    if( Acad::eOk != es && Acad::eKeyNotFound != es )
    {
        pDict->close();
        return 0;
    }

    if( Acad::eKeyNotFound == es )
    {
        if( createNewKey )
        {
            pXrec = new AcDbXrecord();
            AcDbObjectId xrecObjId;
            pDict->setAt( key, pXrec, xrecObjId );
        }
        else
        {
            pDict->close();
            return 0;
        }
    }
    pDict->close();
    return new ArxXRecordManager( pXrec );
}

static bool FindDictKey( const AcDbObjectId& dictId, const CString& key )
{
    AcDbDictionary* pDict = GetDictObject( dictId );
    if( pDict == 0 ) return false;

    bool ret = pDict->has( key );
    pDict->close();
    return ret;
}

static void RemoveDictKey( const AcDbObjectId& dictId, const CString& key )
{
    AcDbDictionary* pDict = GetDictObject( dictId );
    if( pDict == 0 ) return;

    AcDbObjectId objId;
    pDict->remove( key, objId );
    ArxEntityHelper::EraseObject2( objId, true ); // 删除对象
    pDict->close();
}

AcDbObjectId ArxDictTool::GetExtensionDict( const AcDbObjectId& objId )
{
    AcTransaction* pTrans = actrTransactionManager->startTransaction();
    if( pTrans == 0 ) return AcDbObjectId::kNull;

    AcDbObject* pObj;
    if( Acad::eOk != pTrans->getObject( pObj, objId, AcDb::kForWrite ) )
    {
        actrTransactionManager->abortTransaction();
        return AcDbObjectId::kNull;
    }

    AcDbObjectId dictId = pObj->extensionDictionary();
    if( dictId.isNull() )
    {
        if( Acad::eOk == pObj->createExtensionDictionary() )
        {
            dictId = pObj->extensionDictionary();
        }
    }
    actrTransactionManager->endTransaction();

    return dictId;
}

bool ArxDictTool::IsDictExist( const CString& dictName )
{
    AcDbDictionary* pNamedobj;
    acdbHostApplicationServices()->workingDatabase()->getNamedObjectsDictionary( pNamedobj, AcDb::kForRead );

    bool ret = pNamedobj->has( dictName );
    pNamedobj->close();

    return ret;
}

void ArxDictTool::RegDict( const CString& dictName )
{
    // 初始化工作，建立存储词典
    AcDbDictionary* pNamedobj;
    acdbHostApplicationServices()->workingDatabase()->getNamedObjectsDictionary( pNamedobj, AcDb::kForWrite );

    AcDbObject* pObj;
    Acad::ErrorStatus es = pNamedobj->getAt( dictName, pObj, AcDb::kForRead );
    if( Acad::eOk ==  es )
    {
        pObj->close();
    }
    else if( Acad::eKeyNotFound == es )
    {
        AcDbDictionary* pDict = new AcDbDictionary();
        AcDbObjectId dictId;
        if( Acad::eOk != pNamedobj->setAt( dictName, pDict, dictId ) )
        {
            delete pDict;
        }
        else
        {
            pDict->close();
        }
    }
    pNamedobj->close();
}

AcDbObjectId ArxDictTool::GetDict( const CString& dictName )
{
    AcDbDictionary* pNameObjDict;
    if( Acad::eOk != acdbHostApplicationServices()->workingDatabase()->getNamedObjectsDictionary( pNameObjDict, AcDb::kForRead ) )
    {
        return AcDbObjectId::kNull;
    }

    AcDbObjectId dictId;
    Acad::ErrorStatus es = pNameObjDict->getAt( dictName, dictId );
    pNameObjDict->close();

    return dictId;
}

ArxDictTool::ArxDictTool( const AcDbObjectId& dictId ) : m_dictId( dictId )
{

}

bool ArxDictTool::findKey( const CString& key )
{
    return FindDictKey( m_dictId, key );
}

void ArxDictTool::removeKey( const CString& key )
{
    RemoveDictKey( m_dictId, key );
}

void ArxDictTool::getAllKeys( AcStringArray& keys )
{
    AcDbDictionary* pDict = GetDictObject( m_dictId );
    if( pDict == 0 ) return;

    AcDbDictionaryIterator* pIter = pDict->newIterator();
    for ( ; !pIter->done(); pIter->next() )
    {
        keys.append( pIter->name() );
    }
    delete pIter;
    pDict->close();
}

int ArxDictTool::addEntry( const CString& key, const CString& entry )
{
    // 1、获取图元对应的AcDbXrecord
    //    并封装成DataFieldManager对象
    ArxXRecordManager* pDEM = GetXRecordManager( m_dictId, key, true );
    if( pDEM == 0 ) return INVALID_ENTRY;

    // 2、添加字段
    int index = pDEM->addEntry( entry );
    delete pDEM;

    return index;
}

int ArxDictTool::removeEntry( const CString& key, const CString& entry )
{
    // 1、获取图元对应的AcDbXrecord
    //    并封装成DataFieldManager对象
    ArxXRecordManager* pDEM = GetXRecordManager( m_dictId, key );
    if( pDEM == 0 ) return INVALID_ENTRY;

    // 2、删除字段
    int index = pDEM->removeEntry( entry );
    delete pDEM;

    return index;
}

int ArxDictTool::countEntries( const CString& key )
{
    // 1、获取图元对应的AcDbXrecord
    //    并封装成DataFieldManager对象
    ArxXRecordManager* pDEM = GetXRecordManager( m_dictId, key );
    if( pDEM == 0 ) return INVALID_ENTRY;

    int count = pDEM->countEntries();
    delete pDEM;

    return count;
}

int ArxDictTool::findEntry( const CString& key, const CString& entry )
{
    // 1、获取图元对应的AcDbXrecord
    //    并封装成DataFieldManager对象
    ArxXRecordManager* pDEM = GetXRecordManager( m_dictId, key );
    if( pDEM == 0 ) return INVALID_ENTRY;

    // 2、查找字段索引位置
    int index = pDEM->findEntry( entry );
    delete pDEM;

    return index;
}

void ArxDictTool::getAllEntries( const CString& key, AcStringArray& entries )
{
    // 1、获取图元对应的AcDbXrecord
    //    并封装成DataFieldManager对象
    ArxXRecordManager* pDEM = GetXRecordManager( m_dictId, key );
    if( pDEM == 0 ) return;

    pDEM->getAllEntries( entries );
    delete pDEM;
}

bool ArxDictTool::modifyEntry( const CString& key, int index, const CString& newEntry )
{
    if( index == INVALID_ENTRY ) return false;

    ArxXRecordManager* pDEM = GetXRecordManager( m_dictId, key );
    if( pDEM == 0 ) return false;

    bool flag = pDEM->modifyEntry( index, newEntry );
    delete pDEM;

    return flag;
}

bool ArxDictTool::getEntry( const CString& key, int index, CString& entry )
{
    if( index == INVALID_ENTRY ) return false;

    ArxXRecordManager* pDEM = GetXRecordManager( m_dictId, key );
    if( pDEM == 0 ) return false;

    bool flag = pDEM->getEntry( index, entry );
    delete pDEM;

    return flag;
}

ArxDictTool* ArxDictTool::GetDictTool( const CString& dictName )
{
    AcDbObjectId dictId = ArxDictTool::GetDict( dictName );
    if( dictId.isNull() )
        return 0;
    else
        return new ArxDictTool( dictId );
}

ArxDictTool* ArxDictTool::GetDictTool( const AcDbObjectId& dictId )
{
    return new ArxDictTool( dictId );
}


////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

ArxDictTool2* ArxDictTool2::GetDictTool( const CString& dictName )
{
    AcDbObjectId dictId = ArxDictTool::GetDict( dictName );
    if( dictId.isNull() )
        return 0;
    else
        return new ArxDictTool2( dictId );
}

ArxDictTool2* ArxDictTool2::GetDictTool( const AcDbObjectId& dictId )
{
    return new ArxDictTool2( dictId );
}

ArxDictTool2::ArxDictTool2( const AcDbObjectId& dictId ) : m_dictId( dictId )
{

}

bool ArxDictTool2::addEntry( const CString& key, AcDbObject* pObj )
{
    AcDbDictionary* pDict = GetDictObject( m_dictId );
    if( pDict == 0 ) return false;

    bool ret = false;
    if( !pDict->has( key ) )
    {
        AcDbObjectId objId;
        if( Acad::eOk == pDict->setAt( key, pObj, objId ) )
        {
            pObj->close();
            ret = true;
        }
    }
    pDict->close();

    return ret;
}

bool ArxDictTool2::removeEntry( const CString& key )
{
    AcDbDictionary* pDict = GetDictObject( m_dictId );
    if( pDict == 0 ) return false;

    AcDbObjectId objId;
    bool ret = ( Acad::eOk == pDict->remove( key, objId ) );
    pDict->close();

    if( ret )
    {
        ArxEntityHelper::EraseObject2( objId, true );
    }
    return ret;
}

bool ArxDictTool2::findEntry( const CString& key, AcDbObjectId& objId )
{
    AcDbDictionary* pDict = GetDictObject( m_dictId );
    if( pDict == 0 ) return false;

    bool ret = ( Acad::eOk == pDict->getAt( key, objId ) );
    //acutPrintf(_T("\nArxDitToll->Ret:%s"),ret?_T("Y"):_T("N"));
    pDict->close();

    return ret;
}

void ArxDictTool2::getAllKeys( AcStringArray& keys )
{
    AcDbDictionary* pDict = GetDictObject( m_dictId );
    if( pDict == 0 ) return;

    AcDbDictionaryIterator* pIter = pDict->newIterator();
    for ( ; !pIter->done(); pIter->next() )
    {
        keys.append( pIter->name() );
    }
    delete pIter;
    pDict->close();
}

void ArxDictTool2::getAllEntries( AcDbObjectIdArray& objIds )
{
    AcDbDictionary* pDict = GetDictObject( m_dictId );
    if( pDict == 0 ) return;

    AcDbDictionaryIterator* pIter = pDict->newIterator();
    for ( ; !pIter->done(); pIter->next() )
    {
        objIds.append( pIter->objectId() );
    }
    delete pIter;
    pDict->close();
}

void ArxDictHelper::GetAllKeys( const CString& dictName, AcStringArray& keys )
{
    keys.removeAll();
    ArxDictTool* pDictTool = ArxDictTool::GetDictTool( dictName );
    pDictTool->getAllKeys( keys );
    delete pDictTool;
}

bool ArxDictHelper::GetAllEntries( const CString& dictName, const CString& key, AcStringArray& entries )
{
    if( key.GetLength() == 0 ) return false;

    entries.removeAll();
    ArxDictTool* pDictTool = ArxDictTool::GetDictTool( dictName );
    bool ret = pDictTool->findKey( key );
    if( ret )
    {
        pDictTool->getAllEntries( key, entries );
    }
    delete pDictTool;
    return ret;
}

void ArxDictHelper::RemoveAllEntries( const CString& dictName, const CString& key )
{
    if( key.GetLength() == 0 ) return;
    ArxDictTool* pDictTool = ArxDictTool::GetDictTool( dictName );
    pDictTool->removeKey( key );
    delete pDictTool;
}

bool ArxDictHelper::RemoveEntry( const CString& dictName, const CString& key, const CString& entry )
{
    if( key.GetLength() == 0 ) return false;
    ArxDictTool* pDictTool = ArxDictTool::GetDictTool( dictName );
    bool ret = ( INVALID_ENTRY != pDictTool->removeEntry( key, entry ) );
    delete pDictTool;
    return ret;
}

bool ArxDictHelper::AddEntry( const CString& dictName, const CString& key, const CString& entry )
{
    ArxDictTool* pDictTool = ArxDictTool::GetDictTool( dictName );
    bool ret = ( INVALID_ENTRY != pDictTool->addEntry( key, entry ) );
    delete pDictTool;
    return ret;
}
void ArxDictHelper::RemoveKey( const CString& dictName, const CString& key )
{
    ArxDictTool* pDictTool = ArxDictTool::GetDictTool( dictName );
    pDictTool->removeKey( key );
    delete pDictTool;
}
