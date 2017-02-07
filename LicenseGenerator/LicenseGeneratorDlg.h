
// LicenseGeneratorDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CLicenseGeneratorDlg �Ի���
class CLicenseGeneratorDlg : public CDialogEx
{
// ����
public:
	CLicenseGeneratorDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_LICENSEGENERATOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
