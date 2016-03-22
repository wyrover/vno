#include "StdAfx.h"
#include "XData.h"
#include "HelperClass.h"

#define XDATA_PROPERTY_APPNAME _T("扩展属性数据")

void XData::mapString( int pos, CString* pValue )
{
    linkByPos( pos, DataMapper::DT_STRING, pValue );
}

void XData::mapInt( int pos, int* pValue )
{
    linkByPos( pos, DataMapper::DT_INT, pValue );
}

void XData::mapDouble( int pos, double* pValue )
{
    linkByPos( pos, DataMapper::DT_NUMERIC, pValue );
}

void XData::mapBool( int pos, bool* pValue )
{
    linkByPos( pos, DataMapper::DT_BOOL, pValue );
}

void XData::mapDateTime( int pos, COleDateTime* pValue )
{
    linkByPos( pos, DataMapper::DT_DATE, pValue );
}

void XData::mapPoint( int pos, AcGePoint3d* pValue )
{
    linkByPos( pos, DataMapper::DT_POINT, pValue );
}

void XData::mapVector( int pos, AcGeVector3d* pValue )
{
    linkByPos( pos, DataMapper::DT_VECTOR, pValue );
}

class XDao : public Dao
{
public:
    XDao( const AcDbObjectId& objId ) : m_pObj( 0 )
    {
        if( objId.isNull() ) return;

        AcTransaction* pTrans = actrTransactionManager->startTransaction();
        if( pTrans == 0 ) return;

        //AcDb::OpenMode om = ( save ? ( AcDb::kForWrite ) : ( AcDb::kForRead ) );
        if( Acad::eOk != pTrans->getObject( m_pObj, objId, AcDb::kForWrite ) )
        {
            actrTransactionManager->abortTransaction();
            m_pObj = 0;
            return;
        }
    }
    ~XDao()
    {
        if( m_pObj != 0 )
        {
            actrTransactionManager->endTransaction();
        }
    }
    virtual void clear()
    {
        ArxDbgAppXdata xdata( XDATA_PROPERTY_APPNAME, acdbHostApplicationServices()->workingDatabase() );
        xdata.getXdata( m_pObj );
        xdata.removeAll();
        xdata.setXdata( m_pObj );
    }
    virtual bool get( const CString& key, CString& value )
    {
        int pos = -1;
        if( !ArxUtilHelper::StringToInt( key, pos ) ) return false;
        if( pos < 0 ) return false;

        ArxDbgAppXdata xdata( XDATA_PROPERTY_APPNAME, acdbHostApplicationServices()->workingDatabase() );
        xdata.getXdata( m_pObj );
        if( xdata.isEmpty() ) return false;

        return xdata.getString( pos, value );
    }

    virtual bool set( const CString& key, const CString& value )
    {
        int pos = -1;
        if( !ArxUtilHelper::StringToInt( key, pos ) ) return false;
        if( pos < 0 ) return false;

        ArxDbgAppXdata xdata( XDATA_PROPERTY_APPNAME, acdbHostApplicationServices()->workingDatabase() );
        xdata.getXdata( m_pObj );
        //if(xdata.isEmpty()) return false;

        xdata.setString( pos, value );
        return ( Acad::eOk == xdata.setXdata( m_pObj ) );
    }

private:
    AcDbObject* m_pObj;
};

Dao* XData::createDao( const AcDbObjectId& objId )
{
    return new XDao( objId );
}

void XData::Init( const AcDbObjectId& objId, int n )
{
    if( objId.isNull() ) return;
    if( n < 1 ) return;

    AcStringArray values;
    for( int i = 0; i < n; i++ )
    {
        values.append( _T( "" ) );
    }
    XData::Init( objId, values );
}

void XData::Init( const AcDbObjectId& objId, const AcStringArray& values )
{
    if( objId.isNull() ) return;
    if( values.isEmpty() ) return;

    XDao dao( objId );
    dao.clear(); // 清空
    for( int i = 0; i < values.length(); i++ )
    {
        CString field;
        ArxUtilHelper::IntToString( i, field );

        dao.set( field, values[i].kACharPtr() );
    }
}

bool XData::Get( const AcDbObjectId& objId, int pos, CString& value )
{
    if( objId.isNull() ) return false;

    XDao dao( objId );
    CString field;
    ArxUtilHelper::IntToString( pos, field );
    return dao.get( field, value );
}

bool XData::Set( const AcDbObjectId& objId, int pos, const CString& value )
{
    if( objId.isNull() ) return false;

    XDao dao( objId );
    CString field;
    ArxUtilHelper::IntToString( pos, field );
    return dao.set( field, value );
}

void XData::Copy( const AcDbObjectId& sourceObjId, const AcDbObjectId& targetObjId )
{

}
