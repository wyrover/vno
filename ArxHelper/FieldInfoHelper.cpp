#include "StdAfx.h"
#include "HelperClass.h"
#include "config.h"

FieldInfo::FieldInfo()
{
    initDefault();
}

void FieldInfo::initDefault()
{
    m_dt = DT_STRING;
    m_enable = true;
    m_descr = _T( "" );
    m_tolrance = 4;
    m_showInTooltip = false;
    initListType();
    initIntMinMaxValue();
    initNumericMinMaxValue();
}

void FieldInfo::copyFrom( const FieldInfo& info )
{
    m_dt = info.m_dt;
    m_minValue2 = info.m_minValue2;
    m_maxValue2 = info.m_maxValue2;
    m_minValue = info.m_minValue;
    m_maxValue = info.m_maxValue;
    m_enable = info.m_enable;
    m_descr = info.m_descr;
    m_lt = info.m_lt;
    m_varName = info.m_varName;
    m_tolrance = info.m_tolrance;
    m_showInTooltip = info.m_showInTooltip;
}

void FieldInfo::initNumericMinMaxValue()
{
    m_minValue = 0;
    m_maxValue = 0;
}

void FieldInfo::initIntMinMaxValue()
{
    m_minValue2 = 0;
    m_maxValue2 = 0;
}

void FieldInfo::initListType()
{
    m_lt = LT_STRING;
    m_varName = _T( "" );
}

void FieldInfo::revise()
{
    switch( m_dt )
    {
    case DT_STRING:
    case DT_BOOL:
    case DT_DATE:
        initListType();
        initIntMinMaxValue();
        initNumericMinMaxValue();
        break;
    case DT_INT:
        initListType();
        initNumericMinMaxValue();
        break;
    case DT_NUMERIC:
        initListType();
        initIntMinMaxValue();
        break;
    case DT_LIST:
        initIntMinMaxValue();
        initNumericMinMaxValue();
        break;
    }
}

bool FieldInfo::isDefault() const
{
    return ( ( m_dt == DT_STRING ) && m_enable && ( m_descr.GetLength() == 0 ) && !m_showInTooltip );
}

bool FieldInfo::isObjectListType() const
{
    return ( ( m_dt == DT_LIST ) &&
             ( m_lt == LT_OBJECT ) &&
             ( m_varName.GetLength() != 0 ) );
}


Adesk::UInt32 FieldInfoObject::kCurrentVersionNumber = 1 ;

ACRX_DXF_DEFINE_MEMBERS (
    FieldInfoObject, AcDbObject,
    AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent,
    AcDbProxyEntity::kNoOperation, FIELDINFOOBJECT,
    MINEGEAPP )

FieldInfoObject::FieldInfoObject () : AcDbObject ()
{
}

FieldInfoObject::~FieldInfoObject ()
{
}

Acad::ErrorStatus FieldInfoObject::dwgOutFields ( AcDbDwgFiler* pFiler ) const
{
    assertReadEnabled () ;
    //----- Save parent class information first.
    Acad::ErrorStatus es = AcDbObject::dwgOutFields ( pFiler ) ;
    if ( es != Acad::eOk )
        return ( es ) ;
    //----- Object version number needs to be saved first
    if ( ( es = pFiler->writeUInt32 ( FieldInfoObject::kCurrentVersionNumber ) ) != Acad::eOk )
        return ( es ) ;

    pFiler->writeInt16( m_info.m_dt );

    pFiler->writeInt32( m_info.m_minValue2 );
    pFiler->writeInt32( m_info.m_maxValue2 );

    pFiler->writeDouble( m_info.m_minValue );
    pFiler->writeDouble( m_info.m_maxValue );

    pFiler->writeInt16( m_info.m_lt );
    pFiler->writeString( ( LPCTSTR )m_info.m_varName );

    pFiler->writeBool( m_info.m_enable );
    pFiler->writeString( ( LPCTSTR )m_info.m_descr );
    pFiler->writeBool( m_info.m_showInTooltip );

    return ( pFiler->filerStatus () ) ;
}

Acad::ErrorStatus FieldInfoObject::dwgInFields ( AcDbDwgFiler* pFiler )
{
    assertWriteEnabled () ;
    //----- Read parent class information first.
    Acad::ErrorStatus es = AcDbObject::dwgInFields ( pFiler ) ;
    if ( es != Acad::eOk )
        return ( es ) ;
    //----- Object version number needs to be read first
    Adesk::UInt32 version = 0 ;
    if ( ( es = pFiler->readUInt32 ( &version ) ) != Acad::eOk )
        return ( es ) ;
    if ( version > FieldInfoObject::kCurrentVersionNumber )
        return ( Acad::eMakeMeProxy ) ;

    short iValue;
    pFiler->readInt16( &iValue );
    m_info.m_dt = ( FieldInfo::DATA_TYPE )iValue;

    long nValue;
    pFiler->readInt32( &nValue );
    m_info.m_minValue2 = ( int )nValue;
    pFiler->readInt32( &nValue );
    m_info.m_maxValue2 = ( int )nValue;

    double dValue;
    pFiler->readDouble( &dValue );
    m_info.m_minValue = nValue;
    pFiler->readDouble( &dValue );
    m_info.m_maxValue = nValue;

    pFiler->readInt16( &iValue );
    m_info.m_lt = ( FieldInfo::LIST_TYPE )iValue;

    AcString str;
    pFiler->readString( str );
    m_info.m_varName = str.kACharPtr();

    bool bValue;
    pFiler->readBool( &bValue );
    m_info.m_enable = bValue;

    pFiler->readString( str );
    m_info.m_descr = str.kACharPtr();

    pFiler->readBool( &bValue );
    m_info.m_showInTooltip = bValue;

    return ( pFiler->filerStatus () ) ;
}

static CString MakeFieldInfoKey( const CString& type, const CString& field )
{
    CString key;
    key.Format( _T( "%s_%s" ), type, field );
    return key;
}

void FieldInfoHelper::ReadFieldInfo( const CString& type, const CString& field, FieldInfo& info )
{
    // 读取字段信息数据
    ArxDictTool2* pDictTool = ArxDictTool2::GetDictTool( PROPERTY_DATA_FIELD_INFO_DICT );
    AcDbObjectId objId;
    bool ret = pDictTool->findEntry( MakeFieldInfoKey( type, field ), objId );
    delete pDictTool;

    if( !ret ) return;

    AcTransaction* pTrans = actrTransactionManager->startTransaction();
    if( pTrans == 0 ) return;

    AcDbObject* pObj;
    if( Acad::eOk == pTrans->getObject( pObj, objId, AcDb::kForRead ) )
    {
        FieldInfoObject* pInfoObject = FieldInfoObject::cast( pObj );
        info.copyFrom( pInfoObject->m_info );
    }
    actrTransactionManager->endTransaction();
}

void FieldInfoHelper::WriteFieldInfo( const CString& type, const CString& field, const FieldInfo& info )
{
    // 读取字段信息数据
    ArxDictTool2* pDictTool = ArxDictTool2::GetDictTool( PROPERTY_DATA_FIELD_INFO_DICT );
    AcDbObjectId objId;
    bool ret = pDictTool->findEntry( MakeFieldInfoKey( type, field ), objId );
    delete pDictTool;

    if( !ret ) return;

    AcTransaction* pTrans = actrTransactionManager->startTransaction();
    if( pTrans == 0 ) return;

    AcDbObject* pObj;
    if( Acad::eOk == pTrans->getObject( pObj, objId, AcDb::kForWrite ) )
    {
        FieldInfoObject* pInfoObject = FieldInfoObject::cast( pObj );
        pInfoObject->m_info.copyFrom( info );
    }
    actrTransactionManager->endTransaction();
}

void FieldInfoHelper::RemoveFieldInfo( const CString& type, const CString& field )
{
    ArxDictTool2* pDictTool2 = ArxDictTool2::GetDictTool( PROPERTY_DATA_FIELD_INFO_DICT );
    pDictTool2->removeEntry( MakeFieldInfoKey( type, field ) );
    delete pDictTool2;
}

bool FieldInfoHelper::FindFieldInfo( const CString& type, const CString& field )
{
    ArxDictTool2* pDictTool = ArxDictTool2::GetDictTool( PROPERTY_DATA_FIELD_INFO_DICT );
    AcDbObjectId objId;
    bool ret = pDictTool->findEntry( MakeFieldInfoKey( type, field ), objId );
    delete pDictTool;
    return ret;
}

void FieldInfoHelper::AddFieldInfo( const CString& type, const CString& field, const FieldInfo& info )
{
    ArxDictTool2* pDictTool = ArxDictTool2::GetDictTool( PROPERTY_DATA_FIELD_INFO_DICT );
    FieldInfoObject* pInfoObj = new FieldInfoObject();
    pInfoObj->m_info.copyFrom( info );
    if( !pDictTool->addEntry( MakeFieldInfoKey( type, field ), pInfoObj ) ) delete pInfoObj;
    delete pDictTool;
}