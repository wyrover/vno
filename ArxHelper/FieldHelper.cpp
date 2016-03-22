#include "StdAfx.h"
#include "config.h"
#include "HelperClass.h"

#include <set>

#define SEPARATOR _T("~")

static bool IsEmptyString( const CString& str )
{
    return ( str.GetLength() == 0 );
}

static bool FindKey_Helper( const CString& dictName, const CString& type )
{
    ArxDictTool* pDictTool = ArxDictTool::GetDictTool( dictName );
    bool ret = pDictTool->findKey( type );
    delete pDictTool;
    return ret;
}

static void RemoveKey_Helper( const CString& dictName, const CString& type )
{
    ArxDictTool* pDictTool = ArxDictTool::GetDictTool( dictName );
    pDictTool->removeKey( type );
    delete pDictTool;
}

static void GetAllKeys_Helper( const CString& dictName, AcStringArray& keys )
{
    ArxDictTool* pDictTool = ArxDictTool::GetDictTool( dictName );
    pDictTool->getAllKeys( keys );
    delete pDictTool;
}

static bool AddField_Helper( const CString& dictName, const CString& type, const CString& field )
{
    ArxDictTool* pDictTool = ArxDictTool::GetDictTool( dictName );
    int index = pDictTool->addEntry( type, field );
    delete pDictTool;
    return ( index != INVALID_ENTRY );
}

static int RemoveField_Helper( const CString& dictName, const CString& type, const CString& field )
{
    ArxDictTool* pDictTool = ArxDictTool::GetDictTool( dictName );
    int index = pDictTool->removeEntry( type, field );
    delete pDictTool;
    return index;
}

static int CountFields_Helper( const CString& dictName, const CString& type )
{
    ArxDictTool* pDictTool = ArxDictTool::GetDictTool( dictName );
    int count = pDictTool->countEntries( type );
    delete pDictTool;
    return count;
}

static int FindField_Helper( const CString& dictName, const CString& type, const CString& field )
{
    ArxDictTool* pDictTool = ArxDictTool::GetDictTool( dictName );
    int index = pDictTool->findEntry( type, field );
    delete pDictTool;
    return index;
}

static void GetAllFields_Helper( const CString& dictName, const CString& type, AcStringArray& fields )
{
    ArxDictTool* pDictTool = ArxDictTool::GetDictTool( dictName );
    pDictTool->getAllEntries( type, fields );
    delete pDictTool;
}

bool FieldHelper::AddField( const CString& type, const CString& field )
{
    if( IsEmptyString( type ) || IsEmptyString( field ) ) return false;

    bool ret = AddField_Helper( PROPERTY_DATA_FIELD_DICT, type, field );

    return ret;
}

bool FieldHelper::RemoveField( const CString& type, const CString& field )
{
    if( IsEmptyString( type ) || IsEmptyString( field ) ) return false;

    int index = RemoveField_Helper( PROPERTY_DATA_FIELD_DICT, type, field );
    bool ret = ( INVALID_ENTRY != index );
    return ret;
}

// 实现有问题???
void FieldHelper::RemoveAllFields( const CString& type )
{
    AcStringArray fields;
    GetAllFields( type, fields );
    int len = fields.length();
    for( int i = 0; i < len; i++ )
    {
        RemoveField( type, fields[i].kACharPtr() );
    }
    RemoveKey_Helper( PROPERTY_DATA_FIELD_DICT, type );
}

int FieldHelper::CountFields( const CString& type )
{
    return CountFields_Helper( PROPERTY_DATA_FIELD_DICT, type );
}

int FieldHelper::FindField( const CString& type, const CString& field )
{
    return FindField_Helper( PROPERTY_DATA_FIELD_DICT, type, field );
}

void FieldHelper::GetAllFields( const CString& type, AcStringArray& fields )
{
    GetAllFields_Helper( PROPERTY_DATA_FIELD_DICT, type, fields );
}

#include <fstream>
// 需要包含<fstream>才能使用
#include "AcFStream.h"

static void SetFieldInfo( FieldInfo& info, const CString& fieldType, const CString& defaultValue, const CString& tole, const CString& editable, const CString& toolTips )
{
    bool enable = _ttoi( editable ) ? true : false;
    info.m_enable = enable;
    info.m_showInTooltip = true;
    info.m_descr = toolTips;
    if ( _T( "DT_STRING" ) == fieldType )
    {
        info.m_dt = FieldInfo::DT_STRING;
    }

    if ( _T( "DT_INT" ) == fieldType )
    {
        info.m_dt = FieldInfo::DT_INT;
        int pos = defaultValue.Find( _T( "-" ) );
        int minInt = _ttoi( defaultValue.Left( pos ) );
        int maxInt = _ttoi( defaultValue.Mid( pos + 1, defaultValue.GetLength() ) );
        //acutPrintf(_T("\n最小值:%d->最大值:%d"),minInt,maxInt);
        info.m_minValue2 = minInt;
        info.m_maxValue2 = maxInt;
    }

    if ( _T( "DT_NUMERIC" ) == fieldType )
    {
        info.m_dt = FieldInfo::DT_NUMERIC;
        int pos = defaultValue.Find( _T( "-" ) );
        double minDouble = _tstof( defaultValue.Left( pos ) );
        double maxDouble = _tstof( defaultValue.Mid( pos + 1, defaultValue.GetLength() ) );
        //acutPrintf(_T("\n最小值:%lf->最大值:%lf"),minDouble,maxDouble);
        info.m_minValue = minDouble;
        info.m_maxValue = maxDouble;
        info.m_tolrance = _ttoi( tole );
    }

    if ( _T( "DT_LIST" ) == fieldType )
    {
        info.m_dt = FieldInfo::DT_LIST;
        int pos = defaultValue.Find( _T( "-" ) );
        CString ltType = defaultValue.Left( pos );
        CString ltValue = defaultValue.Mid( pos + 1, defaultValue.GetLength() );
        if( _T( "LT_INT" ) == ltType )	info.m_lt = FieldInfo::LT_INT;
        if( _T( "LT_STRING" ) == ltType )	info.m_lt = FieldInfo::LT_STRING;
        if( _T( "LT_OBJECT" ) == ltType )	info.m_lt = FieldInfo::LT_OBJECT;
        info.m_varName = ltValue;
    }

    if ( _T( "DT_BOOL" ) == fieldType )
    {
        info.m_dt = FieldInfo::DT_BOOL;
    }

    if ( _T( "DT_DATE" ) == fieldType )
    {
        info.m_dt = FieldInfo::DT_DATE;
    }
}
// 初始化图元字段
// 从文件中读取数据，格式
// 图元类型	字段1
// 图元类型	字段2
// ...
void FieldHelper::InitDataFieldWithMoreInfo( const CString& fileName )
{
    acutPrintf( _T( "\n从路径: %s加载字段" ), fileName );

    AcIfstream inFile( fileName );
    if( !inFile ) return;

    while( !inFile.eof() )
    {
        ACHAR func[_MAX_PATH], getype[_MAX_PATH], field[_MAX_PATH], fieldType[_MAX_PATH], defaultValue[_MAX_PATH], tole[_MAX_PATH], editable[_MAX_PATH], toolTips[_MAX_PATH];
        inFile >> func >> getype >> field >> fieldType >> defaultValue >> tole >> editable >> toolTips;
        if( inFile.fail() ) break;

        FieldInfo fieldInfo;
        SetFieldInfo( fieldInfo, fieldType, defaultValue, tole, editable, toolTips );
        FuncFieldHelper::AddField( func, getype, field );
        FieldHelper::AddField( getype, field );

        // 新增的字段
        int index = FieldHelper::FindField( getype, field );
        if( index < 1 || !FieldInfoHelper::FindFieldInfo( getype, field ) )
        {
            FieldInfoHelper::AddFieldInfo( getype, field, fieldInfo );
        }
        else
        {
            // 更新已有的字段信息
            FieldInfoHelper::RemoveFieldInfo( getype, field );
            FieldInfoHelper::AddFieldInfo( getype, field, fieldInfo );
        }
    }
    inFile.close();
}

void FieldHelper::InitDataField( const CString& fileName )
{
    acutPrintf( _T( "\n加载数据文件" ), fileName );

    AcIfstream inFile( fileName );
    if( !inFile ) return;

    while( !inFile.eof() )
    {
        ACHAR getype[_MAX_PATH], field[_MAX_PATH];
        inFile >> getype >> field;
        if( inFile.fail() ) break;

        FieldHelper::AddField( getype, field );
    }
    inFile.close();
    //acutPrintf( _T( "\n从路径: %s加载字段结束-->" ), fileName );
}

bool FuncFieldHelper::RemoveFunction( const CString& f )
{
    if( IsEmptyString( f ) ) return false;

    ArxDictHelper::RemoveKey( FUNC_FIELD_DICT, f );
    return true;
}

bool FuncFieldHelper::RemoveType( const CString& f, const CString& type )
{
    if( IsEmptyString( f ) || IsEmptyString( type ) ) return false;

    AcStringArray allEntries;
    ArxDictHelper::GetAllEntries( FUNC_FIELD_DICT, f, allEntries );

    AcStringArray entries;
    for( int i = 0; i < allEntries.length(); i++ )
    {
        int pos = allEntries[i].find( SEPARATOR );
        if( pos == -1 ) continue;

        if( allEntries[i].substr( 0, pos ).compareNoCase( type ) == 0 )
        {
            entries.append( allEntries[i] );
        }
    }

    for( int i = 0; i < entries.length(); i++ )
    {
        ArxDictHelper::RemoveEntry( FUNC_FIELD_DICT, f, entries[i].kACharPtr() );
    }

    return true;
}

bool FuncFieldHelper::GetFunctions( AcStringArray& funcs )
{
    ArxDictHelper::GetAllKeys( FUNC_FIELD_DICT, funcs );
    return true;
}

bool FuncFieldHelper::GetTypes( const CString& f, AcStringArray& types )
{
    if( IsEmptyString( f ) ) return false;

    AcStringArray entries;
    if( !ArxDictHelper::GetAllEntries( FUNC_FIELD_DICT, f, entries ) ) return false;

    typedef std::set<AcString> AcStringSet;
    AcStringSet ss;

    for( int i = 0; i < entries.length(); i++ )
    {
        int pos = entries[i].find( SEPARATOR );
        if( pos == -1 ) continue;

        AcString type = entries[i].substr( 0, pos );
        if( ss.find( type ) == ss.end() )
        {
            types.append( type );
            ss.insert( type );
        }
    }
    return true;
}

bool FuncFieldHelper::GetFields( const CString& f, const CString& type, AcStringArray& fields )
{
    if( IsEmptyString( f ) || IsEmptyString( type ) ) return false;

    AcStringArray entries;
    if( !ArxDictHelper::GetAllEntries( FUNC_FIELD_DICT, f, entries ) ) return false;

    for( int i = 0; i < entries.length(); i++ )
    {
        int pos = entries[i].find( SEPARATOR );
        if( pos == -1 ) continue;

        if( entries[i].substr( 0, pos ).compareNoCase( type ) == 0 )
        {
            fields.append( entries[i].substr( pos + 1, -1 ) );
        }
    }
    return true;
}

bool FuncFieldHelper::AddField( const CString& f, const CString& type, const CString& field )
{
    if( IsEmptyString( f ) || IsEmptyString( type ) || IsEmptyString( field ) ) return false;

    CString entry;
    entry.Format( _T( "%s%s%s" ), type, SEPARATOR, field );
    //acutPrintf(_T("\n添加字段:%s"), entry);
    return ArxDictHelper::AddEntry( FUNC_FIELD_DICT, f, entry );
}

bool FuncFieldHelper::RemoveField( const CString& f, const CString& type, const CString& field )
{
    if( IsEmptyString( f ) || IsEmptyString( type ) || IsEmptyString( field ) ) return false;

    CString entry;
    entry.Format( _T( "%s%s%s" ), type, SEPARATOR, field );
    return ArxDictHelper::RemoveEntry( FUNC_FIELD_DICT, f, entry );
}
