#include "StdAfx.h"
#include "ArxXRecordManager.h"
#include "ArxDictTool.h"

ArxXRecordManager::ArxXRecordManager( AcDbXrecord* pXrec ) : m_pXrec( pXrec ), m_pHead( 0 )
{
    struct resbuf* pRbList = 0;
    pXrec->rbChain( &pRbList );
    m_pHead = pRbList;
}

ArxXRecordManager::~ArxXRecordManager()
{
    m_pXrec->setFromRbChain( *m_pHead );
    acutRelRb( m_pHead );
    m_pXrec->close();

    m_pHead = 0;
    m_pXrec = 0;
}

int ArxXRecordManager::addEntry( const CString& entry )
{
    if( m_pHead == 0 )
    {
        m_pHead = acutBuildList( AcDb::kDxfText, entry, 0 );
        return 1; // ��1��
    }

    // ����Ƿ�����ظ��ֶ�
    // 1������һ��node
    if( entry.CompareNoCase( m_pHead->resval.rstring ) == 0 ) return INVALID_ENTRY; // ������ͬ���ֶ�����

    // 2�����������node
    bool isFieldExist = false;
    resbuf* pTemp;
    int index = 1;
    for ( pTemp = m_pHead; pTemp != NULL; pTemp = pTemp->rbnext )
    {
        if( entry.CompareNoCase( pTemp->resval.rstring ) == 0 )
        {
            // ������ͬ���ֶ�����
            isFieldExist = true;
            break;
        }
        if( pTemp->rbnext == NULL ) break;
        index++;
    }

    if( isFieldExist ) return INVALID_ENTRY; // �����ظ�������0��ʾ��Ч��λ��

    // �ѱ�����resbuf list��ĩβ
    pTemp->rbnext = acutBuildList( AcDb::kDxfText, entry, 0 );

    return index + 1;
}

int ArxXRecordManager::removeEntry( const CString& entry )
{
    if( m_pHead == 0 ) return INVALID_ENTRY; // resbuf listΪ�գ���Ч!

    // 1�������ֶε�λ��
    resbuf* pTemp, *pPos = 0;
    int index = 1;
    for ( pTemp = m_pHead; pTemp != NULL; pTemp = pTemp->rbnext )
    {
        if( entry.CompareNoCase( pTemp->resval.rstring ) == 0 )
        {
            // ������ͬ���ֶ�����
            pPos = pTemp;
            break;
        }
        index++;
    }

    // û�в��ҵ��ֶ�
    if( pPos == 0 ) return INVALID_ENTRY;

    if( pPos == m_pHead )
    {
        // ��һ��node����Ҫ���ҵ��ֶ�λ��
        m_pHead = m_pHead->rbnext;
    }
    else
    {
        // 2�������ֶε�ǰһ��λ��
        resbuf* pPrev;
        for ( pTemp = m_pHead; pTemp != NULL; pTemp = pTemp->rbnext )
        {
            if( pTemp->rbnext == pPos )
            {
                pPrev = pTemp;
                break;
            }
        }
        pPrev->rbnext = pPos->rbnext;
    }

    pPos->rbnext = 0; // ע�⣬Ҫ��rbnext��Ϊ0������acutRelRb��ɾ���������������
    acutRelRb( pPos ); // �ú���ɾ��һ��resbuf list����ֻ��һ��node

    return index;
}

int ArxXRecordManager::findEntry( const CString& entry )
{
    if( m_pHead == 0 ) return INVALID_ENTRY; // resbuf listΪ�գ�����0��ʾ��Ч!

    // �����ֶε�λ��
    int index = 1;
    resbuf* pTemp = 0;
    for ( pTemp = m_pHead; pTemp != NULL; pTemp = pTemp->rbnext )
    {
        if( entry.CompareNoCase( pTemp->resval.rstring ) == 0 ) break;
        index++;
    }
    return ( ( pTemp == 0 ) ? INVALID_ENTRY : index );
}

int ArxXRecordManager::countEntries()
{
    if( m_pHead == 0 ) return 0;

    // �����ֶε�λ��
    int count = 0;
    for ( resbuf* pTemp = m_pHead; pTemp != NULL; pTemp = pTemp->rbnext )
    {
        count++;
    }
    return count;
}

void ArxXRecordManager::getAllEntries( AcStringArray& entries )
{
    if( m_pHead == 0 ) return;

    // �����ֶε�λ��
    for ( resbuf* pTemp = m_pHead; pTemp != NULL; pTemp = pTemp->rbnext )
    {
        entries.append( pTemp->resval.rstring );
    }
}

bool ArxXRecordManager::modifyEntry( int index, const CString& newEntry )
{
    if( m_pHead == 0 ) return false;

    // ���������е����ݱ�����Ψһ��
    if( INVALID_ENTRY != findEntry( newEntry ) ) return false;

    int count = 1;
    resbuf* pTemp = 0;
    for ( pTemp = m_pHead; pTemp != NULL; pTemp = pTemp->rbnext )
    {
        if( count == index )
        {
            acutNewString( newEntry, pTemp->resval.rstring );
            break;
        }
        count++;
    }
    return ( pTemp != 0 );
}

bool ArxXRecordManager::getEntry( int index, CString& entry )
{
    if( m_pHead == 0 ) return false;

    int count = 1;
    resbuf* pTemp = 0;
    for ( pTemp = m_pHead; pTemp != NULL; pTemp = pTemp->rbnext )
    {
        if( count == index )
        {
            entry = pTemp->resval.rstring;
            break;
        }
        count++;
    }
    return ( pTemp != 0 );
}
