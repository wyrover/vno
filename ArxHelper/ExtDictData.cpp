#include "StdAfx.h"
#include "ExtDictData.h"
#include "HelperClass.h"
#include "ArxXRecordManager.h"

void ExtDictData::mapString( const CString& field, CString* pValue )
{
    linkByField( field, DataMapper::DT_STRING, pValue );
}

void ExtDictData::mapInt( const CString& field, int* pValue )
{
    linkByField( field, DataMapper::DT_INT, pValue );
}

void ExtDictData::mapDouble( const CString& field, double* pValue )
{
    linkByField( field, DataMapper::DT_NUMERIC, pValue );
}

void ExtDictData::mapBool( const CString& field, bool* pValue )
{
    linkByField( field, DataMapper::DT_BOOL, pValue );
}

void ExtDictData::mapDateTime( const CString& field, COleDateTime* pValue )
{
    linkByField( field, DataMapper::DT_DATE, pValue );
}

void ExtDictData::mapPoint( const CString& field, AcGePoint3d* pValue )
{
    linkByField( field, DataMapper::DT_POINT, pValue );
}

void ExtDictData::mapVector( const CString& field, AcGeVector3d* pValue )
{
    linkByField( field, DataMapper::DT_VECTOR, pValue );
}

class ExtDictDao : public Dao
{
public:
    ExtDictDao( const AcDbObjectId& objId ) : m_pDict( 0 ), m_createNewKey( true )
    {
        if( objId.isNull() ) return;

        //获取扩展词典id
        AcDbObjectId dictId = ArxDictTool::GetExtensionDict( objId );
        if( dictId.isNull() ) return;

        AcTransaction* pTrans = actrTransactionManager->startTransaction();
        if( pTrans == 0 ) return;

        //AcDb::OpenMode om = ( save ? ( AcDb::kForWrite ) : ( AcDb::kForRead ) );
        AcDbObject* pObj;
        if( Acad::eOk != pTrans->getObject( pObj, dictId, AcDb::kForWrite ) )
        {
            actrTransactionManager->abortTransaction();
            m_pDict = 0;
            return;
        }
        m_pDict = AcDbDictionary::cast( pObj );
        if( m_pDict == 0 )
        {
            actrTransactionManager->abortTransaction();
            return;
        }
    }
    ~ExtDictDao()
    {
        if( m_pDict != 0 )
        {
            actrTransactionManager->endTransaction();
        }
    }
    virtual void clear()
    {
        //清空
        //pDict->erase();
        AcStringArray names;
        AcDbDictionaryIterator* itr = m_pDict->newIterator();
        while( !itr->done() )
        {
            names.append( itr->name() );
            itr->next();
        }
        delete itr;

        for( int i = 0; i < names.length(); i++ )
        {
            m_pDict->remove( names[i].kACharPtr() );
        }
    }
    virtual bool set( const CString& key, const CString& value )
    {
        if( m_pDict == 0 ) return false;

        AcDbXrecord* pXrec = 0;
        // key不存在或者其它原因
        Acad::ErrorStatus es = m_pDict->getAt( key, ( AcDbObject*& ) pXrec, AcDb::kForWrite );
        if( Acad::eOk != es && Acad::eKeyNotFound != es )
        {
            return false;
        }
        if( Acad::eKeyNotFound == es )
        {
            if( m_createNewKey )
            {
                pXrec = new AcDbXrecord();
                AcDbObjectId xrecObjId;
                if( Acad::eOk != m_pDict->setAt( key, pXrec, xrecObjId ) )
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }

        ArxXRecordManager dem( pXrec );
        CString temp_value;
        if( !dem.getEntry( 0, temp_value ) )
        {
            return ( dem.addEntry( value ) != INVALID_ENTRY );
        }
        else
        {
            return dem.modifyEntry( 0, value ); // 每个XRECORD只存放一个数据
        }
    }
    virtual bool get( const CString& key, CString& value )
    {
        if( m_pDict == 0 ) return false;

        AcDbXrecord* pXrec = 0;
        // key不存在或者其它原因
        Acad::ErrorStatus es = m_pDict->getAt( key, ( AcDbObject*& ) pXrec, AcDb::kForWrite );
        if( Acad::eOk != es && Acad::eKeyNotFound != es )
        {
            return false;
        }
        ArxXRecordManager dem( pXrec );
        return dem.getEntry( 0, value ); // 每个XRECORD只存放一个数据
    }

private:
    AcDbDictionary* m_pDict;
    bool m_createNewKey;
};

Dao* ExtDictData::createDao( const AcDbObjectId& objId )
{
    return new ExtDictDao( objId );
}

void ExtDictData::Init( const AcDbObjectId& objId, const AcStringArray& fields, const AcStringArray& values )
{
    if( objId.isNull() ) return;

    ExtDictDao dao( objId );
    dao.clear(); // 清空
    for( int i = 0; i < values.length(); i++ )
    {
        dao.set( fields[i].kACharPtr(), values[i].kACharPtr() );
    }
}

bool ExtDictData::Get( const AcDbObjectId& objId, const CString& field, CString& value )
{
    if( objId.isNull() ) return false;

    ExtDictDao dao( objId );
    return dao.get( field, value );
}

bool ExtDictData::Set( const AcDbObjectId& objId, const CString& field, const CString& value )
{
    if( objId.isNull() ) return false;

    ExtDictDao dao( objId );
    return dao.set( field, value );
}

void ExtDictData::Copy( const AcDbObjectId& sourceObjId, const AcDbObjectId& targetObjId )
{

}
