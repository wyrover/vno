#include "StdAfx.h"
#include "ArxLayerHelper.h"

const static int kNameLength = 260;

////////////////////////////////////////////////////////////////////
//////////////////////����ժ¼����--ͼ�����/////////////////////
////////////////////////////////////////////////////////////////////

static bool getAllLayers( AcDbObjectIdArray& arrLayers )
{

    AcDbLayerTable* layerTable ;
    Acad::ErrorStatus es ;

    //open the layertable in the current drawing
    if ( Acad::eOk !=  acdbHostApplicationServices()->workingDatabase()->getLayerTable( layerTable, AcDb::kForRead ) )
    {
        acutPrintf ( _T( "\nCouldn''t get the layer table" ) ) ;
        return false;
    }

    //create a new iterator
    AcDbLayerTableIterator* pLayerTableIterator ;
    if ( Acad::eOk != layerTable->newIterator ( pLayerTableIterator ) )
    {
        acutPrintf ( _T( "\nCouldn''t get a new layer table iterator" ) ) ;
        layerTable->close () ;
        return false ;
    }
    layerTable->close () ;
    AcDbObjectId layerId ;

    //iterate through the all layers and collect their ids
    for ( ; !pLayerTableIterator->done () ; pLayerTableIterator->step() )
    {
        if ( Acad::eOk != pLayerTableIterator->getRecordId( layerId ) )
        {
            acutPrintf( _T( "\nCannot get layers" ) );
            continue;
        }
        else
        {
            arrLayers.append( layerId );
        }
    }
    delete pLayerTableIterator;

    return true;

}

// Argument : AcDbDatabase* pDb
static Acad::ErrorStatus setCurLayer( const TCHAR* lpLayerName, AcDbDatabase* pDb )
{
    AcDbDatabase* pCurDb = pDb;
    if ( pCurDb == NULL )
        pCurDb = acdbHostApplicationServices() -> workingDatabase();
    // ʹ����layertable��¼ָ�룬�ȽϷ���
    AcDbLayerTableRecordPointer spRecord( lpLayerName, pCurDb, AcDb::kForRead );
    Acad::ErrorStatus es = spRecord.openStatus();
    if ( es == Acad::eOk )
    {
        es = pCurDb -> setClayer( spRecord -> objectId() );
    }
    return es;
}


static AcDbObjectId createNewLayer( const CString& LayerName )
{
    // ��õ�ǰͼ�����ݿ�ķ��ű�
    AcDbLayerTable* pLayerTable;
    acdbHostApplicationServices()->workingDatabase()->getSymbolTable( pLayerTable, AcDb::kForWrite );
    // �����µ�ͼ����¼
    AcDbLayerTableRecord* pLayerTableRecord = new AcDbLayerTableRecord;
    pLayerTableRecord->setName( LayerName ); // ����ͼ����
    //pLayerTableRecord->setColor(LayerColor); // ����ͼ����ɫ
    AcDbObjectId layerId;
    pLayerTable->add( layerId, pLayerTableRecord );
    // �ر�ͼ����ͼ����¼
    pLayerTable->close();
    pLayerTableRecord->close();
    return layerId;
}

static AcDbObjectId addLayer( const TCHAR* LayerName,
                              const Adesk::Int16 LayerColor,
                              //const char* Linetype,
                              AcDbDatabase* pDb )
{
    if( pDb == NULL )
        pDb = acdbHostApplicationServices()->workingDatabase();

    // װ������
    /*pDb->loadLineTypeFile(Linetype,"acadiso.lin");
    AcDbObjectId LineTypeId=AddLineType(pDb,Linetype);*/

    AcDbLayerTable* pLayerTable = NULL;
    AcDbLayerTableRecord* pLayerRecord = NULL;
    AcDbObjectId LayerId = AcDbObjectId::kNull;
    if( Acad::eOk != pDb->getLayerTable( pLayerTable, AcDb::kForRead ) ) return false;

    if( pLayerTable->has( LayerName ) )
    {
        pLayerTable->getAt( LayerName, LayerId );
    }
    else
    {
        pLayerRecord = new AcDbLayerTableRecord;
        AcCmColor color;
        color.setColorIndex( LayerColor );
        pLayerRecord->setColor( color );
        //pLayerRecord->setLinetypeObjectId(LineTypeId);
        pLayerRecord->setName( LayerName );
        pLayerTable->add( LayerId, pLayerRecord );
        pLayerRecord->close();
    }
    pLayerTable->close();
    return LayerId;
}

static bool frozenLayer( const CString& layerName, bool isFrozen )
{
    AcDbDatabase* pDb = acdbHostApplicationServices()->workingDatabase();
    if( pDb == 0 ) return false;

    AcDbLayerTable* pLayerTable = NULL;
    if( Acad::eOk != pDb->getLayerTable( pLayerTable, AcDb::kForRead ) ) return false;

    AcDbLayerTableRecord* pLayerRecord = NULL;
    if( Acad::eOk != pLayerTable->getAt( layerName, pLayerRecord, AcDb::kForWrite ) )
    {
        pLayerTable->close();
        return false;
    }
    pLayerTable->close();

    pLayerRecord->setIsFrozen( isFrozen ); // ����/�ⶳ
    pLayerRecord->close();

    return true;
}

static bool hiddenLayer( const CString& layerName, bool isOn )
{
    AcDbDatabase* pDb = acdbHostApplicationServices()->workingDatabase();
    if( pDb == 0 ) return false;

    AcDbLayerTable* pLayerTable = NULL;
    if( Acad::eOk != pDb->getLayerTable( pLayerTable, AcDb::kForRead ) ) return false;

    AcDbLayerTableRecord* pLayerRecord = NULL;
    if( Acad::eOk != pLayerTable->getAt( layerName, pLayerRecord, AcDb::kForWrite ) )
    {
        pLayerTable->close();
        return false;
    }
    pLayerTable->close();

    pLayerRecord->setIsHidden( isOn ); // ����/��ʾ
    pLayerRecord->close();

    return true;
}

static bool lockLayer( const CString& layerName, bool locked )
{
    AcDbDatabase* pDb = acdbHostApplicationServices()->workingDatabase();
    if( pDb == 0 ) return false;

    AcDbLayerTable* pLayerTable = NULL;
    if( Acad::eOk != pDb->getLayerTable( pLayerTable, AcDb::kForRead ) ) return false;

    AcDbLayerTableRecord* pLayerRecord = NULL;
    if( Acad::eOk != pLayerTable->getAt( layerName, pLayerRecord, AcDb::kForWrite ) )
    {
        pLayerTable->close();
        return false;
    }
    pLayerTable->close();

    pLayerRecord->setIsLocked( locked ); // ����/������
    pLayerRecord->close();

    return true;
}

static bool offLayer( const CString& layerName, bool off )
{
    AcDbDatabase* pDb = acdbHostApplicationServices()->workingDatabase();
    if( pDb == 0 ) return false;

    AcDbLayerTable* pLayerTable = NULL;
    if( Acad::eOk != pDb->getLayerTable( pLayerTable, AcDb::kForRead ) ) return false;

    AcDbLayerTableRecord* pLayerRecord = NULL;
    if( Acad::eOk != pLayerTable->getAt( layerName, pLayerRecord, AcDb::kForWrite ) )
    {
        pLayerTable->close();
        return false;
    }
    pLayerTable->close();

    pLayerRecord->setIsOff( off ); // �ر�/��
    pLayerRecord->close();

    return true;
}

static void renameLayerName( const CString& layerName, const CString& newLayerName )
{
    AcDbDatabase* pDb = acdbHostApplicationServices()->workingDatabase();
    if( pDb == 0 ) return /*false*/;

    AcDbLayerTable* pLayerTable = NULL;
    if( Acad::eOk != pDb->getLayerTable( pLayerTable, AcDb::kForRead ) ) return /*false*/;

    AcDbLayerTableRecord* pLayerRecord = NULL;
    if( Acad::eOk != pLayerTable->getAt( layerName, pLayerRecord, AcDb::kForWrite ) )
    {
        pLayerTable->close();
        return /*false*/;
    }
    pLayerTable->close();

    pLayerRecord->setName( newLayerName ); // �޸�����
    pLayerRecord->close();

    //return true;
}

void ArxLayerHelper::SetCurrentLayer( const CString& layerName )
{
    // ͼ�㲻���ڣ���ʲôҲ��������ǰͼ�㱣�ֲ���
    //if(!IsLayerExist(layerName)) return;

    setCurLayer( layerName, NULL );
}

CString ArxLayerHelper::GetCurrentLayerName()
{
    AcDbObjectId layerId = acdbHostApplicationServices()->workingDatabase()->clayer();

    AcDbObject* pLayer;

    // ��ʧ�ܣ���ʲôҲ���������ؿ��ַ���
    if ( Acad::eOk != acdbOpenObject( pLayer, layerId, AcDb::kForRead ) ) return _T( "" );

    const TCHAR* name;
    AcDbLayerTableRecord::cast( pLayer )->getName( name );
    pLayer->close();

    return name;
}

void ArxLayerHelper::AddLayer( const CString& layerName )
{
    // �����ҵ����룬��Ӧ�ô���һЩ��������������
    // �ַ���Ϊ�մ�""���ַ����а����Ƿ��ַ�'\t','\n',' '
    // Ŀǰ��ʱ�������������

    // ͼ���Ѿ�����
    if( IsLayerExist( layerName ) ) return;

    createNewLayer( layerName );
}

void ArxLayerHelper::RemoveLayer( const CString& layerName )
{
    // ͼ�㲻����
    if( !IsLayerExist( layerName ) ) return;

    // ͼ��Ϊ��ǰͼ�㣬����ɾ��
    if( IsCurrentLayer( layerName ) ) return;

    AcDbLayerTable* layerTable ;

    // �򿪲��
    if ( Acad::eOk !=  acdbHostApplicationServices()->workingDatabase()->getLayerTable( layerTable, AcDb::kForWrite ) )
        return;

    // �жϲ��Ƿ����
    AcDbLayerTableRecord* pLayerTblRecord;
    // �򿪲���¼ʧ�ܣ���ͼ��layerName��
    if( layerTable->getAt( layerName, pLayerTblRecord, AcDb::kForWrite ) != Acad::eOk )
    {
        layerTable->close();
        return;
    }

    // ɾ��ͼ��
    pLayerTblRecord->erase( true );
    pLayerTblRecord->close();

    // �رղ��
    layerTable->close();
}

bool ArxLayerHelper::IsLayerExist( const CString& layerName )
{
    AcDbLayerTable* layerTable ;

    // �򿪲��
    if ( Acad::eOk !=  acdbHostApplicationServices()->workingDatabase()->getLayerTable( layerTable, AcDb::kForRead ) )
        return false;

    // �жϲ��Ƿ����
    bool isExist = layerTable->has( layerName );

    // �رղ��
    layerTable->close();

    return isExist;
}


bool ArxLayerHelper::IsCurrentLayer( const CString& layerName )
{
    AcDbObjectId layerId = acdbHostApplicationServices()->workingDatabase()->clayer();

    AcDbObject* pLayer;

    // ��ʧ�ܣ���ʲôҲ����������
    if ( Acad::eOk != acdbOpenObject( pLayer, layerId, AcDb::kForRead ) ) return false;

    const TCHAR* name;
    AcDbLayerTableRecord::cast( pLayer )->getName( name );
    // �ر�ͼ�����
    pLayer->close();

    return ( layerName == name ); // Ч�ʽϲ�
}

bool ArxLayerHelper::FrozenLayer( const CString& layerName, bool isFrozen )
{
    // ͼ�㲻����
    if( !IsLayerExist( layerName ) ) return false;

    // ��ǰͼ�㣬��������
    if( IsCurrentLayer( layerName ) ) return false;

    return frozenLayer( layerName, isFrozen );
}

bool ArxLayerHelper::HideLayer( const CString& layerName, bool isOn )
{
    // ͼ�㲻����
    if( !IsLayerExist( layerName ) ) return false;

    // ��ǰͼ�㣬����������
    if( IsCurrentLayer( layerName ) ) return false;

    return hiddenLayer( layerName, isOn );
}

bool ArxLayerHelper::LockLayer( const CString& layerName, bool locked )
{
    // ͼ�㲻����
    if( !IsLayerExist( layerName ) ) return false;

    // ��ǰͼ�㣬����������
    if( IsCurrentLayer( layerName ) ) return false;

    return lockLayer( layerName, locked );
}

bool ArxLayerHelper::OffLayer( const CString& layerName, bool off )
{
    // ͼ�㲻����
    if( !IsLayerExist( layerName ) ) return false;

    // ��ǰͼ�㣬����������
    if( IsCurrentLayer( layerName ) ) return false;

    return offLayer( layerName, off );
}

void ArxLayerHelper::RenameLayer( const CString& layerName, const CString& newLayerName )
{
    // ͼ������Ϊ�ղ�����
    if( newLayerName.GetLength() == 0 ) return /*false*/;

    // ͼ�㲻����
    if( !IsLayerExist( layerName ) ) return /*false*/;

    // ��ǰͼ�㣬����������
    //if(IsCurrentLayer(layerName)) return false;

    renameLayerName( layerName, newLayerName );
}

/*
//put the Ids of all the entities on a certain layer in the array, "ents"
bool LayerHelper::GetAllEntitiesOnLayer(const CString& layerName, AcDbObjectIdArray &ents)
{
	Acad::ErrorStatus es;
	//construct a resbuffer to select all the entities on a layer
	struct resbuf eb1;
	TCHAR sbuf1[kNameLength]; // Buffers to hold string
	eb1.restype = 8;  // select based on layer name
	_tcscpy(sbuf1, layerName);
	eb1.resval.rstring = sbuf1;
	eb1.rbnext = NULL; // No other properties

	ads_name ss;
	if (RTNORM != acedSSGet(_T("X"), NULL, NULL, &eb1, ss ) )
		return false;
	long nEnts;

	//Iterate through the selection set, get all the entities' object Ids and
	//append them to the array, "ents"
	acedSSLength( ss, &nEnts );
	ents.setPhysicalLength(nEnts);
	for(int i = 0; i < nEnts; i++ ) {
		ads_name eName;
		acedSSName(ss, i, eName);
		AcDbObjectId id;
		acdbGetObjectId(id, eName);
		ents.append(id);
	}
	acedSSFree( ss );

	return true;
}
*/

bool ArxLayerHelper::GetAllEntitiesOnLayer( const CString& layerName, AcDbObjectIdArray& ents )
{
    AcDbDatabase* pDB = acdbHostApplicationServices()->workingDatabase();
    AcDbBlockTable* pBlkTbl;
    pDB->getSymbolTable( pBlkTbl, AcDb::kForRead );

    AcDbBlockTableRecord* pBlkTblRcd;
    pBlkTbl->getAt( ACDB_MODEL_SPACE, pBlkTblRcd, AcDb::kForRead );
    pBlkTbl->close();

    AcDbBlockTableRecordIterator* pBlkTblRcdItr;
    pBlkTblRcd->newIterator( pBlkTblRcdItr );
    for ( pBlkTblRcdItr->start(); !pBlkTblRcdItr->done(); pBlkTblRcdItr->step() )
    {
        AcDbEntity* pEnt;
        if( Acad::eOk != pBlkTblRcdItr->getEntity( pEnt, AcDb::kForRead ) ) continue;

        if( layerName.CompareNoCase( pEnt->layer() ) == 0 )
        {
            ents.append( pEnt->objectId() );
        }
        pEnt->close();
    }
    delete pBlkTblRcdItr;

    pBlkTblRcd->close();

    return true;
}

void ArxLayerHelper::DeleteAllEntitiesOnLayer( const CString& layerName )
{
    AcDbDatabase* pDB = acdbHostApplicationServices()->workingDatabase();
    AcDbBlockTable* pBlkTbl;
    pDB->getSymbolTable( pBlkTbl, AcDb::kForRead );

    AcDbBlockTableRecord* pBlkTblRcd;
    pBlkTbl->getAt( ACDB_MODEL_SPACE, pBlkTblRcd, AcDb::kForRead );
    pBlkTbl->close();

    AcDbBlockTableRecordIterator* pBlkTblRcdItr;
    pBlkTblRcd->newIterator( pBlkTblRcdItr );
    for ( pBlkTblRcdItr->start(); !pBlkTblRcdItr->done(); pBlkTblRcdItr->step() )
    {
        AcDbEntity* pEnt;
        if( Acad::eOk != pBlkTblRcdItr->getEntity( pEnt, AcDb::kForWrite ) ) continue;

        if( layerName.CompareNoCase( pEnt->layer() ) == 0 )
        {
            pEnt->erase( true );
        }
        pEnt->close();
    }
    delete pBlkTblRcdItr;

    pBlkTblRcd->close();
}

void ArxLayerHelper::GetAllLayers( AcStringArray& layers )
{
    AcDbLayerTable* layerTable ;
    Acad::ErrorStatus es ;

    //open the layertable in the current drawing
    if ( Acad::eOk !=  acdbHostApplicationServices()->workingDatabase()->getLayerTable( layerTable, AcDb::kForRead ) )
    {
        //acutPrintf (_T("\nCouldn''t get the layer table")) ;
        return /*false*/;
    }

    //create a new iterator
    AcDbLayerTableIterator* pLayerTableIterator ;
    if ( Acad::eOk != layerTable->newIterator ( pLayerTableIterator ) )
    {
        acutPrintf ( _T( "\nCouldn''t get a new layer table iterator" ) ) ;
        layerTable->close () ;
        //return false ;
    }
    layerTable->close () ;
    AcDbObjectId layerId ;

    //iterate through the all layers and collect their ids
    for ( ; !pLayerTableIterator->done () ; pLayerTableIterator->step() )
    {
        AcDbLayerTableRecord* pRecord;
        if ( Acad::eOk != pLayerTableIterator->getRecord( pRecord, AcDb::kForRead ) )
        {
            //acutPrintf(_T("\nCannot get layers"));
            continue;
        }
        else
        {
            AcString str;
            pRecord->getName( str );
            layers.append( str );
        }
    }
    delete pLayerTableIterator;

    //return true;
}

LayerSwitch::LayerSwitch( const CString& layerName, bool createNewLayer )
{
    // ��¼��ǰͼ��
    m_curLayer = ArxLayerHelper::GetCurrentLayerName();
    acutPrintf( _T( "\n��ǰͼ��:��%s��" ), m_curLayer );

    if( ArxLayerHelper::IsLayerExist( layerName ) )
    {
        ArxLayerHelper::SetCurrentLayer( layerName );
    }
    else if( createNewLayer )
    {
        ArxLayerHelper::AddLayer( layerName ); // ��������򲻽���
        ArxLayerHelper::SetCurrentLayer( layerName );
    }
}

LayerSwitch::~LayerSwitch()
{
    // �л���ԭ����ͼ��
    ArxLayerHelper::SetCurrentLayer( m_curLayer );
}