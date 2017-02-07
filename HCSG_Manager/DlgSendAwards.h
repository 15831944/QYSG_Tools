#pragma once
#include "afxwin.h"
#include "XColorStatic.h"


// CDlgSendAwards 对话框

#define GOODS_NUM	5

class CDlgSendAwards : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSendAwards)

public:
	CDlgSendAwards(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSendAwards();

// 对话框数据
	enum { IDD = IDD_DIALOG_SEND_AWARDS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	CListCtrl m_CListCtrlAcc;
	CListCtrl m_CListCtrlItem;
	CListCtrl m_CListCtrlConfig;
	CEdit m_CEditFindItem;
	CEdit m_CEditItemId[GOODS_NUM];
// 	CEdit m_CEditItemId2;
// 	CEdit m_CEditItemId3;
// 	CEdit m_CEditItemId4;
// 	CEdit m_CEditItemId5;
	CEdit m_CEditItemName[GOODS_NUM];
// 	CEdit m_CEditItemName2;
// 	CEdit m_CEditItemName3;
// 	CEdit m_CEditItemName4;
// 	CEdit m_CEditItemName5;
	CEdit m_CEditItemNum[GOODS_NUM];
// 	CEdit m_CEditItemNum2;
// 	CEdit m_CEditItemNum3;
// 	CEdit m_CEditItemNum4;
// 	CEdit m_CEditItemNum5;
	CComboBox m_CComboBoxCfgID;

	void CDlgSendAwards::Init();
	void CDlgSendAwards::DoOnEnChangeEditItemId(int nIndex);
	afx_msg void OnEnChangeEditItemId();
	afx_msg void OnEnChangeEditItemId2();
	afx_msg void OnEnChangeEditItemId3();
	afx_msg void OnEnChangeEditItemId4();
	afx_msg void OnEnChangeEditItemId5();
	afx_msg void OnBnClickedButtonAddConfig();
	afx_msg void OnBnClickedButtonDelConfig();
	afx_msg void OnBnClickedButtonSaveConfig();
	afx_msg void OnBnClickedButtonReadAcclist();

	CString CDlgSendAwards::GetPathName();
	afx_msg void OnBnClickedButtonSendAwards();
	CEdit m_CEditPoints;
//	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);

	BOOL bIsInit;
};
