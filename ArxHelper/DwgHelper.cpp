#include "stdafx.h"

// ѡ��dwgͼ���ļ�
bool SelectDwg( const CString& msg, CString& dwgFilePath )
{
    struct resbuf* rb = acutNewRb( RTSTR );
    bool ret = ( RTNORM == acedGetFileD( msg, NULL, _T( "dwg" ), 0, rb ) );
    if( ret )
    {
        dwgFilePath = rb->resval.rstring;
    }
    acutRelRb( rb ); // ����Ҫ�ͷ�ռ�õ��ڴ�
    return ret;
}

// ��dwg�ļ��е�"���"ͼ���ȡ���е�ֱ��ʼĩ����
bool ReadAllLinesFromDwg( const CString& dwgFilePath, const CString& layerName, AcGePoint3dArray& sptArray, AcGePoint3dArray& eptArray )
{
    AcDbDatabase db( false );
    if( Acad::eOk != db.readDwgFile( dwgFilePath ) ) return false;

    // �������ΪBlk�Ŀ���¼
    AcDbBlockTable* pBlkTbl;
    if ( Acad::eOk != db.getBlockTable( pBlkTbl, AcDb::kForRead ) )
    {
        acedAlert( _T( "��ÿ��ʧ��!" ) );
        return false;
    }
    AcDbBlockTableRecord* pBlkTblRcd;
    Acad::ErrorStatus es = pBlkTbl->getAt( ACDB_MODEL_SPACE, pBlkTblRcd, AcDb::kForRead );
    pBlkTbl->close();
    if ( Acad::eOk != es )
    {
        acedAlert( _T( "��ģ�Ϳռ����¼ʧ��!" ) );
        return false;
    }

    // ��������¼������
    AcDbBlockTableRecordIterator* pItr;
    if ( Acad::eOk != pBlkTblRcd->newIterator( pItr ) )
    {
        acedAlert( _T( "����������ʧ��!" ) );
        pBlkTblRcd->close();
        return false;
    }

    for ( pItr->start(); !pItr->done(); pItr->step() )
    {
        AcDbEntity* pEnt;
        if( Acad::eOk != pItr->getEntity( pEnt, AcDb::kForRead ) ) continue;

        if( layerName.CompareNoCase( pEnt->layer() ) == 0 ) // ֻѡ��ָ��ͼ��
        {
            AcDbLine* pLine = AcDbLine::cast( pEnt );   // ֻѡ��ֱ��
            if( pLine != 0 )
            {
                // ��ȡֱ�ߵ�ʼĩ������
                AcGePoint3d spt, ept;
                pLine->getStartPoint( spt );
                pLine->getEndPoint( ept );

                // !!![����]!!!
                //		Ŀǰ������3ά�����ǿ����������z=0
                spt.z = 0;
                ept.z = 0;

                if( spt != ept ) // �ų�ʼĩ����ͬ��ֱ��
                {
                    sptArray.append( spt );
                    eptArray.append( ept );
                }
            }
        }
        pEnt->close();
    }
    delete pItr;
    pBlkTblRcd->close();

    //acutPrintf(_T("\n�������:%d"), sptArray.length());
    return true;
}