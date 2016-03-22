#pragma once

#include "resource.h"
#include "SouiDialog.h"

class EmbedSouiDlg : public CDialog
{
	DECLARE_DYNAMIC(EmbedSouiDlg)

public:
	EmbedSouiDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~EmbedSouiDlg();

// 对话框数据
	enum { IDD = IDD_SOUI_EMBED_DLG };

	//子对话框(soui)
public:
	SouiDialog dlg;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
};
