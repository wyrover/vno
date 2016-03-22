#pragma once

#include "resource.h"
#include "SouiDialog.h"

class EmbedSouiDlg : public CDialog
{
	DECLARE_DYNAMIC(EmbedSouiDlg)

public:
	EmbedSouiDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~EmbedSouiDlg();

// �Ի�������
	enum { IDD = IDD_SOUI_EMBED_DLG };

	//�ӶԻ���(soui)
public:
	SouiDialog dlg;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
};
