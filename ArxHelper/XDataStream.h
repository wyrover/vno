#pragma once

#include "dlimexp.h"

class ArxDbgXdataList;
class ArxDbgXdataListIterator;

class ARXHELPER_API DrawParamReader
{
public:
    DrawParamReader( ArxDbgXdataListIterator* pXDataList );

    void readInt( int& value );
    void readLong( long& value );
    void readDouble( double& value );
    void readString( CString& value );
    void readBoolean( bool& value );
    void readPoint( AcGePoint3d& value );

private:
    ArxDbgXdataListIterator* m_pXDataList;
};

class ARXHELPER_API DrawParamWriter
{
public:
    DrawParamWriter( ArxDbgXdataList* pXDataList );

    void writeInt( int value );
    void writeLong( long value );
    void writeDouble( double value );
    void writeString( const CString& value );
    void writeBoolean( bool value );
    void writePoint( const AcGePoint3d& value );

private:
    ArxDbgXdataList* m_pXDataList;
};
