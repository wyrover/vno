#include "stdafx.h"

// ִ��zoom����
void ExecuteZoomCommand1( const AcGePoint3d& minPt, const AcGePoint3d& maxPt )
{
    /*
     * ���������(һ)
     * �������cad�е�ִ��˳�����뼴��
     * �ո��ʾ�س�
     * ע�⣺�����ַ������һ��Ҫ��һ���ո�(�س�)
     */
    CString cmd;
    cmd.Format( _T( "ZOOM W %.3f,%.3f,%.3f %.3f,%.3f,%.3f " ), minPt.x, minPt.y, minPt.z, maxPt.x, maxPt.y, maxPt.z );
    acDocManager->sendStringToExecute( curDoc(), cmd, true, false, false ); // ����ʾ����ִ�й���
}

void ExecuteZoomCommand2( const AcGePoint3d& minPt, const AcGePoint3d& maxPt )
{
    /*
     * ���������(��)
     * ע��acedCommand������modeless dialog���޷�ʹ��
     * �ο�: "Code Differences under the Application Execution Context" topic in ARX docs
     */
    // ����cad���ZOOM-->W (���ŵ�ͼԪ�Ĵ��ڷ�Χ)
    acedCommand( RTSTR, _T( "ZOOM" ), RTSTR, _T( "W" ), RT3DPOINT, asDblArray( minPt ), RT3DPOINT, asDblArray( maxPt ), 0 );
    //acedCommand(RTSTR, _T("ZOOM"), RTSTR, _T("A"), 0);
}

// don't forget to add for Autocad2007/2008/2009 this line
//#import "acax17enu.tlb" no_implementation raw_interfaces_only named_guids

// for Autocad2010/2011/2012 this line
// �����"no_implementation raw_interfaces_only named_guids"����ɾ��!!!
//#import "acax18enu.tlb" no_implementation raw_interfaces_only named_guids
//
//static void ZommWindowUseCom(const AcGePoint3d& minPt, const AcGePoint3d& maxPt)
//{
//	AcGePoint3d plLowerLeft = minPt, ptUpperRight = maxPt; //-> it's your object extends coords
//
//	long i = 0;
//	CComPtr<AutoCAD::IAcadApplication> IApp;
//	CComPtr<IDispatch> pDisp = acedGetAcadWinApp()->GetIDispatch(TRUE);
//	if(!pDisp) return;
//	HRESULT hr = pDisp->QueryInterface(AutoCAD::IID_IAcadApplication,(void**)&IApp);
//
//
//	SAFEARRAYBOUND rgsaBound;
//	rgsaBound.lLbound = 0L;
//	rgsaBound.cElements = 3;
//	SAFEARRAY* pLLPoint = NULL;
//	pLLPoint = SafeArrayCreate(VT_R8, 1, &rgsaBound);
//	// X value
//
//	SafeArrayPutElement(pLLPoint, &i, &plLowerLeft.x); i++;
//	SafeArrayPutElement(pLLPoint, &i, &plLowerLeft.y); i++;// Y value
//	SafeArrayPutElement(pLLPoint, &i, &plLowerLeft.z);// Z value
//	VARIANT ptLL;
//	VariantInit(&ptLL);
//	V_VT(&ptLL) = VT_ARRAY | VT_R8;
//	V_ARRAY(&ptLL) = pLLPoint;
//
//
//	SAFEARRAY* pURPoint = NULL;
//	pURPoint = SafeArrayCreate(VT_R8, 1, &rgsaBound);
//	i = 0;
//	SafeArrayPutElement(pURPoint, &i, &ptUpperRight.x);i++;// X value
//	SafeArrayPutElement(pURPoint, &i, &ptUpperRight.y);i++;// Y value
//	SafeArrayPutElement(pURPoint, &i, &ptUpperRight.z);// Z value
//	VARIANT ptUR;
//	VariantInit(&ptUR);
//	V_VT(&ptUR) = VT_ARRAY | VT_R8;
//	V_ARRAY(&ptUR) = pURPoint;
//
//	IApp->ZoomWindow(ptLL,ptUR); // zooming
//
//	VariantClear(&ptLL);
//	VariantClear(&ptUR);
//}

static void GetCurrentView( AcDbViewTableRecord& view )
{
    struct resbuf rb;
    struct resbuf wcs, ucs, dcs; // ת������ʱʹ�õ�����ϵ

    wcs.restype = RTSHORT;
    wcs.resval.rint = 0;
    ucs.restype = RTSHORT;
    ucs.resval.rint = 1;
    dcs.restype = RTSHORT;
    dcs.resval.rint = 2;

    // ��õ�ǰ�ӿڵġ��鿴��ģʽ
    acedGetVar( _T( "VIEWMODE" ), &rb );
    view.setPerspectiveEnabled( rb.resval.rint & 1 );
    view.setFrontClipEnabled( rb.resval.rint & 2 );
    view.setBackClipEnabled( rb.resval.rint & 4 );
    view.setFrontClipAtEye( !( rb.resval.rint & 16 ) );

    // ��ǰ�ӿ�����ͼ�����ĵ㣨UCS���꣩
    acedGetVar( _T( "VIEWCTR" ), &rb );
    acedTrans( rb.resval.rpoint, &ucs, &dcs, 0, rb.resval.rpoint );
    view.setCenterPoint( AcGePoint2d( rb.resval.rpoint[X],
                                      rb.resval.rpoint[Y] ) );

    // ��ǰ�ӿ�͸��ͼ�еľ�ͷ���೤�ȣ���λΪ���ף�
    acedGetVar( _T( "LENSLENGTH" ), &rb );
    view.setLensLength( rb.resval.rreal );

    // ��ǰ�ӿ���Ŀ����λ�ã��� UCS �����ʾ��
    acedGetVar( _T( "TARGET" ), &rb );
    acedTrans( rb.resval.rpoint, &ucs, &wcs, 0, rb.resval.rpoint );
    view.setTarget( AcGePoint3d( rb.resval.rpoint[X],
                                 rb.resval.rpoint[Y], rb.resval.rpoint[Z] ) );
    // ��ǰ�ӿڵĹ۲췽��UCS��
    acedGetVar( _T( "VIEWDIR" ), &rb );
    acedTrans( rb.resval.rpoint, &ucs, &wcs, 1, rb.resval.rpoint );
    view.setViewDirection( AcGeVector3d( rb.resval.rpoint[X],
                                         rb.resval.rpoint[Y], rb.resval.rpoint[Z] ) );

    // ��ǰ�ӿڵ���ͼ�߶ȣ�ͼ�ε�λ��
    acedGetVar( _T( "VIEWSIZE" ), &rb );
    view.setHeight( rb.resval.rreal );
    double height = rb.resval.rreal;

    // ������Ϊ��λ�ĵ�ǰ�ӿڵĴ�С��X �� Y ֵ��
    acedGetVar( _T( "SCREENSIZE" ), &rb );
    view.setWidth( rb.resval.rpoint[X] / rb.resval.rpoint[Y] * height );

    // ��ǰ�ӿڵ���ͼŤת��
    acedGetVar( _T( "VIEWTWIST" ), &rb );
    view.setViewTwist( rb.resval.rreal );

    // ��ģ��ѡ������һ������ѡ���Ϊ��ǰ
    acedGetVar( _T( "TILEMODE" ), &rb );
    int tileMode = rb.resval.rint;
    // ���õ�ǰ�ӿڵı�ʶ��
    acedGetVar( _T( "CVPORT" ), &rb );
    int cvport = rb.resval.rint;

    // �Ƿ���ģ�Ϳռ����ͼ
    bool paperspace = ( ( tileMode == 0 ) && ( cvport == 1 ) ) ? true : false;
    view.setIsPaperspaceView( paperspace );

    if ( !paperspace )
    {
        // ��ǰ�ӿ���ǰ�����ƽ�浽Ŀ��ƽ���ƫ����
        acedGetVar( _T( "FRONTZ" ), &rb );
        view.setFrontClipDistance( rb.resval.rreal );

        // ��õ�ǰ�ӿں������ƽ�浽Ŀ��ƽ���ƫ��ֵ
        acedGetVar( _T( "BACKZ" ), &rb );
        view.setBackClipDistance( rb.resval.rreal );
    }
    else
    {
        view.setFrontClipDistance( 0.0 );
        view.setBackClipDistance( 0.0 );
    }
}

void ZoomWindowUseView( const AcGePoint3d& minPt, const AcGePoint3d& maxPt )
{
    ads_pointp pt1 = asDblArray( minPt );
    ads_pointp pt2 = asDblArray( maxPt );

    struct resbuf wcs, ucs, dcs; // ת������ʱʹ�õ�����ϵͳ
    wcs.restype = RTSHORT;
    wcs.resval.rint = 0;
    ucs.restype = RTSHORT;
    ucs.resval.rint = 1;
    dcs.restype = RTSHORT;
    dcs.resval.rint = 2;
    acedTrans( pt1, &ucs, &dcs, 0, pt1 );
    acedTrans( pt2, &ucs, &dcs, 0, pt2 );

    AcDbViewTableRecord view;
    GetCurrentView( view );

    // ������ͼ�����ĵ�
    view.setCenterPoint( AcGePoint2d( ( pt1[X] + pt2[X] ) / 2, ( pt1[Y] + pt2[Y] ) / 2 ) );

    // ������ͼ�ĸ߶ȺͿ��
    view.setHeight( fabs( pt1[Y] - pt2[Y] ) );
    view.setWidth( fabs( pt1[X] - pt2[X] ) );

    // ����ͼ��������Ϊ��ǰ��ͼ
    acedSetCurrentView( &view, NULL );
}

// google����������˵acgsGetGsViewֻ����3dģʽ������������
// 2dģʽ����null�������2������bCreateIfNone=true��������viewҲ��3d��
// �������飬Ҳȷʵ���...
// �ؼ��ʣ�"SHADEMODE and AcGsView",
// ��Դ: Autodesk Discussion Groups
static AcGsView* GetGsView()
{
    resbuf rbCvport;
    acedGetVar( _T( "CVPORT" ), &rbCvport );
    int iVport = rbCvport.resval.rint;

    resbuf rbTile;
    acedGetVar( _T( "TILEMODE" ), &rbTile );
    int iTile = rbTile.resval.rint;

    acutPrintf( _T( "\n�ӿ�:%d, ģ�Ϳռ�ѡ�:%d" ), iVport, iTile );

    if( iTile == 0 && iVport == 1 )
    {
        acutPrintf( _T( "\nģ�Ϳռ�ѡ�û�м���" ), iVport );
        return 0;
    }
    return acgsGetGsView( iVport, false );
}

void ZoomWindowUseGSView( const AcGePoint3d& minPt, const AcGePoint3d& maxPt )
{
    AcGsView* pView = GetGsView();
    if( pView == 0 )
    {
        acutPrintf( _T( "\n��ȡGsViewָ��ʧ��" ) );
        return;
    }

    pView->zoomExtents( minPt, maxPt );
    pView->invalidate();
    pView->update();
}
