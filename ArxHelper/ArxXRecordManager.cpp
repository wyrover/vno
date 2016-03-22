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
        return 1; // 第1个
    }

    // 检查是否存在重复字段
    // 1、检查第一个node
    if( entry.CompareNoCase( m_pHead->resval.rstring ) == 0 ) return INVALID_ENTRY; // 存在相同的字段名称

    // 2、检查其它的node
    bool isFieldExist = false;
    resbuf* pTemp;
    int index = 1;
    for ( pTemp = m_pHead; pTemp != NULL; pTemp = pTemp->rbnext )
    {
        if( entry.CompareNoCase( pTemp->resval.rstring ) == 0 )
        {
            // 存在相同的字段名称
            isFieldExist = true;
            break;
        }
        if( pTemp->rbnext == NULL ) break;
        index++;
    }

    if( isFieldExist ) return INVALID_ENTRY; // 存在重复，返回0表示无效的位置

    // 已遍历到resbuf list的末尾
    pTemp->rbnext = acutBuildList( AcDb::kDxfText, entry, 0 );

    return index + 1;
}

int ArxXRecordManager::removeEntry( const CString& entry )
{
    if( m_pHead == 0 ) return INVALID_ENTRY; // resbuf list为空，无效!

    // 1、查找字段的位置
    resbuf* pTemp, *pPos = 0;
    int index = 1;
    for ( pTemp = m_pHead; pTemp != NULL; pTemp = pTemp->rbnext )
    {
        if( entry.CompareNoCase( pTemp->resval.rstring ) == 0 )
        {
            // 存在相同的字段名称
            pPos = pTemp;
            break;
        }
        index++;
    }

    // 没有查找到字段
    if( pPos == 0 ) return INVALID_ENTRY;

    if( pPos == m_pHead )
    {
        // 第一个node即是要查找的字段位置
        m_pHead = m_pHead->rbnext;
    }
    else
    {
        // 2、查找字段的前一个位置
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

    pPos->rbnext = 0; // 注意，要将rbnext置为0，否则acutRelRb会删除后面的链表数据
    acutRelRb( pPos ); // 该函数删除一个resbuf list，不只是一个node

    return index;
}

int ArxXRecordManager::findEntry( const CString& entry )
{
    if( m_pHead == 0 ) return INVALID_ENTRY; // resbuf list为空，返回0表示无效!

    // 查找字段的位置
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

    // 查找字段的位置
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

    // 查找字段的位置
    for ( resbuf* pTemp = m_pHead; pTemp != NULL; pTemp = pTemp->rbnext )
    {
        entries.append( pTemp->resval.rstring );
    }
}

bool ArxXRecordManager::modifyEntry( int index, const CString& newEntry )
{
    if( m_pHead == 0 ) return false;

    // 链表中所有的数据必须是唯一的
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
