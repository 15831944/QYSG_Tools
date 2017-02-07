#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CArmyDlg 对话框

class CArmyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CArmyDlg)

public:
	CArmyDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CArmyDlg();

// 对话框数据
	enum { IDD = IDD_ARMY_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_CListCtrlPlayers;
	CListCtrl m_CListCtrlDrops;
	CEdit m_CEditName;
	CEdit m_CEditCounter;
	CEdit m_CEditFind;
	CEdit m_CEditDropId;

	CString strCurSelBoss;

	void InitPlayers();
	void InitArmyLists();
	void InitStageList();
	void DoDropListSort();
	CString ConvertMapList(CString MapList);
	afx_msg void OnEnChangeEditFind();
	afx_msg void OnBnClickedButtonPlayerNext();
	afx_msg void OnNMClickListPlayers(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_CListCtrlArmys;
	CEdit m_CEditStageFind;
	CListCtrl m_CListCtrlStageDef;
	CEdit m_CEditCode;
	CEdit m_CEditArmyNameId;
	CEdit m_CEditArmyName;
	CEdit m_CEditRebornDelay;
	CEdit m_CEditRebornRange;
	CEdit m_CEditDisappearTime;
	CEdit m_CEditMapName;
	CEdit m_CEditMapId;
	CEdit m_CEditMapX;
	CEdit m_CEditMapY;
	CEdit m_CEditBossName;
	CListCtrl m_CListCtrlMapList;
	CListCtrl m_CListCtrlBossList;
	afx_msg void OnBnClickedButtonOutput();
	CEdit m_CEditCode2;
	CEdit m_CEditArmyNameId2;
	CEdit m_CEditArmyName2;
	CEdit m_CEditRebornDelay2;
	CEdit m_CEditRebornRange2;
	CEdit m_CEditDisappearTime2;
	afx_msg void OnBnClickedButtonAddOrg();
	afx_msg void OnBnClickedButtonArmySave();
	afx_msg void OnBnClickedButtonAuto();
	afx_msg void OnEnChangeEditArmyNameId2();
	afx_msg void OnNMClickArmyList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeEditArmyNameId();
	afx_msg void OnBnClickedButtonDelOrg();
	afx_msg void OnEnChangeEditOrgFind();
	CEdit m_CEditOrgFind;
	afx_msg void OnBnClickedButtonOrgNext();
	afx_msg void OnBnClickedButtonReflash();
	afx_msg void OnEnChangeEditStageFind();
	afx_msg void OnBnClickedButtonStageNext();
	afx_msg void OnNMClickListStagedef(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeEditMapId();
	afx_msg void OnBnClickedButtonAddMap();
	afx_msg void OnBnClickedButtonDelMap2();
	afx_msg void OnBnClickedButtonAddBoss();
	afx_msg void OnBnClickedButtonDelBoss();
	afx_msg void OnBnClickedButtonSync();
};
