#pragma once

#include "dlimexp.h"

class ARXHELPER_API ArxGroupHelper
{
public:
    static AcDbObjectId CreateGroup( const CString& groupName, const AcDbObjectIdArray& objIds );
    static bool ConvertToAnonymousGroup( const AcDbObjectId& groupId );
    static AcDbObjectId GetGroup( const CString& groupName );
    static bool GetGroupName( const AcDbObjectId& groupId, CString& groupName );
    static bool ClearGroup( const CString& groupName );
    static bool ClearGroup( const AcDbObjectId& groupId );
    static bool RemoveGroup( const CString& groupName );
    static bool RemoveGroup( const AcDbObjectId& groupId );
    static void SetGroupName( const AcDbObjectId& groupId, const CString& groupName );
    static void GetObjectIds( const AcDbObjectId& groupId, AcDbObjectIdArray& objIds );
    static void GetObjectIds( const CString& groupName, AcDbObjectIdArray& objIds );
};
