#pragma once
#include "afxcmn.h"
#include "afxwin.h"

// CVip 对话框

#define VIP_ITEM_NUM	10

class CVip : public CDialogEx
{
	DECLARE_DYNAMIC(CVip)

public:
	CVip(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CVip();

// 对话框数据
	enum { IDD = IDD_DIALOG_VIP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_CListCtrlAccount;
	CListCtrl m_CListCtrlVipAcc;
	virtual BOOL OnInitDialog();
	CEdit m_CEditAcc;
	CComboBox m_CComboBoxMode;
	CEdit m_CEditPoint;
	CEdit m_CEditNote;
	CEdit m_CEditPoint1;
	CEdit m_CEditNote1;
	CComboBox m_CComboBoxVipConfig;
	CEdit m_CEditVipPoint;
	CEdit m_CEditVipAcc;
	CComboBox m_CComboBoxVip;
	afx_msg void OnBnClickedButtonUpdate();
	CStatic m_CStaticAccTotal;
	afx_msg void OnCbnSelchangeComboVipConfig();
	afx_msg void OnBnClickedSave();

	void UpdataAcc();
	afx_msg void OnNMClickListAccount(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeComboMode();
	afx_msg void OnBnClickedSend();

	int nMode;
	CEdit m_CEditPoints;
	afx_msg void OnBnClickedAddVip();
	afx_msg void OnBnClickedDeleteVip();

	void ReadVipList();
	CEdit m_CEditVipDate;
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	void SendPointToVip();

	CListCtrl m_CListCtrlItem;	
	afx_msg void OnEnChangeEditAcc();
	void InitItemDef();
	CEdit m_CEditVipItemId[VIP_ITEM_NUM];
	CEdit m_CEditVipItemName[VIP_ITEM_NUM];
	CEdit m_CEditVipItemNum[VIP_ITEM_NUM];
	void CVip::DoOnEnChangeEditItemId(int nIndex);
	afx_msg void OnEnChangeEditVipItemId();
	afx_msg void OnEnChangeEditVipItemId2();
	afx_msg void OnEnChangeEditVipItemId3();
	afx_msg void OnEnChangeEditVipItemId4();
	afx_msg void OnEnChangeEditVipItemId5();
	afx_msg void OnEnChangeEditVipItemId6();
	afx_msg void OnEnChangeEditVipItemId7();
	afx_msg void OnEnChangeEditVipItemId8();
	afx_msg void OnEnChangeEditVipItemId9();
	afx_msg void OnEnChangeEditVipItemId10();
	afx_msg void OnNMClickListItem(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonFindItem();
	afx_msg void OnBnClickedButtonFindNextItem();
	CEdit m_CEditFindItem;
	afx_msg void OnEnChangeEditFindAcc();
	afx_msg void OnBnClickedButtonFindNextAcc();
	CEdit m_CEditFindAcc;
	afx_msg void OnEnChangeEditFindItem();
	CXColorStatic m_CStaticCopyRight;
};
