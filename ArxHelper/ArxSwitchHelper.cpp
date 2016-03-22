#include "StdAfx.h"
#include "ArxSwitchHelper.h"

ArxTolSetter::ArxTolSetter( double eq )
{
	m_originEq = AcGeContext::gTol.equalPoint();
	setEq( eq );
}

void ArxTolSetter::setEq( double eq )
{
	AcGeContext::gTol.setEqualPoint( eq );
}

ArxTolSetter::~ArxTolSetter()
{
	AcGeContext::gTol.setEqualPoint( m_originEq );
}


ArxDocLockSwitch::ArxDocLockSwitch()
{
	acDocManager->lockDocument( curDoc() );
}
ArxDocLockSwitch::~ArxDocLockSwitch()
{
	acDocManager->unlockDocument( curDoc() );
}

//���캯������controlbar
ArxCtrlBarShowSwitch::ArxCtrlBarShowSwitch( CWnd* _dlg ) : dlg( _dlg )
{
	ShowParentControlBar( dlg, FALSE );
}
//����������ʾcontrolbar
ArxCtrlBarShowSwitch::~ArxCtrlBarShowSwitch()
{
	ShowParentControlBar( dlg, TRUE );
}

void ArxCtrlBarShowSwitch::ShowParentControlBar( CWnd* pWnd, BOOL bShow )
{
	CAcModuleResourceOverride myResources;
	CControlBar* pBar = reinterpret_cast<CControlBar*>( pWnd->GetParent() );
	if( pBar == 0 ) return;

	CMDIFrameWnd* pAcadFrame = acedGetAcadFrame();
	if( pAcadFrame == 0 ) return;

	pAcadFrame->ShowControlBar( pBar, bShow, FALSE );
}


//���캯������
ArxDialogShowSwitch::ArxDialogShowSwitch( CWnd* _dlg ) : dlg( _dlg )
{
	dlg->ShowWindow( SW_HIDE );
	////������֮������CAD����ʧȥ����
	//dlg->SetFocus();
}
//����������ʾ
ArxDialogShowSwitch::~ArxDialogShowSwitch()
{
	dlg->ShowWindow( SW_SHOW );
}
