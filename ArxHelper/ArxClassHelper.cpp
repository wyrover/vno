#include "StdAfx.h"
#include "ArxClassHelper.h"

// ���ҴӸ�����������ͼԪ
void ArxClassHelper::GetArxClassTypes( const CString& root, AcStringArray& types, bool findAbstractType )
{
    // ��������Ͳ����ڣ�Ĭ��ΪAcDbObject
    AcRxClass* pParentClass = AcRxClass::cast( acrxClassDictionary->at( root ) );
    if( pParentClass == 0 ) pParentClass = AcDbObject::desc();

    AcRxDictionaryIterator* iter = acrxClassDictionary->newIterator();
    if( iter == 0 ) return;

    for( ; !iter->done(); iter->next() )
    {
        AcRxClass* pClass;
        if( ( pClass = AcRxClass::cast( iter->object() ) ) != NULL )
        {
            if( pClass->isDerivedFrom( pParentClass ) )
            {
                const ACHAR* text = pClass->name();
                if( text == NULL ) continue;

                if( !findAbstractType && ( pClass->dxfName() == NULL ) || ( pClass->appName() == NULL ) ) continue;

                //acutPrintf(_T("appName:%s\ndxfName:%s\nname:%s\n"), pClass->appName(), pClass->dxfName(), pClass->name());
                types.append( text );
            }
        }
    }
    delete iter;
}

bool ArxClassHelper::IsValidClass( const CString& type )
{
    AcRxClass* pClass = AcRxClass::cast( acrxClassDictionary->at( type ) );
    return ( pClass != 0 );
}

bool ArxClassHelper::IsAbstractClass( const CString& type )
{
    AcRxClass* pClass = AcRxClass::cast( acrxClassDictionary->at( type ) );
    if( pClass == 0 ) return false; // ���Ͳ�����

    // �����࣬ʹ��ACRX_NO_CONS_DEFINE_MEMBERS�궨��
    return ( ( pClass->dxfName() == NULL ) || ( pClass->appName() == NULL ) );
}

bool ArxClassHelper::IsDerivedFrom( const CString& type, const CString& parentType )
{
    AcRxClass* pClass1 = AcRxClass::cast( acrxClassDictionary->at( type ) );
    if( pClass1 == 0 ) return false; // ���Ͳ�����

    AcRxClass* pClass2 = AcRxClass::cast( acrxClassDictionary->at( parentType ) );
    if( pClass2 == 0 ) return false; // ���Ͳ�����

    return pClass1->isDerivedFrom( pClass2 );
}

// ��ȡͼԪ��dxf����
// ��������һ����dxf����Ҳ������Ψһ��
bool ArxClassHelper::GetDxfName( const CString& type, CString& dxfName )
{
    AcRxClass* pClass = AcRxClass::cast( acrxClassDictionary->at( type ) );
    if( pClass == 0 ) return false;

    dxfName = pClass->dxfName();
    return true;
}

void ArxClassHelper::GetClassHierarchy( const CString& type, AcStringArray& types, bool findAbstractType )
{
    AcRxClass* pClass = AcRxClass::cast( acrxClassDictionary->at( type ) );
    if( pClass == 0 ) return;

    while( pClass != AcDbEntity::desc() )
    {
        // �ų���������
        if( !findAbstractType && ( ( pClass->dxfName() == NULL ) || ( pClass->appName() == NULL ) ) )
        {
            pClass = pClass->myParent();
            continue;
        }

        types.append( pClass->name() );
        pClass = pClass->myParent();
    }
    types.reverse();
}

bool ArxClassHelper::GetChildClass( const CString& type, AcStringArray& types )
{
    AcRxClass* pParentClass = AcRxClass::cast( acrxClassDictionary->at( type ) );
    if( pParentClass == 0 ) return false; // ���Ͳ�����

    AcRxDictionaryIterator* iter = acrxClassDictionary->newIterator();
    if( iter == 0 ) return false;

    AcRxClass* pClass;
    for( ; !iter->done(); iter->next() )
    {
        if( ( pClass = AcRxClass::cast( iter->object() ) ) != NULL )
        {
            const ACHAR* text = pClass->name();
            if( ( text != NULL ) && ( pClass->myParent() == pParentClass ) )
            {
                types.append( text );
            }
        }
    }
    delete iter;
    return true;
}

bool ArxClassHelper::GetTopParentClass( const CString& type, CString& parentType )
{
    AcStringArray types;
    GetClassHierarchy( type, types, false );
    if( types.isEmpty() ) return false;	   // type������ǳ�����

    parentType = types.first().kACharPtr();
    return true;
}

bool ArxClassHelper::GetAllTopParentClass( const CString& root, AcStringArray& types )
{
    AcStringArray allGETypes;
    ArxClassHelper::GetArxClassTypes( root, allGETypes, false );
    if( allGETypes.isEmpty() ) return false;

    int len = allGETypes.length();
    for( int i = 0; i < len; i++ )
    {
        CString parentType;
        if( !ArxClassHelper::GetTopParentClass( allGETypes[i].kACharPtr(), parentType ) ) continue;
        if( allGETypes[i].compareNoCase( parentType ) != 0 ) continue;
        if( !types.contains( parentType ) )
        {
            types.append( parentType );
        }
    }
    return true;
}

AcDbObject* ArxClassHelper::CreateObjectByType( const CString& type )
{
    AcRxClass* pClass = AcRxClass::cast( acrxClassDictionary->at( type ) );
    if( pClass == 0 ) return 0; // ���Ͳ�����

    return AcDbObject::cast( pClass->create() );
}