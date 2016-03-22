#include "StdAfx.h"
#include "SystemHelper.h"
#include "HelperClass.h"
#include "config.h"

void SystemHelper::Start()
{
    // ע��dictionary��regAppName
    ArxDictTool::RegDict( PROPERTY_DATA_FIELD_DICT );
    ArxDictTool::RegDict( PROPERTY_DATA_FIELD_INFO_DICT );
    ArxDictTool::RegDict( FUNC_FIELD_DICT );

    //ArxDataTool::RegAppName( acdbHostApplicationServices()->workingDatabase(), DRAW_PARAMS_XDATA_GROUP );

    //������ע��ʽ
    ArxDrawHelper::CreateDimStyle( DIM_STYLE_NAME, false, 1 );
	ArxDrawHelper::CreateDimStyle( DIM_STYLE_NAME2, false, 0.5 );
	ArxDrawHelper::CreateDimStyle( DIM_STYLE_NAME3, false, 0.5 );
}

void SystemHelper::ShutDown()
{

}
