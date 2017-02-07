#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CPlayersDlg �Ի���

class CPlayersDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPlayersDlg)

public:
	CPlayersDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPlayersDlg();

// �Ի�������
	enum { IDD = IDD_PLAYERS_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CEdit m_CEditExpMul;
	CEdit m_CEditSkipExp;
	afx_msg void OnBnClickedButtonExe();
	afx_msg void OnBnClickedButtonExe2();

	CString strCurPath;
	CListCtrl m_CListCtrlAcc;
	CListCtrl m_CListCtrlSkills;

	void LoadAccAttr();
	void LoadAccSkills();
	void DisPlayAccSkills(int nIndex);
	afx_msg void OnBnClickedButtonDelSkill();
	afx_msg void OnNMClickListAccount(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonAccNext();
	afx_msg void OnEnChangeEditFind();
	CEdit m_CEditFind;
	afx_msg void OnEnChangeEditFindSkill();
	CEdit m_CEditFindSkill;
	afx_msg void OnBnClickedButtonSkillNext();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonDelAll();
	CEdit m_CEditAccounts;
	CEdit m_CEditSkillID;
};
