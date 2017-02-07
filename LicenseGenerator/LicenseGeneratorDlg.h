
// LicenseGeneratorDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CLicenseGeneratorDlg 对话框
class CLicenseGeneratorDlg : public CDialogEx
{
// 构造
public:
	CLicenseGeneratorDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_LICENSEGENERATOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit mCEditMachineCode;
	CEdit mCEditStartDate;
	CEdit mCEditEndDate;
	CEdit mCEditName;
	afx_msg void OnBnClickedGenerator();
	afx_msg void OnBnClickedDecode();
	char cKey[1024];
	void Encrypt();
	void Decode(struct sLicense *TmpLicense);	
};
