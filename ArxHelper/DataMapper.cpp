#include "StdAfx.h"
#include "DataMapper.h"
#include "HelperClass.h"

static resbuf* GoToListEnd( resbuf* pHead, const CString& field )
{
    resbuf* pTemp = pHead;
    while( pTemp != 0 )
    {
        // 存在相同的字段名称
        if( field.CompareNoCase( pTemp->resval.rstring ) == 0 ) break;
        bool isBreak = false;
        // 循环3次，跳到下一个字段节点
        for( int i = 0; i < 3; i++ )
        {
            if( pTemp->rbnext == 0 )
            {
                isBreak = true;
                break;
            }
            pTemp = pTemp->rbnext;
        }
        if( isBreak ) break;
    }
    return pTemp;
}

static void LinkGenericDataByField( resbuf*& pHead, const CString& field, short rtype, void* pValue )
{
    if( field.GetLength() == 0 ) return;

    resbuf* pTemp = 0;
    if( pHead == 0 )
    {
        pHead = acutBuildList( RTSTR, field, RTSHORT, rtype, RTLONG_PTR, ( long )pValue, 0 );
    }
    else
    {
        pTemp = GoToListEnd( pHead, field );
        if( pTemp->rbnext == 0 )
        {
            pTemp->rbnext = acutBuildList( RTSTR, field, RTSHORT, rtype, RTLONG_PTR, ( long )pValue, 0 );
        }
    }
}

static void LinkGenericDataByPos( resbuf*& pHead, int pos, short rtype, void* pValue )
{
    if( pos < 0 ) return;

    CString field;
    ArxUtilHelper::IntToString( pos, field );
    LinkGenericDataByField( pHead, field, rtype, pValue );
}

static resbuf* SetData( resbuf* pStart, const CString& value )
{
    resbuf* pTypeNode = pStart->rbnext;
    resbuf* pValueNode = pTypeNode->rbnext;

    short rtype = pTypeNode->resval.rint;
    long ptr = pValueNode->resval.mnLongPtr;
    switch( rtype )
    {
    case DataMapper::DT_STRING:
    {
        CString* pValue = ( CString* )ptr;
        *pValue = value;
    }
    break;

    case DataMapper::DT_INT:
    {
        int iv = 0;
        ArxUtilHelper::StringToInt( value, iv );
        int* pValue = ( int* )ptr;
        *pValue = iv;
    }
    break;

    case DataMapper::DT_NUMERIC:
    {
        double dv = 0;
        ArxUtilHelper::StringToDouble( value, dv );
        double* pValue = ( double* )ptr;
        *pValue = dv;
    }
    break;

    case DataMapper::DT_BOOL:
    {
        int iv = 0;
        bool bv = false;
        if( ArxUtilHelper::StringToInt( value, iv ) )
        {
            bv = ( iv != 0 ); // 等于0为假，不等于0为真
        }
        bool* pValue = ( bool* )ptr;
        *pValue = bv;
    }
    break;

    case DataMapper::DT_DATE:
    {
        COleDateTime dt;
        if( ( value.GetLength() == 0 ) || !dt.ParseDateTime( value ) )
        {
            // 当前时间
            dt = COleDateTime::GetCurrentTime();
        }
        COleDateTime* pValue = ( COleDateTime* )ptr;
        *pValue = dt;
    }
    break;

    case DataMapper::DT_POINT:
    {
        AcGePoint3d pt;
        ArxUtilHelper::StringToPoint3d( value, pt );
        AcGePoint3d* pValue = ( AcGePoint3d* )ptr;
        *pValue = pt;
    }
    break;

    case DataMapper::DT_VECTOR:
    {
        AcGeVector3d v;
        ArxUtilHelper::StringToVector3d( value, v );
        AcGeVector3d* pValue = ( AcGeVector3d* )ptr;
        *pValue = v;
    }
    break;
    }
    return pValueNode->rbnext;
}

static resbuf* GetData( resbuf* pStart, CString& value )
{
    resbuf* pTypeNode = pStart->rbnext;
    resbuf* pValueNode = pTypeNode->rbnext;

    short rtype = pTypeNode->resval.rint;
    long ptr = pValueNode->resval.mnLongPtr;
    switch( rtype )
    {
    case DataMapper::DT_STRING:
        value = *( ( CString* )ptr );
        break;

    case DataMapper::DT_INT:
        ArxUtilHelper::IntToString( *( ( int* )ptr ), value );
        break;

    case DataMapper::DT_NUMERIC:
        ArxUtilHelper::DoubleToString( *( ( double* )ptr ), value );
        break;

    case DataMapper::DT_BOOL:
    {
        bool bv = *( bool* )ptr;
        value.Format( _T( "%d" ), ( bv ? -1 : 0 ) ); // -1表示真, 0表示假
    }
    break;

    case DataMapper::DT_DATE:
    {
        COleDateTime dt = *( COleDateTime* )ptr;
        value = ( COleVariant )dt;
    }
    break;

    case DataMapper::DT_POINT:
    {
        value = ArxUtilHelper::Point3dToString( *( ( AcGePoint3d* )ptr ) );
        break;
    }
    break;

    case DataMapper::DT_VECTOR:
    {
        value = ArxUtilHelper::Vector3dToString( *( ( AcGeVector3d* )ptr ) );
        break;
    }
    break;
    }
    return pValueNode->rbnext;
}

DataMapper::DataMapper() : m_pDatasToFileds( 0 )
{

}

DataMapper::~DataMapper( void )
{
    if( m_pDatasToFileds != NULL )
    {
        acutRelRb( m_pDatasToFileds );
    }
}

void DataMapper::setDataSource( const AcDbObjectId& objId )
{
    // 只允许关联一次
    if( !m_objId.isNull() | objId.isNull() ) return;
    m_objId = objId;
}

AcDbObjectId DataMapper::getDataSource() const
{
    return m_objId;
}

void DataMapper::linkByField( const CString& field, short rtype, void* pValue )
{
    LinkGenericDataByField( m_pDatasToFileds, field, rtype, pValue );
}

void DataMapper::linkByPos( int pos, short rtype, void* pValue )
{
    LinkGenericDataByPos( m_pDatasToFileds, pos, rtype, pValue );
}

static bool UpdateDataHelper( Dao* dao, resbuf* pTemp, bool save )
{
    while( pTemp != 0 )
    {
        CString field = pTemp->resval.rstring;
        if( save )
        {
            CString value;
            pTemp = GetData( pTemp, value );
            dao->set( field, value );
        }
        else
        {
            CString value;
            bool ret = dao->get( field, value );
            if( !ret )
            {
                for( int i = 0; i < 3; i++ ) pTemp = pTemp->rbnext;
            }
            else
            {
                pTemp = SetData( pTemp, value );
            }
        }
    }
    return true;
}

bool DataMapper::update( bool save/*=false*/ )
{
    if( m_objId.isNull() ) return false;

    // 如果字段没有初始化，则初始化
    if( m_pDatasToFileds == 0 )
    {
        regDatas();
    }

    Dao* dao = createDao( m_objId );
    if( dao == 0 ) return false;

    bool ret = UpdateDataHelper( dao, m_pDatasToFileds, save );
    delete dao;
    return ret;
}
