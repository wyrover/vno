#pragma once

class ArxXRecordManager
{
public:
    ArxXRecordManager( AcDbXrecord* pXrec );
    ~ArxXRecordManager();

    int addEntry( const CString& entry );
    int removeEntry( const CString& entry );
    bool modifyEntry( int index, const CString& newEntry );
    bool getEntry( int index, CString& entry );
    int findEntry( const CString& entry );
    int countEntries();
    void getAllEntries( AcStringArray& entries );

private:
    AcDbXrecord* m_pXrec;
    resbuf* m_pHead;
};