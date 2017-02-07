#pragma once
#include "afxwin.h"


// CDropItemDlg 对话框

class CDropItemDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDropItemDlg)

public:
	CDropItemDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDropItemDlg();

// 对话框数据
	enum { IDD = IDD_DROP_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CEdit m_CEditPath;
	CRichEditCtrl m_RichEditResult;
	afx_msg void OnBnClickedScan();
	afx_msg void OnBnClickedRun();
	CListCtrl m_CListCtrlCount;
	CListCtrl m_CListCtrlItem;
	CListCtrl m_CListCtrlPlayers;
	CListCtrl m_CListCtrlDrops;
	void InitItemDef();
	void InitPlayers();
	void InitBagsDrop();
	afx_msg void OnNMClickListPlayers(NMHDR *pNMHDR, LRESULT *pResult);
	CEdit m_CEditName;
	CEdit m_CEditCounter;
	afx_msg void OnEnChangeEditFind();
	CEdit m_CEditFind;
	afx_msg void OnBnClickedButtonPlayerNext();
	CEdit m_CEditFindItem;
	afx_msg void OnEnChangeEditFindItem();
	afx_msg void OnBnClickedButtonItemNext();
	afx_msg void OnNMClickListItem(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListDrops(NMHDR *pNMHDR, LRESULT *pResult);
	CEdit m_CEditItemName;
	CEdit m_CEditDropRange;
	CEdit m_CEditItemName2;
	CEdit m_CEditDropRange2;
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonDel();
	CEdit m_CEditDropId;
	void DoDropListSort();
	void DoDropListSortTemp(CString strDropId);
	afx_msg void OnBnClickedButtonSaveDrop();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButtonModify();
	CEdit m_CEditItemNameTemp;
	CEdit m_CEditItemNameTemp2;
	afx_msg void OnBnClickedButtonDropTxt();
	CListCtrl m_CListCtrlDropsTemp;
	afx_msg void OnBnClickedButtonExe();
	CEdit m_CEditGreater;
	CEdit m_CEditLess;
	CEdit m_CEditInc;
	CEdit m_CEditDec;
	CEdit m_CEditMul;
	CEdit m_CEditFixed;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedFix();
	CEdit m_CEditFixItem;
	CStatic m_CStaticCounter;
};
